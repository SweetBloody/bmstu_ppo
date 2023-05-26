#ifndef SRC_MARKEDOBJECT_H
#define SRC_MARKEDOBJECT_H

#include <vector>
#include "objects/mark/Mark.h"
#include "objects/dot/Dot.h"

enum Figure {
    POLYGON,
    CIRCLE
};

class MarkedObject {
public:
    MarkedObject(int id, int image_id, int type);
    MarkedObject(int id, int image_id, int type, std::vector<Dot> &coords, Mark &mark);

    int GetMarkedObjectId() {return _id;};
    void SetMarkedObjectId(int id) {_id = id;};
    Mark GetMark() {return _mark;};
    void SetMark(Mark &mark) {_mark = mark;};
    int GetType() {return _type;};
    void SetType(int type) {_type = type;};
    int GetImageId() {return _image_id;};

    std::vector<Dot> GetCoords();
    void SetCoords(std::vector<Dot> &coords);
    int AddCoord(Dot &dot);
    int DeleteCoordById(int id);
    int DeleteLastCoord();


protected:
    int _id;
    Mark _mark;
    int _type; // 0 - многоугольник, 1 - круг
    std::vector<Dot> _coords; // для круга: 1 точка - центр, 2 - радиус
    int _image_id;
};


#endif //SRC_MARKEDOBJECT_H
