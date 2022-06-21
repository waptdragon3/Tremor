#include <glad/glad.h>
#include <iostream>
#include "w3d/graphics/Mesh.h"
#include "w3d/graphics/Shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define STB_IMAGE_IMPLEMENTATION
#include "w3d/graphics/stb_image.h"

std::vector<W3D::Graphics::Texture> textures_loaded;

unsigned int TextureFromFile(const char* fileName, const std::string& directory, bool gamma = false)
{
	std::string path = directory + '/' + std::string(fileName);

	unsigned int ID = 0;
	//generate texture
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//load texture
	int nrChannels, width, height;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data != nullptr)
	{
		//send texture to gpu
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load image" << std::endl;
	}
	stbi_image_free(data);

	return ID;
}

std::vector<W3D::Graphics::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, W3D::Graphics::Texture::TextureType textureType, std::string& directory)
{
	std::vector<W3D::Graphics::Texture> textures;
	//textures.resize(mat->GetTextureCount(type));

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			W3D::Graphics::Texture texture;
			texture.ID = TextureFromFile(str.C_Str(), directory);
			texture.type = textureType;
			texture.path = std::string(str.C_Str());

			textures_loaded.push_back(texture);
			textures.push_back(texture);
		}
	}
	return textures;
}



W3D::Graphics::Mesh processMesh(aiMesh* mesh, const aiScene* scene, std::string& directory)
{
	//initialize our lists
	std::vector<W3D::Graphics::Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<W3D::Graphics::Texture> textures;

	//process verts
	//vertices.resize(mesh->mNumVertices); //resize to expected size now to save resizing later
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		W3D::Graphics::Vertex vertex;

		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;

		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0])
		{
			vertex.uvCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.uvCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertex.uvCoords = W3D::Math::fVec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	//process indices
	indices.resize(mesh->mNumFaces * 3); //resize to expected size now to save resizing later. assume all faces are triangles
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	//process materials
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<W3D::Graphics::Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, W3D::Graphics::Texture::TextureType::Diffuse, directory);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<W3D::Graphics::Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, W3D::Graphics::Texture::TextureType::Specular, directory);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return W3D::Graphics::Mesh(vertices, indices, textures);
}

std::vector<W3D::Graphics::Mesh> processNode(aiNode* node, const aiScene* scene, std::string& directory)
{
	std::vector<W3D::Graphics::Mesh> meshes;

	//process current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		W3D::Graphics::Mesh convertedMesh = processMesh(mesh, scene, directory);
		meshes.push_back(convertedMesh);
	}
	//and its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		std::vector<W3D::Graphics::Mesh> children = processNode(node->mChildren[i], scene, directory);
		meshes.insert(meshes.end(), children.begin(), children.end());
	}

	return meshes;
}




W3D::Graphics::Mesh::Mesh(std::vector<Vertex> verts, std::vector<unsigned int> inds, std::vector<Texture> texs)
{
	vertices = verts;
	indices = inds;
	textures = texs;

	setupMesh();
}

void W3D::Graphics::Mesh::Draw(Shader* shader)
{
	unsigned int numDiffuse = 1;
	unsigned int numSpecular = 1;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		//activate proper tecture unit before binding
		glActiveTexture(GL_TEXTURE0 + i);

		//retrieve texture number (the N in diffuse_textureN)
		std::string texName;
		switch (textures[i].type)
		{
		case Texture::TextureType::Diffuse:
			texName = "texture_diffuse" + std::to_string(numDiffuse++);
			break;
		case Texture::TextureType::Specular:
			texName = "texture_specular" + std::to_string(numSpecular++);
			break;
		default:
			break;
		}
		shader->setInt(texName, i);
		glBindTexture(GL_TEXTURE_2D, textures[0].ID);
	}

	glActiveTexture(0);

	//draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

void W3D::Graphics::Mesh::setupMesh()
{
	//gen our buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind the VAO
	glBindVertexArray(VAO);

	//send vertex data to GPU
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	//send index data to GPU
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//set up vertex attribs
	//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	//normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	//UV coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uvCoords));


	//unbind the VAO
	glBindVertexArray(0);
}

W3D::Graphics::Model::Model(std::string path):transform(W3D::Math::Transform::Identity())
{
	loadModel(path);
}

void W3D::Graphics::Model::loadModel(std::string path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));

	meshes = processNode(scene->mRootNode, scene, directory);
}

void W3D::Graphics::Model::Draw(Shader* shader)
{
	shader->setMatrix("model", this->transform);

	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}
