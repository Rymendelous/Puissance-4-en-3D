#include "Partie.h"
#include "IA_Aleatoire.h"
#include "Pion.hpp"
#include "Plateau3D.h"
#include <iostream>

Partie::Partie()
{
    this->J1=new IA_Aleatoire("Joueur 1",Pion::Blanc);
    this->J2=new IA_Aleatoire("Joueur 2",Pion::Noir);

}

Partie::Partie(Joueur* J1,Joueur* J2){
    this->J1 =J1;
    this->J2 = J2;
}

Partie::~Partie()
{

}

Partie::Partie( const Partie & other){
    this->J1= other.J1;
    this->J2 = other.J2;
    this->plateau = other.plateau;
}

Partie & Partie::operator=( const Partie & other){
    if (this!=&other){
        this->J1 = other.J1;
        this->J2 = other.J2;
        this->tours_joues= other.tours_joues;
        this->plateau=other.plateau;
    }
    return(*this);
}

bool Partie::victoire_tour(Joueur * j){
    std::cout << "\nC'est au tour de " << j->getNom() << " (" << (toString(j->getCouleur())) << ")" << std::endl;

    // 1. Demander le coup (Humain ou IA, c'est transparent ici)
    std::pair<int, int> xy = j->choisirCoup(this->plateau);

    // 2. Appliquer le coup
    int z = this->plateau.ajouter_pion(xy.first, xy.second, j->getCouleur());
    
    // On affiche le plateau pour voir ce qui s'est passé
    this->plateau.affiche(); 

    // 3. Vérifier la victoire
    return this->plateau.verifier_victoire(xy.first, xy.second, z, j->getCouleur());
}

void Partie::lancer() {
    bool gagne = false;
    int max_tours = this->plateau.get_total_emplacements();
    Joueur* joueurActuel = this->J1; // On commence par le J1
    
    this->plateau.affiche(); // Affichage initial (vide)  

    while (!gagne && this->tours_joues < max_tours) {
        // Exécuter le tour
        gagne = this->victoire_tour(joueurActuel);

        if (gagne) {
            std::cout << "FÉLICITATIONS ! " << joueurActuel->getNom() << " a gagné !" << std::endl;
        } else {
            // Alternance des joueurs
            joueurActuel = (joueurActuel == this->J1) ? this->J2 : this->J1;
            this->tours_joues++;
        }
    }

    if (!gagne) {
        std::cout << "Match nul ! Le plateau est plein." << std::endl;
    }
}

Joueur* Partie::lancer_silencieux(bool j1commence){
    bool gagne = false;
    int max_tours = this->plateau.get_total_emplacements(); 
    Joueur* joueurActuel = j1commence ? this->J1 : this->J2;

    while (gagne == false && this->tours_joues < max_tours) {
        
        std::pair<int, int> xy = joueurActuel->choisirCoup(this->plateau);
        int z = this->plateau.ajouter_pion(xy.first, xy.second, joueurActuel->getCouleur());
        gagne = this->plateau.verifier_victoire(xy.first, xy.second, z, joueurActuel->getCouleur());

        if (gagne == false) {
            if (joueurActuel == this->J1){
                joueurActuel = this->J2;
            }else{
                joueurActuel = this->J1;
            }
            this->tours_joues++;
        }
    }

    if (gagne == true) {
        return joueurActuel;
    } else {
        return nullptr;
    }
}