
#include <SDL3/SDL.h>
#include <iostream>
#include "paddle.hpp"
#include "ball.hpp"
#include "direction.hpp"
#include "TextureManager.hpp"
#include "score.hpp"

class Game
{

public:
    Game();
    ~Game();

    bool InitGame();
    void GameLoop();
    void EndGame();

    int m_screenWidth;
    int m_screenHeight;

private:
    void HandleInput();
    void UpdateGame(float deltaTime);
    void GenerateOutput();

    void ReadGameFile();
    void WriteGameFile();

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    int m_gameScoreCount;
    bool m_gameRunning;
    Paddle m_paddle;
    Ball m_ball;
    Direction m_direction;
    float m_speed;
    Uint64 m_currentFrameTime;
    Uint64 m_previousFrameTime;
    TextureManager m_textureManager;
    Score m_scoreManager;
    std::vector<Ball> m_PongBalls;
};
