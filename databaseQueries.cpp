//NOTE: These will only get 
#include <iostream>
#include <string>
#include <pqxx/pqxx>

pqxx::result getUser(double user_id, pqxx::connection_base &c){//Gets all information on a user given a user id
	try{
		std::string s = "SELECT * FROM users WHERE user_id = " + user_id + ";";
		pqxx::transaction_base t = transaction_base(c);
		c.prepare("get_user", s);
		pqxx::result r = t.prepared("get_user").exec();
		t.commit();

		return r;
	}
	catch (const std::exception &e){
	}
}

pqxx::result getUserFromEmail(std::string email, pqxx::connection &c){//Gets user from email address
	try{
		std::string s = "SELECT * FROM users WHERE email = " + email + ";";
		pqxx::transaction_base t = transaction_base(c);
		c.prepare("get_user_email", s);
		pqxx::result r = t.prepared("get_user_email").exec();
		t.commit();

		return r;
	}
	catch (const std::exception &e){
	}
}

pqxx::result getGroupsFromUser(double user_id, pqxx::connection &c){ //Gets all groups a user is a member of
	try{
		std::string s = "SELECT * FROM groups natural join membership WHERE user_id = " + user_id + ";"
		pqxx::transaction_base t = transaction_base(c);
		c.prepare("get_user_groups", s);
		pqxx::result r = t.prepared("get_user_groups").exec();
		t.commit();
		
		return r;
	}
	catch (const std::exception &e){
	}
}

pqxx::result getGroupInfo(double group_id, pqxx::connection &c){//Gets all of a groups info 
	try{
		std::string s = "SELECT * FROM groups WHERE group_id = " + group_id + ";";
		pqxx::transaction_base t = transaction_base(c);
		c.prepare("get_group_info", s);
		pqxx::result r = t.prepared("get_group_info").exec();
		t.commit();
		
		return r;
	}
	catch (const std::exception &e){
	}
}

bool createGroup(std::string group_name, pqxx::connection &c){//Creates a new group called "group_name" Returns true if it suceeds
	try{
		std::string s = "INSERT INTO groups (group_name) VALUES (" + group_name + ");";
		pqxx::transaction_base t  = transaction_base(c);
		c.prepare("create_group", s);
		t.prepared("create_group").exec();
		t.commit();
		
		return true;
	}
	catch (const std::exception &e){
		return false;
	}
}

pqxx::result getUsersFromGroup(double group_id, pqxx::connection &c){
	try{
		std::string s  = "SELECT user_id FROM membership WHERE group_id = " + group_id + ";";
		pqxx::transaction_base t = transaction_base(c);
		c.prepare("get_group_users", s);
		pqxx::result r = t.prepared("get_group_users").exec();
		t.commit();
		
		return r;
	}
	catch (const std::exception &e){
	}
}

pqxx::result getMessages(double group_id){
	try{
		std::string s  = "SELECT * FROM messages WHERE group_id = " + group_id + " ORDER BY message_time;";
		pqxx::transaction_base t = transaction_base(c);
		c.prepare("get_messages", s);
		pqxx::result r = t.prepared("get_messages");
		t.commit();
	}
	catch (const std::exception &e){
	}
}

bool addMessage(double group_id, double user_id, std::string message_text, pqxx::connection c){
	try{
		std::string s = "INSERT INTO messages (message_time, user_id, group_id) VALUES (CURRENT_TIMESTAMP, " + user_id + ", " + group_id + ");";
		pqxx::transaction_base t = transaction_base(c);
		c.prepare("add_message", s);
		pqxx::result r = t.prepared("add_message");
		t.commit();
		
		return true;
	}
	catch (const std::exception &e){
		return false;
	}
}