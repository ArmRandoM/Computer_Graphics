//ogni programma OpenGL deve inziare con l'inclusione delle seguenti librerie
#include <GL/glut.h>
#include <GL/gl.h>

int main ( int argc, char** argv )   
{
	glutInit(&argc, argv);

   	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB );
	/*specifica se utilizzare il modo RGBA o il modo color-index, si può specificare se la finestra è single o double buffered*/
   	
	glutInitWindowSize ( 500, 500 ); 
	/*specifica le dimensioni in pixel della finestra*/

   	glutInitWindowPosition ( 100, 100 );
	/*specifica la posizione in pixel dell'angolo in alto a destra della finestra rispetto al sistema di coordinate del sistema a finestre*/
 	
	glutCreateWindow ("Poligono 2D");
	/*crea una finestra con un contesto OpenGL dove l'argomento è il nome della finestra*/

//init
	glClearColor ( 0.0 , 0.0 , 0.0 , 0.0 );

//display
	glClear ( GL_COLOR_BUFFER_BIT );

	glColor3f ( 1.0 , 1.0 , 1.0 );
	/*il 3 indica che il comando accetta 3 elementi, f indica che i 3 elementi sono di tipo float (32 bit), setta 3 valori RGB del più 		articolato stato GL_CURRENT_COLOR, se invece il comando glColor fosse seguito da 3fv questo indica che il comando accetta un array di 3 	elementi di tipo float (32 bit) */
	
	gluOrtho2D ( 0.0 , 1.0 , 0.0 , 1.0 );
	/*definisce una matrice che utilizza un grafica 2D*/

	glBegin ( GL_QUADS);
		glVertex2f ( 0.25 , 0.25 );
		glVertex2f ( 0.75 , 0.25 );
		glVertex2f ( 0.75 , 0.75 );
		glVertex2f ( 0.25 , 0.75 );	
	glEnd();	
	/*specifica la primitiva o le primitive che possono essere create dai vertici presenti tra il comando glBegin e il seguente comando 		glEnd, l'argomento GL_POLYGON rappresenta un singolo poligono con vertici che vanno da 1 a N*/

	glFlush();
	
	glutSwapBuffers();

	glutMainLoop();
	/*mostra tutte le finestre create, inizia il processo di ascolto degli eventi, e attiva le display callback functions*/

	return 0;

}
