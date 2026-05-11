#include "Plateau3D.h"
#include <iostream>
#include "Pion.hpp"

Plateau3D::Plateau3D()
{
    this->grille.fill(Pion::Vide);
    this->initialiser_lignes();
}

Plateau3D::~Plateau3D()
{

}

Plateau3D::Plateau3D(const Plateau3D &other){

    this->grille = other.grille;
    this->LIGNES_POSSIBLES = other.LIGNES_POSSIBLES;
}

Plateau3D& Plateau3D::operator=(const Plateau3D &other){
    if (&other != this){
        this->grille=other.grille;
        this->LIGNES_POSSIBLES = other.LIGNES_POSSIBLES;
    }
    return *this;
}

int Plateau3D::index(int p_longueur, int p_largeur, int p_hauteur) const{
    int index=p_largeur + (p_longueur * largeur) + (p_hauteur * largeur * longueur);

    if (index > (largeur * hauteur * longueur)){
        std::cout<<"Erreur, out of range" <<std::endl;
        return 0;
    }

    return index;
}


Pion Plateau3D::get_pion(int p_longueur, int p_largeur, int p_hauteur)const{
    return this->grille[this-> index(p_longueur,p_largeur,p_hauteur)];
}

Pion Plateau3D::get_pion(int index)const{
    return this->grille[index];
}

void Plateau3D::def_pion(int p_longueur, int p_largeur, int p_hauteur, Pion p){
    this->grille[this-> index(p_longueur,p_largeur,p_hauteur)]=p;
}

void Plateau3D::affiche() {
    // 1. Afficher les titres des étages sur une seule ligne
    for (int z = 0; z < this->hauteur; z++) {
        std::cout << "- Etage " << z << " -     "; // Espacement entre étages
    }
    std::cout << std::endl;

    // 2. Afficher les indices des colonnes (X) pour chaque étage
    for (int z = 0; z < this->hauteur; z++) {
        std::cout << "  "; // Décalage pour l'indice Y
        for (int x = 0; x < this->longueur; x++) {
            std::cout << x << " ";
        }
        std::cout << "    "; // Espace entre les grilles
    }
    std::cout << std::endl;

    // 3. Afficher les lignes (Y)
    for (int y = 0; y < this->largeur; y++) {
        // Pour chaque ligne Y, on parcourt tous les étages Z
        for (int z = 0; z < this->hauteur; z++) {
            std::cout << y << " "; // Indice de ligne à gauche
            
            for (int x = 0; x < this->longueur; x++) {
                std::cout << toString(this->get_pion(x, y, z)) << " ";
            }
            std::cout << "    "; // Espace entre les grilles d'un même étage
        }
        std::cout << std::endl; // On passe à la ligne Y suivante pour tous les étages
    }
    std::cout << std::endl;
}

bool Plateau3D::est_coup_valide(int x, int y) const {
    if (x < 0 || x >= longueur || y < 0 || y >= largeur) {
        return false;
    }

    return get_pion(x, y, hauteur - 1) == Pion::Vide;
}


int Plateau3D::ajouter_pion(int p_longueur, int p_largeur, Pion p){
    if (!this->est_coup_valide(p_longueur,p_largeur)){
        return -1;
    }

    for (int i =0 ; i < hauteur ; i++){
        if (this->get_pion(p_longueur,p_largeur,i)== Pion::Vide){
            this->def_pion(p_longueur,p_largeur,i,p);
            
            this->nbr_pions_places++;
            if(this->verifier_victoire(p_longueur,p_largeur,i,p) or this->nbr_pions_places==this->get_total_emplacements()){
                this->plateau_termine = true;
            }

            return i;
        }
    }
    return -1;
}

int Plateau3D::compter_pions_direction(int x, int y, int z, int dx, int dy, int dz, Pion p) const {
    int compte = 0;
    for (int i = 1; i < 4; ++i) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        int nz = z + i * dz;

        // 1. Vérifier si on sort du plateau (très important pour éviter un crash)
        if (nx < 0 || nx >= longueur || ny < 0 || ny >= largeur || nz < 0 || nz >= hauteur) { //longueur et largeur avait été inversé c'est rectifier maintenant 
            break; 
        }

        // 2. Vérifier si c'est la même couleur
        if ( this->get_pion(nx, ny, nz) == p) {
            compte++;
        } else {
            break; // On a trouvé un pion adverse ou du vide, on arrête de compter
        }
    }
    return compte;
}

bool Plateau3D::verifier_victoire(int x, int y, int z, Pion p) const{
    Vec3 d;
    for (int i=0 ; i<13; i++) {
        d=directions[i];
        int compte = 1;
        
        // On regarde dans un sens (ex: vers la droite/haut)
        compte += compter_pions_direction(x, y, z, d.dx, d.dy, d.dz, p);
        // On regarde dans l'autre sens (ex: vers la gauche/bas) avec le signe moins
        compte += compter_pions_direction(x, y, z, -d.dx, -d.dy, -d.dz, p);

        if (compte >= 4) return true;
    }
    return false;
}

int Plateau3D::get_largeur()const{
    return this->largeur;
}

int Plateau3D::get_longueur()const{
    return this-> longueur;
}

int Plateau3D::get_total_emplacements()const{
    return (largeur*longueur*hauteur);
}

//RECTIFICATIONS POUR retirer_pion
//ici yavait un probleme le compteur nbr_pions_places n'était pas mis a jour
//pareil pour partie_termine() qui n'était pas mis a false 
//si l'ia joue donc appelle ajouter_pion et que verifier_victoire est vrai ça met plateau_termine à true
//maintenant l'ia veut retirer son pion donc on decremente le compteur mais si plateau_termine n'est pas mis a false
//dans la fonction minmax il sera donc a true et ça va directement arreter l'execution lalgo minmax ne sera meme pas executé
//donc j'ai bien mis a jour en mettant plateau_termine= false
int Plateau3D::retirer_pion(int p_longueur, int p_largeur){
    for(int i= hauteur-1;i>=0;i--){
        if (this->get_pion(p_longueur,p_largeur,i)!=Pion::Vide){
            this->def_pion(p_longueur,p_largeur,i,Pion::Vide);
            this->nbr_pions_places--;
            //si on enleve un pion necessairement le plateau n'est plus plein et donc la partie n'est pas terminé 
            this->plateau_termine= false;
            return i;
        }
    }
    return -1;
}

void Plateau3D::initialiser_lignes(){
    this->LIGNES_POSSIBLES.clear();
    Vec3 dir;
    for(int z = 0; z < hauteur; ++z){
        for (int y = 0; y < largeur; ++y){
            for (int x = 0; x < longueur; ++x){
                for (int i=0 ; i<13; i++) {
                    dir=directions[i];
                    int x4 = x + 3 * dir.dx;
                    int y4 = y + 3 * dir.dy;
                    int z4 = z + 3 * dir.dz;


                    if (x4 >= 0 and x4 < longueur and y4 >= 0 and y4 < largeur and z4 >= 0 and z4 < hauteur) {

                        std::vector<int> ligne;
                        for (int i = 0; i < 4; ++i) {
                            ligne.push_back(this->index(x+ i*dir.dx,dir.dy*i +y,z+i*dir.dz));
                            
                        }
                        LIGNES_POSSIBLES.push_back(ligne);

                    }
                }
            }

        }
    }
}

std::vector<std::vector<int>> Plateau3D::lignes_possibles()const{
    return this-> LIGNES_POSSIBLES;
}

bool Plateau3D::est_termine(){
    return this->plateau_termine;
}