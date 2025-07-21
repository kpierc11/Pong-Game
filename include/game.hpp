
#include <SDL3/SDL.h>
#include <iostream>

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
    void UpdateGame();
    void GenerateOutput();

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    int m_screenWidth; 
    int m_screenHeight;
    bool m_gameRunning;
    SDL_FRect m_paddle;
    SDL_FRect m_ball; 
    std::string m_direction;
    float m_speed;
    Uint64 m_previousFrameTime;
};
