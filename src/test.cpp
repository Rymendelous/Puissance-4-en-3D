#include <iostream>

#include "Pion.hpp"
#include "Plateau3D.h"

using namespace std;


int main(){
    Plateau3D plat;
    plat.affiche();

    plat.ajouter_pion(1,1,Pion::Blanc);
    plat.ajouter_pion(1,3,Pion::Blanc);
    plat.ajouter_pion(1,2,Pion::Blanc);
    plat.ajouter_pion(1,0,Pion::Noir);

    plat.affiche();

    cout<<"test : " <<plat.verifier_victoire(1,2,0,Pion::Blanc)<<endl;

}