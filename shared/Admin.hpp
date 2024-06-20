#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "User.hpp"
#include <fstream>
#include <sstream>

class Admin : public User
{
private:
    std::vector<Job> announcements;
public:
    Admin();
    void addJob(const std::string&, const std::vector<std::string>&);
    void deleteJob(int);
    void modifyJobTitle(int, const std::string&);
    void modifyJobSkills(int, const std::string&);
    void viewCandidates(int);
    void modifyFile();
};


#endif