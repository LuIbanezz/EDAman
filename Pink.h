#ifndef _PINK_H_
#define _PINK_H_

#include "Ghost.h"

class Pink : public Ghost
{
public:
	Pink(MQTTClient& mqttClient, GameModel& gameModel);
	~Pink();

	void start();
	void update(float deltaTime);
};

#endif // _PINK_H_