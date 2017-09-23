#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
public:
	Transform(glm::vec2 position = {}, float rotation = 0, glm::vec2 scale = {1, 1}):
		m_pos(position), m_rot(rotation), m_scale(scale), m_transform(){}
	
	inline glm::vec2& getPos(){return m_pos;}
	inline float& getRot(){return m_rot;}
	inline glm::vec2& getScale(){return m_scale;}
	inline const glm::mat4& getModel()
	{
		m_transform = glm::translate(glm::vec3(m_pos.x, m_pos.y, 0)) *
            glm::rotate(m_rot, glm::vec3(0, 0, 1)) *
            glm::scale(glm::vec3(m_scale.x, m_scale.y, 1));
		return m_transform;
	}
private:
	glm::mat4 m_transform;
	glm::vec2 m_pos;
	glm::vec2 m_scale;
	float m_rot;
};

#endif //TRANSFORM_H