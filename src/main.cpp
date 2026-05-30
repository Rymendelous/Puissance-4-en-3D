#include <iostream>
#include <cstdlib>
#include <ctime>
#include "mpi.h"

#include "Pion.hpp"
#include "Plateau3D.h"
#include "IA_MinMax.h"
#include "arbitre.h"
#include "JoueurMPI.h" 
#include "position.h"

/**
 * @file main.cpp
 * @brief Programme principal utilisant MPI.
 *
 * Ce fichier lance une partie entre deux IA MinMax
 * qui communiquent avec un arbitre grâce à MPI.
 */

using namespace std;

// Convertit les coordonnées (x, y) vers la classe position 
position versPosition(int x, int y) {
    return position('A' + y, x, 0); 
}

// Convertit la classe position du vers les coordonnées (x, y)
std::pair<int, int> versCoordonnees(position p) {
    return {p.getv(), p.geth() - 'A'};
}

// Signal de fin pour l'arbitre
position signalFin() { return position('Z', 9, 0); }
bool estSignalFin(position p) { return p.geth() == 'Z'; }

int main(int argc, char *argv[]) {
    MPI::Init(argc, argv);
    int rank = MPI::COMM_WORLD.Get_rank();

    // RANK 2 : L'ARBITRE
    if (rank == 2) {
        arbitre AB;
        bool joue = true;
        cout << "[Arbitre] Pret pour le match !" << endl;
        
        while (joue) {
            position p = AB.receiveCoup(0);
            AB.sendCoup(p, 1);
            if (estSignalFin(p)) break;

            p = AB.receiveCoup(1);
            AB.sendCoup(p, 0);
            if (estSignalFin(p)) break;
        }
        cout << "[Arbitre] Fermeture." << endl;
    }

    // RANK 0 : JOUEUR 1 (Les Blancs)
    if (rank == 0) {
        JoueurMPI J0(rank); 
        Plateau3D plateau;
        IA_MinMax ia("MinMax_Blanc", Pion::Blanc, 4); 
        
        while (true) {
            // Mon tour
            pair<int, int> monCoup = ia.choisirCoup(plateau);
            int monZ = plateau.ajouter_pion(monCoup.first, monCoup.second, ia.getCouleur());
            cout << "[Joueur 0] Joue en (" << monCoup.first << ", " << monCoup.second << ")" << endl;
            
            J0.sendCoup(versPosition(monCoup.first, monCoup.second), 2);
            
            if (plateau.verifier_victoire(monCoup.first, monCoup.second, monZ, ia.getCouleur()) || plateau.est_termine()) {
                J0.receiveCoup(2); 
                break;
            }

            // Tour adverse
            position p = J0.receiveCoup(2);
            if (estSignalFin(p)) break; 
            
            pair<int, int> coupAdv = versCoordonnees(p);
            int advZ = plateau.ajouter_pion(coupAdv.first, coupAdv.second, Pion::Noir);
            
            if (plateau.verifier_victoire(coupAdv.first, coupAdv.second, advZ, Pion::Noir) || plateau.est_termine()) {
                J0.sendCoup(signalFin(), 2); 
                break;
            }
        }
    }

    
    // RANK 1 : JOUEUR 2 (Les Noirs)
   
    if (rank == 1) {
        JoueurMPI J1(rank); 
        Plateau3D plateau;
        IA_MinMax ia("MinMax_Noir", Pion::Noir, 4);
        
        while (true) {
            // Tour adverse
            position p = J1.receiveCoup(2);
            if (estSignalFin(p)) break;
            
            pair<int, int> coupAdv = versCoordonnees(p);
            int advZ = plateau.ajouter_pion(coupAdv.first, coupAdv.second, Pion::Blanc);
            
            if (plateau.verifier_victoire(coupAdv.first, coupAdv.second, advZ, Pion::Blanc) || plateau.est_termine()) {
                J1.sendCoup(signalFin(), 2); 
                break;
            }

            // Mon tour
            pair<int, int> monCoup = ia.choisirCoup(plateau);
            int monZ = plateau.ajouter_pion(monCoup.first, monCoup.second, ia.getCouleur());
            cout << "[Joueur 1] Joue en (" << monCoup.first << ", " << monCoup.second << ")" << endl;
            
            J1.sendCoup(versPosition(monCoup.first, monCoup.second), 2);
            
            if (plateau.verifier_victoire(monCoup.first, monCoup.second, monZ, ia.getCouleur()) || plateau.est_termine()) {
                J1.receiveCoup(2);
                break;
            }
        }
    }

    MPI::Finalize();
    return 0;
}