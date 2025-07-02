#define _CRT_SECURE_NO_WARNINGS

#include "Camera.h"
#define TO_RADIAN 0.01745329252f  
#define TO_DEGREE 57.295779513f

/*****/
enum axes { X_AXIS, Y_AXIS, Z_AXIS };
static int flag_translation_axis;
#define CAM_TSPEED 0.05f

glm::mat3 R33_t;
glm::mat4 T;
glm::vec3 pos, target;
/*****/

static constexpr float MIN_FOVY = 5.0f * TO_RADIAN;
static constexpr float MAX_FOVY = 90.0f * TO_RADIAN;

void Perspective_Camera::define_camera(int win_width, int win_height, float win_aspect_ratio) {
	switch (camera_id) {
	case CAMERA_MAIN:
		flag_valid = true;
		flag_move = true; // yes. the main camera is permitted to move

		// let's use glm funtions to set up the initial camera pose
		ViewMatrix = glm::lookAt(glm::vec3(-600.0f, -600.0f, 400.0f), glm::vec3(125.0f, 80.0f, 25.0f),
			glm::vec3(0.0f, 0.0f, 1.0f)); // initial pose for main camera
		cam_view.uaxis = glm::vec3(ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
		cam_view.vaxis = glm::vec3(ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);
		cam_view.naxis = glm::vec3(ViewMatrix[0][2], ViewMatrix[1][2], ViewMatrix[2][2]);
		R33_t = glm::transpose(glm::mat3(ViewMatrix));
		T = glm::mat4(R33_t) * ViewMatrix;
		cam_view.pos = -glm::vec3(T[3][0], T[3][1], T[3][2]); // why does this work?

		cam_proj.projection_type = CAMERA_PROJECTION_PERSPECTIVE;
		cam_proj.params.pers.fovy = 15.0f * TO_RADIAN;
		cam_proj.params.pers.aspect = win_aspect_ratio;  
		cam_proj.params.pers.n = 1.0f;
		cam_proj.params.pers.f = 50000.0f;

		ProjectionMatrix = glm::perspective(cam_proj.params.pers.fovy, cam_proj.params.pers.aspect,
			cam_proj.params.pers.n, cam_proj.params.pers.f);
		view_port.x = 300; view_port.y = 200; view_port.w = win_width - 200; view_port.h = win_height - 200;
		break;
	case CAMERA_CC_0:
		flag_valid = true;
		flag_move = false;

		pos = glm::vec3(20.0f, 150.0f, 50.0f);
		target = glm::vec3(70.0f, 120.0f, 20.0f);
		ViewMatrix = glm::lookAt(pos, target, glm::vec3(0, 0, 1));

		cam_proj.projection_type = CAMERA_PROJECTION_PERSPECTIVE;
		cam_proj.params.pers.fovy = 30.0f * TO_RADIAN;
		cam_proj.params.pers.aspect = win_aspect_ratio;
		cam_proj.params.pers.n = 1.0f;
		cam_proj.params.pers.f = 500.0f;
		ProjectionMatrix = glm::perspective( cam_proj.params.pers.fovy, cam_proj.params.pers.aspect,
			cam_proj.params.pers.n, cam_proj.params.pers.f
		);
		// ����Ʈ�� ���߿� display() �ʿ��� override
		break;
	case CAMERA_CC_1:
		flag_valid = true;
		flag_move = false;

		pos = glm::vec3(150.0f, 50.0f, 50.0f);
		target = glm::vec3(10.0f, 10.0f, 20.0f);
		ViewMatrix = glm::lookAt(pos, target, glm::vec3(0, 0, 1));

		cam_proj.projection_type = CAMERA_PROJECTION_PERSPECTIVE;
		cam_proj.params.pers.fovy = 30.0f * TO_RADIAN;
		cam_proj.params.pers.aspect = win_aspect_ratio;
		cam_proj.params.pers.n = 1.0f;
		cam_proj.params.pers.f = 500.0f;
		ProjectionMatrix = glm::perspective(cam_proj.params.pers.fovy, cam_proj.params.pers.aspect,
			cam_proj.params.pers.n, cam_proj.params.pers.f
		);
		// ����Ʈ�� ���߿� display() �ʿ��� override
		break;
	case CAMERA_CC_2:
		flag_valid = true;
		flag_move = false;

		pos = glm::vec3(200.0f, 130.0f, 50.0f);
		target = glm::vec3(220.0f, 100.0f, 20.0f);
		ViewMatrix = glm::lookAt(pos, target, glm::vec3(0, 0, 1));
		// u/v/n�� �̾Ƴ��⡦
		// (���ΰ� ���� ������� cam_view.uaxis/vaxis/naxis, cam_view.pos ����)

		cam_proj.projection_type = CAMERA_PROJECTION_PERSPECTIVE;
		cam_proj.params.pers.fovy = 30.0f * TO_RADIAN;
		cam_proj.params.pers.aspect = win_aspect_ratio;
		cam_proj.params.pers.n = 1.0f;
		cam_proj.params.pers.f = 500.0f;
		ProjectionMatrix = glm::perspective(cam_proj.params.pers.fovy, cam_proj.params.pers.aspect,
			cam_proj.params.pers.n, cam_proj.params.pers.f
		);
		// ����Ʈ�� ���߿� display() �ʿ��� override
		break;
	case CAMERA_CC_MOVE:
		flag_valid = true;
		flag_move = true;

		pos = glm::vec3(150.0f, 100.0f, 100.0f);
		target = glm::vec3(150.0f, 0.0f, 0.0f);
		ViewMatrix = glm::lookAt(pos, target, glm::vec3(0, 0, 1));
		
		cam_view.uaxis = glm::vec3(ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
		cam_view.vaxis = glm::vec3(ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);
		cam_view.naxis = glm::vec3(ViewMatrix[0][2], ViewMatrix[1][2], ViewMatrix[2][2]);
		R33_t = glm::transpose(glm::mat3(ViewMatrix));
		T = glm::mat4(R33_t) * ViewMatrix;
		cam_view.pos = -glm::vec3(T[3][0], T[3][1], T[3][2]); // why does this work?

		cam_proj.projection_type = CAMERA_PROJECTION_PERSPECTIVE;
		cam_proj.params.pers.fovy = 30.0f * TO_RADIAN;
		cam_proj.params.pers.aspect = win_aspect_ratio;
		cam_proj.params.pers.n = 1.0f;
		cam_proj.params.pers.f = 500.0f;
		ProjectionMatrix = glm::perspective(cam_proj.params.pers.fovy, cam_proj.params.pers.aspect,
			cam_proj.params.pers.n, cam_proj.params.pers.f
		);
		// ����Ʈ�� ���߿� display() �ʿ��� override
		break;
	}
}

void Perspective_Camera::zoom(float deltaFovy) {
	float newFovy = cam_proj.params.pers.fovy + deltaFovy;
	if (newFovy < MIN_FOVY) newFovy = MIN_FOVY;
	if (newFovy > MAX_FOVY) newFovy = MAX_FOVY;

	cam_proj.params.pers.fovy = newFovy;
	ProjectionMatrix = glm::perspective(
		newFovy,
		cam_proj.params.pers.aspect,
		cam_proj.params.pers.n,
		cam_proj.params.pers.f
	);
}

void Perspective_Camera::rotateLocal(float pitch, float yaw, float /*roll*/) {
	// 1) ��ġ(pitch) : ���� ����(uaxis)�� ������
	glm::mat4 R = glm::rotate(glm::mat4(1.0f), pitch, cam_view.uaxis);
	// 2) ��(�¿�) ȸ��(yaw) : ���� ����(vaxis)�� ������
	R = glm::rotate(R, yaw, cam_view.vaxis);

	// 3) ���� ������(naxis) ȸ�� ����
	cam_view.naxis = glm::mat3(R) * cam_view.naxis;

	// 4) u, v�� ���� (���� ����)
	cam_view.uaxis = glm::normalize(glm::cross(cam_view.vaxis, cam_view.naxis));
	cam_view.vaxis = glm::normalize(glm::cross(cam_view.naxis, cam_view.uaxis));

	// 5) �� ��Ʈ���� ������Ʈ
	ViewMatrix = glm::lookAt(
		cam_view.pos,
		cam_view.pos - cam_view.naxis,
		cam_view.vaxis
	);

	flag_valid = true;
}

void Perspective_Camera::rotateWorld(float pitch, float yaw, float roll) {
	// ���� �� ����
	glm::vec3 worldX = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 worldY = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 worldZ = glm::vec3(0.0f, 0.0f, 1.0f);

	// 1) ���� X��(pitch) ȸ�� ��� ����
	glm::mat4 R = glm::rotate(glm::mat4(1.0f), pitch, worldX);

	// 2) ���� Y��(yaw) ȸ�� ��� ���ϱ�
	R = glm::rotate(R, yaw, worldY);

	// 3) ���� Z��(roll) ȸ�� ��� ���ϱ�
	R = glm::rotate(R, roll, worldZ);

	// 4) ī�޶� ���� ��鿡 ȸ�� ��� ����
	cam_view.uaxis = glm::mat3(R) * cam_view.uaxis;
	cam_view.vaxis = glm::mat3(R) * cam_view.vaxis;
	cam_view.naxis = glm::mat3(R) * cam_view.naxis;

	// 5) ���� ����ȭ (������ ����)
	cam_view.uaxis = glm::normalize(cam_view.uaxis);
	cam_view.vaxis = glm::normalize(cam_view.vaxis);
	cam_view.naxis = glm::normalize(cam_view.naxis);

	// 6) �� ��Ʈ���� ������Ʈ
	ViewMatrix = glm::lookAt(
		cam_view.pos,
		cam_view.pos - cam_view.naxis,
		cam_view.vaxis
	);

	flag_valid = true;
}

void Perspective_Camera::toggleUp(int toggle) {
	glm::vec3 up_vector;
	switch (toggle) {
		case 0:
			up_vector = glm::vec3 (0, 0, 1);
			break;
		case 1:
			up_vector = glm::vec3(0, 1, 0);
			break;
		case 2:
			up_vector = glm::vec3(1, 0, 0);
			break;
	}

	if (camera_id == CAMERA_MAIN || camera_id == CAMERA_CC_MOVE) {
		// ���� ī�޶� ��ġ�� Ÿ���� ������� ���� (�ʿ��ϸ� �����صα�)
		glm::vec3 eye = cam_view.pos;
		glm::vec3 center = cam_view.pos - cam_view.naxis; // ���� ���� ���� Ÿ��

		ViewMatrix = glm::lookAt(eye, center, up_vector);

		cam_view.uaxis = glm::vec3(ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
		cam_view.vaxis = glm::vec3(ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);
		cam_view.naxis = glm::vec3(ViewMatrix[0][2], ViewMatrix[1][2], ViewMatrix[2][2]);

		R33_t = glm::transpose(glm::mat3(ViewMatrix));
		T = glm::mat4(R33_t) * ViewMatrix;
		cam_view.pos = -glm::vec3(T[3][0], T[3][1], T[3][2]);

		flag_valid = true;
	}
}

void Orthographic_Camera::define_camera(int win_width, int win_height, float win_aspect_ratio) {
	flag_valid = true;
	flag_move = false;

	glm::vec3 pos, target, up;
	float view_size;

	switch (camera_id) {
	case ORTH_FRONT:  // ���鵵
		pos = glm::vec3(120.0f, 85.0f, 200.0f);
		target = glm::vec3(120.0f, 85.0f, 0.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		view_size = 150.0f;
		break;
	case ORTH_SIDE: // ���鵵
		pos = glm::vec3(200.0f, 85.0f, 0.0f);
		target = glm::vec3(0.0f, 85.0f, 0.0f);
		up = glm::vec3(0.0f, 0.0f, 1.0f);
		view_size = 100.0f;
		break;
	case ORTH_TOP: // ��鵵
		pos = glm::vec3(120.0f, 200.0f, 0.0f);
		target = glm::vec3(120.0f, 0.0f, 0.0f);
		up = glm::vec3(0.0f, 0.0f, 1.0f);
		view_size = 100.0f;
		break;
	}

	ViewMatrix = glm::lookAt(pos, target, up);

	float left = -view_size * win_aspect_ratio;
	float right = view_size * win_aspect_ratio;
	float bottom = -view_size;
	float top = view_size;

	cam_proj.projection_type = CAMERA_PROJECTION_ORTHOGRAPHIC;
	cam_proj.params.ortho.left = left;
	cam_proj.params.ortho.right = right;
	cam_proj.params.ortho.bottom = bottom;
	cam_proj.params.ortho.n = 0.1f;
	cam_proj.params.ortho.f = 500.0f;

	ProjectionMatrix = glm::ortho(left, right, bottom, top, cam_proj.params.ortho.n, cam_proj.params.ortho.f);
	// ����Ʈ�� ���߿� display() �ʿ��� override
}
