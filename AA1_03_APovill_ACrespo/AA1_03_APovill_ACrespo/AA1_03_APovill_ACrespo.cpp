#include "Zuma.h"

/*
Implementar un struct Player. La implementación debe incluir:
    a. Todos los miembros (atributos) necesarios para mantener la información de un jugador. Es
    especialmente importante pensar en cómo se representa a la pistola.
    b. Un método void init(std::string name, int position), que inicializa al
    jugador poniéndole como su identificador a name y colocándolo en la position dada,
    inicializa el score en 0 y carga a la pistola con 30 bolas aleatorias.
    c. Un método Ball shoot(): Dispara 1 bola, la primera que tiene. La bola se elimina del
    cargador y la función la devuelve.

*/

void RestructArray(Ball* panel, int size)
{
    int a = -1;
    int b, c;
    for (int i = 0; i < size; i++)
    {
        if (a == -1)
        {
            if (panel[i] == Ball::X)
            {
                a = i;
                b = i + 1;
                c = i + 2;
                i = c;
            }
        }
        else if (c < size)
        {
            panel[a] = panel[i];
            panel[b] = panel[i + 1];
            panel[c] = panel[i + 2];
            a = i;
            b = i + 1;
            c = i + 2;
            i = c;
        }
        else if (b < size)
        {
            panel[a] = panel[i];
            panel[b] = panel[i + 1];
            a = i;
            b = i + 1;
            i = b;
        }
        else
        {
            panel[a] = panel[i];
        }
    }
}


void PrintScreen(Player player, Panel panel, char* pos)
{
    system("cls");
    panel.printPanel();
    std::cout << std::endl;
    for (int i = 0; i < panel.size; i++)
    {
        std::cout << pos[i];
    }
    std::cout << std::endl;
    for (int i = 0; i < player.ammo; i++)
    {
        switch (player.gun[i])
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
    std::cout << std::endl;
}

int main()
{
    srand(time(NULL));
    Panel panel;
    panel.init();
    Player player;
    int pPosSize = panel.size;
    player.init("player", pPosSize / 2);
    char* position = new char[pPosSize];
    player.SetPos(position, pPosSize);

    while (player.ammo > 0)
    {
        PrintScreen(player, panel, position);
        char input;
        std::cout << "\nDEBUG: Ammo = " << player.ammo << ", Gun[0] = " << (int)player.gun[0] << " panelSize " << panel.size << " posSize " << pPosSize << " pPos= " << player.pos << std::endl;
        std::cin >> input;
        //for (int i = 0; i < panel.size; i++)
        //{
        //    panel.verifier(i, panel.panel[i]);
        //}

        if ((input == 'd' || input == 'D') && player.pos < pPosSize - 1)
        {
            player.pos++;
        }
        else if ((input == 'a' || input == 'A') && player.pos > 0)
        {
            player.pos--;
        }
        else if (input == 'w' || input == 'W')
        {
            panel.resizePanel();
            pPosSize = panel.size;
            panel.insert(player.pos, player.shoot());         
        }
        player.SetPos(position, pPosSize);
    }
    delete[] panel.panel;
    delete[] player.gun;
    delete[] position;
}
