#ifndef _ORANGE_H
#define _ORANGE_H

#include "Robot.h"

class Orange : public Robot
{
public:
	Orange(MQTTClient &mqttClient, GameModel &gameModel);
	~Orange();

	void start();
	void update(float deltaTime);
};

#endif // _ORANGE_H