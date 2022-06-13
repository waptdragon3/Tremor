#include "core/components/BackAndForthCmpt.h"
#include "core/ComponentManager.h"
#include <cmath>
#include "graphics/GLFW.h"

float lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

void BAFCmpt::start()
{
	transform = dynamic_cast<TransformCmpt*>(cManager->getComponentTypeOnEntity<TransformCmpt>(controllingEntity));
}

void BAFCmpt::update()
{
	W3D::fVec3 pos;
	int numCycles = static_cast<int>(W3D::Graphics::GLFW::getTime() / pathLengthTime);
	float f = W3D::Graphics::GLFW::getTime() - (pathLengthTime * numCycles);
	float rads = (f / pathLengthTime) * 2 * 3.14159f;
	float t = (std::sin(rads) + 1) / 2;
	pos.x = lerp(pathStart.x, pathEnd.x, t);
	pos.y = lerp(pathStart.y, pathEnd.y, t);
	pos.z = lerp(pathStart.z, pathEnd.z, t);

	transform->position = pos;
}
