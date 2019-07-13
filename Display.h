#pragma once
#include<string>
#include"SDL2/SDL.h"

class Display
{
public:
	Display(int widh, int height, const std::string& title);
	void Update();
	bool Isclosed();
	void Clear(float r, float g, float b, float a);
	bool isRightdraged = false, isLeftdraged = false;
	int accumuMoveSize[5] = { 0 };//12 leftdragXY 3 wheel 45 rightdragXY
	~Display();

private:
	SDL_Window* m_window;
	SDL_GLContext m_glcontext;
	bool m_isclosed;
	int mouseMoveSize[2] = { 0 };
};
