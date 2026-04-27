#ifndef JOUEURIA_H
#define JOUEURIA_H

#pragma once

#include "Joueur.h"
#include "Plateau3D.h"
#include "Pion.hpp"
#include <string>

using namespace std;

class JoueurIA : public Joueur
{
public:
    JoueurIA(Pion couleur );
    JoueurIA( string nom , Pion couleur);
    JoueurIA( const JoueurIA & other);
    ~JoueurIA();
    JoueurIA & operator=( const JoueurIA & other);

protected:

};

#endif