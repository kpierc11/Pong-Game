
#include <SDL3/SDL.h>
#include <iostream>
#include "paddle.hpp"
#include "ball.hpp"


struct Vector
{
    float x;
    float y;
};

class Game
{

public:
    Game();
    ~Game();

    bool InitGame();
    void GameLoop();
    void EndGame();

private:
    void HandleInput();
    void UpdateGame(float deltaTime);
    void GenerateOutput();

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    int m_screenWidth;
    int m_screenHeight;
    bool m_gameRunning;
    Paddle m_paddle;
    Ball m_ball;
    std::string m_direction;
    float m_speed;
    Uint64 m_currentFrameTime;
    Uint64 m_previousFrameTime;
};
