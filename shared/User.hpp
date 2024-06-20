#ifndef USER_HPP
#define USER_HPP

#include "Job.hpp"

class User
{
private:
    int id;
    std::string name;
    std::string email;
    std::vector<Job> appliedJobs;
public:
    User(int, const std::string&, const std::string&);

    int getId() const{return id;}
    std::string getName() const {return name;}
    std::string getEmail() const {return email;}
    std::vector<Job> getAppliedJobs() const {return appliedJobs;}

    void applyJob(const Job&);
    // ~User();

    // friend std::ostream& operator<<(std::ostream&, const User&);
};


#endif