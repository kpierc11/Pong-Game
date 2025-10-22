#pragma once
#include "SDL3/SDL_rect.h"
#include <string>
#include "direction.hpp"

class Paddle
{

public:
    Paddle();
    ~Paddle();

    void MovePaddle(float deltaTime);
    void SetPaddleDirection(Direction direction) { m_direction = direction; }
    Direction GetPaddleDirection() const { return m_direction; }
    SDL_FRect m_PongPaddle;

private:
    Direction m_direction;
};