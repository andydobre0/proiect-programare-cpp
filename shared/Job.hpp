#ifndef JOB_HPP
#define JOB_HPP

#include<string>
#include<vector>
#include<iostream>
#include<algorithm>

class Job
{
private:
    int id;
    std::string title;
    std::vector<std::string> skills;
    std::vector<std::string> candidates;
public:
    Job(int, const std::string&);
    
    int getId() const {return id;}
    std::string getTitle() const {return title;}
    std::vector<std::string> getSkills() const {return skills;}
    std::vector<std::string> getCandidates() const {return candidates;}

    void setTitle(const std::string& Title) {this->title = Title;}
    void setSkill(const std::string& Skill) {this->skills.push_back(Skill);}
    
    void addCandidate(const std::string& candidate) {this->candidates.push_back(candidate);}

    friend std::ostream& operator<<(std::ostream& os, const Job& job);
    // ~Job();
};


#endif