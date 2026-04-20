#ifndef PLATEAU3D_H
#define PLATEAU3D_H

#include <array>
#include <string>
#include "Pion.hpp"

class Plateau3D
{

public:

    Plateau3D();
    ~Plateau3D();
    Plateau3D(const Plateau3D &other);
    Plateau3D& operator=(const Plateau3D &other);

    int index(int hauteur, int largeur, int longueur);

    Pion get_pion(int hauteur, int largeur, int longueur);
    void def_pion(int hauteur, int largeur, int longueur, Pion p);

    void affiche();


private:
    static constexpr int hauteur = 4;
    static constexpr int largeur = 4;
    static constexpr int longueur = 5;
    
    std::array<Pion,hauteur*largeur*longueur> grille;
    
};

#endif