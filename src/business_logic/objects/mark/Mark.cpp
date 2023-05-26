#include "Mark.h"

Mark::Mark(int id, const std::string &name) {
    _id = id;
    _name = name;
}

int Mark::GetMarkId() {
    return _id;
}

void Mark::SetMarkId(int id) {
    _id = id;
}

std::string Mark::GetName() {
    return _name;
}

void Mark::SetName(std::string &name) {
    _name = name;
}