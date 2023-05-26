#include "MarkedObjectRepository.h"

std::vector<MarkedObject> MarkedObjectRepository::GetAllMarkedObjects() {
    return _marked_objects;
}

std::vector<MarkedObject> MarkedObjectRepository::GetAllMarkedObjectsOfImage(int image_id) {
    std::vector<MarkedObject> temp;
    for (auto & _marked_object : _marked_objects) {
        if (_marked_object.GetImageId() == image_id)
            temp.push_back(_marked_object);
    }
    return temp;
}

std::vector<Dot> MarkedObjectRepository::GetAllCoords() {
    std::vector<Dot> coords;
    for (auto & _marked_object : _marked_objects) {
        for (int i = 0; i < _marked_object.GetCoords().size(); i++)
            coords.push_back(_marked_object.GetCoords()[i]);
    }
    return coords;
}

int MarkedObjectRepository::AddMarkedObject(MarkedObject &marked_object) {
    _marked_objects.push_back(marked_object);
    return _marked_objects.size() - 1;
}

int MarkedObjectRepository::AddAllMarkedObjectsOfImage(std::vector<MarkedObject> &marked_objects) {
    _marked_objects.insert(_marked_objects.end(), marked_objects.begin(), marked_objects.end());
    return 0;
}
int MarkedObjectRepository::DeleteMarkedObject(int id) {
    _marked_objects.erase(_marked_objects.begin() + id);
    return 0;
}
int MarkedObjectRepository::DeleteAllMarkedObjectsOfImage(int image_id) {
    for (int i = 0; i < _marked_objects.size(); i++) {
        if (_marked_objects.at(i).GetImageId() == image_id)
            _marked_objects.erase(_marked_objects.begin() + i);
    }

    return 0;
}