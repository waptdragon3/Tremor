

namespace W3D::Graphics
{
	class Camera;
	class Shader;

	class Model;

	namespace Renderer
	{
		void setCamera(Camera* c);

		void render(Model* mesh, Shader* shader);
	}

}