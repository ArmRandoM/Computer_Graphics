#include <GL/glut.h>

static int giro_intorno_al_sole_1 = 0, giro_intorno_a_se_stesso_1 = 0, giro_intorno_al_pianeta_1 = 0, giro_intorno_a_se_stesso_satellite_1 = 0;
static int giro_intorno_al_sole_2 = 0, giro_intorno_a_se_stesso_2 = 0, giro_intorno_al_pianeta_2 = 0, giro_intorno_a_se_stesso_satellite_2 = 0;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);
	
	glPushMatrix();//inserisce la matrice di trasformazione corrente nella pila di matrici
		glutWireSphere(0.3, 15, 15);//disegna il sole
		glPushMatrix();
			glRotatef ((GLfloat) giro_intorno_al_sole_1, 0.0, 1.0, 0.0);
			glTranslatef (0.5, 0.0, 0.0);
	
			glPushMatrix();
				glRotatef ((GLfloat) giro_intorno_al_pianeta_1, 0.0, 1.0, 0.0);
				glTranslatef (0.2, 0.0, 0.0);
				glRotatef ((GLfloat) giro_intorno_a_se_stesso_satellite_1, 0.0, 1.0, 0.0);
				glutWireSphere(0.03, 10, 8);//disegna il primo satellite
			glPopMatrix();
	
			glRotatef ((GLfloat) giro_intorno_a_se_stesso_1, 0.0, 1.0, 0.0);
			glutWireSphere(0.08, 10, 8);//disegna il primo pianeta
		glPopMatrix();	
	
		glPushMatrix();
			glRotatef ((GLfloat) giro_intorno_al_sole_2, 0.0, 1.0, 0.0);
			glTranslatef (1.0, 0.0, 0.0);
	
			glPushMatrix();
				glRotatef ((GLfloat) giro_intorno_al_pianeta_2, 0.0, 1.0, 0.0);
				glTranslatef (0.2, 0.0, 0.0);
				glRotatef ((GLfloat) giro_intorno_a_se_stesso_satellite_2, 0.0, 1.0, 0.0);
				glutWireSphere(0.03, 10, 8);//disegna il secondo satellite
			glPopMatrix();
	
			glRotatef ((GLfloat) giro_intorno_a_se_stesso_2, 0.0, 1.0, 0.0);
			glutWireSphere(0.08, 10, 8);//disegna il secondo pianeta
		glPopMatrix();	

	glPopMatrix();//recupera l'ultima matrice inserita		

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
   switch (key) {
      case 'a':
         giro_intorno_a_se_stesso_1 = (giro_intorno_a_se_stesso_1 + 10) % 360;
         glutPostRedisplay();
         break;
      case 'A':
         giro_intorno_a_se_stesso_1 = (giro_intorno_a_se_stesso_1 - 10) % 360;
         glutPostRedisplay();
         break;
      case 's':
         giro_intorno_al_sole_1 = (giro_intorno_al_sole_1 + 5) % 360;
         glutPostRedisplay();
         break;
      case 'S':
         giro_intorno_al_sole_1 = (giro_intorno_al_sole_1 - 5) % 360;
         glutPostRedisplay();
         break;
      case 'd':
	 giro_intorno_a_se_stesso_satellite_1 = (giro_intorno_a_se_stesso_satellite_1 + 2) % 360;
         glutPostRedisplay();
         break;
      case 'D':     
	 giro_intorno_a_se_stesso_satellite_1 = (giro_intorno_a_se_stesso_satellite_1 - 2) % 360;
         glutPostRedisplay();
         break;	
      case 'w':
	 giro_intorno_al_pianeta_1 = ( giro_intorno_al_pianeta_1 + 2 ) % 360;
	 glutPostRedisplay();
	 break;
      case 'W':
	 giro_intorno_al_pianeta_1 = ( giro_intorno_al_pianeta_1 - 2 ) % 360;
	 glutPostRedisplay();
	 break;
       case 'q':
         giro_intorno_a_se_stesso_2 = (giro_intorno_a_se_stesso_2 + 10) % 360;
         glutPostRedisplay();
         break;
      case 'Q':
         giro_intorno_a_se_stesso_2= (giro_intorno_a_se_stesso_2 - 10) % 360;
         glutPostRedisplay();
         break;
      case 'e':
         giro_intorno_al_sole_2 = (giro_intorno_al_sole_2 + 5) % 360;
         glutPostRedisplay();
         break;
      case 'E':
         giro_intorno_al_sole_2 = (giro_intorno_al_sole_2 - 5) % 360;
         glutPostRedisplay();
         break;
      case 'r':
	 giro_intorno_a_se_stesso_satellite_2 = (giro_intorno_a_se_stesso_satellite_2 + 2) % 360;
         glutPostRedisplay();
         break;
      case 'R':     
	 giro_intorno_a_se_stesso_satellite_2 = (giro_intorno_a_se_stesso_satellite_2 - 2) % 360;
         glutPostRedisplay();
         break;	
      case 't':
	 giro_intorno_al_pianeta_2 = ( giro_intorno_al_pianeta_2 + 2 ) % 360;
	 glutPostRedisplay();
	 break;
      case 'T':
	 giro_intorno_al_pianeta_2 = ( giro_intorno_al_pianeta_2 - 2 ) % 360;
	 glutPostRedisplay();
	 break;
      case 'x':
	 giro_intorno_a_se_stesso_satellite_1 =  (giro_intorno_a_se_stesso_satellite_1 + 2 ) % 360;
	 giro_intorno_al_pianeta_1 = ( giro_intorno_al_pianeta_1 + 1 ) % 360;
         giro_intorno_a_se_stesso_1 = (giro_intorno_a_se_stesso_1 + 10) % 360;
         giro_intorno_al_sole_1 = (giro_intorno_al_sole_1 + 5) % 360;
         glutPostRedisplay();
	 break;
      case 'c':
	 giro_intorno_a_se_stesso_satellite_2 =  (giro_intorno_a_se_stesso_satellite_2 + 2 ) % 360;
	 giro_intorno_al_pianeta_2 = ( giro_intorno_al_pianeta_2 + 1 ) % 360;
         giro_intorno_a_se_stesso_2 = (giro_intorno_a_se_stesso_2 + 10) % 360;
         giro_intorno_al_sole_2 = (giro_intorno_al_sole_2 + 5) % 360;
         glutPostRedisplay();
	 break;
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (800, 400); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Sistema Solare");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
