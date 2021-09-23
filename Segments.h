//
// Created by Amalia on 22.09.2021.
//

#ifndef COMPGRAPH_LAB1_SEGMENTS_H
#define COMPGRAPH_LAB1_SEGMENTS_H

#include <GL/gl.h>

int sign(double a);
void DrawPixel(int x, int y, int Red, int Green, int Blue);
void DrawCDALine(int x1, int x2, int y1, int y2);
void DrawBrezehamLine(int x1, int x2, int y1, int y2);
void DrawRealLine(double x1, double x2, double y1, double y2);
void DrawGrid();
void Idle();
void Display();
void Reshape(GLsizei Winw, GLsizei Winh);

#endif //COMPGRAPH_LAB1_SEGMENTS_H
