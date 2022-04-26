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
	Vector2 getPlayerPosition();
	int getPlayerDirection();

private:
	KeyboardKey lastKeyPressed;
	KeyboardKey lastDirection;

	bool check(float deltaTime, bool option);
	void eatDots();
};

#endif // _PLAYER_H