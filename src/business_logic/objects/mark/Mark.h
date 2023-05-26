#ifndef SRC_MARK_H
#define SRC_MARK_H

#include <string>

class Mark {
public:
    Mark() = default;
    Mark(int id, const std::string &name);
    int GetMarkId();
    void SetMarkId(int id);
    std::string GetName();
    void SetName(std::string &name);

private:
    int _id;
    std::string _name;
};


#endif //SRC_MARK_H
