#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

float speed = 0.0;
int open = 0, close = 0;
float transf = 29;
int x = 0, y = 0, z = 0;
int x2 = 0, y2 = 0, z2 = 0;
float speed2 = 0.1, speed3 = -0.1;
float sizeFrame = 40.0;
int e = 0;

float rotateAngle = 0.0f;
float viewDistance = -60.0;
float rotateY = 0.0f;

void sun();
void initTexture(LPCSTR dir);

// Texture
GLuint texture = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == 0x4F) //O key
		{
			open = 1;
		}
		else if (wParam == 0x43) //C key
		{
			close = 1;
		}
		else if (wParam == VK_UP) {
			viewDistance += 10.0f;
		}
		else if (wParam == VK_DOWN) {
			viewDistance -= 10.0f;
		}
		else if (wParam == VK_LEFT) {
			rotateY -= 10.0f;
		}
		else if (wParam == VK_RIGHT) {
			rotateY += 10.0f;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void initTexture(LPCSTR dir)
{
	glDisable(GL_TEXTURE_2D);
	glDeleteTextures(1, &texture);

	glEnable(GL_TEXTURE_2D);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		dir, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE); // First Param can change to bump.
	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	DeleteObject(hBMP);
}

void tower1() {
	initTexture("main.bmp");
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-6, 25, 3);
	glTexCoord2f(1, 0);
	glVertex3f(6, 25, 3);
	glTexCoord2f(0, 0);
	glVertex3f(6, 15, 3);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 15, 3);

	glTexCoord2f(1, 1);
	glVertex3f(-6, 15, 3);
	glTexCoord2f(1, 0);
	glVertex3f(-6, 15, -3);
	glTexCoord2f(0, 0);
	glVertex3f(6, 15, -3);
	glTexCoord2f(0, 1);
	glVertex3f(6, 15, 3);

	glTexCoord2f(1, 1);
	glVertex3f(6, 15, 3);
	glTexCoord2f(1, 0);
	glVertex3f(6, 15, -3);
	glTexCoord2f(0, 0);
	glVertex3f(6, 25, -3);
	glTexCoord2f(0, 1);
	glVertex3f(6, 25, 3);

	glTexCoord2f(1, 1);
	glVertex3f(6, 25, 3);
	glTexCoord2f(1, 0);
	glVertex3f(6, 25, -3);
	glTexCoord2f(0, 0);
	glVertex3f(-6, 25, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 25, 3);

	glTexCoord2f(1, 1);
	glVertex3f(-6, 25, 3);
	glTexCoord2f(1, 0);
	glVertex3f(-6, 15, 3);
	glTexCoord2f(0, 0);
	glVertex3f(-6, 15, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 25, -3);

	glTexCoord2f(1, 1);
	glVertex3f(-6, 25, -3);
	glTexCoord2f(1, 0);
	glVertex3f(6, 25, -3);
	glTexCoord2f(0, 0);
	glVertex3f(6, 15, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 15, -3);
	glEnd();
}

void tower2() {
	initTexture("sub.bmp");
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	//glColor3ub(204, 102, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, GL_TRUE);
	gluCylinder(cylinder, .5, .5, 25, 35, 8);

	gluDeleteQuadric(cylinder);
}

void tower3() {
	initTexture("rooftop.bmp");
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 30, .5);
	glTexCoord2f(1, 1);
	glVertex3f(1, 30, .5);
	glTexCoord2f(1, 0);
	glVertex3f(6, 25, 3);
	glTexCoord2f(0, 0);
	glVertex3f(-6, 25, 3);

	glTexCoord2f(0, 1);
	glVertex3f(-6, 25, 3);
	glTexCoord2f(1, 1);
	glVertex3f(-6, 25, -3);
	glTexCoord2f(1, 0);
	glVertex3f(6, 25, -3);
	glTexCoord2f(0, 0);
	glVertex3f(6, 25, 3);

	glTexCoord2f(0, 1);
	glVertex3f(6, 25, 3);
	glTexCoord2f(1, 1);
	glVertex3f(6, 25, -3);
	glTexCoord2f(1, 0);
	glVertex3f(1, 30, -.5);
	glTexCoord2f(0, 0);
	glVertex3f(1, 30, .5);

	glTexCoord2f(0, 1);
	glVertex3f(1, 30, .5);
	glTexCoord2f(1, 1);
	glVertex3f(1, 30, -.5);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 30, -.5);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 30, .5);

	glTexCoord2f(0, 1);
	glVertex3f(-1, 30, .5);
	glTexCoord2f(1, 1);
	glVertex3f(-6, 25, 3);
	glTexCoord2f(1, 0);
	glVertex3f(-6, 25, -3);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 30, -.5);

	glTexCoord2f(0, 1);
	glVertex3f(-1, 30, -.5);
	glTexCoord2f(1, 1);
	glVertex3f(1, 30, -.5);
	glTexCoord2f(1, 0);
	glVertex3f(6, 25, -3);
	glTexCoord2f(0, 0);
	glVertex3f(-6, 25, -3);
	glEnd();
}

void tower4() {
	initTexture("rooftop.bmp");
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	//glColor3ub(102, 51, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, GL_TRUE);
	gluCylinder(cylinder, .5, .0, 3, 35, 8);

	gluDeleteQuadric(cylinder);
}

void tower5() {
	initTexture("rooftop.bmp");
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glTexCoord2f(.5, .5);
	glVertex3f(0, 31, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 30, .5);
	glTexCoord2f(0, 1);
	glVertex3f(1, 30, .5);

	glTexCoord2f(0, 0);
	glVertex3f(1, 30, .5);
	glTexCoord2f(.5, .5);
	glVertex3f(0, 31, 0);
	glTexCoord2f(0, 1);
	glVertex3f(1, 30, -.5);

	glTexCoord2f(0, 0);
	glVertex3f(1, 30, -.5);
	glTexCoord2f(.5, .5);
	glVertex3f(0, 31, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 30, -.5);

	glTexCoord2f(0, 0);
	glVertex3f(-1, 30, -.5);
	glTexCoord2f(.5, .5);
	glVertex3f(0, 31, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 30, .5);
	glEnd();
}

void tower6() {
	initTexture("sub.bmp");
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	//glColor3ub(204, 102, 0);
	gluQuadricTexture(cylinder, GL_TRUE);
	gluCylinder(cylinder, .5, .5, 2, 35, 8);

	gluDeleteQuadric(cylinder);
}

void tower7() {
	initTexture("main.bmp");
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-6, 15, 3);
	glTexCoord2f(1, 0);
	glVertex3f(6, 15, 3);
	glTexCoord2f(0, 0);
	glVertex3f(6, 10, 3);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 10, 3);

	glTexCoord2f(1, 1);
	glVertex3f(-6, 10, 3);
	glTexCoord2f(1, 0);
	glVertex3f(-6, 10, -3);
	glTexCoord2f(0, 0);
	glVertex3f(6, 10, -3);
	glTexCoord2f(0, 1);
	glVertex3f(6, 10, 3);

	glTexCoord2f(1, 1);
	glVertex3f(6, 10, 3);
	glTexCoord2f(1, 0);
	glVertex3f(6, 10, -3);
	glTexCoord2f(0, 0);
	glVertex3f(6, 15, -3);
	glTexCoord2f(0, 1);
	glVertex3f(6, 15, 3);

	glTexCoord2f(1, 1);
	glVertex3f(6, 15, 3);
	glTexCoord2f(1, 0);
	glVertex3f(6, 15, -3);
	glTexCoord2f(0, 0);
	glVertex3f(-6, 15, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 15, 3);

	glTexCoord2f(1, 1);
	glVertex3f(-6, 15, 3);
	glTexCoord2f(1, 0);
	glVertex3f(-6, 10, 3);
	glTexCoord2f(0, 0);
	glVertex3f(-6, 10, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 15, -3);

	glTexCoord2f(1, 1);
	glVertex3f(-6, 15, -3);
	glTexCoord2f(1, 0);
	glVertex3f(6, 15, -3);
	glTexCoord2f(0, 0);
	glVertex3f(6, 10, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 10, -3);
	glEnd();
}

void road1() {
	initTexture("road.bmp");
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(6, 10, 4);
	glTexCoord2f(1, 0);
	glVertex3f(6, 10, 24);
	glTexCoord2f(0, 0);
	glVertex3f(6, 9, 24);
	glTexCoord2f(0, 1);
	glVertex3f(6, 9, 4);

	glTexCoord2f(1, 1);
	glVertex3f(6, 9, 4);
	glTexCoord2f(1, 0);
	glVertex3f(-6, 9, 4);
	glTexCoord2f(0, 0);
	glVertex3f(-6, 9, 24);
	glTexCoord2f(0, 1);
	glVertex3f(6, 9, 24);

	glTexCoord2f(1, 1);
	glVertex3f(6, 9, 24);
	glTexCoord2f(1, 0);
	glVertex3f(-6, 9, 24);
	glTexCoord2f(0, 0);
	glVertex3f(-6, 10, 24);
	glTexCoord2f(0, 1);
	glVertex3f(6, 10, 24);

	glTexCoord2f(1, 1);
	glVertex3f(6, 10, 24);
	glTexCoord2f(1, 0);
	glVertex3f(-6, 10, 24);
	glTexCoord2f(0, 0);
	glVertex3f(-6, 10, 4);
	glTexCoord2f(0, 1);
	glVertex3f(6, 10, 4);

	glTexCoord2f(1, 1);
	glVertex3f(6, 10, 4);
	glTexCoord2f(1, 0);
	glVertex3f(6, 9, 4);
	glTexCoord2f(0, 0);
	glVertex3f(-6, 9, 4);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 10, 4);

	glTexCoord2f(1, 1);
	glVertex3f(-6, 10, 4);
	glTexCoord2f(1, 0);
	glVertex3f(-6, 10, 24);
	glTexCoord2f(0, 0);
	glVertex3f(-6, 9, 24);
	glTexCoord2f(0, 1);
	glVertex3f(-6, 9, 4);
	glEnd();
}

void roadRope() {
	
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3ub(96, 96, 96);
	for (int i = 45.0; i < 115.0; i++)
	{
		glVertex2f(0 + 5 * cos(i * -3.142 / 180), -0 + 6 * sin(i * -3.142 / 180));
	}
	glEnd();
}

void upperBridge() {
	initTexture("bridge.bmp");
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-12, 20.5, 6.5);
	glTexCoord2f(1, 0);
	glVertex3f(12, 20.5, 6.5);
	glTexCoord2f(0, 0);
	glVertex3f(12, 20, 6.5);
	glTexCoord2f(0, 1);
	glVertex3f(-12, 20, 6.5);

	glTexCoord2f(1, 1);
	glVertex3f(-12, 20, 6.5);
	glTexCoord2f(1, 0);
	glVertex3f(-12, 20, 2.5);
	glTexCoord2f(0, 0);
	glVertex3f(12, 20, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(12, 20, 6.5);

	glTexCoord2f(1, 1);
	glVertex3f(12, 20, 6.5);
	glTexCoord2f(1, 0);
	glVertex3f(12, 20, 2.5);
	glTexCoord2f(0, 0);
	glVertex3f(12, 20.5, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(12, 20.5, 6.5);

	glTexCoord2f(1, 1);
	glVertex3f(12, 20.5, 6.5);
	glTexCoord2f(1, 0);
	glVertex3f(12, 20.5, 2.5);
	glTexCoord2f(0, 0);
	glVertex3f(-12, 20.5, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(12, 20.5, 6.5);

	glTexCoord2f(1, 1);
	glVertex3f(12, 20.5, 6.5);
	glTexCoord2f(1, 0);
	glVertex3f(-12, 20, 6.5);
	glTexCoord2f(0, 0);
	glVertex3f(-12, 20, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(-12, 20.5, 2.5);

	glTexCoord2f(1, 1);
	glVertex3f(-12, 20.5, 2.5);
	glTexCoord2f(1, 0);
	glVertex3f(12, 20.5, 2.5);
	glTexCoord2f(0, 0);
	glVertex3f(12, 20, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(-12, 20, 2.5);
	glEnd();

	initTexture("bridge.bmp");
	glBegin(GL_QUADS);

	glTexCoord2f(1, 1);
	glVertex3f(-12, 20.5, -6.5);
	glTexCoord2f(1, 0);
	glVertex3f(12, 20.5, -6.5);
	glTexCoord2f(0, 0);
	glVertex3f(12, 20, -6.5);
	glTexCoord2f(0, 1);
	glVertex3f(-12, 20, -6.5);

	glTexCoord2f(1, 1);
	glVertex3f(-12, 20, -6.5);
	glTexCoord2f(1, 0);
	glVertex3f(-12, 20, -2.5);
	glTexCoord2f(0, 0);
	glVertex3f(12, 20, -2.5);
	glTexCoord2f(0, 1);
	glVertex3f(12, 20, -6.5);

	glTexCoord2f(1, 1);
	glVertex3f(12, 20, -6.5);
	glTexCoord2f(1, 0);
	glVertex3f(12, 20, -2.5);
	glTexCoord2f(0, 0);
	glVertex3f(12, 20.5, -2.5);
	glTexCoord2f(0, 1);
	glVertex3f(12, 20.5, -6.5);

	glTexCoord2f(1, 1);
	glVertex3f(12, 20.5, -6.5);
	glTexCoord2f(1, 0);
	glVertex3f(12, 20.5, -2.5);
	glTexCoord2f(0, 0);
	glVertex3f(-12, 20.5, -2.5);
	glTexCoord2f(0, 1);
	glVertex3f(12, 20.5, -6.5);

	glTexCoord2f(1, 1);
	glVertex3f(12, 20.5, -6.5);
	glTexCoord2f(1, 0);
	glVertex3f(-12, 20, -6.5);
	glTexCoord2f(0, 0);
	glVertex3f(-12, 20, -2.5);
	glTexCoord2f(0, 1);
	glVertex3f(-12, 20.5, -2.5);

	glTexCoord2f(1, 1);
	glVertex3f(-12, 20.5, -2.5);
	glTexCoord2f(1, 0);
	glVertex3f(12, 20.5, -2.5);
	glTexCoord2f(0, 0);
	glVertex3f(12, 20, -2.5);
	glTexCoord2f(0, 1);
	glVertex3f(-12, 20, -2.5);
	glEnd();
}

void movableBridge() {
	initTexture("bridge.bmp");
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0, 6);
	glTexCoord2f(1, 0);
	glVertex3f(11, 0, 6);
	glTexCoord2f(0, 0);
	glVertex3f(11, 1, 6);
	glTexCoord2f(0, 1);
	glVertex3f(0, 1, 6);

	glTexCoord2f(1, 1);
	glVertex3f(0, 1, 6);
	glTexCoord2f(1, 0);
	glVertex3f(0, 1, -6);
	glTexCoord2f(0, 0);
	glVertex3f(11, 1, -6);
	glTexCoord2f(0, 1);
	glVertex3f(11, 1, 6);

	glTexCoord2f(1, 1);
	glVertex3f(11, 1, 6);
	glTexCoord2f(1, 0);
	glVertex3f(11, 1, -6);
	glTexCoord2f(0, 0);
	glVertex3f(11, 0, -6);
	glTexCoord2f(0, 1);
	glVertex3f(11, 0, 6);

	glTexCoord2f(1, 1);
	glVertex3f(11, 0, 6);
	glTexCoord2f(1, 0);
	glVertex3f(11, 0, -6);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, -6);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 6);

	glTexCoord2f(1, 1);
	glVertex3f(0, 0, 6);
	glTexCoord2f(1, 0);
	glVertex3f(0, 1, 6);
	glTexCoord2f(0, 0);
	glVertex3f(0, 1, -6);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, -6);

	glTexCoord2f(1, 1);
	glVertex3f(0, 0, -6);
	glTexCoord2f(1, 0);
	glVertex3f(11, 0, -6);
	glTexCoord2f(0, 0);
	glVertex3f(11, 1, -6);
	glTexCoord2f(0, 1);
	glVertex3f(0, 1, -6);
	glEnd();
}

void combine1() {
	glPushMatrix();
	glTranslatef(15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(6, 25, 3);
	glRotatef(-90, 1, 0, 0);
	tower6();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(6, 25, -3);
	glRotatef(-90, 1, 0, 0);
	tower6();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-6, 25, -3);
	glRotatef(-90, 1, 0, 0);
	tower6();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-6, 25, 3);
	glRotatef(-90, 1, 0, 0);
	tower6();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(6, 27, 3);
	glRotatef(-90, 1, 0, 0);
	tower4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(6, 27, -3);
	glRotatef(-90, 1, 0, 0);
	tower4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-6, 27, -3);
	glRotatef(-90, 1, 0, 0);
	tower4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-6, 27, 3);
	glRotatef(-90, 1, 0, 0);
	tower4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(6, 0, 3);
	glRotatef(-90, 1, 0, 0);
	tower2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(6, 0, -3);
	glRotatef(-90, 1, 0, 0);
	tower2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-6, 0, -3);
	glRotatef(-90, 1, 0, 0);
	tower2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-6, 0, 3);
	glRotatef(-90, 1, 0, 0);
	tower2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 0, 0);
	glRotatef(90, 0, 1, 0);

	tower7();
	tower5();
	tower3();
	tower1();
	glPopMatrix();
}

void combine2() {
	glPushMatrix();
	glTranslatef(-15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(6, 25, 3);
	glRotatef(-90, 1, 0, 0);
	tower6();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(6, 25, -3);
	glRotatef(-90, 1, 0, 0);
	tower6();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-6, 25, -3);
	glRotatef(-90, 1, 0, 0);
	tower6();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-6, 25, 3);
	glRotatef(-90, 1, 0, 0);
	tower6();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(6, 27, 3);
	glRotatef(-90, 1, 0, 0);
	tower4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(6, 27, -3);
	glRotatef(-90, 1, 0, 0);
	tower4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-6, 27, -3);
	glRotatef(-90, 1, 0, 0);
	tower4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-6, 27, 3);
	glRotatef(-90, 1, 0, 0);
	tower4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(6, 0, 3);
	glRotatef(-90, 1, 0, 0);
	tower2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(6, 0, -3);
	glRotatef(-90, 1, 0, 0);
	tower2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-6, 0, -3);
	glRotatef(-90, 1, 0, 0);
	tower2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-6, 0, 3);
	glRotatef(-90, 1, 0, 0);
	tower2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, 0);
	glRotatef(90, 0, 1, 0);

	tower7();
	tower5();
	tower3();
	tower1();
	glPopMatrix();
}

void combine3() {
	glPushMatrix();
	glTranslatef(15, 0, 0);
	glRotatef(90, 0, 1, 0);
	road1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-43, 0, 0);
	glRotatef(90, 0, 1, 0);
	road1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 6);
	glScalef(3.5, 3.5, 0);
	glTranslatef(-8.8, 10, 0);
	roadRope();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -6);
	glScalef(3.5, 3.5, 0);
	glTranslatef(-8.8, 10, 0);
	roadRope();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -6);
	glRotatef(180, 0, 1, 0);
	glScalef(3.5, 3.5, 0);
	glTranslatef(-8.8, 10, 0);
	roadRope();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 6);
	glRotatef(180, 0, 1, 0);
	glScalef(3.5, 3.5, 0);
	glTranslatef(-8.8, 10, 0);
	roadRope();
	glPopMatrix();
}

void combine4() {
	
	upperBridge();

	if (open >= 1) {
		close = 0;
		speed += 1.0;
		transf -= 0.33;
		if (speed >= 45) {
			open = 0;
			transf = 12;
			speed = 45;
		}
	}
	else if (close >= 1) {
		open = 0;
		speed -= 1.0;
		transf += 0.33;
		if (speed <= 0) {
			close = 0;
			speed = 0;
			transf = 29;
		}
	}

	glPushMatrix();
	glTranslatef(0, transf, 0);
	sun();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-11, 9, 0);
	glRotatef(speed, 0, 0, 1);
	movableBridge();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-11, 9, 0);
	glRotatef(speed, 0, 0, 1);
	movableBridge();
	glPopMatrix();


}

void sun() {
	initTexture("sun.bmp");
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	
	gluSphere(sphere, 6, 30, 30);
	gluDeleteQuadric(sphere);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(0.0, -10.0, viewDistance);
	glRotatef(rotateY, 0, 1, 0);
	glPushMatrix();

	combine1();
	combine2();
	combine3();
	combine4();

	glPopMatrix();

}
//--------------------------------------------------------------------



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(70, 1, 1, 2000);

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------