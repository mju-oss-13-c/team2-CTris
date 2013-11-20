OBJECTS = AI.o gameHistory.o gameResult.o getInput.o grid.o integerManip.o main.o mainMenu.o playTris.o trisGame.o
OUTPUT_NAME = C-Tris.out

INCL_PLAYERS_H = players.h

INCL_INTEGERMANIP_H = integerManip.h
INCL_INTEGERMANIP_C = integerManip.c $(INCL_INTEGERMANIP_H)

INCL_CELL_H = cell.h $(INCL_PLAYERS_H)

INCL_GAMERESULT_H = gameResult.h $(INCL_PLAYERS_H) $(INCL_CELL_H)
INCL_GAMERESULT_C = gameResult.c $(INCL_GAMERESULT_H)

INCL_GRID_H = grid.h $(INCL_PLAYERS_H) $(INCL_CELL_H) $(INCL_GAMERESULT_H)
INCL_GRID_C = grid.c $(INCL_GRID_H)

INCL_AI_H = AI.h $(INCL_PLAYERS_H) $(INCL_GRID_H)
INCL_AI_C = AI.c $(INCL_AI_H)

INCL_GAMEHISTORY_H = gameHistory.h $(INCL_GAMERESULT_H)
INCL_GAMEHISTORY_C = gameHistory.c $(INCL_GAMEHISTORY_H) $(INCL_INTEGERMANIP_H)

INCL_GETINPUT_H = getInput.h $(INCL_CELL_H)
INCL_GETINPUT_C = getInput.c $(INCL_GETINPUT_H)

INCL_MAINMENU_H = mainMenu.h
INCL_MAINMENU_C = mainMenu.c $(INCL_MAINMENU_H) $(INCL_GRID_H) $(INCL_AI_H) $(INCL_GETINPUT_H)

INCL_PLAYTRIS_H = playTris.h $(INCL_PLAYERS_H)
INCL_PLAYTRIS_C = playTris.c $(INCL_PLAYTRIS_H) $(INCL_GRID_H) $(INCL_GETINPUT_H) $(INCL_GAMEHISTORY_H) $(INCL_AI_H) $(INCL_INTEGERMANIP_H)

INCL_TRISGAME_H = trisGame.h
INCL_TRISGAME_C = trisGame.c $(INCL_TRISGAME_H) $(INCL_MAINMENU_H) $(INCL_PLAYTRIS_H)

INCL_MAIN_C = main.c $(INCL_TRISGAME_H)

C-Tris.out: $(OBJECTS)
	cc -o $(OUTPUT_NAME) -lncurses $(OBJECTS)
AI.o: $(INCL_AI_C)
	cc -c AI.c
gameHistory.o: $(INCL_GAMEHISTORY_C)
	cc -c gameHistory.c
gameResult.o: $(INCL_GAMERESULT_C)
	cc -c gameResult.c
getInput.o: $(INCL_GETINPUT_C)
	cc -c getInput.c
grid.o: $(INCL_GRID_C)
	cc -c grid.c
integerManip.o: $(INCL_INTEGERMANIP_C)
	cc -c integerManip.c
main.o: $(INCL_MAIN_C)
	cc -c main.c
mainMenu.o: $(INCL_MAINMENU_C)
	cc -c mainMenu.c
playTris.o: $(INCL_PLAYTRIS_C)
	cc -c playTris.c
trisGame.o: $(INCL_TRISGAME_C)
	cc -c trisGame.c
clean:
	rm -f $(OUTPUT_NAME) $(OBJECTS)
