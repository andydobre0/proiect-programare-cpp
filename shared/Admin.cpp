#include "Admin.hpp"


Admin::Admin() : User(0, "admin", "admin@admin.com"){
    std::ifstream jobsFile("/jobs.csv");
    if(jobsFile.is_open()){
        std::string line;
        std::getline(jobsFile, line);
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
            
            std::string candidate;
            while (std::getline(ss, candidate, ','))
                job.addCandidate(candidate);
            
            announcements.push_back(job);
        }
        jobsFile.close();
    }
}

void Admin::modifyFile(){
    std::ofstream jobsFile("/jobs.csv");
    if(jobsFile.is_open()){
        jobsFile << announcements.size() << std::endl;
        for(const auto& job: announcements){
            jobsFile << job;
        }   
        jobsFile.close();   
    }
    std::cout<<"operation successful"<<std::endl;
}

void Admin::addJob(const std::string& title, const std::vector<std::string>& skills){
    int id = announcements.size() + 1;
    Job job(id, title);
    for(const auto& skill : skills)
        job.setSkill(skill);
    announcements.push_back(job);

    std::ofstream jobsFile("/jobs.csv", std::ios::app);
    if(jobsFile.is_open()){
        jobsFile << id << ',' << title;
        for(const auto& skill : skills)
            jobsFile << ',' << skill;
        jobsFile << std::endl;
        jobsFile.close();
    }
    std::cout << "success adding job." << std::endl;
}

void Admin::deleteJob(int id){
    auto it = find_if(announcements.begin(), announcements.end(), [id](const Job& job){return job.getId()==id;});

    if(it != announcements.end()){
        announcements.erase(it);
        modifyFile();
    } else std::cout<<"job with id " << id << " not found." << std::endl;
}

void Admin::modifyJobTitle(int id, const std::string& newTitle){
    auto it = find_if(announcements.begin(), announcements.end(), [id](const Job& job){return job.getId()==id;});
    if(it != announcements.end()){
        it->setTitle(newTitle);
        modifyFile();
    } else std::cout<<"job with id " << id << " not found." << std::endl;
}

void Admin::modifyJobSkills(int id, const std::string& newSkill){
    auto it = find_if(announcements.begin(), announcements.end(), [id](const Job& job){return job.getId()==id;});
    if(it != announcements.end()){
        it->setSkill(newSkill);
        modifyFile();
    } else std::cout<<"job with id " << id << " not found." << std::endl;
}

void Admin::viewCandidates(int id){
    auto it = find_if(announcements.begin(), announcements.end(), [id](const Job& job){return job.getId()==id;});
    if(it != announcements.end()){
        for(const auto& candidate : it->getCandidates())
            std::cout << candidate << std::endl;
    } else std::cout<<"job with id " << id << " not found." << std::endl;
}