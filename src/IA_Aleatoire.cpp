#include "IA_Aleatoire.h"
#include "JoueurIA.h"
#include <vector>
#include <random>

IA_Aleatoire::IA_Aleatoire(Pion couleur) : JoueurIA("IA_Aléatoire",couleur){
    std::random_device rd;
    this->moteur.seed(rd());
}

IA_Aleatoire::IA_Aleatoire(string nom,Pion couleur) : JoueurIA(nom,couleur){
    std::random_device rd;
    this->moteur.seed(rd());
}

IA_Aleatoire::~IA_Aleatoire(){}

IA_Aleatoire::IA_Aleatoire( const IA_Aleatoire & other):JoueurIA(other){
    std::random_device rd;
    this->moteur.seed(rd());
}

IA_Aleatoire & IA_Aleatoire::operator=( const IA_Aleatoire & other){
    if (this !=&other){
        JoueurIA::operator=(other);
        std::random_device rd;
        this->moteur.seed(rd());
    }
    return(*this);
}

std::pair<int, int> IA_Aleatoire::choisirCoup(const Plateau3D& plateau) {
    std::vector<std::pair<int, int>> coupsPossibles;

    // 1. On scanne le plateau pour voir ce qui est jouable maintenant
    for (int x = 0; x < plateau.get_largeur(); ++x) {
        for (int y = 0; y < plateau.get_largeur(); ++y) {
            if (plateau.est_coup_valide(x, y)) {
                coupsPossibles.push_back({x, y});
            }
        }
    }
    uniform_int_distribution<int> dist(0, coupsPossibles.size() - 1);

    // 2. Tirage aléatoire
    int index = dist(this->moteur);
    return coupsPossibles[index];
}