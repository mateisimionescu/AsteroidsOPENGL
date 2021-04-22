#include<windows.h>
#include <gl/freeglut.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>

using namespace std;

double i = 200;
double j = 0.0;
double z = 200;
double alpha = 1.0;
int border = 800;
float viteza_user = 2;
float viteza_masina = 0;
int gamemode;
string timer = "0:00";
int timer_final;
char test = 'x';
int lives = 3;
long long int timp;
int highscore[4];




class asteroid
{
public:
	float x, y;
	float r, g, b;
	float xviteza, yviteza;

	void setDate(int x, int y, float r, float g, float b, float xviteza, float yviteza)
	{
		this->x = x;
		this->y = y;
		this->r = r;
		this->g = g;
		this->b = b;
		this->xviteza = xviteza;
		this->yviteza = yviteza;


	}

	bool CheckCollision() {
		if (sqrt(pow((x - i), 2) + pow((y - z), 2)) <= 50) {
			cout << "Coliziune";
			return true;
		}
		return false;
	}

	void printCoord() {
	}


};

asteroid m[100];
int nr_masini = 1;


void generare_nivel();
void random_gen(float, float);
void delete_from_array(int);

void load_highscore()
{
	ifstream f("highscore.txt");
	f >> highscore[0] >> highscore[1] >> highscore[2] >> highscore[3];
	f.close();
}

void print_highscore()
{
	ofstream g("highscore.txt");
	g << highscore[0] << '\n' << highscore[1] << '\n' << highscore[2] << '\n' << highscore[3] << '\n';
	g.close();
}

void dificultate()
{
	cout << "Alege dificultatea jocului" << endl;
	cout << "1- Usor" << endl;
	cout << "2- Mediu" << endl;
	cout << "3-Greu" << endl;
	cout << "4- Custom" << endl;


	int alegere = -1;
	cin >> alegere;
	while (alegere < 1 || alegere >4)
	{
		cout << "Alegere nevalida" << endl;
		cin >> alegere;
	}

	cout << alegere;
	gamemode = alegere;

	generare_nivel();
}

void custom_difficulty()
{
	float vitezamin;
	float vitezamax;
	cout << "Numar asteroizi =";
	cin >> nr_masini;
	cout << "Viteza minima a asteroizilor =";
	cin >> vitezamin;
	cout << "Viteza maxima a asteroizilor=";
	cin >> vitezamax;
	random_gen(vitezamin, vitezamax);
}

void generare_nivel()
{
	if (gamemode == 4)
	{
		custom_difficulty();
		return;

	}
	float factor_diff = (float)gamemode / 3;
	nr_masini = gamemode * 3;
	float vitezamin = factor_diff / 4 + 1;
	float vitezamax = factor_diff / 4 + 2;
	cout << vitezamin << " " << vitezamax << endl;
	random_gen(vitezamin, vitezamax);


}

void random_gen(float vitezamin, float vitezamax)
{
	//nr_masini = 10;
	for (int i = 0; i < nr_masini; i++)
	{
		int x = rand() % 600;
		int y = rand() % 600;
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float xviteza = vitezamin + rand() / (RAND_MAX / vitezamax);
		float yviteza = vitezamin + rand() / (RAND_MAX / vitezamax);
		cout << x << " " << y << " " << " " << r << " " << g << " " << b << " " << xviteza << " " << yviteza << endl;
		m[i].setDate(x, y, r, g, b, xviteza, yviteza);

	}
	//generare numere random https://stackoverflow.com/questions/686353/random-float-number-generation

}


void check_coliziune()
{
	for (int i = 0; i < nr_masini; i++)
	{
		m[i].printCoord();
		if (m[i].CheckCollision())
		{
			cout << "True";
			delete_from_array(i);
			lives--;
			cout << lives;
		}
	}
}

void delete_from_array(int i)
{
	for (int j = i; j < nr_masini - 1; j++)
		m[j] = m[j + 1];
	nr_masini--;

}

unsigned char* text(int x)
{
	unsigned char* pp = new unsigned char[4];
	if (x <= 9)
	{
		pp[0] = x + '0';
		pp[1] = NULL;
	}
	else if (x > 9 && x < 100)
	{
		pp[0] = x / 10 + '0';
		pp[1] = x % 10 + '0';
		pp[2] = NULL;
	}
	else
	{
		pp[0] = x / 100 + '0';
		pp[1] = x / 10 % 10 + '0';
		pp[2] = x % 10 + '0';
		pp[3] = NULL;
	}
	return pp;

}


void check_coordonate(asteroid& t)
{
	if (t.x > border - 25) {
		t.x = border - 25;
		t.xviteza = -t.xviteza;
	}

	if (t.y > border - 25) {
		t.y = border - 25;
		t.yviteza = -t.yviteza;
	}

	if (t.x < 25)
	{
		t.x = 25;
		t.xviteza = -t.xviteza;
	}

	if (t.y < 25)
	{
		t.y = 25;
		t.yviteza = -t.yviteza;
	}


}



void init(void)
{
	glClearColor(0.4, 0.4, 0.4, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, 800.0, 0, 800.0, -1.0, 1.0);

}


void deseneazaScena(void)
{
	if (lives == 0) i = z = 1000000;

	check_coliziune();
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//nava_spatiala

	glPushMatrix();
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(i + 25, z + 25);
	glVertex2d(i + 25, z - 25);
	glVertex2d(i - 25, z - 25);
	glVertex2d(i - 25, z + 25);

	glPopMatrix();
	glEnd();

	//asteroizii

	for (int i = 0; i < nr_masini; i++) {
		glLoadIdentity();
		glPushMatrix();
		glPushMatrix();
		check_coordonate(m[i]);
		m[i].x = m[i].x + m[i].xviteza;
		m[i].y = m[i].y + m[i].yviteza;
		glColor3f(m[i].r, m[i].g, m[i].b);
		glBegin(GL_POLYGON);
		glVertex2d(m[i].x + 25, m[i].y + 25);
		glVertex2d(m[i].x + 25, m[i].y - 25);
		glVertex2d(m[i].x - 25, m[i].y - 25);
		glVertex2d(m[i].x - 25, m[i].y + 25);
		glPopMatrix();
		glEnd();
	}


	/*for (int i = 0; i < nr_masini; i++)
	{
		glLoadIdentity();
		glPushMatrix();
		glPushMatrix();
		check_coordonate(m[i]);
		m[i].x = m[i].x + m[i].xviteza;
		m[i].y = m[i].y + m[i].yviteza;
		//cout << m[i].x << " " << m[i].y << endl;
		glTranslated(m[i].x, m[i].y, 0.0); // Vf, stivei: T

		glColor3f(m[i].r, m[i].g, m[i].b);
		glBegin(GL_POLYGON);

		for (int k = 0; k < 8; k++)
		{
			float hexTheta = 6.2831853 * k / 8;
			int x = 50 + 20 * cos(hexTheta);
			int y = 50 + 20 * sin(hexTheta);
			glVertex2i(x, y);
		}
		glPopMatrix();

		glEnd();

	}*/


	// TIMER 
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(0.0, 1.0, 0.0); // Green

	glRasterPos2i(400, 700);
	void* font = GLUT_BITMAP_9_BY_15;
	unsigned char* timer = NULL;
	if (lives > 0)
		timer = text(time(0) - timp);
	glutBitmapString(font, timer);



	//NR_VIETI
	glRasterPos2i(100, 700);
	const unsigned char* vieti_text = reinterpret_cast<const unsigned char*>("Vieti: ");
	glRasterPos2i(100, 700);
	glutBitmapString(font, vieti_text);

	unsigned char* vieti = text(lives);
	glutBitmapString(font, vieti);

	const unsigned char* score = reinterpret_cast<const unsigned char*>("HighScore: ");
	glRasterPos2i(600, 700);
	glutBitmapString(font, score);
	glRasterPos2i(700, 700);
	glutBitmapString(font, text(highscore[gamemode - 1]));

	if (lives > 0)
		glColor3f(0.4, 0.4, 0.4);
	else {
		glColor3f(0.0, 1.0, 0.0);
		if (test == 'x')
		{
			test = 'y';
			timer_final = time(0) - timp;
			if (timer_final > highscore[gamemode - 1])
			{
				highscore[gamemode - 1] = timer_final;
				print_highscore();
			}


		}

	}


	glRasterPos2i(500, 100);

	const unsigned char* text1 = reinterpret_cast<const unsigned char*>("Ati supravietuit ");
	const unsigned char* text2 = reinterpret_cast<const unsigned char*>(" secunde ");
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, text1);
	glRasterPos2i(650, 100);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, text2);
	glRasterPos2i(625, 100);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, text(timer_final));
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();



	glutSwapBuffers();
	glFlush();

}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 600.0, 0.0, 600.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}




void miscasus(void)
{
	if (z < border - 25)
		z = z + viteza_user;
	glutPostRedisplay();

}

void miscajos(void)
{
	if (z > 25)
		z = z - viteza_user;
	glutPostRedisplay();

}

void miscastanga(void)
{
	if (i > 25)
		i = i - viteza_user;
	glutPostRedisplay();
}

void miscadreapta(void)
{
	if (i < border - 25)
		i = i + viteza_user;
	glutPostRedisplay();
}


void mouse(int button, int x, int y)
{

	switch (button) {
	case GLUT_KEY_UP:
		glutIdleFunc(miscasus);
		break;
	case GLUT_KEY_DOWN:
		glutIdleFunc(miscajos);
		break;
	case GLUT_KEY_LEFT:
		glutIdleFunc(miscastanga);
		break;
	case GLUT_KEY_RIGHT:
		glutIdleFunc(miscadreapta);
		break;
	default:
		break;
	}



}


void main(int argc, char** argv)
{


	srand(time(0));
	load_highscore();
	dificultate();
	timp = time(0);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Asteroids");
	init();
	glutDisplayFunc(deseneazaScena);

	glutSpecialFunc(mouse);


	glutMainLoop();

}