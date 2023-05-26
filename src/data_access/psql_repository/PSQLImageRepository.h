#ifndef SRC_PSQLIMAGEREPOSITORY_H
#define SRC_PSQLIMAGEREPOSITORY_H

#include "repository_interface/IImageRepository.h"
#include "repository_interface/IMarkedObjectRepository.h"
#include "objects/connection/Connection.h"
#include "Query.h"
#include "logger/Logger.h"

class PSQLImageRepository : public IImageRepository {
public:
    PSQLImageRepository(std::string &user, std::string &host, std::string &password, std::string &db_name, int port,
                        Logger &logger);
    void SetMarkedObjectRepository(IMarkedObjectRepository &marked_object_repository);

    int AddImage(Image &image);
    Image GetImageById(int id);
    Image UpdateImageById(int id, Image &new_image);
    std::vector<Image> GetAllImages();
    int DeleteImage(int id);

private:
    pqxx::connection *_connection;
    IMarkedObjectRepository *_marked_object_repository;
    Logger *_logger;
};


#endif //SRC_PSQLIMAGEREPOSITORY_H
