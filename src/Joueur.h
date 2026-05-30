#ifndef JOUEUR_H
#define JOUEUR_H

#pragma once

#include "Pion.hpp"
#include "Plateau3D.h"
#include <string>

/**
 * @class Joueur
 * @brief Classe abstraite représentant un joueur.
 *
 * Cette classe contient les informations communes à tous les joueurs,
 * comme le nom et la couleur du pion. Elle impose aussi la méthode
 * choisirCoup(), qui sera redéfinie par les classes filles.
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
     * @brief Demande au joueur de choisir un coup.
     * @param plateau Plateau de jeu.
     * @return Paire d'entiers représentant le coup choisi.
     */
    virtual std::pair<int, int> choisirCoup(const Plateau3D& plateau) =0 ;
    /**
     * @brief Retourne le nom du joueur.
     * @return Nom du joueur.
     */
    std::string getNom() const;

    /**
     * @brief Retourne la couleur du joueur.
     * @return Couleur du pion du joueur.
     */
    Pion getCouleur() const ;

protected:
    std::string nom; ///< Nom du joueur.
    Pion couleur;   ///< Couleur du pion du joueur.
};

#endif