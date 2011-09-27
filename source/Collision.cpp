
#include "Collision.h"

#include "Bounds.h"
#include "BoundingAABB.h"
#include "BoundingCircle.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// \fn	Collision::Collision()
//
// \brief	Default constructor.
//
// \author	Andrew
// \date	12/08/2011
////////////////////////////////////////////////////////////////////////////////////////////////////

Collision::Collision()
{
	OnInit();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// \fn	Collision::~Collision()
//
// \brief	Destructor.
//
// \author	Andrew
// \date	12/08/2011
////////////////////////////////////////////////////////////////////////////////////////////////////

Collision::~Collision()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// \fn	void Collision::OnInit()
//
// \brief	Sets the function pointer array correctly per each collision type on Init.
//
// \author	Andrew
// \date	12/08/2011
////////////////////////////////////////////////////////////////////////////////////////////////////

void Collision::OnInit()
{
	m_pfCollFuncs[Bounds::BOUNDTYPE_CIRCLE][Bounds::BOUNDTYPE_CIRCLE] = (TCollFunc)CircleCircle;
	m_pfCollFuncs[Bounds::BOUNDTYPE_CIRCLE][Bounds::BOUNDTYPE_AABB]   = (TCollFunc)CircleAABB;
	m_pfCollFuncs[Bounds::BOUNDTYPE_AABB]  [Bounds::BOUNDTYPE_CIRCLE] = (TCollFunc)AABBCircle;
	m_pfCollFuncs[Bounds::BOUNDTYPE_AABB]  [Bounds::BOUNDTYPE_AABB]   = (TCollFunc)AABBAABB;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// \fn	ContactData Collision::TestIntersection( Bounds* a_pFirst, Bounds* a_pSecond )
//
// \brief	Tests an intersection. Uses function pointers to get the appropriate function.
//
// \author	Andrew
// \date	12/08/2011
//
// \param [in]	a_pFirst 	If non-null, the first to check.
// \param [in]	a_pSecond	If non-null, the second to check.
//
// \return	ContactData from the appropriate class.
////////////////////////////////////////////////////////////////////////////////////////////////////

ContactData Collision::TestIntersection( Bounds* a_pFirst, Bounds* a_pSecond )
{
	return( m_pfCollFuncs[(int)a_pFirst->GetBoundType()][(int)a_pSecond->GetBoundType()](a_pFirst, a_pSecond) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// \fn	ContactData Collision::CircleCircle( BoundingCircle* a_pCircleA,
// 		BoundingCircle* a_pCircleB )
//
// \brief	Tests Circle to Circle collision.
//
// \author	Andrew
// \date	12/08/2011
//
// \param [in]	a_pCircleA	If non-null, the first circle.
// \param [in]	a_pCircleB	If non-null, the second circle.
//
// \return	ContactData.
////////////////////////////////////////////////////////////////////////////////////////////////////

ContactData Collision::CircleCircle( BoundingCircle* a_pCircleA, BoundingCircle* a_pCircleB )
{
	ContactData kContact;
	kContact.m_bCollision = false;

	Vector3f kPosDiff = a_pCircleB->GetCenter() - a_pCircleA->GetCenter();
	float fDistance = kPosDiff.Magnitude();
	float fCombinedRadius = a_pCircleA->GetRadius() + a_pCircleB->GetRadius();

	float fDepth = fDistance - fCombinedRadius;
	if( fDepth > 0.0f )
	{
		return kContact;
	}

	// normalise the diff of the positions
	Vector3f kPosDiffNorm = kPosDiff;
	kPosDiffNorm.Normalize();

	kContact.m_bCollision = true;
	kContact.m_kLocalContactA = (kPosDiff / fDistance) * a_pCircleA->GetRadius();
	kContact.m_kLocalContactB = (kPosDiff / fDistance) * -a_pCircleB->GetRadius();
	kContact.m_kNormal = kPosDiffNorm;
	kContact.m_fDepth = fDepth;

	return kContact;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// \fn	ContactData Collision::CircleAABB( BoundingCircle* a_pCircle, BoundingAABB* a_pAABB )
//
// \brief	Tests an Circle with an Axis-aligned Bounding Box.
//
// \author	Andrew
// \date	12/08/2011
//
// \param [in]	a_pCircle	If non-null, the circle.
// \param [in]	a_pAABB  	If non-null, the axis-aligned bounding box (AABB).
//
// \return	ContactData.
////////////////////////////////////////////////////////////////////////////////////////////////////

ContactData Collision::CircleAABB( BoundingCircle* a_pCircle, BoundingAABB* a_pAABB )
{
	ContactData kContact;
	kContact.m_bCollision = false;

	Vector3f kBoxHalfWidth = Vector3f(a_pAABB->GetWidth() * 0.5f, 0.0f,  a_pAABB->GetHeight() * 0.5f);
	float fCircleRadius = a_pCircle->GetRadius();
	Vector3f kCircleCenter = a_pCircle->GetCenter();
	Vector3f kRelCenter = a_pCircle->GetCenter() - a_pAABB->GetCenter();

	kCircleCenter.y = 0.0f;
	kRelCenter.y = 0.0f;

	if( ((abs(kRelCenter.x) - fCircleRadius) > kBoxHalfWidth.x) ||
		((abs(kRelCenter.y) - fCircleRadius) > kBoxHalfWidth.y) )
	{
		return kContact;
	}

	Vector3f kClosestPoint = Vector3f();
	float fDistance = 0.0f;

	fDistance = kRelCenter.x;
	if( fDistance > kBoxHalfWidth.x )
	{
		fDistance = kBoxHalfWidth.x;
	}

	if( fDistance < -kBoxHalfWidth.x )
	{
		fDistance = -kBoxHalfWidth.x;
	}

	kClosestPoint.x = fDistance;

	fDistance = kRelCenter.y;
	if( fDistance > kBoxHalfWidth.y )
	{
		fDistance = kBoxHalfWidth.y;
	}

	if( fDistance < -kBoxHalfWidth.y )
	{
		fDistance = -kBoxHalfWidth.y;
	}

	kClosestPoint.z = fDistance;

	fDistance = (kClosestPoint - kRelCenter).Magnitude();
	if( fDistance > fCircleRadius )
	{
		return kContact;
	}
	
	Vector3f kToNormalise = (kRelCenter - kClosestPoint);
	kToNormalise.Normalize();

	kContact.m_bCollision = true;
	kContact.m_kWorldContact = kClosestPoint + a_pAABB->GetCenter();
	kContact.m_kNormal = kToNormalise;
	kContact.m_kLocalContactA = kContact.m_kNormal * -a_pCircle->GetRadius();
	kContact.m_kLocalContactB = kClosestPoint;
	kContact.m_fDepth = fCircleRadius - (float)fDistance;

	return kContact;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// \fn	ContactData Collision::AABBCircle( BoundingAABB* a_pAABB, BoundingCircle* a_pCircle )
//
// \brief	Tests an Axis-aligned Bounding Box with a Circle.
//
// \author	Andrew
// \date	12/08/2011
//
// \param [in]	a_pAABB  	If non-null, the axis-aligned bounding box (AABB).
// \param [in]	a_pCircle	If non-null, the circle.
//
// \return	ContactData.
////////////////////////////////////////////////////////////////////////////////////////////////////

ContactData Collision::AABBCircle( BoundingAABB* a_pAABB, BoundingCircle* a_pCircle )
{
	return CircleAABB( a_pCircle, a_pAABB );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// \fn	ContactData Collision::AABBAABB( BoundingAABB* a_pAABB1, BoundingAABB* a_pAABB2 )
//
// \brief	Tests two Axis-aligned Bounding Boxes.
//
// \author	Andrew
// \date	12/08/2011
//
// \param [in]	a_pAABB1  	If non-null, the axis-aligned bounding box (AABB).
// \param [in]	a_pAABB2  	If non-null, the axis-aligned bounding box (AABB).
//
// \return	ContactData.
////////////////////////////////////////////////////////////////////////////////////////////////////

ContactData Collision::AABBAABB( BoundingAABB* a_pAABB1, BoundingAABB* a_pAABB2 )
{
	ContactData kContact;
	kContact.m_bCollision = false;
	
	Vector3f kDiff = a_pAABB2->GetCenter() - a_pAABB1->GetCenter();
	float fCombinedWidth  = a_pAABB1->GetWidth()  + a_pAABB2->GetWidth();
	float fCombinedHeight = a_pAABB1->GetHeight() + a_pAABB2->GetHeight();

	//is colliding
	if( fabsf(kDiff.x) > fCombinedWidth )
	{
		return kContact;
	}

	if( fabsf(kDiff.z) > fCombinedHeight )
	{
		return kContact;
	}

	Vector3f kDiff2 = a_pAABB1->GetCenter() - a_pAABB2->GetCenter();
	Vector3f kDiffNorm = kDiff;
	Vector3f kDiff2Norm = kDiff2;

	kDiffNorm.Normalize();
	kDiff2Norm.Normalize();

	kContact.m_bCollision = true;
	kContact.m_kLocalContactA = kDiffNorm;
	kContact.m_kLocalContactA = kDiff2Norm;
	kContact.m_kWorldContact = kDiff;

	return kContact;
}
