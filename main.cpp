/**
 * EDA-Man
 *
 * @copyright Copyright (C) 2022
 * @author Marc S. Ressl
 * 
 * @brief Controls an EDA-Man game.
 */

#include <iostream>

#include <raylib.h>

#include "MQTTClient.h"

#include "Game/GameModel.h"
#include "Game/GameView.h"

#include "Player.h"
#include "Ghosts/Red.h"
#include "Ghosts/Orange.h"
#include "Ghosts/Cyan.h"
#include "Ghosts/Pink.h"

using namespace std;

int main(int, char **)
{
    MQTTClient mqttClient("controller");

    const int port = 1883;
    if (!mqttClient.connect("localhost", port, "user", "vdivEMMN3SQWX2Ez"))
    {
        cout << "Could not connect." << endl;
        return 1;
    }

    cout << "Connected." << endl;

    // raylib
    InitWindow(640, 480, "EDAPark Controller");
    SetTargetFPS(60);

    string maze =
        "                            "
        "                            "
        "                            "
        "jbbbbbbbbbbbbonbbbbbbbbbbbbk"
        "s++++++++++++pq++++++++++++r"
        "s+faag+faaag+pq+faaag+faag+r"
        "s#p  q+p   q+pq+p   q+p  q#r"
        "s+v``w+v```w+vw+v```w+v``w+r"
        "s++++++++++++++++++++++++++r"
        "s+faag+fg+faaaaaag+fg+faag+r"
        "s+v``w+pq+v``ih``w+pq+v``w+r"
        "s++++++pq++++pq++++pq++++++r"
        "zccccg+pxaag pq faayq+fcccc{"
        "     s+ph``w vw v``iq+r     "
        "     s+pq          pq+r     "
        "     s+pq dcc__cce pq+r     "
        "     s+vw r      s vw+r     "
        "     s+   r      s   +r     "
        "     s+fg r      s fg+r     "
        "     s+pq tbbbbbbu pq+r     "
        "     s+pq          pq+r     "
        "     s+pq faaaaaag pq+r     "
        "jbbbbw+vw v``ih``w vw+vbbbbk"
        "s++++++++++++pq++++++++++++r"
        "s+faag+faaag+pq+faaag+faag+r"
        "s+v`iq+v```w+vw+v```w+ph`w+r"
        "s#++pq+++++++  +++++++pq++#r"
        "|ag+pq+fg+faaaaaag+fg+pq+fa}"
        "l`w+vw+pq+v``ih``w+pq+vw+v`m"
        "s++++++pq++++pq++++pq++++++r"
        "s+faaaayxaag+pq+faayxaaaag+r"
        "s+v````````w+vw+v````````w+r"
        "s++++++++++++++++++++++++++r"
        "zcccccccccccccccccccccccccc{"
        "                            "
        "                            ";

    // Setup
    GameModel gameModel(&mqttClient);
    GameView gameView(&mqttClient);

    // Configure
    gameModel.setGameView(&gameView);

    Player player(mqttClient, gameModel);
    Red red(mqttClient, gameModel, player);
    Orange orange(mqttClient, gameModel, player);
    Cyan cyan(mqttClient, gameModel, player, red);
    Pink pink(mqttClient, gameModel, player);

    gameModel.addRobot(&player);    // robot1
    gameModel.addRobot(&red);       // robot2
    gameModel.addRobot(&cyan);      // robot3
    gameModel.addRobot(&pink);      // robot4
    gameModel.addRobot(&orange);    // robot5 

    gameModel.start(maze);

    while (!WindowShouldClose() && mqttClient.isConnected())
    {
        float deltaTime = (float)GetFrameTime();

        // raylib
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("EDAPark Controller", 225, 220, 20, LIGHTGRAY);
        EndDrawing();

        vector<MQTTMessage> messages = mqttClient.getMessages();

        // Model update
        gameModel.update(deltaTime);

        // Keyboard control
        if (IsKeyDown(KEY_UP))
        {
            player.setKeyboardKey(KEY_UP);
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            player.setKeyboardKey(KEY_RIGHT);
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            player.setKeyboardKey(KEY_DOWN);
        }
        else if (IsKeyDown(KEY_LEFT))
        {
            player.setKeyboardKey(KEY_LEFT);
        }
        else
        {
            // Your code goes here...
        }

        gameView.update(deltaTime);
    }

    CloseWindow();

    cout << "Disconnected." << endl;
}
