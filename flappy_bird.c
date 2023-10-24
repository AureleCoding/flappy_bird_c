#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define WINDOW_HEIGHT 30
#define WINDOW_WIDTH 60
#define TUBE_WIDTH 4
#define TUBE_HOLE 4
#define GRAVITY 1

int tubeX, birdY, holePos, birdVelocity, end, count;

void init()
{
    tubeX = WINDOW_WIDTH;
    birdY = WINDOW_HEIGHT / 2;
    holePos = WINDOW_HEIGHT / 2 - TUBE_HOLE;
    birdVelocity = 0;
    end = 0;
    count = 0;
}

void clean_stdin(void)
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void window()
{
    for (int i = 0; i < WINDOW_HEIGHT; i++)
    {
        for (int j = 0; j < WINDOW_WIDTH; j++)
        {
            if (j > tubeX && j <= tubeX + TUBE_WIDTH && (i < holePos || i > holePos + TUBE_HOLE))
            {
                putchar('#');
            }
            else if (j == WINDOW_WIDTH / 2 && i == birdY)
            {
                putchar('>');
            }
            else
            {
                putchar(' ');
            }
        }
        putchar('\n');
    }
}

void score()
{
}

void input()
{
    if (_kbhit())
    {
        char key = _getch();
        if (key == ' ')
        {
            birdVelocity = -3;
        }
    }
}

void update()
{
    system("cls");
    tubeX--;

    birdVelocity += GRAVITY;
    birdY += birdVelocity;

    if (birdY >= WINDOW_HEIGHT)
    {
        birdY = WINDOW_HEIGHT - 1;
        birdVelocity = 0;
    }

    if (tubeX < -TUBE_WIDTH)
    {
        tubeX = WINDOW_WIDTH + TUBE_WIDTH;
        holePos = rand() % (WINDOW_HEIGHT - 5 - TUBE_HOLE - 1) + 5;
    }

    if (WINDOW_WIDTH / 2 == tubeX)
    {
        if (birdY > holePos && birdY < holePos + TUBE_HOLE)
        {
            count++;
        }
        else
        {
            end = 1;
        }
    }

    printf("Score : %d", count);
}

int main()
{
    srand(time(NULL));
    init();

    printf("Press ENTER to begin the game!");
    while (getchar() != '\n')
    {
    }

    while (!end)
    {
        input();
        update();
        window();
        Sleep(50);
    }

    printf("\nGame Over! Your Score: %d\n", count);

    printf("Press ENTER to restart the game!");
    while (getchar() != '\n')
    {
    }

    init();
    return 0;
}
