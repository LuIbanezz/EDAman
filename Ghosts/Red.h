#ifndef _RED_H
#define _RED_H

#include "../Ghost.h"
#include "../Player.h"

class Red : public Ghost
{
public:
	Red(MQTTClient& mqttClient, GameModel& gameModel, Player &player);
	~Red();

	void start();
	void update(float deltaTime);

private:
	Player *player;
	void calculateObjectiveTile();
};

#endif // _RED_H