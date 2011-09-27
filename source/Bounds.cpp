
#include "Bounds.h"
#include "Collision.h"

Bounds::Bounds( BOUNDTYPE a_eType )
{
	m_eBoundingType = a_eType;
	m_fOrientation = 0.0f;
	m_kCenter = Vector3f();
	m_kCenterOffset = Vector3f();

	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
}

Bounds::Bounds(Bounds& other)
{
	m_eBoundingType = other.m_eBoundingType;
	m_fOrientation = other.m_fOrientation;
	m_kCenter = other.m_kCenter;
	m_kCenterOffset = other.m_kCenterOffset;

	m_fWidth = other.m_fWidth;
	m_fHeight = other.m_fHeight;
}

Bounds::~Bounds()
{
}

ContactData Bounds::Intersects( Bounds* a_pOther )
{
	Collision kCollision;
	return kCollision.TestIntersection(this, a_pOther);
}
