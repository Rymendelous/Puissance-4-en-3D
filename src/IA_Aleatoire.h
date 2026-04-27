#ifndef IA_ALEATOIRE_H
#define IA_ALEATOIRE_H

#pragma once
#include "JoueurIA.h"
#include "Pion.hpp"
#include <string>
#include <random>

using namespace std;

class IA_Aleatoire : public JoueurIA
{
public:
    IA_Aleatoire(Pion couleur);

    IA_Aleatoire(string nom, Pion couleur);
    IA_Aleatoire( const IA_Aleatoire & other);
    ~IA_Aleatoire();
    IA_Aleatoire & operator=( const IA_Aleatoire & other);

    std::pair<int, int> choisirCoup(const Plateau3D& plateau);

protected:
    mt19937 moteur;

};

#endif