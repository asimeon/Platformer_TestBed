
#ifndef SCENETITLESCREEN_H
#define SCENETITLESCREEN_H

#include "Scene.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// \class	SceneTitleScreen
//
// \brief	Scene title screen. 
//
// \author	Andrew
// \date	9/27/2011
////////////////////////////////////////////////////////////////////////////////////////////////////

class SceneTitleScreen : public Scene
{
public:
	SceneTitleScreen();
	virtual ~SceneTitleScreen();


	virtual bool OnInit();
	virtual bool OnUnInit();

	virtual void Update( float a_fDeltaTime );
	virtual void Render();
};

#endif // SCENETITLESCREEN_H
