#ifndef _IMAGE_H
#define _IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <vector>

/**
 * @file Image.h
 * @brief Fichier d'en-tête déclarant la classe SDLSprite pour gérer les images avec SDL2.
 */

/**
 * @class SDLSprite
 * @brief Classe pour gérer une image avec SDL2.
 *
 * Cette classe encapsule la logique nécessaire pour charger, afficher et animer des images avec SDL2.
 */
class SDLSprite
{

private:
    SDL_Surface *m_surface; /**< Surface de l'image. */
    SDL_Texture *m_texture; /**< Texture de l'image. */
    bool m_hasChanged; /**< Indique si l'image a été modifiée. */
    int m_currentRowFrameIndex; /**< Indice de la ligne de la frame actuelle. */
    int m_currentColFrameIndex; /**< Indice de la colonne de la frame actuelle. */
    bool walk; /**< Indique si l'animation est en cours. */

public:
    /**
     * @brief Constructeur par défaut de la classe SDLSprite.
     */
    SDLSprite();

    /**
     * @brief Destructeur de la classe SDLSprite.
     */
    ~SDLSprite();

    /**
     * @brief Constructeur de copie de la classe SDLSprite.
     * @param im Objet SDLSprite à copier.
     */
    SDLSprite(const SDLSprite &im);

    /**
     * @brief Opérateur d'assignation de la classe SDLSprite.
     * @param im Objet SDLSprite à assigner.
     * @return Une référence vers l'objet SDLSprite assigné.
     */
    SDLSprite &operator=(const SDLSprite &im);

    /**
     * @brief Charge une image à partir d'un fichier.
     * @param filename Chemin du fichier image.
     * @param renderer Pointeur vers le renderer SDL.
     */
    void loadFromFile(const char *filename, SDL_Renderer *renderer);

    /**
     * @brief Charge l'image à partir de la surface actuelle.
     * @param renderer Pointeur vers le renderer SDL.
     */
    void loadFromCurrentSurface(SDL_Renderer *renderer);

    /**
     * @brief Dessine l'image.
     * @param renderer Pointeur vers le renderer SDL.
     * @param x Coordonnée x de l'image.
     * @param y Coordonnée y de l'image.
     * @param w Largeur de l'image (par défaut -1 pour la taille réelle).
     * @param h Hauteur de l'image (par défaut -1 pour la taille réelle).
     */
    void draw(SDL_Renderer *renderer, int x, int y, int w = -1, int h = -1);

    /**
     * @brief Dessine l'image avec des paramètres de taille de cible.
     * @param renderer Pointeur vers le renderer SDL.
     * @param x Coordonnée x de l'image.
     * @param y Coordonnée y de l'image.
     * @param frameWidth Largeur de la frame de l'animation.
     * @param frameHeight Hauteur de la frame de l'animation.
     * @param targetWidth Largeur de la cible.
     * @param targetHeight Hauteur de la cible.
     */
    void draw2(SDL_Renderer *renderer, int x, int y, int frameWidth, int frameHeight, int targetWidth, int targetHeight);

    /**
     * @brief Joue une animation.
     * @param renderer Pointeur vers le renderer SDL.
     * @param x Coordonnée x de l'animation.
     * @param y Coordonnée y de l'animation.
     * @param frameWidth Largeur de la frame de l'animation.
     * @param frameHeight Hauteur de la frame de l'animation.
     * @param numFrames Nombre de frames de l'animation.
     * @param targetWidth Largeur de la cible.
     * @param targetHeight Hauteur de la cible.
     */
    void playAnimation(SDL_Renderer *renderer, int x, int y, int frameWidth, int frameHeight, int numFrames, int targetWidth, int targetHeight);

    /**
     * @brief Définit l'indice de la ligne de la frame actuelle.
     * @param index Indice de la ligne de la frame.
     */
    void setCurrentRowFrameIndex(int index);

    /**
     * @brief Obtient l'indice de la ligne de la frame actuelle.
     * @return L'indice de la ligne de la frame actuelle.
     */
    int getCurrentRowFrameIndex() const;

    /**
     * @brief Définit l'indice de la colonne de la frame actuelle.
     * @param index Indice de la colonne de la frame.
     */
    void setCurrentColFrameIndex(int index);

    /**
     * @brief Obtient l'indice de la colonne de la frame actuelle.
     * @return L'indice de la colonne de la frame actuelle.
     */
    int getCurrentColFrameIndex() const;

    /**
     * @brief Active l'animation.
     */
    void Walk();
};

/**
 * @brief Définit l'indice de la ligne de la frame actuelle.
 * @param index Indice de la ligne de la frame.
 */
inline void SDLSprite::setCurrentRowFrameIndex(int index) { m_currentRowFrameIndex = index; }

/**
 * @brief Obtient l'indice de la ligne de la frame actuelle.
 * @return L'indice de la ligne de la frame actuelle.
 */
inline int SDLSprite::getCurrentRowFrameIndex() const { return m_currentRowFrameIndex; }

/**
 * @brief Définit l'indice de la colonne de la frame actuelle.
 * @param index Indice de la colonne de la frame.
 */
inline void SDLSprite::setCurrentColFrameIndex(int index) { m_currentColFrameIndex = index; }

/**
 * @brief Obtient l'indice de la colonne de la frame actuelle.
 * @return L'indice de la colonne de la frame actuelle.
 */
inline int SDLSprite::getCurrentColFrameIndex() const { return m_currentColFrameIndex; }

/**
 * @brief Active l'animation.
 */
inline void SDLSprite::Walk() { walk = true; }

#endif
