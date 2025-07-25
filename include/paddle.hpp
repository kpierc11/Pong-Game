#include "SDL3/SDL_rect.h"
#include <string>
class Paddle
{

public:
    Paddle();
    ~Paddle();

    void MovePaddle(float deltaTime);
    void SetPaddleDirection(std::string direction) { m_direction = direction; }
    std::string GetPaddleDirection() const { return m_direction; }
    SDL_FRect m_PongPaddle;

private:
    std::string m_direction;
};