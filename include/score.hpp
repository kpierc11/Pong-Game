#include <SDL3/SDL.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

class Score
{
public:
    Score();
    ~Score();

    void CreateScoreTexture(SDL_Renderer *renderer);
    void UpdateScoreTexture(SDL_Renderer *renderer);
    SDL_Texture *GetTexture() const { return m_scoreTexture; }
    SDL_FRect m_scoreRect;
    int m_currentScore;

private:
    SDL_Surface *m_scoreText;
    SDL_Texture *m_scoreTexture;
    TTF_Font *m_scoreFont;
    SDL_Color m_scoreColor = {255, 255, 255, SDL_ALPHA_OPAQUE};
};