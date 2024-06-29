#include"shared/User.hpp"

int main(int argc, char* argv[]) {
    system("cls");
    std::cout << "commands:\n *view_jobs\n *filter_jobs <skill>\n *apply_job <job_id> <user_email>\n";
    if (argc < 2) {
        std::cout << "Usage: ./app2.exe <command> [arguments]" << std::endl;
        return 1;
    }

    std::string command = argv[1];

    if (command == "view_jobs") {
        system("cls");
        if (argc != 2) {
            std::cout << "Usage: ./app2.exe view_jobs" << std::endl;
            return 1;
        }
        User user;
        user.viewJobs();
    }
    else if (command == "filter_jobs") {
        system("cls");
        if (argc != 3) {
            std::cout << "Usage: ./app2.exe filter_jobs <skill>" << std::endl;
            return 1;
        }
        std::string skill = argv[2];
        User user;
        user.filterJobs(skill);
    }
    else if (command == "apply_job") {
        system("cls");
        if (argc != 4) {
            std::cout << "Usage: ./app2.exe apply_job <job_id> <user_email>" << std::endl;
            return 1;
        }
        try {
            int jobId = std::stoi(argv[2]);
            std::string userEmail = argv[3];
            User user(userEmail);
            user.applyForJob(jobId);
        }
        catch (const std::invalid_argument&) {
            std::cerr << "Job ID must be an integer." << std::endl;
        }
    }
    else {
        std::cout << "Unknown command. Available commands are: view_jobs, filter_jobs, apply_job" << std::endl;
    }

    return 0;
}