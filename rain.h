#pragma once
#include<string>
#include <time.h>
#include <string>
#include "Mesh.h"
#include<vector>
using namespace std;
class Rain
{
public:
	Rain() {
		height = 0.04f;
		width = 0.04f;
		xspeed = (float)(rand() % 1920) / 1919 * 0.002f;
		float minspeed = 0.03f;
		float maxspeed = 0.06f;
		speed = (float)(rand() % 1920) / 1919 * (maxspeed - minspeed) + minspeed;
		//speed = speed > minspeed ? speed : minspeed;
		x = (float)(rand() % 1920) / 1919;
		x = x * 2.0f - 1.f;
		y = 1.f + (float)(rand() % 1920) / 1919 * 3;
	};
	~Rain();
	void UpdateSpeed(float minspeed, float maxspeed, float windspeed) {
		speed = (float)(rand() % 1920) / 1919 * (maxspeed - minspeed) + minspeed;
	}
	inline void Update()
	{
		y -= speed;
		if (y < -1 - height)
		{
			y = 1.0f + height;
		}
		float area = 1.1f;
		if (x<area && x>-area && y<area && y>-area&& xspeed < speed / 2)
		{
			xspeed += speed/2;
		}
		else
		{
			xspeed -= speed / 300;
			xspeed = xspeed > 0 ? xspeed : (float)(rand() % 1920) / 1919 * 0.002f;
		}
		x += xspeed;
		if (x > 1)
			x = -1;
	}
	inline string tostring()
	{
		string te = "X:";
		te += to_string(x);
		te += " Y:";
		te += to_string(y);
		te += " Height:";
		te += to_string(height);
		te += " Width:";
		te += to_string(width);
		te += " Speed:";
		te += to_string(speed);
		return te;
	}
	inline vector<Vertex> genVertex() {
		vector<Vertex> temp;
		temp.push_back(Vertex(glm::vec3(x, y, 0), glm::vec2(0, 0)));
		temp.push_back(Vertex(glm::vec3(x + width, y, 0), glm::vec2(1.0, 0)));
		temp.push_back(Vertex(glm::vec3(x, y + height, 0), glm::vec2(0, 1.0)));
		temp.push_back(Vertex(glm::vec3(x + width, y, 0), glm::vec2(1.0, 0)));
		temp.push_back(Vertex(glm::vec3(x, y + height, 0), glm::vec2(0, 1.0)));
		temp.push_back(Vertex(glm::vec3(x + width, y + height, 0), glm::vec2(1.0, 1.0)));
		return temp;
	}
private:
	float x, y, height, width;
	float speed, xspeed;
};


Rain::~Rain()
{
}




