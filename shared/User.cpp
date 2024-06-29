#include "User.hpp"
#include<fstream>
#include<sstream>


int User::userCount = 0;

User::User(const std::string& email) : email(email) {
    loadUserCount();
    id = userCount + 1;
}

void User::applyForJob(int jobId) {
    std::ifstream jobsFile("shared/jobs.csv");
    if (!jobsFile.is_open()) {
        std::cout << "Error: Unable to open jobs file." << std::endl;
        return;
    }

    std::string line;
    std::getline(jobsFile, line);
    bool jobExists = false;
    while (std::getline(jobsFile, line)) {
        std::stringstream ss(line);
        std::string idStr;
        std::getline(ss, idStr, ',');
        if (std::stoi(idStr) == jobId) {
            jobExists = true;
            break;
        }
    }
    jobsFile.close();

    if (!jobExists) {
        std::cout << "Error: Job with ID " << jobId << " does not exist." << std::endl;
        return;
    }

    std::ifstream usersFile("shared/users.csv");
    std::vector<std::string> lines;
    bool userFound = false;
    bool alreadyApplied = false;
    int currentUserCount = 0;

    if (usersFile.is_open()) {
        std::string line;
        
        std::getline(usersFile, line);
        currentUserCount = std::stoi(line);
        lines.push_back(line);

        while (std::getline(usersFile, line)) {
            std::stringstream ss(line);
            std::string idStr, userEmail;
            std::getline(ss, idStr, ',');
            std::getline(ss, userEmail, ',');

            if (userEmail == email) {
                userFound = true;
                std::string appliedJobId;
                while (std::getline(ss, appliedJobId, ',')) {
                    if (std::stoi(appliedJobId) == jobId) {
                        alreadyApplied = true;
                        break;
                    }
                }
                if (!alreadyApplied) {
                    line += "," + std::to_string(jobId);
                }
            }
            lines.push_back(line);
        }

        usersFile.close();

        if (!userFound && !alreadyApplied) {
            currentUserCount++;
            id = currentUserCount;
            lines[0] = std::to_string(currentUserCount);
            lines.push_back(std::to_string(id) + "," + email + "," + std::to_string(jobId));
        }

        std::ofstream outFile("shared/users.csv");
        if (outFile.is_open()) {
            for (const auto& line : lines) {
                outFile << line << std::endl;
            }
            outFile.close();

            if (alreadyApplied) {
                std::cout << "You have already applied for job with ID: " << jobId << std::endl;
            } else {
                std::cout << "Successfully applied for job with ID: " << jobId << std::endl;
                if (!userFound) {
                    std::cout << "New user account created with ID: " << id << std::endl;
                }
            }
        } else {
            std::cout << "Error: Unable to open users file for writing." << std::endl;
        }
    } else {
        std::cout << "Error: Unable to open users file for writing." << std::endl;
    }
}

void User::filterJobs(const std::string& skill) {
    std::ifstream jobsFile("shared/jobs.csv");
    if (!jobsFile.is_open()) {
        std::cout << "Error: Unable to open jobs file." << std::endl;
        return;
    }

    std::string line;
    std::getline(jobsFile, line);

    bool found = false;
    while (std::getline(jobsFile, line)) {
        std::stringstream ss(line);
        std::string idStr, title, currentSkill;
        
        std::getline(ss, idStr, ',');
        std::getline(ss, title, ',');
        
        while (std::getline(ss, currentSkill, ',')) {
            if (currentSkill == skill) {
                std::cout << "ID: " << idStr << ", Title: " << title << ", Skills: ";
                std::cout << skill;
                while (std::getline(ss, currentSkill, ',')) {
                    if (!currentSkill.empty()) {
                        std::cout << ", " << currentSkill;
                    }
                }
                std::cout << std::endl;
                found = true;
                break;
            }
        }
    }

    jobsFile.close();

    if (!found) {
        std::cout << "No jobs found with the skill: " << skill << std::endl;
    }
}

int User::getUserCount() {
    return userCount;
}

void User::incrementUserCount() {
    userCount++;
}

void User::loadUserCount() {
    std::ifstream usersFile("shared/users.csv");
    if (usersFile.is_open()) {
        std::string line;
        if (std::getline(usersFile, line)) {
            userCount = std::stoi(line);
        }
        usersFile.close();
    }
}

void User::saveUserCount() {
    std::ofstream usersFile("shared/users.csv", std::ios::in | std::ios::out);
    if (usersFile.is_open()) {
        usersFile.seekp(0);
        usersFile << userCount << std::endl;
        usersFile.close();
    }
}

void User::viewJobs() {
    std::ifstream jobsFile("shared/jobs.csv");
    if (!jobsFile.is_open()) {
        std::cout << "Error: Unable to open jobs file." << std::endl;
        return;
    }

    std::string line;
    std::getline(jobsFile, line);

    while (std::getline(jobsFile, line)) {
        std::stringstream ss(line);
        std::string idStr, title, skill;
        
        std::getline(ss, idStr, ',');
        std::getline(ss, title, ',');
        
        std::cout << "ID: " << idStr << "\n     Title: " << title << ", Skills: ";
        
        bool firstSkill = true;
        while (std::getline(ss, skill, ',')) {
            if (skill.empty()) break;
            if (!firstSkill) std::cout << ", ";
            std::cout << skill;
            firstSkill = false;
        }
        std::cout << std::endl;
    }

    jobsFile.close();
}