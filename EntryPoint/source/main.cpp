//#include "ZtEntryPoint.h"
#include "ZtVulkanHelloTriangle.h"

int main()
{
    //ZtEntryPoint EntryPoint;
    //EntryPoint.Start();

    ZtVulkanHelloTriangle App;

    try 
    {
        App.Run();
    }
    catch (const std::exception& Ex) 
    {
        std::cerr << Ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}