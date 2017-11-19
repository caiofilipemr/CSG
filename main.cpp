#include <GL/glut.h>

#define ROTATION_SENSIBILITY 5.0

GLfloat xRotation;
GLfloat yRotation;
GLfloat lightPosition[] = {-25.f, 0.f, 50.f, 1.f};
int initialX;
int initialY;
int pressedButton;

void clearBuffers() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void drawCube() {
    glPushMatrix();
    glTranslatef(-10, 0, 0);
    glRotatef(xRotation, 1, 0, 0);
    glRotatef(yRotation, 0, 1, 0);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(5);
    glPopMatrix();
}

void drawSphere() {
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(xRotation, 1, 0, 0);
    glRotatef(yRotation, 0, 1, 0);
    glColor3f(0.0, 1.0, 0.0);
    glutSolidSphere(2.5, 40, 40);
    glPopMatrix();
}

void drawCone() {
    glPushMatrix();
    glTranslatef(10, 0, 0);
    glRotatef(xRotation, 1, 0, 0);
    glRotatef(yRotation, 0, 1, 0);
    glColor3f(0.0, 0.0, 1.0);
    glutSolidCone(2.5, 2.5, 40, 40);
    glPopMatrix();
}

void draw() {
    clearBuffers();
    drawCube();
    drawSphere();
    drawCone();
    glutSwapBuffers();
}

void definePerspective() {
    glMatrixMode(GL_PROJECTION);
    glOrtho(-15, 15, -15, 15, -15, 15);
    glMatrixMode(GL_MODELVIEW);
}

void mouseClick(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        initialX = x;
        initialY = y;
        pressedButton = button;
    } else {
        pressedButton = -1;
    }
}

void mouseMove(int x, int y) {
    if (pressedButton == GLUT_LEFT_BUTTON) {
        int deltaX = initialX - x;
        int deltaY = initialY - y;
        xRotation = xRotation - deltaY / ROTATION_SENSIBILITY;
        yRotation = yRotation - deltaX / ROTATION_SENSIBILITY;

        initialX = x;
        initialY = y;
    }
    glutPostRedisplay();
}

void defineCallbacks() {
    glutDisplayFunc(draw);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);
}

void defineWindowConfiguration() {
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_STENCIL | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("CSG OpenGL");
    glClearColor(1, 1, 1, 0);
}

void defineLightConfiguration() {
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);
}

void init() {
    defineWindowConfiguration();
    definePerspective();
    defineCallbacks();
    defineLightConfiguration();
    glutMainLoop();
}

int main (int argc, char **argv) {
    glutInit(&argc, argv);
    init();
    return 0;
}