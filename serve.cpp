#ifdef _MSC_VER
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <stdlib.h>
#include <signal.h>
#include <map>
#include <mongoose/Server.h>
#include <mongoose/WebController.h>

using namespace std;
using namespace Mongoose;

class MyController : public WebController
{
    public:
        void hello(Request &request, StreamResponse &response)
        {
				cerr << "URL: " << request.getUrl() << "\n";
				cerr << "Method: " << request.getMethod() << "\n";
				cerr << "Data: " << request.getData() << "\n";

				map<string, string> myMap = request.getAllVariable();
				for(auto elem : myMap)
				{
   				cerr << elem.first << " " << elem.second << "\n";
				}

         	response << "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Response><Sms from=\"+17572315125\" to=\"+17579683627\">The message transfer was successful.</Sms></Response>" << endl;
        }

        void setup()
        {
            addRoute("POST", "/", MyController, hello);
				addRoute("GET", "/", MyController, hello);
        }
};


int main()
{
    MyController myController;
    Server server(8080);
    server.registerController(&myController);

    server.start();

    while (1) {
#ifdef WIN32
		Sleep(10000);
#else
        sleep(10);
#endif
    }
}
