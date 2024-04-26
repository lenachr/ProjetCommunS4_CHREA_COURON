#include "RandomGenerator.hpp"
#include <iostream>

// CONSIGNES

// CODE
// On doit avoir au moins une simulaiton de 8 variables alatoires
// 1) Les lois de variables doivent toutes être différentes
// 2) Les lois douvent être connues
// 3) 4 des variables douvent être à densité par rapport à la mesure de Lebesgue
// 4) Au moins une variable ne doit pas prendre ses valeurs dans un ensemble numérique
// 5) On doit connaitre l'espérance et la variance des variables
// 6) on doit avoir la maitrise de l'ensemble des paramètres régissant les lois de variables utilisées
// 7) pouvoir consulter des données statistiques des variables

// RAPPORT
// Décrire les variables aléatoires : comment elles interviennet dans le programme, la méthode de simulaiton utilisée, pourquoi on a choisi cette loi
// Descriptif de la chaine de Markov ainsi qu'éventuellement d'autres structures de correlations
// Difficultés rencontrèes et regard citique sur le projet

// Fonction pour générer un nombre aléatoire entre 0 et 1
double randomProbability()
{
    double U = static_cast<float>(rand()) / RAND_MAX;

    return U;
}

float variance(int loi, float p, float q)
{
    switch (loi)
    {
    case 1: // Loi binomiale de Bernoulli
        return p * (1 - p);
    case 2: // Loi exponentielle
        return 1 / (p * p);
    case 3: // Loi uniforme
        return ((q - p) * (q - p)) / 12;
    case 4: // Loi normale
        return q * q;
    case 5: // Loi de Laplace
        return 2 * q * q;
    default:
        return -1; // Type de loi invalide
    }
    // float variance = 0;
    // return variance;
}

float esperance(int loi, float p, float q)
{
    switch (loi)
    {
    case 1: // Loi binomiale de Bernoulli
        return p;
    case 2: // Loi exponentielle
        return 1 / p;
    case 3: // Loi uniforme
        return (p + q) / 2;
    case 4: // Loi normale
        return p;
    case 5: // Loi de Laplace
        return p;
    default:
        return -1; // Type de loi invalide
    }
    // float esperance = 0;
    // return esperance;
}

// Loi binomiale de Bernoulli pour placer les arbres aléaoirement plus dans les angles avec plus de chances que ce soit en face à gauche
float generateRandomPositionTree()
{
    float u = randomProbability();
    float p = 0.7f;

    // Affichage variance et esperance
    // std::cout << "Esperance : " << esperance(1, p, 0) << std::endl;
    // std::cout << "Variance : " << variance(1, p, 0) << std::endl;

    if (u < p)
    {
        return 0.0f + u * 100.0f;
    }
    else
    {
        return 0.0f + u * -100.0f;
    }
}

// Fonction pour simuler une chute de cerf-volant
bool boidFall(double probability)
{
    return randomProbability() <= probability;
}

// Fonction pour simuler le temps entre chaque chute de cerf-volant avec une loi exponentielle
double timeBetweenFalls(double lambda)
{
    // Génération d'un nombre aléatoire U entre 0 et 1
    float U = randomProbability();

    // Calcul de la valeur selon la loi exponentielle
    float result = -1 / lambda * log(1 - U);

    return result;
}

// Loi exponentielle qui fait tomber des cerf-volants
bool boidFalling(float timeStart)
{
    const double probabilityOfFalling = 0.2; // Probabilité de chute d'un boid
    const double lambda               = 0.1; // Paramètre lambda de la loi exponentielle pour le temps entre chaque chute
    const int    X                    = 15;  // Intervalle de temps entre chaque chute (en secondes)

    // Affichage variance et esperance
    // std::cout << "Esperance : " << esperance(2, lambda, 0) << std::endl;
    // std::cout << "Variance : " << variance(2, lambda, 0) << std::endl;

    float timeNow     = static_cast<int>(glfwGetTime() * 1000.0); // Le tmeps actuel
    float timeElapsed = (timeNow - timeStart) / 10000.0f;         // Le temps écoulé depuis le début de la simulation

    double timeUntilNextFall = timeBetweenFalls(lambda) * 30000; // On choisi aléatoirement le temps avant la prochaine chance de chute

    // On vérifie si on est en dehors de l'intervalle de temps pour la prochaine chance de chute et si on doit chuter
    if (timeUntilNextFall <= X && boidFall(probabilityOfFalling) && timeUntilNextFall > timeElapsed)
    {
        // std::cout << "Un boid tombe au sol apres " << timeElapsed << " secondes." << std::endl;
        return true;
    }
    else
    {
        // std::cout << "Aucun boid n'est tombé au sol à " << timeElapsed << " secondes." << std::endl;
        return false;
    }
}

// Fonction pour choisir aléatoirement une texture de boid, loi de Bernoulli
std::string chooseBoidTexture()
{
    const double probabilityTexture1 = 0.4;

    // Affichage variance et esperance
    // std::cout << "Esperance : " << esperance(1, probabilityTexture1, 0) << std::endl;
    // std::cout << "Variance : " << variance(1, probabilityTexture1, 0) << std::endl;

    if (randomProbability() <= probabilityTexture1)
    {
        return "Texture 1";
    }
    else
    {
        return "Texture 2";
    }
}

// Choix de la couleur de la pierre selon une loi normale
double chooseRockColor()
{
    // Génération d'un nombre aléatoire U1 et U2
    double U1 = randomProbability();
    double U2 = randomProbability();

    // Distribution normale centrée autour de 0 et écart-type 1
    double Z = sqrt(-2 * log(U1)) * cos(2 * 3.1415 * U2);

    // Redimensionner et décaler Z pour qu'il soit centré autour de 0.5 et dans l'intervalle [0, 1]
    double mu           = 0.5;
    double sigma        = 0.2;
    double randomNumber = mu + sigma * Z; // écart-type = 0.2

    // Affichage variance et esperance
    // std::cout << "Esperance : " << esperance(4, mu, sigma) << std::endl;
    // std::cout << "Variance : " << variance(4, mu, sigma) << std::endl;

    // On empêche la valeur de sortir de l'intervalle [0, 1]
    if (randomNumber < 0.0)
    {
        randomNumber = 0.0;
    }
    else if (randomNumber > 1.0)
    {
        randomNumber = 1.0;
    }

    return randomNumber;
}

// Fonction pour choisir la vitesse verticale aléatoire du boid avec une distribution de Laplace
double chooseVerticalBoidSpeed()
{
    // Génération de deux nombres aléatoires uniformément distribués U1 et U2 dans l'intervalle [0, 1]
    double U1 = randomProbability();
    double U2 = randomProbability();

    // Calcul de la position verticale aléatoire avec une distribution de Laplace
    double mu           = 0.3; // Moyenne de la distribution (centrée autour de 0.5 pour le milieu de l'intervalle vertical)
    double b            = 0.2; // Paramètre d'échelle de la distribution (contrôle de la dispersion des valeurs)
    double randomNumber = mu - b * log(U1 / U2);

    // Affichage variance et esperance
    // std::cout << "Esperance : " << esperance(5, mu, b) << std::endl;
    // std::cout << "Variance : " << variance(5, mu, b) << std::endl;

    // On empêche la valeur de sortir de l'intervalle [-0.5, 0.5]
    if (randomNumber < -0.5)
    {
        randomNumber = -0.5;
    }
    else if (randomNumber > 0.5)
    {
        randomNumber = 0.5;
    }

    return randomNumber;
}

// Fonction pour placer les maisons sur la carte, loi de distribution bimodale
double placeHouses()
{
    const double centerProbability = 0.8;   // Probabilité que les maisons soient au centre
    const double centerMin         = -20.0; // Coord min pour le centre
    const double centerMax         = 0.0;   // Coord max pour le centre
    const double edgeMin           = -50.0; // Coord min de la carte
    const double edgeMax           = 30.0;  // Coord max de la carte

    double r = randomProbability();

    // Affichage variance et esperance
    // double esperance = centerProbability * ((centerMin + centerMax) / 2) + (1 - centerProbability) * ((edgeMin + edgeMax) / 2);
    // double variance  = centerProbability * pow(((centerMax - centerMin) / 2), 2) + (1 - centerProbability) * pow(((edgeMax - edgeMin) / 2), 2) + centerProbability * (1 - centerProbability) * pow(((centerMax - centerMin) / 2) - ((edgeMin + edgeMax) / 2), 2);
    // std::cout << "Esperance : " << esperance << std::endl;
    // std::cout << "Variance : " << variance << std::endl;

    // Calculer la position en fonction de la distribution bimodale
    if (r <= centerProbability)
    {
        // Dans le centre
        double rnd = static_cast<double>(rand());

        double randomNumber = centerMin + (rnd / RAND_MAX) * (centerMax - centerMin);

        // On empêche la valeur de sortir de l'intervalle [-50, 50]
        if (randomNumber < edgeMin)
        {
            randomNumber = edgeMin;
        }
        else if (randomNumber > edgeMax)
        {
            randomNumber = edgeMax;
        }

        return static_cast<int>(randomNumber);
    }
    else
    {
        // Dans les bords
        double rnd = static_cast<double>(rand());

        double randomNumber = edgeMin + (rnd / RAND_MAX) * (edgeMax - edgeMin);

        // On empêche la valeur de sortir de l'intervalle [-50, 50]
        if (randomNumber < edgeMin)
        {
            randomNumber = edgeMin;
        }
        else if (randomNumber > edgeMax)
        {
            randomNumber = edgeMax;
        }

        return static_cast<int>(randomNumber);
    }
}

// Si le boid rencontre un nuage
bool crossNuage()
{
    double rnd   = randomProbability();
    double proba = 0.8; // On définit la probabilité que le nuage ait un effet

    // Affichage variance et esperance
    // std::cout << "Esperance : " << esperance(1, proba, 0) << std::endl;
    // std::cout << "Variance : " << variance(1, proba, 0) << std::endl;

    if (rnd < proba)
    {
        // std::cout << "Le nuage affectent la vitesse" << std::endl;
        return true;
    }
    else
    {
        // std::cout << "Le nuages n'affecte pas la vitesse." << std::endl;
        return false;
    }
}

// Sélectionner le type d'arbre
int selectTree()
{
    double              random                = randomProbability();
    double              cumulativeProbability = 0.0;
    std::vector<double> treeProbabilities     = {0.7, 0.3};

    // Affichage variance et esperance
    // double esperance = treeProbabilities[0] * 0 + treeProbabilities[1] * 1;
    // double variance  = treeProbabilities[0] * (0 - esperance) * (0 - esperance) + treeProbabilities[1] * (1 - esperance) * (1 - esperance);
    // std::cout << "Esperance : " << esperance << std::endl;
    // std::cout << "Variance : " << variance << std::endl;

    for (int i = 0; i < treeProbabilities.size(); ++i)
    {
        cumulativeProbability += treeProbabilities[i];
        if (random <= cumulativeProbability)
        {
            return i;
        }
    }

    return -1;
}