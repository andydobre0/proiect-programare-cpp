#include "Job.hpp"

Job::Job(int id, const std::string& title) : id(id), title(title){}

std::ostream& operator<<(std::ostream& os, const Job& job){
    os << job.getId()<< ',' << job.getTitle() << ',';
    for(const auto& skill : job.getSkills()){
        os << skill << ',';
    }
    for(const auto& candidate : job.getCandidates()){
        os << candidate << " ";
    }
    os << std::endl;
    return os;
}
