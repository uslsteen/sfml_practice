//
// Created by anon on 15.07.2020.
//
#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <time.h>
#include <assert.h>


/*enum for params of my game*/
enum Params_of_the_game
{
    NUM_FOR_W = 64, //num of squares in width
    NUM_FOR_H = 36, //num of square in heigth
    SCALE = 32,     //just scale
    WIDTH = NUM_FOR_W*SCALE,
    HEIGTH = NUM_FOR_H*SCALE,
    MAX_FRT_SIZE = 40,
    MAX_SNK_SIZE = 100,
    SPEED_OF_THE_GAME = 75,
    START_SNK_SIZE = 4,
};

enum DIRECTIONS
{
    UP = 0,
    LEFT = 1,
    DOWN = 2,
    RIGHT = 3
};


/*struct for*/

struct points
{
    int point_x;
    int point_y;
};

class Fruits
{
    /*for variables*/
public:
    struct points frts;

    /*for func*/
public:

    Fruits();

    void New_Fruit();
    void Draw_apple();
};

/*Class for my snake*/

class Snake
{
    /*for variables*/
public:

    int dir;

private:

    struct points* snk;
    int size;

//private:

    /*for func*/
public:

    Snake();
    ~Snake();

public:
    void Draw_Field();

    void Moving();

    void Draw_Snake();

//private:

};


/*Common func for working with glut glut*/

void Display();

void Timer(int value);

void MyKeyboard(int key, int param_1, int param_2);


#endif //SNAKE_SNAKE_H
