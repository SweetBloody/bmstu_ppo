#ifndef SRC_DOT_H
#define SRC_DOT_H


class Dot {
public:
    Dot() : _x(0), _y(0) {};
    Dot(int x, int y) : _x(x), _y(y) {};
    Dot(int id, int x, int y, int marked_object_id) : _id(id), _x(x), _y(y), _marked_object_id(marked_object_id) {};
    int GetId(){return _id;};
    int GetX() {return _x;};
    int GetY() {return _y;};
    int GetMarkedObjectId() {return _marked_object_id;};
    void SetId(int id) {_id = id;};
    void SetX(int x) {_x = x;};
    void SetY(int y) {_y = y;};
    void SetMarkedObjectId(int marked_object_id) {_marked_object_id = marked_object_id;};
//    /home/alexey/Documents/University/semester_6/ppo/src/data_files
private:
    int _id;
    int _x;
    int _y;
    int _marked_object_id;
};


#endif //SRC_DOT_H
