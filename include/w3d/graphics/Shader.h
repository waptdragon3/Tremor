#pragma once
#include <string>

namespace W3D::Math
{
    class Transform;
}

namespace W3D::Graphics
{
    class Shader
    {
    public:
        // the program ID
        unsigned int ID;

        // constructor reads and builds the shader
        Shader(const char* vertexCode, const char* fragmentCode);
        // use/activate the shader
        void use();
        // utility uniform functions
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;

        void setMatrix(const std::string& name, W3D::Math::Transform value) const;

        static Shader fromFile(const char* vertexPath, const char* fragmentPath);
    };

}