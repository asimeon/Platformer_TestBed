
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void Update(SDL_Event& a_kEvent);

	bool IsKeyDown( int a_eSDLKey );
	bool IsKeyPressed( int a_eSDLKey );

private:
	bool m_aKeys[SDLK_LAST];
	bool m_aKeysLast[SDLK_LAST];
};

#endif // INPUTMANAGER_H
