#include "components/PlayerControllerCmpt.h"
#include "w3d/component/ComponentManager.h"

#include "w3d/input/Input.h"
#include "w3d/util/Time.h"
#include "w3d/math/fVec2.h"

void PlayerControllerCmpt::start()
{
	transform = cManager->getComponentTypeOnEntity<TransformCmpt>(controllingEntity);
	cameraController = cManager->getComponentTypeOnEntity<CameraControllerCmpt>(controllingEntity);
}

void PlayerControllerCmpt::update()
{
	W3D::Math::fVec3 movement;
	if (W3D::Input::Keyboard::isInputDown("forward"))	movement += transform->Forward();
	if (W3D::Input::Keyboard::isInputDown("left"))		movement += transform->Left();
	if (W3D::Input::Keyboard::isInputDown("right"))		movement += -transform->Left();
	if (W3D::Input::Keyboard::isInputDown("backward"))	movement += -transform->Forward();


	//if (W3D::Input::Keyboard::isInputDown("jump"))		movement += transform->Up();
	if (W3D::Input::Keyboard::isInputDown("crouch"))	movement += -transform->Up();

	if (std::abs(movement.sqrMag()) > 0.5f)
	{
		W3D::Math::fVec3 dir = movement.normalized();
		transform->position += dir * W3D::Time::DTime() * moveSpeed;
	}

	W3D::Math::fVec2 look;

	if (W3D::Input::Keyboard::isInputDown("lookLeft"))	look.x += xSensitivity;
	if (W3D::Input::Keyboard::isInputDown("lookRight"))	look.x -= xSensitivity;


	if (W3D::Input::Keyboard::isInputDown("lookUp"))	look.y -= ySensitivity;
	if (W3D::Input::Keyboard::isInputDown("lookDown"))	look.y += ySensitivity;



	if (std::abs(look.sqrMag()) > 0.5f)
	{
		rot += look * W3D::Time::DTime();

		cameraController->pitch = look.y;
		cameraController->yaw = look.x;

		//transform->rotation.rotateAround(transform->Left(), look.y * W3D::Time::DTime() * ySensitivity);
		//transform->rotation.rotateAround(W3D::Math::fVec3::Up(), look.x * W3D::Time::DTime() * xSensitivity);
	}
	transform->rotation.reset();
	transform->rotation.rotateAround(W3D::Math::fVec3::Up(), rot.x);
	W3D::Math::fVec3 left = transform->Left();
	printf("Left = <%f, %f, %f>\n", left.x, left.y, left.z);
	transform->rotation.rotateAround(left, rot.y);



	if (W3D::Input::Keyboard::isInputDown("jump"))
	{
		rot = W3D::Math::fVec2();
		transform->position = W3D::Math::fVec3::Zero();
	}

}
