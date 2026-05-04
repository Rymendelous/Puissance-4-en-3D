#ifndef JOUEUR_H
#define JOUEUR_H

#pragma once

#include "Pion.hpp"
#include "Plateau3D.h"
#include <string>

/**
 * @class JoueurHumain
 * @brief Représente un joueur humain.
 *
 * Cette classe permet au joueur de choisir ses coups au clavier.
 */

class Joueur
{
public:
    Joueur(std::string nom, Pion couleur);
    Joueur( Pion couleur);
    Joueur( const Joueur & other);
    Joueur & operator=( const Joueur & other);

    virtual ~Joueur();

    /**
     * @brief Demande au joueur humain de choisir un coup.
     * @param plateau Plateau de jeu.
     * @return Paire d'entiers représentant le coup choisi.
     */
    virtual std::pair<int, int> choisirCoup(const Plateau3D& plateau) =0 ;

    std::string getNom() const;
    Pion getCouleur() const ;

protected:
    std::string nom;
    Pion couleur;
};

#endif