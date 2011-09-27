
#ifndef SCENE_H
#define SCENE_H

#include "ObjectLoadable.h"

class Scene : public ObjectLoadable
{
public:
	Scene();
	virtual ~Scene();

	virtual bool OnInit() = 0;
	virtual bool OnUnInit() = 0;

	virtual void Update( float a_fDeltaTime ) = 0;
	virtual void Render() = 0;
};

#endif // SCENE_H
