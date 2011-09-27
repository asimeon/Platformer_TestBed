
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Matrix3x3.h"
#include "Vector3.h"

class Bounds;
class BoundingAABB;
class BoundingCircle;
class ContactData;

class ContactData
{
public:
	ContactData()
	{
		m_kNormal		 = Vector3f();
		m_kLocalContactA = Vector3f();
		m_kLocalContactB = Vector3f();
		m_kWorldContact	 = Vector3f();
		m_fDepth		 = 0.0f;
		m_bCollision	 = false;
		m_bFlip			 = false;
	}

	Vector3f m_kNormal;
	Vector3f m_kLocalContactA;
	Vector3f m_kLocalContactB;
	Vector3f m_kWorldContact;
	float m_fDepth;
	bool m_bCollision;
	bool m_bFlip;
};

class Collision
{
public:
	Collision();
	~Collision();

	ContactData TestIntersection( Bounds* a_pFirst, Bounds* a_pSecond );

private:
	void OnInit();

	static ContactData CircleCircle( BoundingCircle* a_pCircleA, BoundingCircle* a_pCircleB );
	static ContactData CircleAABB( BoundingCircle* a_pCircle, BoundingAABB* a_pAABB );
	static ContactData AABBCircle( BoundingAABB* a_pAABB, BoundingCircle* a_pCircle );
	static ContactData AABBAABB( BoundingAABB* a_pAABB1, BoundingAABB* a_pAABB2 );

	typedef ContactData (*TCollFunc)(Bounds* p1, Bounds* p2);
	TCollFunc m_pfCollFuncs[2][2];
};

#endif // _COLLISION_H_
