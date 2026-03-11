#include "shape.h"


extern float verts[] = { -1.0, 1.0, 1.0,			// Vertex #0
							-1.0, -1.0, 1.0,		// Vertex #1
							1.0,  -1.0, 1.0,		// Vertex #2
							1.0,  1.0, 1.0,			// Vertex #3
};

extern float norms[] = { 0.0, 0.0, 1.0,		//0
						0.0, 0.0, 1.0,		//1
						0.0, 0.0, 1.0,		//2
						0.0, 0.0, 1.0,		//3
};


extern float texcoords[] = { 0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3
};

void Shape::render1(GLuint tex)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	glBindTexture(GL_TEXTURE_2D, tex);

	// add code to render the cube (above) using method 1
	glBegin(GL_QUADS);

		glArrayElement(0);
		glArrayElement(1);
		glArrayElement(2);
		glArrayElement(3);

	glEnd();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
}

void Shape::render2(GLuint tex)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	// add code to render the cube (above) using method 1
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	// glDrawArrays()
}

extern GLuint indices[] = { 0, 1, 2, //front

0, 2, 3
};

// In render3(), replace GL_INDEX_ARRAY with indices
void Shape::render3(GLuint tex)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	// Use indices array for glDrawElements
	glDrawElements(GL_QUADS, 8, GL_UNSIGNED_INT, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}