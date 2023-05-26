#include "MarkedObject.h"

MarkedObject::MarkedObject(int id, int image_id, int type) {
    _id = id;
    _image_id = image_id;
    _type = type;
}

MarkedObject::MarkedObject(int id, int image_id, int type, std::vector<Dot> &coords, Mark &mark) {
    _id = id;
    _image_id = image_id;
    _coords = coords;
    _mark = mark;
    _type = type;
}


std::vector<Dot> MarkedObject::GetCoords() {
    return _coords;
}

void MarkedObject::SetCoords(std::vector<Dot> &coords) {
    _coords = coords;
}

int MarkedObject::AddCoord(Dot &dot) {
    _coords.push_back(dot);
    return  0;
}

int MarkedObject::DeleteCoordById(int id) {
    _coords.erase(_coords.begin() + id);
    return 0;
}

int MarkedObject::DeleteLastCoord() {
    if (!_coords.empty()) {
        _coords.pop_back();
        return 0;
    }
    return 1;
}