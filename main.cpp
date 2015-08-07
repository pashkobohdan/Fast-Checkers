#include "Header.h"

int r_time = clock();
int frames = 0;
int r_fps = 0;
char f[10];

Game g;

void renderStrokeFontString(float x, float y, float z, char *string, double k) {

	char *c;

	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(k, k, k);
	for (c = string; *c != '\0'; c++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
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

void fps_time_game() {

	glColor3d(0, 0, 0.5);
	char *c;
	if (g.menu.fps == 1) {
		sprintf(f, "%d", r_fps);
		renderText("fps : ", -14.5, -8);
		renderText(f);
	}
	if (g.menu.time == 1) {
		renderText("min : ", 11, -8);
		sprintf(f, "%d", int(r_time / 60000));
		renderText(f);
		renderText("   sec : ");
		sprintf(f, "%d", int((r_time / 1000) % 60));
		renderText(f);
	}

	g.game1.output_points();
}

void on_paint()
{

	GLfloat light_ambient[4] = { 0.0f, 0.0f, 0.0f, 1.0f }, light_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f }, light_specular[4] = { 0.6, 0.6f, 0.6, 1.0f }, light_position[4] = { 0.6f, 0.6f, 1.2f, 0.0f };

	glViewport(0, 0, g.width, g.height);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glClearColor(0.3, 0.9, 0.7, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, (GLfloat)g.width / g.height, 1, 100);// задаємо усічений конус видимості

	glMatrixMode(GL_MODELVIEW);// включаємо режим роботи з видовою матрицею
	glLoadIdentity();

	glTranslatef(0, 0, g.distZ);  // камера з початку координат зсувається на distZ, 


	if (g.game_active == 1) {
		fps_time_game();
	}

	glRotatef(g.angleX, 0.0f, 1.0f, 0.0f);  // потім повертається по осі Oy
	glRotatef(g.angleY, 1.0f, 0.0f, 0.0f);  // потім повертається по осі Ox

	glEnable(GL_DEPTH_TEST);  // включаємо буфер глибини

							  ////////////////////////////////////////    Loading !!!

	if (g.loading_active == 1 || g.menu_active == 1 || g.game1.game_end == 1 || g.pause.active == 1) {
		g.show_game();
	}

	frames++;
	if (clock() - r_time >= 1000) {
		r_fps = frames;
		r_time = clock();
		frames = 0;
	}

	if (g.menu.active == 1) {
		if (g.menu.time == 1) {
			glColor3d(0, 0, 0.5);
			glLineWidth(1.5f);

			renderStrokeFontString(10, -7, 0.2, "min ", 0.004);
			sprintf(f, "%d", int(r_time / 60000));
			renderStrokeFontString(11, -7, 0.2, f, 0.005);

			renderStrokeFontString(12, -7, 0.2, "sec ", 0.004);
			sprintf(f, "%d", int((r_time / 1000) % 60));
			renderStrokeFontString(13, -7, 0.2, f, 0.005);
		}

		if (g.menu.fps == 1) {
			sprintf(f, "%d", r_fps);
			glColor3d(0, 0, 0.5);
			glLineWidth(1.5f);
			renderStrokeFontString(-13, -7, 0.2, f, 0.005);
		}
	}


	////////////////////////////////////////


	glEnable(GL_LIGHTING);   // включаємо режим для установки освітлення
	glEnable(GL_LIGHT0);     // додаємо джерело світла № 0 (їх може бути до 8), зараз він світить з "очей"

							 ////





	if (g.menu.active == 0 && g.loading_active == 0 && g.game1.game_end == 0 && g.pause.active == 0) {


		g.show_game();

	}


	////

	glDisable(GL_LIGHT0);// вимкнемо все, що включили
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glFlush();
	glutSwapBuffers(); // перемикання буферів
}

void on_keyboard(unsigned char key, int x, int y) //обробка події від клавіатури
{
	//std::cout << int(key) << "\n";
	switch (key) {

	case 13:if (g.menu.exid.active == 1) { exit(0); }break;

	case 27:if (g.menu.active == 1) { g.menu.games.take = 0; g.menu.setings.take = 0; g.menu.helps.take = 0; g.menu.exid.take = 1; g.menu.exid.take = 1; g.menu.games.take = 0; g.menu.setings.take = 0; g.menu.helps.take = 0; g.menu.rules1.take = 0; g.menu.rules2.take = 0; g.menu.rules3.take = 0; }
			if (g.game_active == 1 && g.menu.active == 0) { g.menu_active = 0; g.game_active = 0; g.menu.active = 0; g.pause.active = 1; g.angleX = 0; g.angleY = 0; }
			break;
	case 97: if (g.game1.turn == -1)g.game1.selection_left();   else { g.game1.selection_right(); } break;
	case 119:if (g.game1.turn == -1)g.game1.selection_up();     else { g.game1.selection_down(); } break;
	case 100:if (g.game1.turn == -1)g.game1.selection_right();  else { g.game1.selection_left(); } break;
	case 115:if (g.game1.turn == -1)g.game1.selection_down();   else { g.game1.selection_up(); }   break;

	case 244:if (g.game1.turn == -1)g.game1.selection_left();   else { g.game1.selection_right(); }break;
	case 246:if (g.game1.turn == -1)g.game1.selection_up();     else { g.game1.selection_down(); } break;
	case 226:if (g.game1.turn == -1)g.game1.selection_right();  else { g.game1.selection_left(); } break;
	case 251:if (g.game1.turn == -1)g.game1.selection_down();   else { g.game1.selection_up(); }   break;

	case 52:g.angleX += 3;
		while (g.angleX >= 360) { g.angleX -= 360; }
		while (g.angleY >= 360) { g.angleY -= 360; }
		while (g.angleX <= -360) { g.angleX += 360; }
		while (g.angleY <= -360) { g.angleY += 360; }break;

	case 54:g.angleX -= 3;
		while (g.angleX >= 360) { g.angleX -= 360; }
		while (g.angleY >= 360) { g.angleY -= 360; }
		while (g.angleX <= -360) { g.angleX += 360; }
		while (g.angleY <= -360) { g.angleY += 360; }break;

	case 56:if (g.angleX >= 90 && g.angleX <= 270)g.angleY -= 3; else g.angleY += 3;  break;
	case 50:if (g.angleX >= 90 && g.angleX <= 270)g.angleY += 3; else g.angleY -= 3; break;

	case 113: if ((g.game1.ability_turn(g.game1.figure_work) == 1) || (g.game1.ability_turn(g.game1.figure_work) == 2)) {
		g.game1.turn_of_gamers(-1);
		g.moving_of_camera = 1;
		g.counter_moving = 30;
		g.moving_x_white = (-180 - g.angleX) / 30; g.moving_y_white = (-150 - g.angleY) / 30;
		g.moving_x_black = (-g.angleX) / 30; g.moving_y_black = (-30 - g.angleY) / 30;
	}
			  break;
	case 101: if ((g.game1.ability_turn(g.game1.figure_work) == 1) || (g.game1.ability_turn(g.game1.figure_work) == 2)) {
		g.game1.turn_of_gamers(1);
		g.moving_of_camera = 1;
		g.counter_moving = 30;
		g.moving_x_white = (-180 - g.angleX) / 30; g.moving_y_white = (-150 - g.angleY) / 30;
		g.moving_x_black = (-g.angleX) / 30; g.moving_y_black = (-30 - g.angleY) / 30;
	}
			  break;

	case 233:if ((g.game1.ability_turn(g.game1.figure_work) == 1) || (g.game1.ability_turn(g.game1.figure_work) == 2)) {
		g.game1.turn_of_gamers(-1);
		g.moving_of_camera = 1;
		g.counter_moving = 30;
		g.moving_x_white = (-180 - g.angleX) / 30; g.moving_y_white = (-150 - g.angleY) / 30;
		g.moving_x_black = (-g.angleX) / 30; g.moving_y_black = (-30 - g.angleY) / 30;
	}
			 break;

	case 243: if ((g.game1.ability_turn(g.game1.figure_work) == 1) || (g.game1.ability_turn(g.game1.figure_work) == 2)) {
		g.game1.turn_of_gamers(1);
		g.moving_of_camera = 1;
		g.counter_moving = 30;
		g.moving_x_white = (-180 - g.angleX) / 30; g.moving_y_white = (-150 - g.angleY) / 30;
		g.moving_x_black = (-g.angleX) / 30; g.moving_y_black = (-30 - g.angleY) / 30;
	}
			  break;

	case 32:if (g.game_active == 1) {
		if (g.game1.turn == -1) {
			g.angleX = 0;
			g.angleY = -30;
		}
		else {
			g.angleX = -180;
			g.angleY = -150;
		}
	}break;

	}
}

void on_motion(int x, int y)
{
	//	std::cout << g.angleX<<"    "<<g.angleY<<"\n";

	if (g.loading_active < 1 && g.menu.active<1 && g.game1.game_end<1 && g.pause.active<1) {
		switch (g.button) {
		case 0:
			g.angleX += x - g.mouseX;
			g.angleY += y - g.mouseY;
			while (g.angleX >= 360) { g.angleX -= 360; }
			while (g.angleY >= 360) { g.angleY -= 360; }
			while (g.angleX <= -360) { g.angleX += 360; }
			while (g.angleY <= -360) { g.angleY += 360; }
			g.mouseX = x;
			g.mouseY = y;

			break;
		}
	}
	else {
		if (g.menu_active == 1 || g.game1.game_end == 1 || g.pause.active == 1) {
			g.angleX = -(10.0*x - 5.0*g.width) / g.width;
			g.angleY = -(10.0 * y - 5.0 * g.height) / g.height;

		}
	}

}

void on_mouse(int _button, int state, int x, int y)
{
	if (state == 1) {
		g.kn = 0;
		g.button = -1;
		return;
	}
	else {
		switch (g.button = _button) {
		case 0: g.mouseX = x; g.mouseY = y;
			if (g.menu_active == 1) { g.menu.pressure(); }
			if (g.game1.game_end == 1) { g.game1.end.pressure(); }
			if (g.menu.active == 1 && g.menu.games.take == 1) {
				if (g.menu.down1.active == 1 || g.menu.down2.active == 1 || g.menu.down3.active == 1) {
					g.menu.active = 0;
					g.menu_active = 0;
					g.game_active = 1;
					g.moving_of_camera = 1;
					g.counter_moving = 30;
					g.moving_x_white = (-180 - g.angleX) / 30; g.moving_y_white = (-150 - g.angleY) / 30;
					g.moving_x_black = (-g.angleX) / 30; g.moving_y_black = (-30 - g.angleY) / 30;

					if (g.menu.down1.active == 1) {
						g.read_data(1);
					}
					else {
						if (g.menu.down2.active == 1) {
							g.read_data(2);
						}
						else {
							if (g.menu.down3.active == 1) {
								g.read_data(3);
							}
						}
					}
				}
			}

			if (g.pause.active == 1) {
				if (g.pause.file1.active == 1) {
					g.record_data(1);
				}
				else {
					if (g.pause.file2.active == 1) { g.record_data(2); }
					else {
						if (g.pause.file3.active == 1) { g.record_data(3); }
					}
				}

				if (g.pause.exit_to_menu.active == 1) {
					g.menu_active = 1;
					g.menu.active = 1;
					g.pause.active = 0;
					g.game_active = 1;
				}

				if (g.pause.resume.active == 1) {
					g.pause.active = 0;
					g.game_active = 1;

					g.moving_of_camera = 1;
					g.counter_moving = 30;
					g.moving_x_white = (-180 - g.angleX) / 30; g.moving_y_white = (-150 - g.angleY) / 30;
					g.moving_x_black = (-g.angleX) / 30; g.moving_y_black = (-30 - g.angleY) / 30;
				}

			}

			break;
		}
	}

}

void on_mouse_passive(int x, int y) {

	if (g.menu_active == 1) {
		g.angleX = -(10.0*x - 5.0*g.width) / g.width;
		g.angleY = -(10.0 * y - 5.0 * g.height) / g.height;
		g.menu.prov_buttons(x, y, g.width, g.height);
	}
	else {
		if (g.game1.game_end == 1) {
			g.angleX = -(10.0*x - 5.0*g.width) / g.width;
			g.angleY = -(10.0 * y - 5.0 * g.height) / g.height;
			g.game1.end.prov_buttons(x, y, g.width, g.height);
		}
		else {
			if (g.pause.active == 1) {
				g.angleX = -(10.0*x - 5.0*g.width) / g.width;
				g.angleY = -(10.0 * y - 5.0 * g.height) / g.height;
				g.pause.prov_buttons(x, y, g.width, g.height);
			}
		}
	}
	//std::cout << g.width << "   " << g.height << "\n";

}

void on_size(int w, int h)
{
	g.width = w;
	g.height = h;
	if (g.height == 0) g.height = 1;
}

void on_timer(int value)
{
	on_paint();                     // перемалюємо екран
	glutTimerFunc(g.menu.vsync, on_timer, 0); // через 5мс викличеться ця функція
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	int full, x, y;

	std::ifstream s;
	s.open("setings\\resolution.ftr", std::ios::out);
	if (s.is_open()) {
		s >> full;
		s >> x;
		s >> y;
	}
	else {
		full = 1;
	}
	s.close();


	if (full == 0) { glutInitWindowSize(x, y); }
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Chess");
	glutDisplayFunc(on_paint);
	glutReshapeFunc(on_size);
	glutKeyboardFunc(on_keyboard);
	glutMotionFunc(on_motion);
	glutMouseFunc(on_mouse);
	glutPassiveMotionFunc(on_mouse_passive);
	if (full == 1) { glutFullScreen(); }
	glutTimerFunc(g.menu.vsync, on_timer, 0);

	glutMainLoop();
}
