#include <iostream>

#include "Pion.hpp"
#include "Plateau3D.h"
#include "JoueurHumain.h"
#include "IA_Aleatoire.h"

using namespace std;


int main(){
    Plateau3D plat;
    plat.affiche();


    IA_Aleatoire j1("IAbob",Pion::Blanc);
    IA_Aleatoire j2("IAbob",Pion::Noir);
    pair<int,int> xy;
    int z;
    for (int i =0; i<20;i++) {
        xy=j1.choisirCoup(plat);
        z=plat.ajouter_pion(xy.first,xy.second,j1.getCouleur());
        plat.affiche();
        if (plat.verifier_victoire(xy.first,xy.second,z,j1.getCouleur()) ){
            cout<<"Joueur1 a gagné"<<endl;
            break;
        }
        xy=j2.choisirCoup(plat);
        z=plat.ajouter_pion(xy.first,xy.second,j2.getCouleur());
        plat.affiche();
        if (plat.verifier_victoire(xy.first,xy.second,z,j2.getCouleur()) ){
            cout<<"Joueur2 a gagné"<<endl;
            break;
        }
    }

}