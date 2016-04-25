//NOTE: These will only get
#include <iostream>
#include <string>
#include <pqxx/pqxx>

namespace Query {

	pqxx::result getUser(double user_id){//Gets all information on a user given a user id
		pqxx::result r;
		try{
			pqxx::connection c;
			pqxx::work w(c);
			r = w.exec("SELECT * FROM users WHERE user_id = " + to_string(user_id) + ";");
			w.commit();

		}
		catch (const std::exception &e){
		}
		return r;
	}

	pqxx::result getUserFromEmail(std::string email){//Gets user from email address
		pqxx::result r;
		try{
			pqxx::connection c;
			pqxx::work w(c);
			r = w.exec("SELECT * FROM users WHERE email = " + email + ";");
			w.commit();

		}
		catch (const std::exception &e){
		}
		return r;
	}

	pqxx::result getGroupsFromUser(double user_id){ //Gets all groups a user is a member of
		pqxx::result r;
		try{
			pqxx::connection c;
			pqxx::work w(c);
			r = w.exec("SELECT * FROM groups natural join membership WHERE user_id = " + to_string(user_id) + ";");
			w.commit();

		}
		catch (const std::exception &e){
		}
		return r;
	}

	pqxx::result getGroupInfo(double group_id){//Gets all of a groups info
		pqxx::result r;
		try{
			pqxx::connection c;
			pqxx::work w(c);
			r = w.exec("SELECT * FROM groups WHERE group_id = " + to_string(group_id) + ";");
			w.commit();

		}
		catch (const std::exception &e){
		}
		return r;
	}

	bool createGroup(std::string group_name){//Creates a new group called "group_name" Returns true if it suceeds
		pqxx::result r;
		try{
			pqxx::connection c;
			pqxx::work w(c);
			r = w.exec("INSERT INTO groups (group_name) VALUES (" + group_name + ");");
			w.commit();

		}
		catch (const std::exception &e){
			return false;
		}
		return true;
	}

	pqxx::result getUsersFromGroup(double group_id){
		pqxx::result r;
		try{
			pqxx::connection c;
			pqxx::work w(c);
			r = w.exec("SELECT user_id FROM membership WHERE group_id = " + to_string(group_id) + ";");
			w.commit();
		}
		catch (const std::exception &e){
		}
		return r;
	}

	pqxx::result getMessages(double group_id){
		pqxx::result r;
		try{
			pqxx::connection c;
			pqxx::work w(c);
			r = w.exec("SELECT * FROM messages WHERE group_id = " + to_string(group_id) + " ORDER BY message_time;");
			w.commit();
		}
		catch (const std::exception &e){
		}
		return r;
	}

	bool addMessage(double group_id, double user_id, std::string message_text){
		pqxx::result r;
		try{
			pqxx::connection c;
			pqxx::work w(c);
			r = w.exec("INSERT INTO messages (message_time, user_id, group_id) VALUES (CURRENT_TIMESTAMP, " + to_string(user_id) + ", " + to_string(group_id) + ");");
			w.commit();
		}
		catch (const std::exception &e){
			return false;
		}
		return true;
	}
}
