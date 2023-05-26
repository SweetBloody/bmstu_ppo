#include "MarkManager.h"

MarkManager::MarkManager(IMarkRepository &mark_repository) {
    _mark_repository = &mark_repository;
}

std::vector<Mark> MarkManager::GetAllMarks() {
    std::vector<Mark> marks = _mark_repository->GetAllMarks();
    if (marks.empty()) {
        std::string msg = "No marks";
        throw NoDataException(msg);
    }
    return marks;
}

Mark MarkManager::GetMarkById(int id) {
    Mark mark;
    try {
        mark = _mark_repository->GetMarkById(id);
    }
    catch (Exception const &e) {
        std::string msg = "No images";
        throw NoDataException(msg);
    }
    return mark;
}

Mark MarkManager::CreateMark(std::string &name) {
    Mark mark = Mark(0, name);
    if (_mark_repository->MarkExist(mark)) {
        std::string msg = "Mark already exist";
        throw AlreadyExistException(msg);
    }
    int id = _mark_repository->AddMark(mark);
    mark.SetMarkId(id);
    return mark;
}

int MarkManager::DeleteMark(int id) {
    _mark_repository->DeleteMark(id);
    return 0;
}

Mark MarkManager::UpdateMark(int id, std::string &name) {
    Mark new_mark = Mark(0, name);
    _mark_repository->UpdateMark(id, new_mark);
    return new_mark;
}