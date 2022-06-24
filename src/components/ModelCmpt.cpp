#include "components/ModelCmpt.h"
#include "w3d/component/ComponentManager.h"
#include "w3d/graphics/Renderer.h"

void ModelCmpt::start()
{
	transform = dynamic_cast<TransformCmpt*>(cManager->getComponentTypeOnEntity<TransformCmpt>(controllingEntity));
}

void ModelCmpt::update()
{
	shader->setMatrix("object", transform->getMatrix());

	W3D::Graphics::Renderer::render(model, shader);
}
