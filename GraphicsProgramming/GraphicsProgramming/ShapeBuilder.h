#pragma once

#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>

class ShapeBuilder
{
private:
	double PI = 3.14159265358979323846;

public:
	void RenderDisc(float radius, float segments);
	void RenderSphere(float segments, float longitude, float latitude);
};

