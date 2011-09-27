
#ifndef _BOUNDINGCIRCLE_H_
#define _BOUNDINGCIRCLE_H_

#include "Bounds.h"

class BoundingCircle : public Bounds
{
public:
	BoundingCircle();
	BoundingCircle( float a_fRadius, Vector3f a_kCenter );

	inline float GetRadius() const { return m_fRadius; }
	inline void SetRadius( float a_fRadius ) { m_fRadius = a_fRadius; }

	//override pure
	bool IsPointInside( Vector3f a_kPoint );

	//override pure
	void Update( Vector3f a_kPosition, float a_fOrientation );

	//override pure
	Bounds::VerticeList GetVerticies();

	//override
	void SetWidth( float a_fWidth ) { m_fRadius = a_fWidth * 0.5f; }
	float GetWidth() const { return m_fRadius * 2.0f; }
	// override
	void SetHeight( float a_fHeight ) { m_fRadius = a_fHeight * 0.5f; }
	float GetHeight() const { return m_fRadius * 2.0f; }

	virtual void AddCollisionLinesToDebugDrawer(class CDebugLineDrawer* pDebugLineDrawer );
private:
	float m_fRadius;
};

#endif // _BOUNDINGCIRCLE_H_
