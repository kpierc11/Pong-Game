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

    void MoveBall(float deltaTime, Paddle paddle);
    SDL_FRect m_ball;

private:
    std::string m_direction;
    int m_ballDirectionX;
    int m_ballDirectionY;
    GameMath::Vector m_ballVelocity;
};

