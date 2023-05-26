#ifndef SRC_CONFIGREADER_H
#define SRC_CONFIGREADER_H

#include <fstream>
#include <iostream>
#include "json.hpp"
#include "logger/Logger.h"

using json = nlohmann::json;

struct DatabaseConfig {
    std::string username;
    std::string host;
    std::string password;
    std::string dbname;
    int port;
};

DatabaseConfig ReadDatabaseConfig(Logger &logger, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        logger.Log(ERROR, "Failed to open file " + filename);
        throw std::runtime_error("Failed to open file " + filename);
    }

    json config;
    file >> config;

    DatabaseConfig dbConfig;
    dbConfig.username = config["username"];
    dbConfig.host = config["host"];
    dbConfig.password = config["password"];
    dbConfig.dbname = config["dbname"];
    dbConfig.port = config["port"];

    return dbConfig;
}

#endif //SRC_CONFIGREADER_H
