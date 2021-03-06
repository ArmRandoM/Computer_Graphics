#include "GL/freeglut.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/*variabili per la gestione del posizionamento casuale della camera, del Tesseract e della sua rotazione*/
static GLint coordinate_random[2];
static GLint coordinate_random_cubo_rotante[3];
static int spin = 0.0;

/*variabili per il posizionamento e per la gestione dell'angolazione della camera in modalità 'FPS'*/
static GLfloat Posizione_Della_Camera[] = {3.0, 4.0, 3.0};
static GLfloat Direzione_Della_Camera[] = {0.0, 4.0, 0.0};
static GLfloat camera_angle_y = 0.0;
static GLfloat sposta = 0.2;

/*variabile utilizzata per generare le texture della sfera*/
GLUquadricObj *sphere = NULL;

/*varibili utilizzate per la gestione della luce, con posizionamento, direzione e modalità in cui i materiali la riflettono*/
GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat specularLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat specref[] = { 0.1f, 0.1f, 0.1f, 1.0f };
static GLfloat lightPos[] = { 45.0, 25.0, 0.0, 0.5 };
static GLfloat spotDir[] = {0.0, 0.0, 0.0};

/*variabili relative alle display list definite*/
GLuint DLLabirintoAsgardiano;
GLuint DLLabirintoTerrestre;
GLuint DLTesseract;

/*variabili utilizzate per la definizione del "visualizzatore di FPS"*/
int frame, timer, timebase = 0;
char s[30];

/*variabili utilizzate per il passaggio da una Display List ad un' altra*/
bool asgard = false;
bool terra = true;

/*variabili utilizzate per definire se un giocatore ha vinto ho perso*/
bool vinto = false;
bool perso = false;
bool vinto1 = false;
bool perso1 = false;
bool continua = true;

/*variabili utilizzate per definire il tempo giocabile*/
int tempo_rimanente = 0;
int tempo_passato = 0;

#define TRUE  1
#define FALSE 0

/*funzione per il calcolo del tempo di gioco*/
void Tempo_Rimanente(int pid)
{
	if (tempo_rimanente < 120)
		tempo_rimanente++;
	else
		tempo_rimanente = 0;

	tempo_passato++;

	glutTimerFunc(1000, Tempo_Rimanente, 345);
}

/*funzione utilizzata per la visualizzazione del tempo di gioco*/
void printTime(int number, float x, float y)
{
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); // save
	glLoadIdentity();// and clear
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
			
	glLoadIdentity();

	char* buf;
	buf = new char[100];

	if(tempo_passato/60 < 3 && vinto != true && perso != true)
		{
			if( ( tempo_rimanente % 60 ) < 10 )
				snprintf ( buf, 100, "Tempo Di Gioco %d:0%d", tempo_passato/60, tempo_rimanente % 60 );
			else
				snprintf ( buf, 100, "Tempo Di Gioco %d:%d", tempo_passato/60, tempo_rimanente % 60 );
		}
	else if( vinto == true)
			{		
				snprintf( buf, 100, "Hai vinto!!");
				if( tempo_rimanente >= 5)
				vinto1 = true;				 	
			}
		else if( tempo_passato/6 >= 3)
				{
					snprintf ( buf, 100, "Hai Perso!!");
					perso = true;
					tempo_rimanente = 0;
					tempo_passato = 0;
				}
			else if( perso == true)
					{
						snprintf ( buf, 100, "Hai Perso!!");
						if( tempo_rimanente >= 5) 
							perso1 = true;
					}
	
	glRasterPos3f(x, y, -1); 
	glColor3f(1.0, 1.0, 1.0);
	
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)buf);

	glMatrixMode(GL_PROJECTION);
	glTranslatef(-10.0, -10.0, -10.0);

	glPopMatrix(); 
	glMatrixMode(GL_MODELVIEW);

	glPopMatrix();

	glEnable(GL_LIGHTING);

	glutPostRedisplay();
}

/*Per rappresentare la mappa del labirinto è stata utilizzata una matrice 40x40*/
int maze[20][20] = 
					{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
					  1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
					  1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,1,0,0,1,
					  1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,
					  1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,
					  1,0,0,1,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,1,
					  1,0,0,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
					  1,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,
					  1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
					  1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,1,
					  1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,
					  1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,
					  1,0,0,1,1,1,1,1,0,0,0,0,0,1,0,0,1,0,0,1,
					  1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,
					  1,0,0,1,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,
					  1,0,0,1,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,
					  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
					  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					};


/*Funzione utilizzata per il caricamento delle texture, prende un parametro in entrata definito da un puntatore a carattere che identifica il nome*/

GLuint Carica_Texture( const char * Nome_File)
{
	GLuint texture;
	unsigned char * data;
	FILE * file;
	file = fopen( Nome_File, "rb" );
	int Larghezza, Altezza;
	if ( file == NULL ) return 0;
	Larghezza = 340;
	Altezza = 340;
	data = (unsigned char *)malloc( Larghezza * Altezza * 3 );
	fread( data, Larghezza * Altezza * 3, 1, file );
	fclose( file );
	for(int i = 0; i < Larghezza * Altezza ; ++i)
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
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, Larghezza, Altezza,GL_RGB, GL_UNSIGNED_BYTE, data );
	free( data );
	return texture;
}

/*funzione utilizzata per creare una porzione del pavimento*/

void Costruisci_Mattone()
{
	glBegin(GL_QUADS);

	glNormal3f( 0.0, -1.0, 0.0 );
	glTexCoord2f( 1.0f, 1.0f );
	glVertex3f( -1.0f, 1.0f, -1.0f );
	glTexCoord2f( 1.0f, 0.0f );
	glVertex3f( -1.0f,  1.0f,  1.0f );
	glTexCoord2f( 0.0f, 0.0f );
	glVertex3f(  1.0f,  1.0f,  1.0f );
	glTexCoord2f( 0.0f, 1.0f );
	glVertex3f(  1.0f,  1.0f, -1.0f );

	glEnd( );
}

/*funzione utilizzata per creare una porzione di muro*/
void Costruisci_Muro()
{
	glBegin(GL_QUADS);

		/* Faccia Anteriore del Mattone */
		glNormal3f( 0.0, 0.0, 1.0 );
		glTexCoord2f( 0.0f, 1.0 );
		glVertex3f( -1.0f, -1.0f, 1.0 );
		glTexCoord2f( 1.0, 1.0 );
		glVertex3f(  1.0, -1.0, 1.0 );
		glTexCoord2f( 1.0, 0.0 );
		glVertex3f(  1.0,  1.0, 1.0 );
		glTexCoord2f( 0.0, 0.0 );
		glVertex3f( -1.0,  1.0, 1.0 );

		/* Faccia Posteriore Del Mattone */	
		glNormal3f( 0.0, 0.0, -1.0 );
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( -1.0f, -1.0f, -1.0f );
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( -1.0f,  1.0f, -1.0f );
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f(  1.0f,  1.0f, -1.0f );
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f(  1.0f, -1.0f, -1.0f );

		/* Faccia Destra Del Mattone*/
		glNormal3f( 1.0, 0.0, 0.0 );
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( 1.0f, -1.0f, -1.0f );
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( 1.0f,  1.0f, -1.0f );
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( 1.0f,  1.0f,  1.0f );
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( 1.0f, -1.0f,  1.0f );

		/* Faccia Sinistra Del Mattone*/
		glNormal3f( -1.0, 0.0, 0.0 );
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


/*funzione utilizzata per creare il Tesseract*/
GLuint Costruisci_Il_Cubo_Rotante_DL()
{
	GLuint DL;

	DL = glGenLists(1);

	glNewList( DL, GL_COMPILE);
		
	GLuint my_texture = Carica_Texture( "Tesseract.bmp");
	glBindTexture (GL_TEXTURE_2D, my_texture);
	
	glBegin(GL_QUADS);
		/* Faccia Anteriore del Mattone */
		glTexCoord2f( 0.0, 1.0 );
		glVertex3f( -0.5, -0.5, 0.5 );
		glTexCoord2f( 1.0, 1.0 );
		glVertex3f(  0.5, -0.5, 0.5 );
		glTexCoord2f( 1.0, 0.0 );
		glVertex3f(  0.5,  0.5, 0.5 );
		glTexCoord2f( 0.0, 0.0 );
		glVertex3f( -0.5,  0.5, 0.5 );
	
		/* Faccia Posteriore Del Mattone */
		glTexCoord2f( 0.0, 0.0 );
		glVertex3f( -0.5, -0.5, -0.5 );	
		glTexCoord2f( 0.0, 1.0 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glTexCoord2f( 1.0, 1.0 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glTexCoord2f( 1.0, 0.0 );
		glVertex3f(  0.5, -0.5, -0.5 );
	
		/*Faccia Superiore Del Mattone */
		glTexCoord2f( 1.0, 1.0 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glTexCoord2f( 1.0, 0.0 );
		glVertex3f( -0.5,  0.5,  0.5 );
		glTexCoord2f( 0.0, 0.0 );
		glVertex3f(  0.5,  0.5,  0.5 );
		glTexCoord2f( 0.0, 1.0 );
		glVertex3f(  0.5,  0.5, -0.5 );
	
		/* Faccia Inferiore Del Mattone*/
		glTexCoord2f( 0.0, 1.0 );
		glVertex3f( -0.5, -0.5, -0.5 );
		glTexCoord2f( 1.0, 1.0 );
		glVertex3f(  0.5, -0.5, -0.5 );
		glTexCoord2f( 1.0, 0.0 );
		glVertex3f(  0.5, -0.5,  0.5 );
		glTexCoord2f( 0.0, 0.0 );
		glVertex3f( -0.5, -0.5,  0.5 );
	
		/* Faccia Destra Del Mattone*/
		glTexCoord2f( 0.0, 0.0 );
		glVertex3f( 0.5, -0.5, -0.5 );
		glTexCoord2f( 0.0, 1.0 );
		glVertex3f( 0.5,  0.5, -0.5 );
		glTexCoord2f( 1.0, 1.0 );
		glVertex3f( 0.5,  0.5,  0.5 );
		glTexCoord2f( 1.0, 0.0 );
		glVertex3f( 0.5, -0.5,  0.5 );
	
		/* Faccia Sinistra Del Mattone*/
		glTexCoord2f( 1.0, 0.0 );
		glVertex3f( -0.5, -0.5, -0.5 );
		glTexCoord2f( 0.0, 0.0 );
		glVertex3f( -0.5, -0.5,  0.5 );
		glTexCoord2f( 0.0, 1.0 );
		glVertex3f( -0.5,  0.5,  0.5 );
		glTexCoord2f( 1.0, 1.0 );
		glVertex3f( -0.5,  0.5, -0.5 );
	
	glEnd( );

	glEndList();
	
	return (DL);
}

/*Funzione per la creazione della Display List relativa al paesaggio terrestre*/
GLuint Terra() 
{
	GLuint MattoniDL, SiepeDL, PavimentoDL, SiepiDL, CieloDL, LunaDL, loopDL;

	MattoniDL = glGenLists(1);
	SiepeDL = glGenLists(1);
	PavimentoDL = glGenLists(1);
	SiepiDL = glGenLists(1);
	CieloDL = glGenLists(1);
	LunaDL = glGenLists(1);
	loopDL = glGenLists(1);

	glNewList(MattoniDL,GL_COMPILE);
		Costruisci_Mattone();
	glEndList();

	glNewList(SiepeDL, GL_COMPILE);
		Costruisci_Muro();
	glEndList();

	glNewList(PavimentoDL ,GL_COMPILE);

		GLuint my_texture = Carica_Texture( "pavimento.bmp");
		glBindTexture (GL_TEXTURE_2D, my_texture);

		for (int yc = 0; yc < 20; yc++)
			{
				for (int xc = 0; xc < 20; xc++)
					{
						if( maze[xc][yc] != 1)
							{
								glPushMatrix();
									glTranslatef( xc*2.0, 0.0, yc*2.0 );
									glCallList(MattoniDL);
								glPopMatrix();
							}
					}
			}

	glEndList();
	
	glNewList(SiepiDL ,GL_COMPILE);

		my_texture = Carica_Texture( "siepi.bmp" );
		glBindTexture (GL_TEXTURE_2D, my_texture);

		GLfloat y = 2.0;

		for( int i = 0; i < 3; i++)
			{
				for (int yc = 0; yc < 20; yc++)
					{
						for (int xc = 0; xc < 20; xc++)
							{
								if (maze[ xc][yc] == 1)
									{
										glPushMatrix();
											glTranslatef( xc*2.0, y, yc*2.0 );
											glCallList(SiepeDL);
										glPopMatrix();
									}
							}
					}
				y = y + 2;
			}

	glEndList();

	glNewList(CieloDL ,GL_COMPILE);

		my_texture = Carica_Texture( "cielo.bmp");
		glBindTexture (GL_TEXTURE_2D, my_texture);

		glPushMatrix();
			glTranslatef( 40.0, 0.0, 40.0 );
			sphere = gluNewQuadric();
			gluQuadricDrawStyle(sphere, GLU_FILL);
			gluQuadricTexture(sphere, GL_TRUE);
			gluQuadricNormals(sphere, GLU_SMOOTH);
			gluSphere(sphere, 65.0, 1000, 1000);
		glPopMatrix();

	glEndList();

	glNewList(LunaDL ,GL_COMPILE);

		my_texture = Carica_Texture( "luna.bmp");
		glBindTexture (GL_TEXTURE_2D, my_texture);

		glPushMatrix();
			glLightfv(GL_LIGHT0,GL_POSITION, lightPos);
			glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spotDir);
			glDisable(GL_LIGHTING);
			glTranslatef( 45.0, 25.0, 0.0 );
			sphere = gluNewQuadric();
			gluQuadricDrawStyle(sphere, GLU_FILL);
			gluQuadricTexture(sphere, GL_TRUE);
			gluQuadricNormals(sphere, GLU_SMOOTH);
			gluSphere(sphere, 0.8, 50, 50);
			glEnable(GL_LIGHTING);
		glPopMatrix();

	glEndList();


	glNewList(loopDL ,GL_COMPILE);

		glCallList(PavimentoDL);
		glCallList(SiepiDL);
		glCallList(CieloDL);
		glCallList(LunaDL);

	glEndList();

	return(loopDL);
}

/*Funzione per la creazione della Display List relativa al paesaggio asgardiano*/
GLuint Asgard() 
{
	GLuint MattoniDL, MuroDL, PavimentoDL, MuriDL, CieloDL, LunaDL, loopDL;

	MattoniDL = glGenLists(1);
	MuroDL = glGenLists(1);
	PavimentoDL = glGenLists(1);
	MuriDL = glGenLists(1);
	CieloDL = glGenLists(1);
	LunaDL = glGenLists(1);
	loopDL = glGenLists(1);

	glNewList(MattoniDL,GL_COMPILE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);	
		Costruisci_Mattone();
		glDisable(GL_BLEND);
	glEndList();

	glNewList(MuroDL, GL_COMPILE);
		Costruisci_Muro();
	glEndList();

	glNewList(PavimentoDL ,GL_COMPILE);

		GLuint my_texture = Carica_Texture( "Bifrost.bmp");
		glBindTexture (GL_TEXTURE_2D, my_texture);

		for (int yc = 0; yc < 20; yc++)
			{
				for (int xc = 0; xc < 20; xc++)
					{
						if( maze[xc][yc] != 1)
							{
								glPushMatrix();
									glTranslatef( xc*2.0, 0.0, yc*2.0 );
									glCallList(MattoniDL);
								glPopMatrix();
							}
					}
			}

	glEndList();
	
	glNewList(MuriDL ,GL_COMPILE);

		my_texture = Carica_Texture( "Gold.bmp");
		glBindTexture (GL_TEXTURE_2D, my_texture);

		GLfloat y = 2.0;

		for( int i = 0; i < 3; i++)
			{
				for (int yc = 0; yc < 20; yc++)
					{
						for (int xc = 0; xc < 20; xc++)
							{
								if (maze[ xc][yc] == 1)
									{
										glPushMatrix();
											glTranslatef( xc*2.0, y, yc*2.0 );
											glCallList(MuroDL);
										glPopMatrix();
									}
							}
					}
				y = y + 2;
			}

	glEndList();

	glNewList(CieloDL ,GL_COMPILE);

		my_texture = Carica_Texture( "CieloAsgard.bmp");
		glBindTexture (GL_TEXTURE_2D, my_texture);

		glPushMatrix();
			glTranslatef( 40.0, 0.0, 40.0 );
				sphere = gluNewQuadric();
				gluQuadricDrawStyle(sphere, GLU_FILL);
				gluQuadricTexture(sphere, GL_TRUE);
				gluQuadricNormals(sphere, GLU_SMOOTH);
				gluSphere(sphere, 65.0, 1000, 1000);
	glPopMatrix();

	glEndList();

	glNewList(LunaDL ,GL_COMPILE);

		my_texture = Carica_Texture( "luna.bmp");
		glBindTexture (GL_TEXTURE_2D, my_texture);

		glPushMatrix();
				glLightfv(GL_LIGHT0,GL_POSITION, lightPos);
				glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spotDir);
				glDisable(GL_LIGHTING);
				glTranslatef( 45.0, 25.0, 0.0 );
				sphere = gluNewQuadric();
				gluQuadricDrawStyle(sphere, GLU_FILL);
				gluQuadricTexture(sphere, GL_TRUE);
				gluQuadricNormals(sphere, GLU_SMOOTH);
				gluSphere(sphere, 0.8, 50, 50);
				glEnable(GL_LIGHTING);
		glPopMatrix();

	glEndList();


	glNewList(loopDL ,GL_COMPILE);

		glCallList(MuriDL);
		glCallList(CieloDL);
		glCallList(LunaDL);
		glCallList(PavimentoDL);

	glEndList();

	return(loopDL);
}

/*funzione init*/
void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	DLLabirintoTerrestre = Terra();
	DLLabirintoAsgardiano = Asgard();
	DLTesseract = Costruisci_Il_Cubo_Rotante_DL();
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specularLight);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
	glMateriali(GL_FRONT, GL_SHININESS,1);
}

/*funzione per la visualizzazione del contesto grafico*/
void display(void)
{

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);

	spin = ( spin + 1 ) % 360;
	glutPostRedisplay();

	glPushMatrix();

		gluLookAt(Posizione_Della_Camera[0], Posizione_Della_Camera[1], Posizione_Della_Camera[2], Posizione_Della_Camera[0] + Direzione_Della_Camera[0],Direzione_Della_Camera[1],Posizione_Della_Camera[2] + Direzione_Della_Camera[2], 0.0, 1.0, 0.0);
		
		if( asgard == true)
			glCallList(DLLabirintoAsgardiano);
		else
			glCallList(DLLabirintoTerrestre);
	
		printTime(tempo_rimanente, -0.9, 0.7);
	
		glPushMatrix();

			glDisable(GL_LIGHTING);

			glTranslatef( coordinate_random_cubo_rotante[0], coordinate_random_cubo_rotante[1], coordinate_random_cubo_rotante[2]);

			if( vinto == true)
				{	
					GLuint my_texture = Carica_Texture( "Gemma.bmp");
					glBindTexture (GL_TEXTURE_2D, my_texture);
					glRotatef( spin, 0.0, 1.0, 0.0);
					gluSphere( sphere, 0.5, 100, 100);
				}
			else 
				{
					glRotatef( spin, 0.0, 1.0, 0.0);
					glCallList(DLTesseract);
				}
			glEnable(GL_LIGHTING);

		glPopMatrix();

//		frame++;
//		timer=glutGet(GLUT_ELAPSED_TIME);
//		if (timer - timebase > 1000) {
//			sprintf(s,"FPS:%4.2f",frame*1000.0/(timer-timebase));
//			glutSetWindowTitle(s);
//			timebase = timer;
//			frame = 0;
//		}
	
	glPopMatrix();

	glutSwapBuffers();
}

/*funzione utilizzata per la gestione delle collisioni*/
int Ricerca_Collisioni(GLfloat x, GLfloat z, GLfloat w)
{
	unsigned int i, j;
	unsigned int minx, minz, maxx, maxz;

	// Convertiamo le coordinate da pixel in un equivalente per la matrice
	minx = x / 2;
	minz = z / 2;

	maxx = (x + w - 1) / 2;
	maxz = (z + w - 1) / 2;


	// Se il rettangolo interseca un mattone nella matrice ritorniamo una collisione
	for (i = minx; i <= maxx ; i++)
		{
			for (j = minz ; j <= maxz ; j++)
				{
					if (maze[i][j] == 1)
						return 1;
				}
		}

	/*coordinate massime e minime della camera*/
	GLfloat minx_camera = Posizione_Della_Camera[0] - 1.2;
	GLfloat minz_camera = Posizione_Della_Camera[2] - 1.2;
	GLfloat maxx_camera = Posizione_Della_Camera[0] + 1.2;
	GLfloat maxz_camera = Posizione_Della_Camera[2] + 1.2;

	/*coordinate massime e minime del Tesseract*/
	GLfloat minx_cubo = coordinate_random_cubo_rotante[0] - 0.5;
	GLfloat minz_cubo = coordinate_random_cubo_rotante[2] - 0.5;
	GLfloat maxx_cubo = coordinate_random_cubo_rotante[0] + 0.5;
	GLfloat maxz_cubo = coordinate_random_cubo_rotante[2] + 0.5;

	//Gestore delle collisioni tra Camera e Tesseract
	if((minx_camera < maxx_cubo && maxx_camera > minx_cubo) && (maxz_camera > minz_cubo && minz_camera < maxz_cubo))
		{
			tempo_rimanente = 0;
			vinto = true;
			return 1;
		}
	
	//Se il tempo è scaduto vengono rilevate Collisioni "Fantasma" per non fare spostare la camera
	if( perso == true)
		return 1;

//	// Nessuna collisione
	return 0;
}

/*funzione utilizzata per la generazione di coordinate casuali relative alla posizione del giocatore e della camera all'interno del labirinto*/
void genera_coordinate_random()
{
	coordinate_random[0] = rand() % 40;
	coordinate_random[1] = rand() % 40;
	while(Ricerca_Collisioni( coordinate_random[0], coordinate_random[1], 3.0))
		{
			coordinate_random[0] = rand() % 40;
			coordinate_random[1] = rand() % 40;
		}

	Posizione_Della_Camera[0] = coordinate_random[0];
	Posizione_Della_Camera[2] = coordinate_random[1];

	coordinate_random_cubo_rotante[0] = rand() % 40;
	coordinate_random_cubo_rotante[1] = 4;
	coordinate_random_cubo_rotante[2] = rand() % 40;

	while(Ricerca_Collisioni( coordinate_random_cubo_rotante[0], coordinate_random_cubo_rotante[2], 2.0))
		{
			coordinate_random_cubo_rotante[0] = rand() % 40;
			coordinate_random_cubo_rotante[2] = rand() % 40;
		}

	maze[coordinate_random_cubo_rotante[0]/2][coordinate_random_cubo_rotante[2]/2] = 2;
}

/*funzione reshape*/
void reshape (int w, int h)
{
		glViewport (0, 0, (GLsizei) w, (GLsizei) h);
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();//rimpiazza la matrice corrente con quella di identità
		gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 600.0);
		glMatrixMode(GL_MODELVIEW);//gestisce le trasformazioni di viewing e modeling
		glLoadIdentity();
}

/*funzione utilizzata per la gestione dei comandi associati ai tasti della keyboard*/
void keyboard (unsigned char key, int x, int y)
{
	GLfloat xc, zc;

	switch (key)
		{
			case 'a':
				if( vinto == false && perso == false)
					{
						camera_angle_y -= 0.05;
						Direzione_Della_Camera[0] = sin(camera_angle_y);
						Direzione_Della_Camera[2] = -cos(camera_angle_y);
						glutPostRedisplay();
						break;
					}
			case 'd':
				if( vinto == false && perso == false)
					{
						camera_angle_y += 0.05;
						Direzione_Della_Camera[0] = sin(camera_angle_y);
						Direzione_Della_Camera[2] = -cos(camera_angle_y);
						glutPostRedisplay();
       					break;
					}
			case 'w':
				xc = (Posizione_Della_Camera[0] + Direzione_Della_Camera[0]);
				zc = ( Posizione_Della_Camera[2] + Direzione_Della_Camera[2]);
				if(!Ricerca_Collisioni( xc, zc, 3.0))
					{
						Posizione_Della_Camera[0] += Direzione_Della_Camera[0] * sposta;
						Posizione_Della_Camera[2] += Direzione_Della_Camera[2] * sposta;
					}
				glutPostRedisplay();
				break;
			case 's':
				xc = (Posizione_Della_Camera[0] - Direzione_Della_Camera[0]);
				zc = ( Posizione_Della_Camera[2] - Direzione_Della_Camera[2]);
				if(!Ricerca_Collisioni( xc, zc, 3.0))
					{
						Posizione_Della_Camera[0] -= Direzione_Della_Camera[0] * sposta;
						Posizione_Della_Camera[2] -= Direzione_Della_Camera[2] * sposta;
					}
				glutPostRedisplay();
				break;
			case 'T':
				terra = true;
				asgard = false;
				break;
			case 'A':
				terra = false;
				asgard = true;	
				break;
		default:
			glutIdleFunc(NULL);
			break;
	}
}

/*funzione main*/
int main(int argc, char** argv)
{
	srand(time (0));
	genera_coordinate_random();
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize ( 1250, 1250);
	glutInitWindowPosition (5, 5);
	glutCreateWindow ("Labirinto IG Armando Pezzimenti");
	init ();
	glutTimerFunc(0, Tempo_Rimanente, 345);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	while( perso1 == false && vinto1 == false )
		glutMainLoopEvent();
	
	return 0;
}
