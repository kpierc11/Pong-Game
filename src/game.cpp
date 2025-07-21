#include "game.hpp"

bool paddleMovingNorth = false;
bool paddleMovingSouth = false;

Game::Game() : m_window(nullptr), m_renderer(nullptr), m_gameRunning(true), m_paddle({}), m_speed(.05f), m_direction("")
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
        640,              // width, in pixels
        480,              // height, in pixels
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

    m_paddle.h = 100;
    m_paddle.w = 10;
    m_paddle.x = 50;
    m_paddle.y = 50;

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
        HandleInput();
        UpdateGame();
        GenerateOutput();
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
                paddleMovingNorth = true;
                paddleMovingSouth = false;
            }

            if (event.key.scancode == SDL_SCANCODE_S)
            {
                paddleMovingNorth = false;
                paddleMovingSouth = true;
            }
        }
        if(event.type == SDL_EVENT_KEY_UP)
        {
             paddleMovingNorth = false;
                paddleMovingSouth = false;
        }
    }
}

void Game::UpdateGame()
{

    if (paddleMovingNorth)
    {
        if (m_paddle.y >= 0)
        {
            m_paddle.y -= m_speed;
        }
    }

    if (paddleMovingSouth)
    {
        if (m_paddle.y <= 480.0f - m_paddle.h)
        {
            m_paddle.y += m_speed;
        }
    }
}

void Game::GenerateOutput()
{

    SDL_SetRenderDrawColor(m_renderer, 12, 12, 12, 255);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 50, 100, 100, 255);

    SDL_RenderFillRect(m_renderer, &m_paddle);

    SDL_RenderPresent(m_renderer);
}
