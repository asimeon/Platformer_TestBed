
#include <SDL.h>
#include "Core.h"

#include <vld.h>

int SDL_main(int argc, char* argv[])
{
	Core::GetInstance()->OnInit();

	bool bDone = false;

	while(!bDone)
	{
		
	}

	Core::GetInstance()->OnUninit();

	return 0;
}
