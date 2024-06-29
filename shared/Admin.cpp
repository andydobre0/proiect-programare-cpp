#include "Admin.hpp"
#include <algorithm>

Admin::Admin() : User(), jobCount(0) {
    std::ifstream jobsFile("shared/jobs.csv");
    if(jobsFile.is_open()){
        std::string line;
        if(std::getline(jobsFile, line)){
            jobCount = std::stoi(line);
        }
        while(std::getline(jobsFile, line)){
            std::stringstream ss(line);
            std::string idStr, title;
            std::getline(ss, idStr, ',');
            std::getline(ss, title, ',');
            int id = std::stoi(idStr);
            Job job(id, title);

            std::string skill;
            while(std::getline(ss, skill, ','))
                job.setSkill(skill);
            
            // std::string candidate;
            // while (std::getline(ss, candidate, ','))
            //     job.addCandidate(candidate);
            
            announcements.push_back(job);
        }
        jobsFile.close();
    }
    jobCount = announcements.size();
}

void Admin::modifyFile(){
    std::ofstream jobsFile("shared/jobs.csv");
    if(jobsFile.is_open()){
        jobsFile << jobCount << std::endl;
        for(const auto& job: announcements){
            jobsFile << job;
        }   
        jobsFile.close();   
    }
    std::cout << "Operation successful" << std::endl;
}

void Admin::addJob(const std::string& title, const std::vector<std::string>& skills){
    auto it = std::find_if(announcements.begin(), announcements.end(),
                           [&title](const Job& job) { return job.getTitle() == title; });
    if (it != announcements.end()) {
        std::cout << "A job with this title already exists. ID: " << it->getId() << std::endl;
        return;
    }
    jobCount++;
    int id = jobCount;
    Job job(id, title);
    for(const auto& skill : skills)
        job.setSkill(skill);
    announcements.push_back(job);

    modifyFile();
    std::cout << "Success adding job with ID: " << id << std::endl;
}

void Admin::deleteJob(int id){
    auto it = find_if(announcements.begin(), announcements.end(), [id](const Job& job){return job.getId()==id;});
    if(it != announcements.end()){
        announcements.erase(it);
        jobCount--;
        for(size_t i = 0; i < announcements.size(); i++)
            announcements[i].setId(i+1);
        modifyFile();
        std::ifstream usersFile("shared/users.csv");
        std::vector<std::string> lines;
        std::string line;

        if (usersFile.is_open()) {
            std::getline(usersFile, line);
            lines.push_back(line);

            while (std::getline(usersFile, line)) {
                std::stringstream ss(line);
                std::string userId, email;
                std::getline(ss, userId, ',');
                std::getline(ss, email, ',');

                std::vector<std::string> appliedJobs;
                std::string jobId;
                while (std::getline(ss, jobId, ',')) {
                    if (std::stoi(jobId) != id) {
                        appliedJobs.push_back(jobId);
                    }
                }

                std::string newLine = userId + "," + email;
                for (const auto& job : appliedJobs) {
                    newLine += "," + job;
                }
                lines.push_back(newLine);
            }
            usersFile.close();

            std::ofstream outUsersFile("shared/users.csv");
            if (outUsersFile.is_open()) {
                for (const auto& line : lines) {
                    outUsersFile << line << std::endl;
                }
                outUsersFile.close();
                std::cout << "Users' applications updated after job deletion." << std::endl;
            } else {
                std::cout << "Error: Unable to open users file for writing." << std::endl;
            }
        } else {
            std::cout << "Error: Unable to open users file for reading." << std::endl;
        }

        std::cout << "Job with id " << id << " has been deleted." << std::endl;
    } else std::cout << "Job with id " << id << " not found." << std::endl;
}

void Admin::modifyJobTitle(int id, const std::string& newTitle){
    auto it = find_if(announcements.begin(), announcements.end(), [id](const Job& job){return job.getId()==id;});
    if(it != announcements.end()){
        it->setTitle(newTitle);
        modifyFile();
    } else std::cout << "Job with id " << id << " not found." << std::endl;
}

void Admin::modifyJobSkills(int id, const std::string& newSkill){
    auto it = find_if(announcements.begin(), announcements.end(), [id](const Job& job){return job.getId()==id;});
    if(it != announcements.end()){
        it->setSkill(newSkill);
        modifyFile();
    } else std::cout << "Job with id " << id << " not found." << std::endl;
}

void Admin::viewCandidates(int jobId) {
    std::ifstream usersFile("shared/users.csv");
    if (usersFile.is_open()) {
        std::string line;
        std::getline(usersFile, line);
        bool foundCandidates = false;
        while (std::getline(usersFile, line)) {
            std::stringstream ss(line);
            std::string id, email, appliedJobId;
            std::getline(ss, id, ',');
            std::getline(ss, email, ',');
            while (std::getline(ss, appliedJobId, ',')) {
                if (std::stoi(appliedJobId) == jobId) {
                    std::cout << "Candidate: " << email << std::endl;
                    foundCandidates = true;
                    break;
                }
            }
        }
        usersFile.close();
        if (!foundCandidates) {
            std::cout << "No candidates found for job with ID: " << jobId << std::endl;
        }
    } else {
        std::cout << "Error: Unable to open users file." << std::endl;
    }
}