#ifndef IA_ALEATOIRE_H
#define IA_ALEATOIRE_H

#pragma once
#include "JoueurIA.h"
#include "Pion.hpp"
#include <string>
#include <random>

using namespace std;

/**
 * @class IA_Aleatoire
 * @brief Intelligence artificielle qui choisit ses coups aléatoirement.
 *
 * Cette classe parcourt les coups possibles sur le plateau,
 * puis en sélectionne un au hasard.
 */
class IA_Aleatoire : public JoueurIA
{
public:
    /**
     * @brief Constructeur avec couleur.
     * @param couleur Couleur du pion de l'IA.
     */
    IA_Aleatoire(Pion couleur);

    /**
     * @brief Constructeur avec nom et couleur.
     * @param nom Nom de l'IA.
     * @param couleur Couleur du pion de l'IA.
     */
    IA_Aleatoire(string nom, Pion couleur);

    /**
     * @brief Constructeur par copie.
     * @param other IA_Aleatoire à copier.
     */
    IA_Aleatoire( const IA_Aleatoire & other);
    
    /**
     * @brief Destructeur.
     */
    ~IA_Aleatoire();
    /**
     * @brief Opérateur d'affectation.
     * @param other IA_Aleatoire à copier.
     * @return Référence vers l'IA courante.
     */
    IA_Aleatoire & operator=( const IA_Aleatoire & other);

    /**
     * @brief Choisit un coup valide au hasard.
     * @param plateau Plateau de jeu.
     * @return Paire d'entiers représentant le coup choisi.
     */
    std::pair<int, int> choisirCoup(const Plateau3D& plateau);

protected:
    mt19937 moteur; ///< Générateur de nombres aléatoires.

};

#endif