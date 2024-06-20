#ifndef _POKEMON_H
#define _POKEMON_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Vector2D.h"
#include "Map.h"

/**
 * @file Pokemon.h
 * @brief Fichier d'en-tête déclarant la classe Pokemon pour représenter un Pokémon dans le jeu.
 */

/**
 * @class Pokemon
 * @brief Classe représentant un Pokémon dans le jeu.
 *
 * Cette classe encapsule la logique nécessaire pour représenter un Pokémon dans le jeu, y compris son nom, sa vie, son genre, ses types et sa position.
 */
class Pokemon {
private:
    std::string name; /**< Nom du Pokémon. */
    int life; /**< Points de vie du Pokémon. */
    bool isMale; /**< Genre du Pokémon. */
    std::vector<std::string> types; /**< Types du Pokémon. */
    Vector2D position; /**< Position du Pokémon sur la carte. */
    static const int MAX_DISTANCE = 3; /**< Distance maximale de déplacement automatique du Pokémon. */
    int m_dir; /**< Direction actuelle du déplacement du Pokémon. */

public:
    /**
     * @brief Obtient le nom du Pokémon.
     * @return Le nom du Pokémon.
     */
    std::string getName() const;

    /**
     * @brief Constructeur par défaut de la classe Pokemon.
     */
    Pokemon();

    /**
     * @brief Destructeur de la classe Pokemon.
     */
    ~Pokemon();

    /**
     * @brief Analyse une chaîne de caractères représentant les types d'un Pokémon.
     * @param typesStr La chaîne de caractères représentant les types du Pokémon.
     * @return Un vecteur de chaînes de caractères représentant les types du Pokémon.
     */
    std::vector<std::string> parseTypes(const std::string &typesStr);

    /**
     * @brief Déplace automatiquement le Pokémon sur la carte.
     * @param map La carte sur laquelle le Pokémon se déplace.
     */
    void moveAuto(const Map &map);

    /**
     * @brief Initialise la position initiale du Pokémon sur la carte.
     * @param map La carte sur laquelle le Pokémon se trouve.
     */
    void initializePosition(const Map &map);

    /**
     * @brief Obtient le genre du Pokémon.
     * @return Le genre du Pokémon.
     */
    std::string getGenre() const;

    /**
     * @brief Obtient les points de vie actuels du Pokémon.
     * @return Les points de vie actuels du Pokémon.
     */
    int getLife() const;

    /**
     * @brief Inflige des dégâts au Pokémon.
     * @param nbDamage Le nombre de dégâts à infliger.
     */
    void damage(int nbDamage);

    /**
     * @brief Déplace le Pokémon vers la gauche sur la carte.
     * @param map La carte sur laquelle le Pokémon se déplace.
     */
    void left(const Map &map);

    /**
     * @brief Déplace le Pokémon vers la droite sur la carte.
     * @param map La carte sur laquelle le Pokémon se déplace.
     */
    void right(const Map &map);

    /**
     * @brief Déplace le Pokémon vers le haut sur la carte.
     * @param map La carte sur laquelle le Pokémon se déplace.
     */
    void up(const Map &map);

    /**
     * @brief Déplace le Pokémon vers le bas sur la carte.
     * @param map La carte sur laquelle le Pokémon se déplace.
     */
    void down(const Map &map);

    /**
     * @brief Déplace le Pokémon de manière aléatoire sur la carte.
     * @param map La carte sur laquelle le Pokémon se déplace.
     */
    void moveRandomly(const Map &map);

    /**
     * @brief Vérifie si une direction donnée est valide pour le déplacement du Pokémon sur la carte.
     * @param map La carte sur laquelle le Pokémon se déplace.
     * @param direction La direction à vérifier.
     * @return True si la direction est valide, sinon False.
     */
    bool isDirectionValid(const Map &map, const Vector2D &direction) const;

    /**
     * @brief Obtient la prochaine position du Pokémon après un déplacement dans une direction spécifiée.
     * @param map La carte sur laquelle le Pokémon se déplace.
     * @param direction La direction du déplacement.
     * @return La prochaine position du Pokémon.
     */
    Vector2D getNextPosition(const Map &map, const Vector2D &direction) const;

    /**
     * @brief Obtient la position actuelle du Pokémon sur la carte.
     * @return La position actuelle du Pokémon.
     */
    Vector2D getPosition() const;

    /**
     * @brief Analyse une ligne de texte représentant les informations d'un Pokémon.
     * @param line La ligne de texte représentant les informations d'un Pokémon.
     * @return Un vecteur de chaînes de caractères représentant les informations du Pokémon.
     */
    std::vector<std::string> parsePokemon(const std::string &line);

    /**
     * @brief Obtient les informations d'un Pokémon à partir d'un fichier à un index spécifié.
     * @param filename Le nom du fichier contenant les informations des Pokémon.
     * @param index L'index du Pokémon dans le fichier.
     * @return Un vecteur de chaînes de caractères représentant les informations du Pokémon.
     */
    std::vector<std::string> getPokemonInfoFromFile(const std::string &filename, int index);
};

/**
 * @brief Obtient la position actuelle du Pokémon sur la carte.
 * @return La position actuelle du Pokémon.
 */
inline Vector2D Pokemon::getPosition() const
{
    return position;
}

/**
 * @brief Analyse une ligne de texte représentant les informations d'un Pokémon.
 * @param line La ligne de texte représentant les informations d'un Pokémon.
 * @return Un vecteur de chaînes de caractères représentant les informations du Pokémon.
 */
inline std::vector<std::string> Pokemon::parsePokemon(const std::string &line) {
    std::vector<std::string> result;

    // Créer un flux à partir de la chaîne de caractères
    std::istringstream iss(line);

    // Variables pour stocker les valeurs extraites
    std::string id, name, size, weight, types;

    // Extraire les valeurs séparées par le délimiteur '/'
    std::getline(iss, id, '/');
    std::getline(iss, name, '{');
    std::getline(iss, size, ',');
    std::getline(iss, weight, ',');

    // Extraire les types entre parenthèses
    std::getline(iss, types, '}');
    types = types.substr(types.find("(") + 1, types.find(")") - types.find("(") - 1);

    // Ajouter les valeurs extraites au résultat
    result.push_back(name);
    result.push_back(size);
    result.push_back(weight);
    result.push_back(types);

    return result;
}

/**
 * @brief Obtient les informations d'un Pokémon à partir d'un fichier à un index spécifié.
 * @param filename Le nom du fichier contenant les informations des Pokémon.
 * @param index L'index du Pokémon dans le fichier.
 * @return Un vecteur de chaînes de caractères représentant les informations du Pokémon.
 */
inline std::vector<std::string> Pokemon::getPokemonInfoFromFile(const std::string &filename, int index) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return {};
    }

    // Lire et ignorer les lignes jusqu'à ce que l'indice corresponde
    std::string line;
    for (int i = 0; i < index; ++i) {
        if (!std::getline(file, line)) {
            std::cerr << "L'indice de ligne spécifié est en dehors de la plage du fichier." << std::endl;
            return {};
        }
    }

    // Lire la ligne correspondante
    if (!std::getline(file, line)) {
        std::cerr << "L'indice de ligne spécifié est en dehors de la plage du fichier." << std::endl;
        return {};
    }

    // Fermer le fichier
    file.close();

    // Extraire les informations du Pokémon à partir de la ligne
    return parsePokemon(line);
}
#endif

