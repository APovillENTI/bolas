#pragma once
#include <windows.h>
#include <iostream>

const int PLAYER_AMMO = 30;

enum class Ball
{
    G,
    R,
    Y,
    O,
    B,
    X
};

Ball* ResizeArray(Ball* original, int oldSize, int newSize);

void RestructArray(Ball* panel, int size);

struct Player
{
    std::string pName;
    int pos;
    char symbol;
    int score;
    int ammo = PLAYER_AMMO;
    Ball* gun = new Ball[ammo];

    void init(std::string name, int position)
    {
        pName = name;
        pos = position;
        symbol = '^';
        score = 0;
        ammo = PLAYER_AMMO;
        for (int i = 0; i < ammo; i++)
        {
            gun[i] = (Ball)(rand() % 5);
        };
    }

    void SetPos(char* position, int size)
    {
        for (int i = 0; i < size; i++)
        {
            if (i == pos)
            {
                position[i] = symbol;
            }
            else
            {
                position[i] = ' ';
            }
        }
    }

    Ball shoot()
    {
        Ball ball = gun[0];
        gun = ResizeArray(gun, ammo, ammo-1);
        ammo--;
        return ball;
    }
};

struct Panel
{
    int size; //representa en todo momento el tamaño del panel
    Ball* panel;

    void init() //Inicializa al panel con un número aleatorio de bolas aleatorias que es leído del estándar input
    {
        std::cout << "Cuantas bolas quieres que te aparescan? ";
        std::cin >> size;
        system("cls");
        panel = new Ball[size];

        panel[0] = (Ball)(rand() % 5);
        Ball ball = panel[0];
        for (int i = 1; i < size; i++)
        {
            do
            {
                panel[i] = (Ball)(rand() % 5);
            } while (ball == panel[i]);
            ball = panel[i];
        }
    }

    void insert(int position, Ball ball) //Inserta la bola ball en el panel de bolas en la posición indicada.La inserción la realiza desplazando a la derecha las bolas.
    {
        for (int i = size - 1; i > position; i--)
        {
            panel[i] = panel[i - 1];
        }
        panel[position] = ball;
        int mostLeft = verifier(position, ball);
        if (mostLeft != -1)
        {
            deleteThree(mostLeft);
        }
    }

    int verifier(int position, Ball ball) const /*Verifica si alrededor de la position hay una secuencia de 3 bolas consecutivas iguales a ball.
    Debe retornar un valor que indique dónde está la primera bola de las 3, en caso de existir 3. Si no hay 3 consecutivas, el valor de retorno lo debe indicar de alguna manera.*/
    {
        int count = 1;
        int left = position - 1;
        int right = position + 1;

        // Busca hacia la izquierda
        while (left >= 0 && panel[left] == ball) {
            count++;
            left--;
        }

        // Busca hacia la derecha
        while (right < size && panel[right] == ball) {
            count++;
            right++;
        }

        if (count >= 3) {
            return left + 1; // Devuelve la posición de la primera bola de la secuencia
        }

        return -1; // No hay 3 consecutiva
    }

    void resizePanel() //Modifica el tamaño de bolas que pueden haber en el panel en base a newSize.
    {
        Ball* nuevoArray = new Ball[size + 1];
        // Copiar los elementos antiguos (hasta el menor tamaño)
        for (int i = 0; i < size; i++) {
            nuevoArray[i] = panel[i];
        }
        nuevoArray[size] = Ball::X;
        delete[] panel;
        size++;
        panel = new Ball[size];
        for (int i = 0; i < size; i++)
            {
                panel[i] = nuevoArray[i];
            }
            delete[] nuevoArray;     
    }

    void deleteThree(int position) //Elimina 3 bolas consecutivas del panel a partir de la position dada.
    {
        for (int i = position; i < size - 3; ++i) {
            panel[i] = panel[i + 3];
        }
        insertThree();
    }

    void insertThree() //Inserta 3 bolas aleatorias en el panel por el final.
    {
        panel[size - 3] = (Ball)(rand() % 5);
        do
        {
            panel[size - 2] = (Ball)(rand() % 5);
        } while (panel[size - 2] == panel[size - 1]);

        panel[size - 1] = (Ball)(rand() % 5);
    }

    void printPanel() //Un método que imprima las bolas que hay en el panel.
    {
        for (int i = 0; i < size; i++)
        {
            switch (panel[i])
            {
            case Ball::G:
                std::cout << 'G';
                break;
            case Ball::R:
                std::cout << 'R';
                break;
            case Ball::Y:
                std::cout << 'Y';
                break;
            case Ball::O:
                std::cout << 'O';
                break;
            case Ball::B:
                std::cout << 'B';
                break;
            }
        }
    }
};

void PrintScreen(Player player, Panel panel, char* pos);

