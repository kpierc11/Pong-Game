#pragma once
#include <SDL3/SDL.h>
#include <string>
#include "paddle.hpp"
#include "math.hpp"

class Ball
{
public:
    Ball();
    ~Ball();

    void MoveBall(float deltaTime, Paddle &paddle);
    void SetBallTexture(SDL_Texture *text) { m_ballTexture = text; };
    void SetGame(class Game *game) { m_game = game; };

    SDL_FRect m_ball;
    std::string m_direction;
    int m_ballDirectionX;
    int m_ballDirectionY;
    GameMath::Vector m_ballVelocity;
    SDL_Texture *m_ballTexture;
    class Game *m_game;
};
