//NOTE: These will only get 
#include <iostream>
#include <string>
#include <pqxx/pqxx>

pqxx::result getUser(double user_id){//Gets all information on a user given a user id
	try{
		pqxx::connection c;
		pqxx::work w(c);
		pqxx::result r = w.exec("SELECT * FROM users WHERE user_id = " + user_id + ";");
		w.commit();
		return r;
	}
	catch (const std::exception &e){
	}
}

pqxx::result getUserFromEmail(std::string email){//Gets user from email address
	try{
		pqxx::connection c;
		pqxx::work w(c);
		pqxx::result r = w.exec("SELECT * FROM users WHERE email = " + email + ";");
		w.commit();
		return r;
	}
	catch (const std::exception &e){
	}
}

pqxx::result getGroupsFromUser(double user_id){ //Gets all groups a user is a member of
	try{
		pqxx::connection c;
		pqxx::work w(c);
		pqxx::result r = w.exec("SELECT * FROM groups natural join membership WHERE user_id = " + user_id + ";");
		w.commit();
		return r;
	}
	catch (const std::exception &e){
	}
}

pqxx::result getGroupInfo(double group_id){//Gets all of a groups info 
	try{
		pqxx::connection c;
		pqxx::work w(c);
		pqxx::result r = w.exec("SELECT * FROM groups WHERE group_id = " + group_id + ";");
		w.commit();
		return r;
	}
	catch (const std::exception &e){
	}
}

bool createGroup(std::string group_name){//Creates a new group called "group_name" Returns true if it suceeds
	try{
		pqxx::connection c;
		pqxx::work w(c);
		pqxx::result r = w.exec("INSERT INTO groups (group_name) VALUES (" + group_name + ");");
		w.commit();
		return true;
	}
	catch (const std::exception &e){
		return false;
	}
}

pqxx::result getUsersFromGroup(double group_id){
	try{
		pqxx::connection c:
		pqxx::work w(c);
		pqxx::result r = w.exec("SELECT user_id FROM membership WHERE group_id = " + group_id + ";");
		w.commit();
	}
	catch (const std::exception &e){
	}
}

pqxx::result getMessages(double group_id){
	try{
		pqxx::connection c :
		pqxx::work w(c);
		pqxx::result r = w.exec("SELECT * FROM messages WHERE group_id = " + group_id + " ORDER BY message_time;");
		w.commit();
	}
	catch (const std::exception &e){
	}
}

bool addMessage(double group_id, double user_id, std::string message_text){
	try{
		pqxx::connection c :
		pqxx::work w(c);
		pqxx::result r = w.exec("INSERT INTO messages (message_time, user_id, group_id) VALUES (CURRENT_TIMESTAMP, " + user_id + ", " + group_id + ");");
		w.commit();
		return true;
	}
	catch (const std::exception &e){
		return false;
	}
}