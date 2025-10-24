#include "ball.hpp"
#include "game.hpp"
#include <cmath>
#include <iostream>

using namespace GameMath;

Ball::Ball() : m_ball{100, 100, 10, 10}, // x, y, w, h
               m_ballDirectionX(1),
               m_ballDirectionY(1),
               m_ballVelocity{1.0f, 1.0f},
               m_ballTexture(nullptr),
               m_game(nullptr)
{
}

Ball::~Ball()
{
}

void Ball::MoveBall(float deltaTime, Paddle &paddle)
{

    float speed = 400.0f;

    float screenWidth = static_cast<float>(m_game->m_screenWidth);
    float screenHeight = static_cast<float>(m_game->m_screenHeight);

    // bottom
    if (m_ball.y > screenHeight)
    {
        m_ballVelocity.y *= -1.0f;
    }

    // top
    if (m_ball.y < 0.0f)
    {
        m_ballVelocity.y *= -1.0f;
    }

    // right
    if (m_ball.x > screenWidth)
    {
        m_ballVelocity.y *= 1.0f;
        m_ballVelocity.x *= -1.0f;
    }

    if (m_ball.x <= 0)
    {
        m_ball.x = screenWidth;
        m_ball.y = screenHeight / 2.0f;
    }

    float paddleCenterY = paddle.m_PongPaddle.y + paddle.m_PongPaddle.h / 2.0f;
    float ballCenterY = m_ball.y + m_ball.h / 2.0f;
    float diff = std::fabs(paddleCenterY - ballCenterY);
    float paddleHalfHeight = paddle.m_PongPaddle.h / 2.0f;

    if (m_ball.x <= paddle.m_PongPaddle.x + paddle.m_PongPaddle.w &&
        diff <= paddleHalfHeight && m_ball.x >= paddle.m_PongPaddle.x - paddle.m_PongPaddle.w )
    {
        m_ballVelocity.x *= -1.0f;
        m_ballVelocity.y *= 1.0f;
    }

    m_ball.x += (speed * m_ballVelocity.x) * deltaTime;
    m_ball.y += (speed * m_ballVelocity.y) * deltaTime;
}