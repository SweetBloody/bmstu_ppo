#ifndef SRC_IMARKEDOBJECTREPOSITORY_H
#define SRC_IMARKEDOBJECTREPOSITORY_H

#include <vector>
#include "objects/marked_object/MarkedObject.h"

class IMarkedObjectRepository {
public:
    virtual std::vector<MarkedObject> GetAllMarkedObjects() = 0;
    virtual std::vector<MarkedObject> GetAllMarkedObjectsOfImage(int image_id) = 0;
    virtual std::vector<Dot> GetAllCoords() = 0;
    virtual int AddMarkedObject(MarkedObject &marked_object) = 0;
    virtual int AddAllMarkedObjectsOfImage(std::vector<MarkedObject> &marked_objects) = 0;
    virtual int DeleteMarkedObject(int id) = 0;
    virtual int DeleteAllMarkedObjectsOfImage(int image_id) = 0;
};


#endif //SRC_IMARKEDOBJECTREPOSITORY_H
