#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "controllers/SDLSprite.h"

using namespace std;

const int SIZE_SPRITE = 32;

float time()
{
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC;
}


// Structure représentant le personnage
struct Character {
    int x, y; // Position du personnage
    SDLSprite sprite; // Sprite du personnage
};

// Fonction pour vérifier si un déplacement est valide
bool isValidMove(const char map[19][143], int x, int y) {
    // Vérifier les limites de la carte
    if (x < 0 || x >= 142 || y < 0 || y >= 19) {
        return false; // Déplacement en dehors de la carte
    }

    // Vérifier si la case est vide ou contient un obstacle (-)
    if (map[y][x] == ' ' || map[y][x] == '-') {
        return true; // Déplacement valide
    }

    return false; // Déplacement invalide
}

int main()
{
    const char map[19][143] = 
    {
        "#############0ttt6##############################              ##### ------##############--------#####################       ##################",
        "#############l5b2d##############################              ####  ------##############----------##################         #################",
        "#############34y34#####################0ttt6####-             ###   -------##############----------##############             ################",
        "#########|  ggggggg |####  ########0ttt1+++d####--            ###     r #---  -############--------############    p           #### ##########",
        "#########|  ggggggg | ##     ######l+++++++d###---          #####      ##-------#############-------########                          ########", 
        "######## |  $ggggg$ |          ##0t1+++5bbb4##----           ###    r  ### ------##############-----#######                              #####",        
        "######   |  ggggggg |          0t1+++5b4   ##-----           ##       #####  -- #################---####                      ##   r       ###",
        "####  .  |  $g$g$g$ |          32+++54     ##----- ##        #      ########    #################-  ##                      ####   r        ##",
        "#    ....|          |           l+++d      ##-----####  r  #    r   ######## r   ########   ##                      #############  r   r    ##",
        "    .....u##__| |___i     ##    3bbb4      ###-- #####    ##       #######       ####             r              ##################r       ###",
        "     ....#### | |p        ###    ###        ##   #####    ##      #######             r                        ####################       ####",
        "####  .  ####             #####  ####        # r ####    ##       #######                                    #######################    ######",
        "######    p##             ####    ###            ###                ####                                    ##################################",
        "#######          ..  ..  ..##                    ###                                                     #####################################",
        "########                                                                                               #######################################",
        "#############                      ##                                                            #############################################",
        "##############..  ..  ..   ###   # #####   #               ##                    r  ##   #####################################################",
        "########################################## ###        ###########         ###   ##############################################################",
        "##############################################################################################################################################",
    };
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
    //Mix_Chunk *sound;
    //bool withSound;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
     
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
/*
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        cout << "No sound !!!" << endl;
        // SDL_Quit();exit(1);
        withSound = false;
    }
    else
        withSound = true;
*/
    int dimx, dimy;
    dimx = 142;//game.getConstTerrain().getDimY();
    dimy = 19;//game.getConstTerrain().getDimX();
    dimx = dimx * SIZE_SPRITE;
    dimy = dimy * SIZE_SPRITE;

    // Creation de la fenetre
    window = SDL_CreateWindow("Pokemone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    tree.loadFromFile("data/tree.png", renderer);
    rock.loadFromFile("data/rock.jpg", renderer);
    bush.loadFromFile("data/bush.png", renderer);
    ground.loadFromFile("data/ground.png", renderer);
    grass.loadFromFile("data/grass.png", renderer);
    water.loadFromFile("data/water.png", renderer);
    rempartH.loadFromFile("data/barriere.jpg", renderer);
    rempartV.loadFromFile("data/barrierevertical.jpg", renderer);
    top.loadFromFile("data/top.jpg", renderer);
    bottom.loadFromFile("data/bottom.png", renderer);
    right.loadFromFile("data/right.jpg", renderer);
    left.loadFromFile("data/left.png", renderer);
    lotus.loadFromFile("data/lotus.png", renderer);
    flower.loadFromFile("data/flower.png", renderer);
    bottomLeft.loadFromFile("data/bottomLeft.png", renderer);
    bottomRight.loadFromFile("data/bottomRight.png", renderer);
    topLeft.loadFromFile("data/topLeft.png", renderer);
    topRight.loadFromFile("data/topRight.png", renderer);
    cornerUpLeft.loadFromFile("data/cornerUpLeft.png", renderer);
    cornerBottomRight.loadFromFile("data/cornerBottomRight.png", renderer);
    cornerTopRight.loadFromFile("data/cornerTopRight.png", renderer);
    panneaux.loadFromFile("data/panneaux.png", renderer);
    temple.loadFromFile("data/temple.jpg", renderer);
    rempart1.loadFromFile("data/barriere1.jpg", renderer);
    rempart2.loadFromFile("data/barriere2.jpg", renderer);
    
    while(true)
    {
        SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
        SDL_RenderClear(renderer);
        int x, y;

        for (x=0; x<142; x++)
            for (y=0; y<19; y++){
                if (map[y][x]== '#')
                    tree.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== 'r')
                    rock.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== '$')
                    bush.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== 'g')
                    ground.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== ' ')
                    grass.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== '+')
                    water.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== '|')
                    rempartV.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== '_')
                    rempartH.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== 't')
                    top.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== 'b')
                    bottom.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== 'd')
                    right.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== 'l')
                    left.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== '-')
                    lotus.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== '.')
                    flower.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== '0')
                    topLeft.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== '6')
                    topRight.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== '4')
                    bottomRight.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== '3')
                    bottomLeft.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== '5')
                    cornerUpLeft.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== '1')
                    cornerBottomRight.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== '2')
                    cornerTopRight.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== 'p')
                    panneaux.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== 'y')
                    temple.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== 'u')
                    rempart1.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
                if (map[y][x]== 'i')
                    rempart2.draw(renderer, x * SIZE_SPRITE, y * SIZE_SPRITE, SIZE_SPRITE, SIZE_SPRITE);
            }
        SDL_RenderPresent(renderer);
    }

//DESTRUCTION
 /*if (withSound)
        Mix_Quit();
    TTF_Quit();*/
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

