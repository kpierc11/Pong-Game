#include "paddle.hpp"

Paddle::Paddle()
{
    m_PongPaddle.x = 20;
    m_PongPaddle.y = 200;
    m_PongPaddle.h = 100;
    m_PongPaddle.w = 10;
}

Paddle::~Paddle()
{
}

void Paddle::MovePaddle(float deltaTime)
{
    if (m_direction == "north" && m_PongPaddle.y >=0)
    {
        m_PongPaddle.y -= 300.0f * deltaTime;
    }

    if (m_direction == "south" && m_PongPaddle.y <= 480 - m_PongPaddle.h )
    {
        m_PongPaddle.y += 300.0f * deltaTime;
    }
}