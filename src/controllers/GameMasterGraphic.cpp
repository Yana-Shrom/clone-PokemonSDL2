#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cstdlib> // Pour rand()
#include <ctime>   // Pour time()

#include "GameMasterGraphic.h"
#include "../models/Map.h"
#include "../models/Player.h"
#include "../models/Inventory.h"
#include "../models/Battle.h"

using namespace std;

const int SIZE_SPRITE = 62;
float time()
{
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC;
}

GameMasterGraphic::GameMasterGraphic() : game()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() < 0)
    {
        cout << "Erreur lors de l'initialisation de SDL_ttf : " << TTF_GetError() << endl;
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

    // Creation de la fenetre
    
    //SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    window = SDL_CreateWindow("Pokemone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920 /*windowWidth*/, 1080/*windowHeight*/, SDL_WINDOW_FULLSCREEN);
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

    Background.loadFromFile("data/Designer.png", renderer);
    Bulbasaur.loadFromFile("data/Bulbasaur.gif", renderer);
    Charmander.loadFromFile("data/Charmander.gif", renderer);
    Squirtle.loadFromFile("data/Squirtle.gif", renderer);
    Chenipan.loadFromFile("data/Chenipan.gif", renderer);
    Aspicot.loadFromFile("data/Aspicot.gif", renderer);
    Pikachu.loadFromFile("data/Pikachu.gif", renderer);
    //player
    p1.loadFromFile("data/boy.png", renderer);


    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "Erreur lors de l'initialisation de SDL_mixer : " << Mix_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // Charger la musique de fond
    backgroundMusic = Mix_LoadMUS("data/battle.mp3");
    if (backgroundMusic == nullptr)
    {
        cout << "Erreur lors du chargement de la musique de fond : " << Mix_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    //Cree 10 personnage/*

    
    game.createPokemons(10);
    for(unsigned int z= 0; z <game.getPokemons().size();z++){
        //game.getPokemon(z).initializePosition(game.getConstMap());
    }
}
GameMasterGraphic::~GameMasterGraphic()
{
     //if (withSound)
       // Mix_Quit();
    //TTF_CloseFont(font);
    Mix_HaltMusic();
    Mix_FreeMusic(backgroundMusic);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

void GameMasterGraphic::Print()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    const Map &map = game.getConstMap();
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);


    // Obtenez la position du joueur
    const Player &player = game.getConstPlayer();
    int playerX = player.getPosition().x * SIZE_SPRITE;
    int playerY = player.getPosition().y * SIZE_SPRITE;

    // Définir les limites de suivi de la caméra autour du joueur
    int minX = playerX - 10 * SIZE_SPRITE;
    int minY = playerY - 10 * SIZE_SPRITE;
    int maxX = playerX + 10 * SIZE_SPRITE - windowWidth;
    int maxY = playerY + 10 * SIZE_SPRITE - windowHeight;

    // Limitez la caméra pour qu'elle reste dans les limites de la carte
    int cameraX = std::max(0, std::min(playerX - windowWidth / 2, map.getWidth() * SIZE_SPRITE - windowWidth));
    int cameraY = std::max(0, std::min(playerY - windowHeight / 2, map.getHeight() * SIZE_SPRITE - windowHeight));

    // Si le joueur est près du bord de la carte, ajustez la caméra pour le suivre sans sortir de la carte
    cameraX = std::min(std::max(cameraX, minX), maxX);
    cameraY = std::min(std::max(cameraY, minY), maxY);

    // Appliquez le zoom aux dimensions de la fenêtre
    //int zoomedWindowWidth = windowWidth * zoomFactor;
    //int zoomedWindowHeight = windowHeight * zoomFactor;

     for (int x = 0; x < map.getWidth() ; x++) {
        for (int y = 0; y < map.getHeight() ; y++) {
            // Ajustez les coordonnées de rendu en fonction du zoom
            int tileX = x * SIZE_SPRITE - cameraX;
            int tileY = y * SIZE_SPRITE - cameraY;

            if (tileX + SIZE_SPRITE < 0 || tileX > windowWidth || tileY + SIZE_SPRITE < 0 || tileY > windowHeight) {
                // Ne dessinez pas les tuiles qui ne sont pas visibles
                continue;
            }
            
            for(unsigned int z= 0; z <game.getPokemons().size();z++){
                int ptileX = game.getPokemon(z).getPosition().x * SIZE_SPRITE - cameraX;
                int ptileY = game.getPokemon(z).getPosition().y * SIZE_SPRITE - cameraY;
                if(game.getPokemon(z).getName()== "Bulbasaur")
                {
                    Bulbasaur.draw(renderer, ptileX, ptileY, SIZE_SPRITE , SIZE_SPRITE);
                }
                if(game.getPokemon(z).getName()== "Charmender"){
                    Charmander.draw(renderer, ptileX, ptileY, SIZE_SPRITE , SIZE_SPRITE);
                }
                if(game.getPokemon(z).getName()== "Squirtle"){
                    Squirtle.draw(renderer, ptileX, ptileY, SIZE_SPRITE , SIZE_SPRITE);
                }
                if(game.getPokemon(z).getName()== "Chenipan"){
                    Chenipan.draw(renderer, ptileX, ptileY, SIZE_SPRITE , SIZE_SPRITE);
                }
                if(game.getPokemon(z).getName()== "Aspicot"){
                    Aspicot.draw(renderer, ptileX, ptileY, SIZE_SPRITE , SIZE_SPRITE);
                }
                if(game.getPokemon(z).getName()== "Pikachu"){
                    Pikachu.draw(renderer, ptileX, ptileY, SIZE_SPRITE , SIZE_SPRITE);
                }
                
            }
            // Obtenez le caractère de la case de la carte
            char tile = map.getWidthHeight(x, y);

            // Dessinez l'élément correspondant de la carte avec les coordonnées zoomées
            switch (tile) {
                case '#':
                    tree.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case 'r':
                    rock.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case '$':
                    bush.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case 'g':
                    ground.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case ' ':
                    grass.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case '+':
                    water.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case '|':
                    rempartV.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case '_':
                    rempartH.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case 't':
                    top.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case 'b':
                    bottom.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case 'd':
                    right.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case 'l':
                    left.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case '-':
                    lotus.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case '.':
                    flower.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case '0':
                    topLeft.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case '6':
                    topRight.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case '4':
                    bottomRight.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case '3':
                    bottomLeft.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case '5':
                    cornerUpLeft.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case '1':
                    cornerBottomRight.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case '2':
                    cornerTopRight.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case 'p':
                    panneaux.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case 'y':
                    temple.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case 'u':
                    rempart1.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                case 'i':
                    rempart2.draw(renderer, tileX, tileY, SIZE_SPRITE , SIZE_SPRITE);
                    break;
                default:
                    break;
            }
            
        }
    }
    int tileX = player.getPosition().x * SIZE_SPRITE - cameraX;
    int tileY = player.getPosition().y * SIZE_SPRITE - cameraY;
    // Dessiner le joueur avec l'animation mise à jour
    p1.playAnimation(renderer,tileX , tileY, 16, 16, 6, SIZE_SPRITE ,SIZE_SPRITE);
    // Mettre à jour l'affichage
    SDL_RenderPresent(renderer);

    
}

void GameMasterGraphic::EventTick()
{
    SDL_Event events;
    bool quit = false;

    // Délai minimum entre chaque pression de touche en millisecondes
    const Uint32 DELAY_MS = 100; // par exemple, 200 millisecondes

    // Dernier moment où une touche a été pressée
    Uint32 lastKeyPressTime = 0;
    std::srand(std::time(0));
    Uint32 t = SDL_GetTicks(), nt;
    game.getPlayer().getInventory().addPokemon(Pokemon());
    afficheMenu();
    while (!quit)
    {
        nt = SDL_GetTicks();
        if (nt - t > 500)
        {
            for(unsigned int z= 0; z <game.getPokemons().size();z++){
                game.getPokemon(z).moveAuto(game.getConstMap());
                if(game.getPlayer().getPosition().x==game.getPokemon(z).getPosition().x && game.getPlayer().getPosition().y==game.getPokemon(z).getPosition().y)
                {
                    displayBattle(renderer, game.getPlayer(), game.getPokemon(z));
            
                }
            }
            t = nt;
        }
        
    

        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (events.type == SDL_KEYDOWN)
            {
                if (SDL_GetTicks() - lastKeyPressTime >= DELAY_MS)
                {
                    switch (events.key.keysym.sym)
                    {
                    case SDLK_z:
                        game.actionKeyboard('s');
                        p1.Walk();
                        p1.setCurrentRowFrameIndex(0);
                        std::cout << "passe " << std::endl;
                        break;
                    case SDLK_s:
                        game.actionKeyboard('z');
                        p1.Walk();
                        p1.setCurrentRowFrameIndex(1);
                        break;
                    case SDLK_q:
                        game.actionKeyboard('q');
                        p1.Walk();
                        p1.setCurrentRowFrameIndex(2);
                        break;
                    case SDLK_d:
                        game.actionKeyboard('d');
                        p1.Walk();
                        p1.setCurrentRowFrameIndex(3);
                        break;
                    case SDLK_i:
                        displayInventory(renderer, game.getPlayer().getInventory());
                        break;
                    case SDLK_ESCAPE:
                    case SDLK_n:
                        quit = true;
                        break;
                    default:
                        break;
                    }
                    // Mettre à jour le dernier moment où une touche a été pressée
                    lastKeyPressTime = SDL_GetTicks();
                }
            }
        }
        
    
        Print();
        
        SDL_RenderPresent(renderer);

    }
}

void GameMasterGraphic::afficheMenu() {
    bool quitMenu = false;
    SDL_Event e;
    Mix_PlayMusic(backgroundMusic, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);

    // Charger une police de caractères
    TTF_Font* font = TTF_OpenFont("data/arial.ttf", 24); // Ajustez le chemin et la taille de la police selon vos besoins
    if (font == nullptr) {
        std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    
    // Libérer la surface de l'image de fond car elle n'est plus nécessaire


    // Créer des couleurs pour le texte
    SDL_Color textColor = { 255, 255, 255 }; // Couleur blanche
    SDL_Color selectedColor = { 255, 0, 0 }; // Couleur rouge pour le bouton sélectionné

    // Texte des boutons
    std::string buttonsText[] = { "Singleplayer", "Multiplayer", "Help", "Credit", "Quit" };
    const int numButtons = sizeof(buttonsText) / sizeof(buttonsText[0]);
    int selectedButtonIndex = 0;

    while (!quitMenu) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quitMenu = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_z:
                        // Déplacer la sélection du menu vers le haut
                        selectedButtonIndex = (selectedButtonIndex - 1 + numButtons) % numButtons;
                        break;
                    case SDLK_s:
                        // Déplacer la sélection du menu vers le bas
                        selectedButtonIndex = (selectedButtonIndex + 1) % numButtons;
                        break;
                    case SDLK_SPACE:
                        // Exécuter l'action correspondant au bouton sélectionné
                        switch (selectedButtonIndex) {
                            case 0:
                                // Action pour Singleplayer
                                // Mettre à jour pour quitter le menu
                                quitMenu = true;
                                break;
                            case 1:
                                // Action pour Multiplayer
                                // Mettre à jour pour quitter le menu
                                quitMenu = true;
                                break;
                            case 2:
                                // Action pour Help
                                // Mettre à jour pour quitter le menu
                                quitMenu = true;
                                break;
                            case 3:
                                // Action pour Credit
                                // Mettre à jour pour quitter le menu
                                quitMenu = true;
                                break;
                            case 4:
                                // Action pour Quit
                                // Quitter l'application
                                quitMenu = true;
                                SDL_Quit();
                                exit(0);
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        // Effacer le rendu précédent
        SDL_RenderClear(renderer);

        // Dessiner le fond d'écran
        // (assurez-vous d'avoir une texture de fond chargée auparavant)
        //SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Calculer la position des boutons
        int buttonX = 100; // Position horizontale fixe
        int buttonY = 100; // Position verticale initiale
        int buttonSpacing = 20; // Espacement entre les boutons


        
        // Créer une texture à partir de la surface de l'image de fond
        Background.draw(renderer, 0, 0, 1920,1080);


        // Dessiner les boutons du menu sous forme de texte
        for (int i = 0; i < numButtons; ++i) {
            // Créer une surface de texte à partir de la police et du texte
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, buttonsText[i].c_str(), (i == selectedButtonIndex) ? selectedColor : textColor);
            if (textSurface == nullptr) {
                std::cerr << "Failed to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
                continue;
            }

            // Créer une texture à partir de la surface de texte
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (textTexture == nullptr) {
                std::cerr << "Failed to create text texture! SDL Error: " << SDL_GetError() << std::endl;
                SDL_FreeSurface(textSurface);
                continue;
            }

            // Dessiner la texture du texte
            SDL_Rect textRect = { buttonX, buttonY, textSurface->w, textSurface->h };
            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

            // Libérer la surface de texte et la texture du texte
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);

            // Mettre à jour la position verticale pour le prochain bouton
            buttonY += textSurface->h + buttonSpacing;
        }

        // Présenter le rendu
        SDL_RenderPresent(renderer);
    }

    // Fermer la police de caractères
    TTF_CloseFont(font);
    
}
void GameMasterGraphic::displayInventory(SDL_Renderer* renderer, Inventory& inventory) {
    // Définition des dimensions et de la position du rectangle de l'inventaire
    int inventoryWidth = 400;
    int inventoryHeight = 300;
    int inventoryX = (windowWidth - inventoryWidth) / 2;
    int inventoryY = (windowHeight - inventoryHeight) / 2;

    // Définition de la police et de la couleur du texte
    TTF_Font* font = TTF_OpenFont("data/arial.ttf", 24); // Remplacez "arial.ttf" par le chemin de votre police
    SDL_Color textColor = { 255, 255, 255, 255 };

    // Affichage du fond noir semi-transparent pour l'inventaire
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 20); // Noir avec une opacité de 200
    SDL_Rect inventoryRect = { inventoryX, inventoryY, inventoryWidth, inventoryHeight };
    SDL_RenderFillRect(renderer, &inventoryRect);

    // Affichage du cadre bleu autour de l'inventaire
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Bleu opaque
    SDL_RenderDrawRect(renderer, &inventoryRect);

    // Affichage du titre "Inventaire"
    SDL_Surface* titleSurface = TTF_RenderText_Solid(font, "Inventaire", textColor);
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    SDL_Rect titleRect = { inventoryX + 50, inventoryY + 20, titleSurface->w, titleSurface->h };
    SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
    SDL_FreeSurface(titleSurface);
    SDL_DestroyTexture(titleTexture);

    SDL_RenderPresent(renderer);

    // Affichage des noms des Pokémon dans le rectangle de l'inventaire
    int startY = inventoryY + 50;
    int padding = 10;
    unsigned int selectedItem = 0; // Index de l'élément sélectionné dans l'inventaire
    // Présentation du rendu de la fenêtre principale avec l'inventaire


    // Attente d'un événement pour interagir avec l'inventaire
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_z:
                        // Déplacer la sélection vers le haut
                        selectedItem = (selectedItem - 1 + inventory.getAllPokemons().size()) % inventory.getAllPokemons().size();
                        break;
                    case SDLK_s:
                        // Déplacer la sélection vers le bas
                        selectedItem = (selectedItem + 1) % inventory.getAllPokemons().size();
                        break;
                    case SDLK_SPACE:
                        // Sélectionner l'élément
                        // Vous pouvez ajouter votre logique de sélection ici
                        break;
                    case SDLK_i:
                        quit = true;
                        break;
                    default:
                        break;
                }
            }
        }

        for (unsigned int i = 0; i < inventory.getAllPokemons().size(); ++i) {
            // Détermination de la couleur du texte pour l'élément sélectionné
            if (i == selectedItem) {
                textColor = { 255, 0, 0, 255 }; // Rouge pour l'élément sélectionné
            } else {
                textColor = { 255, 255, 255, 255 }; // Blanc pour les autres éléments
            }

            // Création de la surface de texte pour le nom du Pokémon
            std::string pokemonName = std::to_string(i + 1) + ". " + inventory.getPokemon(i).getName();
            std::cout << inventory.getPokemon(i).getName()<< " et "<< i << std::endl;
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, pokemonName.c_str(), textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);

            // Affichage du texte du nom du Pokémon
            SDL_Rect textRect;
            textRect.x = inventoryX + 50;
            textRect.y = startY + (i * (TTF_FontHeight(font) + padding)); // Utilisation de TTF_FontHeight pour obtenir la hauteur du texte
            SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_RenderClear(renderer);
    // Nettoyage de la police
    TTF_CloseFont(font);
}


void GameMasterGraphic::displayBattle(SDL_Renderer* renderer, const Player& player, const Pokemon& pokemon) {
    Battle battle{player, pokemon};
    bool quitBattle = false;
    SDL_Event e;
    Mix_PlayMusic(backgroundMusic, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);

    // Charger une police de caractères
    TTF_Font* font = TTF_OpenFont("data/arial.ttf", 24); // Ajustez le chemin et la taille de la police selon vos besoins
    if (font == nullptr) {
        std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    // Libérer la surface de l'image de fond car elle n'est plus nécessaire

    // Créer des couleurs pour le texte
    SDL_Color textColor = { 255, 255, 255 }; // Couleur blanche
    SDL_Color selectedColor = { 255, 0, 0 }; // Couleur rouge pour le bouton sélectionné

    // Texte des boutons
    std::string buttonsText[] = { "Attack", "Defense", "Catch"};
    const int numButtons = sizeof(buttonsText) / sizeof(buttonsText[0]);
    int selectedButtonIndex = 0;

    // Dégradé de vert
    SDL_Rect gradientRect = {0, 0, 1920, 1080 / 2};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for (int i = 255; i > 0; i -= 5) {
        SDL_SetRenderDrawColor(renderer, 0, i, 0, 255);
        SDL_RenderFillRect(renderer, &gradientRect);
        gradientRect.y += 5;
    }

    // Variables pour l'animation de secousse
    int shakeOffset = 0;
    int shakeDirection = 1;

    while (!quitBattle) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quitBattle = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_z:
                        // Déplacer la sélection du menu vers le haut
                        selectedButtonIndex = (selectedButtonIndex - 1 + numButtons) % numButtons;
                        break;
                    case SDLK_s:
                        // Déplacer la sélection du menu vers le bas
                        selectedButtonIndex = (selectedButtonIndex + 1) % numButtons;
                        break;
                    case SDLK_SPACE:
                        // Exécuter l'action correspondant au bouton sélectionné
                        switch (selectedButtonIndex) {
                            case 0:
                                battle.process_action("Attack");
                                break;
                            case 1:
                                battle.process_action("Defense");
                                break;
                            case 2:
                                battle.process_action("catch");
                                break;
                            default:
                                SDL_Quit();
                                exit(0);
                                break;
                        }
                    case SDLK_e :
                        quitBattle=true;
                    break;
                }
            }
        }

        // Effacer le rendu précédent
        SDL_RenderClear(renderer);

        // Dessiner le fond d'écran
        // (assurez-vous d'avoir une texture de fond chargée auparavant)
        //SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Calculer la position des boutons
        int buttonX = 100; // Position horizontale fixe
        int buttonY = 1080 - 150; // Position verticale en bas
        int buttonSpacing = 20; // Espacement entre les boutons

        // Dessiner les boutons du menu sous forme de texte
        for (int i = 0; i < numButtons; ++i) {
            // Créer une surface de texte à partir de la police et du texte
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, buttonsText[i].c_str(), (i == selectedButtonIndex) ? selectedColor : textColor);
            if (textSurface == nullptr) {
                std::cerr << "Failed to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
                continue;
            }

            // Créer une texture à partir de la surface de texte
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (textTexture == nullptr) {
                std::cerr << "Failed to create text texture! SDL Error: " << SDL_GetError() << std::endl;
                SDL_FreeSurface(textSurface);
                continue;
            }

            // Dessiner la texture du texte
            SDL_Rect textRect = { buttonX, buttonY, textSurface->w, textSurface->h };
            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

            // Libérer la surface de texte et la texture du texte
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);

            // Mettre à jour la position verticale pour le prochain bouton
            buttonY += textSurface->h + buttonSpacing;
        }

        // Animation de secousse des images de Pokémon
        shakeOffset += shakeDirection * 5;
        if (abs(shakeOffset) >= 10) {
            shakeDirection *= -1;
        }

        // Dessiner l'image du Pokémon du joueur en bas à gauche
        // Remplacer playerPokemonTexture par la texture du Pokémon du joueur
    int X = 50;
    int Y = 1080 - 200;

    if(game.getPlayer().getInventory().getPokemon(0).getName()=="Bulbasaur")
    {
        Bulbasaur.draw(renderer, X, Y, SIZE_SPRITE , SIZE_SPRITE);
    }
    else if(game.getPlayer().getInventory().getPokemon(0).getName()=="Charmander")
    {
        Charmander.draw(renderer, X, Y, SIZE_SPRITE , SIZE_SPRITE);
    }
    else if(game.getPlayer().getInventory().getPokemon(0).getName()=="Squirtle")
    {
        Squirtle.draw(renderer, X, Y, SIZE_SPRITE , SIZE_SPRITE);
    }
    else if(game.getPlayer().getInventory().getPokemon(0).getName()=="Chenipan")
    {
        Chenipan.draw(renderer, X, Y, SIZE_SPRITE , SIZE_SPRITE);
    }
    else if(game.getPlayer().getInventory().getPokemon(0).getName()=="Aspicot")
    {
        Aspicot.draw(renderer, X, Y, SIZE_SPRITE , SIZE_SPRITE);
    }
    else if(game.getPlayer().getInventory().getPokemon(0).getName()=="Pikachu")
    {
        Pikachu.draw(renderer, X, Y, SIZE_SPRITE , SIZE_SPRITE);
    }

    X = 1920-200;
    Y = 50;

    if(pokemon.getName()=="Bulbasaur")
    {
        Bulbasaur.draw(renderer, X, Y, SIZE_SPRITE , SIZE_SPRITE);
    }
    else if(pokemon.getName()=="Charmander")
    {
        Charmander.draw(renderer, X, Y, SIZE_SPRITE , SIZE_SPRITE);
    }
    else if(pokemon.getName()=="Squirtle")
    {
        Squirtle.draw(renderer, X, Y, SIZE_SPRITE , SIZE_SPRITE);
    }
    else if(pokemon.getName()=="Chenipan")
    {
        Chenipan.draw(renderer, X, Y, SIZE_SPRITE , SIZE_SPRITE);
    }
    else if(pokemon.getName()=="Aspicot")
    {
        Aspicot.draw(renderer, X, Y, SIZE_SPRITE , SIZE_SPRITE);
    }
    else if(pokemon.getName()=="Pikachu")
    {
        Pikachu.draw(renderer, X, Y, SIZE_SPRITE , SIZE_SPRITE);
    }
    // Afficher la vie du Pokémon
    std::string healthText = "HP: " + std::to_string(pokemon.getLife()) + "/" + std::to_string(100);
    SDL_Surface* healthSurface = TTF_RenderText_Solid(font, healthText.c_str(), textColor);
    if (healthSurface == nullptr) {
        std::cerr << "Failed to render health surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
    } else {
        SDL_Texture* healthTexture = SDL_CreateTextureFromSurface(renderer, healthSurface);
        if (healthTexture == nullptr) {
            std::cerr << "Failed to create health texture! SDL Error: " << SDL_GetError() << std::endl;
        } else {
            SDL_Rect healthRect = {X, Y + SIZE_SPRITE, healthSurface->w, healthSurface->h};
            SDL_RenderCopy(renderer, healthTexture, nullptr, &healthRect);
            SDL_FreeSurface(healthSurface);
            SDL_DestroyTexture(healthTexture);
        }
    }
            SDL_RenderPresent(renderer);
        }

    // Fermer la police de caractères
    TTF_CloseFont(font);
}
