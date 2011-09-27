
#include "BoundingAABB.h"
#include "Collision.h"

BoundingAABB::BoundingAABB()
	: Bounds(Bounds::BOUNDTYPE_AABB)
{
	m_kMin = Vector3f();
	m_kMax = Vector3f();

	//m_kDebugColor = NiColorA((NiRand() % 100) / 100.f, (NiRand() % 100) / 100.f, (NiRand() % 100) / 100.f, 1);
}

BoundingAABB::BoundingAABB( Vector3f a_kMin, Vector3f a_kMax )
	: Bounds(Bounds::BOUNDTYPE_AABB)
{
	m_kMin = a_kMin;
	m_kMax = a_kMax;

	Repair();
}

void BoundingAABB::Repair()
{
	float fTemp = .0f;

	if( m_kMin.x > m_kMax.x )
	{
		fTemp = m_kMin.x;
		m_kMin.x = m_kMax.x;
		m_kMax.x = fTemp;
	}
	
	if( m_kMin.y > m_kMax.y )
	{
		fTemp = m_kMin.y;
		m_kMin.y = m_kMax.y;
		m_kMax.y = fTemp;
	}
}

bool BoundingAABB::IsPointInside( Vector3f a_kPoint )
{
	ContactData kData;
	Collision kCollision;

	// create aabb
	BoundingAABB pAABB;
	pAABB.SetCenter(a_kPoint);
	pAABB.SetWidth(2.0f);
	pAABB.SetHeight(1.0f);

	kData = kCollision.TestIntersection(this, &pAABB);

	return kData.m_bCollision;
}

void BoundingAABB::Update( Vector3f a_kPosition, float a_fOrientation )
{
	m_kCenter = a_kPosition + m_kCenterOffset;

	SetWidth(GetWidth());
	SetHeight(GetHeight());
}

Bounds::VerticeList BoundingAABB::GetVerticies()
{
	m_vVerts.clear();

	m_vVerts.push_back(m_kMin);
	m_vVerts.push_back(Vector3f(m_kMax.x, 0.0f, m_kMin.y));
	m_vVerts.push_back(m_kMax);
	m_vVerts.push_back(Vector3f(m_kMin.x, 0.0f, m_kMax.y));

	return m_vVerts;
}

void BoundingAABB::AddCollisionLinesToDebugDrawer(CDebugLineDrawer* pDebugLineDrawer)
{
// 	Bounds::VerticeList vVerts = GetVerticies();
// 	for( unsigned int iVert = 0; iVert < vVerts.size()-1; ++iVert )
// 	{
// 		pDebugLineDrawer->AddLine(vVerts.at(iVert), vVerts.at(iVert+1), m_kDebugColor);
// 	}
// 	pDebugLineDrawer->AddLine(vVerts.at(vVerts.size()-1), vVerts.at(0), m_kDebugColor);
// 	pDebugLineDrawer->AddLine(vVerts.at(0), vVerts.at(vVerts.size()/2), m_kDebugColor);
}
