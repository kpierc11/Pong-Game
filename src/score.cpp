#include "score.hpp"
#include <string>

Score::Score() : m_scoreText(nullptr), m_scoreTexture(nullptr), m_currentScore(0), m_scoreFont(nullptr), m_scoreColor({})
{
    m_scoreRect.h = 200;
    m_scoreRect.w = 200;
    m_scoreRect.x = 100;
    m_scoreRect.y = 50;
}

Score::~Score()
{
    if (m_scoreFont)
        TTF_CloseFont(m_scoreFont);
    if (m_scoreTexture)
        SDL_DestroyTexture(m_scoreTexture);
}

/*Creates the initial score texture. */
void Score::CreateScoreTexture(SDL_Renderer *renderer)
{

    m_scoreColor = {255, 255, 255, 255};

    m_scoreFont = TTF_OpenFont("assets/fonts/roboto.ttf", 24);
    if (!m_scoreFont)
    {
        SDL_Log("Couldn't open font: %s\n", SDL_GetError());
    }

    std::string s = std::to_string(m_currentScore);
    const char *scoreText = s.c_str();

    m_scoreText = TTF_RenderText_Solid(m_scoreFont, scoreText, strlen(scoreText), m_scoreColor);
    if (m_scoreText)
    {
        m_scoreTexture = SDL_CreateTextureFromSurface(renderer, m_scoreText);
        m_scoreRect.w = m_scoreText->w;
        m_scoreRect.h = m_scoreText->h;
        SDL_DestroySurface(m_scoreText);
    }
    if (!m_scoreTexture)
    {
        SDL_Log("Couldn't create text: %s\n", SDL_GetError());
    }
}

/*Updates the score texture with the new score value*/
void Score::UpdateScoreTexture(SDL_Renderer *renderer)
{

    std::string s = std::to_string(m_currentScore);
    const char *scoreText = s.c_str();

    m_scoreText = TTF_RenderText_Solid(m_scoreFont, scoreText, strlen(scoreText), m_scoreColor);

    if (m_scoreTexture)
    {
        SDL_DestroyTexture(m_scoreTexture);
    }

    if (m_scoreText)
    {
        m_scoreTexture = SDL_CreateTextureFromSurface(renderer, m_scoreText);
        m_scoreRect.w = m_scoreText->w;
        m_scoreRect.h = m_scoreText->h;
        SDL_DestroySurface(m_scoreText);
    }
    if (!m_scoreTexture)
    {
        SDL_Log("Couldn't create text: %s\n", SDL_GetError());
    }
}
