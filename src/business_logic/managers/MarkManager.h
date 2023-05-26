#ifndef SRC_MARKMANAGER_H
#define SRC_MARKMANAGER_H

#include "exception/Exception.h"
#include "repository_interface/IMarkRepository.h"

class MarkManager {
public:
    MarkManager(IMarkRepository &mark_repository);

    std::vector<Mark> GetAllMarks();
    Mark GetMarkById(int id);
    Mark CreateMark(std::string &name);
    int DeleteMark(int id);
    Mark UpdateMark(int id, std::string &name);

private:
    IMarkRepository *_mark_repository;
};


#endif //SRC_MARKMANAGER_H
