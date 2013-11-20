#ifndef BOOL
#define BOOL int
#define FALSE 0
#define TRUE 1
#endif

#ifndef TRISGAME_H
#define TRISGAME_H

/* Inizializza l'ambiente di gioco. Va chiamato una volta all'appertura dell'applicazione
 * consoleB: il numero di colonne della console
 * consoleH: il numero di righe della console
 * consoleHandle: (solo Windows) l'handle riferente alla console attuale
 */
void initializeTrisGame(int consoleB, int consoleH, void *consoleHandle);
/* Distrugge l'ambiente di gioco liberando la memoria occupata
 */
void destroyTrisGame();

/* Si occupa di aggiornare la logica di gioco e di ricevere gli input del giocatore.
 * deltaT: il numero di millisecondi trascorsi dall'ultimo frame
 * Ritorno: TRUE se ordina di uscire dall'applicazione, FALSE altrimenti
 */
BOOL updateTrisGame(int deltaT);
/* Si occupa di aggiornare la schermata ad ogni ciclo di gioco
 */
void drawTrisGame();

#endif