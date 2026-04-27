#include "Plateau3D.h"
#include <iostream>
#include "Pion.hpp"

Plateau3D::Plateau3D()
{
    this->grille.fill(Pion::Vide);
}

Plateau3D::~Plateau3D()
{

}

Plateau3D::Plateau3D(const Plateau3D &other){

    this->grille = other.grille;
}

Plateau3D& Plateau3D::operator=(const Plateau3D &other){
    if (&other != this){
        this->grille=other.grille;
    }
    return *this;
}

int Plateau3D::index(int p_longueur, int p_largeur, int p_hauteur) const{
    int index=p_largeur + (p_longueur * largeur) + (p_hauteur * largeur * longueur);

    if (index > (largeur * hauteur * longueur)){
        std::cout<<"Erreur, out of range" <<std::endl;
        return 0;
    }

    return index;
}


Pion Plateau3D::get_pion(int p_longueur, int p_largeur, int p_hauteur)const{
    return this->grille[this-> index(p_longueur,p_largeur,p_hauteur)];
}
void Plateau3D::def_pion(int p_longueur, int p_largeur, int p_hauteur, Pion p){
    this->grille[this-> index(p_longueur,p_largeur,p_hauteur)]=p;
}

void Plateau3D::affiche(){
    for (int z = 0 ; z<this->hauteur ; z++){
        std::cout<<"Etage numero "<< z<< std::endl;
        std::cout<< "  ";
        for (int index_longueur=0 ; index_longueur <this->longueur; index_longueur++){
            std::cout<<index_longueur<<" ";
        }
        std::cout<<std::endl;

        for (int y = 0 ; y < this-> largeur; y++){
            std::cout<< y << " ";
            for( int  x = 0 ; x < this->longueur; x++){
                std::cout <<toString(this->get_pion(x,y,z))<<" ";
            }
            std::cout <<std::endl;
        }
        std::cout<<std::endl;
    }

}

bool Plateau3D::est_coup_valide(int x, int y) const {
    if (x < 0 || x >= largeur || y < 0 || y >= longueur) {
        return false;
    }

    return get_pion(x, y, hauteur - 1) == Pion::Vide;
}

int Plateau3D::ajouter_pion(int p_longueur, int p_largeur, Pion p){
    if (!this->est_coup_valide(p_longueur,p_largeur)){
        return -1;
    }

    for (int i =0 ; i < hauteur ; i++){
        if (this->get_pion(p_longueur,p_largeur,i)== Pion::Vide){
            this->def_pion(p_longueur,p_largeur,i,p);
            return i;
        }
    }
}

int Plateau3D::compter_pions_direction(int x, int y, int z, int dx, int dy, int dz, Pion p) const {
    int compte = 0;
    for (int i = 1; i < 4; ++i) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        int nz = z + i * dz;

        // 1. Vérifier si on sort du plateau (très important pour éviter un crash)
        if (nx < 0 || nx >= largeur || ny < 0 || ny >= longueur || nz < 0 || nz >= hauteur) {
            break; 
        }

        // 2. Vérifier si c'est la même couleur
        if ( this->get_pion(nx, ny, nz) == p) {
            compte++;
        } else {
            break; // On a trouvé un pion adverse ou du vide, on arrête de compter
        }
    }
    return compte;
}

bool Plateau3D::verifier_victoire(int x, int y, int z, Pion p) const{
    Vec3 d;
    for (int i=0 ; i<13; i++) {
        d=directions[i];
        int compte = 1;
        
        // On regarde dans un sens (ex: vers la droite/haut)
        compte += compter_pions_direction(x, y, z, d.dx, d.dy, d.dz, p);
        // On regarde dans l'autre sens (ex: vers la gauche/bas) avec le signe moins
        compte += compter_pions_direction(x, y, z, -d.dx, -d.dy, -d.dz, p);

        if (compte >= 4) return true;
    }
    return false;
}