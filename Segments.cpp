//
// Created by Amalia on 22.09.2021.
//

#include "Segments.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <gl\glut.h>

const GLint WinW = 830, WinH = 600;
#define STEP 50
const int X1 = 0, Y1 = 0, X2 = 100, Y2 = -100;
int scr = 1;
long T = 0, startT = clock();

int sign(double a) {
    if (a > 0) return 1;
    if (a < 0) return -1;
    return 0;
}

void DrawPixel(int x, int y, int Red, int Green, int Blue) {
    double sizeX = (float )WinW / (float) STEP;
    double sizeY = (float )WinH / (float) STEP;
    glColor3d(Red, Green, Blue);
    glBegin(GL_QUADS);
    int _x = (int)((int)(x /sizeX) * sizeX);
    int _y = (int)((int)(y / sizeY) * sizeY);
    glVertex2d(_x, _y);
    glVertex2d(_x + sizeX, _y);
    glVertex2d(_x + sizeX, _y - sizeY);
    glVertex2d(_x, _y - sizeY);
    glEnd();
}

void DrawCDALine(int x1, int x2, int y1, int y2) {
    double dx, dy, x, y, length;

    if (abs(x2 - x1) >= abs(y2 - y1))
        length = abs(x2 - x1);
    else
        length = abs(y2 - y1);

    dx = (x2 - x1) / length;
    dy = (y2 - y1) / length;
    x = (double) x1 + 0.5 * sign(dx);
    y = (double) y1 + 0.5 * sign(dy);

    for (int i = 1; i <= length; i++) {
        DrawPixel(floor(x), floor(y), 1, 0, 1);
        x += dx;
        y += dy;
    }
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
        DrawPixel(x, y, 1, 5, 0);
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
}

void DrawRealLine(double x1, double x2, double y1, double y2) {
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3d(0, 2, 0);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();

}

void DrawGrid() {
    glLineWidth(1);
    glColor3d(0, 0, 0);
    for (float i = -STEP; i < STEP; ++i) {
        glBegin(GL_LINES);
        glVertex2d(i * WinW / (float) STEP, -WinH);
        glVertex2d(i * WinW / (float) STEP, WinH);
        glEnd();
    }
    for (float i = -STEP; i < STEP; ++i) {
        glBegin(GL_LINES);
        glVertex2d(-WinW, i * WinH / (float) STEP);
        glVertex2d(WinW, i * WinH / (float) STEP);
        glEnd();
    }

    glLineWidth(3);
    glColor3d(256, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-WinW, 0);
    glVertex2f(WinW, 0);
    glVertex2f(0, WinH);
    glVertex2f(0, -WinH);
    glEnd();
}

void Idle() {
    T = clock();
    if ((T - startT) / CLK_TCK > 2) {
        scr++;
        startT = clock();
        glutPostRedisplay();
    }
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    DrawGrid();

    if (scr > 0) DrawCDALine(X1, X2, Y1, Y2);

    if (scr > 1) DrawBrezehamLine(X1, X2, Y1, Y2);

    if (scr > 2) DrawRealLine(X1, X2, Y1, Y2);

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
