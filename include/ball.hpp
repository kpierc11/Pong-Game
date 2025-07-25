#include <SDL3/SDL.h>
#include <string>
class Ball
{
    public:
    Ball();
    ~Ball();

    void MoveBall(float deltaTime);
    SDL_FRect m_ball;

private:
    std::string m_direction;

};

