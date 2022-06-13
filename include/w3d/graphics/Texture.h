#pragma once

namespace W3D::Graphics
{
	class Texture
	{
	public:
		Texture(const char* fileName);
		void bind();
	private:
		int width, height;
		unsigned int OGLtextureID;
	};

	class TextureManager
	{
	public:

	private:

	};
}