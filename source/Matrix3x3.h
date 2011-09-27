
#ifndef MATRIX3X3_H_
#define MATRIX3X3_H_

#include "Vector3.h"

template <typename T>
class Matrix3x3
{
public:
	Matrix3x3();

	void Identity();

	void CreateRotation( const float angle );
	void CreateTranslation();
	void CreateTranslation( float dir, float amnt );

	void SetTranslation( const Vector3<T> newTranslation );
	Vector3<T> GetTranslation() const;
	void Translate( Matrix3x3<T> translation );

	void SetRotation( const float angle );
	Vector3<T> GetRotation() const;

	Matrix3x3<T> operator + ( const Matrix3x3<T> &rhs );
	Matrix3x3<T> operator * ( const Matrix3x3<T> &rhs );
	Matrix3x3<T> operator * ( const float scalar );
	Vector3<T> operator * ( Vector3<T> &rhs );
	Matrix3x3<T>& operator = ( const Matrix3x3<T> &rhs );

private:
	Vector3<T> _0;
	Vector3<T> _1;
	Vector3<T> _2;
};

typedef Matrix3x3<float> Matrix3x3f;
typedef Matrix3x3<double> Matrix3x3d;

template <typename T>
Matrix3x3<T>::Matrix3x3()
{
	Identity();
}

//******************************************************************************
// \name	Identity()
// \purpose	Sets the matrix to identity.
// \parameters
//		none
template <typename T>
void Matrix3x3<T>::Identity()
{
	_0 = 0;
	_1 = 0;
	_2 = 0;

	_0.x = 1;
	_1.y = 1;
	_2.z = 1;
}

template <typename T>
void Matrix3x3<T>::CreateTranslation()
{
	Matrix3x3<T> temp;

	//temp._0._0 = 
}

template <typename T>
void Matrix3x3<T>::CreateTranslation( float dir, float amnt )
{
	_0.x = amnt * sin(dir);
	_1.y = amnt * cos(dir);

	if( dir >= 90 && dir < 270 ) _0.x *= -1;
}

//******************************************************************************
// \name	CreateRotation
// \purpose	Sets the matrix to identity.
// \parameters
//		none
template <typename T>
void Matrix3x3<T>::CreateRotation( const float angle )
{
	_0.x = cos(angle);
	_0.y = sin(angle) * -1;
	_0.z = 0;

	_1.x = sin(angle);
	_1.y = cos(angle);
	_1.z = 0;

	_2.x = 0;
	_2.y = 0;
	_2.z = 1;
}

template <typename T>
void Matrix3x3<T>::SetTranslation( const Vector3<T> newTranslation )
{
	_2 = newTranslation;
}

template <typename T>
Vector3<T> Matrix3x3<T>::GetTranslation() const
{
	return _2;
}

template <typename T>
void Matrix3x3<T>::Translate( Matrix3x3<T> translation )
{
	_2.x += translation._0.x;
	_2.y += translation._1.y;
}

template <typename T>
void Matrix3x3<T>::SetRotation( const float angle )
{
	_0.x = cos(angle);
	_0.y = -sin(angle);

	_1.x = sin(angle);
	_1.y = cos(angle);
}

template <typename T>
Vector3<T> Matrix3x3<T>::GetRotation() const
{
	return Vector3<T>( _0.x, _1.y, 0 );
}

template <typename T>
Matrix3x3<T> Matrix3x3<T>::operator + ( const Matrix3x3<T> &rhs )
{
	Matrix3x3<T> result;

	result._0.x = rhs._0.x + _0.x;
	result._0.y = rhs._0.y + _0.y;
	result._0.z = rhs._0.z + _0.z;

	result._1.x = rhs._1.x + _1.x;
	result._1.y = rhs._1.y + _1.y;
	result._1.z = rhs._1.z + _1.z;

	result._2.x = rhs._2.x + _2.x;
	result._2.y = rhs._2.y + _2.y;
	result._2.z = rhs._2.z + _2.z;

	return result;
}

template <typename T>
Matrix3x3<T> Matrix3x3<T>::operator * ( const Matrix3x3<T> &rhs )
{
	Matrix3x3<T> result;

	/*			local						rhs
		_0		_1		z			_0		_1		z
	_0	_0._0		_1._0		z._0		_0	_0._0		_1._0		z._0
	_1	_1._0		_1._1		z._1		_1	_1._0		_1._1		z._1
	_2	_2._0		_2._1		_2.z		_2	_2._0		_2._1		_2.z
	*/

	result._0.x = ( _0.x * rhs._0.x ) + ( _0.y * rhs._1.x ) + ( _0.z * rhs._2.x );
	result._0.y = ( _0.x * rhs._0.y ) + ( _0.y * rhs._1.y ) + ( _0.z * rhs._2.y );
	result._0.z = ( _0.x * rhs._0.z ) + ( _0.y * rhs._1.z ) + ( _0.z * rhs._2.z );

	result._1.x = ( _1.x * rhs._0.x ) + ( _1.y * rhs._1.x ) + ( _1.z * rhs._2.x );
	result._1.y = ( _1.x * rhs._0.y ) + ( _1.y * rhs._1.y ) + ( _1.z * rhs._2.y );
	result._1.z = ( _1.x * rhs._0.z ) + ( _1.y * rhs._1.z ) + ( _1.z * rhs._2.z );

	result._2.x = ( _2.x * rhs._0.x ) + ( _2.y * rhs._1.x ) + ( _2.z * rhs._2.x );
	result._2.y = ( _2.x * rhs._0.y ) + ( _2.y * rhs._1.y ) + ( _2.z * rhs._2.y );
	result._2.z = ( _2.x * rhs._0.z ) + ( _2.y * rhs._1.z ) + ( _2.z * rhs._2.z );

	return result;
}

template <typename T>
Matrix3x3<T> Matrix3x3<T>::operator * ( float scalar )
{
	Matrix3x3<T> result;

	result._0.x = _0.x * scalar;
	result._0.y = _0.y * scalar;
	result._0.z = _0.z * scalar;

	result._1.x = _1.x * scalar;
	result._1.y = _1.y * scalar;
	result._1.y = _1.z * scalar;

	result._2.x = _2.x * scalar;
	result._2.y = _2.y * scalar;
	result._2.y = _2.z * scalar;

	return result;
}

template <typename T>
Vector3<T> Matrix3x3<T>::operator * ( Vector3<T> &rhs )
{
	Vector3<T> result;

	result.x = ( _0.x * rhs.x ) + ( _1.x * rhs.y ) + ( _2.x * rhs.z );
	result.y = ( _0.y * rhs.x ) + ( _1.y * rhs.y ) + ( _2.y * rhs.z );
	result.z = ( _0.z * rhs.x ) + ( _1.z * rhs.y ) + ( _2.z * rhs.z );

	return result;
}

template <typename T>
Matrix3x3<T>& Matrix3x3<T>::operator = ( const Matrix3x3<T> &rhs )
{
	_0.x = rhs._0.x;	_0.y = rhs._0.y; _0.z = rhs._0.z;
	_1.x = rhs._1.x;	_1.y = rhs._1.y; _1.z = rhs._1.z;
	_2.x = rhs._2.x;	_2.y = rhs._2.y; _2.z = rhs._2.z;

	return *this;
}

#endif // MATRIX3X3_H_
