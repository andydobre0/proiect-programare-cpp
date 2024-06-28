#include "User.hpp"
#include<fstream>
#include<sstream>

User::User(int id, const std::string& name, const std::string& email) : id(id), name(name), email(email){}

void User::viewJobs(){
    if(announcements.empty()) {
        std::cout << "No jobs available." << std::endl;
        return;
    }
    for(const auto& announcement : announcements){
        std::cout << "ID: " << announcement.getId() << ", Title: " << announcement.getTitle() << ", Skills: ";
        const auto& skills = announcement.getSkills();
        for(size_t i = 0; i < skills.size(); ++i) {
            std::cout << skills[i];
            if(i < skills.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
}