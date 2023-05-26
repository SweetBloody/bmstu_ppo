#ifndef SRC_QUERY_H
#define SRC_QUERY_H

#include <string>
#include <iostream>
#include <fmt/core.h>


class Query {
public:
    Query() = default;

    static std::string AddUser(const std::string &login, const std::string &password, int privilege_lvl);
    static std::string GetPasswordByLogin(const std::string &login);
    static std::string GetUserById(int id);
    static std::string GetUserByLogin(const std::string &login);
    static std::string UpdatePassword(const std::string &login, const std::string &password);
    static std::string DeleteUser(const std::string &login);

    static std::string GetAllMarks();
    static std::string GetMarkById(int id);
    static std::string GetMarkByName(const std::string &name);
    static std::string AddMark(const std::string &name);
    static std::string UpdateMark(int id, const std::string &new_name);
    static std::string DeleteMark(int id);

    static std::string GetAllMarkedObjects();
    static std::string GetAllMarkedObjectsOfImage(int id);
    static std::string AddMarkedObject(int type, int mark_id, int image_id);
    static std::string DeleteMarkedObject(int id);
    static std::string DeleteAllMarkedObjectsOfImage(int image_id);

    static std::string GetAllCoords();
    static std::string GetCoordsOfMarkedObject(int marked_object_id);
    static std::string AddCoord(int marked_object_id, int x_coord, int y_coord);
    static std::string DeleteCoord(int id);
    static std::string DeleteCoordsOfMarkedObject(int marked_object_id);

    static std::string GetAllImages();
    static std::string AddImage(const std::string &image_path);
    static std::string GetImageById(int id);
    static std::string UpdateImageById(int id, const std::string &new_path_name);
    static std::string DeleteImage(int id);
};

#endif //SRC_QUERY_H
