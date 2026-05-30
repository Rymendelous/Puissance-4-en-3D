#ifndef IA_MINMAX_H
#define IA_MINMAX_H

#pragma once
#include <string>
#include "Pion.hpp"
#include "JoueurIA.h"

/**
 * @class IA_MinMax
 * @brief Intelligence artificielle utilisant l'algorithme MinMax.
 *
 * Cette IA évalue les coups possibles sur le plateau afin de choisir
 * le coup ayant le meilleur score. Elle utilise aussi l'élagage alpha-bêta
 * pour limiter le nombre de situations à explorer.
 */
class IA_MinMax : public JoueurIA
{
public:
    /**
     * @brief Constructeur avec nom, couleur et profondeur.
     * @param nom Nom de l'IA.
     * @param couleur Couleur du pion de l'IA.
     * @param ProfondeurEntree Profondeur de recherche de l'algorithme.
     */
    IA_MinMax(std::string nom, Pion couleur,int ProfondeurEntree);

    /**
     * @brief Constructeur avec couleur.
     * @param couleur Couleur du pion de l'IA.
     */
    IA_MinMax( Pion couleur);

    /**
     * @brief Constructeur par copie.
     * @param other IA_MinMax à copier.
     */
    IA_MinMax( const IA_MinMax & other);

    /**
     * @brief Destructeur.
     */
    ~IA_MinMax();

    /**
     * @brief Opérateur d'affectation.
     * @param other IA_MinMax à copier.
     * @return Référence vers l'IA courante.
     */
    IA_MinMax & operator=( const IA_MinMax & other);

    /**
     * @brief Choisit le meilleur coup selon l'algorithme MinMax.
     * @param plateau Plateau de jeu.
     * @return Paire d'entiers représentant le coup choisi.
     */
    std::pair<int, int> choisirCoup(const Plateau3D& plateau);

    /**
     * @brief Évalue l'état global du plateau.
     * @param plateau Plateau à évaluer.
     * @return Score associé au plateau.
     */
    int evaluerPlateau(const Plateau3D& plateau);

    /**
     * @brief Évalue une ligne de quatre cases.
     * @param nbrPions Nombre de pions de l'IA.
     * @param Pions_adverse Nombre de pions adverses.
     * @return Score de la ligne.
     */
    int evaluer(int nbrPions,int Pions_adverse)const;

    /**
     * @brief Applique l'algorithme MinMax avec élagage alpha-bêta.
     * @param plateau Plateau simulé.
     * @param profondeur Profondeur restante.
     * @param alpha Meilleur score déjà trouvé pour le joueur maximisant.
     * @param beta Meilleur score déjà trouvé pour le joueur minimisant.
     * @param estMax Indique si le tour simulé est celui de l'IA.
     * @return Score du meilleur coup trouvé.
     */
    int min_max(Plateau3D& plateau, int profondeur,int alpha, int beta, bool estMax);

protected:
static constexpr int ordreX[] = {2, 1, 3, 0, 4}; // je priorise les lignes aux centre et je met dans une liste à la main
static constexpr int ordreY[] = {1, 2, 0, 3};    // je priorise les colonnes au centre et je met dans une liste à la main
int profondeur; ///< Profondeur de recherche de l'algorithme.


};

#endif