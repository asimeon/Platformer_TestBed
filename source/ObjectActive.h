
#ifndef OBJECTACTIVE_H
#define OBJECTACTIVE_H

#include "ObjectLoadable.h"
#include "SDL_opengl.h"

class ObjectActive : public ObjectLoadable
{
public:
	ObjectActive();
	virtual ~ObjectActive();

	virtual bool OnInit();
	virtual bool OnUnInit();

	virtual void Update(float a_fDeltaTime);
	virtual void Render();

private:
	GLuint m_uiTextureID;
	float m_fTextureWidth;
	float m_fTextureHeight;
};

#endif // OBJECTACTIVE_H
