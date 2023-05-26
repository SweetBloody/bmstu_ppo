#include "AccountManager.h"

#include <utility>

AccountManager::AccountManager(IUserRepository &user_repository) {
    _user_repository = &user_repository;
}

User AccountManager::CreateUser(std::string &login, std::string &password) {
    User user(0, login, password, USER);
    if (_user_repository->UserExist(user)) {
        std::string msg = "Already exist";
        throw AlreadyExistException(msg);
    }
    int id = _user_repository->AddUser(user);
    user.SetUserId(id);
    return user;
}

User AccountManager::GetUserByLogin(std::string &login) {
    return _user_repository->GetUserByLogin(login);
}

bool AccountManager::UserExist(std::string &login) {
    return _user_repository->UserExist(login);
}

bool AccountManager::UserExist(User &user) {
    return _user_repository->UserExist(user);
}

bool AccountManager::CheckPassword(std::string &login, std::string &password) {
    User user(0, login, password, NOT_AUTH);
    if (!_user_repository->UserExist(user)) {
        std::string msg = "There is no such user";
        throw UserNotExistException(msg);
    }
//        return false;
    if (!_user_repository->CheckPassword(login, password)) {
        std::string msg = "Wrong password";
        throw WrongPasswordException(msg);
    }

    return true;
}

User AccountManager::UpdatePassword(std::string &login, std::string &old_password, std::string &new_password) {
    User user(0, login, old_password, NOT_AUTH);
    if (!_user_repository->UserExist(user)) {
        std::string msg = "There is no such user";
        throw UserNotExistException(msg);
    }

    if (!_user_repository->CheckPassword(login, old_password)) {
        std::string msg = "Wrong password";
        throw WrongPasswordException(msg);
    }

    _user_repository->UpdatePassword(user, new_password);
    user.SetPassword(new_password);
    return user;
//    return 1;
}

User AccountManager::UpdatePassword(User &user, std::string &new_password) {
    if (!_user_repository->UserExist(user)) {
        std::string msg = "There is no such user";
        throw UserNotExistException(msg);
    }

//    if (!_user_repository->CheckPassword(login, old_password)) {
//        std::string msg = "Wrong password";
//        throw WrongPasswordException(msg);
//    }

    _user_repository->UpdatePassword(user, new_password);
    user.SetPassword(new_password);
    return user;
}

int AccountManager::DeleteUser(User &user) {
    if (!_user_repository->UserExist(user)) {
        std::string msg = "There is no such user";
        throw UserNotExistException(msg);
    }

    return _user_repository->DeleteUser(user);
}
