#ifndef PLATEAU3D_H
#define PLATEAU3D_H

#include <array>
#include <string>
#include <vector>
#include "Pion.hpp"

/**
 * @struct Vec3
 * @brief Représente une direction en 3 dimensions.
 */

struct Vec3 {
    int dx; ///< Direction selon l'axe x.
    int dy; ///< Direction selon l'axe y.
    int dz; ///< Direction selon l'axe z.
};

/**
 * @class Plateau3D
 * @brief Représente le plateau de jeu du Puissance 4 en 3D.
 *
 * Cette classe gère la grille, l'ajout et le retrait des pions,
 * ainsi que la vérification des coups et des victoires.
 */

class Plateau3D
{

public:
    /** * @brief Constructeur par défaut. */
    Plateau3D();
    /** * @brief Destructeur. */
    ~Plateau3D();
    /** * @brief Constructeur par copie. * @param other Plateau à copier. */
    Plateau3D(const Plateau3D &other);
    /** * @brief Opérateur d'affectation. * @param other Plateau à copier. * @return Référence vers le plateau courant. */
    Plateau3D& operator=(const Plateau3D &other);

    /** * @brief Vérifie si un coup est valide. * @param x Coordonnée en longueur. * @param y Coordonnée en largeur. * @return true si le coup est autorisé, false sinon. */
    bool est_coup_valide(int x, int y) const;

    /**
     * @brief Ajoute un pion sur le plateau.
    * @param longueur Coordonnée en longueur.
     * @param largeur Coordonnée en largeur.
     * @param p Pion à ajouter.
     * @return Hauteur du pion placé, ou -1 si le coup  est invalide.
    */
    int ajouter_pion(int longueur, int largeur, Pion p);
    /** * @brief Retire le dernier pion d'une colonne. * @param longueur Coordonnée en longueur. * @param largeur Coordonnée en largeur. * @return Hauteur du pion retiré. */
    int retirer_pion(int longueur, int largeur);

    /** * @brief Affiche le plateau dans la console. */
    void affiche();

    /** * @brief Vérifie si un joueur a gagné. * @param x Coordonnée en longueur. * @param y Coordonnée en largeur. * @param z Coordonnée en hauteur. * @param p Pion du joueur. * @return true si une victoire est détectée. */
    bool verifier_victoire(int x, int y, int z, Pion p) const;

    /// @return Largeur du plateau.
    int get_largeur()const;
    /// @return Longueur du plateau.
    int get_longueur()const;
    /// @return Nombre total de cases du plateau.
    int get_total_emplacements()const;

    /** * @brief Retourne l'ensemble des lignes gagnantes possibles. * @return Liste des lignes du plateau. */
    std::vector<std::vector<int>> lignes_possibles()const;
    /** * @brief Accède à un pion du plateau. * @return Pion présent à la position indiquée. */
    Pion get_pion(int hauteur, int largeur, int longueur) const ;
    /** * @brief Accède à un pion via son indice. * @param index Indice dans la grille. * @return Pion correspondant. */
    Pion get_pion(int index) const;

    /** * @brief Indique si la partie est terminée. * @return true si le plateau est dans un état final. */
    bool est_termine();

private:
    static constexpr int hauteur = 4;
    static constexpr int largeur = 4;
    static constexpr int longueur = 5;
    
    std::array<Pion, hauteur * largeur * longueur>      grille; ///< Grille du plateau.
    bool plateau_termine; ///< Indique si la partie est terminée.
    int nbr_pions_places; ///< Nombre de pions placés.


    static constexpr Vec3 directions[] = {
        {1,0,0}, {0,1,0}, {0,0,1},                // Axes
        {1,1,0}, {1,-1,0}, {1,0,1}, {1,0,-1}, {0,1,1}, {0,1,-1}, // Diagonales faces
        {1,1,1}, {1,1,-1}, {1,-1,1}, {1,-1,-1}    // Diagonales spatiales
    };

    std::vector<std::vector<int>> LIGNES_POSSIBLES;
    void initialiser_lignes();
    
    int index(int longueur, int largeur, int hauteur) const; 


    void def_pion(int hauteur, int largeur, int longueur, Pion p);

    int compter_pions_direction(int x, int y, int z, int dx, int dy, int dz, Pion p) const;
};

#endif