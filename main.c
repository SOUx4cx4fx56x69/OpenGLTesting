#include<GL/glu.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<stdio.h>

#define NAMEWINDOW "OpenGLTesting"
float sizeRect = 100; // global var is shit of course


void updateScreen(int value){
/*
glutTimerFunc using pointer to function void (*func)(int value);
*/
//printf("update\n");
glutPostRedisplay();
//printf("Updated \n");
glutTimerFunc(20*100, updateScreen, 0); // loop update
}

void EventKeydown(char unsigned key, int x, int y){ // x,y mouse location
	printf("EVENT: %c(%d) ; mouse coords %d:%d\n",key,key,x,y);
	if(key == 's') sizeRect-=0.1;
	else if(key == 'w') sizeRect+=0.1; 
	else if(key == 27) sizeRect=100;
	printf("sizeRect %f\n",sizeRect);
//	glutPostRedisplay(); // redisplay window, without this you don't see update
}

void render(void){

	glMatrixMode(GL_PROJECTION); // Set Matrix mode \
	not GL_MODELVIEW now
	glLoadIdentity(); // update current matrix

	//left right bottom top near far (xD)

	glOrtho(0, 640, 480, 0, 1, -1); // multiple matrix ^^
	glMatrixMode(GL_MODELVIEW); // update mode to modelview
	glLoadIdentity(); // update current matrix

	glClearColor(.3,.4,.5,1); // set clear color
	glClear(GL_COLOR_BUFFER_BIT); // clear color with buffer bit flag
	glutSwapBuffers(); // swap buffers(update window)

	// if we are dont it then we get 0,0,0 dots and y=0(top, not bottom/center) as center
	glTranslated( 640/2, 480/2, 0.f ); // multiply the current matrix by a translation matrix
	

	glBegin(GL_TRIANGLES);//  begin draw figure (enum)\
	for poits as example GL_POINTS\
	GL_QUADS is simply quad CAP lol(4 dot)
		//first triangle
		glNormal3f(sizeRect*2,sizeRect*2,0); // normal for light
		// than far then less light
		glColor3f(1.,0,0); // set color RGB
		glVertex3f(-sizeRect,-sizeRect,1);  // set first vertex in -N(x) -N(y) 1(z)
		glColor3f(0,1.,0); 
		glVertex3f(sizeRect,-sizeRect,-1); // set 2 vertex in N(x) -N(y) -1(z)
		glColor3f(0,0,1);
		glVertex3f(sizeRect,sizeRect,1); // vertex of matrix 3
		glColor3f(0,0,0);
		glVertex3f(sizeRect,sizeRect,1); // vertex of matrix 4
		glColor3f(1,1,1);
		// second 
		glVertex2f(sizeRect*2,sizeRect*2); //x,y without z (f -> float)
		glVertex2f(sizeRect,sizeRect*2);
		glVertex2f(sizeRect,-sizeRect*2);
//		glVertex3f(sizeRect,-sizeRect*2,-1); // z (1) near for me. -1 far for me
		//
	glEnd();
	glutSwapBuffers();
}

void main(int argumentscount, char ** arguments){
	glutInit(&argumentscount,arguments);
	glutInitWindowSize(640,480);
	glutInitDisplayMode(GLUT_DOUBLE); // Double Buffer for Window https://www.opengl.org/resources/libraries/glut/spec3/node12.html
	glutCreateWindow(NAMEWINDOW); // CreateWindow with title (NAMEWINDOW)

	glutDisplayFunc(render);
	glutKeyboardFunc(EventKeydown);//funcion at C is pointers default also as arrays
	glutTimerFunc(200, updateScreen, 0); // use updateScreen function after 200 ms with 0 as first argument

	glutMainLoop();
}

