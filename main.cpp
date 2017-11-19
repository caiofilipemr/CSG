#include <GL/glut.h>

GLfloat xRotation;
GLfloat yRotation;
GLfloat zRotation;
GLfloat lightPosition[] = {-25.f, 0.f, 50.f, 1.f};

void clearBuffers() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void setViewAngle() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(xRotation, 1, 0, 0);
    glRotatef(yRotation, 0, 1, 0);
    glRotatef(zRotation, 0, 0, 1);
}

void firstInsideSecond(void(*drawFirstObject)(void), void(*drawSecondObject)(void), GLenum face, GLenum test)
{
    glEnable(GL_DEPTH_TEST);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glCullFace(face); /* controls which face of a to use*/
    drawFirstObject(); /* draw a face of a into depth buffer */

    /* use stencil plane to find parts of a in b */
    glDepthMask(GL_FALSE);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 0, 0);
    glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
    glCullFace(GL_BACK);
    drawSecondObject(); /* increment the stencil where the front face of b is drawn */
    glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
    glCullFace(GL_FRONT);
    drawSecondObject(); /* decrement the stencil buffer where the back face of b is drawn */
    glDepthMask(GL_TRUE);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

    glStencilFunc(test, 0, 1);
    glDisable(GL_DEPTH_TEST);

    glCullFace(face);
    drawFirstObject(); /* draw the part of a that's in b */
    glDisable(GL_STENCIL_TEST);
}

void fixDepth(void(*drawObject)(void))
{
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
    drawObject();
    glDepthFunc(GL_LESS);
    glDisable(GL_DEPTH_TEST);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

void drawCube() {
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(5);
    glPopMatrix();
}

void drawSphere() {
    glPushMatrix();
    glTranslatef(2.5f, 2.5, 2.5);
    glColor3f(0.0, 1.0, 0.0);
    glutSolidSphere(2.5, 40, 40);
    glPopMatrix();
}

void drawCone() {
    glPushMatrix();
    glRotatef(270, 1, 0, 0);
    glTranslatef(0, 0, -3);
    glColor3f(0.0, 0.0, 1.0);
    glutSolidCone(2.5, 8, 40, 40);
    glPopMatrix();
}

void _union(void(*drawFirstObject)(void), void(*drawSecondObject)(void)) {
    glEnable(GL_DEPTH_TEST);
    drawFirstObject();
    drawSecondObject();
    glDisable(GL_DEPTH_TEST);
}

void intersection(void(*drawFirstObject)(void), void(*drawSecondObject)(void)) {
    firstInsideSecond(drawFirstObject, drawSecondObject, GL_BACK, GL_NOTEQUAL);
    fixDepth(drawSecondObject);
    firstInsideSecond(drawSecondObject, drawFirstObject, GL_BACK, GL_NOTEQUAL);
}

void subtraction(void(*drawFirstObject)(void), void(*drawSecondObject)(void)) {
    firstInsideSecond(drawFirstObject, drawSecondObject, GL_FRONT, GL_NOTEQUAL);
    fixDepth(drawSecondObject);
    firstInsideSecond(drawSecondObject, drawFirstObject, GL_BACK, GL_EQUAL);
}

void draw() {
    clearBuffers();
    setViewAngle();
    _union(drawCube, drawCone);
    glutSwapBuffers();
}

void definePerspective() {
    glMatrixMode(GL_PROJECTION);
    glOrtho(-15, 15, -15, 15, -15, 15);
    glMatrixMode(GL_MODELVIEW);
}

void mouseClick(int button, int state, int x, int y) {
}

void mouseMove(int x, int y) {
}

void keyboardKeys(unsigned char key, int, int) {
    switch (key) {
        case ',':
            zRotation += 1;
            break;
        case '.':
            zRotation -= 1;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void keyboardSpecialKeys(int key, int, int) {
    switch (key) {
        case GLUT_KEY_LEFT:
            yRotation -= 1;
            break;
        case GLUT_KEY_RIGHT:
            yRotation += 1;
            break;
        case GLUT_KEY_UP:
            xRotation -= 1;
            break;
        case GLUT_KEY_DOWN:
            xRotation += 1;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void defineCallbacks() {
    glutDisplayFunc(draw);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);
    glutKeyboardFunc(keyboardKeys);
    glutSpecialFunc(keyboardSpecialKeys);
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

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    init();
    return 0;
}