//
// Created by anon on 15.07.2020.
//
#include "snake.h"

/*Yeah, its defenition of global classes*/
Snake snke;
Fruits frt[MAX_FRT_SIZE];

/*******************************************************/
void Display()
{

    glClear(GL_COLOR_BUFFER_BIT);

    snke.Draw_Field();
    snke.Draw_Snake();

    for (int i = 0; i < MAX_FRT_SIZE; ++i)
    {
        frt[i].Draw_apple();
    }

    glFlush();
    glutSwapBuffers();
}


void Timer(int value)
{
    Display();

    snke.Moving();

    glutTimerFunc(SPEED_OF_THE_GAME, Timer, 0);
}


void MyKeyboard(int key, int param_1, int param_2)
{
    switch(key)
    {
        case 100: snke.dir = LEFT;
            break;

        case 101: snke.dir = UP;
            break;

        case 102: snke.dir = DOWN;
            break;

        case 103: snke.dir = RIGHT;
            break;

        default: printf("Unrecognized command\n");
            abort();
    }
}

/*****************************************************/

Snake::Snake() : size(START_SNK_SIZE)
{
    snk = new struct points[MAX_SNK_SIZE];

    snk[0].point_x = 10;
    snk[0].point_y= 10;
}

Snake::~Snake()
{
    delete[] snk;
}


void Snake::Draw_Field()
{
    int i = 0, j = 0;

    glColor3f(0.0, 10.0, 1.0);
    glBegin(GL_LINES);

    for (i = 0; i < WIDTH; i+= SCALE)
    {
        glVertex2f(i,0);
        glVertex2f(i,HEIGTH);
    }

    for (j = 0; j < HEIGTH; j+=SCALE)
    {
        glVertex2f(0, j);
        glVertex2f(WIDTH, j);
    }

    glEnd();
}


void Snake::Moving()
{
    int i = 0;

    for (i = size; i > 0; i--)
    {
        snk[i].point_x = snk[i-1].point_x;
        snk[i].point_y = snk[i-1].point_y;
    }

    switch(dir)
    {
        case UP: snk[0].point_y++;
            break;

        case LEFT: snk[0].point_x--;
            break;

        case RIGHT: snk[0].point_y--;
            break;

        case DOWN: snk[0].point_x++;
            break;

        default: printf("Error in the func moving!\n");
            abort();
    }

    for (i = 0; i < MAX_FRT_SIZE; i++)
    {
        if ((snk[0].point_x == frt[i].frts.point_x) && (snk[0].point_y == frt[i].frts.point_y))
        {
            size++;
            frt[i].New_Fruit();
        }
    }

    if (snk[0].point_x > NUM_FOR_W)
    {
        dir = 1;
        size = START_SNK_SIZE;
    }
    else if (snk[0].point_x < 0)
    {
        dir = 2;
        size = START_SNK_SIZE;
    }
    else if (snk[0].point_y > NUM_FOR_H)
    {
        dir = 3;
        size = START_SNK_SIZE;
    }
    else if (snk[0].point_y < 0)
    {
        dir = 0;
        size = START_SNK_SIZE;
    }

    for (i = 1; i < size; ++i)
    {
        if ((snk[0].point_x == snk[i].point_x) && (snk[0].point_y == snk[i].point_y))
        {
            size = START_SNK_SIZE;
        }
    }

}

void Snake::Draw_Snake()
{
    int i = 0;

    glColor3f(1.0, 1.0, 0.0);

    for (i = 0; i < size; i++)
    {
        glRectf((snk[i].point_x)*SCALE, (snk[i].point_y)*SCALE, (snk[i].point_x+0.9)*SCALE, (snk[i].point_y+0.9)*SCALE);
    }
}

/**********************************************************/

Fruits::Fruits()
{
    for (int i = 0; i < MAX_FRT_SIZE; ++i)
    {
        frt[i].New_Fruit();
    }
}


void Fruits::New_Fruit()
{
    frts.point_x = rand() % NUM_FOR_W;
    frts.point_y = rand() % NUM_FOR_H;
}

void Fruits::Draw_apple()
{
    glColor3f(5.0, 0.0, 0.0);
    glRectf(frts.point_x*SCALE,  frts.point_y*SCALE, (frts.point_x+1)*SCALE, (frts.point_y + 1)*SCALE);
}




