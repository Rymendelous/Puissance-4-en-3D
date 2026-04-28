#include <iostream>

#include "Pion.hpp"
#include "Plateau3D.h"
#include "JoueurHumain.h"
#include "IA_Aleatoire.h"
#include "Partie.h"

using namespace std;


int main(){
    Plateau3D plat;
    plat.affiche();


    IA_Aleatoire  j1("IA bob",Pion::Blanc);
    IA_Aleatoire  j2("IA bob 2",Pion::Noir);
    
    Partie p(&j1,&j2);
    p.lancer();
    

}