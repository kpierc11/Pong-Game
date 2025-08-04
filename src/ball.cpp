#include "ball.hpp"


Ball::Ball()
{
    m_ball.x = 300;
    m_ball.y = 250;
    m_ball.h = 10;
    m_ball.w = 10;
    m_ballDirectionX = 1;
    m_ballDirectionY = 1;
}

Ball::~Ball()
{
}

void Ball::MoveBall(float deltaTime, Paddle paddle)
{

    float speed = 200.0f;

    // bottom
    if (m_ball.y > 480)
    {
        m_ballDirectionY = -1;
        m_ballDirectionX = 1;
    }

    // top
    if (m_ball.y <= 1)
    {
        m_ballDirectionY = 1;
        m_ballDirectionX = -1;
    }

    // right
    if (m_ball.x >= 640)
    {
        m_ballDirectionY = -1;
        m_ballDirectionX = -1;
    }

    // //paddle
    if (m_ball.x <= paddle.m_PongPaddle.x)
    {
        m_ballDirectionX = 1;
        m_ballDirectionY = 1;
    }

    m_ball.x += (speed * m_ballDirectionX) * deltaTime;
    m_ball.y += (speed * m_ballDirectionY) * deltaTime;
}
