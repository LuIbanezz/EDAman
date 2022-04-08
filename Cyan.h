#ifndef _CYAN_H
#define _CYAN_H

#include "Robot.h"

class Cyan : public Robot
{
public:
	Cyan(MQTTClient &mqttClient, GameModel &gameModel);
	~Cyan();

	void start();
	void update(float deltaTime);
};

#endif // _CYAN_H