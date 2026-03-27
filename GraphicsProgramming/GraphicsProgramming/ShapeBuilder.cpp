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

void ShapeBuilder::RenderCylinder(float radius, float height, float segments) {
    float angleStep = (2.0f * PI) / segments;

    glBegin(GL_QUADS);
    for (int i = 0; i < segments; i++)
    {
        float angle1 = i * angleStep;
        float angle2 = (i + 1) * angleStep;

        float x1 = radius * cos(angle1);
        float z1 = radius * sin(angle1);
        float x2 = radius * cos(angle2);
        float z2 = radius * sin(angle2);

        float y_bottom = -height / 2.0f;
        float y_top = height / 2.0f;

        float nx1 = cos(angle1);
        float nz1 = sin(angle1);
        float nx2 = cos(angle2);
        float nz2 = sin(angle2);

        glNormal3f(nx1, 0.0f, nz1);
        glTexCoord2f(static_cast<float>(i) / segments, 0.0f);
        glVertex3f(x1, y_bottom, z1);

        glNormal3f(nx1, 0.0f, nz1);
        glTexCoord2f(static_cast<float>(i) / segments, 1.0f);
        glVertex3f(x1, y_top, z1);

        glNormal3f(nx2, 0.0f, nz2);
        glTexCoord2f(static_cast<float>(i + 1) / segments, 1.0f);
        glVertex3f(x2, y_top, z2);

        glNormal3f(nx2, 0.0f, nz2);
        glTexCoord2f(static_cast<float>(i + 1) / segments, 0.0f);
        glVertex3f(x2, y_bottom, z2);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(0.0f, height / 2.0f, 0.0f);
    for (int i = 0; i <= segments; i++)
    {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle));
        glVertex3f(x, height / 2.0f, z);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(0.0f, -height / 2.0f, 0.0f);
    for (int i = segments; i >= 0; i--)
    {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glNormal3f(0.0f, -1.0f, 0.0f);
        glTexCoord2f(0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle));
        glVertex3f(x, -height / 2.0f, z);
    }
    glEnd();
}

void ShapeBuilder::GenerateDisc(float radius, int segments) {
    discVerts.clear();
    discNorms.clear();
    discTexCoords.clear();
    discIndices.clear();

    float angleStep = (2.0f * PI) / segments;

    discVerts.push_back(0.0f);
    discVerts.push_back(0.0f);
    discVerts.push_back(0.0f);

    discNorms.push_back(0.0f);
    discNorms.push_back(1.0f);
    discNorms.push_back(0.0f);

    discTexCoords.push_back(0.5f);
    discTexCoords.push_back(0.5f);

    for (int i = 0; i <= segments; i++) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        discVerts.push_back(x);
        discVerts.push_back(0.0f);
        discVerts.push_back(z);

        discNorms.push_back(0.0f);
        discNorms.push_back(1.0f);
        discNorms.push_back(0.0f);

        discTexCoords.push_back(0.5f + 0.5f * cos(angle));
        discTexCoords.push_back(0.5f + 0.5f * sin(angle));
    }

    for (int i = 1; i <= segments; i++) {
        discIndices.push_back(0);
        discIndices.push_back(i);
        discIndices.push_back(i + 1);
    }
}

void ShapeBuilder::GenerateSphere(float radius, int longitude, int latitude) {
    sphereVerts.clear();
    sphereNorms.clear();
    sphereTexCoords.clear();
    sphereIndices.clear();

    float thetaStep = (2.0f * PI) / longitude;
    float deltaStep = PI / latitude;

    for (int longs = 0; longs <= longitude; longs++) {
        float theta = longs * thetaStep;

        for (int lats = 0; lats <= latitude; lats++) {
            float delta = lats * deltaStep;

            float x = radius * cos(theta) * sin(delta);
            float y = radius * cos(delta);
            float z = radius * sin(theta) * sin(delta);

            sphereVerts.push_back(x);
            sphereVerts.push_back(y);
            sphereVerts.push_back(z);

            float len = sqrt(x * x + y * y + z * z);
            sphereNorms.push_back(x / len);
            sphereNorms.push_back(y / len);
            sphereNorms.push_back(z / len);

            float u = static_cast<float>(longs) / longitude;
            float v = static_cast<float>(lats) / latitude;
            sphereTexCoords.push_back(u);
            sphereTexCoords.push_back(v);
        }
    }

    for (int longs = 0; longs < longitude; longs++) {

        for (int lats = 0; lats < latitude; lats++) {
            int first = longs * (latitude + 1) + lats;
            int second = first + latitude + 1;

            sphereIndices.push_back(first);
            sphereIndices.push_back(second);
            sphereIndices.push_back(first + 1);

            sphereIndices.push_back(second);
            sphereIndices.push_back(second + 1);
            sphereIndices.push_back(first + 1);
        }
    }
}

void ShapeBuilder::GenerateCylinder(float radius, float height, int segments) {
    cylinderVerts.clear();
    cylinderNorms.clear();
    cylinderTexCoords.clear();
    cylinderIndices.clear();

    float angleStep = (2.0f * PI) / segments;
    float y_top = height / 2.0f;
    float y_bottom = -height / 2.0f;

    for (int i = 0; i <= segments; i++) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        float nx = cos(angle);
        float nz = sin(angle);

        cylinderVerts.push_back(x);
        cylinderVerts.push_back(y_bottom);
        cylinderVerts.push_back(z);

        cylinderNorms.push_back(nx);
        cylinderNorms.push_back(0.0f);
        cylinderNorms.push_back(nz);

        cylinderTexCoords.push_back(static_cast<float>(i) / segments);
        cylinderTexCoords.push_back(0.0f);

        cylinderVerts.push_back(x);
        cylinderVerts.push_back(y_top);
        cylinderVerts.push_back(z);

        cylinderNorms.push_back(nx);
        cylinderNorms.push_back(0.0f);
        cylinderNorms.push_back(nz);

        cylinderTexCoords.push_back(static_cast<float>(i) / segments);
        cylinderTexCoords.push_back(1.0f);
    }

    for (int i = 0; i < segments; i++) {
        int base = i * 2;

        cylinderIndices.push_back(base);
        cylinderIndices.push_back(base + 1);
        cylinderIndices.push_back(base + 2);

        cylinderIndices.push_back(base + 1);
        cylinderIndices.push_back(base + 3);
        cylinderIndices.push_back(base + 2);
    }

    unsigned int topCenterIndex = cylinderVerts.size() / 3;
    cylinderVerts.push_back(0.0f);
    cylinderVerts.push_back(y_top);
    cylinderVerts.push_back(0.0f);

    cylinderNorms.push_back(0.0f);
    cylinderNorms.push_back(1.0f);
    cylinderNorms.push_back(0.0f);

    cylinderTexCoords.push_back(0.5f);
    cylinderTexCoords.push_back(0.5f);

    for (int i = 0; i <= segments; i++) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        cylinderVerts.push_back(x);
        cylinderVerts.push_back(y_top);
        cylinderVerts.push_back(z);

        cylinderNorms.push_back(0.0f);
        cylinderNorms.push_back(1.0f);
        cylinderNorms.push_back(0.0f);

        cylinderTexCoords.push_back(0.5f + 0.5f * cos(angle));
        cylinderTexCoords.push_back(0.5f + 0.5f * sin(angle));
    }

    for (int i = 0; i < segments; i++) {
        cylinderIndices.push_back(topCenterIndex);
        cylinderIndices.push_back(topCenterIndex + i + 1);
        cylinderIndices.push_back(topCenterIndex + i + 2);
    }

    unsigned int bottomCenterIndex = cylinderVerts.size() / 3;
    cylinderVerts.push_back(0.0f);
    cylinderVerts.push_back(y_bottom);
    cylinderVerts.push_back(0.0f);

    cylinderNorms.push_back(0.0f);
    cylinderNorms.push_back(-1.0f);
    cylinderNorms.push_back(0.0f);

    cylinderTexCoords.push_back(0.5f);
    cylinderTexCoords.push_back(0.5f);

    for (int i = segments; i >= 0; i--) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        cylinderVerts.push_back(x);
        cylinderVerts.push_back(y_bottom);
        cylinderVerts.push_back(z);

        cylinderNorms.push_back(0.0f);
        cylinderNorms.push_back(-1.0f);
        cylinderNorms.push_back(0.0f);

        cylinderTexCoords.push_back(0.5f + 0.5f * cos(angle));
        cylinderTexCoords.push_back(0.5f + 0.5f * sin(angle));
    }

    for (int i = 0; i < segments; i++) {
        cylinderIndices.push_back(bottomCenterIndex);
        cylinderIndices.push_back(bottomCenterIndex + i + 1);
        cylinderIndices.push_back(bottomCenterIndex + i + 2);
    }
}

void ShapeBuilder::RenderDiscVA() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, discVerts.data());
    glNormalPointer(GL_FLOAT, 0, discNorms.data());
    glTexCoordPointer(2, GL_FLOAT, 0, discTexCoords.data());

    glDrawElements(GL_TRIANGLES, discIndices.size(), GL_UNSIGNED_INT, discIndices.data());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void ShapeBuilder::RenderSphereVA() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, sphereVerts.data());
    glNormalPointer(GL_FLOAT, 0, sphereNorms.data());
    glTexCoordPointer(2, GL_FLOAT, 0, sphereTexCoords.data());

    glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, sphereIndices.data());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void ShapeBuilder::RenderCylinderVA() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, cylinderVerts.data());
    glNormalPointer(GL_FLOAT, 0, cylinderNorms.data());
    glTexCoordPointer(2, GL_FLOAT, 0, cylinderTexCoords.data());

    glDrawElements(GL_TRIANGLES, cylinderIndices.size(), GL_UNSIGNED_INT, cylinderIndices.data());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}