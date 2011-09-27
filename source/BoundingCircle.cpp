
#include "BoundingCircle.h"

BoundingCircle::BoundingCircle()
	: Bounds(BOUNDTYPE_CIRCLE)
{
	m_fRadius = 0.0f;
}

BoundingCircle::BoundingCircle( float a_fRadius, Vector3f a_kCenter )
	: Bounds(BOUNDTYPE_CIRCLE)
{
	m_fRadius = a_fRadius;
	m_kCenter = a_kCenter;
}

//override pure
bool BoundingCircle::IsPointInside( Vector3f a_kPoint )
{
	float fDistance = (m_kCenter - a_kPoint).Magnitude();
	
	if (fDistance < m_fRadius)
	{
		return true;
	}

	return false;
}

//override pure
void BoundingCircle::Update( Vector3f a_kPosition, float a_fOrientation )
{
	m_kCenter = a_kPosition + m_kCenterOffset;
}

Bounds::VerticeList BoundingCircle::GetVerticies()
{
	m_vVerts.clear();
	m_vVerts.push_back(m_kCenter);
	return m_vVerts;
}

void BoundingCircle::AddCollisionLinesToDebugDrawer(CDebugLineDrawer* pDebugLineDrawer )
{
// 	float fAngleIncrement = (3.14159265f * 2.0f) / 20.0f;
// 
// 	for(unsigned int i = 0; i < 21; i++)
// 	{
// 		pDebugLineDrawer->AddLine(this->GetCenter() + Vector3f(sinf(fAngleIncrement * (float)i) * this->m_fRadius, 0, 
// 			cosf(fAngleIncrement * (float)i) * this->m_fRadius), this->GetCenter() + Vector3f(sinf(fAngleIncrement * (float)(i+1)) * this->m_fRadius, 0, 
// 			cosf(fAngleIncrement * (float)(i+1)) * this->m_fRadius) );
// 	}
}