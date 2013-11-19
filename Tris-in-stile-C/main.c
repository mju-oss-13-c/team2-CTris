#include "tris.h"

int main (){
	int vittoria;
	int difficolta;
	tastierino = 1;
	a = 'a';
	do{
		giocatore=1,vittoria=0;
        scelta=0, difficolta=0, mossa=0;
        
		/*Menu d'inizio*/
		system(clear);
		printf("\n%-64s%-70s%s\n\n", SOTTOLINEATO GIALLO, "Tris in stile C", RESET BIANCO);
		printf("\n%-53s%s%s %s\n", ROSSO, "[1]", BIANCO, "Partita con 2 giocatori");
		printf("\n%-53s%s%s %s\n", ROSSO, "[2]", BIANCO, "Partita singolo giocatore");
		if(!os)
			printf("\n%-53s%s%s %s%c %s\n", ROSSO, "[3]", BIANCO, "Modalit", 133, "di input");
		else
			printf("\n%-53s%s%s %s\n", ROSSO, "[3]", BIANCO, "Modalità di input");
		printf("\n%-53s%s%s %s\n", ROSSO, "[4]", BIANCO, "Informazioni");
		printf("\n%-53s%s%s %s\n", ROSSO, "[5]", BIANCO, "Esci");
		scanf("\n%d",&scelta);
        switch(scelta){
			
			/*case per la partita con 2 giocatori*/
            case 1:{
				
				/*Vuota la tabella, pulisce lo schermo e la stampa*/
               	vuota();
               	system(clear);
               	stampa();
				
				/*ciclo che contiene la partita. Dura fino alla vittoria*/
               	do{
					/*Legge la mossa del giocatore*/
					leggimossa();
                   	system(clear);
                   	
					/* conteggio delle mosse, 
					 * assegnazione del simbolo alle coordinate scelte, 
					 * stampa della tabella,
					 */
					mossa++;
                   	tabella[i][k]=giocatore;
                   	stampa();
                   	/*Controlla se il giocatore ha vinto*/
					if(controlla(1)||controlla(2)){
						vittoria=1;
                       	break;
                    }
					/*cambia il turno del giocatore*/
                   	if(giocatore==1)
                       	giocatore=2;
                   	else
                       	giocatore=1;
                }
                while(!vittoria && mossa<M*M);
				
				/*Stampa il risultato della partita,
				 * mette in pausa,
				 * rompe lo switch,
				 * ritorna al menu
				 */
                if(controlla(1)==-1)
                    printf("%-34s%s\n", ROSSO, "Pareggio.");
                else
                    printf("%-26s%s\n%-20s %d.\n\n", ROSSO, "Partita terminata.", "Ha vinto il giocatore", giocatore);
				pausa();
                break;
            }
			
			/*Case che contiene la partita singolo giocatore*/
           	case 2:{
               	vuota();

				/*ciclo per scegliere la difficolta del gioco*/
				do{
					system(clear);	
					if(!os)
                   		printf("\n%-60s%-75s%c%s:\n\n", SOTTOLINEATO GIALLO, "Scegli la difficolt", 133, RESET BIANCO);
                   	else
						printf("\n%-60s%-75s%s\n\n", SOTTOLINEATO GIALLO, "Scegli la difficoltà:", RESET BIANCO);
					printf("%-60s%s%s %s\n", ROSSO, "[1]", BIANCO, "Facile");
					printf("%-60s%s%s %s\n", ROSSO, "[2]", BIANCO, "Medio");
					printf("%-60s%s%s %s\n", ROSSO, "[3]", BIANCO, "Difficile");
					scanf("\n%d", &difficolta);
                   	if(difficolta < 1 || difficolta > 3){
						printf("\n%-62s%s%s\n\n", GRASSETTO ROSSO, "Scelta non valida.", RESET BIANCO);
						aspetta(2);
					}
				}while(difficolta < 1 || difficolta > 3);
               	system(clear);
               	stampa();

				/*Ciclo che contiene la partita fino alla vittoria o al pareggio*/
               	do{

					/*Turno del giocatore umano*/
					if(giocatore==1){
						leggimossa();
						tabella[i][k]=1;
						system(clear);
						stampa();
						aspetta(1);
                   	}

					/*Turno del computer*/
					else{
                       	system(clear);
                       	printf("\n%-60s%s%s\n", ROSSO, "Gioco io ora...", RESET BIANCO);
                       	spinner(1);

	                   	/*switch che contiene la mossa del computer in base alla difficolta scelta*/
						switch(difficolta){
                            case 1:{
                                facile();
                                break;
                            }
                            case 2:{
                                medio();
                                break;
                            }
                            case 3:{
                                difficile();
                                break;
                            }
                        }
                        printf("\n%-60s%s%s\n", ROSSO, "Ok, ho scelto.", RESET BIANCO);
                        stampa();
                        aspetta(1);
                        system(clear);
                    }

					/*Conteggio delle mosse, 
					 * assegnazione del simbolo alle coordinate scelte,
					 * stampa della tabella
					 */
                   	mossa++;
                   	stampa();

					/*Controlla se qualcuno ha vinto*/
                   	if(controlla(1) || controlla(2)){
                       	vittoria=1;
                       	break;
                    }
					/*Cambia il turno del giocatore*/
                   	if(giocatore==1)
						giocatore=2;
                    else
                   		giocatore=1;
               	}
               	while(!vittoria && mossa<M*M);
               	system(clear);
               	stampa();
				printf(ROSSO);
				/*Stampa il risultato della partita, mette in pausa, rompe lo switch e ritorna al menu*/
               	if(controlla(1)==-1 && difficolta==1)
                   	printf("%-45s%s", "", "Pareggio, potevi fare di meglio.");
				else{
					if(controlla(1)==-1 && difficolta==2)
						printf("%-45s%s", "", "Pareggio, ci eri quasi, riprova...");
					else{
						if(controlla(1)==-1 && difficolta==3){
							if(!os)
								printf("%-45s%s %c %s%c %s", "", "Pareggio, ti", 138, "andata gi", 133, ", bene...");
							else
								printf("%-45s%s", "", "Pareggio, ti è andata già bene...");
						}
                    }
                }
               	if(controlla(2) && difficolta==1)
                   	printf("%-25s%s", "", "Hai perso. Ti sei fatto battere da delle mosse pseudocasuali, complimenti.");
                else{
                    if(controlla(2) && difficolta==2)
                       printf("%-45s%s", "", "Hai perso. Dai... lo potevi battere.");
                    else{
                        if(controlla(2) && difficolta==3)
                          printf("%-45s%s", "", "Lo sai... non puoi battere il minimax.");
                    }
                }

                if(controlla(1) && difficolta==1)
                    printf("%-38s%s", "", "Bravo, hai battuto uno che mette crocette a caso!");
				else{
                    if(controlla(1) && difficolta==2){
                        if(!os)
							printf("%-48s%s %c %s", "", "Bravo, non", 138, "stato facile!");
						else
                            printf("%-48s%s", "", "Bravo, non è stato facile!");
					}
                    else{
                        if(controlla(1) && difficolta==3){
                            printf("%-48s%s", "", "Impossibile!! Non hai vinto!!!");
							if(!os)
                                printf("%-30s%s%c %s", "", "Sei vedi questo messaggio sicuramente c'",138, "qualcosa che non va.");
                            else
                                printf("%-30s%s", "", "Sei vedi questo messaggio sicuramente c'è qualcosa che non va.");
						}
					}
				}
				pausa();
				break;
			}
			case 3:{

				/*Case per la scelta delle modalità di input*/
				system(clear);
				do{
					system(clear);
					printf("%-34s %s%s%s%s%s\n", "", "Vuoi usare il tastierino numerico o le coordinate", ROSSO, "[T,C]", BIANCO, "?");
                    scanf("\n%c",&a);
                }while(a!='T' && a!='C' && a!='t' && a!='c');

                if(a=='T' || a=='t')
                    tastierino=1;
                else
                    tastierino=0;

                if(tastierino==1){
                    system(clear);
					printf("\n%-60s%-74s%s\n\n", SOTTOLINEATO GIALLO, "Istruzioni per giocare", RESET BIANCO);
					printf("\n%-40s%s%s %s\n", ROSSO, "*", BIANCO, "Usa il tastierino come se fosse la tabella del tris.");
					if (!os)
						printf("\n%-40s%s%s %s %c %s\n" ,ROSSO, "*", BIANCO, "Ad esempio il tasto 5", 138, "il centro.");
                    else
						printf("\n%-40s%s%s %s\n", ROSSO, "*", BIANCO, "Ad esempio il tasto 5 è il centro.");
					printf("\n%-40s%s%s %s\n\n", ROSSO, "*", BIANCO, "Divertiti.");
                }

                else{
                    system(clear);
					printf("\n%-60s%-74s%s\n\n", SOTTOLINEATO GIALLO, "Istruzioni per giocare", RESET BIANCO);
                    if(!os)
                        printf("%-35s%s %s %s %c %s\n", ROSSO, "*", BIANCO, "Il tris", 138, "contenuto in una tabella numerica:");
                    else
                        printf("%-35s%s %s%s\n", ROSSO, "*", BIANCO, "Il tris è contenuto in una tabella numerica:");
                    
                    printf("%-37s%s\n","", "Le coordinata della mosssa vanno in indicate con: x,y.");
                    printf("%-37s%s\n\n", "", "x sono le righe e y le colonne.");
                    printf("%-35s%s%s %s\n", ROSSO, "*", BIANCO, "Ricordati che stai parlando di un'array: quindi si conta da 0:");
                    if(!os)
                        printf("%-37s%c %s%c %s\n\n", "la casella nella 1", 248, "riga nella 1", 248, "colonna ha quindi coordinate 0,0.");
                    else
                        printf("%-37s%s\n\n", "", "la casella nella 1° riga nella 1° colonna ha quindi coordinate 0,0.");
                    printf("%-35s%s %s%s\n\n", ROSSO, "*", BIANCO, "Divertiti.");
                }
                pausa();
                break;
            }
            case 4:{

				/*About*/
               	system(clear);
				printf("\n%-64s%-70s%s\n\n", SOTTOLINEATO GIALLO, "Tris in stile C", RESET BIANCO);
                if (!os)
                    printf("%-28s%s %c %s\n%-28s%s\n\n", "", "Questo gioco", 138, "stato sviluppato da Michele Guerini Rocco in una fredda", "", "notte di premiazioni e sistemato per l'intero anno successivo.");
                else
                    printf("%-28s%s\n%-28s%s\n\n", "", "Questo gioco è stato sviluppato da Michele Guerini Rocco in una fredda", "", "notte di premiazioni e sistemato per l'intero anno successivo.");
                pausa();
                break;
            }
        }
        
    }while(scelta!=5);
    return 0;
}

