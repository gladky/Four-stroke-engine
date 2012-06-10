#include <math.h>
#include <iostream>
#include <gl/GL.h>
#include "colors.h"
using namespace std;

const float PI = 3.14159265358979323846;
GLuint textureHandle; 
GLuint textureSideHandle; 
GLuint textureTopHandle; 

void drawHelpers(){
	glColor4fv(Red);
	//glEnable (GL_DEPTH_TEST);
	glPushMatrix();		//	-	-	-	-	-	-	-	-	-	//TORUS 
		//glRotatef( 100.0, 1.0, 0.0, 0.0 );
		glMaterialfv( GL_FRONT, GL_DIFFUSE, Aqua );
		//glScalef(0.5, 0.5, 0.5);
		glutSolidCube( 0.1 ); //center
	glPopMatrix();
	glPushMatrix();		//	-	-	-	-	-	-	-	-	-	//TORUS
		glMaterialfv( GL_FRONT, GL_DIFFUSE, Aqua );
		glTranslatef( 1.0, 0.0, 0.0 );
		glutSolidCube( 0.1 ); // x +1
	glPopMatrix();
	glPushMatrix();
		glMaterialfv( GL_FRONT, GL_DIFFUSE, Aqua );
		glTranslatef( -1.0, 0.0, 0.0 );
		glutSolidCube( 0.1 ); //x -1
	glPopMatrix();
	glPushMatrix();
		glMaterialfv( GL_FRONT, GL_DIFFUSE, Aqua );
		glTranslatef( 0.0, 0.0, 1.0 );
		glutSolidCube( 0.1 ); //z +1
	glPopMatrix();
	glPushMatrix();
		glMaterialfv( GL_FRONT, GL_DIFFUSE, Aqua );
		glTranslatef( 0.0, 0.0, -1.0 );
		glutSolidCube( 0.1 ); //z -1
	glPopMatrix();
		glPushMatrix();
		glMaterialfv( GL_FRONT, GL_DIFFUSE, Aqua );
		glTranslatef( 0.0, 0.0, 2.0 );
		glutSolidCube( 0.1 ); //z +2
	glPopMatrix();
	glPushMatrix();
		glMaterialfv( GL_FRONT, GL_DIFFUSE, Aqua );
		glTranslatef( 2.0, 0.0, 0.0 );
		glutSolidCube( 0.1 ); //x +2
	glPopMatrix();
	glPushMatrix();
		glMaterialfv( GL_FRONT, GL_DIFFUSE, Aqua );
		glTranslatef( 3.0, 0.0, 0.0 );
		glutSolidCube( 0.1 ); //x +3
	glPopMatrix();
	//glDisable (GL_DEPTH_TEST);
}

void drawSampleShit(){
	glPushMatrix();
		glBegin(GL_QUADS);					//Drawing Using Quads
			glNormal3f( 0.0, 1.0, 0.0);
			glVertex3f( 0.0, 0.0, 0.0);
			glVertex3f( 1.0, 0.0, 0.0);
			glVertex3f( 1.0, 0.0, 1.0);
			glVertex3f( 0.0, 0.0, 1.0);
		glEnd();
		glBegin(GL_QUADS);					//Drawing Using Quads
			glNormal3f( -1.0, 0.0, 0.0);
			glVertex3f( 0.0, 0.0, 0.0);
			glVertex3f( 0.0, 0.0, 1.0);
			glVertex3f( 0.0, 1.0, 1.0);
			glVertex3f( 0.0, 1.0, 0.0);
		glEnd();
	

		glBegin(GL_TRIANGLES);				//Drawing Using Triangles
			glVertex3f( 0.0, 0.0, 0.0);
			glVertex3f(-1.0, 0.0, 0.0);
			glVertex3f( 0.0, 0.0,-1.0);
		glEnd(); 
	glPopMatrix();
}

void drawPistonArm(){
	float thickness = 1.0;
	float y,z, ny, normal;
	float vX[6]={0.0, 1.0, 2.0, 11.5, 12.0, 12.5 };
	float vY[6]={2.5, 2.5, 0.5,  0.5,  1.0, 1.0  };
	glPushMatrix();
	glTranslatef( -12.5, 0.0, -0.5*thickness );
	//glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse ); 
	for(int i=0; i<5; i++){
		for(int j=0; j<4; j++){
			if(j%2 == 0)	{y =  vY[i];	  ny =  vY[i+1];	   }
			else			{y = -1.0* vY[i]; ny = -1.0 * vY[i+1]; }
			if(j >= 2) {z = thickness; normal = 1.0;}
			else {z = 0; normal = -1.0;}
			glBegin(GL_QUADS);				//front/back
				glNormal3f( 0.0, 0.0, normal );
				glVertex3f( vX[i],	0.0,	z );
				glVertex3f( vX[i],	y,		z );
				glVertex3f( vX[i+1],ny,		z );
				glVertex3f( vX[i+1],0,		z );
			glEnd();		
		}
		for(int k=0; k<2; k++){
			if(k%2 == 0)	{y =  vY[i];	  ny =  vY[i+1];	   normal =  1.0;}
			else			{y = -1.0* vY[i]; ny = -1.0 * vY[i+1]; normal = -1.0;}

			glBegin(GL_QUADS);				//sides
				glNormal3f( 0.0, normal, 0.0 );
				glVertex3f( vX[i],	y,  0.0 );
				glVertex3f( vX[i],	y,  thickness);
				glVertex3f( vX[i+1],ny, thickness);
				glVertex3f( vX[i+1],ny, 0.0 );
			glEnd();
		}
	}
	glPopMatrix();

}

void drawCylinder(){
	GLfloat diffuse[]  = { 0.9, 0.9, 0.9, 1.0 };
	int segments = 32;
	float height = 1.0;
	float radius = 0.9;
	float x,y, z,xt,zt, sx, sz, sxt, szt;
	float angle;

	for (int i = 0; i < segments*8/8; i++){
		angle = (2* PI / (float)segments) ;
		x  =  sin( ((float)i  ) * angle) * radius;			//curr x
		z  =  cos( ((float)i  ) * angle) * radius;			//curr z
		xt =  sin( ((float)i+1) * angle) * radius;			//next x
		zt =  cos( ((float)i+1) * angle) * radius;			//next z
		sx =  sin( ((float)i  ) * angle) * 0.8*radius;		//curr x small radious
		sz =  cos( ((float)i  ) * angle) * 0.8*radius;		//curr z small radious
		sxt=  sin( ((float)i+1) * angle) * 0.8*radius;		//next x small radious
		szt=  cos( ((float)i+1) * angle) * 0.8*radius;		//next z small radious
		y = height;
		glPushMatrix();
			glTranslatef( 0.0, -0.2 * height, 0 );
			glPushMatrix();
				glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );    
				//glTranslatef( x, 0.0, z );
				glutSolidCube( 0.1 );
				glBegin(GL_QUADS);				//sides
					glNormal3f( x,	 0.0,  z );
					glVertex3f( x,	 0.0,  z );
					glNormal3f( xt,	 0.0,  zt);
					glVertex3f( xt,  0.0,  zt);
					glNormal3f( xt,	   y,  zt);
					glVertex3f( xt,    y,  zt);
					glNormal3f( x,	   y,  z );
					glVertex3f( x,	   y,  z );
				glEnd();
				glBegin(GL_TRIANGLES);			//top
					glNormal3f( 0.0, 1.0, 0.0);
					glVertex3f( 0.0,0.9*y, 0.0);
					glVertex3f(	x,	   y,   z);
					glVertex3f( xt,    y,  zt);
				glEnd(); 
				glBegin(GL_QUADS);				//bottom
					glNormal3f( 0.0,-1.0,0.0 );
					glVertex3f(   x, 0.0,  z );
					glVertex3f(  xt, 0.0, zt );
					glVertex3f( sxt, 0.0, szt);
					glVertex3f(  sx, 0.0, sz );
				glEnd();
				glBegin(GL_QUADS);				//interior
					glNormal3f(-sx,	 0.0, -sz );
					glVertex3f( sx,	 0.0,  sz );
					glNormal3f(-sxt, 0.0, -szt );
					glVertex3f( sxt, 0.0,  szt);
					glNormal3f(-sxt, 0.0, -szt );
					glVertex3f( sxt, 0.5*y,  szt);
					glNormal3f(-sx,	 0.0, -sz );
					glVertex3f( sx,	 0.5*y,  sz );
				glEnd();
				glBegin(GL_TRIANGLES);			//bottom interior
					glNormal3f( 0.0, -1.0, 0.0);
					glVertex3f( 0.0,0.5*y, 0.0);
					glVertex3f(	sx,	0.5*y,   sz);
					glVertex3f( sxt, 0.5*y,  szt);
				glEnd(); 
			glPopMatrix();
			glPushMatrix();
				GLUquadricObj *quadratic;
				quadratic = gluNewQuadric();
				glTranslatef( 0.0, 0.2 * height, -0.95*radius );
				gluCylinder(quadratic,0.1f,0.1f,1.9*radius,8,1);
			glPopMatrix();
		glPopMatrix();
	}
}

void drawPiston(float frame_no, float phase){
	glPushMatrix();
		glPushMatrix();
			glScalef(0.7, 0.7,0.7);
			drawCylinder();
		glPopMatrix();
		glPushMatrix();
			glRotatef(14.0*sin(frame_no + phase), 0.0, 0.0, 1.0);
			glRotatef(90.0, 0.0, 0.0, 1.0);
			glScalef(0.16, 0.2, 0.2);
			drawPistonArm();
		glPopMatrix();
	glPopMatrix();
}

void draw4Pistons(float frame){
	float frame_no = 1.0/360.0*frame*(2*PI); // 3600 klatek na obrot
	glPushMatrix();
	glTranslatef( 0.0, 0.2*12.5, 0.0 );
		glPushMatrix();
			glTranslatef( 0.0, -0.5 + 0.5*sin((float)frame_no + PI/2.0 ) - 0.05*abs(cos((float)frame_no + PI/2.0 )) , -1.5 );
			drawPiston(frame_no, PI/1.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, -0.5 + 0.5*sin((float)frame_no - PI/2.0) - 0.05*abs(cos((float)frame_no + PI/2.0 )), 0.0 );
			drawPiston(frame_no, 0.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, -0.5 + 0.5*sin((float)frame_no - PI/2.0 ) - 0.05*abs(cos((float)frame_no + PI/2.0 )), 1.5 );
			drawPiston(frame_no, 0.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, -0.5 + 0.5*sin((float)frame_no + PI/2.0) - 0.05*abs(cos((float)frame_no + PI/2.0 )), 3.0 );
			drawPiston(frame_no, PI/1.0);
		glPopMatrix();
	glPopMatrix();
}

void drawRectangle(float height, float depth, float width){
	float x,y,z;
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric(); 

	glPushMatrix();
	//glScalef(1.0,1.0,0.4);
		glBegin(GL_QUADS);							//side y
			glNormal3f( 0.0,		1.0,		0.0 );
			glVertex3f( 0.5*depth,	0.5*width,	0.0 );
			glVertex3f( 0.5*depth,  0.5*width,  height );
			glVertex3f( -0.5*depth,	0.5*width,	height );
			glVertex3f( -0.5*depth, 0.5*width,  0.0 );
		glEnd();
		glBegin(GL_QUADS);							//side -y
			glNormal3f( 0.0,		-1.0,		0.0 );
			glVertex3f( 0.5*depth,	-0.5*width,	0.0 );
			glVertex3f( 0.5*depth,  -0.5*width,  height );
			glVertex3f( -0.5*depth,	-0.5*width,	height );
			glVertex3f( -0.5*depth, -0.5*width,  0.0 );
		glEnd();
		glBegin(GL_QUADS);							//side x
			glNormal3f( 1.0,		0.0,		0.0 );
			glVertex3f( 0.5*depth,	0.5*width,	0.0 );
			glVertex3f( 0.5*depth,  0.5*width,  height );
			glVertex3f( 0.5*depth,	-0.5*width,	height );
			glVertex3f( 0.5*depth, -0.5*width,  0.0 );
		glEnd();
		glBegin(GL_QUADS);							//side -x
			glNormal3f( -1.0,		0.0,		0.0 );
			glVertex3f( -0.5*depth,	0.5*width,	0.0 );
			glVertex3f( -0.5*depth,  0.5*width,  height );
			glVertex3f( -0.5*depth,	-0.5*width,	height );
			glVertex3f( -0.5*depth, -0.5*width,  0.0 );
		glEnd();
		glBegin(GL_QUADS);							//side z
			glNormal3f( 0.0,		0.0,		1.0 );
			glVertex3f( 0.5*depth,	-0.5*width,	height );
			glVertex3f( 0.5*depth,  0.5*width,  height );
			glVertex3f( -0.5*depth,	0.5*width,	height );
			glVertex3f( -0.5*depth,	-0.5*width,	height );
		glEnd();
		glBegin(GL_QUADS);							//side -z
			glNormal3f( 0.0,		0.0,		-1.0 );
			glVertex3f( 0.5*depth,	-0.5*width,	0.0 );
			glVertex3f( 0.5*depth,  0.5*width,  0.0 );
			glVertex3f( -0.5*depth,	0.5*width,	0.0 );
			glVertex3f( -0.5*depth,	-0.5*width,	0.0 );
		glEnd();

	glPopMatrix();
}

void drawCrankArm(float height, float depth, float width){
	int segments = 8;
	float x,y,z, xn,zn, angle;
	float r = 3*depth;
	angle = ( PI / (float)segments) ;

	drawRectangle(height,width,depth);
	for(int i=0; i<segments; i++){
		x = cos((float)i*angle)*r;
		z = sin((float)i*angle)*r;
		xn = cos((float)(i+1)*angle)*r;
		zn = sin((float)(i+1)*angle)*r;
		glPushMatrix();
		glRotatef(180.0, 0.0, 1.0, 0.0);
		glScalef(1.0,1.0,0.8);
		glTranslatef( 0.0, -0.5*depth, 0.0 );
			glBegin(GL_QUADS);							//polokrag
				glNormal3f( x,	0.0,	z );
				glVertex3f( x,	0.0,	z );
				glNormal3f( x,	0.0,	z );
				glVertex3f( x,  depth,  z );
				glNormal3f( xn,	0.0,	zn );
				glVertex3f( xn,	depth,	zn );
				glNormal3f( xn,	0.0,	zn );
				glVertex3f( xn,	0.0,	zn );
			glEnd();
			glBegin(GL_TRIANGLES);							//bok y
				glNormal3f( 0.0,	1.0,	0.0 );
				glVertex3f( 0.0,	depth,	0.0 );
				glVertex3f( x,		depth,  z );
				glVertex3f( xn,		depth,	zn );
			glEnd();
			glBegin(GL_TRIANGLES);							//bok -y
				glNormal3f( 0.0,	-1.0,	0.0 );
				glVertex3f( 0.0,	0.0,	0.0 );
				glVertex3f( x,		0.0,  z );
				glVertex3f( xn,		0.0,	zn );
			glEnd();
			glBegin(GL_QUADS);							//bok -z
				glNormal3f( 0.0,	0.0,	-1.0 );
				glVertex3f( r,		0.0,	0.0 );
				glVertex3f( r,		depth,	0.0 );
				glVertex3f( -r,		depth,	0.0 );
				glVertex3f( -r,		0.0,	0.0 );
			glEnd();
		glPopMatrix();
	}
	for(int i=0; i<segments; i++){
		x = cos((float)i*angle)*depth;
		z = sin((float)i*angle)*depth;
		xn = cos((float)(i+1)*angle)*depth;
		zn = sin((float)(i+1)*angle)*depth;
		glPushMatrix();
		glRotatef(0.0, 0.0, 1.0, 0.0);
		glTranslatef( 0.0, -0.5*depth, height );
			glBegin(GL_QUADS);							//polokrag
				glNormal3f( x,	0.0,	z );
				glVertex3f( x,	0.0,	z );
				glNormal3f( x,	0.0,	z );
				glVertex3f( x,  depth,  z );
				glNormal3f( xn,	0.0,	zn );
				glVertex3f( xn,	depth,	zn );
				glNormal3f( xn,	0.0,	zn );
				glVertex3f( xn,	0.0,	zn );
			glEnd();
			glBegin(GL_TRIANGLES);							//bok y
				glNormal3f( 0.0,	1.0,	0.0 );
				glVertex3f( 0.0,	depth,	0.0 );
				glVertex3f( x,		depth,  z );
				glVertex3f( xn,		depth,	zn );
			glEnd();
			glBegin(GL_TRIANGLES);							//bok -y
				glNormal3f( 0.0,	-1.0,	0.0 );
				glVertex3f( 0.0,	0.0,	0.0 );
				glVertex3f( x,		0.0,  z );
				glVertex3f( xn,		0.0,	zn );
			glEnd();
		glPopMatrix();

	}
}

void drawCrankSmallArm(float height, float depth, float width){
	int segments = 8;
	float x,y,z, xn,zn, angle;
	float r = 3*depth;
	angle = ( PI / (float)segments) ;

	drawRectangle(height,width,depth);
	for(int i=0; i<segments; i++){
		x = cos((float)i*angle)*depth;
		z = sin((float)i*angle)*depth;
		xn = cos((float)(i+1)*angle)*depth;
		zn = sin((float)(i+1)*angle)*depth;
		glPushMatrix();
		glRotatef(0.0, 0.0, 1.0, 0.0);
		glTranslatef( 0.0, -0.5*depth, height );
			glBegin(GL_QUADS);							//polokrag pedal
				glNormal3f( x,	0.0,	z );
				glVertex3f( x,	0.0,	z );
				glNormal3f( x,	0.0,	z );
				glVertex3f( x,  depth,  z );
				glNormal3f( xn,	0.0,	zn );
				glVertex3f( xn,	depth,	zn );
				glNormal3f( xn,	0.0,	zn );
				glVertex3f( xn,	0.0,	zn );
			glEnd();
			glBegin(GL_TRIANGLES);							//bok y
				glNormal3f( 0.0,	1.0,	0.0 );
				glVertex3f( 0.0,	depth,	0.0 );
				glVertex3f( x,		depth,  z );
				glVertex3f( xn,		depth,	zn );
			glEnd();
			glBegin(GL_TRIANGLES);							//bok -y
				glNormal3f( 0.0,	-1.0,	0.0 );
				glVertex3f( 0.0,	0.0,	0.0 );
				glVertex3f( x,		0.0,  z );
				glVertex3f( xn,		0.0,	zn );
			glEnd();
		glPopMatrix();
		glPushMatrix();
		glRotatef(180.0, 0.0, 1.0, 0.0);
		glTranslatef( 0.0, -0.5*depth, 0.0 );
			glBegin(GL_QUADS);							//polokrag srodek
				glNormal3f( x,	0.0,	z );
				glVertex3f( x,	0.0,	z );
				glNormal3f( x,	0.0,	z );
				glVertex3f( x,  depth,  z );
				glNormal3f( xn,	0.0,	zn );
				glVertex3f( xn,	depth,	zn );
				glNormal3f( xn,	0.0,	zn );
				glVertex3f( xn,	0.0,	zn );
			glEnd();
			glBegin(GL_TRIANGLES);							//bok y
				glNormal3f( 0.0,	1.0,	0.0 );
				glVertex3f( 0.0,	depth,	0.0 );
				glVertex3f( x,		depth,  z );
				glVertex3f( xn,		depth,	zn );
			glEnd();
			glBegin(GL_TRIANGLES);							//bok -y
				glNormal3f( 0.0,	-1.0,	0.0 );
				glVertex3f( 0.0,	0.0,	0.0 );
				glVertex3f( x,		0.0,  z );
				glVertex3f( xn,		0.0,	zn );
			glEnd();
		glPopMatrix();

	}
}

void drawCrankshaft(float frame_no){
	float radius = 0.5;
	float width = 0.6;
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	glPushMatrix();								//lozyska do tlokow
	glMaterialfv( GL_FRONT, GL_DIFFUSE, Silver );
	glTranslatef( 0.0, 0.0, -0.05 );
	glRotatef( frame_no, 0.0, 0.0, 1.0 );
		glPushMatrix();
			glTranslatef( 0.0, 0.0, -0.25 );
			glPushMatrix();
				glTranslatef( 0.0, 0.5, -1.5 );
				gluCylinder(quadratic,0.1f,0.1f,width,8,1);
			glPopMatrix();
			glPushMatrix();
				glTranslatef( 0.0, -0.5, 0.0 );
				gluCylinder(quadratic,0.1f,0.1f,width,8,1);
			glPopMatrix();
			glPushMatrix();
				glTranslatef( 0.0, -0.5, 1.5 );
				gluCylinder(quadratic,0.1f,0.1f,width,8,1);						//3
			glPopMatrix();
			glPushMatrix();
				glTranslatef( 0.0, 0.5, 3.0 );
				gluCylinder(quadratic,0.1f,0.1f,width,8,1);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();							//lozyska osi glownej
		glTranslatef( 0.0, 0.0, -1.0 );
			glPushMatrix();
				glTranslatef( 0.0, 0.0, -1.5 );
				gluCylinder(quadratic,0.2f,0.2f,width,8,1);
			glPopMatrix();
			glPushMatrix();
				glTranslatef( 0.0, 0.0, 0.0 );
				gluCylinder(quadratic,0.2f,0.2f,width,8,1);
			glPopMatrix();
			glPushMatrix();
				glTranslatef( 0.0, 0.0, 1.5 );
				gluCylinder(quadratic,0.2f,0.2f,width,8,1);
			glPopMatrix();
			glPushMatrix();
				glTranslatef( 0.0, 0.0, 3.0 );
				gluCylinder(quadratic,0.2f,0.2f,width,8,1);
			glPopMatrix();
			glPushMatrix();
				glTranslatef( 0.0, 0.0, 4.5 );
				gluCylinder(quadratic,0.2f,0.2f,width,8,1);
			glPopMatrix();
		glPopMatrix();

		// pionowe
		glPushMatrix();
			glTranslatef( 0.0, 0.0, 1.9 );
			glRotatef( 90, 1.0, 0.0, 0.0 );
			glTranslatef( 0.0, 0.0, -0.0 );
			drawCrankSmallArm(0.5,0.2,0.4);										//3
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, 0.0, 1.2 );
			glRotatef( 90, 1.0, 0.0, 0.0 );
			glTranslatef( 0.0, 0.0, -0.5 );
			drawCrankArm(1.0,0.2,0.4);
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, 0.0, 0.4 );
			glRotatef( 90, 1.0, 0.0, 0.0 );
			glTranslatef( 0.0, 0.0, -0.5 );
			drawCrankArm(1.0,0.2,0.4);
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, 0.0, 3.4 );
			glRotatef( 90, -1.0, 0.0, 0.0 );
			glTranslatef( 0.0, 0.0, -0.5 );
			drawCrankArm(1.0,0.2,0.4);//1
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, 0.0, 2.7 );
			glRotatef( 90, -1.0, 0.0, 0.0 );
			glTranslatef( 0.0, 0.0, -0.0 );
			drawCrankSmallArm(0.5,0.2,0.4);//3
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, 0.0, -0.3 );
			glRotatef( 90, 1.0, 0.0, 0.0 );
			glTranslatef( 0.0, 0.0, -0.0 );
			drawCrankSmallArm(0.5,0.2,0.4);//3
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, 0.0, -1.1 );
			glRotatef( 90, -1.0, 0.0, 0.0 );
			glTranslatef( 0.0, 0.0, -0.0 );
			drawCrankSmallArm(0.5,0.2,0.4);//3
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, 0.0, -1.8 );
			glRotatef( 90, -1.0, 0.0, 0.0 );
			glTranslatef( 0.0, 0.0, -0.5 );
			drawCrankArm(1.0,0.2,0.4);//8
		glPopMatrix();
	
	glPopMatrix();
}

void drawSphere(){
	static bool first = true;

	GLfloat torus_diffuse[]  = { 0.9, 0.9, 0.9, 1.0 };
	int segments = 30;
	float radius= 3;
	float x,y,z, angleI, angleO, radiusI;
	angleO = ((PI/2.0) / (float)segments) ;
		for(int i=0; i<segments; i++){
			x = sin((float)i* angleO) * radius;
			z = cos((float)i* angleO) * radius;
			angleI = ((PI/2.0) / (float)segments)  ;
			radiusI = x;
			for(int j=0; j <= segments; j++){
				if(x !=0.0){
					//y korzysta z x jako "promienia"
					//petla w plaszczyznie z
					y = sin((float)j*angleI) * radiusI;
					x = cos((float)j*angleI) * radiusI;
					glPushMatrix();
						glMaterialfv( GL_FRONT, GL_DIFFUSE, torus_diffuse );
						glTranslatef( x, y, z );
						glutSolidCube( 0.1 ); //z +1
					glPopMatrix();
				}
			}
		}	
	first = false;
}

void drawBottom(){
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	glPushMatrix();
		glTranslatef( 0, -1.2, -2.5 );
		drawRectangle(6.5,1,0.25);
		glPushMatrix();	
			glTranslatef( 0.0, 1.5, 1.45 );
			glPushMatrix();
				glTranslatef( 0.0, -0.85, -1.4 );
				drawRectangle(0.4, 0.8, 1.05);
			glPopMatrix();
			glPushMatrix();
				glTranslatef( 0.0, -0.85, 0.1 );
				drawRectangle(0.4, 0.8, 1.05);
			glPopMatrix();
			glPushMatrix();
				glTranslatef( 0.0, -0.85, 1.6 );
				drawRectangle(0.4, 0.8, 1.05);
			glPopMatrix();
			glPushMatrix();
				glTranslatef( 0.0, -0.85, 3.1 );
				drawRectangle(0.4, 0.8, 1.05);
			glPopMatrix();
			glPushMatrix();
				glTranslatef( 0.0, -0.85, 4.6 );
				drawRectangle(0.4, 0.8, 1.05);
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();
}

void drawHoleBox(bool a, bool b, bool c, bool d, bool connectorRight, bool connectorLeft, bool transSwitch){
	float width =1.5;
	float height =1.5;
	float depth =1.5;

	int segments = 32;
	float radius = 0.9;
	float x,y, z,xt,zt, sx, sz, tmpx, tmpz;
	float angle;
	float normal, hShifter;

	for (int i = 0; i < segments*8/8; i++){
		angle = (2* PI / (float)segments) ;
		x  =  sin( ((float)i  ) * angle) * radius;			//curr x
		z  =  cos( ((float)i  ) * angle) * radius;			//curr z
		xt =  sin( ((float)i+1) * angle) * radius;			//next x
		zt =  cos( ((float)i+1) * angle) * radius;			//next z
		y = height;
		glPushMatrix();
			if(transSwitch){
				glDepthMask(GL_FALSE);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
			else
			{
				glDepthMask(GL_TRUE);
			}
			glMaterialfv( GL_FRONT, GL_DIFFUSE, SilverTrans );

			glTranslatef( 0.0, - 0.75* height, 0 );
			glScalef(1.0, 1.6, 1.0);
			glScalef(0.701, 0.701,0.701);
			glPushMatrix();   
				glBegin(GL_QUADS);				//sides
					glNormal3f( -x,	 0.0,  -z );
					glVertex3f( x,	 0.0,  z );
					glNormal3f( -xt, 0.0,  -zt);
					glVertex3f( xt,  0.0,  zt);
					glNormal3f( -xt, 0.0,  -zt);
					glVertex3f( xt,    y,  zt);
					glNormal3f( -x,	 0.0,  -z );
					glVertex3f( x,	   y,  z );
				glEnd();


				if(x>=0.0 && z>= 0.0){ // 1cwiartka
					tmpx = width/2.0;
					tmpz = depth/2.0;
				}
				else if(x<0.0 && z>= 0.0){ // 2cwiartka
					tmpx = -width/2.0;
					tmpz = depth/2.0;
				}
				else if(x<0.0 && z< 0.0){ // 3cwiartka
					tmpx = -width/2.0;
					tmpz = -depth/2.0;
				}
				else if(x>=0.0 && z< 0.0){ // 4cwiartka
					tmpx = width/2.0;
					tmpz = -depth/2.0;
				}

				tmpx = tmpx * 1/0.7001;
				tmpz = tmpz * 1/0.7001;
				for (int j=0; j<2; j++){
					normal =-1.0;
					hShifter = 0.0;
					if(j == 0) {
						normal = 1.0;
						hShifter = 1.0;
					}
					glPushMatrix();
						glBegin(GL_TRIANGLES);				//gora/dol
							glNormal3f( 0.0, normal,  0.0 );
							glVertex3f( x,	 hShifter*height,  z );
							glVertex3f( xt,  hShifter*height,  zt);
							glVertex3f( tmpx,   hShifter*height,  tmpz);
						glEnd();
					glPopMatrix();
				}
			glPopMatrix();
			//,.
		glPopMatrix();
	}


	glPushMatrix();
	glTranslatef( 0.0,  0.75* height, 0 );
	glTranslatef( 0.0, -height, 0 );
	glTranslatef( (-depth)/2.0, (-height)/2.0 , (-width)/2.0 );
	glScalef(1.0, 1.6, 1.0);
	glScalef(1.0, 0.701,1.0);
		glPushMatrix();
			if(a){									//os x 
				glBegin(GL_QUADS);				
					glNormal3f(1.0, 0.0, 0.0 );
					glVertex3f(width, 0.0, 0.0 );
					glVertex3f(width, 0.0, depth );
					glVertex3f(width, height, depth );
					glVertex3f(width, height, 0.0 );
				glEnd();
			}
			if(b){									//os -x
				glBegin(GL_QUADS);				
					glNormal3f(-1.0, 0.0, 0.0 );
					glVertex3f(0.0, 0.0, 0.0 );
					glVertex3f(0.0, 0.0, depth );
					glVertex3f(0.0, height, depth );
					glVertex3f(0.0, height, 0.0 );
				glEnd();
			}
			if(c){									//os z
				glBegin(GL_QUADS);				
					glNormal3f(0.0, 0.0, 1.0);
					glVertex3f(0.0, 0.0, depth);
					glVertex3f(width, 0.0, depth);
					glVertex3f(width, height, depth);
					glVertex3f(0.0, height, depth);
				glEnd();
			}
			if(d){									//os -z
				glBegin(GL_QUADS);						
					glNormal3f(0.0, 0.0, -1.0);
					glVertex3f(0.0, 0.0, 0.0);
					glVertex3f(width, 0.0, 0.0);
					glVertex3f(width, height, 0.0);
					glVertex3f(0.0, height, 0.0);
				glEnd();
			}

			if(connectorRight){									//os -x
				glBegin(GL_QUADS);				
					glNormal3f(1.0, 0.0, 0.0 );
					glVertex3f(0.0, 0.1*height, 0.0 );
					glVertex3f(0.0, 0.1*height, -depth );
					glVertex3f(0.0, height, -depth );
					glVertex3f(0.0, height, 0.0 );
				glEnd();
				glBegin(GL_QUADS);								//botom down
					glNormal3f(0.0, -1.0, 0.0 );
					glVertex3f(0.0, 0.0, 0.0 );
					glVertex3f(0.0, 0.0, -depth );
					glVertex3f(width, 0.0, -depth );
					glVertex3f(width, 0.0, 0.0 );
				glEnd();
				glBegin(GL_QUADS);								//botom up
					glNormal3f(0.0, 1.0, 0.0 );
					glVertex3f(0.0, 0.1*height, 0.0 );
					glVertex3f(0.0, 0.1*height, -depth );
					glVertex3f(width, 0.0, -depth );
					glVertex3f(width, 0.0, 0.0 );
				glEnd();
			}
			if(connectorLeft){									//os x 
				glBegin(GL_QUADS);				
					glNormal3f(-1.0, 0.0, 0.0 );
					glVertex3f(width, 0.1*height, 0.0 );
					glVertex3f(width, 0.1*height, -depth );
					glVertex3f(width, height, -depth );
					glVertex3f(width, height, 0.0 );
				glEnd();
				glBegin(GL_QUADS);								//bottom down	
					glNormal3f(0.0, -1.0, 0.0 );
					glVertex3f(width, 0.0, 0.0 );
					glVertex3f(width, 0.0, -depth );
					glVertex3f(0.0, 0.0, -depth );
					glVertex3f(0.0, 0.0, 0.0 );
				glEnd();
				glBegin(GL_QUADS);								//bottom up	
					glNormal3f(0.0, 1.0, 0.0 );
					glVertex3f(width, 0.1*height, 0.0 );
					glVertex3f(width, 0.1*height, -depth );
					glVertex3f(0.0, 0.0, -depth );
					glVertex3f(0.0, 0.0, 0.0 );
				glEnd();
			}

		glPopMatrix();

		for (int j=0; j<2; j++){
				normal =-1.0;
				hShifter = 0.0;
			if(j == 0) {
				normal = 1.0;
				hShifter = 1.0;
			}
		glPushMatrix();
				glBegin(GL_TRIANGLES);											//bok
					glNormal3f( 0.0, normal,  0.0 );
					glVertex3f( 0.0, hShifter*height,  0.0 );
					glVertex3f( width*0.5, hShifter*height, (depth - radius*2*0.701)/2.0 );
					glVertex3f( width, hShifter*height,  0.0 );
				glEnd();
				glBegin(GL_TRIANGLES);											//bok
					glNormal3f( 0.0, normal,  0.0 );
					glVertex3f( 0.0, hShifter*height,  0.0 );
					glVertex3f( (width - radius*2*0.701)/2.0, hShifter*height,  width/2.0 );
					glVertex3f( 0.0, hShifter*height,  depth );
				glEnd();
				glBegin(GL_TRIANGLES);											//bok
					glNormal3f( 0.0, normal,  0.0 );
					glVertex3f( 0.0, hShifter*height,  depth );
					glVertex3f( width*0.5, hShifter*height,  radius*2*0.701+(depth - radius*2*0.701)/2.0 );
					glVertex3f( width, hShifter*height,  depth );
				glEnd();
				glBegin(GL_TRIANGLES);											//bok
					glNormal3f( 0.0, normal,  0.0 );
					glVertex3f( width, hShifter*height,  depth );
					glVertex3f( radius*2*0.701+(width - radius*2*0.701)/2.0, hShifter*height,  depth*0.5 );
					glVertex3f( width, hShifter*height,  0.0 );
				glEnd();
		glPopMatrix();
		}
		if(transSwitch){
			glDisable(GL_BLEND);
		}
	glPopMatrix();
}

void draw4Holes(bool transSwitch){
	glPushMatrix();
	//glEnable(GL_BLEND);         // W³¹cz mieszanie kolorów
	//glColor4f(0.1f,0.1,0.1,0.9f);
	glTranslatef( 0.0, 0.2*12.5, 0.0 );
		glPushMatrix();
			glTranslatef( 0.0, 0.0 , -1.5 );
			glPushMatrix();
				drawHoleBox(true,true,false,true,false,false,transSwitch);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, 0.0, 0.0 );
			glPushMatrix();
				drawHoleBox(true,true,false,false,false,false,transSwitch);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, 0.0, 1.5 );
			glPushMatrix();
				drawHoleBox(true,true,false,false,false,false,transSwitch);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, 0.0, 3.0 );
			glPushMatrix();
				drawHoleBox(true,true,true,false,false,false,transSwitch);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void drawValve(){

	int segments = 32;
	float height = 1.0;
	float radius = 0.9;
	float x,y, z,xt,zt, yt, xh, zh,xth, zth, xh2, zh2,xth2, zth2;
	float angle;

	for (int i = 0; i < segments*8/8; i++){
		angle = (2* PI / (float)segments) ;
		x  =  sin( ((float)i  ) * angle) * radius;			//curr x
		z  =  cos( ((float)i  ) * angle) * radius;			//curr z
		xt =  sin( ((float)i+1) * angle) * radius;			//next x
		zt =  cos( ((float)i+1) * angle) * radius;			//next z
		y = height;

		glPushMatrix();
			//glRotatef(90, 1.0, 0.0, 0.0);
			glScalef(1.0,0.3,1.0);
			glPushMatrix();
					//glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );    
					glBegin(GL_TRIANGLES);				//bottom
						glNormal3f( 0.0,	-1.0,	0.0);
						glVertex3f( x,		0.0,	z );
						glVertex3f( xt,		0.0,	zt);
						glVertex3f( 0.0,	0.0,	0.0);
					glEnd();
			glPopMatrix();
			glPushMatrix();
					//glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );    
					glBegin(GL_TRIANGLES);				//top
						glNormal3f( 0.0,		1.0,	0.0);
						glVertex3f( 0.15*x,		9.25*y,	0.15*z );
						glVertex3f( 0.15*xt,	9.25*y,	0.15*zt);
						glVertex3f( 0.0,		9.25*y,	0.0);
					glEnd();
			glPopMatrix();
			glPushMatrix();
				glBegin(GL_QUADS);				//sides
					glNormal3f( x,		0.0,	z );
					glVertex3f( 0.15*x,	9.0,	0.15*z );
					glNormal3f( xt,		0.0,	zt);
					glVertex3f( 0.15*xt, 9.0,	0.15*zt);
					glNormal3f( xt,		0.0,		zt);
					glVertex3f( 0.15*xt, 9.25*y,		0.15*zt);
					glNormal3f( x,		0.0,		z );
					glVertex3f( 0.15*x,	9.25*y,		0.15*z );
				glEnd();
			glPopMatrix();
			glPushMatrix();
				glBegin(GL_QUADS);				//sides
					glNormal3f( x,		0.0,	z );
					glVertex3f( 0.1*x,	0.0,	0.1*z );
					glNormal3f( xt,		0.0,	zt);
					glVertex3f( 0.1*xt, 0.0,	0.1*zt);
					glNormal3f( xt,		0.0,		zt);
					glVertex3f( 0.1*xt, 9.25*y,		0.1*zt);
					glNormal3f( x,		0.0,		z );
					glVertex3f( 0.1*x,	9.25*y,		0.1*z );
				glEnd();
			glPopMatrix();
		for(int j=0; j<8; j++){
			y = (float)j * 0.2;
			yt =(float)(j+1) * 0.2;

			xh =	x  * (1.0 - 0.9*sin((float)(j+0) * angle));
			xth =	xt * (1.0 - 0.9*sin((float)(j+0) * angle));
			zh =	z  * (1.0 - 0.9*sin((float)(j+0) *  angle));
			zth =	zt * (1.0 - 0.9*sin((float)(j+0) * angle));
			xh2 =	x  * (1.0 - 0.9*sin((float)(j+1) * angle));
			xth2 =	xt * (1.0 - 0.9*sin((float)(j+1) * angle));
			zh2 =	z  * (1.0 - 0.9*sin((float)(j+1) * angle));
			zth2 =	zt * (1.0 - 0.9*sin((float)(j+1) * angle));
				glPushMatrix();
					//glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );    
					glBegin(GL_QUADS);				//sides
						glNormal3f( x,			0.0,	z );
						glVertex3f( xh2,			yt,		zh2 );
						glNormal3f( xt,			0.0,	zt);
						glVertex3f( xth2,		yt,		zth2);
						glNormal3f( xt,			0.0,	zt);
						glVertex3f( xth,		y,		zth);
						glNormal3f( x,			0.0,	z );
						glVertex3f( xh,			y,		zh );
					glEnd();
				glPopMatrix();
		}
		glPopMatrix();
	}
    //glEnable(GL_DEPTH_TEST);
}

void drawCamshaftCoverLeft(int frame_no, boolean transparent,bool transSwitch){
	float ycorr = 0.21;
	glPushMatrix();
	//glMaterialfv( GL_FRONT, GL_DIFFUSE, White );
	//glEnable(GL_BLEND);         // W³¹cz mieszanie kolorów
	//glColor4f(0.1f,0.1,0.1,0.9f);
		glPushMatrix();
			glTranslatef( -0.0, ycorr , -1.5 );
			glScalef(0.5,0.7,0.5);
			glPushMatrix();
				glTranslatef(0.0,-1.125,0.0);
				glScalef(0.7,0.6,0.7);
				if(frame_no>450 && frame_no <=630) glTranslatef(0.0,  -0.2*sin((float)(frame_no-450)*(2*PI/360)), 0.0);
				if(!transparent)drawValve();
			glPopMatrix();
			glPushMatrix();
				if(transparent)drawHoleBox(false,true,true,true,false,false,transSwitch);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef( -0.0, ycorr , 0.0 );
			glScalef(0.5,0.7,0.5);
			glPushMatrix();
				glTranslatef(0.0,-1.125,0.0);
				glScalef(0.7,0.6,0.7);
				if(frame_no>270 && frame_no <=450) glTranslatef(0.0,  -0.2*sin((float)(frame_no-270)*(2*PI/360)), 0.0);
				if(!transparent)drawValve();
			glPopMatrix();
			glPushMatrix();
				if(transparent)drawHoleBox(false,true,true,true,false,true,transSwitch);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef( -0.0, ycorr , 1.5 );
			glScalef(0.5,0.7,0.5);
			glPushMatrix();
				if(transparent)drawHoleBox(false,true,true,true,false,true,transSwitch);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0,-1.125,0.0);
				glScalef(0.7,0.6,0.7);
				if(frame_no>630 || frame_no <=90) glTranslatef(0.0,  -0.2*sin((float)(frame_no-630)*(2*PI/360)), 0.0);
				if(!transparent)drawValve();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef( -0.0, ycorr , 3.0 );
			glScalef(0.5,0.7,0.5);
			glPushMatrix();
				if(transparent)drawHoleBox(false,true,true,true,false,true,transSwitch);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0,-1.125,0.0);
				glScalef(0.7,0.6,0.7);
				if(frame_no>90 && frame_no <=270) glTranslatef(0.0,  0.2*sin((float)(frame_no+90)*(2*PI/360)), 0.0);
				if(!transparent)drawValve();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void drawCamshaftCoverRight(int frame_no,bool transparent,bool transSwitch){
	float ycorr = 0.21;
	glPushMatrix();
	//glEnable(GL_BLEND);         // W³¹cz mieszanie kolorów
	//glColor4f(0.1f,0.1,0.1,0.9f);
		glPushMatrix();
			glTranslatef( 0.0, ycorr , -1.5 );
			glScalef(0.5,0.7,0.5);
			glPushMatrix();
				if(transparent)drawHoleBox(true,false,true,true,false,false,transSwitch);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0,-1.125,0.0);
				glScalef(0.7,0.6,0.7);
				if(frame_no>270 && frame_no <=450) glTranslatef(0.0,  -0.2*sin((float)(frame_no-270)*(2*PI/360)), 0.0);
				if(!transparent)drawValve();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, ycorr , 0.0 );
			glScalef(0.5,0.7,0.5);
			glPushMatrix();
				if(transparent)drawHoleBox(true,false,true,true,true,false,transSwitch);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0,-1.125,0.0);
				glScalef(0.7,0.6,0.7);
				if(frame_no>90 && frame_no <=270) glTranslatef(0.0,  0.2*sin((float)(frame_no+90)*(2*PI/360)), 0.0);
				if(!transparent)drawValve();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, ycorr , 1.5 );
			glScalef(0.5,0.7,0.5);
			glPushMatrix();
				if(transparent)drawHoleBox(true,false,true,true,true,false,transSwitch);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0,-1.125,0.0);
				glScalef(0.7,0.6,0.7);
				if(frame_no>450 && frame_no <=630) glTranslatef(0.0,  -0.2*sin((float)(frame_no-450)*(2*PI/360)), 0.0);
				if(!transparent)drawValve();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, ycorr , 3.0 );
			glScalef(0.5,0.7,0.5);
			glPushMatrix();
				if(transparent)drawHoleBox(true,false,true,true,true,false,transSwitch);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0,-1.125,0.0);
				glScalef(0.7,0.6,0.7);
				if(frame_no>630 || frame_no <=90) glTranslatef(0.0,  -0.2*sin((float)(frame_no-630)*(2*PI/360)), 0.0);
				if(!transparent)drawValve();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void drawFlywheel(){

	int segments = 32;
	float height = 1.0;
	float radius = 0.9;
	float x,y, z,xt,zt, xs, zs,xst, zst;
	float angle;

	for (int i = 0; i < segments*8/8; i++){
		angle = (2* PI / (float)segments) ;
		x  =  sin( ((float)i  ) * angle) * radius;			//curr x
		z  =  cos( ((float)i  ) * angle) * radius;			//curr z
		xt =  sin( ((float)i+1) * angle) * radius;			//next x
		zt =  cos( ((float)i+1) * angle) * radius;			//next z
		y = height;

		glPushMatrix();
			glScalef(1.0,0.1,1.0);
			glPushMatrix();
				
				//glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );    
				glBegin(GL_QUADS);				//sides
					glNormal3f( -x,			0.0,	-z );
					glVertex3f( 0.2*x,		y-0.9,	0.2*z );
					glNormal3f( -xt,		0.0,	-zt);
					glVertex3f( 0.2*xt,		y-0.9,	0.2*zt);
					glNormal3f( -xt,		y,		-zt);
					glVertex3f( 0.2*xt,		-1.6,	0.2*zt);
					glNormal3f( -x,			y,		-z );
					glVertex3f( 0.2*x,		-1.6,	0.2*z );
				glEnd();
			glPopMatrix();

			glPushMatrix();
				
//				glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );    
				glBegin(GL_QUADS);				//tyl zew
					glNormal3f( 0.0,		-1.0,	0.0 );
					glVertex3f( 0.2*x,		0.0,	0.2*z );
					glVertex3f( 0.2*xt,		0.0,	0.2*zt);
					glVertex3f( xt,			0.0,		zt);
					glVertex3f( x,			0.0,		z );
				glEnd();
				glBegin(GL_QUADS);				//przod zew
					glNormal3f( 0.0,		1.0,	0.0 );
					glVertex3f( 0.7*x,		y,	0.7*z );
					glVertex3f( 0.7*xt,		y,	0.7*zt);
					glVertex3f( xt,			y,		zt);
					glVertex3f( x,			y,		z );
				glEnd();
				glBegin(GL_QUADS);				//przod pol 1
					glNormal3f( -0.7*x,		0.0,	-0.7*z );
					glVertex3f( 0.7*x,		y,	0.7*z );
					glVertex3f( 0.7*xt,		y,	0.7*zt);
					glVertex3f( 0.7*xt,		y-0.5,	0.7*zt);
					glVertex3f( 0.7*x,		y-0.5,	0.7*z );
				glEnd();
				glBegin(GL_QUADS);				//przod sro
					glNormal3f( 0.0,		1.0,	0.0 );
					glVertex3f( 0.7*x,		y-0.5,	0.7*z );
					glVertex3f( 0.7*xt,		y-0.5,	0.7*zt);
					glVertex3f( 0.4*xt,		y-0.5,	0.4*zt);
					glVertex3f( 0.4*x,		y-0.5,	0.4*z );
				glEnd();
				glBegin(GL_QUADS);				//przod pol 1
					glNormal3f( -0.7*x,		0.0,	-0.7*z );
					glVertex3f( 0.4*x,		y-0.5,	0.4*z );
					glVertex3f( 0.4*xt,		y-0.5,	0.4*zt);
					glVertex3f( 0.4*xt,		y-0.9,	0.4*zt);
					glVertex3f( 0.4*x,		y-0.9,	0.4*z );
				glEnd();
				glBegin(GL_QUADS);				//przod wew
					glNormal3f( 0.0,		1.0,	0.0 );
					glVertex3f( 0.4*x,		y-0.9,	0.4*z );
					glVertex3f( 0.4*xt,		y-0.9,	0.4*zt);
					glVertex3f( 0.2*xt,		y-0.9,	0.2*zt);
					glVertex3f( 0.2*x,		y-0.9,	0.2*z );
				glEnd();
			glPopMatrix();



			xs=x*1.1;
			zs=z*1.1;
			xst=xt*1.1;
			zst=zt*1.1;

			glPushMatrix();
				//glScalef(1.0,0.2,1.0);
//				glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );    
				glBegin(GL_QUADS);				//sides
					glNormal3f( xs,		0.0,	zs );
					glVertex3f( xs,		0.0,	zs );
					glNormal3f( xst,		0.0,	zst);
					glVertex3f( xst,		0.0,	zst);
					glNormal3f( xst,		y,		zst);
					glVertex3f( xst,		y,		zst);
					glNormal3f( xs,		y,		zs );
					glVertex3f( xs,		y,		zs );
				glEnd();
			glPopMatrix();

			glPushMatrix();
				//glScalef(1.0,0.2,1.0);
//				glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );    
				glBegin(GL_QUADS);				//sides
					glNormal3f( 0.0,	y,	0.0 );
					glVertex3f( x,		y,	z );
					glVertex3f( xs,		y,	zs);
					glVertex3f( xst,	y,	zst);
					glVertex3f( xt,		y,	zt );
				glEnd();
			glPopMatrix();

			glPushMatrix();
				//glScalef(1.0,0.2,1.0);
//				glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );    
				glBegin(GL_QUADS);				//sides
					glNormal3f( 0.0,	-y,	0.0 );
					glVertex3f( x,		0.0,	z );
					glVertex3f( xs,		0.0,	zs);
					glVertex3f( xst,	0.0,	zst);
					glVertex3f( xt,		0.0,	zt );
				glEnd();
			glPopMatrix();
		glPopMatrix();
	}
    //glEnable(GL_DEPTH_TEST);
}


void drawCog(int segments){

	float height = 1.0;
	float radius = 0.9;
	float x,y, z,xt,zt, xs, zs,xst, zst;
	float angle;

	for (int i = 0; i < segments*8/8; i++){
		angle = (2* PI / (float)segments) ;
		x  =  sin( ((float)i  ) * angle) * radius;			//curr x
		z  =  cos( ((float)i  ) * angle) * radius;			//curr z
		xt =  sin( ((float)i+1) * angle) * radius;			//next x
		zt =  cos( ((float)i+1) * angle) * radius;			//next z
		y = height;

		glPushMatrix();
			glScalef(1.0,0.1,1.0);
			glPushMatrix();
				
				//glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );    
				glBegin(GL_QUADS);				//sides
					glNormal3f( -x,			0.0,	-z );
					glVertex3f( 0.2*x,		y-0.9,	0.2*z );
					glNormal3f( -xt,		0.0,	-zt);
					glVertex3f( 0.2*xt,		y-0.9,	0.2*zt);
					glNormal3f( -xt,		y,		-zt);
					glVertex3f( 0.2*xt,		-1.6,	0.2*zt);
					glNormal3f( -x,			y,		-z );
					glVertex3f( 0.2*x,		-1.6,	0.2*z );
				glEnd();
			glPopMatrix();

			glPushMatrix();
				
//				glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );    
				glBegin(GL_QUADS);				//tyl zew
					glNormal3f( 0.0,		-1.0,	0.0 );
					glVertex3f( 0.5*x,		0.0,	0.5*z );
					glVertex3f( 0.5*xt,		0.0,	0.5*zt);
					glVertex3f( xt,			0.0,		zt);
					glVertex3f( x,			0.0,		z );
				glEnd();
				glBegin(GL_QUADS);				//tyl pol
					glNormal3f( 0.5*x,		0.0,	0.5*z );
					glVertex3f( 0.5*x,		0.0,	0.5*z );
					glVertex3f( 0.5*xt,		0.0,	0.5*zt);
					glVertex3f( 0.5*xt,		-1.6,	0.5*zt);
					glVertex3f( 0.5*x,		-1.6,	0.5*z );
				glEnd();
				glBegin(GL_QUADS);				//tyl wew
					glNormal3f( 0.0,		-1.0,	0.0 );
					glVertex3f( 0.5*x,		-1.6,	0.5*z );
					glVertex3f( 0.5*xt,		-1.6,	0.5*zt);
					glVertex3f( 0.2*xt,		-1.6,	0.2*zt);
					glVertex3f( 0.2*x,		-1.6,	0.2*z );
				glEnd();
				glBegin(GL_QUADS);				//przod zew
					glNormal3f( 0.0,		1.0,	0.0 );
					glVertex3f( 0.7*x,		y,	0.7*z );
					glVertex3f( 0.7*xt,		y,	0.7*zt);
					glVertex3f( xt,			y,		zt);
					glVertex3f( x,			y,		z );
				glEnd();
				glBegin(GL_QUADS);				//przod pol 1
					glNormal3f( -0.7*x,		0.0,	-0.7*z );
					glVertex3f( 0.7*x,		y,	0.7*z );
					glVertex3f( 0.7*xt,		y,	0.7*zt);
					glVertex3f( 0.7*xt,		y-0.5,	0.7*zt);
					glVertex3f( 0.7*x,		y-0.5,	0.7*z );
				glEnd();
				glBegin(GL_QUADS);				//przod sro
					glNormal3f( 0.0,		1.0,	0.0 );
					glVertex3f( 0.7*x,		y-0.5,	0.7*z );
					glVertex3f( 0.7*xt,		y-0.5,	0.7*zt);
					glVertex3f( 0.4*xt,		y-0.5,	0.4*zt);
					glVertex3f( 0.4*x,		y-0.5,	0.4*z );
				glEnd();
				glBegin(GL_QUADS);				//przod pol 1
					glNormal3f( -0.7*x,		0.0,	-0.7*z );
					glVertex3f( 0.4*x,		y-0.5,	0.4*z );
					glVertex3f( 0.4*xt,		y-0.5,	0.4*zt);
					glVertex3f( 0.4*xt,		y-0.9,	0.4*zt);
					glVertex3f( 0.4*x,		y-0.9,	0.4*z );
				glEnd();
				glBegin(GL_QUADS);				//przod wew
					glNormal3f( 0.0,		1.0,	0.0 );
					glVertex3f( 0.4*x,		y-0.9,	0.4*z );
					glVertex3f( 0.4*xt,		y-0.9,	0.4*zt);
					glVertex3f( 0.2*xt,		y-0.9,	0.2*zt);
					glVertex3f( 0.2*x,		y-0.9,	0.2*z );
				glEnd();
			glPopMatrix();


			if(i%2 == 0){
				if(segments<=32){
					xs=x*1.1;
					zs=z*1.1;
					xst=xt*1.4;
					zst=zt*1.4;
				}
				else{
					xs=x*1.1;
					zs=z*1.1;
					xst=xt*1.3;
					zst=zt*1.3;
				}
			}
			else{
				if(segments<=32){
					xs=x*1.4;
					zs=z*1.4;
					xst=xt*1.1;
					zst=zt*1.1;
				}
				else{
					xs=x*1.3;
					zs=z*1.3;
					xst=xt*1.1;
					zst=zt*1.1;
				}
			}
			glPushMatrix();
				//glScalef(1.0,0.2,1.0);
//				glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );    
				glBegin(GL_QUADS);				//sides
					glNormal3f( xs,		0.0,	zs );
					glVertex3f( xs,		0.0,	zs );
					glNormal3f( xst,		0.0,	zst);
					glVertex3f( xst,		0.0,	zst);
					glNormal3f( xst,		y,		zst);
					glVertex3f( xst,		y,		zst);
					glNormal3f( xs,		y,		zs );
					glVertex3f( xs,		y,		zs );
				glEnd();
			glPopMatrix();

			glPushMatrix();
				//glScalef(1.0,0.2,1.0);
//				glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );    
				glBegin(GL_QUADS);				//sides
					glNormal3f( 0.0,	y,	0.0 );
					glVertex3f( x,		y,	z );
					glVertex3f( xs,		y,	zs);
					glVertex3f( xst,	y,	zst);
					glVertex3f( xt,		y,	zt );
				glEnd();
			glPopMatrix();

			glPushMatrix();
				//glScalef(1.0,0.2,1.0);
//				glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );    
				glBegin(GL_QUADS);				//sides
					glNormal3f( 0.0,	-y,	0.0 );
					glVertex3f( x,		0.0,	z );
					glVertex3f( xs,		0.0,	zs);
					glVertex3f( xst,	0.0,	zst);
					glVertex3f( xt,		0.0,	zt );
				glEnd();
			glPopMatrix();
		glPopMatrix();
	}
    //glEnable(GL_DEPTH_TEST);
}

void drawTriangle(){
	glPushMatrix();	
		glTranslatef(0.25,0.0,0.0);
		glRotatef(180,0.0,1.0,0.0);
		glBegin(GL_QUADS);				//bok
			glNormal3f( 0.0,	1.0,	1.0 );
			glVertex3f( 0.0,	0.0,	0.5 );
			glVertex3f( 0.5,	0.0,	0.5);
			glVertex3f( 0.5,	0.5,	0.0);
			glVertex3f( 0.0,	0.5,	0.0 );
		glEnd();
	glPopMatrix();
}

void drawFlywheelExt(){

	int segments = 32;
	float height = 1.0;
	float radius = 0.9;
	float x,y, z,xt,zt, xs, zs,xst, zst;
	float angle;

	angle = (2* PI / (float)segments) ;

	for (int i = 0; i < segments*8/8; i++){	
		x  =  sin( ((float)i  ) * angle) * radius;			//curr x
		z  =  cos( ((float)i  ) * angle) * radius;			//curr z
		xt =  sin( ((float)i+1) * angle) * radius;			//next x
		zt =  cos( ((float)i+1) * angle) * radius;			//next z
		y = height;

		x*=1.2;
		xt*=1.2;
		z*=1.2;
		zt*=1.2;

		y*=0.1;

		glPushMatrix();
			glScalef(1.0,1.0,1.0);
			glPushMatrix();
				glBegin(GL_QUADS);				//sides
					glNormal3f( x,		0.0,	z );
					glVertex3f( x,		y,		z );
					glNormal3f( xt,		0.0,	zt);
					glVertex3f( xt,		y,		zt);
					glNormal3f( xt,		y,		zt);
					glVertex3f( xt,		3*y,	zt);
					glNormal3f( x,		y,		z );
					glVertex3f( x,		3*y,	z );
				glEnd();
			glPopMatrix();
			glPushMatrix();	
				glBegin(GL_QUADS);				//bok
					glNormal3f( 0.0,	1.0,	0.0 );
					glVertex3f( 0.95*x,	3*y,	0.95*z );
					glVertex3f( 0.95*xt,	3*y,	0.95*zt);
					glVertex3f( xt,		3*y,	zt);
					glVertex3f( x,		3*y,	z );
				glEnd();
			glPopMatrix();
			glPushMatrix();	
				glBegin(GL_QUADS);				//bok
					glNormal3f( 0.0,	-1.0,	0.0 );
					glVertex3f( 0.95*x,	y+0.01,	0.95*z );
					glVertex3f( 0.95*xt,	y+0.01,	0.95*zt);
					glVertex3f( xt,		y+0.01,	zt);
					glVertex3f( x,		y+0.01,	z );
				glEnd();
			glPopMatrix();
			glPushMatrix();
				glBegin(GL_QUADS);				//sides
					glNormal3f( -x,			0.0,		-z );
					glVertex3f( 0.95*x,		y,			0.95*z );
					glNormal3f( -xt,		0.0,		-zt);
					glVertex3f( 0.95*xt,	y,			0.95*zt);
					glNormal3f( -xt,		y,			-zt);
					glVertex3f( 0.95*xt,	3*y,		0.95*zt);
					glNormal3f( -x,			y,			-z );
					glVertex3f( 0.95*x,		3*y,		0.95*z );
				glEnd();
			glPopMatrix();

			if(i%8==0){
				glPushMatrix();
				glScalef(0.5,0.5,0.5);
				glTranslatef(1.9*x,y,1.9*z);
					glRotatef(i*360/segments, 0.0, 1.0, 0.0);
					//glRotatef(-90, 0.0, 1.0, 0.0);
					drawTriangle();
				glPopMatrix();
			}
			
		glPopMatrix();
	}
}

void drawCamshaftInvoker(){
	int segments = 32;
	float height = 1.0;
	float radius = 0.9;
	float x,y, z,xt,zt, sx, sz, sxt, szt;
	float angle;
	float helper;

	for (int i = 0; i < segments*8/8; i++){
		angle = (2* PI / (float)segments) ;
		x  =  sin( ((float)i  ) * angle) * radius;			//curr x
		z  =  cos( ((float)i  ) * angle) * radius;			//curr z
		xt =  sin( ((float)i+1) * angle) * radius;			//next x
		zt =  cos( ((float)i+1) * angle) * radius;			//next z
		y = height;
		glPushMatrix();
			glTranslatef( 0.0, -0.2 * height, 0 );
			glPushMatrix();
				//glMaterialfv( GL_FRONT, GL_DIFFUSE, Blue );    
				//glTranslatef( x, 0.0, z );
				if(i < segments/2){
					helper = 0.5* sin(((float)i) * angle);
					helper = helper * helper * helper * helper ; 
					x  *= (1+ 10*helper);
					z  *= (1+ 10*helper);
					helper = 0.5* sin(((float)i+1) * angle);
					helper = helper * helper * helper * helper ;
					xt *= (1+ 10*helper);
					zt *= (1+ 10*helper);
				}
				glBegin(GL_QUADS);				//sides
					glNormal3f( x,	 0.0,  z );
					glVertex3f( x,	 0.0,  z );
					glNormal3f( xt,	 0.0,  zt);
					glVertex3f( xt,  0.0,  zt);
					glNormal3f( xt,	   y,  zt);
					glVertex3f( xt,    y,  zt);
					glNormal3f( x,	   y,  z );
					glVertex3f( x,	   y,  z );
				glEnd();
				glBegin(GL_TRIANGLES);			//top
					glNormal3f( 0.0, 1.0, 0.0);
					glVertex3f( 0.0,	y, 0.0);
					glVertex3f(	x,	   y,   z);
					glVertex3f( xt,    y,  zt);
				glEnd(); 
				glBegin(GL_TRIANGLES);				//bottom
					glNormal3f( 0.0,-1.0,0.0 );
					glVertex3f(   x, 0.0,  z );
					glVertex3f(  xt, 0.0, zt );
					glVertex3f( 0.0, 0.0, 0.0);
				glEnd();
			glPopMatrix();
		glPopMatrix();
	}
}

void drawCamshaftInvokers(){
	glPushMatrix();
	glTranslatef(0.0, 0.0, 2.64);
		glPushMatrix();
			glTranslatef(0.0, 0.0, -1.5);
			glScalef(0.15,0.15,0.15);
			glRotatef(90.0, 1.0, 0.0, 0.0);
			glRotatef(0.0, 0.0, 1.0, 0.0);
			drawCamshaftInvoker();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, 0.0, 0.0);
			glScalef(0.15,0.15,0.15);
			glRotatef(90.0, 1.0, 0.0, 0.0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			drawCamshaftInvoker();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, 0.0, 1.5);
			glScalef(0.15,0.15,0.15);
			glRotatef(90.0, 1.0, 0.0, 0.0);
			glRotatef(270.0, 0.0, 1.0, 0.0);
			drawCamshaftInvoker();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, 0.0, 3.0);
			glScalef(0.15,0.15,0.15);
			glRotatef(90.0, 1.0, 0.0, 0.0);
			glRotatef(180.0, 0.0, 1.0, 0.0);
			drawCamshaftInvoker();
		glPopMatrix();
	glPopMatrix();
}

void drawCamshaftMechanism(bool rotate, int frame_no){
	float width = 6.0;
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	glPushMatrix();
		glRotatef( (float)frame_no/2.0, 0.0, 0.0, 1.0 );
		gluCylinder(quadratic,0.1f,0.1f,width,8,1);
	glPopMatrix();
	glPushMatrix();
		glRotatef( (float)frame_no/2.0, 0.0, 0.0, 1.0 );
		if(rotate){
			glRotatef(90.0, 0.0, 0.0, 1.0);
		}
		drawCamshaftInvokers();
	glPopMatrix();
}

void drawCamshaft(bool rotate, int frame_no){
	glPushMatrix();
		//glMaterialfv( GL_FRONT, GL_DIFFUSE, Black );
		glTranslatef(0.0,0.35*1.5+0.2,-2.7);
		drawCamshaftMechanism(rotate, frame_no);
		glPushMatrix();
			glRotatef(90,1.0,0.0,0.0);
			glScalef(0.5,0.5,0.5);
			glRotatef( (float)frame_no/2.0, 0.0, 1.0, 0.0 );
			drawCog(64);
		glPopMatrix();
	glPopMatrix();
}

void drawCovers(int frame_no, bool transSwitch){
	glPushMatrix();
		glMaterialfv( GL_FRONT, GL_DIFFUSE, Silver );
		glPushMatrix();
			glMaterialfv( GL_FRONT, GL_DIFFUSE, Brown );
			drawBottom();
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, 0.308*12.5, 0.0 );
			glRotatef(-15.0, 0.0, 0.0, 1.0);
			glTranslatef( 0.5295, 0.0 , 0.0 );
			glPushMatrix();
				glMaterialfv( GL_FRONT, GL_DIFFUSE, Red );
				drawCamshaft(true, frame_no);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, 0.308*12.5, 0.0 );
			glRotatef(15.0, 0.0, 0.0, 1.0);
			glTranslatef( -0.5295, 0.0 , 0.0 );
			glPushMatrix();
				glMaterialfv( GL_FRONT, GL_DIFFUSE, Red );
				drawCamshaft(false, frame_no);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, 0.308*12.5, 0.0 );
			glRotatef(-15.0, 0.0, 0.0, 1.0);
			glTranslatef( 0.5295, 0.0 , 0.0 );
			glPushMatrix();
				glMaterialfv( GL_FRONT, GL_DIFFUSE, Silver );
				drawCamshaftCoverRight(frame_no,false,transSwitch);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, 0.308*12.5, 0.0 );
			glRotatef(15.0, 0.0, 0.0, 1.0);
			glTranslatef( -0.5295, 0.0 , 0.0 );
			glPushMatrix();	
				drawCamshaftCoverLeft(frame_no,false,transSwitch);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, 0.308*12.5, 0.0 );
			glRotatef(-15.0, 0.0, 0.0, 1.0);
			glTranslatef( 0.5295, 0.0 , 0.0 );
			glPushMatrix();
				glMaterialfv( GL_FRONT, GL_DIFFUSE, Silver );
				drawCamshaftCoverRight(frame_no,true,transSwitch);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef( 0.0, 0.308*12.5, 0.0 );
			glRotatef(15.0, 0.0, 0.0, 1.0);
			glTranslatef( -0.5295, 0.0 , 0.0 );
			glPushMatrix();	
				drawCamshaftCoverLeft(frame_no,true,transSwitch);
			glPopMatrix();
		glPopMatrix();
		float width = 0.61;
		glPushMatrix();
			if(transSwitch){
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
			glMaterialfv( GL_FRONT, GL_DIFFUSE, SilverTrans );
			glPushMatrix();
				glTranslatef( -width/2.0, 4.3899, 0.0 );
				glScalef(width,1.0,1.0);
				glBegin(GL_QUADS);	
					glNormal3f(0.0, 1.0, 0.0 );
					glVertex3f(0.0, 0.0, -1.875 );
					glVertex3f(1.0, 0.0, -1.875 );
					glVertex3f(1.0, 0.0, 3.375 );
					glVertex3f(0.0, 0.0, 3.375 );
				glEnd();
			glPopMatrix();
			glPushMatrix();
				glTranslatef( -0.0, 3.3899, 0.0 );
				glScalef(width,1.0,1.0);
				glBegin(GL_TRIANGLES);	
					glNormal3f(0.0, 0.0, 1.0 );
					glVertex3f(0.0, -0.15, 3.375 );
					glVertex3f(0.5, 1.0, 3.375 );
					glVertex3f(-0.5, 1.0, 3.375 );
				glEnd();
			glPopMatrix();
			glPushMatrix();
				glTranslatef( -0.0, 3.3899, 0.0 );
				glScalef(width,1.0,1.0);
				glBegin(GL_TRIANGLES);	
					glNormal3f(0.0, 0.0, -1.0 );
					glVertex3f(0.0, -0.15, -1.875 );
					glVertex3f(0.5, 1.0, -1.875 );
					glVertex3f(-0.5, 1.0, -1.875 );
				glEnd();
			glPopMatrix();
			if(transSwitch){
				glDisable(GL_BLEND);
			}
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		//glDisable(GL_DEPTH_TEST);
		//glDepthFunc(GL_FALSE);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glMaterialfv( GL_FRONT, GL_DIFFUSE, SilverTrans );
		draw4Holes(transSwitch);
		//glDisable(GL_BLEND);
		//glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_TRUE);
	glPopMatrix();
}



void putFlywheel(float frame_no){
	//glDisable(GL_BLEND);
	//glDepthMask(TRUE);
	glPushMatrix();
	glMaterialfv( GL_FRONT, GL_DIFFUSE, Silver );
		glRotatef(frame_no, 0.0, 0.0,1.0);
		glScalef(1.0,1.0,1.0);
		glTranslatef(0.0,0.0,-2.7);
		glRotatef(-90.0, 1.0, 0.0,0.0);
		drawFlywheel();
		drawFlywheelExt();
		glPushMatrix();
			glScalef(0.25,0.5,0.25);
			glTranslatef(0.0,-0.32,0.0);
			drawCog(32);
		glPopMatrix();
	glPopMatrix();
}

void drawTablePiece(){
	glPushMatrix();
		glTranslatef(0.0, 0.0, 3.5);
		glRotatef(90.0, 0.0,0.0,1.0);
		glPushMatrix();
			drawRectangle(0.2,0.2,10.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1.0, 0.0, 0.0);
			drawRectangle(0.2,0.2,10.0);
		glPopMatrix();

		for(int i=-2; i<3; i++){
			glPushMatrix();
				glTranslatef(-0.5, 2.0 * (float)i , 0.0);
				glRotatef(45.0, 0.0,0.0,1.0);
				drawRectangle(0.1,0.1,1.4);
			glPopMatrix();
		}
		for(int i=-2; i<2; i++){
			glPushMatrix();
				glTranslatef(-0.5, 1.0+2.0 * (float)i , 0.0);
				glRotatef(135.0, 0.0,0.0,1.0);
				drawRectangle(0.1,0.1,1.4);
			glPopMatrix();
		}

	glPopMatrix();
}

void drawTable(){
	glPushMatrix();
		drawTablePiece();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 0.0, -5.5);
		drawTablePiece();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.5, 0.0, 1.0);
		glScalef(1.0, 1.0, 0.55);
		glRotatef(90.0, 0.0,1.0,0.0);
		drawTablePiece();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.5, 0.0, 1.0);
		glScalef(1.0, 1.0, 0.55);
		glRotatef(90.0, 0.0,1.0,0.0);
		drawTablePiece();
	glPopMatrix();

	glPushMatrix();			//noga
		glTranslatef(-4.8, -1.9, 3.3);
		drawRectangle(0.5,0.5,4.0);
	glPopMatrix();
	glPushMatrix();			//noga
		glTranslatef(-4.8, -1.9, -2.0);
		drawRectangle(0.5,0.5,4.0);
	glPopMatrix();

	glPushMatrix();			//noga
		glTranslatef(5.0, -1.9, 3.3);
		drawRectangle(0.5,0.5,4.0);
	glPopMatrix();
	glPushMatrix();			//noga
		glTranslatef(5.0, -1.9, -2.0);
		drawRectangle(0.5,0.5,4.0);
	glPopMatrix();
}
void drawRoom(){
	glPushMatrix();
	glMaterialfv( GL_FRONT, GL_DIFFUSE, White );
	glTranslatef(0.0,-4.15,0.0);
	glScalef(5.0,5.0,8.0);
		glBindTexture(GL_TEXTURE_2D, textureHandle);
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glBegin(GL_QUADS);				//podloga

			glNormal3f(0.0, 1.0, 0.0 );
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-5.0, 0.0, -5.0 );
			glTexCoord2f(0.0, 1.0);
			glVertex3f(-5.0, 0.0, 5.0 );
			glTexCoord2f(1.0, 1.0);
			glVertex3f(5.0, 0.0, 5.0 );
			glTexCoord2f(1.0, 0.0);
			glVertex3f(5.0, 0.0, -5.0 );
		glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, textureTopHandle);
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glBegin(GL_QUADS);				//sufit
				glNormal3f(0.0, -1.0, 0.0 );
				glTexCoord2f(0.0, 0.0);
				glVertex3f(-5.0, 5.0, -5.0 );
				glTexCoord2f(0.0, 1.0);
				glVertex3f(-5.0, 5.0, 5.0 );
				glTexCoord2f(1.0, 1.0);
				glVertex3f(5.0, 5.0, 5.0 );
				glTexCoord2f(1.0, 0.0);
				glVertex3f(5.0, 5.0, -5.0 );
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, textureSideHandle);
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glBegin(GL_QUADS);				//sciana
				glNormal3f(0.0, 0.0, -1.0 );
				glTexCoord2f(1.0, 0.0);
				glVertex3f(5.0, 0.0, 5.0 );
				glTexCoord2f(0.0, 0.0);
				glVertex3f(-5.0, 0.0, 5.0 );
				glTexCoord2f(0.0, 1.0);
				glVertex3f(-5.0, 5.0, 5.0 );
				glTexCoord2f(1.0, 1.0);
				glVertex3f(5.0, 5.0, 5.0 );
			glEnd();
		glPopMatrix();
		
		glPushMatrix();
			glBegin(GL_QUADS);				//sciana
				glNormal3f(0.0, 0.0, 1.0 );
				glTexCoord2f(1.0, 0.0);
				glVertex3f(5.0, 0.0, -5.0 );
				glTexCoord2f(0.0, 0.0);
				glVertex3f(-5.0, 0.0, -5.0 );
				glTexCoord2f(0.0, 1.0);
				glVertex3f(-5.0, 5.0, -5.0 );
				glTexCoord2f(1.0, 1.0);
				glVertex3f(5.0, 5.0, -5.0 );
			glEnd();
		glPopMatrix();
		glPushMatrix();
			glBegin(GL_QUADS);				//sciana
				glNormal3f(1.0, 0.0, 0.0 );
				glTexCoord2f(1.0, 0.0);
				glVertex3f(-5.0, 0.0, -5.0 );
				glTexCoord2f(0.0, 0.0);
				glVertex3f(-5.0, 0.0, 5.0 );
				glTexCoord2f(0.0, 1.0);
				glVertex3f(-5.0, 5.0, 5.0 );
				glTexCoord2f(1.0, 1.0);
				glVertex3f(-5.0, 5.0, -5.0 );
			glEnd();
		glPopMatrix();
		glPushMatrix();
			glBegin(GL_QUADS);				//sciana
				glNormal3f(-1.0, 0.0, 0.0 );
				glTexCoord2f(1.0, 0.0);
				glVertex3f(5.0, 0.0, -5.0 );
				glTexCoord2f(0.0, 0.0);
				glVertex3f(5.0, 0.0, 5.0 );
				glTexCoord2f(0.0, 1.0);
				glVertex3f(5.0, 5.0, 5.0 );
				glTexCoord2f(1.0, 1.0);
				glVertex3f(5.0, 5.0, -5.0 );
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
		glMaterialfv( GL_FRONT, GL_DIFFUSE, Silver );
		glScalef(0.5,0.7, 1.0);
		glTranslatef(0.0,-2.0,0.0);
		drawTable();
	glPopMatrix();
	glFlush();
	
}

