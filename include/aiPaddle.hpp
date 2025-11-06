#pragma once
#include "SDL3/SDL_rect.h"
#include <string>
#include "direction.hpp"

class AIPaddle
{

public:
    AIPaddle(class Game *game);
    ~AIPaddle();

    void MovePaddle(float deltaTime);
    void SetPaddleDirection(Direction direction) { m_direction = direction; }
    Direction GetPaddleDirection() const { return m_direction; }
    SDL_FRect m_PongPaddle;
    float m_paddleVelocity;

private:
    Direction m_direction;
};