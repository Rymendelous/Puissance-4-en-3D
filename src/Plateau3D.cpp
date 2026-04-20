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

    for (int i=0; i<this->grille.size(); i++){
        this->grille[i]=other.grille[i];
    }
}

Plateau3D& Plateau3D::operator=(const Plateau3D &other){
    for (int i=0; i<this->grille.size(); i++){
        this->grille[i]=other.grille[i];
    }
}

int Plateau3D::index(int p_largeur, int p_longueur, int p_hauteur){
    int index=p_largeur + (p_longueur * Plateau3D::largeur) + (p_hauteur * Plateau3D::largeur * Plateau3D::longueur);

    if (index > (Plateau3D::largeur * Plateau3D::hauteur * Plateau3D::longueur)){
        std::cout<<"Erreur, out of range" <<std::endl;
        return 0;
    }

    return index;
}


Pion Plateau3D::get_pion(int p_largeur, int p_longueur, int p_hauteur){
    return this->grille[this-> index(p_largeur,p_longueur,p_hauteur)];
}
void Plateau3D::def_pion(int p_largeur, int p_longueur, int p_hauteur, Pion p){
    this->grille[this-> index(p_largeur,p_longueur,p_hauteur)]=p;
}

void Plateau3D::affiche(){
    for (int z = 0 ; z<this->hauteur ; z++){
        std::cout<<"Etage numero "<< z<< std::endl;
        for (int y = 0 ; y < this-> largeur; y++){
            for( int  x = 0 ; x < this->longueur; x++){
                std::cout <<toString(this->get_pion(y,x,z))<<" ";
            }
            std::cout <<std::endl;
        }
        std::cout<<std::endl;
    }

}
