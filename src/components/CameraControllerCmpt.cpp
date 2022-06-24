#include "components/CameraControllerCmpt.h"
#include "w3d/component/ComponentManager.h"

void CameraControllerCmpt::start()
{
	transform = dynamic_cast<TransformCmpt*>(cManager->getComponentTypeOnEntity<TransformCmpt>(controllingEntity));
}

void CameraControllerCmpt::update()
{
	//camera->view = transform->getMatrix();
	camera->position = transform->position;
	camera->rotation = transform->rotation;
	camera->scale = transform->scale;

	W3D::Math::fVec3 fwd;
	fwd.x = std::sin(W3D::Math::degreesToRad(yaw));
	fwd.z = std::cos(W3D::Math::degreesToRad(yaw));
	fwd.y = std::sin(W3D::Math::degreesToRad(pitch));


	W3D::Math::fVec3 cameraRight = (W3D::Math::fVec3::cross(W3D::Math::fVec3(0.0f, 1.0f, 0.0f), fwd)).normalized();
	W3D::Math::fVec3 cameraUp = (W3D::Math::fVec3::cross(fwd, cameraRight)).normalized();


	camera->view = W3D::Math::Mat4::LookAt(transform->position, transform->position + fwd, cameraUp);

}
