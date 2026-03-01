#pragma once
#include <iostream>
#include "raylib.h"
#include <deque>
#include <raymath.h>
#include <string>
#include "AdditionalFunc.h"
#include "ConstValue.h"

using namespace std;

class Snake {
public:
    deque <Vector2> body;
    Vector2 direction;
    bool addSegment;

    Texture2D headTexture;
    Texture2D bodyTexture;
    Texture2D tailTexture;

    Snake();
    ~Snake();

    void Draw();
    void Update();
    void Reset();

};

class Food {
public:
    Vector2 position;
    Texture2D texture;

    Food(deque <Vector2> SnakeBody); //Constructor
    ~Food();

    void Draw();

    Vector2 GetRandomCell();

    Vector2 GenerateRandomPos(deque <Vector2> SnakeBody);

};

class Game {
public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;
    int score = 0;

    Sound eatSound;
    Sound wallColSound;

    Game();
    ~Game();

    void Draw();
    void Update();

    void CheckCollisionwithFood();

    void GameOver();
    void checkCollisionWithWalls();
    void checkCollisionWithBody();
};
