#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
using namespace std;

/*posizione ed angolazione della camera modalità 'FPS'*/
static GLfloat camera_position[] = {3.0, 3.5, 3.0};
static GLfloat camera_direction[] = {0.0, 3.5, 0.0};
static GLfloat camera_angle_y = 0.0;
static GLfloat sposta = 0.2;
bool ruotata = false;

//valore utilizzato per generare le texture della sfera
GLUquadricObj *sphere = NULL;

//valori delle luci
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 10.0 };
GLfloat light_position[] = { 0.0, 50.0, 0.0, 1.0 };

#define TRUE  1
#define FALSE 0

int maze[40][40] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					 1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
					 1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
					 1,1,1,0,0,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,0,0,1,1,1,1,1,1,1,0,0,1,1,
					 1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,1,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,1,
					 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,1,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,1,
					 1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,
					 1,0,0,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
					 1,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
					 1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,
					 1,0,0,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,1,1,
					 1,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
					 1,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,0,0,0,0,1,
					 1,0,0,1,0,0,1,1,1,1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,1,1,
					 1,1,1,1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,1,1,
					 1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,0,0,0,0,1,
					 1,0,0,1,0,0,0,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
					 1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,1,1,
					 1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,
					 1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
					 1,0,0,0,1,0,0,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
					 1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,
					 1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,1,1,
					 1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,1,
					 1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,
					 1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,
					 1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,
					 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,1,1,
					 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,
					 1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,
					 1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,
					 1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,
					 1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					 1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
					 1,1,1,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
					 1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,
					 1,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,
					 1,0,0,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
					 1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
					 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
             };

GLuint LoadTexture( const char * filename, int width, int height )
{
  GLuint texture;
  unsigned char * data;
  FILE * file;
  file = fopen( filename, "rb" );
  if ( file == NULL ) return 0;
  data = (unsigned char *)malloc( width * height * 3 );
  //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );
  fclose( file );
  for(int i = 0; i < width * height ; ++i)
  	  {
	  	  int index = i*3;
	  	  unsigned char B,R;
	  	  B = data[index];
	  	  R = data[index+2];

	  	  data[index] = R;
	  	  data[index+2] = B;
  	  }
  glGenTextures( 1, &texture );
  glBindTexture( GL_TEXTURE_2D, texture );
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
  free( data );
  return texture;
}

void draw_cube()
{
	    glBegin(GL_QUADS);
	      /* Front Face */
	      glTexCoord2f( 0.0f, 1.0 );
	      glVertex3f( -1.0f, -1.0f, 1.0 );
	      glTexCoord2f( 1.0, 1.0 );
	      glVertex3f(  1.0, -1.0, 1.0 );
	      glTexCoord2f( 1.0, 0.0 );
	      glVertex3f(  1.0,  1.0, 1.0 );
	      glTexCoord2f( 0.0, 0.0 );
	      glVertex3f( -1.0,  1.0, 1.0 );

	      /* Back Face */
	      glTexCoord2f( 0.0f, 0.0f );
	      glVertex3f( -1.0f, -1.0f, -1.0f );
	      glTexCoord2f( 0.0f, 1.0f );
	      glVertex3f( -1.0f,  1.0f, -1.0f );
	      glTexCoord2f( 1.0f, 1.0f );
	      glVertex3f(  1.0f,  1.0f, -1.0f );
	      glTexCoord2f( 1.0f, 0.0f );
	      glVertex3f(  1.0f, -1.0f, -1.0f );

	      /* Top Face */
	      glTexCoord2f( 1.0f, 1.0f );
	      glVertex3f( -1.0f,  1.0f, -1.0f );
	      glTexCoord2f( 1.0f, 0.0f );
	      glVertex3f( -1.0f,  1.0f,  1.0f );
	      glTexCoord2f( 0.0f, 0.0f );
	      glVertex3f(  1.0f,  1.0f,  1.0f );
	      glTexCoord2f( 0.0f, 1.0f );
	      glVertex3f(  1.0f,  1.0f, -1.0f );

	      /* Bottom Face */
	      /* Top Right Of The Texture and Quad */
	      glTexCoord2f( 0.0f, 1.0f );
	      glVertex3f( -1.0f, -1.0f, -1.0f );
	      glTexCoord2f( 1.0f, 1.0f );
	      glVertex3f(  1.0f, -1.0f, -1.0f );
	      glTexCoord2f( 1.0f, 0.0f );
	      glVertex3f(  1.0f, -1.0f,  1.0f );
	      glTexCoord2f( 0.0f, 0.0f );
	      glVertex3f( -1.0f, -1.0f,  1.0f );

	      /* Right face */
	      glTexCoord2f( 0.0f, 0.0f );
	      glVertex3f( 1.0f, -1.0f, -1.0f );
	      glTexCoord2f( 0.0f, 1.0f );
	      glVertex3f( 1.0f,  1.0f, -1.0f );
	      glTexCoord2f( 1.0f, 1.0f );
	      glVertex3f( 1.0f,  1.0f,  1.0f );
	      glTexCoord2f( 1.0f, 0.0f );
	      glVertex3f( 1.0f, -1.0f,  1.0f );

	      /* Left Face */
	      glTexCoord2f( 1.0f, 0.0f );
	      glVertex3f( -1.0f, -1.0f, -1.0f );
	      glTexCoord2f( 0.0f, 0.0f );
	      glVertex3f( -1.0f, -1.0f,  1.0f );
	      glTexCoord2f( 0.0f, 1.0f );
	      glVertex3f( -1.0f,  1.0f,  1.0f );
	      glTexCoord2f( 1.0f, 1.0f );
	      glVertex3f( -1.0f,  1.0f, -1.0f );
	    glEnd( );
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);/*Abilita le luci*/
	glEnable(GL_LIGHT0);/*Abilita il tipo di luce LIGH_0*/
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL) ;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void display(void)
{

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();

		gluLookAt(camera_position[0], camera_position[1], camera_position[2], camera_position[0] + camera_direction[0],camera_direction[1],camera_position[2] + camera_direction[2], 0.0, 1250.0, 0.0);

		GLuint my_texture = LoadTexture( "cielo.bmp", 340, 340);
		glBindTexture (GL_TEXTURE_2D, my_texture);

		glPushMatrix();
			glTranslatef( 40.0, 0.0, 40.0 );
				sphere = gluNewQuadric();
				gluQuadricDrawStyle(sphere, GLU_FILL);
				gluQuadricTexture(sphere, GL_TRUE);
				gluQuadricNormals(sphere, GLU_SMOOTH);
				gluSphere(sphere, 100.0, 100, 100);
		glPopMatrix();

		my_texture = LoadTexture( "luna.bmp", 340, 340);
		glBindTexture (GL_TEXTURE_2D, my_texture);

		glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef( 70.0, 30.0, -30.0 );
				sphere = gluNewQuadric();
				gluQuadricDrawStyle(sphere, GLU_FILL);
				gluQuadricTexture(sphere, GL_TRUE);
				gluQuadricNormals(sphere, GLU_SMOOTH);
				gluSphere(sphere, 1.5, 100, 100);
				glEnable(GL_LIGHTING);
		glPopMatrix();

		my_texture = LoadTexture( "pavimento.bmp", 340, 340);
		glBindTexture (GL_TEXTURE_2D, my_texture);

		for (int yc = 0; yc < 40; yc++)
		    {
		    	for (int xc = 0; xc < 40; xc++)
		    		{
		    			glPushMatrix();
		    				glTranslatef( xc*2.0, 0.0, yc*2.0 );
		    				draw_cube();
		    			glPopMatrix();
		    		}
		    }

	    my_texture = LoadTexture( "siepi.bmp", 340, 340 );
		glBindTexture (GL_TEXTURE_2D, my_texture);

		GLfloat y = 2.0;

		for( int i = 0; i < 3; i++)
			{
				for (int yc = 0; yc < 40; yc++)
					{
						for (int xc = 0; xc < 40; xc++)
							{
								if (maze[ xc][yc] == 1)
									{
										glPushMatrix();
											glTranslatef( xc*2.0, y, yc*2.0 );
											draw_cube();
										glPopMatrix();
									}
							}
					}
				y = y + 2;
			}

		glutSwapBuffers();

	glPopMatrix();

	glutSwapBuffers();
}

int tileCollision(GLfloat x, GLfloat z, GLfloat w)
{
	unsigned int i, j;
	unsigned int minx, minz, maxx, maxz;

	// Convertiamo le coordinate da pixel in un equivalente per la matrice
	minx = x / 2;
	minz = z / 2;

	maxx = (x + w - 1) / 2;
	maxz = (z + w - 1) / 2;

	// Se il rettangolo interseca un tile nella matrice ritorniamo una collisione
	for (i = minx; i <= maxx ; i++)
		{
			for (j = minz ; j <= maxz ; j++)
				{
					if (maze[i][j] == 1)
						return 1;
				}
		}

	// Nessuna collisione
	return 0;
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();//rimpiazza la matrice corrente con quella di identità
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 600.0);
   glMatrixMode(GL_MODELVIEW);//gestisce le trasformazioni di viewing e modeling
   glLoadIdentity();
}

void keyboard (unsigned char key, int x, int y)
{
	GLfloat xc, zc;

	switch (key)
		{
			case 'a':
				ruotata = true;
				camera_angle_y -= 0.05;
				camera_direction[0] = sin(camera_angle_y);
				camera_direction[2] = -cos(camera_angle_y);
				glutPostRedisplay();
				break;
			case 'd':
				ruotata = true;
				camera_angle_y += 0.05;
				camera_direction[0] = sin(camera_angle_y);
				camera_direction[2] = -cos(camera_angle_y);
				glutPostRedisplay();
       			break;
			case 'w':
				xc = (camera_position[0] + camera_direction[0]);
				zc = ( camera_position[2] + camera_direction[2]);
				if(!tileCollision( xc, zc, 3.0))
					{
						camera_position[0] += camera_direction[0] * sposta;
						camera_position[2] += camera_direction[2] * sposta;
					}
				glutPostRedisplay();
				break;
			case 's':
				xc = (camera_position[0] - camera_direction[0]);
				zc = ( camera_position[2] - camera_direction[2]);
				if(!tileCollision( xc, zc, 3.0))
					{
						camera_position[0] -= camera_direction[0] * sposta;
						camera_position[2] -= camera_direction[2] * sposta;
					}
				glutPostRedisplay();
				break;
		default:
			glutIdleFunc(NULL);
			break;
	}
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (12500, 12500);
   glutInitWindowPosition (1250, 1250);
   glutCreateWindow ("Labirinto IG Armando Pezzimenti");
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
