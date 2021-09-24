//
// Created by Amalia on 22.09.2021.
//

#include "Segments.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <gl\glut.h>

#define WinW 830
#define WinH 600
#define STEP 50
#define X1 -2
#define Y1 -2
#define X2 -4
#define Y2 -10
int scr = 1;
long T, startT = clock();

int sign(double a) {
    if (a > 0) return 1;
    if (a < 0) return -1;
    return 0;
}

void DrawPixel(int x, int y, int Red, int Green, int Blue) {
    double sizeX = (float) WinW / (float) STEP;
    double sizeY = (float) WinH / (float) STEP;
    glColor3d(Red, Green, Blue);
    glBegin(GL_QUADS);

    double _x = x * sizeX;
    double _y = y * sizeY;

    glVertex2d(_x, _y);
    glVertex2d(_x + sizeX, _y);
    glVertex2d(_x + sizeX, _y + sizeY);
    glVertex2d(_x, _y + sizeY);
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

    for (int i = 0; i <= length; i++) {
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
    if(sx < 0) x +=sx;
    if(sy < 0) y +=sy;
    for (int i = 0; i <= dx; i++) {
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
    glVertex2d(x1*WinW/STEP, y1*WinH/STEP);
    glVertex2d(x2*WinW/STEP, y2*WinH/STEP);
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

    if (scr > 0) DrawCDALine(X1, X2, Y1, Y2);

    if (scr > 1) DrawBrezehamLine(X1, X2, Y1, Y2);

    if (scr > 2) DrawRealLine(X1, X2, Y1, Y2);
    DrawGrid();
    glPopMatrix();
    glutSwapBuffers();
}

void Reshape(GLsizei Winw, GLsizei Winh) {
    glViewport(0, 0, Winw, Winh);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Winw / 2, Winw / 2, -Winh / 2, Winh / 2, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
