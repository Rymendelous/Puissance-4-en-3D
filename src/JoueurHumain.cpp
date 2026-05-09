#include "JoueurHumain.h"
#include "Joueur.h"
#include "Pion.hpp"
#include <string>
#include <iostream>

using namespace std;



JoueurHumain::JoueurHumain(string nom, Pion couleur) : Joueur(nom,couleur) {

}

JoueurHumain::~JoueurHumain()
{

}

JoueurHumain::JoueurHumain( const JoueurHumain & other) : Joueur(other) {

}

JoueurHumain & JoueurHumain::operator=( const JoueurHumain & other) {
    Joueur::operator=( other);
    return (*this);
}


std::pair<int, int> JoueurHumain::choisirCoup(const Plateau3D & plateau){
    int largeur,longueur;
    bool coup_invalide=true;
//boucle while pour forcer le joueur a donner un coup valide
    while (coup_invalide){
        cout<<this->nom<<" choisis un coup."<<endl;
        cout<<"index Colonne : ";
        cin>>longueur;
        cout<<"Index de ligne : ";
        
        cin>> largeur ; 
        cout<<endl;
        if (plateau.est_coup_valide(longueur,largeur)){
            coup_invalide=false;
        }
    }
    return pair<int,int>(largeur,longueur);
    
}