#ifndef _MAP_H
#define _MAP_H

#include <vector>
#include <cassert>

/**
 * @file Map.h
 * @brief Fichier d'en-tête déclarant la classe Map pour représenter la carte du jeu.
 */

/**
 * @class Map
 * @brief Classe représentant la carte du jeu.
 *
 * Cette classe encapsule la logique nécessaire pour représenter la carte du jeu, y compris les différents types de cases.
 */
class Map {
private:
    /**
     * @brief Énumération des différents types de cases possibles sur la carte.
     */
    enum TypeCase
    {
        TREE = '#',
        ROCK = 'r',
        BUSH = '$',
        GROUND = 'g',
        GRASS = ' ',
        WATER = '+',
        REMPARTV = '|',
        REMPARTH = '_',
        TOP = 't',
        BOTTOM = 'b',
        RIGHT = 'd',
        LEFT = 'l',
        LOTUS = '-',
        FLOWER = '.',
        TOPLEFT = '0',
        TOPRIGHT = '6',
        BOTTOMRIGHT = '4',
        BOTTOMLEFT = '3',
        CORNERUPLEFT = '5',
        CORNERBOTTOMRIGHT ='1',
        CORNERTOPRIGHT = '2',
        PANNEAUX = 'p',
        TEMPLE = 'y',
        REMPART1 = 'u',
        REMPART2 = 'i'
    };

    int width; /**< Largeur de la carte. */
    int height; /**< Hauteur de la carte. */
    TypeCase cells[200][200]; /**< Tableau représentant les cellules de la carte. */

public:
    /**
     * @brief Constructeur par défaut de la classe Map.
     */
    Map();

    /**
     * @brief Vérifie si une position donnée est valide sur la carte.
     * @param x Coordonnée horizontale.
     * @param y Coordonnée verticale.
     * @return True si la position est valide, sinon False.
     */
    bool estPositionValide(const int x, const int y) const;

    /**
     * @brief Obtient le type de case à une position donnée sur la carte.
     * @param x Coordonnée horizontale.
     * @param y Coordonnée verticale.
     * @return Le type de case à la position spécifiée.
     */
    TypeCase getWidthHeight(const int x, const int y) const;

    /**
     * @brief Obtient le caractère représentant le type de case à une position donnée sur la carte.
     * @param x Coordonnée horizontale.
     * @param y Coordonnée verticale.
     * @return Le caractère représentant le type de case à la position spécifiée.
     */
    unsigned char getXYtoChar(const int x, const int y) const;

    /**
     * @brief Obtient la largeur de la carte.
     * @return La largeur de la carte.
     */
    int getWidth() const;

    /**
     * @brief Obtient la hauteur de la carte.
     * @return La hauteur de la carte.
     */
    int getHeight() const;

};

/**
 * @brief Obtient la largeur de la carte.
 * @return La largeur de la carte.
 */
inline int Map::getWidth() const { return width;}

/**
 * @brief Obtient la hauteur de la carte.
 * @return La hauteur de la carte.
 */
inline int Map::getHeight() const { return height;}

/**
 * @brief Obtient le type de case à une position donnée sur la carte.
 * @param x Coordonnée horizontale.
 * @param y Coordonnée verticale.
 * @return Le type de case à la position spécifiée.
 */
inline Map::TypeCase Map::getWidthHeight(const int x, const int y) const
{
    return cells[y][x];
}

/**
 * @brief Obtient le caractère représentant le type de case à une position donnée sur la carte.
 * @param x Coordonnée horizontale.
 * @param y Coordonnée verticale.
 * @return Le caractère représentant le type de case à la position spécifiée.
 */
inline unsigned char Map::getXYtoChar(const int x, const int y) const
{
    assert(x >= 0);
    assert(y >= 0);
    assert(x < width);
    assert(y < height);
    return (char)(cells[y][x]);
}

#endif
