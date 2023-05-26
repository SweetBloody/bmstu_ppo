#include "Query.h"

 std::string Query::AddUser(const std::string &login, const std::string &password, int privilege_lvl) {
    std::string query = fmt::format("insert into users (login, password, privilege_lvl)\n"
                                         "values ('{}', '{}', {})\n"
                                         "returning id;", login, password, privilege_lvl);
    return query;
}

std::string Query::GetPasswordByLogin(const std::string &login) {
    std::string query = fmt::format("select password\n"
                                    "from users\n"
                                    "where login = '{}'", login);
    return query;
}

std::string Query::GetUserById(int id) {
    std::string query = fmt::format("select *\n"
                                    "from users\n"
                                    "where id = {}", id);
    return query;
}

std::string Query::GetUserByLogin(const std::string &login) {
    std::string query = fmt::format("select *\n"
                                    "from users\n"
                                    "where login = '{}'", login);
    return query;
}

std::string Query::UpdatePassword(const std::string &login, const std::string &password) {
    std::string query = fmt::format("update users\n"
                                    "set password = '{}'\n"
                                    "where login = '{}'", password, login);
    return query;
}

std::string Query::DeleteUser(const std::string &login) {
    std::string query = fmt::format("delete from users\n"
                                    "where login = '{}'", login);
    return query;
}

std::string Query::GetAllMarks() {
    std::string query = fmt::format("select *\n"
                                    "from mark");
    return query;
}

std::string Query::GetMarkById(int id) {
    std::string query = fmt::format("select *\n"
                                    "from mark\n"
                                    "where id = {}", id);
    return query;
}

std::string Query::GetMarkByName(const std::string &name) {
    std::string query = fmt::format("select *\n"
                                    "from mark\n"
                                    "where name = '{}'", name);
    return query;
}

std::string Query::AddMark(const std::string &name) {
    std::string query = fmt::format("insert into mark (name)\n"
                                    "values ('{}')\n"
                                    "returning id;", name);
    return query;
}

std::string Query::UpdateMark(int id, const std::string &new_name) {
    std::string query = fmt::format("update mark\n"
                                    "set name = '{}'\n"
                                    "where id = {}", new_name, id);
    return query;
}

std::string Query::DeleteMark(int id) {
    std::string query = fmt::format("delete from users\n"
                                    "where id = {}", id);
    return query;
}

std::string Query::GetAllMarkedObjects() {
    std::string query = fmt::format("select *\n"
                                    "from markedobject");
    return query;
}

std::string Query::GetAllMarkedObjectsOfImage(int id) {
    std::string query = fmt::format("select *\n"
                                    "from markedobject\n"
                                    "where image_id = {}", id);
    return query;
}

std::string Query::AddMarkedObject(int type, int mark_id, int image_id) {
    std::string query = fmt::format("insert into markedobject (type, mark_id, image_id)\n"
                                    "values ({}, {}, {})\n"
                                    "returning id;", type, mark_id, image_id);
    return query;
}

std::string Query::DeleteMarkedObject(int id) {
    std::string query = fmt::format("delete from markedobject\n"
                                    "where id = {}", id);
    return query;
}

std::string Query::DeleteAllMarkedObjectsOfImage(int image_id) {
    std::string query = fmt::format("delete from markedobject\n"
                                    "where image_id = {}", image_id);
    return query;
}

std::string Query::GetAllCoords() {
    std::string query = fmt::format("select *\n"
                                    "from coord");
    return query;
}

std::string Query::GetCoordsOfMarkedObject(int marked_object_id) {
    std::string query = fmt::format("select *\n"
                                    "from coord\n"
                                    "where marked_object_id = {}", marked_object_id);
    return query;
}

std::string Query::AddCoord(int marked_object_id, int x_coord, int y_coord) {
    std::string query = fmt::format("insert into coord (marked_object_id, x_coord, y_coord)\n"
                                    "values ({}, {}, {})", marked_object_id, x_coord, y_coord);
    return query;
}

std::string Query::DeleteCoord(int id) {
    std::string query = fmt::format("delete from coord\n"
                                    "where id = {}", id);
    return query;
}

std::string Query::DeleteCoordsOfMarkedObject(int marked_object_id) {
    std::string query = fmt::format("delete from coord\n"
                                    "where marked_object_id = {}", marked_object_id);
    return query;
}


std::string Query::GetAllImages() {
    std::string query = fmt::format("select *\n"
                                    "from image");
    return query;
}

std::string Query::AddImage(const std::string &image_path) {
    std::string query = fmt::format("insert into image (image_path)\n"
                                    "values ('{}')\n"
                                    "returning id;", image_path);
    return query;
}

std::string Query::GetImageById(int id) {
    std::string query = fmt::format("select *\n"
                                    "from image\n"
                                    "where id = {}", id);
    return query;
}

std::string Query::UpdateImageById(int id, const std::string &new_path_name) {
    std::string query = fmt::format("update image\n"
                                    "set image_path = '{}'\n"
                                    "where id = {}", new_path_name, id);
    return query;
}

std::string Query::DeleteImage(int id) {
    std::string query = fmt::format("delete from image\n"
                                    "where id = {}", id);
    return query;
}