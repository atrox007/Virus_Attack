                                                        /*VIRUS_ATTACK*/ 
                                                        
#include <stdio.h>      // It contains standard I/O operations.
#include <stdlib.h>    //  It contains general purpose functions. 
#include <conio.h>    //   It contains console I/O functions.
#include <windows.h> //    It contains functions of Windows API.

void ques () ;     //  Function Prototype

int main() 
{   
     	
	int sizey = 23;
    int sizex = 40;
    int x, y, yi;
    char world[sizey][sizex];
    char player = 'A';
    char playerLaser = '^';
    char enemy = 'M';
    char enemyShielded = 'O';
    char enemyLaser = 'I';
    char explosion = 'X';
    int score = 0;
    int victory = 1;
    int laserReady = 1;
    int enemyReady = 0;
    int time=0;


    /*welcome screen*/
    system("color 09") ;      // It changes background and foreground color.
    printf("\nViruses have invaded your network.\n \n");  // It prints data on the screen.
    Sleep(1500);   // It stops the execution for a specified time.
    printf("They are searching for your servers, erase them before they reach your servers  and create a havoc.\n \n");
    Sleep(2500);
    printf("You are the Cyberlord, fight them to the end.\n\n");
    Sleep(1000);
    printf("The enemy is not to be underestimated. Their weapons have devastating and magical effect. They can either erase you or teleport you somewhere inside the network.");
    Sleep(1000) ;
    printf("\n\nYou've got a powerful weapon.\n") ;
    Sleep(1000) ;
	printf("It's time to teach them a good lesson. \n \n");
    Sleep(1000);
    printf("Controls-> \n  A- Move Left\n  D- Move Right\n  M- Laser \n \n \n  ");
    Sleep(1000);
    printf("\n \n Press any key to start...");
    getch();       // It holds the screen until a key is pressed.
    system("color 0A") ;

    /*initialise world*/
    int totalEnemies = 0;
    for (x = 0; x < sizex; x ++) {
        for (y = 0; y < sizey; y ++) {
            if ((y+1) % 2 == 0 && y < 7 && x > 4
            && x < sizex - 5 && x % 2 ==0) {
                world[y][x] = enemy;
                totalEnemies ++;
            }
            else if ((y+1) % 2 == 0 && y >= 7 && y < 9 && x > 4
            && x < sizex - 5 && x % 2 ==0){
                world[y][x] = enemyShielded;
                totalEnemies = totalEnemies + 2;
            }
            else {
                world[y][x] = ' ';
            }
        }
    }
    world[sizey - 1][sizex / 2] = player;
    int i = 1;
    char direction = 'l';
    char keyPress;
    int currentEnemies = totalEnemies;
    while(currentEnemies > 0 && victory) {
        int drop = 0;
        int enemySpeed = 1 + 10 * currentEnemies / totalEnemies;
        laserReady ++;

        /*display world*/
        system("cls");     // It clears the screen.
        printf("     SCORE:    %d", score);
        printf("\n");
            for (y = 0; y < sizey; y ++) {
            printf("|");
                for (x = 0; x < sizex; x ++) {
                    printf("%c",world[y][x]);
                }
            printf("|");
            printf("\n");
            }

        /*laser time*/
        for (x = 0; x < sizex; x ++) {
            for (y = sizey-1; y >= 0; y --) {
                if (i%2 == 0 && world[y][x] == enemyLaser
                && (world[y+1][x] != enemy & world[y+1][x] != enemyShielded)){
                world[y+1][x] = enemyLaser;
                world[y][x] = ' ';
                }
                else if (i%2 == 0 && world[y][x] == enemyLaser
                && (world[y+1][x] == enemy | world[y+1][x] == enemyShielded)){
                    world[y][x] = ' ';
                }
            }
        }
        for (x = 0; x < sizex; x ++) {
            for (y = 0; y < sizey; y ++) {
                if ((i % 5) == 0 && (world[y][x] == enemyShielded
                | world[y][x] == enemy) && (rand() % 15) > 13
                && world[y+1][x] != playerLaser) {
                    for (yi = y+1; yi < sizey; yi ++) {
                        if (world[yi][x] == enemy
                        | world[yi][x] == enemyShielded) {
                            enemyReady = 0;
                            break;
                        }
                        enemyReady = 1;
                    }
                    if (enemyReady) {
                        world[y+1][x] = enemyLaser;
                    }
                }
                if (world[y][x] == playerLaser && world[y-1][x] == enemy) {
                    world[y][x] = ' ';
                    world[y-1][x] = explosion;
                    currentEnemies --;
                    score = score + 50;
                }
                else if (world[y][x] == playerLaser
                && world[y-1][x] == enemyShielded) {
                    world[y][x] = ' ';
                    world[y-1][x] = enemy;
                    currentEnemies --;
                    score = score + 50;
                }
                else if (world[y][x] == playerLaser
                && world[y-1][x] == enemyLaser) {
                    world[y][x] = ' ';
                }
                else if (world[y][x] == explosion) {
                    world[y][x] = ' ';
                }
                else if ((i+1) % 2 == 0 && world[y][x] == enemyLaser
                && world[y+1][x] == player) {
                    world[y+1][x] = explosion;
                    world[y][x] = ' ';
                    victory = 0;
                }
                else if (world[y][x] == playerLaser
                && world[y-1][x] != enemyLaser) {
                        world[y][x] = ' ';
                        world[y-1][x] = playerLaser;
                }
            }
        }

        /*update enemy direction*/
        for (y = 0; y < sizey; y ++) {
            if (world[y][0] == enemy) {
                direction = 'r';
                drop = 1;
                break;
            }
            if (world[y][sizex-1] == enemy){
                direction = 'l';
                drop = 1;
                break;
            }
        }

        /*update board*/
        if (i % enemySpeed == 0) {
            if (direction == 'l') {
                for (x = 0; x < sizex - 1; x ++) {
                    for (y = 0; y < sizey; y ++) {
                        if (drop && (world[y-1][x+1] == enemy
                            || world[y-1][x+1] == enemyShielded)){
                            world[y][x] = world[y-1][x+1];
                            world[y-1][x+1] = ' ';
                        }
                        else if (!drop && (world[y][x+1] == enemy
                            || world[y][x+1] == enemyShielded)) {
                            world[y][x] = world[y][x+1];
                            world[y][x+1] = ' ';
                        }
                    }
                }
            }
            else {
                for (x = sizex; x > 0; x --) {
                    for (y = 0; y < sizey; y ++) {
                        if (drop && (world[y-1][x-1] == enemy
                            || world[y-1][x-1] == enemyShielded)) {
                            world[y][x] = world[y-1][x-1];
                            world[y-1][x-1] = ' ';
                        }
                        else if (!drop && (world[y][x-1] == enemy
                            || world[y][x-1] == enemyShielded)) {
                            world[y][x] = world[y][x-1];
                            world[y][x-1] = ' ';
                        }
                    }
                }
            }
            for (x = 0; x < sizex; x ++) {
                if (world[sizey - 1][x] == enemy) {
                    victory = 0;
                }
            }
        }
                
        /*control player*/
        if(kbhit()){
            keyPress = getch();
        }
        else {
            keyPress = ' ';
        }   
        if (keyPress == 'A' || keyPress == 'a') {
            for (x = 0; x < sizex; x = x+1) {
                if ( world[sizey-1][x+1] == player) {
                    world[sizey-1][x] = player;
                    world[sizey-1][x+1] = ' ';
                }
            }
        }

        if (keyPress == 'D' || keyPress == 'd') {
            for (x = sizex - 1; x > 0; x = x-1) {
                if ( world[sizey-1][x-1] == player) {
                    world[sizey-1][x] = player;
                    world[sizey-1][x-1] = ' ';
                }
            }
        }
        if (keyPress == 'M' || keyPress == 'm' && laserReady > 2) {
            for (x = 0; x < sizex; x = x+1) {
                if ( world[sizey-1][x] == player) {
                    world[sizey - 2][x] = playerLaser;
                    laserReady = 0;
                }
            }    // Easter Egg :-> To make the game easy activate the caps lock. It will make your weapon more powerful.
        }
        i ++;
        Sleep(50);
    }                     
    system("cls");         // It clears the screen.
        printf("     SCORE:    %d", score);
        printf("\n");
            for (y = 0; y < sizey; y ++) {
            printf("|");
                for (x = 0; x < sizex; x ++) {
                    printf("%c",world[y][x]);
                }
            printf("|");
            printf("\n");
            }
            
    Sleep(1000);    // It stops the execution for a specified time.
    system("cls");  
    if (victory != 0) {   system("color 09") ;
        printf("\n \n \n \n \n \n               CONGRATULATIONS!");
        Sleep(1000);
        printf(" CYBERLORD \n \n \n");
        Sleep(1000);
        printf("\n \n               Score: %d", score);
        Sleep(1000);
        int bonus = totalEnemies*20 - i;
        printf("\n \n               Bonus: %d", bonus);
        Sleep(1000);
        printf("\n \n               Total Score: %d", score + bonus);
        Sleep(4000);
        system("exit") ;  // It closes the program.
    }
    else {    
	       system("color 0C") ;   // It changes background and foreground color.
           printf("\n \n \n \n \n \n               You have failed.");
           Sleep(1000);
           printf("\n \n \n \n               They corrupted everything.");
           Sleep(2000);
           printf("\n \n \n \n              Final Score: %d", score);
           Sleep(1500) ;
           ques () ;    // Calls function ques.
       }
    
}   // End of main.

  void ques()    // Function Declaration
    { 
	   loop:   // Label
	    char answer ;
		printf("\n Do you want to restart(Y/N)") ;
        scanf("%s", &answer);    // It is used to take input from user.
        if (answer=='Y' or answer=='y') 
        { 
          system("cls") ;  // It clears the screen.
          main () ;       // Calls main function
		  
		}
		else if(answer=='N' or answer=='n')
		{  
		  system("exit");   // It closes the program.
		}
		else
		{ 
		  printf("\n Wrong Choice\n") ;
		  goto loop ;  // Jumps to specified label.
		}
    }       
                                                       /* END */
