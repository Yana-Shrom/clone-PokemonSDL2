#ifndef _GAMEMASTERGRAPHIC_H
#define _GAMEMASTERGRAPHIC_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "../models/Game.h"
#include "SDLSprite.h"



class GameMasterGraphic
{
private:
    Game game;

    SDL_Window *window;
    SDL_Renderer *renderer;
    //TTF_Font *font;
    SDLSprite font_im;
    //SDL_Color font_color;
    SDLSprite tree;
    SDLSprite rock;
    SDLSprite bush;
    SDLSprite ground;
    SDLSprite grass;
    SDLSprite water;
    SDLSprite rempartV;
    SDLSprite rempartH;
    SDLSprite top;
    SDLSprite bottom;
    SDLSprite right;
    SDLSprite left;
    SDLSprite lotus;
    SDLSprite flower;
    SDLSprite bottomLeft;
    SDLSprite bottomRight;
    SDLSprite topRight;
    SDLSprite topLeft;
    SDLSprite cornerUpLeft;
    SDLSprite cornerBottomRight;
    SDLSprite cornerTopRight;
    SDLSprite panneaux;
    SDLSprite temple;
    SDLSprite rempart1;
    SDLSprite rempart2;
    SDLSprite Background;
    
    SDLSprite Bulbasaur;
    SDLSprite Charmander;
    SDLSprite Squirtle;
    SDLSprite Chenipan;
    SDLSprite Aspicot;
    SDLSprite Pikachu;
    Mix_Music* backgroundMusic;
    
    //bool withSound;
    SDLSprite p1;
    int windowWidth, windowHeight;
public:
    GameMasterGraphic();
    ~GameMasterGraphic();
    void Print();
    void EventTick();
    void afficheMenu();
    void displayInventory(SDL_Renderer *renderer, Inventory &inventory);
    void displayBattle(SDL_Renderer *renderer, const Player &player, const Pokemon &pokemon);
};

#endif