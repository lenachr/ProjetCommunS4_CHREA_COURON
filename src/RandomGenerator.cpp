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
// Descriptif de la chaine de Markov
// Difficultés rencontrèes et regard citique sur le projet

// Fonction pour générer un nombre aléatoire entre 0 et 1
double randomProbability()
{
    static std::random_device               rd;
    static std::mt19937                     gen(rd());
    static std::uniform_real_distribution<> dis(0, 1);
    // std::cout << "rnd : " << dis(gen) << std::endl;
    return dis(gen);
}

// Loi binomiale de Bernoulli pour placer les arbres aléaoirement plus dans les angles avec plus de chances que ce soit en face à gauche
float generateRandomPositionTree()
{
    float u = static_cast<float>(rand()) / RAND_MAX;

    if (u < 0.7f)
    {
        return 0.0f + u * 100.0f;
    }
    else
    {
        return 0.0f + u * -100.0f;
    }
}

// float randPoisson(float alpha)
// {
//     float L = std::exp(-alpha);
//     float p = 1.0;
//     float k = 0;

//     do
//     {
//         k++;
//         p *= static_cast<float>(std::rand()) / RAND_MAX;
//         k += static_cast<float>(std::rand()) / (RAND_MAX / 2) - 1.0f;
//     } while (p > L);

//     return k * 10;
// }

// Fonction pour simuler une chute de cerf-volant
bool boidFall(double probability)
{
    return randomProbability() <= probability;
}

// Fonction pour simuler le temps entre chaque chute de cerf-volant
double timeBetweenFalls(double lambda)
{
    static std::random_device              rd;
    static std::mt19937                    gen(rd());
    static std::exponential_distribution<> dis(lambda);
    // std::cout << "rnd : " << dis(gen) << std::endl;
    return dis(gen);
}

// Loi exponentielle qui fait tomber des cerf-volants
bool boidFalling(float timeStart)
{
    const double probabilityOfFalling = 0.2; // Probabilité de chute d'un boid
    const double lambda               = 0.1; // Paramètre lambda de la loi exponentielle pour le temps entre chaque chute
    const int    X                    = 15;  // Intervalle de temps entre chaque chute (en secondes)
    const int    simulationTime       = 60;  // Durée de simulation (en secondes)

    // connaitre le temps écoulé depuis le début de la simulation

    // int timeStart = glutGet(GLUT_ELAPSED_TIME);
    // int timeNow   = glutGet(GLUT_ELAPSED_TIME);
    // int elapsed   = timeNow - timeStart;

    // int timeElapsed = 0; // Temps écoulé
    float timeNow     = static_cast<int>(glfwGetTime() * 1000.0); // Assuming GLUT_ELAPSED_TIME is defined in GLUT library
    float timeElapsed = (timeNow - timeStart) / 10000.0f;
    // auto start       = std::chrono::high_resolution_clock::now();
    // auto now         = std::chrono::high_resolution_clock::now();
    // auto timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
    // std::cout << "now : " << now << std::endl;
    // while (timeElapsed < simulationTime)
    // {
    double timeUntilNextFall = timeBetweenFalls(lambda) * 1000;
    // timeElapsed              = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
    // timeElapsed += X; // Avance dans le temps de X secondes

    // Vérifie si un boid tombe à ce moment-là
    std::cout << "timeUntilNextFall : " << timeUntilNextFall << " & elps time" << timeElapsed << " & now : " << timeNow << std::endl;
    if (timeUntilNextFall <= X && boidFall(probabilityOfFalling) && timeUntilNextFall > timeElapsed)
    {
        std::cout << "Un boid est tombé au sol à " << timeElapsed << " secondes." << std::endl;
        return true;
    }
    else
    {
        return false;
        // std::cout << "Aucun boid n'est tombé au sol à " << timeElapsed << " secondes." << std::endl;
    }
    // }
}

// Fonction pour choisir aléatoirement une texture de boid, loi de distribution uniforme
std::string chooseBoidTexture()
{
    const double probabilityTexture1 = 0.4;
    if (randomProbability() <= probabilityTexture1)
    {
        return "Texture 1";
    }
    else
    {
        return "Texture 2";
    }
}

// Choix de la couleur de la pierre selon une distribution normale
std::string chooseRockColor()
{
    const double meanGrayProbability = 0.7; // Probabilité d'avoir un gris moyen
    const double meanGrayValue       = 128; // Valeur de gris moyen
    const double stdDev              = 50;  // Écart-type de la distribution normale

    double colorValue = randomProbability();

    if (colorValue >= 0.25 && colorValue <= 0.75)
    {
        // Gris moyen
        return "Gray (" + std::to_string(static_cast<int>(colorValue * 255)) + ")";
    }
    else if (colorValue < 0.25)
    {
        // Limite inférieure (noir)
        return "Dark Gray";
    }
    else
    {
        // Limite supérieure (blanc)
        return "light Gray";
    }
}