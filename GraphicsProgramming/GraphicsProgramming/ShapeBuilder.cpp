#include "ShapeBuilder.h"

void ShapeBuilder::RenderDisc(float radius, float segments) {

	float angleStep = (2.0f * PI) / segments;

    glBegin(GL_TRIANGLE_FAN);

    glVertex3f(0.0f, 0.0f, 0.0f);

    for (int i = 0; i <= segments; i++)  
    {
        float angle = i * angleStep;

        float x = radius * cos(angle);
        float y = radius * sin(angle);

        glVertex3f(x, y, 0.0f);
    }

    glEnd();
}

void ShapeBuilder::RenderSphere(float radius, float longitude, float latitude) {

    float thetaStep = (2.0f * PI) / longitude;
    float deltaStep = PI / latitude;

    for (int longs = 0; longs <= longitude; longs++) {
        float theta = longs * thetaStep;
        float thetaNext = (longs + 1) * thetaStep;

        for (int lats = 0; lats < latitude; lats++)
        {
            float delta = lats * deltaStep;
            float deltaNext = (lats + 1) * deltaStep;

            float x1 = radius * cos(theta) * sin(delta);
            float y1 = radius * cos(delta);
            float z1 = radius * sin(theta) * sin(delta);

            float x2 = radius * cos(theta) * sin(deltaNext);
            float y2 = radius * cos(deltaNext);
            float z2 = radius * sin(theta) * sin(deltaNext);

            float x3 = radius * cos(thetaNext) * sin(deltaNext);
            float y3 = radius * cos(deltaNext);
            float z3 = radius * sin(thetaNext) * sin(deltaNext);

            float x4 = radius * cos(thetaNext) * sin(delta);
            float y4 = radius * cos(delta);
            float z4 = radius * sin(thetaNext) * sin(delta);

            glBegin(GL_QUADS);

            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
            glVertex3f(x3, y3, z3);
            glVertex3f(x4, y4, z4);

            glEnd();
        }
    }
}