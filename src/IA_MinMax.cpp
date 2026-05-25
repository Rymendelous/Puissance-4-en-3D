#include "IA_MinMax.h"
#include "JoueurIA.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;

IA_MinMax::IA_MinMax(std::string nom, Pion couleur,int ProfondeurEntree) : JoueurIA(nom,couleur)
{
this->profondeur = ProfondeurEntree;
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

//elle evalue sur une ligne 
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
    int scoreTotal = 0; 
    int menacesIA = 0; //nombre de lignes ou ya trois pions aligné chez l'ia ie je peux gagner
    int menacesAdv = 0; //nombre de lignes ou ya trois pions aligné chez ladversaire ie attention il va gagner 
    const std::vector<std::vector<int>>& lignes = plateau.lignes_possibles();

    for (int i = 0; i<(int)lignes.size(); i++){
        const std::vector<int>& ligne = lignes[i];

        int nbrIA = 0; //nombre de pions IA sur une ligne 
        int nbrAdv = 0; //nombre de pions de l'adversaire sur une ligne 

        for (int j = 0; j<(int)ligne.size();j++){
            int index = ligne[j];
            if (plateau.get_pion(index)==this->couleur){
                nbrIA++;
            }else if (plateau.get_pion(index)!=Pion::Vide){
                nbrAdv++;
            }
        }
        scoreTotal+=this->evaluer(nbrIA,nbrAdv);

        if (nbrIA==3 && nbrAdv==0) {
            menacesIA++;
        }
        if (nbrAdv==3 && nbrIA==0) {
            menacesAdv++;
        }
    }
    //en plus du score de base on le modifie selon qu'il ya deux lignes de trois pions chez l'ia ou ladversaire
    if (menacesIA>=2) {
        scoreTotal= scoreTotal+50000;  //l'ia a deux lignes avec 3pions j'augmente enormement son score pour l'ia comprenne qu'il faut mettre un pion a cet endroit
    }
    if (menacesAdv>=2) {
        scoreTotal= scoreTotal-80000; //score tres negatif pour ladversaire comme ça l'ia peut prevoir les coups a lavance pour pas etre dans ce cas
    }
    return scoreTotal;
}

int IA_MinMax::min_max(Plateau3D& plateau, int profondeur, int alpha, int beta, bool estMax) {

    // On ajoute un bonus pour gagner le plus vite possible (IA ne fait pas la diff entre gagner dans 1 coup ou dans 4 coups)
    if (profondeur == 0 or plateau.est_termine()) {
        int score = this->evaluerPlateau(plateau);
        if (score > 40000) return score +(profondeur *1000);
        if (score < 40000) return score - (profondeur *1000);
        return score;
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

//l'ia va choisir le plus gros score et risquer de laisser passer une opportunité de bloquer une ligne de 3 de l'adversaire
//donc en plus de l'utilisation de l'algo minmax je lui dis en parallele si tu vois que ya 3 pions adversaire aligné bloque les
//et si tu vois que toi l'ia tu peux immédiatement gagné en ajoutant un pion a une ligne de 3 pions fais le meme si ton algo minmax te dis
//que tu as un score très élevé à un autre endroit 
std::pair<int, int> IA_MinMax::choisirCoup(const Plateau3D& plateauActuel){
     // On fait une copie locale pour travailler
    Plateau3D plateauSimule = plateauActuel; 
    //je regarde si l'ia peut gagner directement 
    Pion couleurAdverse = (this->couleur == Pion::Blanc) ? Pion::Noir : Pion::Blanc;
    
    for (int x : ordreX) {
        for (int y : ordreY) {
            if (plateauSimule.est_coup_valide(x, y)) {
                int z = plateauSimule.ajouter_pion(x, y, this->couleur);
                if (plateauSimule.verifier_victoire(x, y, z, this->couleur)) {
                    return {x, y}; //je pose mon pion a cette emplacement
                }
                plateauSimule.retirer_pion(x, y);
            }
        }
    }

    //je bloque l'adversaire
    for (int x : ordreX) {
        for (int y : ordreY) {
            if (plateauSimule.est_coup_valide(x, y)) {
                int z = plateauSimule.ajouter_pion(x, y, couleurAdverse);
                if (plateauSimule.verifier_victoire(x, y, z, couleurAdverse)) {
                    plateauSimule.retirer_pion(x, y); 
                    return {x, y}; //je bloque ladversaire à cet emplacement 
                }
                plateauSimule.retirer_pion(x, y);
            }
        }
    }

    //maintenant que j'ai fais ces vérif je peux appeler minmax 
    int meilleurScore = -1000000;
    std::vector<std::pair<int, int>> meilleurCoup; //liste pour stocker les mêmes coups
    int alpha =-1000000;
    int beta = 1000000;

for (int x : ordreX) {
    for (int y : ordreY) {
            if (plateauSimule.est_coup_valide(x, y)) {
                plateauSimule.ajouter_pion(x, y, this->couleur);
                //on passe profondeur -1 car on vient de jouer un coup
                int score = this->min_max(plateauSimule, this->profondeur-1, alpha, beta, false); 
                
                if (score > meilleurScore) {
                    meilleurScore = score;
                    meilleurCoup.clear(); // on jette, on a trouvé mieux
                    meilleurCoup.push_back({x,y});
                }
                else if(score == meilleurScore){
                     meilleurCoup.push_back({x,y}); // on ajoute à la liste des similaires 
                }
                alpha = std::max(alpha,meilleurScore); // maj de alpha pour optimiser
            }
        }
    }

  //On tire un coup au sort parmi tous ceux qui ont obtenu le meilleur score
    if (!meilleurCoup.empty()) {
        int indexAleatoire = rand() % meilleurCoup.size();
        return meilleurCoup[indexAleatoire];
    }

    return {0, 0}; // au cas où le plateau est plein
}

