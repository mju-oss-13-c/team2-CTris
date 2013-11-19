#ifndef _TRIS_H_

	#define _TRIS_H_

	/*Librerie Principali*/
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include <limits.h>

	/*Colori ANSI*/
	#define NERO "\033[22;30m"
	#define BLU "\033[34m"
	#define GIALLO "\033[33m"
	#define BIANCO "\033[37m"
	#define ROSSO "\033[31m"
	#define RESET "\033[0m"
	#define GRASSETTO "\033[1m"
	#define SOTTOLINEATO "\033[4m"

	/*Definizioni*/
	#define random(x) rand() % x
	#define randomize srand((unsigned)time(NULL))
	#define M 3

	/*Funzione specifiche degli os*/
	#ifdef __WIN32__

		#include <conio.h>
		#include <windows.h>
		#define os 0
		#define clear "cls"
		#define sleep(x) Sleep(x)

	#else

		#include <termios.h>
		#include <unistd.h>
		#define os 1
		#define clear "clear"
		#define sleep(x) usleep(x*1000)
		int mgetchar(void);

	#endif

	/*Prototipi*/
	void stampa(void);
	void vuota(void);
	void leggimossa(void);
	int controlla(int giocatore);
	int minimax(int giocatore, int profondita);
	void facile(void);
	void medio(void);
	void difficile(void);
	void pausa(void);
	void spinner(int tempo);
	void aspetta(int t);
	void beep(int t);

	/*Variabili globali*/
	char a,c;
	int i,k;
	int giocatore,scelta,mossa;
	int tabella[M][M];
	int tastierino;
	
#endif
