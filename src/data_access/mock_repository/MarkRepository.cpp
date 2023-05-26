#include "MarkRepository.h"

std::vector<Mark> MarkRepository::GetAllMarks() {
    return _marks;
}

Mark MarkRepository::GetMarkById(int id) {
    if (_marks.empty() || (_marks.size() <= id)) {
        std::string msg = "No data";
        throw NoDataException(msg);
    }
    return _marks.at(id);
}

bool MarkRepository::MarkExist(Mark &mark) {
    for (auto & _mark : _marks)
        if (_mark.GetName() == mark.GetName())
            return true;
    return false;
}

int MarkRepository::AddMark(Mark &mark) {
    _marks.push_back(mark);
    return _marks.size() - 1;
}

int MarkRepository::DeleteMark(int id) {
    _marks.erase(_marks.begin() + id);
    return 0;
}

Mark MarkRepository::UpdateMark(int id, Mark &mark) {
    _marks.at(id) = mark;
    return mark;
}