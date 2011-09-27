
#include "Core.h"
#include <conio.h>

Core* Core::m_pInstance = NULL;

Core::Core()
{

}

Core::~Core()
{
	OnUninit();
}

Core* Core::GetInstance()
{
	if( m_pInstance == NULL )
	{
		m_pInstance = new Core;
	}

	return m_pInstance;
}

void Core::DestroyInstance()
{
	if( m_pInstance != NULL )
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

int Core::OnInit()
{
	printf( "Starting SDL ... " );

	int error = 0;

	error = SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER );

	// Set up GL settings.
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 32 );
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );

	SDL_WM_SetCaption( DEFAULT_WINDOW_NAME, NULL );

	int flags = SDL_OPENGL | SDL_HWSURFACE | ( DEFAULT_WINDOW_FULLSCREEN ? SDL_FULLSCREEN : 0 );

	SDL_SetVideoMode( DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, 32, flags );

	glClearColor( 0.0, 0.0, 0.0, 0.0 );

	glViewport( 0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT );

	// Set up orthographic projection (flat z)
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0.0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, 0.0, -1.0, 1.0 );
	//glOrtho( -w/2, w/2, h/2, -h/2, -1, 1 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	// Enable 2D textures
	glEnable( GL_TEXTURE_2D );

	// Enable blending (transparencies)
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	// Disable vsync
	typedef void (APIENTRY * WGLSWAPINTERVALEXT) (int);
	WGLSWAPINTERVALEXT wglSwapIntervalEXT = (WGLSWAPINTERVALEXT)
		wglGetProcAddress("wglSwapIntervalEXT");
	if (wglSwapIntervalEXT)
	{
		wglSwapIntervalEXT(0); // disable vertical synchronization
	}

	// Hide cursor
	SDL_ShowCursor(SDL_DISABLE);

	if( error == 0 ) printf( "done\n" );

	return error;
}

int Core::OnUninit()
{
	SDL_Quit();

	return 0;
}

int Core::LoadTexture( const char* File )
{
	printf( "Loading texture %s ... ", File );
	// Load the image using SDL.
	SDL_Surface* imageFile = IMG_Load( File );

	if( imageFile == NULL )
	{
		printf( "failed: %s", IMG_GetError() );
		return -1;
	}

	// 1 dimensional array, just an easy way to create a pointer to an integer
	// and have it contain something.
	GLuint TextureNum[1];

	// Standard GL texture creation code.
	glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );

	// Create the texture
	glGenTextures( 1, TextureNum );

	// Bind the texture, this is the current texture being worked on in GL
	glBindTexture( GL_TEXTURE_2D, TextureNum[0] );

	// Now the image file may not be in a nice friendly format
	// This format structure stores format information
	// this will be used to guarantee that the image is in a 32bit format
	SDL_PixelFormat Format;

	Format.Aloss = Format.Rloss = Format.Bloss = Format.Gloss = 0;
	Format.BitsPerPixel = 32;
	Format.BytesPerPixel = 4;
	Format.Rshift = 0; Format.Gshift = 8; Format.Bshift = 16; Format.Ashift = 24; // bit locations for each channel
	Format.Rmask = 0xFF; Format.Gmask = 0xFF00; Format.Bmask = 0xFF0000; Format.Amask = 0xFF000000; // a Mask you can use to access each channel
	Format.colorkey = 0xFF00FF; // Transparent colorkey
	Format.alpha = 255; // max alpha
	Format.palette = NULL;

	SDL_Surface *Image = SDL_ConvertSurface( imageFile, &Format, 0 );

	SDL_FreeSurface( imageFile );

	int newWidth = Image->w;
	int newHeight = Image->h;

	bool Rescale = false;

	// Is the width and the height off the image powers of 2, if not,
	// what is the next largest power of 2 that will work?
	if( GoodTextureValue( Image->w ) != 0 )
	{
		Rescale = true;
		newWidth = GoodTextureValue( Image->w );
	}

	if( GoodTextureValue( Image->h ) != 0 )
	{
		Rescale = true;
		newHeight = GoodTextureValue( Image->h );
	}

	// If the image needs to be rescaled..
	if( Rescale )
	{
		// Create a new blank image large enough to take the new resized image in the correct format.
		SDL_Surface* RescaleImage = SDL_CreateRGBSurface( Image->flags, newWidth, newHeight, Image->format->BitsPerPixel,
			Image->format->Rmask, Image->format->Gmask, Image->format->Bmask, Image->format->Amask );

		// Lock the surfaces, grabs memory to make sure the graphics card doesn't have it and we cna get true write access to it.
		SDL_LockSurface( RescaleImage );
		SDL_LockSurface( Image );

		// SDL has no scaling of images, so we have to use GL utility function scale image
		gluScaleImage( GL_RGBA, Image->w, Image->h, GL_UNSIGNED_BYTE, Image->pixels,
			RescaleImage->w, RescaleImage->h, GL_UNSIGNED_BYTE, RescaleImage->pixels );

		// Unlock for normal use
		SDL_UnlockSurface( RescaleImage );
		SDL_UnlockSurface( Image );

		// Free old image.
		SDL_FreeSurface( Image );

		// Set the image to be the new rescaled image.
		Image = RescaleImage;
	}

	// Sets up filtering parameters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// This copies the SDL image in our known format into the GL texture
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Image->w, Image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, Image->pixels );

	printf( "done\n" );

	// Return the GL image
	return TextureNum[0];
}

size_t Core::GoodTextureValue( size_t value )
{

	size_t i = 2;

	for( ; i <= MAX_TEXTURE_SIZE; i *= 2 )
	{
		if( value == i )
			return 0;

		// If texture size is bigger than the value
		// then we have gone past it.
		// return the value to upscale to.
		if( value < i )
			return i;
	}

	return i;
}

void Core::UpdateDirtyRect( SDL_Rect a_kRect )
{
	// if supplied x is less than the current x, make the dirty x to supplied
	if( m_kDirtyRect.x > a_kRect.x )
	{
		m_kDirtyRect.x = a_kRect.x;
	}

	// width
	if( m_kDirtyRect.x + m_kDirtyRect.w < a_kRect.x + a_kRect.w )
	{
		float fWidth = a_kRect.x + a_kRect.w;
	}

	// if supplied y is less than the current y, make the dirty y to supplied
	if( m_kDirtyRect.y > a_kRect.y )
	{
		m_kDirtyRect.y = a_kRect.y;
	}

	// height
	if( m_kDirtyRect.y + m_kDirtyRect.h < a_kRect.y + a_kRect.h )
	{
		float fWidth = a_kRect.x + a_kRect.w;
	}
}
