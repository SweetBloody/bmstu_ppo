#ifndef SRC_REQUEST_H
#define SRC_REQUEST_H


#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>

enum REQUEST_KEYS {
    EXIT,
    UN_AUTH,
    AUTH,
    REGISTER,
    LOAD_IMAGE,
    DELETE_IMAGE,
    CREATE_MARK,
    CREATE_DATA_FILE,
    GET_IMAGES,
    LABEL_IMAGE,
    GET_MARKED_OBJECTS_OF_IMAGE,
    DELETE_MARKED_OBJECT,
    NOT_A_COMMAND
};

class RequestHandler {
public:
    RequestHandler() = default;
    ~RequestHandler() = default;
    REQUEST_KEYS handle(std::string req);
private:
    bool check_is_number(std::string req);
};


#endif //SRC_REQUEST_H
