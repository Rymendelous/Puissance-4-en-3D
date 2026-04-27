#ifndef JOUEUR_H
#define JOUEUR_H

#pragma once

#include "Pion.hpp"
#include "Plateau3D.h"
#include <string>


class Joueur
{
public:
    Joueur(std::string nom, Pion couleur);
    virtual ~Joueur();

    virtual std::pair<int, int> choisirCoup(const Plateau3D& plateau) ;

    std::string getNom() const;
    Pion getCouleur() const ;

protected:
    std::string nom;
    Pion couleur;
};

#endif