nclude <stdio.h>

#include <stdlib.h>

#include <math.h>

#include <ctype.h>

struct tic{

        char selection;

        char selection2;

        char board[25];

        int people;

};

/****** opening_screen* Displays instructions and prompts for a character*

Parameters: the global struct. * Precond: the declared struct* Postcond: The struct contains the character for playing*****/



void opening_screen (struct tic* StBoard)  {

        printf("\n\n!!!!! TIC-TAC-TOE °ÔÀÓ!!!!!\n\n\n");

        printf("  0  |  1  |  2  |  3  |  4  \n");

        printf("-----------------------------\n");

        printf("  5  |  6  |  7  |  8  |  9  \n");

        printf("-----------------------------\n");

        printf("  10 |  11 |  12 |  13 |  14 \n");

        printf("-----------------------------\n");

        printf("  13 |  14 |  15 |  18 |  19 \n");

        printf("-----------------------------\n");

        printf("  20 |  21 |  22 |  23 |  24 \n");

        printf("\n");



        printf("À§ ±×ž²ÀÇ ŒýÀÚŽÂ °¢°¢ÀÇ ÀÚž®ÀÔŽÏŽÙ.\n");

        printf("\n");



        printf("o ¿Í x Áß ¿øÇÏŽÂ °ÍÀ» ÀÔ·ÂÇÏŒŒ¿ä.:\n");



        fflush(stdin);



        scanf(" %c", &StBoard->selection); //pass a character to the struct

        printf("\n");



}



void playing_piece (struct tic* StBoard)  {

        int cabrone = 1; //will allow for error handle

        if (StBoard->people == 1)  {

                if (StBoard->selection == 'x')  {

                        printf("ÄÄÇ»ÅÍŽÂ o ÀÔŽÏŽÙ.\n");

                        StBoard->selection2 = 'o';

                }

                else  {

                        printf("ÄÄÇ»ÅÍŽÂ x ÀÔŽÏŽÙ.\n");

                        StBoard->selection2 = 'x';

                }

                printf("\n");



        }

        else if (StBoard->people == 2)  {

                while (cabrone > 0)  {

                        printf("o ¿Í x Áß 2ÇÃ·¹ÀÌŸîÀÇ ¿øÇÏŽÂ °ÍÀ» ÀÔ·ÂÇÏŒŒ¿ä:\n");

                        printf("\n");



                        fflush(stdin);

                        scanf(" %c", &StBoard->selection2);

                        if (StBoard->selection2 == StBoard->selection)  {

                                printf("ºÒ°¡ŽÉÇÕŽÏŽÙ. ŽÙž¥ °ÍÀ» ÀÔ·ÂÇÏŒŒ¿ä.\n");  //invalid if character is chosen already full

                        }

                        else cabrone--;

                }

        }

}

void draw_board (struct tic* StBoard) {

        printf("  %c  |  %c  |  %c  |  %c |  %c  \n", StBoard->board[0], StBoard->board[1], StBoard->board[2], StBoard->board[3], StBoard->board[4]);

        printf("---------------------------------\n");

        printf("  %c  |  %c  |  %c  |  %c |  %c  \n", StBoard->board[5], StBoard->board[6], StBoard->board[7],StBoard->board[8], StBoard->board[9]);

        printf("---------------------------------\n");

        printf("  %c  |  %c  |  %c  |  %c |  %c  \n", StBoard->board[10], StBoard->board[11], StBoard->board[12],StBoard->board[13], StBoard->board[14]);

        printf("---------------------------------\n");

        printf("  %c  |  %c  |  %c  |  %c |  %c  \n", StBoard->board[15], StBoard->board[16], StBoard->board[17], StBoard->board[18], StBoard->board[19]);

        printf("---------------------------------\n");

        printf("  %c  |  %c  |  %c  |  %c |  %c  \n", StBoard->board[20], StBoard->board[21], StBoard->board[22], StBoard->board[23], StBoard->board[24]);



        //look at this board_ptr, prettier than my girlfriend

}



int check_winner (struct tic* StBoard)  {

        char num1 = StBoard->selection;

        char num2 = StBoard->selection2;

        /*        ** declared chars represent above places in StBoard,         ** for ease of typing.        */

        // 1player horizon

        if ((StBoard->board[0] == num1) && (StBoard->board[1] == num1) && (StBoard->board[2] == num1) && (StBoard->board[3] == num1) && (StBoard->board[4] == num1)) {

                return 1;

        }

        if ((StBoard->board[5] == num1) && (StBoard->board[6] == num1) && (StBoard->board[7] == num1) && (StBoard->board[8] == num1) && (StBoard->board[9] == num1))  {

                return 1;

        }

        if ((StBoard->board[10] == num1) && (StBoard->board[11] == num1) && (StBoard->board[12] == num1) && (StBoard->board[13] == num1) && (StBoard->board[14] == num1))  {

                return 1;

        }

        if ((StBoard->board[15] == num1) && (StBoard->board[16] == num1) && (StBoard->board[17] == num1) && (StBoard->board[18] == num1) && (StBoard->board[19] == num1))  {

                return 1;

        }

        if ((StBoard->board[20] == num1) && (StBoard->board[21] == num1) && (StBoard->board[22] == num1) && (StBoard->board[23] == num1) && (StBoard->board[24] == num1))  {

                return 1;

        }

        //1player vertical

        if ((StBoard->board[0] == num1) && (StBoard->board[5] == num1) && (StBoard->board[10] == num1) && (StBoard->board[15] == num1) && (StBoard->board[20] == num1))  {

                return 1;

        }

        if ((StBoard->board[1] == num1) && (StBoard->board[6] == num1) && (StBoard->board[11] == num1) && (StBoard->board[16] == num1) && (StBoard->board[21] == num1))  {

                return 1;

        }

        if ((StBoard->board[2] == num1) && (StBoard->board[7] == num1) && (StBoard->board[12] == num1) && (StBoard->board[17] == num1) && (StBoard->board[22] == num1))  {

                return 1;

        }

        if ((StBoard->board[3] == num1) && (StBoard->board[8] == num1) && (StBoard->board[13] == num1) && (StBoard->board[18] == num1) && (StBoard->board[23] == num1))  {

                return 1;

        }

        if ((StBoard->board[4] == num1) && (StBoard->board[9] == num1) && (StBoard->board[14] == num1) && (StBoard->board[19] == num1) && (StBoard->board[24] == num1))  {

                return 1;

        }



        //1player dialog

        if ((StBoard->board[0] == num1) && (StBoard->board[6] == num1) && (StBoard->board[12] == num1) && (StBoard->board[18] == num1) && (StBoard->board[24] == num1))  {

                return 1;

        }

        if ((StBoard->board[4] == num1) && (StBoard->board[8] == num1) && (StBoard->board[12] == num1) && (StBoard->board[16] == num1) && (StBoard->board[20] == num1))  {

                return 1;

        }



        //2player dialog

        if ((StBoard->board[0] == num2) && (StBoard->board[6] == num2) && (StBoard->board[12] == num2) && (StBoard->board[18] == num2) && (StBoard->board[24] == num2))  {

                return 1;

        }

        if ((StBoard->board[4] == num2) && (StBoard->board[8] == num2) && (StBoard->board[12] == num2) && (StBoard->board[16] == num2) && (StBoard->board[20] == num2))  {

                return 1;

        }



        //2player horizon

        if ((StBoard->board[0] == num2) && (StBoard->board[1] == num2) && (StBoard->board[2] == num2) && (StBoard->board[3] == num2) && (StBoard->board[4] == num2)) {

                return 1;

        }

        if ((StBoard->board[5] == num2) && (StBoard->board[6] == num2) && (StBoard->board[7] == num2) && (StBoard->board[8] == num2) && (StBoard->board[9] == num2))  {

                return 1;

        }

        if ((StBoard->board[10] == num2) && (StBoard->board[11] == num2) && (StBoard->board[12] == num2) && (StBoard->board[13] == num2) && (StBoard->board[14] == num2))  {

                return 1;

        }

        if ((StBoard->board[15] == num2) && (StBoard->board[16] == num2) && (StBoard->board[17] == num2) && (StBoard->board[18] == num2) && (StBoard->board[19] == num2))  {

                return 1;

        }

        if ((StBoard->board[20] == num2) && (StBoard->board[21] == num2) && (StBoard->board[22] == num2) && (StBoard->board[23] == num2) && (StBoard->board[24] == num2))  {

                return 1;

        }



        //2player vertical

        if ((StBoard->board[0] == num2) && (StBoard->board[5] == num2) && (StBoard->board[10] == num2) && (StBoard->board[15] == num2) && (StBoard->board[20] == num2))  {

                return 1;

        }

        if ((StBoard->board[1] == num2) && (StBoard->board[6] == num2) && (StBoard->board[11] == num2) && (StBoard->board[16] == num2) && (StBoard->board[21] == num2))  {

                return 1;

        }

        if ((StBoard->board[2] == num2) && (StBoard->board[7] == num2) && (StBoard->board[12] == num2) && (StBoard->board[17] == num2) && (StBoard->board[22] == num2))  {

                return 1;

        }

        if ((StBoard->board[3] == num2) && (StBoard->board[8] == num2) && (StBoard->board[13] == num2) && (StBoard->board[18] == num2) && (StBoard->board[23] == num2))  {

                return 1;

        }

        if ((StBoard->board[4] == num2) && (StBoard->board[9] == num2) && (StBoard->board[14] == num2) && (StBoard->board[19] == num2) && (StBoard->board[24] == num2))  {

                return 1;

        }







        else return 0;

}



void AI(struct tic* StBoard)  {

        int i;

        int fart = 1;

        srand(time(NULL));

        //no time in between random choice

        while(fart > 0)  {

                i = rand()%25;

                //make i a random number, but mod it by 9

                while (StBoard->board[i] == StBoard->selection || StBoard->board[i] == StBoard->selection2)  {

                        i = rand()%25;

                        /*                        ** Keep making up a new number until it doesn't match the one player1 or it played                        */

                }

                StBoard->board[i] = StBoard->selection2;

                //put in the character for AI

                printf("ÄÄÇ»ÅÍ°¡ ÀÔ·ÂÇÑ ŒýÀÚ :, %d\n\n", i);

                //ya dig?

                fart --;

                //decrease fart by one, making the while false, breaking dat loop de loop

        }

}



void player_move(struct tic* StBoard)  {

        int i;

        int fart = 1;

        while (fart > 0)  {

                printf("1ÇÃ·¹ÀÌŸîÀÇ ŒøŒ­ÀÔŽÏŽÙ. ¿øÇÏŽÂ ÀÚž®ÀÇ ŒýÀÚžŠ ÀÔ·ÂÇÏŒŒ¿ä.: ");

                fflush(stdin);

                scanf("%d", &i);

                //scans in number from reference grid

        //      if (i != (sizeof(int)))  {

        //              printf("ºÒ°¡ŽÉÇÕŽÏŽÙ. ŽÙž¥ ŒýÀÚžŠ ÀÔ·ÂÇÏŒŒ¿ä.\n");

        //      }

                if (i < 0 || i > 24)  {

                        printf("ºÒ°¡ŽÉÇÕŽÏŽÙ. ŽÙž¥ ŒýÀÚžŠ ÀÔ·ÂÇÏŒŒ¿ä.\n");

                        //invalid input

                }

                else if (StBoard->board[i] == StBoard->selection || StBoard->board[i] == StBoard->selection2)  {

                        printf("ºÒ°¡ŽÉÇÕŽÏŽÙ. ŽÙž¥ ŒýÀÚžŠ ÀÔ·ÂÇÏŒŒ¿ä.\n");

                        //invalid if space full

                }

                else  {

                        StBoard->board[i] = StBoard->selection;

                        fart--;

                        //set while loop to 0, break

                }

        }

}



void player2_move(struct tic* StBoard)  {

        //so when this function is called you will love to see how player 2 moves

        int i = 0;

        int fart = 1;

        while (fart > 0)  {

                printf("2ÇÃ·¹ÀÌŸîÀÇ ŒøŒ­ÀÔŽÏŽÙ. ¿øÇÏŽÂ ÀÚž®ÀÇ ŒýÀÚžŠ ÀÔ·ÂÇÏŒŒ¿ä.: ");

                fflush(stdin);

                scanf("%d", &i);

                //scans in move, according to reference numbers.

                if (i < 0 || i > 24)  {

                        printf("ºÒ°¡ŽÉÇÕŽÏŽÙ. ŽÙž¥ ŒýÀÚžŠ ÀÔ·ÂÇÏŒŒ¿ä.\n");

                }

                else if (StBoard->board[i] == StBoard->selection || StBoard->board[i] == StBoard->selection2)  {

                        printf("ºÒ°¡ŽÉÇÕŽÏŽÙ. ŽÙž¥ ŒýÀÚžŠ ÀÔ·ÂÇÏŒŒ¿ä.\n");

                }

                else  {

                        StBoard->board[i] = StBoard->selection2;

                        fart --;

                }

        }

        while (fart > 0);

}



int main ()  {

        int i;

        int fart = 0;

        char reps = 'y';

        //initializes reps, will control repitition of game

        while (reps == 'y')  {

                struct tic* StBoard = (struct tic*)(malloc(sizeof(struct tic)));

                //mallocs teh memory for the struct

                i = 0;

                fart = 0;

                //ooh get that fart

                printf("\n\nÄÄÇ»ÅÍ¿Í °ÔÀÓÇÏ±â (1), 2ÀÎ¿ë °ÔÀÓÇÏ±â (2): ");

                scanf("%d", &StBoard->people);

                //IMPORTANT, fills the struct with how many people will play, decides if AI is used

                opening_screen(StBoard);

                playing_piece(StBoard);

                while (fart == 0)  {

                        if (StBoard->people == 2)  {

                                for (i = 0; i <= 12; i++)  {

                                        //error checking for the case where too many turns occur, shouldn't be able to happen, but still.

                                        player_move(StBoard);

                                        draw_board(StBoard);

                                        fart = check_winner(StBoard);

                                        if(fart == 1){

                                                //checks to see if check_winner returned a 1, which is a won game

                                                break;

                                                //cuts out if above case is true

                                        }

                                        player2_move(StBoard);

                                        draw_board(StBoard);

                                        fart = check_winner(StBoard);

                                        if(fart == 1){

                                                break;

                                        }

                                }

                        }

                        if (StBoard->people == 1)  {

                                for (i = 0; i <= 12; i++)  {

                                        player_move(StBoard);

                                        draw_board(StBoard);

                                        fart = check_winner(StBoard);

                                        if(fart == 1){

                                                break;

                                        }

                                        AI(StBoard);

                                        draw_board(StBoard);

                                        fart = check_winner(StBoard);

                                        if(fart == 1){

                                                break;

                                        }

                                }

                        }

                }

                printf("ŽçœÅÀÌ ÀÌ°åœÀŽÏŽÙ!!!!!!!!!\n\n");

                printf("\n");



                printf("ŽÙœÃ °ÔÀÓÇÏœÃ°ÚœÀŽÏ±î?  [y] [n]\n");

                scanf(" %c", &reps);

                /*                ** prints a winner message and asks if want to play again

                 ** gives option for yes and no, are chars.

                 ** 'n' will break the program

                 */

        }

        return 0;

}
B
B
B
B
B
B
B
B
B
B
B
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
A
}
