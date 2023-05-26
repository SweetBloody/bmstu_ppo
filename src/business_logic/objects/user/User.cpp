#include "User.h"

User::User(int id, const std::string &login, const std::string &password, PrivilegeLvl privilege_lvl) {
    _user_id = id;
    _login = login;
    _password = password;
    _privelege_lvl = privilege_lvl;
}

void User::SetUserId(int user_id) {
    _user_id = user_id;
}

int User::GetUserId() {
    return _user_id;
}

void User::SetLogin(std::string &login) {
    _login = login;
}

std::string User::GetLogin() {
    return _login;
}

void User::SetPassword(std::string &password) {
    _password = password;
}

std::string User::GetPassword() {
    return _password;
}

void User::SetPrivilegeLvl(PrivilegeLvl privilege_lvl) {
    _privelege_lvl = privilege_lvl;
}

PrivilegeLvl User::GetPrivilegeLvl() {
    return _privelege_lvl;
}