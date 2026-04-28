#ifndef PLATEAU3D_H
#define PLATEAU3D_H

#include <array>
#include <string>
#include <vector>
#include "Pion.hpp"

struct Vec3 {
    int dx, dy, dz;
};

class Plateau3D
{

public:

    Plateau3D();
    ~Plateau3D();
    Plateau3D(const Plateau3D &other);
    Plateau3D& operator=(const Plateau3D &other);

    bool est_coup_valide(int x, int y) const;

    int ajouter_pion(int longueur, int largeur, Pion p);
    int retirer_pion(int longueur, int largeur);

    void affiche();

    bool verifier_victoire(int x, int y, int z, Pion p) const;

    int get_largeur()const;
    int get_longueur()const;
    int get_total_emplacements()const;

    std::vector<std::vector<int>> lignes_possibles()const;
    Pion get_pion(int hauteur, int largeur, int longueur) const ;
    Pion get_pion(int index) const;

    bool est_termine();

private:
    static constexpr int hauteur = 4;
    static constexpr int largeur = 4;
    static constexpr int longueur = 5;
    
    std::array<Pion,hauteur*largeur*longueur> grille;
    bool plateau_termine; //partie finie, plateau complet
    int nbr_pions_places;


    static constexpr Vec3 directions[] = {
        {1,0,0}, {0,1,0}, {0,0,1},                // Axes
        {1,1,0}, {1,-1,0}, {1,0,1}, {1,0,-1}, {0,1,1}, {0,1,-1}, // Diagonales faces
        {1,1,1}, {1,1,-1}, {1,-1,1}, {1,-1,-1}    // Diagonales spatiales
    };

    std::vector<std::vector<int>> LIGNES_POSSIBLES;
    void initialiser_lignes();
    
    int index(int hauteur, int largeur, int longueur) const;


    void def_pion(int hauteur, int largeur, int longueur, Pion p);

    int compter_pions_direction(int x, int y, int z, int dx, int dy, int dz, Pion p) const;
};

#endif