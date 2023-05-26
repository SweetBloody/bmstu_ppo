#ifndef SRC_LOGGER_H
#define SRC_LOGGER_H


#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>

enum LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    Logger(const std::string &filename);
    ~Logger();

    void Log(LogLevel level, const std::string &message);

private:
    static std::string GetLevelString(LogLevel level);
    std::ofstream _file;
};


#endif //SRC_LOGGER_H
