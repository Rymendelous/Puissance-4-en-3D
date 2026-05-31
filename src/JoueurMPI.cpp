/*
 * joueur.cpp
 *
 *  Created on: 29 avr. 2026
 *      Author: dtromeur
 */

#include "JoueurMPI.h"

JoueurMPI::JoueurMPI(int color,Joueur* ia) {
	me = MPI::COMM_WORLD.Get_rank();
    this->color=color;
    this->monIA=ia;
}

JoueurMPI::~JoueurMPI() {
}

JoueurMPI::JoueurMPI(const JoueurMPI &o) {
    this->color=o.color;
    this->plateau=o.plateau;
    this->monIA=o.monIA;

}

JoueurMPI& JoueurMPI::operator=(const JoueurMPI &o) {
    if (this != &o){
        this->color=o.color;
        this->plateau=o.plateau;
        this->monIA=o.monIA;
    }
	return *this;
}
/*

bool JoueurMPI::jejoue(position p){
	int ii;
    ii = p.PositionNum();
int ier=MPI_Send(&ii,1, MPI::INT,(me+1)%2, 100,MPI::COMM_WORLD);
	return false;
}

position JoueurMPI::tujoues(){
	int ii;
	position p;
	MPI_Status status;
int ier=MPI_Recv(&ii,1, MPI::INT,(me+1)%2, 100,MPI::COMM_WORLD, &status);
     p.setalpha(p.alpha[ii/10]);
     p.setv(ii%10);
return p;
}

*/

position JoueurMPI::receiveCoup( int rank){
	int ii,ier;
	position p;
	MPI_Status status;
    ier=MPI_Recv(&ii,1, MPI::INT,rank, 100,MPI::COMM_WORLD, &status);
     p.seth(p.getalpha(ii/10));
     p.setv(ii%10);
     return p;
}

void JoueurMPI::sendCoup(position p, int rank){
	int ii;
    ii = p.positionNumMPI();
    int ier=MPI_Send(&ii,1, MPI::INT,rank, 100,MPI::COMM_WORLD);
}

void JoueurMPI::ecouterAdversaire(int rankArbitre) {
    position coupAdversaire = receiveCoup(rankArbitre);
    int codeMPI = coupAdversaire.positionNumMPI(); 
    int xAdverse = coupAdversaire.getalpha(coupAdversaire.h);
    int yAdverse = coupAdversaire.v;
    Pion couleurAdverse = (this->monIA->getCouleur() == Pion::Blanc) ? Pion::Noir : Pion::Blanc;
    plateau.ajouter_pion(xAdverse, yAdverse, couleurAdverse);
}

void JoueurMPI::calculerEtEnvoyer(int rankArbitre) {
    std::pair<int, int> monChoix = monIA->choisirCoup(plateau);
    plateau.ajouter_pion(monChoix.first, monChoix.second, monIA->getCouleur());
    
    position monCoupPourLArbitre;
    monCoupPourLArbitre.seth(monCoupPourLArbitre.getalpha(monChoix.first));
    monCoupPourLArbitre.setv(monChoix.second);
    sendCoup(monCoupPourLArbitre, rankArbitre);
}