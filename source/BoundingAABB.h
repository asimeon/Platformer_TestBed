
#ifndef _BOUNDINGAABB_H_
#define _BOUNDINGAABB_H_

#include "Vector3.h"

#include "Bounds.h"

class BoundingAABB : public Bounds
{
public:
	BoundingAABB();
	BoundingAABB( Vector3f a_kMin, Vector3f a_kMax );

	//override
	void SetWidth( float a_fWidth )
	{
		m_kMin.x = m_kCenter.x - a_fWidth * 0.5f;
		m_kMax.x = m_kCenter.x + a_fWidth * 0.5f;

		m_fWidth = abs((m_kMax.x - m_kMin.x));
	}
	float GetWidth() const { return abs((m_kMax.x - m_kMin.x)); }

	// override
	void SetHeight( float a_fHeight )
	{
		m_kMin.z = m_kCenter.z - a_fHeight * 0.5f;
		m_kMax.z = m_kCenter.z + a_fHeight * 0.5f;

		m_fHeight = abs((m_kMax.z - m_kMin.z));
	}
	float GetHeight() const { return abs((m_kMax.z - m_kMin.z)); }
	
	inline Vector3f Min() { return m_kMin; }
	inline Vector3f Max() { return m_kMax; }

	//override pure
	bool IsPointInside( Vector3f a_kPoint );

	//override pure
	void Update( Vector3f a_kPosition, float a_fOrientation );

	//override pure
	Bounds::VerticeList GetVerticies();

	virtual void AddCollisionLinesToDebugDrawer(CDebugLineDrawer* pDebugLineDrawer );

private:
	Vector3f m_kMin;
	Vector3f m_kMax;

	void Repair();
};

#endif // _BOUNDINGAABB_H_
