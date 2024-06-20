#ifndef _VECTOR2D_H
#define _VECTOR2D_H

#include <math.h>

/**
 * @file Vector2D.h
 * @brief Fichier d'en-tête déclarant la structure Vector2D pour représenter un vecteur 2D.
 */

/**
 * @struct Vector2D
 * @brief Structure représentant un vecteur 2D.
 *
 * Cette structure encapsule les coordonnées x et y d'un vecteur 2D et fournit des opérations mathématiques de base.
 */
struct Vector2D
{
    int x; /**< Coordonnée x du vecteur. */
    int y; /**< Coordonnée y du vecteur. */

    /**
     * @brief Constructeur par défaut de la structure Vector2D.
     */
    Vector2D();

    /**
     * @brief Constructeur de la structure Vector2D prenant des coordonnées spécifiques.
     * @param nx La coordonnée x du vecteur.
     * @param ny La coordonnée y du vecteur.
     */
    Vector2D(const int &nx, const int &ny);

    /**
     * @brief Surcharge de l'opérateur d'addition pour additionner deux vecteurs.
     * @param a Le vecteur à ajouter.
     * @return Le résultat de l'addition.
     */
    Vector2D operator+(const Vector2D &a);

    /**
     * @brief Surcharge de l'opérateur de soustraction pour soustraire deux vecteurs.
     * @param a Le vecteur à soustraire.
     * @return Le résultat de la soustraction.
     */
    Vector2D operator-(const Vector2D &a);

    /**
     * @brief Surcharge de l'opérateur de multiplication pour effectuer le produit de deux vecteurs.
     * @param a Le vecteur à multiplier.
     * @return Le résultat du produit.
     */
    Vector2D operator*(const Vector2D &a);

    /**
     * @brief Surcharge de l'opérateur de multiplication pour multiplier un vecteur par un scalaire.
     * @param i Le scalaire à multiplier.
     * @return Le résultat de la multiplication par le scalaire.
     */
    Vector2D operator*(const int &i);

    /**
     * @brief Calcule la norme du vecteur.
     * @return La norme du vecteur.
     */
    Vector2D calculNorme();
};

#endif
