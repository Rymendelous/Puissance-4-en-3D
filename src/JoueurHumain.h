#ifndef JOUEURHUMAIN_H
#define JOUEURHUMAIN_H

#pragma once

#include "Joueur.h"
#include "Pion.hpp"
#include <string>
using namespace std;

/**
 * @class JoueurHumain
 * @brief Représente un joueur humain.
 *
 * Cette classe permet à un utilisateur de choisir ses coups au clavier.
 */
class JoueurHumain :public Joueur 
{
public:
    /**
     * @brief Constructeur avec nom et couleur.
     * @param nom Nom du joueur.
     * @param couleur Couleur du pion du joueur.
     */
    JoueurHumain(string nom, Pion couleur);

    /**
     * @brief Constructeur par copie.
     * @param other JoueurHumain à copier.
     */
    JoueurHumain( const JoueurHumain & other);

    /**
     * @brief Destructeur.
     */
    ~JoueurHumain();

    /**
     * @brief Opérateur d'affectation.
     * @param other JoueurHumain à copier.
     * @return Référence vers le joueur humain courant.
     */
    JoueurHumain & operator=( const JoueurHumain & other);

    /**
     * @brief Demande au joueur humain de choisir un coup.
     * @param plateau Plateau de jeu.
     * @return Paire d'entiers représentant le coup choisi.
     */
    std::pair<int, int> choisirCoup(const Plateau3D& plateau);

protected:

};

#endif