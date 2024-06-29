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
public:
    Job(int, const std::string&);
    
    int getId() const {return id;}
    std::string getTitle() const {return title;}
    std::vector<std::string> getSkills() const {return skills;}

    void setId(int id){this->id = id;}
    void setTitle(const std::string& Title) {this->title = Title;}
    void setSkill(const std::string& Skill) {this->skills.push_back(Skill);}

    friend std::ostream& operator<<(std::ostream& os, const Job& job);
    // ~Job();
};


#endif