
#ifndef _BOUNDS_H_
#define _BOUNDS_H_

////////////////////////////////////////////////////////////////////////////////////////////////////
// \class	Bounds
//
// \brief	Bounds. 
//
// \author	Andrew
// \date	12/08/2011
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

#ifdef _DEBUG
#include <string>
#endif

#include "Vector3.h"

class ContactData;
class CDebugLineDrawer;

class Bounds
{
public:
	enum BOUNDTYPE
	{
		BOUNDTYPE_AABB = 0,
		BOUNDTYPE_CIRCLE,
		BOUNDTYPE_OBB,
		BOUNDTYPE_COUNT
	};

	typedef std::vector<Vector3f> VerticeList;

	Bounds( BOUNDTYPE a_eType );
	Bounds(Bounds& other); 
	~Bounds();

	inline BOUNDTYPE GetBoundType() const { return m_eBoundingType; }

	ContactData Intersects( Bounds* a_pOther );

	virtual VerticeList GetVerticies() = 0;
	virtual bool IsPointInside( Vector3f a_kPoint ) = 0;

	inline void SetCenter( Vector3f a_kCenter ) { m_kCenter = a_kCenter; }
	inline Vector3f GetCenter() const { return m_kCenter; }
	
	inline void SetCenterOffset( Vector3f a_kCenterOffset ) { m_kCenterOffset = a_kCenterOffset; }
	inline Vector3f GetCenterOffset() const { return m_kCenterOffset; }

	inline void SetOrientation( float a_fOrientation );
	inline float GetOrientation() const { return m_fOrientation; }

	virtual inline void SetWidth( float a_fWidth ) { m_fWidth = a_fWidth; }
	virtual inline float GetWidth() const { return m_fWidth; }

	virtual inline void SetHeight( float a_fHeight ) { m_fHeight = a_fHeight; }
	virtual inline float GetHeight() const { return m_fHeight; }

	virtual void Update( Vector3f a_kPosition, float a_fOrientation ) = 0;

#ifdef _DEBUG
	std::string ssName;
#endif

	virtual void AddCollisionLinesToDebugDrawer(CDebugLineDrawer* pDebugLineDrawer ) = 0;
protected:
	BOUNDTYPE m_eBoundingType;
	float m_fOrientation;
	Vector3f m_kCenter;
	Vector3f m_kCenterOffset;

	float m_fWidth;
	float m_fHeight;

	VerticeList m_vVerts;
};

#endif // _BOUNDS_H_
