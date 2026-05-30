#ifndef PION_HPP
#define PION_HPP

#include <string>

/**
 * @enum Pion
 * @brief Représente le contenu d'une case du plateau.
 */

enum class Pion {
    Vide,
    Blanc,
    Noir
};

/**
 * @brief Convertit un pion en chaîne de caractères.
 * @param p Pion à convertir.
 * @return "O" pour un pion blanc, "X" pour un pion noir, "." pour une case vide.
 */

inline std::string toString(Pion p){
    switch (p){
        case Pion::Blanc: return "O";
        case Pion::Noir : return "X";
        default : return ".";
    }
}

/**
 * @brief Retourne le pion de couleur opposée.
 * @param p Pion à inverser.
 * @return Pion::Noir si p est blanc, Pion::Blanc si p est noir, Pion::Vide sinon.
 */
 
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