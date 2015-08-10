#include <GL/glut.h>


static GLfloat spin = 0.0;

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   glRotatef(spin, 0.0, 0.0, 1.0);
   glColor3f(1.0, 1.0, 1.0);
   glRectf(-25.0, -25.0, 25.0, 25.0);
   glPopMatrix();

   glutSwapBuffers();
}

void Orario(void)
{
   spin = spin - 2.0;
   if (spin < 360.0)
      spin = spin + 360.0;
   glutPostRedisplay();
}

void Antiorario(void)
{
   spin = spin + 2.0;
   if (spin < 360.0)
      spin = spin - 360.0;
   glutPostRedisplay();
}

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   /*riserva l'intera area della finestra come area per l' output grafico, l'angolo in basso a sinistra coincide con il punto 0,0 e quello in alto
   a destra coincide con il punto w,h dove w e h sono il numero di colonne e linee della finestra in linee*/ 
  
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-50.0, 50.0, -50.0, 50.0, 1.0, -1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void mouse(int button, int state, int x, int y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)//GLUT_DOWN quando viene premuto
            glutIdleFunc(Orario);
         break;

      case GLUT_MIDDLE_BUTTON:
          if (state == GLUT_UP)//GLUT_UP quando viene rilasciato
            glutIdleFunc(NULL);
            /*specifica una funzione che deve essere eseguita mentre nessun altro evento deve essere soddisfatto, passare NULL come argomento
            implica la disattivazione del processo in background*/
          break;
    
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)//GLUT_DOWN quando viene premuto
            glutIdleFunc(Antiorario);
         break;
      default:
         break;
   }
}
   
/* 
 *  Request double buffer display mode.
 *  Register mouse input callback functions
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (250, 250); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Poligono O e AO");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 

   glutMouseFunc(mouse);
   /*determina l'esecuzione di una funzione ogn volta che un tasto del mouse viene premuto o rilasciato*/

   glutMainLoop();
   return 0;   /* ANSI C requires main to return int. */
}
