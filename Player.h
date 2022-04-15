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

private:
	KeyboardKey lastKeyPressed;
	KeyboardKey previousDirection;

	bool check(float deltaTime, bool option);
};

#endif // _PLAYER_H