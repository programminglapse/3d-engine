#include "CCamera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace
{

glm::mat4 CalculateViewMatrix( const glm::vec3& aPos, const glm::vec3& aFront, const glm::vec3& aUp );

} // anonymous namespace

namespace Engine
{

CCamera::CCamera( const glm::vec3& aPos, const glm::vec3& aFront, const glm::vec3& aUp, const glm::mat4& aProjectionMatrix,
		const float& aSpeed ) :
	mPos( aPos ),
	mFront( aFront ),
	mUp( aUp ),
	mProjectionMatrix( aProjectionMatrix ),
	mViewMatrix( CalculateViewMatrix( mPos, mFront, mUp ) ),
	mSpeed( aSpeed )
{
}

const glm::mat4& CCamera::GetProjectionMatrix() const
{
	return mProjectionMatrix;
}

const glm::mat4& CCamera::GetViewMatrix() const
{
	return mViewMatrix;
}

const glm::mat4& CCamera::GetModelMatrix() const
{
	return mModelMatrix;
}

void CCamera::SetProjectionMatrix( const glm::mat4& aProjectionMatrix )
{
	mProjectionMatrix = aProjectionMatrix;
}

void CCamera::Move( const glm::vec3& aMove )
{
	mPos += aMove*mSpeed;
	mViewMatrix = CalculateViewMatrix( mPos, mFront, mUp );
}

} // namespace Engine

namespace
{

glm::mat4 CalculateViewMatrix( const glm::vec3& aPos, const glm::vec3& aFront, const glm::vec3& aUp )
{
	return glm::lookAt( aPos, aPos + aFront, aUp );
}

} // anonymous namespace
