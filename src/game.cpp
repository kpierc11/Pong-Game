#include "game.hpp"
#include <cmath>
#include <SDL3_ttf/SDL_ttf.h>

float scoreTimePassed = 0;

Game::Game() : m_window(nullptr), m_renderer(nullptr), m_screenWidth(900), m_screenHeight(480), m_gameScoreCount(0), m_gameRunning(true), m_paddle({}), m_speed(300.0f), m_direction(Direction::None), m_currentFrameTime(SDL_GetTicks()), m_previousFrameTime(0), m_textureManager({}), m_scoreManager({}), m_PongBalls({})
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

    if (!TTF_Init())
    {
        SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
        return 0;
    }

    m_scoreManager.CreateScoreTexture(m_renderer);

    SDL_Texture *textureBall = m_textureManager.LoadTexture(m_renderer, "assets/pepe-frog-head.bmp");

    for (int i = 0; i < 1; i++)
    {
        Ball ball;
        ball.SetBallTexture(textureBall);
        ball.SetGame(this);

        m_PongBalls.push_back(ball);
    }

   // m_ball.SetGame(this);

    char *filePath = SDL_GetPrefPath("EmberwindStudios", "PongGame");

    printf(filePath);
    WriteGameFile();
    ReadGameFile();

    return 1;
}

void Game::EndGame()
{
    WriteGameFile();
    ReadGameFile();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    TTF_Quit();
    SDL_Quit();
}

void Game::GameLoop()
{

    while (m_gameRunning)
    {

        m_currentFrameTime = SDL_GetTicks();
        float deltaTime = (m_currentFrameTime - m_previousFrameTime) / 1000.0f;

        m_previousFrameTime = m_currentFrameTime;

        HandleInput();
        UpdateGame(deltaTime);
        GenerateOutput();

        // Uint64 frameEndTime = SDL_GetTicks();
        // float frameDuration = static_cast<float>(frameEndTime - m_currentFrameTime);
        // if (frameDuration < 1000.0f / 60.0f)
        // {
        //     SDL_Delay(static_cast<Uint32>((1000.0f / 60.0f) - frameDuration));
        // }
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

        if (event.type == SDL_EVENT_MOUSE_MOTION)
        {
        }

        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.scancode == SDL_SCANCODE_W)
            {
                m_paddle.SetPaddleDirection(Direction::North);
            }

            if (event.key.scancode == SDL_SCANCODE_S)
            {
                m_paddle.SetPaddleDirection(Direction::South);
            }
        }
        if (event.type == SDL_EVENT_KEY_UP)
        {
            m_paddle.SetPaddleDirection(Direction::None);
        }
    }
}

void Game::UpdateGame(float deltaTime)
{
    float mouseX, mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    for (auto &ball : m_PongBalls)
    {
        ball.MoveBall(deltaTime, m_paddle);
    }

    //m_ball.MoveBall(deltaTime, m_paddle);

    m_paddle.MovePaddle(deltaTime);

    scoreTimePassed += deltaTime;

    if (scoreTimePassed > 2.0f)
    {

        m_gameScoreCount += 50;
        scoreTimePassed = 0;

        SDL_Texture *textureBall = m_textureManager.LoadTexture(m_renderer, "assets/pepe-frog-head.bmp");

        Ball ball;
        ball.SetBallTexture(textureBall);
        ball.SetGame(this);

        m_PongBalls.push_back(ball);
    }

    m_scoreManager.m_currentScore = m_gameScoreCount;
    m_scoreManager.UpdateScoreTexture(m_renderer);
}

void Game::GenerateOutput()
{

    SDL_SetRenderDrawColor(m_renderer, 12, 12, 12, 255);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

    SDL_RenderFillRect(m_renderer, &m_paddle.m_PongPaddle);

    for (auto &ball : m_PongBalls)
    {
        SDL_RenderFillRect(m_renderer, &ball.m_ball);
    }

    SDL_RenderDebugText(m_renderer, 50, 50, "Score");
    SDL_RenderTexture(m_renderer, m_scoreManager.GetTexture(), NULL, &m_scoreManager.m_scoreRect);

    SDL_RenderPresent(m_renderer);
}

void Game::ReadGameFile()
{
    SDL_Storage *user = SDL_OpenUserStorage("EmberwindStudios", "PongGame", 0);
    if (user == NULL)
    {
        // Something bad happened!
    }
    while (!SDL_StorageReady(user))
    {
        SDL_Delay(1);
    }

    Uint64 saveLen = 0;
    if (SDL_GetStorageFileSize(user, "save0.sav", &saveLen) && saveLen > 0)
    {
        void *dst = SDL_malloc(saveLen);
        if (SDL_ReadStorageFile(user, "save0.sav", dst, saveLen))
        {
            // Interpret the bytes as an int
            int loadedScore = *(int *)dst;

            SDL_Log("Loaded score: %d", loadedScore);
        }
        else
        {
            // Something bad happened!
        }
        SDL_free(dst);
    }
    else
    {
        // Something bad happened!
    }

    SDL_CloseStorage(user);
}

void Game::WriteGameFile()
{

    SDL_Storage *user = SDL_OpenUserStorage("EmberwindStudios", "PongGame", 0);
    if (user == NULL)
    {
        SDL_Log("Couldn't open user storage: %s\n", SDL_GetError());
    }
    while (!SDL_StorageReady(user))
    {
        SDL_Delay(1);
    }

    int saveData = m_gameScoreCount;
    const void *saveDataPtr = &saveData;
    Uint64 saveLen = sizeof(saveData);
    if (!SDL_WriteStorageFile(user, "save0.sav", saveDataPtr, saveLen))
    {

    }

    SDL_CloseStorage(user);
}
