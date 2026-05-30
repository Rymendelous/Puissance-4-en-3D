#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Pion.hpp"
#include "Plateau3D.h"
#include "JoueurHumain.h"
#include "IA_Aleatoire.h"
#include "Partie.h"
#include "IA_MinMax.h"

/**
 * @file test.cpp
 * @brief Fichier de test pour comparer les IA.
 *
 * Ce fichier permet de lancer plusieurs parties automatiquement
 * afin de comparer les performances des différentes IA.
 */
 
using namespace std;

void visualiserLignes(const Plateau3D& plateau) {
    const auto& lignes = plateau.lignes_possibles();
    std::cout << "--- VISUALISATION DES LIGNES POSSIBLES (" << lignes.size() << ") ---" << std::endl;

    for (size_t i = 0; i < lignes.size(); ++i) {
        std::cout << "Ligne n°" << i << " : ";
        for (int index : lignes[i]) {
            // On décompose l'index pour retrouver x, y, z
            // Attention : utilise bien tes propres constantes largeur/longueur ici
            int z = index / (4 * 5);
            int reste = index % (4 * 5);
            int y = reste / 4;
            int x = reste % 4;

            std::cout << "(" << x << "," << y << "," << z << ") [" << index << "]  ";
        }
        std::cout << std::endl;
    }
}


//commande K C sur mac pour commenter
//command K U pour decommenter
// int main(){
//     Plateau3D plat;
//     plat.affiche();


//     IA_MinMax  j1("IA minou",Pion::Blanc);
//     IA_MinMax  j2("IA bob 2",Pion::Noir);
    
//     Partie p(&j1,&j2);
//     p.lancer();
    

//    plat.ajouter_pion(2,1,Pion::Noir);
//    plat.ajouter_pion(2,2,Pion::Noir);
//    plat.ajouter_pion(2,3,Pion::Noir);
//
//
//    plat.affiche();
//    cout<<j1.evaluerPlateau(plat)<<endl;
//    pair<int,int> coup=j1.choisirCoup(plat);
//    
//    cout<<coup.first<<", "<<coup.second<<endl;
    

//}

//POUR TESTER IA BETE CONTRE IA FORTE PENDANT 10 PARTIES
int main(){
    int n = 10;
    srand(time(0));
    bool j1commence = rand() % 2;
    //test ia minmax avec l'ia bete pour voir si l'ia minmax gagne tout le temps


    IA_MinMax expert("MinMax_Expert", Pion::Blanc, 4); //profondeur 4 
    IA_Aleatoire bete("IA_Bete", Pion::Noir);

    int victoiresExpert = 0;
    int victoiresBete = 0;
    int matchsnuls = 0;
     cout<<"Partie IA aleatoire contre IAminmax profondeur 4 en cours"<<endl;
     for(int i=0; i<n; i++){
        cout << "Partie " << i+1 << " en cours..." << endl;
        Partie p(&expert, &bete);
        Joueur* gagnant = p.lancer_silencieux(j1commence);
        //on incrémente les compteurs 
        if(gagnant == &expert){
            victoiresExpert++;
        } 
        else if(gagnant == &bete){
            victoiresBete++;
        } 
        else{
            matchsnuls++;
        }
    }
    cout<<"résultat final sur les"<<n<<"parties:"<<endl;
    cout<< "Victoires de "<<expert.getNom()<< ": "<<victoiresExpert<<endl;
    cout<< "Victoires de "<<bete.getNom()<<": "<<victoiresBete<<endl;
    cout<< "Matchs nuls : "<<matchsnuls<<endl;

//POUR TESTER IA MINMAX CONTRE ELLE MEME AVEC PROFONDEURS DIFFERENTES PENDANT 10 PARTIES
   cout<<"Partie IAminmax profondeur 4 contre IAminmax profondeur 2 maintenant ..."<<endl;
    IA_MinMax expert1("MinMax_4", Pion::Blanc, 4);
    IA_MinMax expert2("MinMax_2", Pion::Noir, 2);

    int victoiresExpert1 = 0;
    int victoiresExpert2 = 0;
    matchsnuls = 0;

    for(int i=0;i<n;i++){
        cout << "Partie " << i+1 << " en cours..." << endl;
        //pour que ce soit pas biaisé je fais en sorte que c pas tout le temps la meme ia qui joue en premier
        Partie p(&expert1, &expert2);
        Joueur* gagnant= p.lancer_silencieux(j1commence);
        //pour alterner a chaque partie
        j1commence = !j1commence;

        if(gagnant == &expert1) victoiresExpert1++;
        else if(gagnant == &expert2) victoiresExpert2++;
        else matchsnuls++;
    }
    cout<<"résultat final sur les"<<n<<"parties:"<<endl;
    cout<<"Victoires de "<<expert1.getNom()<< ": "<<victoiresExpert1<<endl;
    cout<<"Victoires de "<<expert2.getNom()<<": "<<victoiresExpert2<<endl;
    cout<<"Matchs nuls : "<<matchsnuls<<endl;
}