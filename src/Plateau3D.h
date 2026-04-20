#ifndef PLATEAU3D_H
#define PLATEAU3D_H

#include <array>
#include <string>
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

    

    void ajouter_pion(int largeur, int longueur, Pion p);

    void affiche();

    bool verifier_victoire(int x, int y, int z, Pion p) const;


private:
    static constexpr int hauteur = 4;
    static constexpr int largeur = 4;
    static constexpr int longueur = 5;
    
    std::array<Pion,hauteur*largeur*longueur> grille;


    static constexpr Vec3 directions[] = {
        {1,0,0}, {0,1,0}, {0,0,1},                // Axes
        {1,1,0}, {1,-1,0}, {1,0,1}, {1,0,-1}, {0,1,1}, {0,1,-1}, // Diagonales faces
        {1,1,1}, {1,1,-1}, {1,-1,1}, {1,-1,-1}    // Diagonales spatiales
    };
    
    int index(int hauteur, int largeur, int longueur) const;

    Pion get_pion(int hauteur, int largeur, int longueur) const ;
    void def_pion(int hauteur, int largeur, int longueur, Pion p);

    int compter_pions_direction(int x, int y, int z, int dx, int dy, int dz, Pion p) const;
};

#endif