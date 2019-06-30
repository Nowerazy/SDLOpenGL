#pragma once
#include <glm/glm.hpp>
#include<glm/gtx/transform.hpp>
class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar) {
		this->pos = pos;
		this->forword = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, zNear, zFar);
		//投影矩阵(世界坐标系转成投影坐标2D)
	}
	inline glm::mat4 GetViewProjection()const {
		return projection * glm::lookAt(pos, pos + forword, up);
		/*  1:camera position
			2 camera angle of view
			3 top direction*/
	}
	~Camera() {}

private:
	glm::mat4 projection;
	glm::vec3 pos;//camera position
	glm::vec3 forword;//visual direction
	glm::vec3 up;// Direction from the top down

};

