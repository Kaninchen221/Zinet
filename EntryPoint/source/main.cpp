
#include "Zinet/GraphicLayer/ZtGLRenderer.h"

int main()
{
	zt::gl::Renderer renderer;
	renderer.contentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";
	renderer.prepare();
	renderer.run();

    return 0;
}