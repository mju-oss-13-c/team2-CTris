#include"players.h"
#include"cell.h"

#ifndef GAMERESULT_H
#define GAMERESULT_H

struct GameResult
{
	enum Players winner;
	enum CellLine winningLine;
};

struct GameResult createGameResult();
void deleteGameResult(struct GameResult result);
struct GameResult copyGameResult(struct GameResult result);

void getGameResultState(struct GameResult result, enum Players *winner, enum CellLine *winningLine);
void setGameResultState(struct GameResult *result, enum Players winner, enum CellLine winningLine);
#endif