#include "Joueur.h"
#include "Pion.hpp"
#include <string>
using namespace std;


Joueur::Joueur(string nom, Pion couleur)
{
    this->nom = nom;
    this->couleur= couleur;
}

Joueur::~Joueur()
{

}

std::string Joueur::getNom() const{
    return this-> nom;
}

Pion Joueur::getCouleur() const {
    return this->couleur;
}

Joueur::Joueur( const Joueur & other){
    this->couleur=other.couleur;
    this->nom=other.nom;
}


Joueur & Joueur::operator=( const Joueur & other){
    if( this != &other){
    this->couleur= other.couleur;
    this->nom= other.nom;
    }
    return (*this);
}
