#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <conio.h>
#include <string>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib,"GLU32.lib")

#define WINDOW_TITLE "P7"

GLuint texture = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;

int rotate = 0;
bool pyramid = true;

void initTexture(LPCSTR bmp_dir);

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case VK_LEFT:
			if (rotate == 0)
				rotate = 1;
			else
				rotate = 0;
			break;
		case VK_RIGHT:
			if (rotate == 0)
				rotate = 2;
			else
				rotate = 0;
			break;
		default:
			break;
		}
	case WM_CHAR:
		switch (wParam)
		{

		case 0x43:
			pyramid = false;
			break;
		case 0x50:
			pyramid = true;
			break;
		case VK_F1:
			initTexture("brick.bmp");
			break;
		case VK_F2:
			initTexture("metal.bmp");
			break;
		case VK_F3:
			initTexture("box.bmp");
			break;
		default:
			break;
		}


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

void drawCube(float size) {

	glBegin(GL_QUADS);

	// front
	//red
	//glColor3f(1, 0, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, 0, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, 0, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);

	// left
	//green
	//glColor3f(0, 1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, 0, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, size, size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size, size, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(size, 0, 0);

	// bottom
	//blue
	//glColor3f(0, 0, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, size, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, size, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(size, 0, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);

	// right
	//glColor3f(1, 0, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, size, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 0, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, size, 0);

	// behind
	//white
	//glColor3f(0, 1, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, size, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, size, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, size, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, size, 0);

	// top
	//black
	//glColor3f(1, 0, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, size, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, size, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, 0, size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, size);

	glEnd();
}

void initTexture(LPCSTR bmp_dir) {
	// Init
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		bmp_dir, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE); // First Param can change to bump.
	GetObject(hBMP, sizeof(BMP), &BMP);
}

void drawPyramid()
{
	glPushMatrix();

	glTranslatef(0, -0.3f, 0);
	//glRotatef(rotateDeg, 1, 1, 1);
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 0.5);
	glVertex3f(0, 0.5, -0.25);
	glTexCoord2f(-0.25, 0);
	glVertex3f(-0.25, 0, 0);
	glTexCoord2f(0.25, 0);
	glVertex3f(0.25, 0, 0);

	glTexCoord2f(0, 0.5);
	glVertex3f(0, 0.5, -0.25);
	glTexCoord2f(-0.25, 0);
	glVertex3f(-0.25, 0, 0);
	glTexCoord2f(0.25, 0);
	glVertex3f(-0.25, 0, -0.5);

	glTexCoord2f(0, 0.5);
	glVertex3f(0, 0.5, -0.25);
	glTexCoord2f(-0.25, 0);
	glVertex3f(0.25, 0, 0);
	glTexCoord2f(0.25, 0);
	glVertex3f(0.25, 0, -0.5);

	glTexCoord2f(0, 0.5);
	glVertex3f(0, 0.5, -0.25);
	glTexCoord2f(-0.25, 0);
	glVertex3f(0.25, 0, -0.5);
	glTexCoord2f(0.25, 0);
	glVertex3f(-0.25, 0, -0.5);

	glEnd();

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 1);
		glVertex3f(-0.25, 0, -0.5);

		glTexCoord2f(1, 1);
		glVertex3f(-0.25, 0, 0);

		glTexCoord2f(1, 0.0f);
		glVertex3f(0.25, 0, 0);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.25, 0, -0.5);
	}
	glEnd();

	glPopMatrix();
}

void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	if (rotate == 1)
	{
		glRotatef(-0.05, 1, 1, 1);
	}
	else if (rotate == 2)
	{
		glRotatef(0.05, 1, 1, 1);
	}
	if (!pyramid)
	{
		drawCube(0.5);
	}
	else {
		drawPyramid();
	}


	glDisable(GL_TEXTURE_2D);
	glDeleteTextures(1, &texture);


}
//--------------------------------------------------------------------

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevInstance,
	_In_ LPSTR cmdLine, _In_ int nCmdShow) // FIXED
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
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
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

	DeleteObject(hBMP);

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}

//--------------------------------------------------------------------