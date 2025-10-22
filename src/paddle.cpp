#include "paddle.hpp"

Paddle::Paddle()
{
    m_PongPaddle.x = 20.0f;
    m_PongPaddle.y = 200.0f;
    m_PongPaddle.h = 100.0f;
    m_PongPaddle.w = 10.0f;
}

Paddle::~Paddle()
{
}

void Paddle::MovePaddle(float deltaTime)
{
  
    if (m_direction == Direction::North && m_PongPaddle.y >= 0)
    {
        m_PongPaddle.y -= 300.0f * deltaTime;
    }

    if (m_direction == Direction::South && m_PongPaddle.y <= 480 - m_PongPaddle.h)
    {
        m_PongPaddle.y += 300.0f * deltaTime;
    }

}