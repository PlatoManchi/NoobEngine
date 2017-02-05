#include "pch.h"
#include "Container/SList.h"
#include "Container/Vector.h"
#include <stdio.h>
#include "Container/Hashmap.h"
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
	NoobEngine::Container::Hashmap<uint32_t, uint32_t> map;
	map.begin();
	map.end();
	
	map[10U] = 100;
	map[20U] = 200;

	NoobEngine::Container::Hashmap<uint32_t, uint32_t>::Iterator itr = map.begin();

	uint32_t tmp = (*itr).second;
	++itr;
	
	tmp = (*itr).second;
	tmp;
	++itr;
	

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