#include "ball.hpp"
#include <cmath>
#include <iostream>

Ball::Ball()
{
    m_ball.x = 300;
    m_ball.y = 250;
    m_ball.h = 10;
    m_ball.w = 10;
    m_ballDirectionX = 1;
    m_ballDirectionY = 1;
    m_ballVelocity = GameMath::Vector{1, 1};
}

Ball::~Ball()
{
}

void Ball::MoveBall(float deltaTime, Paddle paddle)
{


    GameMath::Vector vec1 = {1,1};
    GameMath::Vector vec2 = {2,2};

    GameMath::Vector vecAdd = vec1 + vec2;

    std::cout << (vecAdd.x) << "\n";


    float speed = 300.0f;

    // bottom
    if (m_ball.y > 470.0f)
    {
        m_ballVelocity.y *= -1.0f;
    }

    // top
    if (m_ball.y < 1.0f)
    {
        m_ballVelocity.y *= -1.0f;
    }

    // right
    if (m_ball.x > 640.0f)
    {
        m_ballVelocity.y *= 1.0f;;
        m_ballVelocity.x *= -1.0f;
    }

    if (m_ball.x < 0)
    {
        m_ball.x = 640.0f;
        m_ball.y = 480.0f /2.0f;
    }

    // paddle
    if (m_ball.x < 20 && abs(m_ball.y - paddle.m_PongPaddle.y) < paddle.m_PongPaddle.h)
    {
       m_ballVelocity.x *= -1.0f;
       m_ballVelocity.y *= 1.0f;
    }

    m_ball.x += (speed * m_ballVelocity.x) * deltaTime;
    m_ball.y += (speed * m_ballVelocity.y) * deltaTime;
}
