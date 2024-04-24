#pragma once
#include <chrono>
#include <glimac/common.hpp>
#include "p6/p6.h"

double randomProbability();
float  variance();
float  esperance();
float  randPoisson(float alpha);
double timeBetweenFalls(double lambda);
bool   boidFall(double probability);

// Loi binomiale de Bernoulli pour placer les arbres aléaoirement plus dans les angles avec plus de chances que ce soit en face à gauche
float generateRandomPositionTree();
// Loi exponentielle qui fait tomber des cerf-volants
// bool boidFalling(auto start, auto now);
bool boidFalling(float timeStart);
// Fonction pour choisir aléatoirement une texture de boid, loi de distribution uniforme
std::string chooseBoidTexture();
// Choix de la couleur de la pierre selon une distribution normale
double chooseRockColor();
// Fonction pour choisir la vitesse verticale aléatoire du boud avec une distribution de Laplace
double chooseVerticalBoidSpeed();
// Fonction pour placer les maisons sur la carte, loi de distribution bimodale
double placeHouses();
// Si le boid rencontre un nuage
bool crossNuage();