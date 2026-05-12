#ifndef PARTIE_H
#define PARTIE_H

#pragma once
#include "Joueur.h"
#include "Plateau3D.h"

/**
 * @class Partie
 * @brief Gère le déroulement d'une partie de Puissance 4.
 *
 * La classe Partie est responsable de :
 * - la gestion des joueurs
 * - le suivi du plateau de jeu
 * - l’alternance des tours
 * - la détection de fin de partie
 */
class Partie
{
public:
    /**
     * @brief Constructeur par défaut.
     */
    Partie();

    /**
     * @brief Constructeur avec deux joueurs.
     * @param J1 Premier joueur.
     * @param J2 Deuxième joueur.
     */
    Partie(Joueur* J1, Joueur* J2);

    /**
     * @brief Constructeur par copie.
     * @param other Partie à copier.
     */
    Partie(const Partie & other);

    /**
     * @brief Destructeur.
     */
    ~Partie();

    /**
     * @brief Opérateur égal.
     * @param other Partie à copier.
     * @return Référence vers la partie courante.
     */
    Partie & operator=(const Partie & other);

    /**
     * @brief Joue le tour d'un joueur et vérifie s'il gagne.
     *
     * Le joueur choisit un coup, celui-ci est joué sur le plateau,
     * puis la fonction vérifie si ce coup provoque une victoire.
     *
     * @param j Pointeur vers le joueur qui joue le tour.
     * @return true si le joueur gagne après son coup, false sinon.
     */
    bool victoire_tour(Joueur *j);

    /**
     * @brief Lance le déroulement complet de la partie.
     *
     * Cette méthode alterne les tours entre les deux joueurs
     * jusqu'à ce qu'un joueur gagne ou que la partie se termine.
     */
    void lancer();
    Joueur* lancer_silencieux(bool j1commence);
    const Plateau3D& getPlateau() const{
        return this->plateau;
        }

protected:
    Joueur* J1;          ///< Premier joueur.
    Joueur* J2;          ///< Deuxième joueur.
    Plateau3D plateau;   ///< Plateau de jeu.
    int tours_joues = 0; ///< Nombre de tours joués.
};

#endif