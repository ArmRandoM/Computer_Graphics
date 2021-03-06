//ogni programma OpenGL deve iniziare con l'inclusione delle seguenti librerie
#include <GL/glut.h>
#include <GL/gl.h>
#include <cstdlib>
#include <ctime>
	
static int spinx = 0, spiny = 0, giro_intorno_al_cubo_orizzontale = 0, giro_intorno_al_cubo_verticale = 0;

bool particelle = false;

GLfloat coordinate_xyz[49];
GLfloat coordinate_xyz_l[97];

GLfloat indicix[50];
GLfloat indiciy[50];
GLfloat indiciz[50];

GLfloat indicix_copia[50];
GLfloat indiciy_copia[50];
GLfloat indiciz_copia[50];

// Valori della luce e coordinate
static GLfloat lightPos[] = { 0.0, 0.0, 2.5, 0.47 };
static GLfloat  spotDir[] = { 0.0, 0.0, -0.5 };

void crea_indici(void)
{	
	int coordinatex = 0;
	int coordinatey = 0;
	int coordinatez = 0;

	coordinate_xyz[0] = 0.00;
	coordinate_xyz_l[0] = 0.00;

	for( int i = 1; i <= 49; i++)
		coordinate_xyz[i] = coordinate_xyz[i-1] + 0.01;

	for( int i = 1; i <= 97; i++)
		coordinate_xyz_l[i] = coordinate_xyz_l[i-1] + 0.01;

	for( int i = 0; i < 50; i++ )
		{
			
			coordinatex = rand() % 49;			
			indicix[i] = coordinate_xyz[coordinatex];	
			indicix_copia[i] = coordinate_xyz[coordinatex];
	
			coordinatey = rand() % 49;		
			while( coordinatex == coordinatey)			
				coordinatey = rand() % 49;
			indiciy[i] = coordinate_xyz[coordinatey];
			indiciy_copia[i] = coordinate_xyz[coordinatey];

			coordinatez = rand() % 49;
			while ( coordinatez == coordinatex )
				coordinatez = rand() % 49;
			while(  coordinatez == coordinatey )
				coordinatez = rand() % 49;
			indiciz[i] = coordinate_xyz[coordinatez];
			indiciz_copia[i] = coordinate_xyz[coordinatez];
	
		}
}


void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);/*Abilita le luci*/
	glEnable(GL_LIGHT0);/*Abilita il tipo di luce LIGH_0*/
	glEnable (GL_COLOR_MATERIAL);/*Abilita il modo in cui i materiali riflettono la luce*/
}

void display(void)
{
	glShadeModel(GL_SMOOTH);

	glClear(GL_DEPTH_BUFFER_BIT);
	glClear (GL_COLOR_BUFFER_BIT);

	glPushMatrix();	
	
		glPolygonMode (GL_FRONT_AND_BACK, GL_LINE );
		
		glRotatef (spiny, 1.0, 0.0, 0.0);  
		glRotatef (spinx, 0.0, 1.0, 0.0);

		/*creo un cubo*/
		glBegin( GL_QUADS );//inizio a definire il poligono con colore e vertici	
		
			//prima faccia
                    
			glNormal3f( -1.0, -1.0, -1.0 );
			glColor3f (1.0 , 0.0 , 0.0);
			glVertex3f (-1.0 , -1.0, -1.0);
					
			glNormal3f( -1.0, 1.0, -1.0 );
			glColor3f (0.0 , 1.0 , 0.0);
			glVertex3f (-1.0 , 1.0, -1.0);
			
			glNormal3f( 1.0, 1.0, -1.0 );
			glColor3f (0.0 , 0.0 , 1.0);
			glVertex3f (1.0, 1.0, -1.0);
			
			glNormal3f( 1.0, -1.0, -1.0 );
			glColor3f (0.0 , 1.0 , 1.0);
			glVertex3f (1.0 , -1.0, -1.0);
					
			//seconda faccia

			glNormal3f( -1.0, -1.0, -1.0 );
			glColor3f (1.0 , 0.0 , 1.0);
			glVertex3f (-1.0 , -1.0, -1.0);
				
			glNormal3f( -1.0, 1.0, -1.0 );
			glColor3f (1.0 , 1.0 , 0.0);
			glVertex3f (-1.0 , 1.0, -1.0);	
		
        	
			glNormal3f( -1.0, 1.0, 1.0 );
			glColor3f (1.0 , 0.0 , 0.0);
			glVertex3f (-1.0 , 1.0, 1.0);
				
			glNormal3f( -1.0, -1.0, 1.0 );
			glColor3f (1.0 , 1.0 , 1.0);
			glVertex3f (-1.0 , -1.0, 1.0);	
			
			//terza faccia

			glNormal3f( 1.0, 1.0, -1.0);
			glColor3f (0.0 , 1.0 , 0.0);
			glVertex3f (1.0 , 1.0, -1.0);
		
			glNormal3f( 1.0, -1.0, -1.0 );		
			glColor3f (0.0 , 0.0 , 0.0);
			glVertex3f (1.0 , -1.0, -1.0);	
		
			glNormal3f( 1.0, -1.0, 1.0 );
			glColor3f (1.0 , 0.0 , 1.0);
			glVertex3f (1.0 , -1.0, 1.0);
					
			glNormal3f( 1.0, 1.0, 1.0 );
			glColor3f (1.0 , 0.0 , 1.0);
			glVertex3f (1.0 , 1.0, 1.0);
		
			//quarta faccia

			glNormal3f( 1.0, 1.0, 1.0 );
			glColor3f (1.0 , 0.0 , 0.0);
			glVertex3f (1.0 , 1.0, 1.0);
					
			glNormal3f( -1.0, 1.0, 1.0 );
			glColor3f (1.0 , 1.0 , 0.0);
			glVertex3f (-1.0 , 1.0, 1.0);	
		
			glNormal3f( -1.0, -1.0, 1.0 );
			glColor3f (0.0 , 1.0 , 0.0);
			glVertex3f (-1.0 , -1.0, 1.0);
						
			glNormal3f( 1.0, -1.0, 1.0 );
			glColor3f (1.0 , 1.0 , 1.0);
			glVertex3f (1.0, -1.0, 1.0);
	
			//superfice

			glNormal3f( -1.0, 1.0, 1.0 );
			glColor3f (1.0 , 0.0 , 1.0);
			glVertex3f (-1.0 , 1.0, 1.0);

			glNormal3f( 1.0, 1.0, 1.0 );			
			glColor3f (1.0 , 0.0 , 1.0);
			glVertex3f (1.0 , 1.0, 1.0);	
		
			glNormal3f( 1.0, 1.0, -1.0 );
			glColor3f (0.0 , 1.0 , 1.0);
			glVertex3f (1.0 , 1.0, -1.0);
	
			glNormal3f( -1.0, 1.0, -1.0 );					
			glColor3f (0.0 , 1.0 , 0.0);
			glVertex3f (-1.0 , 1.0, -1.0);
		
			//base

			glNormal3f( -1.0, -1.0, 1.0);
			glColor3f (0.0 , 0.0 , 1.0);
			glVertex3f (-1.0 , -1.0, 1.0);

			glNormal3f( 1.0, -1.0, 1.0);			
			glColor3f (0.0 , 0.0 , 0.0);
			glVertex3f (1.0 , -1.0, 1.0);	

			glNormal3f( 1.0, -1.0, -1.0);		
			glColor3f (0.0 , 1.0 , 1.0);
			glVertex3f (1.0 , -1.0, -1.0);
					
			glNormal3f( -1.0, -1.0, -1.0);
			glColor3f (1.0 , 1.0 , 0.0);
			glVertex3f (-1.0 , -1.0, -1.0);	
		
		glEnd();		
			
		glPolygonMode (GL_FRONT_AND_BACK, GL_FILL );

		glEnable(GL_BLEND);

		glBlendFunc(GL_ONE, GL_ONE);	
			
		glDisable(GL_DEPTH_TEST);		  

		glBegin( GL_QUADS );//inizio a definire il poligono con colore e vertici	
		
			//prima faccia
					
			glNormal3f( -0.5, -0.5, -0.5 );
			glColor3f (1.0 , 0.0 , 0.0);
			glVertex3f (-0.5 , -0.5, -0.5);
						
			glNormal3f( -0.5, 0.5, -0.5 );
			glColor3f (0.0 , 1.0 , 0.0);
			glVertex3f (-0.5 , 0.5, -0.5);
			
			glNormal3f( 0.5, 0.5, -0.5 );
			glColor3f (0.0 , 0.0 , 1.0);
			glVertex3f (0.5, 0.5, -0.5);
			
			glNormal3f( 0.5, -0.5, -0.5 );
			glColor3f (0.0 , 1.0 , 1.0);
			glVertex3f (0.5 , -0.5, -0.5);
					
			//seconda faccia

			glNormal3f( -0.5, -0.5, -0.5 );
			glColor3f (1.0 , 0.0 , 1.0);
			glVertex3f (-0.5 , -0.5, -0.5);
				
			glNormal3f( -0.5, 0.5, -0.5 );
			glColor3f (1.0 , 1.0 , 0.0);
			glVertex3f (-0.5 , 0.5, -0.5);	
		
			glNormal3f( -0.5, 0.5, 0.5 );
			glColor3f (1.0 , 0.0 , 0.0);
			glVertex3f (-0.5 , 0.5, 0.5);
				
			glNormal3f( -0.5, -0.5, 0.5 );
			glColor3f (1.0 , 1.0 , 1.0);
			glVertex3f (-0.5 , -0.5, 0.5);	
		
			//terza faccia

			glNormal3f( 0.5, 0.5, -0.5);
			glColor3f (0.0 , 1.0 , 0.0);
			glVertex3f (0.5 , 0.5, -0.5);
		
			glNormal3f( 0.5, -0.5, -0.5 );		
			glColor3f (0.0 , 0.0 , 0.0);
			glVertex3f (0.5 , -0.5, -0.5);	
		
			glNormal3f( 0.5, -0.5, 0.5 );
			glColor3f (1.0 , 0.0 , 1.0);
			glVertex3f (0.5 , -0.5, 0.5);
					
			glNormal3f( 0.5, 0.5, 0.5 );
			glColor3f (1.0 , 0.0 , 1.0);
			glVertex3f (0.5 , 0.5, 0.5);
		
			//quarta faccia

			glNormal3f( 0.5, 0.5, 0.5 );
			glColor3f (1.0 , 0.0 , 0.0);
			glVertex3f (0.5 , 0.5, 0.5);
					
			glNormal3f( -0.5, 0.5, 0.5 );
			glColor3f (1.0 , 1.0 , 0.0);
			glVertex3f (-0.5 , 0.5, 0.5);	
		
			glNormal3f( -0.5, -0.5, 0.5 );
			glColor3f (0.0 , 1.0 , 0.0);
			glVertex3f (-0.5 , -0.5, 0.5);
						
			glNormal3f( 0.5, -0.5, 0.5 );
			glColor3f (1.0 , 1.0 , 1.0);
			glVertex3f (0.5, -0.5, 0.5);

			//superfice

			glNormal3f( -0.5, 0.5, 0.5 );
			glColor3f (1.0 , 0.0 , 1.0);
			glVertex3f (-0.5 , 0.5, 0.5);

			glNormal3f( 0.5, 0.5, 0.5 );			
			glColor3f (1.0 , 0.0 , 1.0);
			glVertex3f (0.5 , 0.5, 0.5);	
		
			glNormal3f( 0.5, 0.5, -0.5 );
			glColor3f (0.0 , 1.0 , 1.0);
			glVertex3f (0.5 , 0.5, -0.5);

			glNormal3f( -0.5, 0.5, -0.5 );					
			glColor3f (0.0 , 1.0 , 0.0);
			glVertex3f (-0.5 , 0.5, -0.5);
		
			//base

			glNormal3f( -0.5, -0.5, 0.5);
			glColor3f (0.0 , 0.0 , 1.0);
			glVertex3f (-0.5 , -0.5, 0.5);

			glNormal3f( 0.5, -0.5, 0.5);			
			glColor3f (0.0 , 0.0 , 0.0);
			glVertex3f (0.5 , -0.5, 0.5);	

			glNormal3f( 0.5, -0.5, -0.5);		
			glColor3f (0.0 , 1.0 , 1.0);
			glVertex3f (0.5 , -0.5, -0.5);
					
			glNormal3f( -0.5, -0.5, -0.5);
			glColor3f (1.0 , 1.0 , 0.0);
			glVertex3f (-0.5 , -0.5, -0.5);	
			
		glEnd();

	glDisable(GL_BLEND);	

	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
            
		glRotatef (giro_intorno_al_cubo_verticale, 1.0, 0.0, 0.0);
		glRotatef (giro_intorno_al_cubo_orizzontale, 0.0, 1.0, 0.0);

		// Specifica la posizione e le coordinate
		glLightfv(GL_LIGHT0,GL_POSITION, lightPos);
		glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spotDir);

		glTranslatef(lightPos[0],lightPos[1],lightPos[2]);

		glColor3f (0.0 , 0.0 , 1.0);

		glPolygonMode (GL_BACK, GL_FILL );
        	glPolygonMode (GL_FRONT, GL_FILL );

           	glutSolidCone( 0.1, 0.1, 80, 80 );

		glPushAttrib(GL_LIGHTING_BIT);
				
			glDisable(GL_LIGHTING);
			glColor3f (1.0 , 1.0 , 0.0);
			glutSolidSphere( 0.07 , 15, 15);

		glPopAttrib();
				
	glPopMatrix();
	
	glPushMatrix();

		glColor3f (1.0 , 1.0 , 1.0);
			
		int coordinate = 0;

		for( int i = 0; i < 50; i++)
			{
				
				glPushMatrix();
				glColor3f (1.0 , 0.0 , 0.0);
				glTranslatef( indicix[i], indiciy[i], indiciz[i]);
				glutSolidSphere( 0.01, 10, 8);
				glPopMatrix();
						
				glPushMatrix();
				glColor3f (0.0 , 1.0 , 0.0);
				glTranslatef( -indicix[i], -indiciy[i], -indiciz[i]);
				glutSolidSphere( 0.01, 10, 8);
				glPopMatrix();							
						
				glPushMatrix();
				glColor3f (0.0 , 0.0 , 1.0);
				glTranslatef( indicix[i], -indiciy[i], -indiciz[i]);
				glutSolidSphere( 0.01, 10, 8);
				glPopMatrix();							
							
				glPushMatrix();
				glColor3f (1.0 , 1.0 , 0.0);							
				glTranslatef( -indicix[i], indiciy[i], -indiciz[i]);
				glutSolidSphere( 0.01, 10, 8);
				glPopMatrix();							
							
				glPushMatrix();
				glColor3f (1.0 , 0.0 , 1.0);							
				glTranslatef( -indicix[i], -indiciy[i], indiciz[i]);
				glutSolidSphere( 0.01, 10, 8);
				glPopMatrix();							
						
				glPushMatrix();
				glColor3f (1.0 , 1.0 , 1.0);
				glTranslatef( -indicix[i], indiciy[i], indiciz[i]);
				glutSolidSphere( 0.01, 10, 8);
				glPopMatrix();							
							
				glPushMatrix();
				glColor3f (0.0 , 1.0 , 1.0);
				glTranslatef( indicix[i], indiciy[i], -indiciz[i]);
				glutSolidSphere( 0.01, 10, 8);
				glPopMatrix();							
						
				glPushMatrix();
				glColor3f (1.0 , 0.0 , 0.0);
				glTranslatef( indicix[i], -indiciy[i], indiciz[i]);
				glutSolidSphere( 0.01, 10, 8);
				glPopMatrix();
																		
			}

	glPopMatrix();

	glutSwapBuffers();
		
	glDisable(GL_BLEND);

	glPopMatrix();
	
}

void particelle_impazzite()
{
	int coordinatex = 0;
	int coordinatey = 0;
	int coordinatez = 0;

	for( int i = 0; i < 50; i++ )
		{
			coordinatex = rand() % 97;		
			indicix[i] = coordinate_xyz_l[coordinatex];	
	
			coordinatey = rand() % 97;		
			indiciy[i] = coordinate_xyz_l[coordinatey];

			coordinatez = rand() % 97;
			indiciz[i] = coordinate_xyz_l[coordinatez];
		}

	glutPostRedisplay();
}

void riposiziona_particelle()
{
	for( int i = 0; i < 50; i++)
		{
			indicix[i] = indicix_copia[i];
			
			indiciy[i] = indiciy_copia[i];

			indiciz[i] = indiciz_copia[i];
		}
	glutPostRedisplay();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();//rimpiazza la matrice corrente con quella di identità
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);//gestisce le trasformazioni di viewing e modeling
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key)
		{
			case 'a':
				spinx = ( spinx - 5 ) % 360;
				glutPostRedisplay();
				break;
			case 'd':
				spinx = ( spinx + 5 ) % 360;
				glutPostRedisplay();
				break;
			case 'w':
				spiny = ( spiny - 5 ) % 360;
				glutPostRedisplay();
				break;
			case 's':
				spiny = ( spiny + 5 ) % 360;
				glutPostRedisplay();
		        	break;
			case 'h':
				giro_intorno_al_cubo_orizzontale = ( giro_intorno_al_cubo_orizzontale + 5 ) % 360;
				glutPostRedisplay();
		        	break;
			case 'f':
				giro_intorno_al_cubo_orizzontale = ( giro_intorno_al_cubo_orizzontale - 5 ) % 360;	
				glutPostRedisplay();	
				break;
			case 't':
				giro_intorno_al_cubo_verticale = ( giro_intorno_al_cubo_verticale + 5 ) % 360;
				glutPostRedisplay();	
				break;
			case 'g':
				giro_intorno_al_cubo_verticale = ( giro_intorno_al_cubo_verticale - 5 ) % 360;
				glutPostRedisplay();
				break;
			case 'i':
				lightPos[2] = ( lightPos[2] + 0.1 );
				glutPostRedisplay();	
				break;
			case 'k':
				lightPos[2] = ( lightPos[2] - 0.1 );
				glutPostRedisplay();	
				break;
			case 'z':
				if( particelle )
					{
						glutIdleFunc(particelle_impazzite);
						particelle= false;
					}
				else 
					{
						glutIdleFunc( NULL);
						particelle = true;
					}			
				break;
			case 'Z':
				glutIdleFunc(riposiziona_particelle);
				break;
			break;
	}
}

int main(int argc, char** argv)
{
   srand(time(0));
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (800, 800); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Cubo");
   init();
   crea_indici();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glFlush();
   glutMainLoop();
   return 0;
}
		
		
