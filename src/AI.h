#include"players.h"
#include"grid.h"

#ifndef AI_H
#define AI_H

//restituisce la cella dove l'IA intende fare la prossima mossa
//Funzionamento:
//-da priorità alle celle dove può creare un tris
//-se non ci sono tris da creare fornisce priorità alle celle nelle quali è necessario bloccare un tris
//-se non ci sono celle dove può creare un tris, allora viene scelta una cella in maniera casuale, ma con probabilità pesata:
//		 -----       /
//      |2|1|2|     /
//      |-|-|-|    /
//      |1|4|1|   /  16
//      |-|-|-|  /
//      |2|1|2| /
//       ----- /
//Ritorno:
//Ritorna TRUE o FALSE nel caso in cui l'operazione sia riuscita o meno. L'operazione non riesce nel caso in cui:
// 1) non ci sia più spazio per effettuare una mossa
// 2) qualcuno ha già vinto la partita
//L'operazione riesce in tutti gli altri casi
BOOL nextMoveAI(Grid grid, enum Players AISign, enum Cell *move);

#endif
