#include "pch.h"
#include "Container/SList.h"
#include <stdio.h>

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);

	const float CornflowerBlue[4] = { 0.392f, 0.584f, 0.929f, 1.0f };
	if (!glfwInit()) 
	{
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
	if (!window) 
	{
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (gl3wInit() != 0)
	{
		return -1;
	}
	
	// testing the library linking capability
	NoobEngine::Container::SList<int32_t> sampleList;
	sampleList.PushBack(10);
	sampleList.PushBack(20);
	sampleList.PushBack(30);

	sampleList.Remove(10);

	for (NoobEngine::Container::SList<int32_t>::Iterator itr = sampleList.begin(); itr != sampleList.end(); itr++)
	{
		char debug[256];
		sprintf_s(debug, "ranged based for loop: %d\n", *itr);
		OutputDebugString(debug);
	}

	for each(int32_t var in sampleList)
	{
		char debug[256];
		sprintf_s(debug, "for each: %d\n", var);
		OutputDebugString(debug);
	}
	
	
	glViewport(0, 0, 800, 600);
	while (!glfwWindowShouldClose(window))
	{
		glClearBufferfv(GL_COLOR, 0, &CornflowerBlue[0]);
		 
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	// sort through and find what code to run for the message given
	switch (message) {
		// this message is read when the window is closed
		case WM_DESTROY:
		{
			// close the application entirely
			PostQuitMessage(0);
			return 0;
		}
		break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}