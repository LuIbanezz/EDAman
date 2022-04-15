#ifndef _ORANGE_H
#define _ORANGE_H

#include "Ghost.h"

class Orange : public Ghost
{
public:
	Orange(MQTTClient &mqttClient, GameModel &gameModel);
	~Orange();

	void start();
	void update(float deltaTime);
};

#endif // _ORANGE_H