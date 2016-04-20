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

string TWILIO_NUM = "+17572315125";

using namespace std;
using namespace Mongoose;

class MyController : public WebController {
    public:
        void receive_sms(Request &request, StreamResponse &response) {
				//cerr << "URL: " << request.getUrl() << "\n";
				//cerr << "Method: " << request.getMethod() << "\n";
				//cerr << "Data: " << request.getData() << "\n";

				map<string, string> myMap = request.getAllVariable();
				for(auto elem : myMap) {
   				cerr << elem.first << " " << elem.second << "\n";
				}
				response << form_sms_response("+1" + myMap["From"].erase(0,3), "Test successful: " + myMap["Body"]);
        }

		  string form_sms_response(string to, string message) {
				string sms = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
				sms += "<Response>";
				sms += "<Sms from=\"" + TWILIO_NUM + "\" to=\"" + to + "\">" + message + "</Sms>";
				sms += "</Response>";
				return sms;
		  }

		  void send_sms() {
			  /*

			  curl -X POST 'https://api.twilio.com/2010-04-01/Accounts/{Account SID}/Messages.xml' \
				> --data-urlencode 'To=+17579683627'  \
				> --data-urlencode 'From=+17572315125'  \
				> --data-urlencode 'Body=This is a curl test.' \
				> -u {Account SID}:25c4d5dbc8f0f8a6cb37c39156ce97cf

				*/
		  }

		  void receive_im(Request &request, StreamResponse &response) {
			  map<string, string> myMap = request.getAllVariable();
			  for(auto elem : myMap) {
				  cerr << elem.first << " " << elem.second << "\n";
			  }
		  }

        void setup() {
            addRoute("POST", "/receive_sms", MyController, receive_sms);
				addRoute("POST", "/receive_im", MyController, receive_im);
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
