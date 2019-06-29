#pragma once
#include<string>
#include"SDL2/SDL.h"

class Display
{
public:
	Display(int widh,int height,const std::string&title);
	void Update();
	bool Isclosed();
	~Display();

private:
	SDL_Window* m_window;
	SDL_GLContext m_glcontext;
	bool m_isclosed;
};
