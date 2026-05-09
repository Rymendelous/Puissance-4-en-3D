#include "IA_MinMax.h"
#include "JoueurIA.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

IA_MinMax::IA_MinMax(std::string nom, Pion couleur) : JoueurIA(nom,couleur)
{

}
IA_MinMax::IA_MinMax( Pion couleur) :JoueurIA("IA MinMax",couleur)
{

}

IA_MinMax::~IA_MinMax()
{

}

IA_MinMax::IA_MinMax( const IA_MinMax & other) : JoueurIA(other){

}

IA_MinMax & IA_MinMax::operator=( const IA_MinMax & other){
    if (this!= &other){
        JoueurIA::operator=(other);
    }
    return (*this);
}

int IA_MinMax::evaluer(int nbrIA,int nbrAdv) const {
    if (nbrIA == 4)  return 100000;
    if (nbrAdv == 4) return -100000;

    if (nbrIA == 3 and nbrAdv == 0) return 100;
    if (nbrAdv == 3 and nbrIA == 0) return -500; //je diminue encore plus le score de l'adversaire je trouve que -100 c'est pas assez 

    if (nbrIA == 2 and nbrAdv == 0) return 10;
    if (nbrAdv == 2 and nbrIA == 0) return -20; //pareil ici
    return 0;
}
void index(const std::vector<int>& lignes){
    for (int index : lignes) {
        // On décompose l'index pour retrouver x, y, z
        int z = index / (4 * 5);
        int reste = index % (4 * 5);
        int x = reste / 4;
        int y = reste % 4;

        std::cout << "(" << x << "," << y << "," << z << ") [" << index << "]  ";
    }
    std::cout << std::endl;
}

int IA_MinMax::evaluerPlateau(const Plateau3D& plateau){
    int score = 0;
    const std::vector<std::vector<int>>& lignes = plateau.lignes_possibles();

    for (int i = 0; i<(int)lignes.size(); i++){
        const std::vector<int>& ligne = lignes[i];
        int scoreIA(0),scoreAdv(0);
        for (int j = 0; j<(int)ligne.size();j++){
            int index = ligne[j];
            if (plateau.get_pion(index)==this->couleur){
                scoreIA++;
            }else if (plateau.get_pion(index)!=Pion::Vide){
                scoreAdv++;
            }
        }
        score+=this->evaluer(scoreIA,scoreAdv);
    }
    return score;
}

int IA_MinMax::min_max(Plateau3D& plateau, int profondeur, int alpha, int beta, bool estMax) {

    if (profondeur == 0 or plateau.est_termine()) {
        return this->evaluerPlateau(plateau);
    }

    if (estMax) { //cas ou l'ia joue
        int meilleurScore = -1000000;
        for (int x : ordreX) { //on commence par les cases du milieu au lieu de la case haut gauche
            for (int y : ordreY) { 
                if (plateau.est_coup_valide(x, y)) {
                    plateau.ajouter_pion(x, y, this->couleur);
                    int score = this->min_max(plateau,profondeur-1,alpha,beta, false);
                    plateau.retirer_pion(x, y);

                    meilleurScore = max(score,meilleurScore);
                    alpha = std::max(alpha,score);
                    if (beta<=alpha){break;}
                }
            }
            if(beta<=alpha) {break;}
        }
        return meilleurScore; 
    } 
    else { //cas ou ladversaire joue
        int pireScore = 1000000;
        for (int x : ordreX) { 
            for (int y : ordreY) { 
                if (plateau.est_coup_valide(x,y)) {
                    plateau.ajouter_pion(x,y,!this->couleur); 
                    int score = this->min_max(plateau,profondeur-1,alpha,beta,true);
                    plateau.retirer_pion(x,y);

                    pireScore = std::min(pireScore, score);
                    beta = std::min(beta,score);
                    if (beta <= alpha){break;}
                }
            }
            if(beta<=alpha) {break;}
        }
        return pireScore;
    }
}

std::pair<int, int> IA_MinMax::choisirCoup(const Plateau3D& plateauActuel){
    int meilleurScore = -1000000;
    std::pair<int, int> meilleurCoup = {0, 0};
    
    // On fait une copie locale pour travailler
    Plateau3D plateauSimule = plateauActuel; 

for (int x : ordreX) {
    for (int y : ordreY) {
            if (plateauSimule.est_coup_valide(x, y)) {
                plateauSimule.ajouter_pion(x, y, this->couleur);
                
                int score = this->min_max(plateauSimule, 6, -1000000, 1000000, false);
                
                if (score > meilleurScore) {
                    meilleurScore = score;
                    meilleurCoup = {x, y};
                }
                plateauSimule.retirer_pion(x, y);
            }
        }
    }
    return meilleurCoup;
}
