#include <GL\glut.h>
#include "Segments.h"

const GLint WinW = 830, WinH = 600;

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(WinW, WinH);
    glutInitWindowPosition(300, 80);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Segment generation by Amalia D.");
    glClearColor(255, 255, 255, 255);
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutIdleFunc(Idle);
    glutMainLoop();
    return 0;
}