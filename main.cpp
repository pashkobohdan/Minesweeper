#include <glut.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <windows.h>

//#pragma comment(lib,"glut32")

using namespace std;



int kn = 0;
int x_w;
int y_w;
int          width, height;
int          button = -1;
float        angleX = 0, angleY = -30;
float        mouseX, mouseY;
float        distZ = -15;
double param_x;


int r_time = clock();
int frames = 0;
int r_fps = 0;
char f[10];


int active_menu = 1;
int active_game = 0;
int active_win = 0;

int win = -1;

int first_press = 0;

void renderStrokeFontString(float x, float y, float z, char *string, double k) {

	char *c;

	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(k, k, k);
	for (c = string; *c != '\0'; c++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glTranslatef(-x, -y, -z);
	glPopMatrix();

}

void renderText(char *string, float x, float y) {
	char *c;
	glRasterPos2f(x, y);


	for (c = string; *c != '\0'; c++) {

		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

	}
}

void renderText(char *string) {
	char *c;

	for (c = string; *c != '\0'; c++) {

		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

	}
}

class Button {
public:

	double x1;
	double y1;
	double x2;
	double y2;

	char *text;

	int active;
	int length;
	int off_on;
	int take;

	Button() {}

	Button(int off_on, double x1, double y1, double x2, double y2, char *string, int length) {
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
		this->length = length;
		this->off_on = off_on;

		take = 0;
		active = 0;

		text = string;
	}

	void show_button() {

		if (off_on == 1) {

			glColor3d(0, 0, 0.5);

			if (length == 1) {
				renderStrokeFontString(x1, y1 + 0.3, 0.2, text, 0.005);
			}
			if (length == 2) {
				renderStrokeFontString(x1, y1 + 0.5, 0.2, text, 0.005);
			}


			if (take == 1) {
				glColor3d(0.74, 0.24, 1);
			}
			else {
				if (active == 1) {
					glColor3d(1, 0.6, 0);
				}
				else {
					glColor3d(1, 0.8, 0.5);
				}
			}


			glBegin(GL_QUADS);
			glVertex3d(x1, y1, 0.1);
			glVertex3d(x1, y2, 0.1);
			glVertex3d(x2, y2, 0.1);
			glVertex3d(x2, y1, 0.1);
			glEnd();
		}
	}
};

class Quad {
public:
	int x;
	int y;
	double x_d;
	double y_d;

	int bomba;
	int sost;

	int number;

	int take_bomba;

	Quad() {}

	Quad(int x, int y) {
		this->x = x;
		this->y = y;

		x_d = double(x - 5);
		y_d = double(y - 5);
		bomba = 0;
		sost = 0;
		number = 0;
		take_bomba = 0;
	}

	void show_quad() {


		glBegin(GL_QUADS);

		if (sost == 0) {
			glColor3d(0.75, 0.3, 0.75);
		}
		else {
			glColor3d(0.75, 0.75, 0);
		}
		if (take_bomba == 1) {
			glColor3d(0.9, 0.3, 0);
		}
		//}

		glVertex3d(x_d - 0.3, y_d - 0.3, 0.1);//верх
		glVertex3d(x_d - 0.3, y_d + 0.3, 0.1);
		glVertex3d(x_d + 0.3, y_d + 0.3, 0.1);
		glVertex3d(x_d + 0.3, y_d - 0.3, 0.1);

		glVertex3d(x_d - 0.3, y_d - 0.3, -0.9);//низ
		glVertex3d(x_d - 0.3, y_d + 0.3, -0.9);
		glVertex3d(x_d + 0.3, y_d + 0.3, -0.9);
		glVertex3d(x_d + 0.3, y_d - 0.3, -0.9);
		//боковушки

		if (sost == 0) {
			glColor3d(0.75, 0.5, 0.5);
		}
		else {
			glColor3d(0.8, 0.8, 0);
		}
		if (take_bomba == 1) {
			glColor3d(0.95, 0.5, 0);
		}

		glVertex3d(x_d - 0.3, y_d - 0.3, -0.9);
		glVertex3d(x_d - 0.3, y_d + 0.3, -0.9);
		glVertex3d(x_d - 0.3, y_d + 0.3, 0.1);
		glVertex3d(x_d - 0.3, y_d - 0.3, 0.1);

		glVertex3d(x_d - 0.3, y_d + 0.3, 0.1);
		glVertex3d(x_d + 0.3, y_d + 0.3, 0.1);
		glVertex3d(x_d + 0.3, y_d + 0.3, -0.9);
		glVertex3d(x_d - 0.3, y_d + 0.3, -0.9);

		glVertex3d(x_d + 0.3, y_d + 0.3, 0.1);
		glVertex3d(x_d + 0.3, y_d - 0.3, 0.1);
		glVertex3d(x_d + 0.3, y_d - 0.3, -0.9);
		glVertex3d(x_d + 0.3, y_d + 0.3, -0.9);

		glVertex3d(x_d + 0.3, y_d - 0.3, 0.1);
		glVertex3d(x_d - 0.3, y_d - 0.3, 0.1);
		glVertex3d(x_d - 0.3, y_d - 0.3, -0.9);
		glVertex3d(x_d + 0.3, y_d - 0.3, -0.9);

		glEnd();
	}
};

class Game {
public:

	Quad q[100];

	int x_gamer = 1;
	int y_gamer = 1;

	Game(int r) {
		x_gamer = 1;
		y_gamer = 1;
		for (int i = 0; i < 100; i++) {
			q[i] = Quad(i % 10 + 1, i / 10 + 1);
		}
		number_all();
	}


	Game() {
		for (int i = 0; i < 100; i++) {
			q[i] = Quad(i % 10 + 1, i / 10 + 1);
		}

		int x = 20;
		for (int i = 0; i < 100; i++) {
			if (x == 0) {
				break;
			}
			srand(clock()*i * 149);
			if (int(rand()) % 2 == 0 && rand() % 3 == 0 && q[i].x != x_gamer &&q[i].y != y_gamer) {
				q[i].bomba = 1;
				x--;
			}
		}
		number_all();
	}

	void show_game() {
		for (int i = 0; i < 100; i++) {
			q[i].show_quad();
			if (q[i].sost == 1 && q[i].number != 0) {
				//cout << "\a";
				glColor3d(1, 0, 0);
				sprintf(f, "%d", q[i].number);
				renderStrokeFontString(q[i].x - 5.2, q[i].y - 5.2, 0.11, f, 0.004);
			}
		}

		glBegin(GL_QUADS);
		glColor3d(1, 0, 0);
		glVertex3d(x_gamer - 5 - 0.3, y_gamer - 5 - 0.3, 0.11);
		glVertex3d(x_gamer - 5 - 0.3, y_gamer - 5 + 0.3, 0.11);
		glVertex3d(x_gamer - 5 + 0.3, y_gamer - 5 + 0.3, 0.11);
		glVertex3d(x_gamer - 5 + 0.3, y_gamer - 5 - 0.3, 0.11);
		glEnd();
	}

	int quad_in_cell_number(int x, int y) {
		if (x >= 1 && y >= 1 && x <= 10 && y <= 10) {
			for (int i = 0; i < 100; i++) {
				if (q[i].x == x && q[i].y == y) {
					if (q[i].bomba == 0) {
						return i;
					}
					else {
						return -1;
					}
				}
			}
		}
		else {
			return -1;
		}
	}

	int quad_in_cell(int x, int y) {
		if (x >= 1 && y >= 1 && x <= 10 && y <= 10) {
			for (int i = 0; i < 100; i++) {
				if (q[i].x == x && q[i].y == y) {
					if (q[i].bomba == 1) {
						return 1;
					}
					return 0;
				}
			}
		}
		else {
			return 0;
		}
	}

	void press(int i) {
		q[i].number += quad_in_cell(q[i].x - 1, q[i].y - 1);
		q[i].number += quad_in_cell(q[i].x - 1, q[i].y);
		q[i].number += quad_in_cell(q[i].x - 1, q[i].y + 1);
		q[i].number += quad_in_cell(q[i].x, q[i].y + 1);
		q[i].number += quad_in_cell(q[i].x, q[i].y - 1);
		q[i].number += quad_in_cell(q[i].x + 1, q[i].y - 1);
		q[i].number += quad_in_cell(q[i].x + 1, q[i].y);
		q[i].number += quad_in_cell(q[i].x + 1, q[i].y + 1);
	}

	void number_all() {
		for (int i = 0; i < 100; i++) {
			press(i);
		}
	}

	void open_cell(int num) {
		if (q[num].bomba == 1) {
			active_game = 0;
			active_win = -1;
		}
		else {
			if (q[num].number != 0) {
				q[num].sost = 1;
			}
			else {
				q[num].sost = 1;
				int value;

				value = quad_in_cell_number(q[num].x - 1, q[num].y - 1);
				if (value != -1 && q[value].sost == 0) { open_cell(value); }

				value = quad_in_cell_number(q[num].x - 1, q[num].y);
				if (value != -1 && q[value].sost == 0) { open_cell(value); }

				value = quad_in_cell_number(q[num].x - 1, q[num].y + 1);
				if (value != -1 && q[value].sost == 0) { open_cell(value); }

				value = quad_in_cell_number(q[num].x, q[num].y + 1);
				if (value != -1 && q[value].sost == 0) { open_cell(value); }

				value = quad_in_cell_number(q[num].x, q[num].y - 1);
				if (value != -1 && q[value].sost == 0) { open_cell(value); }

				value = quad_in_cell_number(q[num].x + 1, q[num].y - 1);
				if (value != -1 && q[value].sost == 0) { open_cell(value); }

				value = quad_in_cell_number(q[num].x + 1, q[num].y + 1);
				if (value != -1 && q[value].sost == 0) { open_cell(value); }

				value = quad_in_cell_number(q[num].x + 1, q[num].y);
				if (value != -1 && q[value].sost == 0) { open_cell(value); }

			}
		}
	}

	void open_cell(int x, int y) {

		if (x >= 1 && x <= 10 && y >= 1 && y <= 10) {
			int num;
			for (int i = 0; i < 100; i++) {
				if (q[i].x == x &&q[i].y == y) {
					num = i;
					break;
				}
			}
			if (q[num].take_bomba == 0) {

				if (q[num].bomba == 1) {
					active_game = 0;
					active_win = -1;
				}
				else {
					if (q[num].sost == 0) {
						if (q[num].number != 0) {
							q[num].sost = 1;
						}
						else {
							q[num].sost = 1;
							int value;

							value = quad_in_cell_number(q[num].x - 1, q[num].y - 1);
							if (value != -1 && q[value].sost == 0) { open_cell(value); }

							value = quad_in_cell_number(q[num].x - 1, q[num].y);
							if (value != -1 && q[value].sost == 0) { open_cell(value); }

							value = quad_in_cell_number(q[num].x - 1, q[num].y + 1);
							if (value != -1 && q[value].sost == 0) { open_cell(value); }

							value = quad_in_cell_number(q[num].x, q[num].y + 1);
							if (value != -1 && q[value].sost == 0) { open_cell(value); }

							value = quad_in_cell_number(q[num].x, q[num].y - 1);
							if (value != -1 && q[value].sost == 0) { open_cell(value); }

							value = quad_in_cell_number(q[num].x + 1, q[num].y - 1);
							if (value != -1 && q[value].sost == 0) { open_cell(value); }

							value = quad_in_cell_number(q[num].x + 1, q[num].y + 1);
							if (value != -1 && q[value].sost == 0) { open_cell(value); }

							value = quad_in_cell_number(q[num].x + 1, q[num].y);
							if (value != -1 && q[value].sost == 0) { open_cell(value); }

						}
					}
				}
			}
			int open_cell = 0;
			for (int i = 0; i < 100; i++) {
				if (q[i].sost == 1 || q[i].bomba == 1) {
					++open_cell;
				}
			}
			if (open_cell == 100) {
				active_game = 0;
				active_win = 1;
			}
		}
	}

	void save_game() {
		std::ofstream f;

		f.open("text.txt", std::ios::out);


		if (f.is_open()) {
			f << x_gamer << " ";
			f << y_gamer << " ";
			for (int i = 0; i < 100; i++) {

				f << q[i].x << " ";
				f << q[i].y << " ";
				f << q[i].x_d << " ";
				f << q[i].y_d << " ";


				f << q[i].bomba << " ";
				f << q[i].sost << " ";

				f << q[i].number << " ";

				f << q[i].take_bomba << " ";
			}
		}

		f.close();
	}

	void take_cell(int x, int y) {
		for (int i = 0; i < 100; i++) {
			if (q[i].x == x && q[i].y == y) {
				if (q[i].sost == 0) {
					if (q[i].take_bomba == 0) { q[i].take_bomba = 1; }
					else { q[i].take_bomba = 0; }
				}
			}
		}
	}

	

	void load_game() {
		std::ifstream f;

		f.open("text.txt");



		if (f.is_open()) {
			f >> x_gamer;
			f >> y_gamer;
			for (int i = 0; i < 100; i++) {

				f >> q[i].x;
				f >> q[i].y;
				f >> q[i].x_d;
				f >> q[i].y_d;


				f >> q[i].bomba;
				f >> q[i].sost;

				f >> q[i].number;

				f >> q[i].take_bomba;
			}
		}

		f.close();
	}

}game(0);

class Menu {
public:
	Button games, loading, exit;
	int active;

	Menu::Menu() {
		active = 1;
		games = Button(1, -2, 4, 2, 5, "  Game", 1);
		loading = Button(1, -2, 1, 2, 2, "  Loading", 1);
		exit = Button(1, -2, -2, 2, -1, "  Exit", 1);
	}

	void Menu::show_menu() {
		glColor3d(0.3, 0.9, 0.6);


		glBegin(GL_QUADS);
		glVertex3d(-30, -30, 0);
		glVertex3d(-30, 30, 0);
		glVertex3d(30, 30, 0);
		glVertex3d(30, -30, 0);
		glEnd();


		glColor3d(1, 0, 0);

		games.show_button();
		loading.show_button();
		exit.show_button();

	}

	void prov_buttons(int x, int y, int w, int h) {
		double xx = double(x);
		double yy = double(y);

		//std::cout << games.active << "   " << setings.active << "   " << helps.active << "   " << exid.active << "   \n";


		//std::cout<<"   "<< double(xx / w) <<  "  "  << double(yy / h) << "\n";


		if (double(xx / w) >= 0.43411 && double(xx / w) <= 0.56515 && double(yy / h) >= 0.20963 && double(yy / h) <= 0.26953) { games.active = 1; }
		else { games.active = 0; }

		if (double(xx / w) >= 0.43411 && double(xx / w) <= 0.56515 && double(yy / h) >= 0.38411 && double(yy / h) <= 0.44270) { loading.active = 1; }
		else { loading.active = 0; }

		if (double(xx / w) >= 0.43411 && double(xx / w) <= 0.56515 && double(yy / h) >= 0.55859 && double(yy / h) <= 0.61458) { exit.active = 1; }
		else { exit.active = 0; }



	}

	void pressure() {

		if (games.active == 1) { active = 0; game = Game(); active_menu = 0; active_game = 1; }
		if (loading.active == 1) { active = 0; game = Game(); active_menu = 0; active_game = 1; game.load_game(); }
	}
}menu;

void on_paint()
{


	glViewport(0, 0, width, height);

	glClearColor(0.3, 0.9, 0.7, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, (GLfloat)width / height, 1, 100);// задаємо усічений конус видимості

	glMatrixMode(GL_MODELVIEW);// включаємо режим роботи з видовою матрицею
	glLoadIdentity();

	glTranslatef(0, 0, distZ);  // камера з початку координат зсувається на distZ, 


								/////////////////////////////////////////

	if (active_menu == 1) {
		menu.show_menu();
	}

	/////////////////////////////////////////

	glRotatef(angleX, 0.0f, 1.0f, 0.0f);  // потім повертається по осі Oy
	glRotatef(angleY, 1.0f, 0.0f, 0.0f);  // потім повертається по осі Ox

	glEnable(GL_DEPTH_TEST);  // включаємо буфер глибини

							  ////////////////////////////////////////    Loading !!!

	glPushMatrix();

	if (active_game == 1) {
		game.show_game();
	}

	if (active_win == -1) {
		renderStrokeFontString(0, 0, 0, "YOU LOSE", 0.006);
	}

	if (active_win == 1) {
		renderStrokeFontString(0, 0, 0, "YOU WIN", 0.006);
	}



	glPopMatrix();
	////////////////////////////////////////


	glFlush();
	glutSwapBuffers(); // перемикання буферів
}

void on_keyboard(unsigned char key, int x, int y) //обробка події від клавіатури
{
	std::cout << int(key) << "\n";
	switch (key) {

	case 27: if (active_menu == 1) { exit(0); }if (active_game == 1 || active_win != 0) { active_game = 0; active_menu = 1; active_win = 0; }break;

	case 97:if (active_game == 1)if (game.x_gamer >= 2)game.x_gamer--; break;
	case 119:if (active_game == 1)if (game.y_gamer <= 9)game.y_gamer++; break;
	case 100:if (active_game == 1)if (game.x_gamer <= 9)game.x_gamer++; break;
	case 115:if (active_game == 1)if (game.y_gamer >= 2)game.y_gamer--; break;

	case 13:
		if (active_game == 1) {
			game.open_cell(game.x_gamer, game.y_gamer);
		}break;

	case  32:if (active_game == 1) { game.take_cell(game.x_gamer, game.y_gamer); }break;

	case 112:if (active_game == 1) { game.save_game(); }break;
	}

}

void on_motion(int x, int y)
{
	//	std::cout << angleX<<"    "<<angleY<<"\n";

	switch (button) {
	case 0:
		angleX += x - mouseX;
		angleY += y - mouseY;
		while (angleX >= 360) { angleX -= 360; }
		while (angleY >= 360) { angleY -= 360; }
		while (angleX <= -360) { angleX += 360; }
		while (angleY <= -360) { angleY += 360; }
		mouseX = x;
		mouseY = y;

		break;
	}


}

void on_mouse(int _button, int state, int x, int y) {

	if (state == 1) {
		kn = 0;
		button = -1;
		return;
	}
	else {
		if (active_menu == 1) {
			if (menu.exit.active == 1) { exit(0); }
			menu.pressure();
		}
		else {
			switch (button = _button) {
			case 0: mouseX = x; mouseY = y; break;
			}
		}
	}



}

void on_mouse_passive(int x, int y) {

	if (active_menu == 1) {
		menu.prov_buttons(x, y, width, height);
	}

}

void on_size(int w, int h)
{
	width = w;
	height = h;
	if (height == 0) height = 1;
}

void on_timer(int value)
{
	on_paint();                     // перемалюємо екран
	glutTimerFunc(3, on_timer, 0); // через 5мс викличеться ця функція
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	game.number_all();
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Chess");
	glutDisplayFunc(on_paint);
	glutReshapeFunc(on_size);
	glutKeyboardFunc(on_keyboard);
	glutMotionFunc(on_motion);
	glutMouseFunc(on_mouse);
	glutPassiveMotionFunc(on_mouse_passive);
	glutFullScreen();
	glutTimerFunc(3, on_timer, 0);

	glutMainLoop();
}
