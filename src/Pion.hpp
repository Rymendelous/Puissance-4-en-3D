#ifndef PION_HPP
#define PION_HPP

#include <string>

enum class Pion {
    Vide,
    Blanc,
    Noir
};

inline std::string toString(Pion p){
    switch (p){
        case Pion::Blanc: return "O";
        case Pion::Noir : return "X";
        default : return ".";
    }
}

inline Pion operator!(Pion p){
    switch (p)
    {
    case Pion::Blanc: return Pion::Noir;
    case Pion::Noir:  return Pion::Blanc;
    default:
        return Pion::Vide;
    }
}

#endif