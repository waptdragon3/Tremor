#include "w3d/graphics/Renderer.h"
#include "w3d/math/Mat4.h"
#include "w3d/graphics/Camera.h"
#include "w3d/graphics/Shader.h"
#include "w3d/graphics/Mesh.h"

namespace W3D::Graphics
{

	namespace Renderer
	{
		Camera* mainCamera;
		void setCamera(Camera* c)
		{
			mainCamera = c;
		}

		void render(Model* mesh, Shader* shader)
		{
			W3D::Math::Mat4 view;

			shader->setMatrix("view", mainCamera->getViewMatrix());

			mesh->Draw(shader);
		}



	}
}