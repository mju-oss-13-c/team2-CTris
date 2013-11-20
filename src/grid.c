#include<stdlib.h>
#include"grid.h"

// *interfaccia per il tipo Grid
Grid createGrid() //costruisce una nuova griglia
{
	Grid grid = (CellState**) malloc(sizeof(CellState*)*3);
	int i, j;
	for(i = 0; i < 3; i++)
	{
		grid[i] = (CellState*) malloc(sizeof(CellState)*3);
		for(j = 0; j < 3; j++)
			grid[i][j] = (CellState)noPlayer;
	}
	return grid;
}
void deleteGrid(Grid grid) //elimina una griglia deallocandone la memoria
{
	int i;
	for(i = 0; i < 3; i++)
		free(grid[i]);
	free(grid);
}
Grid copyGrid(Grid grid) //Fornisce la copia di una griglia
{
	Grid newGrid = createGrid();
	int i, j;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			newGrid[i][j] = grid[i][j];
	return newGrid;
}
// Restituisce il valore della cella selezionata all'interno di una griglia.
// Se gli indici passati sono errati, viene restituita una cella vuota
CellState getCell(Grid grid, enum Cell cell)
{
	return grid[(int)cell/3][(int)cell%3];
}
// Scrive il simbolo passato all'interno della cella selezionata in una griglia.
void setCell(Grid grid, enum Cell cell, CellState value)
{
	grid[(int)cell/3][(int)cell%3] = value;
}

//determina se la griglia è vuota
BOOL emptyGrid(Grid grid)
{
	int i, j;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			if(grid[i][j] != noPlayer)
				return FALSE;
	return TRUE;
}

//determina se la griglia è piena
BOOL fullGrid(Grid grid)
{
	int i, j;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			if(grid[i][j] == noPlayer)
				return FALSE;
	return TRUE;
}

//determina se un giocatore ha vinto nella griglia passata indicandone in caso anche la/e linea con cui ha vinto
//Ritorno: indica con TRUE che qualcuno ha vinto, con FALSE indica invece che nessuno ha vinto
//Parametri: grid - la griglia di gioco da cui leggere l'eventuale vincita
//           result - [out] identifica il risultato della griglia, indicando l'eventuale vincitore e la riga di vincita
BOOL won(Grid grid, struct GameResult *result)
{
	int i;

	if(result != NULL)
		setGameResultState(result, noPlayer, (enum CellLine)0);
	
	//controllo righe
	for(i = 0; i < 3; i++)
		if( getCell(grid, (enum Cell)(i*3    )) == getCell(grid, (enum Cell)(i*3 + 1)) && 
			getCell(grid, (enum Cell)(i*3 + 1)) == getCell(grid, (enum Cell)(i*3 + 2)) &&
			getCell(grid, (enum Cell)(i*3    )) != noPlayer)
		{
			if(result != NULL)
				setGameResultState(result, getCell(grid, (enum Cell)(i*3)), (enum CellLine)i);
			return TRUE;
		}

	//controllo colonne
	for(i = 0; i < 3; i++)
		if( getCell(grid, (enum Cell)(i  )) == getCell(grid, (enum Cell)(i+3)) && 
			getCell(grid, (enum Cell)(i+3)) == getCell(grid, (enum Cell)(i+6)) &&
			getCell(grid, (enum Cell)(i  )) != noPlayer)
		{
			if(result != NULL)
				setGameResultState(result, getCell(grid, (enum Cell)(i)), (enum CellLine)(i+3));
			return TRUE;
		}

	//controllo diagonale d0
	if(getCell(grid, cellA1) == getCell(grid, cellB2) &&
		getCell(grid, cellB2) == getCell(grid, cellC3) &&
		getCell(grid, cellA1) != noPlayer)
	{
		if(result != NULL)
			setGameResultState(result, getCell(grid, cellA1), d0);
		return TRUE;
	}

	//controllo diagonale d1
	if(getCell(grid, cellA3) == getCell(grid, cellB2) &&
		getCell(grid, cellB2) == getCell(grid, cellC1) &&
		getCell(grid, cellA3) != noPlayer)
	{
		if(result != NULL)
			setGameResultState(result, getCell(grid, cellA3), d1);
		return TRUE;
	}

	return FALSE;
}

void printGrid(Grid grid, enum Cell lastMove, int timeFromLastMove, int animTime, char** imageGrid)
{
	int i, j;
	
	for(i = 0; i < GRID_IMAGE_SIZE_H; i++)
	{
		if(i % 7 == 0)
		{
			char *line;
			switch(i)
			{
			case 0:	line = "/------+------+------\\"; break;
			case 21: line = "\\------+------+------/"; break;
			default: line = "+------+------+------+";
			}
			for(j = 0; j < GRID_IMAGE_SIZE_B; j++)
				imageGrid[i][j] = line[j];
		}
		else
		{
			for(j = 0; j < GRID_IMAGE_SIZE_B; j++)
				if(j % 7 == 0)
					imageGrid[i][j] = '|';
				else
				{
					int row = (i / 7), column = (j / 7);
					enum Cell currentCell = (enum Cell)(row*3+column);
					int limitTimeForDraw;
					char charToDraw;

					switch(getCell(grid, currentCell))
					{
					case noPlayer:
						imageGrid[i][j] = imageEmptyCell[(i-1)%7][(j-1)%7];
						break;
					case circle:
						if(currentCell != lastMove || animTime == 0 ||
							drawTimeCircleCell[(i-1)%7][(j-1)%7] <= totalDrawTimeCircleCell * timeFromLastMove / animTime)
							imageGrid[i][j] = imageCircleCell[(i-1)%7][(j-1)%7];
						else
							imageGrid[i][j] = ' ';
						break;
					case cross:
						if(currentCell != lastMove || animTime == 0 ||
							drawTimeCrossCell[(i-1)%7][(j-1)%7] <= totalDrawTimeCrossCell * timeFromLastMove / animTime)
							imageGrid[i][j] = imageCrossCell[(i-1)%7][(j-1)%7];
						else
							imageGrid[i][j] = ' ';
					}
				}
		}
	}
}
