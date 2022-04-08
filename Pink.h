#ifndef _PINK_H_
#define _PINK_H_

#include "Robot.h"

class Pink : public Robot
{
public:
	Pink();
	~Pink();

	void start();
	void update(float deltaTime);
};

#endif // _PINK_H_