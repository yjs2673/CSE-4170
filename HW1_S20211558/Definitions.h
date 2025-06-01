#pragma once

#define BACKGROUND_COLOR  159.0f / 255.0f, 226.0f / 255.0f, 191.0f / 255.0f
#define POINT_COLOR  0.0f, 0.0f, 1.0f
#define LINE_COLOR  1.0f, 0.0f, 0.0f
#define CENTER_POINT_COLOR 1.0f, 1.0f, 0.0f
//*****
#define CENTER_POINT_COLOR_ROTATE 1.0f, 0.0f, 1.0f
#define MOVE_COLOR 0.0f, 0.0f, 0.0f
//*****

#define ROTATION_STEP 100 // ms
#define TRANSLATION_OFFSET 0.05f

#define COS_5_DEGREES 0.9961947f
#define SIN_5_DEGREES 0.08715574f

typedef struct {
	int width, height;
	int initial_anchor_x, initial_anchor_y;
} Window;

typedef struct {
	int rightbuttonpressed;
	int leftbuttonpressed;
	int rotation_mode;
	int polygon_mode;
	int polygon_finished; //*****
	int move_mode; // *****
} Status;

#define MAX_POSITIONS 256
typedef struct {
	float point[MAX_POSITIONS][2];
	int n_points;
	float center_x, center_y;
} My_Polygon;

// Functions for My_Polygon
void add_point(My_Polygon* pg, Window* wd, int x, int y);
void close_line_segments(My_Polygon* pg);
void draw_lines_by_points(My_Polygon* pg, Status* st); //***** st ���� �߰�
void update_center_of_gravity(My_Polygon* pg);
void move_points(My_Polygon* pg, float del_x, float del_y);
void rotate_points_around_center_of_grivity(My_Polygon* pg);
void resize_points(My_Polygon* pg, int dir); //***** ������ ũ�� ���� �Լ�
