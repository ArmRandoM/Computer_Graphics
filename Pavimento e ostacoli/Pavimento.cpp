#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>

// Valori della luce e coordinate
static GLfloat lightPos[] = { 0.0, 100.0, 0.0, 10.0 };
static GLfloat spotDir[] = { 0.0, -20.0, 0.0};
static GLfloat mat_emission[] = { 0.0, 0.0, 0.0, 30.0};

/* descrivo una matrice, più grande è la larghezza e la lunghezza più la scacchiera sarà definita*/
const int larghezza_pavimento = 450, lunghezza_pavimento = 450;
GLubyte pavimento_a_scacchi[larghezza_pavimento][lunghezza_pavimento][3];

/*posizione ed angolazione della camera modalità 'FPS'*/
static GLfloat camera_position[] = {0.0, 1.0, 0.0};
static GLfloat camera_direction[] = {0.0, 1.0, -19.0};
static GLfloat camera_angle_y = 0.0;
static GLfloat ruota = 0.0;
static GLfloat sposta = 0.2;
bool ruotata = false;

void crea_pavimento_a_scacchi(void)
{
	int c = 255;

	for (int i = 0; i < larghezza_pavimento; i++) 
		{
			for (int j = 0; j < lunghezza_pavimento; j++) 
				{

							/*Se il quarto bit di "i" è 0 o il quarto bit di "j" è 0, 
							 *ma non entrambi, allora c = 255, oppure c = 0*/  
				    	/*Loperatore "^" è un operatore logico che viene utilizzato per fare interrogazioni su bit,
							 *viene utilizzato molto spesso quando si devono fare calcoli per la definizione dei
							 *pixel.*/
					
					if((j&0x8)^(i&0x8))
						{
							pavimento_a_scacchi[i][j][0] = (GLubyte) c;
							pavimento_a_scacchi[i][j][1] = (GLubyte) c;
							pavimento_a_scacchi[i][j][2] = (GLubyte) c;
						}
					else
						{
							pavimento_a_scacchi[i][j][2] = (GLubyte) c;
							pavimento_a_scacchi[i][j][2] = (GLubyte) c;
							pavimento_a_scacchi[i][j][2] = (GLubyte) c;
						}
				}
		}
}

void init(void) 
{

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);/*Abilita le luci*/
	glEnable(GL_LIGHT0);/*Abilita il tipo di luce LIGH_0*/
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL) ;

	// Specifica la posizione e le coordinate della luce
	glLightfv(GL_LIGHT0,GL_POSITION, lightPos);	
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spotDir);	
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0);
	
	glDepthFunc(GL_LEQUAL);
	crea_pavimento_a_scacchi();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, larghezza_pavimento, lunghezza_pavimento, 0, GL_RGB, GL_UNSIGNED_BYTE, &pavimento_a_scacchi[0][0][0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_MODULATE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);

	glEnable(GL_TEXTURE_2D);

	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
}

void display(void)
{
	
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glPushMatrix();

		gluLookAt(camera_position[0], camera_position[1], camera_position[2], camera_position[0] + camera_direction[0],camera_direction[1],camera_position[2] + camera_direction[2], 0.0, 1.0, 0.0);

		// Specifica la posizione e le coordinate della luce
		glLightfv(GL_LIGHT0,GL_POSITION, lightPos);	
		
				glBegin(GL_QUADS);
				
					glNormal3f( 0.0, 1.0, 0.0);
					glTexCoord2f(0.0, 0.0); 
					glVertex3f(-20.0, 0.0, -20.0);
					
					glNormal3f( 0.0, 1.0, 0.0);
					glTexCoord2f(0.0, 1.0);
					glVertex3f(20.0, 0.0, -20.0);
					
					glNormal3f( 0.0, 1.0, 0.0);
					glTexCoord2f(1.0, 1.0); 
					glVertex3f(20.0, 0.0, 20.0);

					glNormal3f( 0.0, 1.0, 0.0);
					glTexCoord2f(1.0, 0.0); 
					glVertex3f(-20.0, 0.0, 20.0);

				glEnd();

			glDisable(GL_TEXTURE_2D);
			
			glPushMatrix();
				glRotatef( 270, 1.0, 0.0,0.0);
				glutSolidSphere( 1.5, 100, 100 );
			glPopMatrix();
				
		glEnable(GL_TEXTURE_2D);
	
	glPopMatrix();
	
	glutSwapBuffers();	
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
			if( !ruotata)
				camera_position[2] -= 0.1;
			else
				{	
					camera_position[0] += camera_direction[0] * sposta;
					camera_position[2] += camera_direction[2] * sposta;
				}
			glutPostRedisplay();			
			break;	
		case 's':
			if( !ruotata)
				camera_position[2] += 0.1;
			else
				{
					camera_position[0] -= camera_direction[0] * sposta;
					camera_position[2] -= camera_direction[2] * sposta;
				}
			glutPostRedisplay();
			break;
		case 'z':		
			lightPos[1] -= 0.5;		
			glutPostRedisplay();
			break;
		case 'x':
			lightPos[1] += 0.5;
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
   glutInitWindowSize (400, 400); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Pavimento");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
