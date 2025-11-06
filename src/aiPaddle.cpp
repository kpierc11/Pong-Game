#include "aiPaddle.hpp"
#include "game.hpp"

AIPaddle::AIPaddle(Game *game)
{
    m_PongPaddle.x = game->m_screenWidth - 20.0f;
    m_PongPaddle.y = game->m_screenHeight - 200.0f;
    m_PongPaddle.h = 100.0f;
    m_PongPaddle.w = 10.0f;
    m_paddleVelocity = 1.0f;

}

AIPaddle::~AIPaddle()
{
}

void AIPaddle::MovePaddle(float deltaTime)
{

    float speed = 400.0f;
    if (m_PongPaddle.y < 20.0f)
    {
       m_paddleVelocity *= -1.0f;
    }

    if (m_PongPaddle.y >= 480.0f - m_PongPaddle.h)
    {
        m_paddleVelocity *= -1.0f;
    }

     m_PongPaddle.y += (speed * m_paddleVelocity) * deltaTime;
}