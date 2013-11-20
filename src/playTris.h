#include"players.h"

#ifndef PLAYTRIS_H
#define PLAYTRIS_H

enum GameMode {local, network};

/* Inizializza l'ambiente di gioco
 * consoleB: il numero di colonne disponibili nella console
 * consoleH: il numero di righe disponibili nella console
 * prevScreen: il buffer video che rappresenta la schermata precedente da congelare
 * cameMode: determina il tipo di gioco da effettuare, se locale o in rete (solo locale disponibile per ora)
 * circleIntelligence: determina il tipo di intelligenza del cerchio, IA o umana
 * crossIntelligence: determina il tipo di intelligenza della croce, IA o umana
 *
 * Nota: E' possibile evitare comunque di visualizzare l'animazione di scorrimento impostando prevScreen a 0.
 * Se si decide di visualizzarla è necessario che prevScreen sia un array di caratteri lungo almeno VIDEOBUFFER_SIZE.
 */
void playTrisInitialize(int consoleB, int consoleH, char *prevScreen, enum GameMode gameMode,
	enum PlayerTypes circleIntelligence, enum PlayerTypes crossIntelligence);
/* Distrugge il gioco liberando la memoria occupata
 */
void playTrisDestroy();

/* Si occupa di aggiornare la logica di gioco single player e di ricevere gli input del giocatore.
 * deltaT: lasso di tempo trascorso dall'ultima chiamata
 * Ritorno: int che indica il comando da intraprendere secondo la seguente tabella
 *			-1: torna a menu iniziale
 *			0: non eseguire nulla
 */
int playTrisUpdate(int deltaT);
/* Si occupa di aggiornare la schermata ad ogni ciclo di gioco.
 * videoBuffer: parametro di output. Contiene la schermata da stampare
 *
 * La stringa passata dovrà essere lunga necessariamente almeno VIDEOBUFFER_SIZE
 */
void playTrisDraw(char *videoBuffer);

#endif