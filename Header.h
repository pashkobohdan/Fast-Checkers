// play Fast-Checkers

#include <glut.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <windows.h>

//karina.v.melnyk@gmail.com - Карина Владимировна

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void renderStrokeFontString(float x, float y, float z, char *string, double k);
void renderText(char *string, float x, float y);
void renderText(char *string);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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

	Button(int off_on, double x1, double y1, double x2, double y2, char *string, int length);
	Button();
	void show_button();
};

class Chec {
public:
	int x;
	int y;
	int white_black;
	int need_of_turn;
	int take;
	int active;
	int color;
	double plus_z;
	int active_sinn;

	double x_d;
	double y_d;


	Chec() {}
	Chec(int xx, int yy, int wb, int color);
	void show();
};

class Game_end {
public:
	Button exit_to_menu;
	int active;
	int winner;

	Game_end();
	void show_end();
	void prov_buttons(int x, int y, int w, int h);
	void pressure();
};

class Game_checker {
public:
	Chec f[24];
	Game_end end;

	int end_exit;
	int game_end;
	int gamer_win;
	int turn;
	int figure_work;
	int delete_figure;
	int vector_turn;
	int xx, yy;
	int x_hod, y_hod;
	int gamer1_point;
	int gamer2_point;
	int color;
	int type_of_games;
	double sinn;

	Game_checker() {}
	Game_checker(int color);

	void initi();
	void show_board();
	void show_games();

	int figure_in_coordinate(int x, int y);
	int availability_figure(int x, int y);       //  есть ли фигура
	int need_turn(int i);						  //  нужно ли ходить
	int ability_turn(int i);					  //  есть ли ход
	void selection_new_figure();				  //  выбор новвой фигуры

	void selection_left();         // выбор влево 
	void selection_up();			// вверх
	void selection_right();			// вправо
	void selection_down();			// вниз

	void turn_of_gamers(int left_right);

	void output_points();
};

class Loading {
	double progress_loading;
	double x;
public:
	int active;
	Loading();
	void show_loading();
};

class Menu {
public:
	Button games, setings, helps, exid, cheker, poddavki, four_four, exit_yes, exit_no,
		rules1, rules2, rules3, color_black, color_dark, color_blue, fps_off, fps_on,
		time_off, time_on, vsync60, vsync120, down1, down2, down3;
	int active;

	int color_of_figure;
	int fps;
	int time;
	double vsync;
	int type;

	int change_angle;

	Menu();
	void show_menu();
	void prov_buttons(int x, int y, int w, int h);
	void pressure();
};

class Pause {
public:
	Button file1, file2, file3, exit_to_menu, resume;
	int active;

	Pause();
	void show_pause();
	void prov_buttons(int x, int y, int w, int h);
};

class Game {
public:
	Menu menu;
	Loading loading;
	Game_checker game1;
	Pause pause;

	int kn = 0;
	int x_w;
	int y_w;
	int          width, height;
	int          button = -1;
	float        angleX = 0, angleY = -30;
	float        mouseX, mouseY;
	float        distZ = -15;
	double param_x;
	double param_y;

	int loading_active;
	int menu_active;
	int pause_active;
	int game_active;

	int moving_of_camera;
	double moving_x_white, moving_y_white, moving_x_black, moving_y_black;
	int counter_moving;

	int type_of_game;

	int first_loading;

	int first_end;

	int r_time;
	int frames;
	int r_fps;
	char f[10];

	Game();

	void show_game();
	void moving_camera();

	void record_data(int n);
	void read_data(int n);

	void fps_time_game();
	void on_paint();
	void on_keyboard(unsigned char key, int x, int y);
	void on_motion(int x, int y);
	void on_mouse(int _button, int state, int x, int y);
	void on_mouse_passive(int x, int y);
	void on_size(int w, int h);
};
