#include"gameResult.h"

struct GameResult createGameResult()
{
	struct GameResult result;
	result.winner = noPlayer;
	return result;
}
void deleteGameResult(struct GameResult result)
{
}
struct GameResult copyGameResult(struct GameResult result)
{
	struct GameResult newResult = createGameResult();
	newResult.winner = result.winner;
	newResult.winningLine = result.winningLine;
	return newResult;
}

void getGameResultState(struct GameResult result, enum Players *winner, enum CellLine *winningLine)
{
	*winner = result.winner;
	*winningLine = result.winningLine;
}
void setGameResultState(struct GameResult *result, enum Players winner, enum CellLine winningLine)
{
	result->winner = winner;
	result->winningLine = winningLine;
}