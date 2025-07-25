#include "game.hpp"
#include <cmath>

Game::Game() : m_window(nullptr), m_renderer(nullptr), m_screenWidth(640), m_screenHeight(480), m_gameRunning(true), m_paddle({}), m_speed(300.0f), m_direction(""), m_currentFrameTime(SDL_GetTicks()), m_previousFrameTime(0)
{
}

Game::~Game()
{
}

bool Game::InitGame()
{
    // Initialize sdl3
    SDL_Init(SDL_INIT_VIDEO);

    m_window = SDL_CreateWindow(
        "Pong Game",      // window title
        m_screenWidth,    // width, in pixels
        m_screenHeight,   // height, in pixels
        SDL_WINDOW_OPENGL // flags - see below
    );

    if (m_window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 0;
    }

    m_renderer = SDL_CreateRenderer(m_window, "");

    if (m_renderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}

void Game::EndGame()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Game::GameLoop()
{

    while (m_gameRunning)
    {

        m_currentFrameTime = SDL_GetTicks();
        float deltaTime = (m_currentFrameTime - m_previousFrameTime) / 1000.0f;

        std::cout << deltaTime << std::endl;

        m_previousFrameTime = m_currentFrameTime;

        HandleInput();
        UpdateGame(deltaTime);
        GenerateOutput();

        Uint64 frameEndTime = SDL_GetTicks();
        float frameDuration = static_cast<float>(frameEndTime - m_currentFrameTime);
        if (frameDuration < 1000.0f / 60.0f)
        {
            SDL_Delay(static_cast<Uint32>((1000.0f / 60.0f) - frameDuration));
        }
    }
}

void Game::HandleInput()
{

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            m_gameRunning = false;
        }

        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.scancode == SDL_SCANCODE_W)
            {
               m_paddle.SetPaddleDirection("north");
            }

            if (event.key.scancode == SDL_SCANCODE_S)
            {
                m_paddle.SetPaddleDirection("south");
            }
        }
        if (event.type == SDL_EVENT_KEY_UP)
        {
           m_paddle.SetPaddleDirection("");
        }
    }
}

void Game::UpdateGame(float deltaTime)
{

    m_paddle.MovePaddle(deltaTime);

}

void Game::GenerateOutput()
{

    SDL_SetRenderDrawColor(m_renderer, 12, 12, 12, 255);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 50, 100, 100, 255);

    SDL_RenderFillRect(m_renderer, &m_paddle.m_PongPaddle);
    SDL_RenderFillRect(m_renderer, &m_ball.m_ball);
    SDL_RenderPresent(m_renderer);
}
