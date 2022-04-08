#ifndef _RED_H
#define _RED_H

#include "Robot.h"

class Red : public Robot
{
public:
	Red(MQTTClient& mqttClient, GameModel& gameModel);
	~Red();

	void start();
	void update(float deltaTime);
};

#endif // _RED_H