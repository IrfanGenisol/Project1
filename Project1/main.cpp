//
//  Irfan Genisol
//  040080180
//  Bilgisayar Bilisim Fakultesi - Bilgisayar Muhendisligi
//  Isletme Fakultesi - Endustri Muhendisligi
//
//  BLG 440 PROJE 2
//  Proje 1, Gunes Sistemi
//

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "SOIL.h"

#define DEPTH_TEST
#define TEXTURE_MAP
#define MIPMAP

//GLenum doubleBuffer;

GLdouble angleWorld = 0;
GLdouble angleMars = 0;
GLdouble angleEarth = 0;


GLdouble angleMarsSatellite = 0;
GLdouble angleMarsSatelliteTwo = 0;
GLdouble angleWorldSatellite = 0;

GLuint texture[6];

GLint LoadGLTexture(const char *filename, int width, int height);

GLfloat material_shininess[] = { 20 };

static void Init()
{
	// Background Color
	glClearColor(0.0, 0.0, 0.0, 1.0);
    
#ifdef DEPTH_TEST
	glEnable(GL_DEPTH_TEST);
#endif

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10, 10, -10, 10, -1000, 1000);
	gluPerspective(45, 800/600, 1, 10000);
	glTranslated(0, 0, -310);
    // to see up the screen
	//gluLookAt(0.1, -50, 0, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
    
#ifdef TEXTURE_MAP
    texture[0] = LoadGLTexture("/Users/irfangenisol/Desktop/workspace/BLG440/Project1/planets/sun.jpg",1024,512);
    texture[1] = LoadGLTexture("/Users/irfangenisol/Desktop/workspace/BLG440/Project1/planets/mars.jpg",1024,512);
    texture[2] = LoadGLTexture("/Users/irfangenisol/Desktop/workspace/BLG440/Project1/planets/uranus.jpg",1024,512);
    texture[3] = LoadGLTexture("/Users/irfangenisol/Desktop/workspace/BLG440/Project1/planets/venus.jpg",1024,512);
    texture[4] = LoadGLTexture("/Users/irfangenisol/Desktop/workspace/BLG440/Project1/planet/neptune.jpg",1024,512);
    texture[5] = LoadGLTexture("/Users/irfangenisol/Desktop/workspace/BLG440/Project1/planets/mercury.jpg",1024,512);
    
#endif
}

static void Draw(void)
{
    glEnable(GL_TEXTURE_2D);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

    // Sphere
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
	glPushMatrix();  // to push the scene to stack for use later
    
	//glColor3ub(255, 127, 80);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    gluQuadricTexture(quadric, texture[0]);
    glDisable(GL_LIGHTING);
    glRotated(angleEarth, 0, 1, 0);
    gluSphere(quadric ,15 , 64 , 32);
    glPushMatrix(); // to push the sun
    
    glRotated(angleMars, 0, 1, 0);
    glTranslatef(50, 0, 0);
    glRotated(angleMars, 0, 1, 0);
    //glColor3ub(255, 255, 0);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    gluQuadricTexture(quadric, texture[1]);
    gluSphere(quadric, 4, 64, 32);
    glPushMatrix();  //to push th mars
    
    glRotated(angleMarsSatellite, 0, 1, 0);
    glTranslatef(15, 0, 0);
    glRotated(angleMarsSatellite, 0, 1, 0);
    //glColor3ub(0, 255, 0);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    gluQuadricTexture(quadric, texture[2]);
    gluSphere(quadric, 3, 10, 10);
    glPopMatrix();  //to pop for drawing other satellite for mars
    
    glRotated(angleMarsSatelliteTwo, 0, 1, 0);
    glTranslatef(25, 0, 0);
    glRotated(angleMarsSatelliteTwo, 0, 1, 0);
    //glColor3ub(255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    gluQuadricTexture(quadric, texture[3]);
    gluSphere(quadric, 3, 10, 10);
    glPopMatrix(); //to pop for drawing the world it provides us same level
    //mars
    
    glRotated(angleWorld, 0, 1, 0);
    glTranslatef(-100, 0, 0);
    glRotated(angleWorld, 0, 1, 0);
    //glColor3ub(255, 100, 100);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    gluQuadricTexture(quadric, texture[4]);
    gluSphere(quadric, 5, 64, 32);
    glPushMatrix();  //to push th world
    
    glRotated(angleWorldSatellite, 0, 1, 0);
    glTranslatef(-15, 0, 0);
    glRotated(angleWorldSatellite, 0, 1, 0);
    //glColor3ub(20, 250, 250);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    gluQuadricTexture(quadric, texture[5]);
    gluSphere(quadric, 3, 64, 32);
    
    glPopMatrix();
    glPopMatrix() ;
    
	glutSwapBuffers();
}
static void Key(unsigned char key, int x, int y)
{
	switch (key) {
        //  to exit the program
		case 27:
			exit(0);
	}
}

static void timerCallback (int value)
{
	// Do timer processing
    // Assume that variables are the same with own around and
    // around the its orbit. it does not matter.
    
	angleWorld += 0.8;
	angleMars += 0.4;
    angleEarth += 0.1;
    
    angleMarsSatellite -= 1;
    angleMarsSatelliteTwo += 0.7;
    
    angleWorldSatellite -= 2;
    
    
	// call back again after 10ms have passed
	glutTimerFunc(10, timerCallback, value);
	// Re-draw
	glutPostRedisplay();
}

GLint LoadGLTexture(const char *filename, int width, int height)
{
    GLuint _texture;
    // filename = "/Users/gurelerceis/Documents/XCodeWorkspace/Ders2/SOIL/img_test.bmp"
    _texture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
    (
     filename,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    // check for an error during the load process
    if(_texture == 0)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    glBindTexture(GL_TEXTURE_2D, _texture); // select our current texture
    //glGenerateMipmap(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // texture should tile
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    return _texture;
    
}
void setupLight(){
    glEnable(GL_LIGHTING);
    
    GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 100.0, 100.0, 100.0, 100.0 };
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
    
    glShadeModel(GL_SMOOTH);
}


int main (int argc, char ** argv)
{
    
	GLenum type;
	
	glutInit(&argc, argv);
    glutInitWindowSize(800,600);
    
	type = GLUT_RGB;
	type |= GLUT_DOUBLE;
	type |= GLUT_DEPTH;
	glutInitDisplayMode(type);
	glutCreateWindow("Proje 1, Gunes Sistemi");
	
    Init();
    setupLight();
	glutKeyboardFunc(Key);
	glutDisplayFunc(Draw);
	timerCallback(0);
	glutMainLoop();
    
	return 0;
}