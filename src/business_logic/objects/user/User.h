#ifndef SRC_USER_H
#define SRC_USER_H

#include "objects/image/Image.h"
#include <string>

enum PrivilegeLvl {
    NOT_AUTH,
    USER,
    ADMIN
};


class User {
public:
    User() = default;
    User(int id, const std::string &login, const std::string &password, PrivilegeLvl privilege_lvl = NOT_AUTH);

    void SetUserId(int user_id);
    int GetUserId();
    void SetLogin(std::string &login);
    std::string GetLogin();
    void SetPassword(std::string &password);
    std::string GetPassword();
    void SetPrivilegeLvl(PrivilegeLvl privilege_lvl);
    PrivilegeLvl GetPrivilegeLvl();

private:
    int _user_id;
    std::string _login;
    std::string _password;
    PrivilegeLvl _privelege_lvl;
};


#endif //SRC_USER_H
