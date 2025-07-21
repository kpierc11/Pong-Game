
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
    bool m_gameRunning;
    SDL_FRect m_paddle;
    std::string m_direction;
    float m_speed;
};
