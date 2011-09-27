
#ifndef OBJECTLOADABLE_H
#define OBJECTLOADABLE_H

#include "Object.h"

class ObjectLoadable : public Object
{
public:
	ObjectLoadable(){}
	virtual ~ObjectLoadable(){}

	virtual bool OnInit() = 0;
	virtual bool OnUnInit() = 0;
};

#endif // OBJECTLOADABLE_H
