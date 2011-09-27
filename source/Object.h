
#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class Object
{
public:
	Object(){}
	virtual ~Object(){}

	void SetName( std::string a_ssName ) { m_szName = a_ssName.c_str(); }
	const char* GetName() const { return m_szName; }

protected:
	const char* m_szName;
};

#endif // OBJECT_H
