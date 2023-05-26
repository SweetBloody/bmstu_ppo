#ifndef SRC_ACCOUNTMANAGERTEST_H
#define SRC_ACCOUNTMANAGERTEST_H

#include "gtest/gtest.h"
#include "managers/AccountManager.h"
#include "mock_repository/UserRepository.h"

TEST(AccountManagerTest, CreateUserTest) {
    UserRepository user_repository;
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", password = "123";

    User user = account_manager.CreateUser(login, password);

    EXPECT_STREQ(user.GetLogin().c_str(), login.c_str());
    EXPECT_STREQ(user.GetPassword().c_str(), password.c_str());
    EXPECT_EQ(user.GetUserId(), 0);
}

TEST(AccountManagerTest, CreateExistedUserTest) {
    UserRepository user_repository;
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", password = "123";
    User user1(0, login, password);

    int id = user_repository.AddUser(user1);
    user1.SetUserId(id);

    ASSERT_THROW(account_manager.CreateUser(login, password), AlreadyExistException);
}

TEST(AccountManagerTest, UserExistedTest) {
    UserRepository user_repository;
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", password = "123";

    User user = account_manager.CreateUser(login, password);
    int res1 = account_manager.UserExist(login);
    int res2 = account_manager.UserExist(user);

    EXPECT_EQ(res1, 1);
    EXPECT_EQ(res2, 1);
}

TEST(AccountManagerTest, CheckPasswordCorrectTest) {
    UserRepository user_repository;
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", password = "123";

    User user = account_manager.CreateUser(login, password);
    int res1 = account_manager.CheckPassword(login, password);

    EXPECT_EQ(res1, 1);
}

TEST(AccountManagerTest, CheckPasswordUserNotExistTest) {
    UserRepository user_repository;
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", password = "123";
    std::string login2 = "Userr";

    User user = account_manager.CreateUser(login, password);

    ASSERT_THROW(account_manager.CheckPassword(login2, password), UserNotExistException);
}

TEST(AccountManagerTest, CheckPasswordWrongPasswordTest) {
    UserRepository user_repository;
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", password = "123";
    std::string password2 = "321";

    User user = account_manager.CreateUser(login, password);

    ASSERT_THROW(account_manager.CheckPassword(login, password2), WrongPasswordException);
}

TEST(AccountManagerTest, UpdatePasswordCorrectTest) {
    UserRepository user_repository;
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", old_password = "123", new_password = "321";

    User user = account_manager.CreateUser(login, old_password);
    account_manager.UpdatePassword(login, old_password, new_password);

    User user_res = user_repository.GetUserByLogin(login);

    EXPECT_STREQ(user_res.GetLogin().c_str(), login.c_str());
    EXPECT_STREQ(user_res.GetPassword().c_str(), new_password.c_str());
}

TEST(AccountManagerTest, UpdatePasswordUserNotExistTest) {
    UserRepository user_repository;
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", login2 = "Userr",
            old_password = "123", new_password = "321";

    User user = account_manager.CreateUser(login, old_password);

    ASSERT_THROW(account_manager.UpdatePassword(login2, old_password, new_password), UserNotExistException);
}

TEST(AccountManagerTest, UpdatePasswordWrongOldPasswordTest) {
    UserRepository user_repository;
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", old_password = "123",
            old_password2 = "12333", new_password = "321";

    User user = account_manager.CreateUser(login, old_password);

    ASSERT_THROW(account_manager.UpdatePassword(login, old_password2, new_password), WrongPasswordException);
}

TEST(AccountManagerTest, DeleteUserCorrectTest) {
    UserRepository user_repository;
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", password = "123";

    User user = account_manager.CreateUser(login, password);
    int res1 = account_manager.UserExist(user);
    EXPECT_EQ(res1, 1);

    account_manager.DeleteUser(user);
    int res2 = account_manager.UserExist(user);
    EXPECT_EQ(res2, 0);
}

TEST(AccountManagerTest, DeleteUserUserNotExistTest) {
    UserRepository user_repository;
    AccountManager account_manager(user_repository);
    std::string login = "SweetBloody", password = "123",
            login2 = "Userr", password2 = "321";

    User user = account_manager.CreateUser(login, password);
    int res1 = account_manager.UserExist(user);
    EXPECT_EQ(res1, 1);

    User user2(1, login2, password2);
    ASSERT_THROW(account_manager.DeleteUser(user2), UserNotExistException);
}


#endif //SRC_ACCOUNTMANAGERTEST_H
