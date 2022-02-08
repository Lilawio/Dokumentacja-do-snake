#include <iostream>
#include <stdio.h>
#include <random>
#include <chrono>
#include <thread>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include "windows.h" 

using namespace std;
const int wysokosc = 20;
const int szerokosc = 20;
char** tablica = new char* [20];
char kierunek = 'o';
int dł = 1;
int speed = 1*100;//1-10 (1 szybko, 10 wolno)
void HideCursor()//nie pytaj jak co (stack overflow)
{
    ::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    ::CONSOLE_CURSOR_INFO hCCI;
    ::GetConsoleCursorInfo(hConsoleOut, &hCCI);
    hCCI.bVisible = FALSE;
    ::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}
int start()
{
    srand((unsigned int)time(NULL));
    int rng = rand() % 18 + 1;
    return rng;
}

int x = start();
int y = start();
void kursor_usun(int x, int y)
{
    COORD c;
    c.X = y;
    c.Y = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    cout<< ' ';
    HideCursor();
}
void kursor_napisz(int x, int y)
{
    COORD c;
    c.X = y;
    c.Y = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    cout<< 'O';
    HideCursor();
}
void wypisz()//tło
{
    for (int i = 0; i < wysokosc; i++)
    {
        for (int j = 0; j < szerokosc; j++)
        {
            cout << tablica[i][j];
        }
        cout << endl;
    }
}
void plansza()//rysowanie planszy
{
    for (int i = 0; i < wysokosc; i++)
    {
        tablica[i] = new char[20];
    }
    for (int i = 0; i < wysokosc; i++)
    {
        for (int j = 0; j < szerokosc; j++)
        {
            if (i == 0 or i == wysokosc - 1)
            {
                tablica[i][j] = '-';
            }
            if (j == 0 or j == szerokosc - 1 and i != 0 and i != wysokosc - 1)
            {
                if (i == 0 or i == wysokosc - 1)
                {
                    continue;
                }
                tablica[i][j] = '|';
            }
            else if (j > 0 and j < wysokosc - 1 and i != 0 and i != wysokosc - 1)
            {
                tablica[i][j] = ' ';
            }
        }
    }
}
void sterowanie()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a': 
            kierunek = 'a';
            break;
        case 'w':
            kierunek = 'w';
            break;
        case 's':
            kierunek = 's';
            break;
        case 'd':
            kierunek = 'd';
            break;
        }
    }
}
int kxowoc{};
int kyowoc{};
int owocek(int a, int b)
{
    a = start();
    b = start();
    COORD v;
    v.X = a;
    v.Y = b;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), v);
    cout <<'+';
    HideCursor();
    kxowoc = a;
    kyowoc = b;
    return 0;
}
void przedluz(int dł, int wazx[], int wazy[],int x, int y)
{ 
    wazx[dł] = x;
    wazy[dł] = y;
    kursor_usun(wazx[0], wazy[0]);
    for (int i = 0; i < dł; i++)
    {
        wazx[i] = wazx[i + 1];
        wazy[i] = wazy[i + 1];
    }
}
bool lose(int dł,int wazx[], int wazy[], int x, int y)
{
    for (int i = 3; i <= dł; i++)
    {
        if (dł>4 and x == wazx[i] and y == wazy[i])
        {
            return true;
            break;
        }
        return false;
    }
}
char przeciwnoscilosu(char kierunek, char prz)
{
    if (kierunek == 'a' and prz == 'd')
    {
        kierunek = 'd';
    }
    else if (kierunek == 'd' and prz == 'a')
    {
        kierunek = 'a';
    }
    else if (kierunek == 's' and prz == 'w')
    {
        kierunek = 'w';
    }
    else if (kierunek == 'w' and prz == 's')
    {
        kierunek = 's';
    }
    return kierunek;
}
void gra()
{
    int wazx[400] = {};
    int wazy[400] = {};
    char prz = ' ';
    plansza();
    bool koniec = false;
    tablica[x][y] = 'O';
    wypisz();
    owocek(kxowoc, kyowoc);
    dł = 1;
    while (koniec != true)
    {
        prz = kierunek;
        sterowanie();
        kierunek = przeciwnoscilosu(kierunek, prz);
        koniec = lose(dł, wazx, wazy, x, y);
        Sleep(200);
        if (x == kxowoc and y == kyowoc)
        {
            owocek(kxowoc, kyowoc);
            dł++;
        }
        if (kierunek == 'a')
        {
            y--;
            if (y == 0)
            {
                y = 18;
            }
            kursor_napisz(x, y);
        }
        else if (kierunek == 'w')
        {
            x--;
            if (x == 0)
            {
                x = 18;
            }
            kursor_napisz(x, y);
        }
        else if (kierunek == 's')
        {
            x++;
            if (x == 19)
            {
                x = 1;
            }
            kursor_napisz(x, y);
        }
        else if (kierunek == 'd')
        {
            y++;
            if (y == 19)
            {
                y = 1;
            }
            kursor_napisz(x, y);
        }
        koniec = lose(dł, wazx, wazy, x, y);
        przedluz(dł, wazx, wazy, x, y);
    }
    char odp = 'N';
    cout << endl << endl << endl << endl << endl<< endl << endl << endl << endl << endl << endl << endl << endl<<endl<<endl;
    cout << "PRZEGRALES" << endl;
    cout << "Gramy od nowa? (T/N) ";
    cin >> odp;
    if (odp == 'T')
    {
        system("cls");
        plansza();
        gra();
    }
    else
    {
        cout << "Dzięki za grę";
    }
}
int main()
{
    gra();
}