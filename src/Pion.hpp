#ifndef PION_HPP
#define PION_HPP

#include <string>

enum class Pion {
    Vide,
    Blanc,
    Noir
};

std::string toString(Pion p){
    switch (p){
        case Pion::Blanc: return "O";
        case Pion::Noir : return "X";
        default : return ".";
    }
}

#endif