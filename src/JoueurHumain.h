#ifndef JOUEURHUMAIN_H
#define JOUEURHUMAIN_H

#pragma once

#include "Joueur.h"
#include "Pion.hpp"
#include <string>
using namespace std;

class JoueurHumain :public Joueur 
{
public:
    JoueurHumain(string nom, Pion couleur);
    JoueurHumain( const JoueurHumain & other);
    ~JoueurHumain();
    JoueurHumain & operator=( const JoueurHumain & other);

    std::pair<int, int> choisirCoup(const Plateau3D& plateau);

protected:

};

#endif