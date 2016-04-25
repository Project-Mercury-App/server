#ifdef _MSC_VER
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <map>
#include <mongoose/Server.h>
#include <mongoose/WebController.h>
#include <pqxx/pqxx>
#include "databaseQueries.cpp"

string TWILIO_NUM = "+17572315125";

using namespace std;
using namespace Mongoose;
using namespace pqxx;

string strcast(char* str_) {
  string str = str_;
  return str;
}

class MyController : public WebController {
    public:
      void twilio(Request &request, StreamResponse &response) {
  			//cerr << "URL: " << request.getUrl() << "\n";
  			//cerr << "Method: " << request.getMethod() << "\n";
  			//cerr << "Data: " << request.getData() << "\n";

				map<string, string> myMap = request.getAllVariable();
				for(auto elem : myMap) {
   				cerr << elem.first << " " << elem.second << "\n";
				}
        try {

        }
        catch(const std::exception &e) {
          response << "ERROR: " << e.what();
        }
				response << form_sms_response("+1" + myMap["From"].erase(0,3), "Test successful: " + myMap["Body"]);
      }

      void http(Request &request, StreamResponse &response) {
        map<string, string> myMap = request.getAllVariable();
        string r = "";
        for(auto elem : myMap) {
          r += "\n" + elem.first + ": " + elem.second;
   				cerr << elem.first << ": " << elem.second << "\n";
				}
        try {

        }
        catch(const std::exception &e) {
          response << "ERROR: " << e.what();
        }
        response << r;
      }

		  string form_sms_response(string to, string message) {
				string sms = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
				sms += "<Response>";
				sms += "<Sms from=\"" + TWILIO_NUM + "\" to=\"" + to + "\">" + message + "</Sms>";
				sms += "</Response>";
				return sms;
		  }

		  void send_sms(string phone_number, string msg) {
			  /*

			  curl -X POST 'https://api.twilio.com/2010-04-01/Accounts/{Account SID}/Messages.xml' \
				> --data-urlencode 'To=+17579683627'  \
				> --data-urlencode 'From=+17572315125'  \
				> --data-urlencode 'Body=This is a curl test.' \
				> -u {Account SID}:25c4d5dbc8f0f8a6cb37c39156ce97cf

				*/
		  }

      void send_im() {

      }



		  void send_message(Request &request, StreamResponse &response) {
			  map<string, string> myMap = request.getAllVariable();
			  for(auto elem : myMap) {
				  cerr << elem.first << " " << elem.second << "\n";
			  }
        //getGroup
        //postMessage
		  }

      void post_message(double group_id, string msg) {
        //database INSERT
        send_message_to_members(group_id, msg);
      }

      void send_message_to_members(double group_id, string msg) {
        //getGroup
        //for all users in group
          //send message
      }

      void authenticate(Request &request, StreamResponse &response) {
        map<string, string> myMap = request.getAllVariable();
        try {
          //TODO: If user exists, return id
        }
        catch(const std::exception &e) {
          //TODO: If not, create user and return id
        }
      }

      void get_all_groups(Request &request, StreamResponse &response) {
        map<string, string> myMap = request.getAllVariable();

        std::string::size_type sz;     // alias of size_t
        double user_id = std::stod (myMap["user_id"], &sz);

        try {
          pqxx::result r = Query::getGroupsFromUser(user_id);
          response << r.query();
        }
        catch(const std::exception &e) {
          response << "ERROR: " << e.what();
        }
      }

      void get_user(Request &request, StreamResponse &response) {
        map<string, string> myMap = request.getAllVariable();

        std::string::size_type sz;     // alias of size_t
        double user_id = std::stod (myMap["user_id"], &sz);

        try {
          pqxx::result r =  Query::getUser(user_id);
          response << r.query();
        }
        catch(const std::exception &e) {
          response << "ERROR: " << e.what();
        }
      }

      void get_group(Request &request, StreamResponse &response) {
        map<string, string> myMap = request.getAllVariable();

        std::string::size_type sz;     // alias of size_t
        double group_id = std::stod (myMap["group_id"], &sz);

        try {
          pqxx::result r =  Query::getGroupInfo(group_id);
          response << r.query();
        }
        catch(const std::exception &e) {
          response << "ERROR: " << e.what();
        }
      }

      void create_group(Request &request, StreamResponse &response) {
        map<string, string> myMap = request.getAllVariable();
        try {
          Query::createGroup(myMap["group_name"]);
          //TODO: What is the group's id?
          response << myMap["group_name"];
        }
        catch(const std::exception &e) {
          response << "ERROR: " << e.what();
        }
      }

      void setup() {
          addRoute("POST", "/twilio", MyController, twilio);
          addRoute("POST", "/http", MyController, http);
          addRoute("POST", "/send_message", MyController, send_message);
          addRoute("POST", "/authenticate", MyController, authenticate);
  				addRoute("POST", "/get_all_groups", MyController, get_all_groups);
  				addRoute("POST", "/get_user", MyController, get_user);
  				addRoute("POST", "/get_group", MyController, get_group);
  				addRoute("POST", "/create_group", MyController, create_group);

			/*
				Authentication - if successful, return user object with id, email, name
				Get all groups - return array of all those fields in the database
				Get a user given user id
				Get group given group id
				Get all messages given a group
				Create a group
			*/
      }
};


int main() {

	try {
    //host=pdc-amd01.poly.edu dbname=sw2371 user=jsw407 password=ecrnpazb
		connection C("host=" + strcast(getenv("pghost")) + " dbname=" + strcast(getenv("pgdbname")) + " user=" + strcast(getenv("pguser")) + " password=" + strcast(getenv("pgpassword")));
		cout << "Connected to " << C.dbname() << endl;
		/*
		work W(C);

		result R = W.exec("SELECT name FROM employee");

		cout << "Found " << R.size() << "employees:" << endl;
		for (result::const_iterator r = R.begin();
		     r != R.end();
		     ++r)
		{
			cout << r[0].c_str() << endl;
		}

		cout << "Doubling all employees' salaries..." << endl;
		W.exec("UPDATE employee SET salary=salary*2");

		cout << "Making changes definite: ";
		W.commit();
		cout << "ok." << endl;
		*/
	}
	catch (const exception &e) {
		cerr << e.what() << endl;
		return 1;
	}

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
