/*

Written by: Esam Ghaleb
Student Number: 040080905


//  main.cpp

*/


#include <iostream>
#include <glut.h>
#include "SOIL.h"
#include <math.h>
GLdouble angle = 0, Moon_angle = 0;


GLuint texture[10];
	
GLfloat material_shininess[] = { 20 };
GLint LoadGLTexture(const char *filename)
{
    GLuint _texture;
    // filename = "/Users/gurelerceis/Documents/XCodeWorkspace/Ders2/SOIL/img_test.bmp"
    
    _texture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture 
	(
     filename,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT 
     );
    
    // check for an error during the load process 
    if(_texture == 0)
    {
	    printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
	

    return _texture;
}
static void Draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

	//*****  The Sun    ***************************************/
    GLUquadric* quadric = gluNewQuadric();
     
	glDisable (GL_LIGHTING); // this done for illmunating the sun ( the source of the light)
	glDisable(GL_LIGHT0);

	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE);
    glTranslatef(0.f, 0.f, -10.f);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
	glRotated(angle, 0, 1, 0);
    glPushMatrix();


	glPushMatrix();
	glRotated(90, 1, 0, 0);
	gluSphere( quadric , .8 , 36 , 18 );
	glPopMatrix();


	glEnable(GL_LIGHTING); // this done for illmunating the sun ( the source of the light)
	glEnable(GL_LIGHT0);
    /**************  Mercury *******************************/
 
	glPushMatrix();
    glRotated(angle, 0, 1, 0);
    glTranslatef(2 ,  0,   0);
	glBindTexture(GL_TEXTURE_2D, texture[3]);

	glPushMatrix();
	glRotated(90, 1, 0, 0);
    gluSphere( quadric , .5 , 36 , 18 );
	glPopMatrix();

	/******** Moon of Mercury  ***********/
	glPushMatrix();
    glRotated(Moon_angle, 0, 1, 0);
    glTranslatef(1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texture[2]);

	glPushMatrix();
	glRotated(90, 1, 0, 0);
	gluSphere( quadric , .3 , 36 , 18 );
	glPopMatrix();

	
	glPopMatrix(); // pop the moon of mercury
	glPopMatrix(); // pop mercury

	/**************** Earth *******************/
    glPushMatrix();
    glRotated(angle, 0, 1, 0);
    glTranslatef(5 ,  0,   0);
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glPushMatrix();
	glRotated(90, 1, 0, 0);
    gluSphere( quadric , .6 , 36 , 18 );
	glPopMatrix();

	/**************** Two moons for earth **************/
	glPushMatrix();
    glRotated(Moon_angle, 0, 1, 0);
    glTranslatef(1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, texture[2]);

	glPushMatrix();
	glRotated(90, 1, 0, 0);
	gluSphere( quadric , .3 , 36 , 18 );
	glPopMatrix();

	glPopMatrix(); // pop the first moon of the earth

	glPushMatrix();
    glRotated(Moon_angle, 0, 1, 0);
    glTranslatef(1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texture[2]);

	glPushMatrix();
	glRotated(90, 1, 0, 0);
	gluSphere( quadric , .3 , 36 , 18 );
	glPopMatrix(); 

	glPopMatrix(); // pop the second moon of the earth
   
	glPopMatrix(); // pop earth
	glPopMatrix(); // pop sun
 
    glutSwapBuffers();
    
}
void setupLight(){
    glEnable(GL_LIGHTING);
    
    GLfloat light_position[] = {0.f, 0.f, -10.f, 1};
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    
    
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    GLfloat global_ambient[] = { 0.2,  0.2, 0.2, 1.0 };
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat material_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    
    
    glMaterialfv(GL_FRONT,GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT,GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT,GL_SHININESS, material_shininess);
   
    glShadeModel(GL_SHININESS);
}

static void timerCallback (int value)
{
 
    angle= angle +.3;
    Moon_angle = Moon_angle + 1;
    glutTimerFunc(10, timerCallback, 0);
    glutPostRedisplay();
}
int main (int argc, char ** argv)
{


    GLenum type;
    
	glutInit(&argc, argv);

	glutInitWindowSize(1600,1200);
	type = GLUT_RGB;
	type |= GLUT_DOUBLE;
	type |= GLUT_DEPTH;
    type |= GLUT_MULTISAMPLE;
	glutInitDisplayMode(type);
	glutCreateWindow("Ders 2");
   
    glClearColor(0.0, 0, 0.0, 0);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
    texture[0] = LoadGLTexture("sun_sphere.jpg");
    texture[1] = LoadGLTexture("earth_sphere.jpg");
    texture[2] = LoadGLTexture("moon_sphere.jpg");
    texture[3] = LoadGLTexture("mercury_sphere.bmp");
    
    glMatrixMode(GL_PROJECTION);
    gluPerspective(55, 1600/1200, 0.1, 100);
    
    glMatrixMode(GL_MODELVIEW);
    
    timerCallback(0);
	
    glutDisplayFunc(Draw);
	setupLight();
    glutMainLoop();
    return 0;
}

