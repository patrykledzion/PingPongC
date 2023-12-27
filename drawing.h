#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>
#include <stdio.h>
#include "utils.h"
#include "window.h"

void drawTriangle(Vector3_t c1, Vector3_t c2, Vector3_t c3, Color4_t color, window* window);
void drawRect(long x, long y, long width, long height, Color4_t color, long depth, window* window);
void drawCircle(long x, long y, long r, int vCount, Color4_t color, long depth, window* window);