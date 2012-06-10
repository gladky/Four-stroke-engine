/*
 * GKOM Four stroke engine
 */


#pragma comment(lib, "lib\\glew32") 
#pragma comment(lib, "lib\\glfw") 
#pragma comment(lib, "IL\\ILU") 
#pragma comment(lib, "IL\\ILUT") 
#pragma comment(lib, "IL\\DevIL") 



#include "GL/glew.h"		// Include GLEW, which pulls in OpenGL headers as required
#include "GL/glfw.h"		// Include OpenGL Framework headers

#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include "colors.h"
//#include "particle.cpp"
#include "modele.cpp"
#include <math.h>
#include <conio.h>

 
#define ILUT_USE_OPENGL		// This MUST be defined before calling the DevIL headers or we don't get OpenGL functionality
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

#include <objidl.h>

bool fullScreenMode = false;													// Fullscreen disabled by default
bool transEnable = false;
static float engineSpeed = 0.1;
float lightIntense = 1.0;

int windowPosX = 0;
int windowPosY = 0;
int windowWidth = 854;
int windowHeight = 480;


float eyePositionX =	0.0;
float eyePositionY =	0.75;
float eyePositionZ =	12.0;
float eyePositionVerticalDeg =	0.0;
float eyePositionHorizontalDeg =	0.0;
float eyePositionZoom = 1.0;
float lookAtPositionX=	0.0;
float lookAtPositionY=	1.0;
float lookAtPositionZ=	0.0;

float tmpX, tmpY, tmpZ, eyeZoomTmp;

bool light1 = false;
bool light2 = false;
bool light3 = false;
bool light4 = false;

																	// identyfikatory list wyswietlania

/* inicjuje 
 * -oswietlenie
 * -cieniowanie
 * -biblioteke glut
 * -wspolprace z systemem okienkowym
 */
void init()
{   
   GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "GLEW initialisation error: " << glewGetErrorString(err) << std::endl;
		exit(-1);
	}
	std::cout << "GLEW intialised successfully. Using GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;
 


    GLfloat mat_ambient[]    = { 1.0, 1.0,  1.0, 1.0 };
	GLfloat mat_diffuse[]    = { 0.5, 0.5,  0.5, 1.0 };
    GLfloat mat_specular[]   = { 1.0, 1.0,  1.0, 1.0 };
    GLfloat light1_position[] = { 10.0,		5.0,	10.0,	1.0 };
	GLfloat light2_position[] = { -10.0,	10.0,	-10.0,	1.0 };
	GLfloat light3_position[] = { 10.0,		10.0,	-10.0,	1.0 };
	GLfloat light4_position[] = { -10.0,	10.0,	10.0,	1.0 };
    GLfloat lm_ambient[]     = { 0.2, 0.2,  0.2, 1.0 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialf( GL_FRONT, GL_SHININESS, 50.0 );
    glLightfv( GL_LIGHT0, GL_POSITION, light1_position );
		glLightfv( GL_LIGHT1, GL_POSITION, light2_position );
		glLightfv(GL_LIGHT1, GL_DIFFUSE, mat_diffuse);
		glLightfv( GL_LIGHT2, GL_POSITION, light3_position );
		glLightfv(GL_LIGHT2, GL_DIFFUSE, mat_diffuse);
		glLightfv( GL_LIGHT3, GL_POSITION, light4_position );
		glLightfv(GL_LIGHT3, GL_DIFFUSE, mat_diffuse);
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lm_ambient );
    
	glEnable(GL_NORMALIZE);

    glShadeModel( GL_SMOOTH );													// obliczanie swiatla 
	
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
	glEnable( GL_LIGHT1 );
	glEnable( GL_LIGHT2 );
	glEnable( GL_LIGHT3 );

    glDepthFunc( GL_LESS );
    glEnable( GL_DEPTH_TEST );
	//glBlendFunc (GL_SRC_ALPHA, GL_ONE);


	// DevIL sanity check
	if ( (iluGetInteger(IL_VERSION_NUM) < IL_VERSION) || (iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION) || (ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION) )
	{
		std::cout << "DevIL versions are different... Exiting." << std::endl;
		exit(-1);
	}
	

	// Initialise all DevIL functionality
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);	// Tell DevIL that we're using OpenGL for our rendering

}

void reshape(GLsizei w, GLsizei h)
{
    if( h > 0 && w > 0 ) {														//minimalized window
      glViewport( 0, 0, w, h );
      glMatrixMode( GL_PROJECTION );											//projection mode
      glLoadIdentity();															//"przeksztalcenie ktore nic nie robi"
      if( w <= h ) {
         //glOrtho( -2.25, 2.25, -2.25*h/w, 2.25*h/w, -10.0, 10.0 );
		 glFrustum(-0.2, 0.2, -0.2*h/w, 0.2*h/w, 0.5, 150.0);
      }
      else {
         //glOrtho( -2.25*w/h, 2.25*w/h, -2.25, 2.25, -10.0, 10.0 );
		 glFrustum( -0.2*w/h, 0.2*w/h, -0.2, 0.2, 0.5, 150.0 );
      }
	  gluLookAt(eyePositionX,eyePositionY,eyePositionZ,lookAtPositionX,lookAtPositionY,lookAtPositionZ,0,1,0); //musi byc po perspektywie
      glMatrixMode( GL_MODELVIEW );
    }
}

void displayObjects(int frame_no, int sceneRotation)
{
	GLfloat mat_diffuse[]    = { lightIntense*0.5, lightIntense*0.5,  lightIntense*0.5, 1.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, mat_diffuse);
	reshape (glutGet (GLUT_WINDOW_WIDTH),glutGet (GLUT_WINDOW_HEIGHT));
	glDepthMask(GL_TRUE);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glPushMatrix();																//scene
		//glTranslatef( 0.0, 0.0, -55.0 ); 
		//glRotatef( 180.0, 1.0, 0.0, 0.0 );
		//glRotatef( 90.0, 0.0, 1.0, 0.0 );
		glPushMatrix();															//group 1
			//glRotatef( 45*sin((float)sceneRotation*0.01), 1.0, 0.0, 0.0 );
			//glRotatef( 100.0, 0.0, 1.0, 0.0 );
			//glRotatef( (float)sceneRotation*1.0, 0.0, 1.0, 0.0 );
			glPushMatrix();
				//drawHelpers();
			glPopMatrix();
			glPushMatrix();
				drawRoom();
				drawCrankshaft(frame_no  );
				draw4Pistons( frame_no  );
				putFlywheel(frame_no);
				drawCovers(frame_no + 90, transEnable);
				

				//drawValve();
				//drawCamshaft(); //debug
				//drawCamshaftCoverLeft(); // debug
				//drawTriangle(); // debug
				//drawFlywheel(); // debug
				//drawCamshaftMechanism(); //debug
			glPopMatrix();
		glPopMatrix();															//end of group 1
    glPopMatrix();																//end of scene	 
}

void display()
{
	static int frame_no=0;
	static int sceneRotation=0;

    glClearColor (0.3,0.3,0.8,1.0);												//background color - color buffer

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//clearing buffers of: colors, z-buffer, "szablonowego"
	// wybór macierzy modelowania
    //glMatrixMode (GL_MODELVIEW);
	//glLoadIdentity ();
	
	frame_no += engineSpeed;
	if(frame_no<720) frame_no ++; else frame_no = 0;
	if(sceneRotation<3600 ) sceneRotation ++; else sceneRotation = 0;
	
	//okrazanie sceny przez obserwatora
	//glMatrixMode( GL_PROJECTION );//rotacja sceny
	//glPushMatrix();//rotacja sceny
	//	glRotatef( frame_no, 0.0, 1.0, 0.0 );//rotacja sceny
	//	glMatrixMode( GL_MODELVIEW );//rotacja sceny
		displayObjects(frame_no, sceneRotation);								//displaying scene
	//	glMatrixMode( GL_PROJECTION );//rotacja sceny
	//glPopMatrix();//

	glFlush();
	glutSwapBuffers();
	glfwSwapBuffers();
}


void keyFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':	
		if(engineSpeed < 150.0)
			engineSpeed *= 1.1f; break;
	case 's':
		if(engineSpeed > 1.0)
				engineSpeed *= 0.9f; break;
	case 'i':	
		if(lightIntense < 2.0)
			lightIntense *= 1.1f; break;
	case 'k':
		if(lightIntense > 0.01)
				lightIntense *= 0.9f; break;
	
	case 't':
		transEnable = !transEnable;	break;
	case '1':
		light1 = !light1;
		if(light1) glEnable( GL_LIGHT0 );
		else glDisable(GL_LIGHT0);
		break;
	case '2':
		light2 = !light2;	
		if(light2) glEnable( GL_LIGHT1 );
		else glDisable(GL_LIGHT1);
		break;
	case '3':
		light3 = !light3;	
		if(light3) glEnable( GL_LIGHT2 );
		else glDisable(GL_LIGHT2);
		break;
	case '4':
		light4 = !light4;	
		if(light4) glEnable( GL_LIGHT3 );
		else glDisable(GL_LIGHT3);
		break;
	}
}

// Callback handler for special-key event
void specialKeys(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_F1:														// F1: Toggle between full-screen and windowed mode
			fullScreenMode = !fullScreenMode;									// Toggle state
			if (fullScreenMode) {												// Full-screen mode
				windowPosX   = glutGet(GLUT_WINDOW_X);							// Save parameters
				windowPosY   = glutGet(GLUT_WINDOW_Y);
				windowWidth  = glutGet(GLUT_WINDOW_WIDTH);
				windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
				glutFullScreen();												// Switch into full screen
			} else {															// Windowed mode
				glutReshapeWindow(windowWidth, windowHeight);					// Switch into windowed mode
				glutPositionWindow(windowPosX,windowPosY);						// Postion top-left corner
		}
        break;
		case GLUT_KEY_UP:														// Up: increase speed
			if(eyePositionVerticalDeg < 88.0 ){
				eyePositionVerticalDeg +=2.0;
				tmpY = 20*sin(eyePositionVerticalDeg* 2*PI / 360.0) * eyePositionZoom;
				tmpX = 20*sin(eyePositionHorizontalDeg* 2*PI / 360.0)*cos(eyePositionVerticalDeg* 2*PI / 360.0) * eyePositionZoom;
				tmpZ = 20*cos(eyePositionHorizontalDeg* 2*PI / 360.0)*cos(eyePositionVerticalDeg* 2*PI / 360.0) * eyePositionZoom;
				if(tmpX <= 20.0 && tmpZ <= 40.0 && tmpX >=-20.0 && tmpZ >= -40 && tmpY >= -2.0 && tmpY < 20.0){
					eyePositionY = tmpY;
					eyePositionX = tmpX;
					eyePositionZ = tmpZ;
				}
				else eyePositionVerticalDeg -=2.0;
			}
			break;
		case GLUT_KEY_DOWN:														// Up: decrease speed
			if(eyePositionVerticalDeg > -88.0){
				eyePositionVerticalDeg -=2.0;
				tmpY = 20*sin(eyePositionVerticalDeg* 2*PI / 360.0) * eyePositionZoom;
				tmpX = 20*sin(eyePositionHorizontalDeg* 2*PI / 360.0)*cos(eyePositionVerticalDeg* 2*PI / 360.0) * eyePositionZoom;
				tmpZ = 20*cos(eyePositionHorizontalDeg* 2*PI / 360.0)*cos(eyePositionVerticalDeg* 2*PI / 360.0) * eyePositionZoom;
				if(tmpX <= 20.0 && tmpZ <= 40.0 && tmpX >=-20.0 && tmpZ >= -40 && tmpY >= -2.0 && tmpY < 20.0){
					eyePositionY = tmpY;
					eyePositionX = tmpX;
					eyePositionZ = tmpZ;
				}
				else eyePositionVerticalDeg +=2.0;
			}
			break;
		case GLUT_KEY_LEFT:														// Up: increase speed
			if(eyePositionHorizontalDeg > 0.0){
				eyePositionHorizontalDeg -=4.0;
				tmpX = 20*sin(eyePositionHorizontalDeg* 2*PI / 360.0)*cos(eyePositionVerticalDeg* 2*PI / 360.0) * eyePositionZoom;
				tmpZ = 20*cos(eyePositionHorizontalDeg* 2*PI / 360.0)*cos(eyePositionVerticalDeg* 2*PI / 360.0) * eyePositionZoom;
				if(tmpX <= 20.0 && tmpZ <= 40.0 && tmpX >=-20.0 && tmpZ >= -40){
					eyePositionX = tmpX;
					eyePositionZ = tmpZ;
				}
				else eyePositionHorizontalDeg +=4.0;
			}
			else eyePositionHorizontalDeg = 360.0;
			break;
		case GLUT_KEY_RIGHT:														// Up: decrease speed
			if(eyePositionHorizontalDeg < 360.0){
				eyePositionHorizontalDeg +=4.0;
				tmpX = 20*sin(eyePositionHorizontalDeg* 2*PI / 360.0)*cos(eyePositionVerticalDeg* 2*PI / 360.0) * eyePositionZoom;
				tmpZ = 20*cos(eyePositionHorizontalDeg* 2*PI / 360.0)*cos(eyePositionVerticalDeg* 2*PI / 360.0) * eyePositionZoom;
				if(tmpX <= 20.0 && tmpZ <= 40.0 && tmpX >=-20.0 && tmpZ >= -40){
				eyePositionX = tmpX;
				eyePositionZ = tmpZ;
				}
				else eyePositionHorizontalDeg -=4.0;
			}
			else eyePositionHorizontalDeg = 0.0;
			break;
		case GLUT_KEY_PAGE_UP:														// Up: decrease speed
			if(eyePositionZoom > 0.1){
				eyeZoomTmp = eyePositionZoom * 0.99;
				tmpX = 20*sin(eyePositionHorizontalDeg* 2*PI / 360.0)*cos(eyePositionVerticalDeg* 2*PI / 360.0) * eyeZoomTmp;
				tmpY = 20*sin(eyePositionVerticalDeg* 2*PI / 360.0) * eyeZoomTmp;
				tmpZ = 20*cos(eyePositionHorizontalDeg* 2*PI / 360.0)*cos(eyePositionVerticalDeg* 2*PI / 360.0) * eyeZoomTmp;
				if(tmpX <= 20.0 && tmpZ <= 40.0 && tmpX >=-20.0 && tmpZ >= -40 && tmpY >= -2.0 && tmpY < 20.0){
					eyePositionX = tmpX;
					eyePositionY = tmpY;
					eyePositionZ = tmpZ;
					eyePositionZoom = eyeZoomTmp;
				}
			}
			break;
		case GLUT_KEY_PAGE_DOWN:														// Up: decrease speed
			if(eyePositionZoom < 10.0 ){
				eyeZoomTmp = eyePositionZoom * 1.01;
				tmpX = 20*sin(eyePositionHorizontalDeg* 2*PI / 360.0)*cos(eyePositionVerticalDeg* 2*PI / 360.0) * eyeZoomTmp;
				tmpY = 20*sin(eyePositionVerticalDeg* 2*PI / 360.0) * eyeZoomTmp;
				tmpZ = 20*cos(eyePositionHorizontalDeg* 2*PI / 360.0)*cos(eyePositionVerticalDeg* 2*PI / 360.0) * eyeZoomTmp;
				if(tmpX <= 20.0 && tmpZ <= 40.0 && tmpX >=-20.0 && tmpZ >= -40 && tmpY >= -2.0 && tmpY < 20.0){
					eyePositionX = tmpX;
					eyePositionY = tmpY;
					eyePositionZ = tmpZ;
					eyePositionZoom = eyeZoomTmp;
				}
			}
			break;
		case GLUT_KEY_END:														// Up: decrease speed
			if(lookAtPositionY > -2.0){
				lookAtPositionY -= 0.5;
				//eyePositionY -= 0.5;
			}
			break;
		case GLUT_KEY_HOME:														// Up: decrease speed
			if(lookAtPositionY < 20.0){
				lookAtPositionY += 0.5;
				//eyePositionY += 0.5;
			}
			break;
			
   }
}


int main(int argc, char** argv)
{

	int width      = 800, height   = 600;
	int redBits    = 8,   greenBits = 8,  blueBits    = 8;
	int alphaBits  = 8,   depthBits = 24, stencilBits = 8;

   glutInit( &argc, argv );

   glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL );					//tryb wyswietlania (podwojne buforowanie|RGB|zbuforem glebokosci)

   glutInitWindowPosition( windowPosX, windowPosY );							//polozenie okna
   glutInitWindowSize( 854, 480 );												//rozmiar okna

   glutCreateWindow( "four stroke engine");

   glutDisplayFunc( display );													//rejestracja funkcji rysujacej zawartosc okna - display funkcja uzytkownika
   glutReshapeFunc( reshape );													//rejestracja funkcji zminieniajacej rozmiar okna - reshape funk uzytkownika
   glutKeyboardFunc(keyFunc);
   glutSpecialFunc(specialKeys);
   glutIdleFunc( display);


   glfwInit();


   init();																		//oswietlenie i cieniowanie

   //wchar_t imageFilename[] = L"image.jpg";  // Specify filename
	textureHandle = ilutGLLoadImage((wchar_t *)"ground.jpg");
	std::cout << "Image width         : " << ilGetInteger(IL_IMAGE_WIDTH)          << std::endl;
	std::cout << "Image height        : " << ilGetInteger(IL_IMAGE_HEIGHT)         << std::endl;
	std::cout << "Image bits per pixel: " << ilGetInteger(IL_IMAGE_BITS_PER_PIXEL) << std::endl;

	textureSideHandle = ilutGLLoadImage((wchar_t *)"side.jpg");
	std::cout << "Image width         : " << ilGetInteger(IL_IMAGE_WIDTH)          << std::endl;
	std::cout << "Image height        : " << ilGetInteger(IL_IMAGE_HEIGHT)         << std::endl;
	std::cout << "Image bits per pixel: " << ilGetInteger(IL_IMAGE_BITS_PER_PIXEL) << std::endl;

	textureTopHandle = ilutGLLoadImage((wchar_t *)"top.jpg");

	std::cout << "Image width         : " << ilGetInteger(IL_IMAGE_WIDTH)          << std::endl;
	std::cout << "Image height        : " << ilGetInteger(IL_IMAGE_HEIGHT)         << std::endl;
	std::cout << "Image bits per pixel: " << ilGetInteger(IL_IMAGE_BITS_PER_PIXEL) << std::endl;
 

   glutMainLoop();																//rozpoczyna przetwarzanie zdarzen przez system

   return 0;
}
