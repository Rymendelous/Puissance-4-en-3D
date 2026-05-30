#ifndef JOUEURIA_H
#define JOUEURIA_H

#pragma once

#include "Joueur.h"
#include "Plateau3D.h"
#include "Pion.hpp"
#include <string>

using namespace std;

/**
 * @class JoueurIA
 * @brief Représente un joueur contrôlé par une intelligence artificielle.
 *
 * Cette classe sert de base aux différentes IA du projet,
 * comme l'IA aléatoire ou l'IA MinMax.
 */

class JoueurIA : public Joueur
{
public:
    /**
     * @brief Constructeur avec couleur.
     * @param couleur Couleur du pion de l'IA.
     */
    JoueurIA(Pion couleur );

    /**
     * @brief Constructeur avec nom et couleur.
     * @param nom Nom de l'IA.
     * @param couleur Couleur du pion de l'IA.
     */
    JoueurIA( string nom , Pion couleur);

    /**
     * @brief Constructeur par copie.
     * @param other JoueurIA à copier.
     */
    JoueurIA( const JoueurIA & other);

    /**
     * @brief Destructeur.
     */
    ~JoueurIA();

    /**
     * @brief Opérateur d'affectation.
     * @param other JoueurIA à copier.
     * @return Référence vers l'IA courante.
     */
    JoueurIA & operator=( const JoueurIA & other);

protected:

};

#endif