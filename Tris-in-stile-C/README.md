#Tris in stile C

#Gioco del Tris in C

### Informazioni
È il classico gioco del tris con 2 modalità: a 2 giocatori o singolo contro il computer.
Le mosse del computer sono pseudocasuali (livello facile) o calcolate usando l'algoritmo minimax (medio e difficile).
È possibile cambiare la grandezza della tabella con una qualunque dimensione; in ogni caso per vincere basterà fare tris. 

L'output è a colori grazie alle sequenze di escape ANSI. 
Per visualizzare decentemente il testo è necessario un terminale compatibile.
Su Windows si può usare [ANSIcon](http://github.com/adoxa/ansicon) che ripristina il supporto al driver ANSI.SYS per le console Win32.

### Compilazione
Per compilare il programma su UNIX usa _make_.
  Su windows usa un compilatore qualisasi o _mingw32-make_ se hai [MinGW](http://www.mingw.org).

### Istruzioni
Le istruzioni su come giocare sono cotenute nel programma stesso.

### Avvisi
Se provando a compilare ricevi avvisi del tipo:
    
    warning: implicit declaration of function ‘getch’
    warning: implicit declaration of function ‘kbhit’

oppure:

    warning: implicit declaration of function ‘mgetchar’

è perchè stai compilando rispettivamente su UNIX o su Windows e queste funzioni vengono sostituite dalle loro controparti per quel sistema dato che non sono portabili. Anche se sono nel sorgente e nel file oggetto non verranno mai eseguite.
