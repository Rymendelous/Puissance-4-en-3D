#ifndef PARTIE_H
#define PARTIE_H

#pragma once
#include "Joueur.h"
#include "Plateau3D.h"

class Partie
{
public:
    Partie();
    Partie(Joueur* J1,Joueur* J2);
    Partie( const Partie & other);
    ~Partie();
    Partie & operator=( const Partie & other);

    bool victoire_tour(Joueur *j);

    void lancer();


protected:
    Joueur* J1;
    Joueur* J2;
    Plateau3D plateau;
    int tours_joues=0;

};

#endif