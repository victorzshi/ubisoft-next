//---------------------------------------------------------------------------------
// Main.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
//---------------------------------------------------------------------------------
#include <windows.h>  // for MS Windows
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <list>
//---------------------------------------------------------------------------------
#include "app.h"
#include "SimpleSound.h"
#include "SimpleController.h"

//---------------------------------------------------------------------------------
// Initial setup globals.
//---------------------------------------------------------------------------------
int WINDOW_WIDTH = APP_INIT_WINDOW_WIDTH;
int WINDOW_HEIGHT = APP_INIT_WINDOW_HEIGHT;
HWND MAIN_WINDOW_HANDLE = nullptr;

//---------------------------------------------------------------------------------
static const double UPDATE_MAX = ((1.0 / APP_MAX_FRAME_RATE)*1000.0);
//---------------------------------------------------------------------------------
// Internal globals for timing.
double gPCFreq = 0.0;
__int64 gCounterStart = 0;
double gLastTime;

//---------------------------------------------------------------------------------
// User implemented methods.
//---------------------------------------------------------------------------------
extern void Init();
extern void Update(float deltaTime);
extern void Render();
extern void Shutdown();
//---------------------------------------------------------------------------------
void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
	{
		printf("Failed to init performance counters.");
	}
	gPCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	gCounterStart = li.QuadPart;
}

double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return (double(li.QuadPart - gCounterStart) / gPCFreq);
}


class CProfiler
{
public:
	CProfiler() : m_startTime(0), m_elapsedTime(0)
	{		
	}
	void Start()
	{
		m_startTime = GetCounter();
	}
	double Stop()
	{ 
		m_elapsedTime = GetCounter() - m_startTime;
		return m_elapsedTime;
	}
	void Print(float x, float y, const char *text)
	{
		char textBuffer[64];
		sprintf(textBuffer, "%s: %0.4f ms", text,m_elapsedTime);
		App::Print(x, y, textBuffer,1.0f,0.0f,1.0f, GLUT_BITMAP_HELVETICA_10);
	}
private:	
	double m_startTime;
	double m_elapsedTime;
};

CProfiler	gUserRenderProfiler;
CProfiler	gUserUpdateProfiler;
CProfiler	gUpdateDeltaTime;
bool		gRenderUpdateTimes = APP_RENDER_UPDATE_TIMES;

/* Initialize OpenGL Graphics */
void InitGL()
{
	StartCounter();
	gLastTime = GetCounter();
	// Set "clearing" or background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

//---------------------------------------------------------------------------------
// Handler for window-repaint event. Call back when the window first appears and
// whenever the window needs to be re-painted. */
//---------------------------------------------------------------------------------
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

	gUserRenderProfiler.Start();	
	Render();						// Call user defined render.
	gUserRenderProfiler.Stop();
	if (gRenderUpdateTimes)
	{
		gUpdateDeltaTime.Print	 (10, 40, "Update");
		gUserRenderProfiler.Print(10, 25, "User Render");
		gUserUpdateProfiler.Print(10, 10, "User Update");
	}
	glFlush();  // Render now						 
}

//---------------------------------------------------------------------------------
// Update from glut. Called when no more event handling.
//---------------------------------------------------------------------------------
void Idle()
{	
	static double prevTime = GetCounter();
	double tick = GetCounter() - prevTime;
	double currentTime = GetCounter();
	double deltaTime = currentTime - gLastTime;
	// Update.
	if (deltaTime > (UPDATE_MAX))
	{	
		gUpdateDeltaTime.Stop();
		glutPostRedisplay(); //everytime you are done 
		CSimpleControllers::GetInstance().Update();

		gUserUpdateProfiler.Start();
		Update((float)deltaTime);				// Call user defined update.
		gUserUpdateProfiler.Stop();
		
		gLastTime = currentTime;		
		RECT tileClientArea;
		if (GetClientRect( MAIN_WINDOW_HANDLE, &tileClientArea))
		{
			WINDOW_WIDTH = tileClientArea.right - tileClientArea.left;
			WINDOW_HEIGHT = tileClientArea.bottom - tileClientArea.top;
		}

		if (App::GetController().CheckButton(APP_ENABLE_DEBUG_INFO_BUTTON) )
		{
			gRenderUpdateTimes = !gRenderUpdateTimes;
		}

		if (App::IsKeyPressed(APP_QUIT_KEY))
		{		
			exit(0);
		}
		gUpdateDeltaTime.Start();
	}
	
}

// Break here and use the diagnostics debug view to check for user mem leaks.
void CheckMemCallback()
{
}


//---------------------------------------------------------------------------------
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, 	_In_opt_ HINSTANCE hPrevInstance,	_In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{	
	int argc = 0;	char* argv = "";

	// Exit handler to check memory on exit.
	const int result_1 = std::atexit(CheckMemCallback);

	// Setup glut.
	glutInit(&argc, &argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	int glutWind = glutCreateWindow(APP_WINDOW_TITLE);	
	HDC dc = wglGetCurrentDC();
	MAIN_WINDOW_HANDLE = WindowFromDC(dc);
	glutIdleFunc(Idle);
	glutDisplayFunc(Display);       // Register callback handler for window re-paint event	
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	InitGL();                       // Our own OpenGL initialization



	// Init sounds system.
	CSimpleSound::GetInstance().Initialize(MAIN_WINDOW_HANDLE);
	
	// Call user defined init.
	Init();

	// Enter glut the event-processing loop				
	glutMainLoop();
	
	// Call user shutdown.
	Shutdown();	

	// Shutdown sound system.
	CSimpleSound::GetInstance().Shutdown();

	// And we are done.
	return 0;
}


