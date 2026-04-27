#include "JoueurIA.h"
#include <string>
#include "Pion.hpp"
#include "Joueur.h"

using namespace std;

JoueurIA::JoueurIA(Pion couleur) : Joueur("Joueur IA",couleur){}


JoueurIA::JoueurIA( string nom , Pion couleur) : Joueur(nom,couleur){}

JoueurIA::~JoueurIA(){}

JoueurIA::JoueurIA( const JoueurIA & other): Joueur(other){}

JoueurIA & JoueurIA::operator=( const JoueurIA & other){
    if (this != &other){
        Joueur::operator=(other);
    }
    return (*this);
}
