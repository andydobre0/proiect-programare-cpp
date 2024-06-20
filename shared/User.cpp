#include "User.hpp"
#include<fstream>
#include<sstream>

User::User(int id, const std::string& name, const std::string& email) : id(id), name(name), email(email){}