#include "components/BackAndForthCmpt.h"
#include "w3d/component/ComponentManager.h"
#include <cmath>
#include "w3d/util/Time.h"

float lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

void BAFCmpt::start()
{
	transform = dynamic_cast<TransformCmpt*>(cManager->getComponentTypeOnEntity<TransformCmpt>(controllingEntity));
	totalTime = 0.0f;
}

void BAFCmpt::update()
{
	W3D::Math::fVec3 pos;
	totalTime += W3D::Time::DTime();
	float rads = (totalTime / pathLengthTime) * 2 * 3.14159f;
	float t = (std::sin(rads) + 1) / 2;
	pos.x = lerp(pathStart.x, pathEnd.x, t);
	pos.y = lerp(pathStart.y, pathEnd.y, t);
	pos.z = lerp(pathStart.z, pathEnd.z, t);

	transform->position = pos;

	if (totalTime > pathLengthTime)
	{
		totalTime -= pathLengthTime;
	}

}
