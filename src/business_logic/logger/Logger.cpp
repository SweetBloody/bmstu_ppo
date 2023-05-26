#include "Logger.h"

Logger::Logger(const std::string &filename) {
    _file.open(filename, std::ios::out | std::ios::app);
}

Logger::~Logger() {
    _file.close();
}

void Logger::Log(LogLevel level, const std::string &message) {
    time_t now = time(0);
    char* tmp = ctime(&now);
    std::string str_time(tmp);
    str_time = str_time.substr(0, str_time.length() - 1);

    _file << std::setw(0) << "[" << GetLevelString(level) << "] " <<std::setw(12) << message << std::setw(5) << " (" << str_time << ")" << std::endl;
}

std::string Logger::GetLevelString(LogLevel level) {
    switch (level) {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        default:
            return "";
    }
}