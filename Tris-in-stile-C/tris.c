#include "tris.h"

#if os
	/*Legge dalla tastiera senza usare il buffer*/
	int mgetchar(){
		char buf=0;	
		struct termios old={0};
		if(tcgetattr(0,&old)<0)
			perror("tcsetattr()");
		old.c_lflag&=~ICANON;
		old.c_lflag&=~ECHO;
		old.c_cc[VMIN]=1;
		old.c_cc[VTIME]=0;
		if(tcsetattr(0,TCSANOW,&old)<0)
			perror("tcsetattr ICANON");
		if(read(0,&buf,1)<0)
			perror("read()");
		old.c_lflag|=ICANON;
		old.c_lflag|=ECHO;
		if(tcsetattr(0,TCSADRAIN,&old)<0)
			perror("tcsetattr ~ICANON");
		return (buf);
	}
#endif

/*Funzioni*/

/*Stampa la tabella del tris*/
void stampa(){
	int i,k;
	printf("\n\n\n");
	for(i=0;i<M;i++) {
		printf("%-60s", RESET);
		for(k=0;k<M;k++) {
			if(tabella[i][k]==1)
				printf(GIALLO"  O ");
			else {
				if(tabella[i][k]==2)
					printf(ROSSO"  X ");
				else
					printf(BIANCO"  . ");
			}
		}
		printf("\n\n");
	}
	printf("\n");
}


/*Cancella la tabella del tris*/
void vuota() {
	for(i=0;i<M;i++)
		for(k=0;k<M;k++)
			tabella[i][k]=0;
}


/*Legge la mossa del giocatore*/
void leggimossa(){
	int tasto=0;
	fflush(stdin);

	/*Se è attivo il tastierino*/
	if(tastierino==1){
		do{
			tasto=0;
			fflush(stdin);

			/*2 giocatori*/
			if(scelta==2)
				printf("%-59s%s%s\n", GIALLO, "Fai la tua mossa:", BIANCO);
			else
				printf("%58s%s %d\n%-55s%s%s\n", GIALLO, "Gioca il giocatore", giocatore, "", "Fai la tua mossa:",BIANCO);
			if(os)
				tasto=mgetchar();
			else
				do{
					tasto=getch();
				}while(kbhit());

			switch(tasto){
				case 49:{
					i=2;
					k=0;
					break;
				}
				case 50:{
					i=2;
					k=1;
					break;
				}
				case 51:{
					i=2;
					k=2;
					break;
				}
				case 52:{
					i=1;
					k=0;
					break;
				}
				case 53:{
					i=1;
					k=1;
					break;
				}
				case 54:{
					i=1;
					k=2;
					break;
				}
				case 55:{
					i=0;
					k=0;
					break;
				}
				case 56:{
					i=0;
					k=1;
					break;
				}
				case 57:{
					i=0;
					k=2;
					break;
				}
					
			}
			if(tabella[i][k]==1 || tabella[i][k]==2 || i<0 || k<0 || i>=M || k>=M){
				system(clear);
				stampa();
				printf("%-59s%s%s\n\n", GRASSETTO ROSSO, "Mossa non valida, riprova.", RESET BIANCO);
			}
		}while(tabella[i][k]==1 || tabella[i][k]==2 || i<0 || k<0 || i>=M || k>=M);
	}

	/*Mossa con coordinate*/
	else{
		do{

			/*Giocatore singolo*/
			if(scelta==2)
				printf("%-63s%s\n%-40s%s%s %s%s\n", GIALLO, "Tocca a te.", "", "Inserisci coordinate della mossa", ROSSO, "[Riga,colonna]:", BIANCO);

			/*2 giocatori*/
			else
				printf("%-58s%s %d\n%-40s%s %s%s%s\n", GIALLO, "Gioca il giocatore", giocatore, "", "Inserisci coordinate della mossa", ROSSO, "[Riga,colonna]:", BIANCO);
			scanf("%d,%d",&i,&k);
			if(tabella[i][k]==1 || tabella[i][k]==2 || i<0 || k<0 || i>=M || k>=M){
				system(clear);
				stampa();
				printf("\n\n%-56s%s%s\n\n\n", GRASSETTO ROSSO, "Coordinate non valide, riprova.", RESET BIANCO);
			}
		}while(tabella[i][k]==1 || tabella[i][k]==2 || i<0 || k<0 || i>=M || k>=M);
		system(clear);
	}
	
}

/*Controlla se il giocatore ha vinto*/
int controlla(int giocatore){
	/*Diagonali*/
	for(i=0;i<M;i++){
		for(k=(M-1);k>=0;k--)
			if((tabella[i][k]==giocatore && tabella[i+1][k-1]==giocatore && tabella[i+2][k-2]==giocatore) && (i+2<M))
				return 1;
		for(k=0;k<M;k++)
			if((tabella[i][k]==giocatore && tabella[i+1][k+1]==giocatore && tabella[i+2][k+2]==giocatore) && ((i+2<M) && (k+2<M)))
				return 1;	
	}
	/*Righe e colonne*/
	for(i=0;i<M;i++){
		for(k=0;k<M;k++)
			if((tabella[i][k]==giocatore && tabella[i][k+1]==giocatore && tabella[i][k+2]==giocatore) && (k+2<M))
				return 1;
		
		for(k=0;k<M;k++)
			if((tabella[k][i]==giocatore && tabella[k+1][i]==giocatore && tabella[k+2][i]==giocatore) && (k+2<M))
				return 1;
	}
	int piene=M*M;
	for(i=0;i<M;i++)
		for(k=0;k<M;k++)
			if(!tabella[i][k])
				piene--;
	if(piene==M*M)
		return -1;
	else	
		return 0;
}

/*Minimax*/
int minimax(int giocatore, int profondita){
	if(controlla(2))
		return INT_MAX;
	if(controlla(1)==-1)
		return INT_MIN;
	int res,tmp;
	if(giocatore==1){
		res=1;
		for(i=0;i<M;i++){
			for(k=0;k<M;k++){
				if(!tabella[i][k]){
					tabella[i][k]=1;
					if(controlla(1)){
						if(profondita==20){
							tabella[i][k]=0;
							return INT_MIN;
						}
						else
							res-=2;
					}
					else if(((tmp=minimax(2,profondita-1))<res) || (tmp==INT_MIN))
						res=tmp;
					tabella[i][k]=0;
				}
			}
		}
	}
	else{
		res=-1;
		for(i=0;i<M;i++){
			for(k=0;k<M;k++){
				if(!tabella[i][k]){
					tabella[i][k]=2;
					if(controlla(2))
						res+=2;
					else if(((tmp=minimax(1,profondita-1))>res) || (tmp==INT_MAX))
						res=tmp;
					tabella[i][k]=0;
				}
			}
		}
	}
	return res;
}

/*Mossa del computer a difficoltà facile*/
void facile() {
	int a,b;
	do{
		randomize;
		a=random(M);
		b=random(M);
	}while(tabella[a][b]==1 || tabella[a][b]==2);
	tabella[a][b]=2;
}

/*Mossa del computer a difficoltà media*/
void medio(){
	int max=INT_MIN,mi=1,mk=1,t;
	for(i=0;i<M;i++){
		for(k=0;k<M;k++){
			if(!tabella[i][k]){
				tabella[i][k]=2;
				t=minimax(1,10);
				if(t>max){
					max=t;
					mi=i;
					mk=k;
				}
				tabella[i][k]=0;
			}
		}
	}
	tabella[mi][mk]=2;
}

/*Mossa del computer a difficoltà difficile*/
void difficile(){
	int max=INT_MIN,mi=1,mk=1,t;
	for(i=0;i<M;i++){
		for(k=0;k<M;k++){
			if(!tabella[i][k]){
				tabella[i][k]=2;
				t=minimax(1,20);
				if(t>max){
					max=t;
					mi=i;
					mk=k;
				}
				tabella[i][k]=0;
			}
		}
	}
	tabella[mi][mk]=2;
}

/* Blocca l'esecuzione finchè non viene premuto invio*/
void pausa() {
	do
		getchar();
	while ((c= getchar()) != '\n' && c!= EOF);
}

/*Replica di Sleep()*/
void aspetta(int t){
	time_t Ti,Tf;
	time(&Ti);
	do{
		time(&Tf);
	}while(difftime(Tf,Ti)<t);
}

/*Caricamento stile Ajax*/
void spinner(int tempo) {
	char spinner[] = "/-\\|";
	printf("\n%-66s", GIALLO);
	for (int i=0; i<(tempo*10);i++){
		putchar(spinner[i%4]);
		fflush(stdout);
		sleep(200);
		putchar('\b');
	}
	printf(RESET);
	putchar(' ');
}

/*Beep*/
void beep(int t){
	for(i=0;i<t*100;i++)
		putchar('\a');
}

