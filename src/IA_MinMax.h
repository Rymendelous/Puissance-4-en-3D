#ifndef IA_MINMAX_H
#define IA_MINMAX_H

#pragma once
#include <string>
#include "Pion.hpp"
#include "JoueurIA.h"

class IA_MinMax : public JoueurIA
{
public:
    IA_MinMax(std::string nom, Pion couleur);
    IA_MinMax( Pion couleur);
    IA_MinMax( const IA_MinMax & other);
    ~IA_MinMax();
    IA_MinMax & operator=( const IA_MinMax & other);

    std::pair<int, int> choisirCoup(const Plateau3D& plateau);

    int evaluerPlateau(const Plateau3D& plateau);

    int evaluer(int nbrPions,int Pions_adverse)const;

    int min_max(Plateau3D& plateau, int profondeur, bool estMax);

protected:

};

#endif