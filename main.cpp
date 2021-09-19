#include <iostream>
#include <cmath>
#include <gl\glut.h>

using namespace std;

GLint WinW = 800, WinH = 600;
int step = 20;
int X1 = 0, Y1 = 0, X2 = 10, Y2 = -4;

int sign(double a) {
    if (a > 0) return 1;
    if (a < 0) return -1;
    return 0;
}

void paintPixel(double x, double y, int Red, int Green, int Blue) {
    glColor3d(Red, Green, Blue);
    glBegin(GL_QUADS);
    glVertex2d(x, y);
    glVertex2d(x + step, y);
    glVertex2d(x + step, y + step);
    glVertex2d(x, y + step);
    glEnd();
}

void DrawDDALine(int x1, int x2, int y1, int y2) {
    double dx, dy, x, y, length;

    if (abs(x2 - x1) >= abs(y2 - y1))
        length = abs(x2 - x1);
    else
        length = abs(y2 - y1);

    dx = (x2 - x1) / length;
    dy = (y2 - y1) / length;
    x = (float) x1 + 0.5 * sign(dx);
    y = (float) y1 + 0.5 * sign(dy);

    for (int i = 1; i <= length; i++) {
        paintPixel(floor(x) * step, floor(y) * step, 1, 0, 1);
        x += dx;
        y += dy;
    }
    glEnd();
}

void DrawBrezehamLine(int x1, int x2, int y1, int y2) {
    int x, y, dx, dy, sx, sy;

    x = x1, y = y1;
    dx = abs(x2 - x1), dy = abs(y2 - y1);
    sx = sign(x2 - x1), sy = sign(y2 - y1);
    bool swap = false;

    if (dx < dy) {
        std::swap(dx, dy);
        swap = true;
    }
    int eps = 2 * dy - dx;

    for (int i = 0; i < dx; i++) {
        paintPixel(x * step, y * step, 1, 5, 0);
        while (eps >= 0) {
            if (swap)
                x += sx;
            else
                y += sy;
            eps -= (2 * dx);
        }
        if (swap)
            y += sy;
        else
            x += sx;
        eps += (2 * dy);
    }
    glEnd();
}

void realLine(double x1, double x2, double y1, double y2) {
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3d(0, 2, 0);
    glVertex2d(x1 * step, y1 * step);
    glVertex2d(x2 * step, y2 * step);
    glEnd();

}
void DrawGrid() {
    glLineWidth(1);
    glColor3d(0, 0, 0);
    glBegin(GL_LINES);
    for (int i = -WinW / 2; i <= WinW / 2; i += step) {
        glVertex2d(i, WinH / 2);
        glVertex2d(i, -WinH / 2);
    }
    for (int i = -WinH / 2; i <= WinH / 2; i += step) {
        glVertex2d(WinW / 2, i);
        glVertex2d(-WinW / 2, i);
    }
    glEnd();
    glLineWidth(3);
    glColor3d(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-WinW, 0);
    glVertex2f(WinW, 0);
    glVertex2f(0, WinH);
    glVertex2f(0, -WinH);
    glEnd();
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    DrawGrid();
    DrawDDALine(X1, X2, Y1, Y2);
    DrawBrezehamLine(X1, X2, Y1, Y2);
    realLine(X1, X2, Y1, Y2);
    glPopMatrix();
    glutSwapBuffers();
}

void Reshape(GLsizei WinW, GLsizei WinH) {
    glViewport(0, 0, WinW, WinH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WinW / 2, WinW / 2, -WinH / 2, WinH / 2, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(WinW, WinH);
    glutInitWindowPosition(300, 80);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Segment generation by Amalia D.");
    glClearColor(255, 255, 255, 255);
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutMainLoop();
    return 0;
}