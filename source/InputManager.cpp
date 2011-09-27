
#include "InputManager.h"

InputManager::InputManager()
{
	for( int iKey = 0; iKey < SDLK_LAST; ++iKey )
	{
		m_aKeys[iKey] = false;
		m_aKeysLast[iKey] = false;
	}
}

InputManager::~InputManager()
{

}

void InputManager::Update(SDL_Event& a_kEvent)
{
	while( SDL_PollEvent(&a_kEvent) )
	{
		if( a_kEvent.type == SDL_KEYDOWN )
		{
			m_aKeys[a_kEvent.key.keysym.sym] = true;
		}
		else if( a_kEvent.type == SDL_KEYUP )
		{
			m_aKeys[a_kEvent.key.keysym.sym] = false;
		}
		else
		{
			continue;
		}
	}
}

bool InputManager::IsKeyDown( int a_eSDLKey )
{
	return m_aKeys[a_eSDLKey];
}

bool InputManager::IsKeyPressed( int a_eSDLKey )
{
	// if it wasn't down the previous frame, and is down now, it's pressed
	if( m_aKeys[a_eSDLKey] && !m_aKeysLast[a_eSDLKey] )
	{
		m_aKeysLast[a_eSDLKey] = true;
		return true;
	}
	// if it isn't down the current frame, and was last frame it's not pressed
	else if( !m_aKeys[a_eSDLKey] && m_aKeysLast[a_eSDLKey] )
	{
		m_aKeysLast[a_eSDLKey] = false;
	}

	return false;
}
