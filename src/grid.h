#include"players.h"
#include"cell.h"
#include"gameResult.h"

#ifndef BOOL
#define BOOL int
#define FALSE 0
#define TRUE 1
#endif

#ifndef GRID_H
#define GRID_H

#define GRID_IMAGE_SIZE_B 22
#define GRID_IMAGE_SIZE_H 22

// **definizione tipi**
typedef CellState** Grid;	// struttura a matrice 3x3 che rappresenta la griglia di gioco
								// Il primo indice indica la riga,
								// il secondo indice la colonna
								//
								// [0][0]  [0][1]  [0][2]
								// [1][0]  [1][1]  [1][2]
								// [2][0]  [2][1]  [2][2]

// **interfaccia**
Grid createGrid(); //Costruisce una nuova griglia
void deleteGrid(Grid grid); //Elimina una griglia deallocandone la memoria
Grid copyGrid(Grid grid); //Fornisce la copia di una griglia

CellState getCell(Grid grid, enum Cell cell);	//Restituisce il valore della cella selezionata all'interno di una griglia.
void setCell(Grid grid, enum Cell cell, CellState value); //Scrive il simbolo passato all'interno della cella selezionata in una griglia.

BOOL emptyGrid(Grid grid); //determina se la griglia è vuota
BOOL fullGrid(Grid grid); //determina se la griglia è piena

//determina se un giocatore ha vinto nella griglia passata indicandone in caso anche la/e linea con cui ha vinto
//Ritorno: indica con TRUE che qualcuno ha vinto, con FALSE indica invece che nessuno ha vinto
//Parametri: grid - la griglia di gioco da cui leggere l'eventuale vincita
//           result - [out] identifica il risultato della griglia, indicando l'eventuale vincitore e la riga di vincita
BOOL won(Grid grid, struct GameResult *result);

//restituisce un array di stringhe che compone la visualizzazione della griglia di gioco
//L'output quindi è una matrice 22*22 di caratteri simile a
//{ "/--------------------\",
//  "|      |  __  |      |",
//  "| \  / | /  \ | \  / |",
//  "|  \/  ||    ||  \/  |",
//  "|  /\  ||    ||  /\  |",
//  "| /  \ | \__/ | /  \ |",
//  "|      |      |      |",
//  "|------+------+------|",
//  "|      |  __  |  __  |",
//  "| \  / | /  \ | /  \ |",
//  "|  \/  ||    |||    ||",
//  "|  /\  ||    |||    ||",
//  "| /  \ | \__/ | \__/ |",
//  "|      |      |      |",
//  "|------+------+------|",
//  "|      |  __  |      |",
//  "| \  / | /  \ | \  / |",
//  "|  \/  ||    ||  \/  |",
//  "|  /\  ||    ||  /\  |",
//  "| /  \ | \__/ | /  \ |",
//  "|      |      |      |",
//  "\------+------+------/"
// La stringa passata deve necessariamente essere già della giusta dimensione
//}
void printGrid(Grid grid, enum Cell lastMove, int timeFromLastMove, int animTime, char** imageGrid);
#endif