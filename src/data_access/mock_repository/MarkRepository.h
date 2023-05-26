#ifndef SRC_MARKREPOSITORY_H
#define SRC_MARKREPOSITORY_H

#include "exception/Exception.h"
#include "repository_interface/IMarkRepository.h"

class MarkRepository : public IMarkRepository {
public:
    std::vector<Mark> GetAllMarks();
    Mark GetMarkById(int id);
    bool MarkExist(Mark &mark);
    int AddMark(Mark &mark);
    int DeleteMark(int id);
    Mark UpdateMark(int id, Mark &mark);

private:
    std::vector<Mark> _marks;
};


#endif //SRC_MARKREPOSITORY_H
