#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Definitions.h"

void add_point(My_Polygon *pg, Window *wd, int x, int y) {
	pg->point[pg->n_points][0] = 2.0f * ((float)x) / wd->width - 1.0f;
	pg->point[pg->n_points][1] = 2.0f * ((float)wd->height - y) / wd->height - 1.0f;
	pg->n_points++; 
}

void close_line_segments(My_Polygon *pg) {
	pg->point[pg->n_points][0] = pg->point[0][0];
	pg->point[pg->n_points][1] = pg->point[0][1];
	pg->n_points++;
}

void draw_lines_by_points(My_Polygon* pg, Status* st) { //***** MOVE�� ���� �߰�
	glColor3f(POINT_COLOR);
	for (int i = 0; i < pg->n_points; i++) {
		glBegin(GL_POINTS);
		glVertex2f(pg->point[i][0], pg->point[i][1]);
		glEnd();
	}
	if (st->leftbuttonpressed == 0) glColor3f(LINE_COLOR);
	else glColor3f(MOVE_COLOR); //***** MOVE�� ���� �� ����
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < pg->n_points; i++)
		glVertex2f(pg->point[i][0], pg->point[i][1]);
	glEnd();
}

void update_center_of_gravity(My_Polygon* pg) {
	pg->center_x = pg->center_y = 0.0f;
	if (pg->n_points == 0) return;
	for (int i = 0; i < pg->n_points; i++) {
		pg->center_x += pg->point[i][0], pg->center_y += pg->point[i][1];
	}
	pg->center_x /= (float)pg->n_points, pg->center_y /= (float)pg->n_points;
}

void move_points(My_Polygon* pg, float del_x, float del_y) {
	
	for (int i = 0; i < pg->n_points; i++) {
		pg->point[i][0] += del_x, pg->point[i][1] += del_y;
	}
}

void rotate_points_around_center_of_grivity(My_Polygon* pg) {
	for (int i = 0; i < pg->n_points; i++) {
		float x, y;
		x = COS_5_DEGREES * (pg->point[i][0] - pg->center_x)
			- SIN_5_DEGREES * (pg->point[i][1] - pg->center_y) + pg->center_x;
		y = SIN_5_DEGREES * (pg->point[i][0] - pg->center_x)
			+ COS_5_DEGREES * (pg->point[i][1] - pg->center_y) + pg->center_y;
		pg->point[i][0] = x, pg->point[i][1] = y;
	}
}

//***** ������ ũ�� ���� �Լ�
void resize_points(My_Polygon* pg, int dir) {
	if (dir < 0) { // ���� �÷��� ��� (���) -> ��ǥ ũ�� ����
		for (int i = 0; i < pg->n_points; i++) {
			pg->point[i][0] = ((pg->point[i][0] - pg->center_x) * 0.99) + pg->center_x;
			pg->point[i][1] = ((pg->point[i][1] - pg->center_y) * 0.99) + pg->center_y;
		}
	}
	else { // ���� ������ ��� (Ȯ��) -> ��ǥ ũ�� ����
		for (int i = 0; i < pg->n_points; i++) {
			pg->point[i][0] = ((pg->point[i][0] - pg->center_x) * 1.01) + pg->center_x;
			pg->point[i][1] = ((pg->point[i][1] - pg->center_y) * 1.01) + pg->center_y;
		}
	}
}
//*****