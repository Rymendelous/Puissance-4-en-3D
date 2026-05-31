/*
 ============================================================================
 Name        : TestJeu.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */
#include <math.h> 
#include <iostream>
#include "mpi.h" 
#include "arbitre.h"
#include "JoueurMPI.h"
#include "IA_MinMax.h"
#include "Pion.hpp"
using namespace std;
 
/**
 * @file TestJeu.cpp
 * @brief Ancien fichier de test pour les communications MPI.
 */
 
int main(int argc, char *argv[]) {
	int rank, size;
	MPI::Init(argc, argv);
	size = MPI::COMM_WORLD.Get_size();
	rank = MPI::COMM_WORLD.Get_rank();

if (rank == 2) {
        // arbitre
        arbitre AB;
        bool partieTerminee = false;
        int tour = 0;

        while (!partieTerminee) {
            int rankJoueurCourant = (tour % 2 == 0) ? 0 : 1;
            int rankAdversaire = (tour % 2 == 0) ? 1 : 0;
            Pion couleurCourante = (tour % 2 == 0) ? Pion::Blanc : Pion::Noir;

            // L'arbitre attend le coup
            position p = AB.receiveCoup(rankJoueurCourant);

            // Il traite le coup (mise a jour grille + check victoire)
            partieTerminee = AB.traiterCoup(p, couleurCourante);
            AB.afficherPlateau();

            // Transmet le coup a l'adversaire (si le match continue)
            if (!partieTerminee) {
                AB.sendCoup(p, rankAdversaire);
            }
            tour++;
        }
    }
    else {
        // joueur
        Pion maCouleur = (rank == 0) ? Pion::Blanc : Pion::Noir;
        
        // On instancie ton IA avec une profondeur de 3
        IA_MinMax monIA("IA_MinMax", maCouleur, 3);
        JoueurMPI monJoueurReseau(rank, &monIA);

        bool premierTour = true;

        
        while (true) {
            if (rank == 0 && premierTour) {
                // Le Joueur 0 (Blanc) commence directement sans ecouter
                monJoueurReseau.calculerEtEnvoyer(2);
                premierTour = false;
            } else {
                // Les autres tours : on ecoute le coup de l'adversaire d'abord, puis on joue
                monJoueurReseau.ecouterAdversaire(2);
                monJoueurReseau.calculerEtEnvoyer(2);
                premierTour = false;
            }
        }
    }

    MPI::Finalize();
    return 0;
}

