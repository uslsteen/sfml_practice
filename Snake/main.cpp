#include "snake.h"

int main(int argc, char** argv)
{
    srand(time(0));

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGTH);


    glutCreateWindow("Snake");
    glClearColor(10.0, 10.0, 100.0, 100.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, WIDTH, 0, HEIGTH);

    glutDisplayFunc(Display);
    glutSpecialFunc(MyKeyboard);
    glutTimerFunc(SPEED_OF_THE_GAME, Timer, 0);

    glutMainLoop();

    return 0;
}




