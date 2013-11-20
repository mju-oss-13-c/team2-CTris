#include"players.h"
#include"grid.h"

#ifndef AI_H
#define AI_H

//restituisce la cella dove l'IA intende fare la prossima mossa
//Funzionamento:
//-da priorit� alle celle dove pu� creare un tris
//-se non ci sono tris da creare fornisce priorit� alle celle nelle quali � necessario bloccare un tris
//-se non ci sono celle dove pu� creare un tris, allora viene scelta una cella in maniera casuale, ma con probabilit� pesata:
//		 -----       /
//      |2|1|2|     /
//      |-|-|-|    /
//      |1|4|1|   /  16
//      |-|-|-|  /
//      |2|1|2| /
//       ----- /
//Ritorno:
//Ritorna TRUE o FALSE nel caso in cui l'operazione sia riuscita o meno. L'operazione non riesce nel caso in cui:
// 1) non ci sia pi� spazio per effettuare una mossa
// 2) qualcuno ha gi� vinto la partita
//L'operazione riesce in tutti gli altri casi
BOOL nextMoveAI(Grid grid, enum Players AISign, enum Cell *move);

#endif
