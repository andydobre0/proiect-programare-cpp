#include "shared/Admin.hpp"

int main(int argc, char* argv[]){
    Admin admin;
    std::cout << "commands:\n *add_job\n *delete_job [provide id of the job you wish to delete]\n";
    std::cout << " *modify_job [provide id of the job you wish to delete]\n";
    if(argc < 2){
        std::cout << "Usage: ./app1.exe <command> [arguments]" << std::endl; 
        return 1;
    }
    std::string command = argv[1];

    if(command == "add_job"){
        if(argc != 4){
            std::cout << "Usage: ./app1.exe add_job <title> <skills>" << std::endl;
            return 1;
        }
        std::string title = argv[2];
        std::string skills = argv[3];
        std::vector<std::string> skillsVector;
        std::istringstream iss(skills);
        std::string skill;
        while(std::getline(iss, skill, ','))
            skillsVector.push_back(skill);
        admin.addJob(title, skillsVector);
    }
}