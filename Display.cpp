#include"Display.h"
#include "GL/glew.h"
#include <iostream>
Display::Display(int widh, int height, const std::string& title) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, widh, height, SDL_WINDOW_OPENGL);
	m_glcontext = SDL_GL_CreateContext(m_window);
	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		std::cerr << "Glew Init failure " << std::endl;
	}
	m_isclosed = false;
	glEnable(GL_DEPTH_TEST);
}
Display::~Display() {
	SDL_GL_DeleteContext(m_glcontext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
void Display::Update() {
	SDL_GL_SwapWindow(m_window);
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) {
			m_isclosed = true;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			mouseMoveSize[0] = e.motion.x;
			mouseMoveSize[1] = e.motion.y;
			if (SDL_BUTTON_LEFT == e.button.button)
			{
				isLeftdraged = true;
				//std::cerr << "SDL_MOUSEBUTTONDOWN x/y:" << mouseMoveSize[0] << " / " << mouseMoveSize[1] << std::endl;
			}
			else if (SDL_BUTTON_RIGHT == e.button.button)
			{
				isRightdraged = true;
			}
		}
		else if (e.type == SDL_MOUSEBUTTONUP)
		{
			if (SDL_BUTTON_LEFT == e.button.button)
			{
				isLeftdraged = false;
			}
			else if (SDL_BUTTON_RIGHT == e.button.button)
			{

				isRightdraged = false;
			}
			//std::cerr << "SDL_MOUSEBUTTONUP" << std::endl;

		}
		else if (e.type == SDL_MOUSEMOTION)
		{
			if (isLeftdraged == true)
			{

				accumuMoveSize[0] += e.motion.x - mouseMoveSize[0];
				accumuMoveSize[1] += e.motion.y - mouseMoveSize[1];
				mouseMoveSize[0] = e.motion.x;
				mouseMoveSize[1] = e.motion.y;
			}
			else if (isRightdraged == true)
			{
				accumuMoveSize[3] += e.motion.x - mouseMoveSize[0];
				accumuMoveSize[4] += e.motion.y - mouseMoveSize[1];
				mouseMoveSize[0] = e.motion.x;
				mouseMoveSize[1] = e.motion.y;
			}

		}
		else if (e.type == SDL_MOUSEWHEEL)
		{
			if (accumuMoveSize[2] >> 31 != e.wheel.y >> 31)//inverse symbol
			{
				accumuMoveSize[2] = 0;
				accumuMoveSize[2] += e.wheel.y;
			}
			else {
				accumuMoveSize[2] += e.wheel.y;
			}
			//std::cerr << "accumuMoveSize[2]:" << accumuMoveSize[2] << std::endl;

		}

	}
}

void Display::Clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
bool Display::Isclosed() {
	return m_isclosed;
}