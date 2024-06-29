#include "shared/Admin.hpp"

int main(int argc, char* argv[]){
    system("cls");
    static Admin admin;
    std::cout << "commands:\n *add_job <title> <skills>\n *delete_job <id> [provide id of the job you wish to delete]\n";
    std::cout << " *modify_job_title <id> <new title> [provide id of the job] [the new title you wish to set]\n";
    std::cout << " *view_jobs\n";
    std::cout << " *view_candidates [provide id of the job]" << std::endl;
    if(argc < 2){
        std::cout << "Usage: ./app1.exe <command> [arguments]" << std::endl; 
        return 1;
    }
    std::string command = argv[1];

    if(command == "add_job"){
        system("cls");
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
    else if (command=="view_jobs"){
        system("cls");
        if(argc != 2){
            std::cout << "Usage: ./app1.exe view_jobs";
            return 1;
        }
        admin.viewJobs();
    }
    else if (command=="delete_job"){
        system("cls");
        if(argc != 3){
            std::cout << "Usage: ./app1.exe delete_job <ID>";
            return 1;
        }
        try
        {
            admin.deleteJob(std::stoi(argv[2]));
        }
        catch(const std::invalid_argument&)
        {
            std::cerr << "Idmust be an integer." << '\n';
        }
        
    }
    else if (command=="modify_job_title"){
        system("cls");
        if(argc != 4){
            std::cout << "Usage: ./app1.exe modify_job_title <ID> <new title>";
            return 1;
        }
        try{
            admin.modifyJobTitle(std::stoi(argv[2]), argv[3]);
        }catch(const std::invalid_argument&){
            std::cerr << "Id must be an integer." << '\n';
        }
    }
    else if(command=="view_candidates"){
        system("cls");
        if(argc != 3){
            std::cout << "Usage: ./app1.exe view_candidates <ID>";
            return 1;
        }
        try
        {
            admin.viewCandidates(std::stoi(argv[2]));
        }catch(const std::exception&)
        {
            std::cerr << "Id must be an integer." << '\n';
        }
        
    }
}