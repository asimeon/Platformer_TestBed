
#include "ObjectActive.h"

ObjectActive::ObjectActive()
{
	OnInit();
}

ObjectActive::~ObjectActive()
{
	OnUnInit();
}

bool ObjectActive::OnInit()
{
	m_uiTextureID = 0;
	m_fTextureWidth	= 0.0f;
	m_fTextureHeight = 0.0f;
}

bool ObjectActive::OnUnInit()
{

}

void ObjectActive::Update( float a_fDeltaTime )
{

}

void ObjectActive::Render()
{

}
