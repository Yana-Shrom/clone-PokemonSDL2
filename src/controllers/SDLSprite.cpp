

#include "SDLSprite.h"
#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

SDLSprite::SDLSprite() : m_surface(nullptr), m_texture(nullptr), m_hasChanged(false), m_currentRowFrameIndex(0), m_currentColFrameIndex(0), walk(false)
{
}

SDLSprite::~SDLSprite()
{
    if (m_surface) SDL_FreeSurface(m_surface);
    if (m_texture) SDL_DestroyTexture(m_texture);

    m_surface = nullptr;
    m_texture = nullptr;
    m_hasChanged = false;
}

SDLSprite::SDLSprite(const SDLSprite &im)
{
    // @ TODO  Il faut recopier la surface et la texture de im dans cette nouvelle Image
    assert(false);
}

SDLSprite &SDLSprite::operator=(const SDLSprite &im)
{
    // @TODO  Il faut recopier la surface et la texture de im dans cette nouvelle Image
    assert(false);
    return *this;
}

void SDLSprite::loadFromFile(const char *filename, SDL_Renderer *renderer)
{
    m_surface = IMG_Load(filename);
    if (m_surface == nullptr)
    {
        string nfn = string("../") + filename;
        cout << "Error: cannot load " << filename << ". Trying " << nfn << endl;
        m_surface = IMG_Load(nfn.c_str());
        if (m_surface == nullptr)
        {
            nfn = string("../") + nfn;
            m_surface = IMG_Load(nfn.c_str());
        }
    }
    if (m_surface == nullptr)
    {
        cout << "Error: cannot load " << filename << endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Surface *surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(m_surface, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(m_surface);
    m_surface = surfaceCorrectPixelFormat;

    m_texture = SDL_CreateTextureFromSurface(renderer, surfaceCorrectPixelFormat);
    if (m_texture == NULL)
    {
        cout << "Error: problem to create the texture of " << filename << endl;
        SDL_Quit();
        exit(1);
    }
}

void SDLSprite::loadFromCurrentSurface(SDL_Renderer *renderer)
{
    m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
    if (m_texture == nullptr)
    {
        cout << "Error: problem to create the texture from surface " << endl;
        SDL_Quit();
        exit(1);
    }
}

void SDLSprite::draw(SDL_Renderer *renderer, int x, int y, int w, int h)
{
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w < 0) ? m_surface->w : w;
    r.h = (h < 0) ? m_surface->h : h;

    if (m_hasChanged)
    {
        ok = SDL_UpdateTexture(m_texture, nullptr, m_surface->pixels, m_surface->pitch);
        assert(ok == 0);
        m_hasChanged = false;
    }

    ok = SDL_RenderCopy(renderer, m_texture, nullptr, &r);
    assert(ok == 0);
}

void SDLSprite::draw2(SDL_Renderer *renderer, int x, int y, int frameWidth, int frameHeight, int targetWidth, int targetHeight)
{
    int ok;
    SDL_Rect srcRect; // Rectangle source pour la frame à dessiner
    srcRect.x = m_currentColFrameIndex * frameWidth; // La coordonnée x de la frame dans la spritesheet
    srcRect.y = m_currentRowFrameIndex * frameHeight; // La coordonnée y de la frame dans la spritesheet
    srcRect.w = frameWidth; // Largeur de la frame dans la spritesheet
    srcRect.h = frameHeight; // Hauteur de la frame dans la spritesheet

    SDL_Rect destRect; // Rectangle de destination pour le dessin
    destRect.x = x;
    destRect.y = y;
    destRect.w = (targetWidth < 0) ? frameWidth : targetWidth; // Largeur de la frame à dessiner
    destRect.h = (targetHeight < 0) ? frameHeight : targetHeight; // Hauteur de la frame à dessiner

    if (m_hasChanged)
    {
        ok = SDL_UpdateTexture(m_texture, nullptr, m_surface->pixels, m_surface->pitch);
        assert(ok == 0);
        m_hasChanged = false;
    }

    ok = SDL_RenderCopy(renderer, m_texture, &srcRect, &destRect);
    assert(ok == 0);
}

void SDLSprite::playAnimation(SDL_Renderer *renderer, int x, int y, int frameWidth, int frameHeight, int numFrames, int targetWidth, int targetHeight)
{
    if(!walk){
        draw2(renderer, x, y, frameWidth, frameHeight, targetWidth, targetHeight);
    }else{
        for (int i=0; i < numFrames; ++i)
        {
            setCurrentColFrameIndex(i);
            draw2(renderer, x, y, frameWidth, frameHeight, targetWidth, targetHeight);
            SDL_RenderPresent(renderer);// Facultatif : Pause entre chaque frame (en millisecondes)
            SDL_Delay(10);// Vous pouvez ajuster le délai selon la vitesse de votre animation
        }
    }
    setCurrentColFrameIndex(0);
    walk=false;

    //A ajouter si le temps quand on lache la touche ou maintient pour quoi affecte aussi l'animation
}

