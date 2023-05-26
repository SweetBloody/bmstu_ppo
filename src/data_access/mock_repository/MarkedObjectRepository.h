#ifndef SRC_MARKEDOBJECTREPOSITORY_H
#define SRC_MARKEDOBJECTREPOSITORY_H

#include "repository_interface/IMarkedObjectRepository.h"

class MarkedObjectRepository : public IMarkedObjectRepository {
public:
    std::vector<MarkedObject> GetAllMarkedObjects();
    std::vector<MarkedObject> GetAllMarkedObjectsOfImage(int image_id);
    std::vector<Dot> GetAllCoords();
    int AddMarkedObject(MarkedObject &marked_object);
    int AddAllMarkedObjectsOfImage(std::vector<MarkedObject> &marked_objects);
    int DeleteMarkedObject(int id);
    int DeleteAllMarkedObjectsOfImage(int image_id);

private:
    std::vector<MarkedObject> _marked_objects;
};


#endif //SRC_MARKEDOBJECTREPOSITORY_H
