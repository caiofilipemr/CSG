#include <stdlib.h>
#include <GL/glut.h>

GLsizei WIDTH = 600, HEIGHT = 600;
GLsizei MOUSEx, MOUSEy;
GLfloat SIDE = 1;

GLfloat RED[3] = {1,0,0};
GLfloat GREEN[3] = {0,1,0};
GLfloat BLUE[3] = {0,0,1};
GLfloat WHITE[3] = {1,1,1};
GLfloat BLACK[3] = {0,0,0};
GLfloat YELLOW[3] = {1,1,0};
GLfloat CYAN[3] = {0,1,1};
GLfloat MAGENTA[3] = {1,0,1};

void display (void) {
    glClearColor(1.0,1.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-0.5, -0.5, 0.0);
    glFlush();
}

void drawPoint(int x, int y) {

}

void mouse(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {

    }
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) {
        exit(1);
    }
}

int main (int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("New Window");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}