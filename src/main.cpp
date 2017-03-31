#include "Application.h"

#ifdef __WIN32
#include "windows.h"
#endif // __WIN32

namespace
{
    void errorMessage(const std::string& message)
    {
        #ifdef __WIN32
            MessageBox(nullptr, message.c_str(), "Error", MB_OK);
        #else // __WIN32
            std::cerr << message << std::endl;
            std::cin.ignore();
        #endif
    }
}

int main() try
{
	Application app("Community Game", { 800, 600, true, VSYNC_DISABLED });
	app.start();

	return EXIT_SUCCESS;
}
catch(std::out_of_range& e)
{
    std::string msg = e.what();
    errorMessage(msg);
    std::cin.ignore();
}
catch(std::runtime_error& e)
{
    std::string msg = e.what();
    errorMessage(msg);
    std::cin.ignore();
}
catch(...)
{
    errorMessage("Unknown error.");
    std::cin.ignore();
}


/*
This project is maintained by the  Community on Hopson97's Discord server.
The people who are currently working together on this are:
    KiddieD,
    Esscoder,byujh
    ans66f,
    DCubix,
    DarkCart,
    RagingRabbit,
    kaizi99,
    Pol_hp,
	Repertoi-e
*/
