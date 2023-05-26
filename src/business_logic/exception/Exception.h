#ifndef SRC_EXCEPTION_H
#define SRC_EXCEPTION_H

#include <string>
#include <exception>

class Exception : public std::exception
{
public:
    explicit Exception(std::string &msg) : _msg(msg) { }

    const char *what() const noexcept override { return "Something went wrong!"; }
    const std::string &GetInfo() const noexcept { return _msg; }

protected:
    std::string _msg;
};

class NoDataException : public Exception
{
public:
    explicit NoDataException(std::string &msg) : Exception(msg) { }

    const char *what() const noexcept override { return "No data"; }
};

class AlreadyExistException : public Exception
{
public:
    explicit AlreadyExistException(std::string &msg) : Exception(msg) { }

    const char *what() const noexcept override { return "This object already exist"; }
};

class MarkedObjectCoordsException : public Exception
{
public:
    explicit MarkedObjectCoordsException(std::string &msg) : Exception(msg) { }

    const char *what() const noexcept override { return "MarkedObject error"; }
};


class UserNotExistException : public Exception
{
public:
    explicit UserNotExistException(std::string &msg) : Exception(msg) { }

    const char *what() const noexcept override { return "No such user"; }
};


class WrongPasswordException : public Exception
{
public:
    explicit WrongPasswordException(std::string &msg) : Exception(msg) { }

    const char *what() const noexcept override { return "Wrong password"; }
};

class LoadImageException : public Exception
{
public:
    explicit LoadImageException(std::string &msg) : Exception(msg) { }

    const char *what() const noexcept override { return "Load image error"; }
};

class ConnectException : public Exception
{
public:
    explicit ConnectException(std::string &msg) : Exception(msg) { }

    const char *what() const noexcept override { return "Connect error"; }
};


#endif //SRC_EXCEPTION_H
