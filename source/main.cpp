
#include <SDL.h>

#include "Core.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SceneTitleScreen.h"

#ifdef _DEBUG
#include <vld.h>
#include <conio.h>
#endif

int SDL_main(int argc, char* argv[])
{
	Core::GetInstance()->OnInit();
	InputManager kInput;

	SceneManager::GetInstance(); // initialise SceneManager.

	bool bDone = false;

	SceneTitleScreen* pSceneTitleScreen = new SceneTitleScreen;
	SceneManager::GetInstance()->PushScene(pSceneTitleScreen);

	SDL_Event kEvent;

	float fDeltaTime = 0.0f;
	float fPrevTime = 0.0f;
	float fCurrTime = 0.0f;

	while(!bDone)
	{
		fPrevTime = fCurrTime;
		fCurrTime = (float)SDL_GetTicks();
		fDeltaTime = (fCurrTime - fPrevTime) / 1000.f;

		char buf[256];
		sprintf(buf, "PrevTicks: %f, CurrTicks: %f, DeltaTime: %f\n", fPrevTime, fCurrTime, fDeltaTime);
		printf(buf);

		SceneManager::GetInstance()->RunCurrentScene(fDeltaTime);

		while(SDL_PollEvent(&kEvent))
		{
			if( kEvent.type == SDL_QUIT )
			{
				bDone = true;
				break;
			}
		}

		kInput.Update(kEvent);
	}

	SceneManager::GetInstance()->DestroyInstance();
	Core::GetInstance()->DestroyInstance();

	return 0;
}
