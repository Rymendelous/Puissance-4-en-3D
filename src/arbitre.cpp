/*
 * arbitre.cpp
 *
 *  Created on: 30 avr. 2026
 *      Author: dtromeur
 */

#include "arbitre.h"

arbitre::arbitre() {

}

arbitre::~arbitre() {
}

arbitre::arbitre(const arbitre &o) {
this->partie=o.partie;
this->plateau = o.plateau;
}

arbitre& arbitre::operator=(const arbitre &o) {
	if (this != &o){
		this->partie=o.partie;
		this->plateau = o.plateau;
	}
	return (*this);

}


position arbitre::receiveCoup( int rank){
	int ii;
	position p;
	MPI_Status status;
int ier=MPI_Recv(&ii,1, MPI::INT,rank, 100,MPI::COMM_WORLD, &status);
     p.seth(p.getalpha(ii/10));
     p.setv(ii%10);
     return p;
}
void arbitre::sendCoup(position p, int rank){

	int ii;
    ii = p.positionNumMPI();
    int ier=MPI_Send(&ii,1, MPI::INT,rank, 100,MPI::COMM_WORLD);
}

bool arbitre::traiterCoup(position p, Pion couleurJoueur) {
    // On décode la position envoyée par MPI pour retrouver X et Y
    int codeMPI = p.positionNumMPI();
    int x = codeMPI / 10;
    int y = codeMPI % 10;

    //  On ajoute le pion dans la grille officielle de l'arbitre
    int z = plateau.ajouter_pion(x, y, couleurJoueur);

    // On enregistre le coup dans l'historique de la partie
    partie.push_back(p);

    // On vérifie s'il y a un gagnant avec ce coup 
    if (z != -1 && plateau.verifier_victoire(x, y, z, couleurJoueur)) {
        std::cout << "\n=========================================" << std::endl;
        std::cout << " VICTOIRE DU JOUEUR " << toString(couleurJoueur) << " !" << std::endl;
        std::cout << "=========================================\n" << std::endl;
        return true; // La partie est terminée
    }

    // On vérifie si la grille est totalement pleine (Match Nul)
    if (plateau.est_termine()) {
        std::cout << "\n=========================================" << std::endl;
        std::cout << " MATCH NUL " << std::endl;
        std::cout << "=========================================\n" << std::endl;
        return true; // La partie est terminée
    }

    return false; // La partie continue
}

void arbitre::afficherPlateau(){
	plateau.affiche();
}