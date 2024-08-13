#ifndef C_CAMERA__H
#define C_CAMERA__H

#include "glm/glm.hpp"

namespace Engine
{

class CCamera
{
public:
	CCamera( const glm::vec3& aPos, const glm::vec3& aFront, const glm::vec3& aUp, const glm::mat4& aProjectionMatrix,
			const float& aSpeed = 1.0f );

	const glm::mat4& GetProjectionMatrix() const;
	const glm::mat4& GetViewMatrix() const;
	const glm::mat4& GetModelMatrix() const;

	void SetProjectionMatrix( const glm::mat4& aProjectionMatrix );

	void Move( const glm::vec3& aMove );

private:
	glm::vec3 mPos;
	glm::vec3 mFront;
	glm::vec3 mUp;

	glm::mat4 mProjectionMatrix;
	glm::mat4 mViewMatrix;
	glm::mat4 mModelMatrix = glm::mat4(1.0f);

	float mSpeed;
};

} // namespace Engine

#endif
