#include "Pokemon.h"
#include <cstdlib> // Pour rand()
#include <ctime> // Pour time()

std::string Pokemon::getName() const
{
    return name;
}

Pokemon::Pokemon(): position(Vector2D(48,10)), m_dir(0)
{
    // Initialiser la seed pour la génération de nombres aléatoires
    std::srand(std::time(0));

    // Lire le fichier stats.txt et obtenir les informations sur les Pokémon disponibles
    std::vector<std::vector<std::string>> pokemonData;
    std::ifstream statsFile("data/stats.txt");
    if (statsFile.is_open()) {
        std::string line;
        while (std::getline(statsFile, line)) {
            pokemonData.push_back(parsePokemon(line));
        }
        statsFile.close();
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier stats.txt." << std::endl;
        return;
    }

    // Choisir un Pokémon aléatoire
    int randomIndex = std::rand() % pokemonData.size();
    std::vector<std::string> randomPokemonInfo = pokemonData[randomIndex];

    // Initialiser les propriétés du Pokémon avec les valeurs correspondantes
    name = randomPokemonInfo[0]; // Nom du Pokémon
    life = 100; // Points de vie
    isMale = std::rand() % 2 == 0; // Genre aléatoire
    types = parseTypes(randomPokemonInfo[3]); // Types du Pokémon
}
Pokemon::~Pokemon() {}

std::vector<std::string> Pokemon::parseTypes(const std::string& typesStr) {
    std::vector<std::string> types;
    std::istringstream iss(typesStr);
    std::string type;
    while (std::getline(iss, type, ',')) {
        types.push_back(type);
    }
    return types;
}

void Pokemon::moveAuto(const Map &map)
{
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    int xtmp, ytmp;
    xtmp = position.x + dx[m_dir];
    ytmp = position.y + dy[m_dir];
    if (map.estPositionValide(xtmp, ytmp))
    {
        position.x  = xtmp;
        position.y = ytmp;
    }
    else
        m_dir = rand() % 4;
}



int Pokemon::getLife() const
{
    return life;
}

void Pokemon::damage(int nbDamage)
{
    life-=nbDamage;
}

void Pokemon::left(const Map &map)
{
    if(map.estPositionValide(position.x-1, position.y)){
        std::cout <<"position valide"<<std::endl;
        position.x--;
    }
}

void Pokemon::right(const Map &map)
{
    if(map.estPositionValide(position.x+1, position.y))
        position.x++;
}

void Pokemon::up(const Map &map)
{
    if(map.estPositionValide(position.x, position.y+1))
        position.y++;
}

void Pokemon::down(const Map &map)
{
    if(map.estPositionValide(position.x, position.y-1))
        position.y--;
}

void Pokemon::moveRandomly(const Map& map) {
    // Supposons que nous avons défini MAX_DISTANCE comme constante membre de classe

    // Déterminer les directions possibles
    std::vector<Vector2D> possibleDirections = {Vector2D(0, 1), Vector2D(0, -1), Vector2D(1, 0), Vector2D(-1, 0)};

    // Choisir une direction aléatoire parmi les directions possibles
    Vector2D direction;
    do {
        direction = possibleDirections[std::rand() % possibleDirections.size()];
    } while (!isDirectionValid(map, direction));

    // Déplacer le Pokémon dans la direction choisie
    position = getNextPosition(map, direction);
}

bool Pokemon::isDirectionValid(const Map& map, const Vector2D& direction) const {
    // Vérifier si la prochaine position est valide sur la carte
    Vector2D nextPosition = getNextPosition(map, direction);
    if (!map.estPositionValide(nextPosition.x, nextPosition.y)) {
        return false;
    }

    // Calculer la magnitude du déplacement
    int displacementMagnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // Vérifier si le déplacement est trop brusque (limite de maxDistance)
    return displacementMagnitude <= MAX_DISTANCE;
}
Vector2D Pokemon::getNextPosition(const Map& map, const Vector2D& direction) const {
    // Calculer la prochaine position en fonction de la direction
    Vector2D nextPosition = getPosition()+direction;

    // Vérifier si la prochaine position est valide sur la carte
    if (!map.estPositionValide(nextPosition.x, nextPosition.y)) {
        // Si la prochaine position n'est pas valide, rester sur place
        return position;
    }

    return nextPosition;
}