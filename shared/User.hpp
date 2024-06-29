#ifndef USER_HPP
#define USER_HPP

#include "Job.hpp"

class User
{
protected:
    int id;
    static int userCount;
    std::string email;
    std::vector<Job> announcements;
    std::vector<int> appliedJobs;
public:
    User(){}
    User(const std::string&);

    int getId() const{return id;}
    std::string getEmail() const {return email;}
    std::vector<int> getAppliedJobs() const {return appliedJobs;}

    void setEmail(std::string email){this->email = email;}
    void applyForJob(int);
    void viewJobs();
    void filterJobs(const std::string& skill);

    static int getUserCount();
    static void incrementUserCount();
    static void loadUserCount();
    static void saveUserCount();
    // ~User();
};


#endif