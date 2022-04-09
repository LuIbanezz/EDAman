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
	void setKeyboardKey(KeyboardKey lastKeyPressed);

private:
	KeyboardKey lastKeyPressed;
	bool isNextLocationPosible(float deltaTime);
};

#endif // _PLAYER_H