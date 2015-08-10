//ogni programma OpenGL deve iniziare con l'inclusione delle seguenti librerie
#include <GL/glut.h>
#include <GL/gl.h>

static int spinx = 0, spiny = 0;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);/*Abilita le luci*/
   glEnable(GL_LIGHT0);/*Abilita il tipo di luce LIGH_0*/
   glEnable (GL_COLOR_MATERIAL) ;/*Abilita il modo in cui i materiali riflettono la luce*/
   glColorMaterial (GL_FRONT, GL_AMBIENT_AND_DIFFUSE ) ;/*Definisce il colore dei materiali in presenza di luce*/
}

void display(void)
{
	
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear (GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	
	glRotatef ((GLfloat) spinx, 0.0, 1.0, 0.0);
	glRotatef ((GLfloat) spiny, 1.0, 0.0, 0.0);	

	/*creo un cubo*/
		glBegin( GL_QUADS );//inizio a definire il poligono con colore e vertici

			//prima faccia

			glColor3f (1.0 , 0.0 , 0.0);
			glVertex3f (-1.0 , -1.0, -1.0);
			
			glColor3f (0.0 , 1.0 , 0.0);
			glVertex3f (-1.0 , 1.0, -1.0);
	
			glColor3f (0.0 , 0.0 , 1.0);
			glVertex3f (1.0 , 1.0, -1.0);
	
			glColor3f (0.0 , 1.0 , 1.0);
			glVertex3f (1.0 , -1.0, -1.0);
			
			//seconda faccia
			
			glColor3f (1.0 , 0.0 , 1.0);
			glVertex3f (-1.0 , -1.0, -1.0);
			
			glColor3f (1.0 , 1.0 , 0.0);
			glVertex3f (-1.0 , 1.0, -1.0);	

			glColor3f (1.0 , 0.0 , 0.0);
			glVertex3f (-1.0 , 1.0, 1.0);
			
			glColor3f (1.0 , 1.0 , 1.0);
			glVertex3f (-1.0 , -1.0, 1.0);	

			//terza faccia

			glColor3f (0.0 , 1.0 , 0.0);
			glVertex3f (1.0 , 1.0, -1.0);
			
			glColor3f (0.0 , 0.0 , 0.0);
			glVertex3f (1.0 , -1.0, -1.0);	

			glColor3f (1.0 , 0.0 , 1.0);
			glVertex3f (1.0 , -1.0, 1.0);
			
			glColor3f (1.0 , 0.0 , 1.0);
			glVertex3f (1.0 , 1.0, 1.0);

			//quarta faccia

			glColor3f (1.0 , 0.0 , 0.0);
			glVertex3f (1.0 , 1.0, 1.0);
			
			glColor3f (1.0 , 1.0 , 0.0);
			glVertex3f (-1.0 , 1.0, 1.0);	

			glColor3f (0.0 , 1.0 , 0.0);
			glVertex3f (-1.0 , -1.0, 1.0);
			
			glColor3f (1.0 , 1.0 , 1.0);
			glVertex3f (1.0 , -1.0, 1.0);		
			
			//tetto

			glColor3f (1.0 , 0.0 , 1.0);
			glVertex3f (-1.0 , 1.0, -1.0);
			
			glColor3f (1.0 , 0.0 , 1.0);
			glVertex3f (1.0 , 1.0, -1.0);	

			glColor3f (0.0 , 1.0 , 1.0);
			glVertex3f (1.0 , 1.0, 1.0);
			
			glColor3f (0.0 , 1.0 , 0.0);
			glVertex3f (-1.0 , 1.0, 1.0);	

			//base

			glColor3f (0.0 , 0.0 , 1.0);
			glVertex3f (-1.0 , -1.0, -1.0);
			
			glColor3f (0.0 , 0.0 , 0.0);
			glVertex3f (-1.0 , -1.0, 1.0);
			
			glColor3f (0.0 , 1.0 , 1.0);
			glVertex3f (1.0 , -1.0, 1.0);
		
			glColor3f (1.0 , 1.0 , 0.0);
			glVertex3f (1.0 , -1.0, -1.0);																
			
		glEnd();
	
	glPopMatrix();	

	glutSwapBuffers();
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
				spinx = ( spinx + 8 ) % 360;
				glutPostRedisplay();
				break;
			case 'd':
				spinx = ( spinx - 8 ) % 360;
				glutPostRedisplay();
				break;
			case 'w':
				spiny = ( spiny + 8 ) % 360;
				glutPostRedisplay();
				break;
			case 's':
				spiny = ( spiny - 8 ) % 360;
				glutPostRedisplay();
				break;

	}
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Cubo");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
		
		
