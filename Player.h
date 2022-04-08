#ifndef _PLAYER_H
#define _PLAYER_H

#include "Robot.h"

class Player : public Robot
{
public:
	Player(MQTTClient &mqttClient, GameModel &gameModel);
	~Player();

	void start();
	void update(float deltaTime);

private:

};

#endif // _PLAYER_H