#ifndef SRC_IMARKREPOSITORY_H
#define SRC_IMARKREPOSITORY_H

#include <vector>
#include "objects/mark/Mark.h"

class IMarkRepository {
public:
    virtual std::vector<Mark> GetAllMarks() = 0;
    virtual Mark GetMarkById(int id) = 0;
    virtual bool MarkExist(Mark &mark) = 0;
    virtual int AddMark(Mark &mark) = 0;
    virtual int DeleteMark(int id) = 0;
    virtual Mark UpdateMark(int id, Mark &mark) = 0;
};


#endif //SRC_IMARKREPOSITORY_H
