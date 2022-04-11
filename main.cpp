/*
 * EDA-Man
 *
 * Copyright (C) 2022 Marc S. Ressl
 *
 * Controls an EDA-Man game.
 */

#include <iostream>

#include <raylib.h>

#include "MQTTClient.h"

#include "GameModel.h"
#include "GameView.h"

#include "Player.h"
#include "Red.h"
#include "Orange.h"
#include "Cyan.h"
#include "Pink.h"

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
    InitWindow(640, 480, "EDA-Man Controller");
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
        "jbbbbw+vw r      s vw+vbbbbk"
        "s     +   r      s   +     r"
        "zccccg+fg r      s fg+fcccc{"
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
    Red red(mqttClient, gameModel);
    Orange orange(mqttClient, gameModel);
    Cyan cyan(mqttClient, gameModel);
    Pink pink(mqttClient, gameModel);

    gameModel.addRobot(&player);    // robot1
    gameModel.addRobot(&red);       // robot2
    gameModel.addRobot(&pink);      // robot3
    gameModel.addRobot(&cyan);      // robot4
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
        if (IsKeyPressed(KEY_UP))
        {
            player.setKeyboardKey(KEY_UP);
        }
        else if (IsKeyPressed(KEY_RIGHT))
        {
            player.setKeyboardKey(KEY_RIGHT);
        }
        else if (IsKeyPressed(KEY_DOWN))
        {
            player.setKeyboardKey(KEY_DOWN);
        }
        else if (IsKeyPressed(KEY_LEFT))
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