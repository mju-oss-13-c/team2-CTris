#ifndef BOOL
#define BOOL int
#define FALSE 0
#define TRUE 1
#endif

#ifndef MAINMENUMODE_H
#define MAINMENUMODE_H

/* Inizializza il menu iniziale
 * consoleB: il numero di colonne disponibili nella console
 * consoleH: il numero di righe disponibili nella console
 * prevScreen: il buffer video che rappresenta la schermata precedente da congelare
 * skipIntro: indica se si vuole o meno saltare l'animazione introduttiva
 *
 * Nota: L'animazione di scorrimento si può ottenere soltanto se non si visualizza l'animazione introduttiva.
 * E' possibile evitare comunque di visualizzarla impostando prevScreen a 0. Se si decide di visualizzarla
 * è necessario che prevScreen sia un array di caratteri lungo almeno VIDEOBUFFER_SIZE.
 */
void mainMenuInitialize(int consoleB, int consoleH, char *prevScreen, BOOL skipIntro);
/* Distrugge il menu principale liberando la memoria occupata
 */
void mainMenuDestroy();

/* Si occupa di aggiornare la logica del menu e di ricevere gli input del giocatore.
 * deltaT: lasso di tempo trascorso dall'ultima chiamata
 * Ritorno: int che indica il comando da intraprendere secondo la seguente tabella
 *			-1: esci
 *			0: non eseguire nulla
 *			1: partita single player
 *			2: partita multi player
 */
int mainMenuUpdate(int deltaT);
/* Si occupa di aggiornare la schermata ad ogni ciclo di gioco.
 * videoBuffer: parametro di output. Contiene la schermata da stampare
 *
 * La stringa passata dovrà essere lunga necessariamente almeno VIDEOBUFFER_SIZE
 */
void mainMenuDraw(char *videoBuffer);

#endif
