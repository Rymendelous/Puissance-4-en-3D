/*
 * arbitre.h
 *
 *  Created on: 30 avr. 2026
 *      Author: dtromeur
 */

#ifndef ARBITRE_H_
#define ARBITRE_H_
#include <list>
#include "position.h"
#include "mpi.h"
#include "Plateau3D.h"
#include "Pion.hpp"

class arbitre {
	std::list<position> partie;
	Plateau3D plateau; // l'arbitre possède la grille pour surveiller le match 
public:
	arbitre();
	virtual ~arbitre();
	arbitre(const arbitre &other);
	arbitre& operator=(const arbitre &other);

position receiveCoup( int rank);
/**
 * \fn receives the move from the player rank
 *    the move is given as a 2D position instance
 *    l not answered
 */
void sendCoup(position, int rank);
/**
  * \fn sends the move  to the player rank
  *    the move is given as a 2D position instance
  *    attribute l is not taken into account.
  */

// met a jour la grille de l'arbitre et verifie si le coup est gagnant
bool traiterCoup(position p, Pion couleurJoueur);

// pour afficher la grille dans le terminal
void afficherPlateau();

};

#endif /* ARBITRE_H_ */
