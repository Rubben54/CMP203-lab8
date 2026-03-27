#pragma once

#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <vector>

class ShapeBuilder
{
private:
	double PI = 3.14159265358979323846;

public:
	void RenderDisc(float radius, float segments);
	void RenderSphere(float segments, float longitude, float latitude);
	void RenderCylinder(float radius, float height, float segments);

    void GenerateDisc(float radius, int segments);
    void GenerateSphere(float radius, int longitude, int latitude);
    void GenerateCylinder(float radius, float height, int segments);

    void RenderDiscVA();
    void RenderSphereVA();
    void RenderCylinderVA();

private:
    // Disc data
    std::vector<float> discVerts;
    std::vector<float> discNorms;
    std::vector<float> discTexCoords;
    std::vector<GLuint> discIndices;

    // Sphere data
    std::vector<float> sphereVerts;
    std::vector<float> sphereNorms;
    std::vector<float> sphereTexCoords;
    std::vector<GLuint> sphereIndices;

    // Cylinder data
    std::vector<float> cylinderVerts;
    std::vector<float> cylinderNorms;
    std::vector<float> cylinderTexCoords;
    std::vector<GLuint> cylinderIndices;
};

