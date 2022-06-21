#include "w3d/util/Time.h"
#include <GLFW/glfw3.h>


namespace W3D
{
    namespace Time
    {
        double lastFrame = 0.0;
        float dt = 0.0f;

        float DTime()
        {
            return dt;
        }

        void update()
        {
            double d = glfwGetTime();
            dt = static_cast<float>(d - lastFrame);

            lastFrame = d;
        }
    }
}