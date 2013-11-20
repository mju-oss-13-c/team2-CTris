#include"players.h"

#ifndef CELL_H
#define CELL_H

#define CELL_IMAGE_SIZE_B 6
#define CELL_IMAGE_SIZE_H 6

enum Cell {cellA1 = 0, cellA2, cellA3,
           cellB1    , cellB2, cellB3,
           cellC1    , cellC2, cellC3};
enum CellLine { r0 = 0, r1,    r2,	//Definisce tutte le righe da 3 contenute in una griglia
				c0    , c1,    c2,	//righe: r0, r0, r0    colonne: c0, c1, c2    diagonale0: d0, . , .     diagonale1: . , . , d1
				d0    , d1};		//       r1, r1, r1             c0, c1, c2                . , d0, .                 . , d1, . 
									//       r2, r2, r2             c0, c1, c2                . , . , d0                d1, . , . 

typedef enum Players CellState; //definisce una cella con gli stati che essa può assumere

//definizione delle immagini che rappresentano i vari tipi di Cella
const static char imageCrossCell[CELL_IMAGE_SIZE_H][CELL_IMAGE_SIZE_B+1] = {"      ",
																			" \\  / ",
																			"  \\/  ",
																			"  /\\  ",
																			" /  \\ ",
																			"      "};
const static int drawTimeCrossCell[CELL_IMAGE_SIZE_H][CELL_IMAGE_SIZE_B] = {{0,0,0,0,0,0},
																			{0,1,0,0,8,0},
																			{0,0,2,7,0,0},
																			{0,0,6,3,0,0},
																			{0,5,0,0,4,0},
																			{0,0,0,0,0,0}};
const static int totalDrawTimeCrossCell = 8;
const static char imageCircleCell[CELL_IMAGE_SIZE_H][CELL_IMAGE_SIZE_B+1] = {"  __  ",
																			 " /  \\ ",
																			 "|    |",
																			 "|    |",
																			 " \\__/ ",
																			 "      "};
const static int drawTimeCircleCell[CELL_IMAGE_SIZE_H][CELL_IMAGE_SIZE_B] = {{0,0,12,11,0 ,0},
																			 {0,1,0 ,0 ,10,0},
																			 {2,0,0 ,0 ,0 ,9},
																			 {3,0,0 ,0 ,0 ,8},
																			 {0,4,5 ,6 ,7 ,0},
																			 {0,0,0 ,0 ,0 ,0}};
const static int totalDrawTimeCircleCell = 12;
const static char imageEmptyCell[CELL_IMAGE_SIZE_H][CELL_IMAGE_SIZE_B+1] = {"      ",
																			"      ",
																			"      ",
																			"      ",
																			"      ",
																			"      "};
const static int drawTimeEmptyCell[CELL_IMAGE_SIZE_H][CELL_IMAGE_SIZE_B] = {{0,0,0,0,0,0},
																			{0,0,0,0,0,0},
																			{0,0,0,0,0,0},
																			{0,0,0,0,0,0},
																			{0,0,0,0,0,0},
																			{0,0,0,0,0,0}};
const static int totalDrawTimeEmptyCell = 0;

#endif