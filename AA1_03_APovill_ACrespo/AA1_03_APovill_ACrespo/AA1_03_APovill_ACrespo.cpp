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

//void RestructArray()

Ball* ResizeArray(Ball* original, int oldSize, int newSize) {
    Ball* nuevoArray = new Ball[newSize];

    // Copiar los elementos antiguos (hasta el menor tamaño)
    for (int i = 0; i < newSize; i++) {
        nuevoArray[i] = original[i];
    }

    // Liberar memoria del array antiguo
    delete[] original;

    return nuevoArray;
}

void PrintScreen(Player player, Panel panel, char* pos)
{
    system("cls");
    panel.printPanel();
    std::cout << std::endl;
    std::cout << std::endl;
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
    //if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
    //{
    //    Ball shoot(Player player);
    //}
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
        std::cin >> input;
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
            panel.resizePanel(panel.size + 1);

            player.shoot();
        }
        player.SetPos(position, pPosSize);
    }
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
