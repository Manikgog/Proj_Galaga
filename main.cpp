#include <iostream>    // управление стрелочками на клавиатурe:
#include "windows.h"   // вверх, вниз, вправо, влево
#include "conio.h"
#include "ctime"

using namespace std;

const int LINES = 30;
const int COLS = 41;
int point = 10;
char pole[LINES][COLS];
const int number_of_ships = 5;

void gotoxy(int xpos, int ypos) // переход курсора в точку с координатами xpos, ypos
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}

void poleConstruct() {

    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLS; j++) {
            pole[i][j] = '\0';
        }
    }

    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLS; j++) {
            if (j == 10 || j == 40) {
                pole[i][j] = '#';
            }
            else if ((i == 0 || i == 29) && (j >= 10 && j <= 40)) {
                pole[i][j] = '#';
            }
            else {
                pole[i][j] = ' ';
            }
        }
    }
}

void conclusionPole() // вывод поля со счётом
{
    gotoxy(0, 0);
    cout << endl << pole;
    /*gotoxy(58, 2);
    cout << "Score = " << point;*/
}

struct ship {
    int x = 0;
    int y = 0;
};

int main()
{
   srand(time(NULL));
   poleConstruct();
   char click;
   int x = 25, y = 28;
   ship ships[5]{};
   bool gameOver = 0;
   

   for (int cols = 0; cols < 120; cols++) {
       for (int rows = 0; rows < 30; rows++) {
           if (cols == 10 || cols == 40) {

               gotoxy(cols, rows);
               cout << '#';
           }
           else if ((rows == 0 || rows == 29) && (cols >= 10 && cols <= 40)) {
               gotoxy(cols, rows);
               cout << '#';
           }
           else {
               gotoxy(cols, rows);
               cout << ' ';
           }
          
       }
      
   }
   
   for (int i = 0; i < number_of_ships; i++) {
       ships[i].x = rand() % 30 + 10;
       ships[i].y = rand() % 5 - 5;
   }

   while (!gameOver) {
       poleConstruct();
       //if (_kbhit()) { _getch(); } // считывание 224 перед направлением
       
       if (_kbhit()) // считывание направления
       {
           click = _getch();
            if (click == 65 || click == 97)//влево
           {
                gotoxy(x, y);
                cout << ' ';
                pole[y][x] = ' ';
                x--;
               if (x == 10)
                   x = 11;

               pole[y][x] = 'A';
               gotoxy(x, y);
               cout << 'A';
           }
           else if (click == 68 || click == 100)//вправо
           {
                gotoxy(x, y);
                cout << ' ';
                pole[y][x] = ' ';
                x++;
               if (x == 40)
                   x = 39;
               pole[y][x] = 'A';
               gotoxy(x, y);
               cout << 'A';
            }
           else if (click == 's' || click == 'S') {
                for (int i = 1; i < y; i++) {
                    gotoxy(x, i);
                    cout << 'I';
                    for (int j = 0; j < number_of_ships; j++) {
                        if (x == ships[j].x) {
                            gotoxy(ships[i].x, ships[i].y);
                            cout << ' ';
                            ships[i].x = rand() % 30 + 10;
                            ships[i].y = 0;
                        }
                    }
                }
                Sleep(100);
                for (int i = 1; i < y; i++) {
                    gotoxy(x, i);
                    cout << ' ';
                }
           }

       }
       
        for (int i = 0; i < number_of_ships; i++) {
            if (ships[i].y < 0) {
                ships[i].y++;
            }
            else {

                gotoxy(ships[i].x, ships[i].y);
                cout << ' ';

                gotoxy(ships[i].x, ++ships[i].y);
                cout << 'X';
            }
            if (ships[i].y + 1 == LINES - 1) {
                gameOver = 1;
            }
        }
           



       
       Sleep(500);

   }

    return 0;
}
