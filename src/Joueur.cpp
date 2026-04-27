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
