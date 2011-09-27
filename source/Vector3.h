
#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <math.h>

#define M_PI 3.14159265

template<typename T>
class Vector3
{
public:
	Vector3();
	Vector3( T xx, T yy, T zz );

	float Magnitude();
	float MagnitudeSquared();
	void Normalize();
	Vector3<T> NormalizeCopy();

	Vector3<T> operator + ( Vector3<T> &rhs );
	Vector3<T> operator + ( T &rhs );
	Vector3<T> operator - ( Vector3<T> &rhs );

	Vector3<T> operator * ( Vector3<T> &rhs );
	Vector3<T> operator * ( float scalar );

	Vector3<T> operator / ( Vector3<T> &rhs );
	Vector3<T> operator / ( float scalar );

	Vector3<T>& operator += ( Vector3<T> &rhs );
	Vector3<T>& operator -= ( Vector3<T> &rhs );

	Vector3<T>& operator *= ( Vector3<T> &rhs );
	Vector3<T>& operator *= ( float scalar );

	Vector3<T>& operator /= ( Vector3<T> &rhs );
	Vector3<T>& operator /= ( float scalar );

	Vector3<T>& operator = ( Vector3<T> &rhs );
	Vector3<T>& operator = ( T set );

	bool operator == ( Vector3<T> &rhs );

	Vector3<T> GetPerpendicular();
	Vector3<T> GetPerpendicularAntiClockwise();

	T x;
	T y;
	T z;
};

template <typename T>
float DotProduct( Vector3<T> &lhs, Vector3<T> &rhs );

template <typename T>
float CalculateAngle( Vector3<T> v1, Vector3<T> v2 );

typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;


template <typename T>
Vector3<T>::Vector3()
{
	x = y = z = 0;
}

template <typename T>
Vector3<T>::Vector3( T xx, T yy, T zz )
{
	x = xx;
	y = yy;
	z = zz;
}

template <typename T>
float Vector3<T>::Magnitude()
{
	return sqrt( (x * x) + (y * y) + (z * z) );
}

template <typename T>
float Vector3<T>::MagnitudeSquared()
{
	return (x * x) + (y * y) + (z * z);
}

template <typename T>
void Vector3<T>::Normalize()
{
	x /= Magnitude();
	y /= Magnitude();
	z /= Magnitude();
}

template <typename T>
Vector3<T> Vector3<T>::NormalizeCopy()
{
	Vector3<T> result;

	result.x = x / Magnitude();
	result.y = y / Magnitude();
	result.z = z / Magnitude();

	return result;
}

template <typename T>
Vector3<T> Vector3<T>::operator + ( Vector3<T> &rhs )
{
	return Vector3<T>( x + rhs.x, y + rhs.y, z + rhs.z );
}

template <typename T>
Vector3<T> Vector3<T>::operator + ( T &rhs )
{
	return Vector3<T>( x + rhs, y + rhs, z /*+ rhs*/ ); // uncomment for z use
}

template <typename T>
Vector3<T> Vector3<T>::operator - ( Vector3<T> &rhs )
{
	return Vector3<T>( x - rhs.x, y - rhs.y, z - rhs.z );
}

template <typename T>
Vector3<T> Vector3<T>::operator * ( Vector3<T> &rhs )
{
	//	return Vector3<T>( x * rhs.x, y * rhs.y, z * rhs.z ); Remove when using z.
	return Vector3<T>( x * rhs.x, y * rhs.y, rhs.z );
}

template <typename T>
Vector3<T> Vector3<T>::operator * ( float scalar )
{
	return Vector3<T>( x * scalar, y * scalar, z * scalar );
}

template <typename T>
Vector3<T> Vector3<T>::operator / ( Vector3<T> &rhs )
{
	return Vector3<T>( x / rhs.x, y / rhs.y, z / rhs.z );
}

template <typename T>
Vector3<T> Vector3<T>::operator / ( float scalar )
{
	return Vector3<T>( x / scalar, y / scalar, z / scalar );
}

template <typename T>
Vector3<T>& Vector3<T>::operator += ( Vector3<T> &rhs )
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator -= ( Vector3<T> &rhs )
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator *= ( Vector3<T> &rhs )
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator *= ( float scalar )
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator /= ( Vector3<T> &rhs )
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator /= ( float scalar )
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator = ( Vector3<T> &rhs )
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

template <typename T>
Vector3<T>& Vector3<T>::operator = ( T set )
{
	x = set;
	y = set;
	z = set;

	return *this;
}

template <typename T>
bool Vector3<T>::operator == ( Vector3<T> &rhs )
{
	return ( x == rhs.x && y == rhs.y && z == rhs.z ) ? true : false;
}

template <typename T>
float DotProduct( Vector3<T> &lhs, Vector3<T> &rhs )
{
	// A.B = Ax * Bx + Ay * By
	return ( (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) );
}

template <typename T>
float CalculateAngle( Vector3<T> v1, Vector3<T> v2 )
{
	Vector3<T> vect = v1 - v2;

	float angle = 0;

	if( vect.y == 0 )
		return angle;

	angle = atan( vect.x / vect.y );

	if( v2.y < v1.y )
		angle += M_PI;

	return angle;
}

template <typename T>
Vector3<T> Vector3<T>::GetPerpendicular()
{
	return Vector3<T>( -y, x, 0 );
}

template <typename T>
Vector3<T> Vector3<T>::GetPerpendicularAntiClockwise()
{
	return Vector3<T>( y, -x, 0 );
}

#endif // VECTOR3_H_
