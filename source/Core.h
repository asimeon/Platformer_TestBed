
#ifndef _CORE_H_
#define _CORE_H_

#ifndef NULL
#define NULL 0
#endif

#define MAX_TEXTURE_SIZE 4096

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

// Default defines
#define DEFAULT_WINDOW_NAME				"Platformer_TestBed"
#define DEFAULT_WINDOW_WIDTH			1280
#define DEFAULT_WINDOW_HEIGHT			720
#define DEFAULT_WINDOW_FULLSCREEN		0 // 0: windowed; 1: fullscreen

struct Colour
{
	Colour()
	{
		Red = Green = Blue = 0; // black
	}

	Colour(float a_fRed, float a_fGreen, float a_fBlue)
	{
		Red = a_fRed;
		Green = a_fGreen;
		Blue = a_fBlue;
	}

	float Red;
	float Green;
	float Blue;
};

class Core
{
public:
	~Core();

	static Core* GetInstance();
	void DestroyInstance();

	int OnInit();
	int OnUninit();

	int LoadTexture( const char* File );

private:
	Core();

	size_t GoodTextureValue( size_t value );

	static Core* m_pInstance;
};

#endif // _CORE_H_
