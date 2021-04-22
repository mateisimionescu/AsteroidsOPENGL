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
float user_speed = 2;
int gamemode;
string timer = "0:00";
char test = 'x';
int timer_final;
int lives = 3;
long long int timp;
int highscore[4];




class Asteroid
{
public:
	float x, y;
	float r, g, b;
	float xspeed, yspeed;

	void setDate(int x, int y, float r, float g, float b, float xspeed, float yspeed)
	{
		this->x = x;
		this->y = y;
		this->r = r;
		this->g = g;
		this->b = b;
		this->xspeed = xspeed;
		this->yspeed = yspeed;


	}

	bool CheckCollision() {
		if (sqrt(pow((x - i), 2) + pow((y - z), 2)) <= 50) {
			cout << "Collision";
			return true;
		}
		return false;
	}

	void printCoord() {
	}


};

Asteroid m[100];
int asteroidNumber = 1;


void generateLevel();
void generateRandom(float, float);
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
	cout << "Pick difficulty" << endl;
	cout << "1- Easy" << endl;
	cout << "2- Medium" << endl;
	cout << "3- Hard" << endl;
	cout << "4- Custom" << endl;


	int choice = -1;
	cin >> choice;
	while (choice < 1 || choice >4)
	{
		cout << "Invalid choice" << endl;
		cin >> choice;
	}

	cout << choice;
	gamemode = choice;

	generateLevel();
}

void custom_difficulty()
{
	float minspeed;
	float maxspeed;
	cout << "Number of asteroids =";
	cin >> asteroidNumber;
	cout << "Minimum asteroid speed =";
	cin >> minspeed;
	cout << "Max asteroid speed =";
	cin >> maxspeed;
	generateRandom(minspeed, maxspeed);
}

void generateLevel()
{
	if (gamemode == 4)
	{
		custom_difficulty();
		return;

	}
	float factor_diff = (float)gamemode / 3;
	asteroidNumber = gamemode * 3;
	float minspeed = factor_diff / 4 + 1;
	float maxspeed = factor_diff / 4 + 2;
	cout << minspeed << " " << maxspeed << endl;
	generateRandom(minspeed, maxspeed);


}

void generateRandom(float minspeed, float maxspeed)
{
	for (int i = 0; i < asteroidNumber; i++)
	{
		int x = rand() % 600;
		int y = rand() % 600;
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float xspeed = minspeed + rand() / (RAND_MAX / maxspeed);
		float yspeed = minspeed + rand() / (RAND_MAX / maxspeed);
		cout << x << " " << y << " " << " " << r << " " << g << " " << b << " " << xspeed << " " << yspeed << endl;
		m[i].setDate(x, y, r, g, b, xspeed, yspeed);

	}

}


void check_coliziune()
{
	for (int i = 0; i < asteroidNumber; i++)
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
	for (int j = i; j < asteroidNumber - 1; j++)
		m[j] = m[j + 1];
	asteroidNumber--;

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


void check_coordonate(Asteroid& t)
{
	if (t.x > border - 25) {
		t.x = border - 25;
		t.xspeed = -t.xspeed;
	}

	if (t.y > border - 25) {
		t.y = border - 25;
		t.yspeed = -t.yspeed;
	}

	if (t.x < 25)
	{
		t.x = 25;
		t.xspeed = -t.xspeed;
	}

	if (t.y < 25)
	{
		t.y = 25;
		t.yspeed = -t.yspeed;
	}


}



void init(void)
{
	glClearColor(0.4, 0.4, 0.4, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, 800.0, 0, 800.0, -1.0, 1.0);

}


void drawScene(void)
{
	if (lives == 0) i = z = 1000000;

	check_coliziune();
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


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


	for (int i = 0; i < asteroidNumber; i++) {
		glLoadIdentity();
		glPushMatrix();
		glPushMatrix();
		check_coordonate(m[i]);
		m[i].x = m[i].x + m[i].xspeed;
		m[i].y = m[i].y + m[i].yspeed;
		glColor3f(m[i].r, m[i].g, m[i].b);
		glBegin(GL_POLYGON);
		glVertex2d(m[i].x + 25, m[i].y + 25);
		glVertex2d(m[i].x + 25, m[i].y - 25);
		glVertex2d(m[i].x - 25, m[i].y - 25);
		glVertex2d(m[i].x - 25, m[i].y + 25);
		glPopMatrix();
		glEnd();
	}


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(0.0, 1.0, 0.0); 

	glRasterPos2i(400, 700);
	void* font = GLUT_BITMAP_9_BY_15;
	unsigned char* timer = NULL;
	if (lives > 0)
		timer = text(time(0) - timp);
	glutBitmapString(font, timer);



	
	glRasterPos2i(100, 700);
	const unsigned char* lifeText = reinterpret_cast<const unsigned char*>("Lives: ");
	glRasterPos2i(100, 700);
	glutBitmapString(font, lifeText);

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

	const unsigned char* text1 = reinterpret_cast<const unsigned char*>("You survived ");
	const unsigned char* text2 = reinterpret_cast<const unsigned char*>(" seconds ");
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




void moveup(void)
{
	if (z < border - 25)
		z = z + user_speed;
	glutPostRedisplay();

}

void movedown(void)
{
	if (z > 25)
		z = z - user_speed;
	glutPostRedisplay();

}

void moveleft(void)
{
	if (i > 25)
		i = i - user_speed;
	glutPostRedisplay();
}

void moveright(void)
{
	if (i < border - 25)
		i = i + user_speed;
	glutPostRedisplay();
}


void mouse(int button, int x, int y)
{

	switch (button) {
	case GLUT_KEY_UP:
		glutIdleFunc(moveup);
		break;
	case GLUT_KEY_DOWN:
		glutIdleFunc(movedown);
		break;
	case GLUT_KEY_LEFT:
		glutIdleFunc(moveleft);
		break;
	case GLUT_KEY_RIGHT:
		glutIdleFunc(moveright);
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
	glutDisplayFunc(drawScene);

	glutSpecialFunc(mouse);


	glutMainLoop();

}