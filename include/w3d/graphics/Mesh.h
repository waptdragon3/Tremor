#pragma once
#include <string>
#include <vector>

#include "w3d/math/fVec2.h"
#include "w3d/math/fVec3.h"
#include "w3d/math/Transform.h"

#include "w3d/util/DynamicList.h"


namespace W3D::Graphics
{
	class Shader;
	class Model;
	namespace Renderer
	{
		void render(Model* mesh, Shader* shader);
	}

	struct Vertex
	{
		W3D::Math::fVec3 position;
		W3D::Math::fVec3 normal;
		W3D::Math::fVec2 uvCoords;
	};
	struct Texture
	{
		enum class TextureType
		{
			Invalid, Diffuse, Specular
		};
		unsigned int ID;
		TextureType type = TextureType::Invalid;
		std::string path;
	};

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> verts, std::vector<unsigned int> inds, std::vector<Texture> texs);
		Mesh() {}
	private:
		friend class Model;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		unsigned int VAO, VBO, EBO;
		void Draw(Shader* shader);

		void setupMesh();
	};


	class Model
	{
	private:


	public:
		Model(std::string path);
	private:
		std::vector<Mesh> meshes;
		std::string directory;


		void loadModel(std::string fileName);
		void Draw(Shader* shader);
		W3D::Math::Transform transform;


		Model():transform(W3D::Math::Transform::Identity()) { }
		friend void Renderer::render(Model* mesh, Shader* shader);
	};

}