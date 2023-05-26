#ifndef SRC_DATAFILEMANAGER_H
#define SRC_DATAFILEMANAGER_H

#include <fstream>

#include "exception/Exception.h"
#include "repository_interface/IImageRepository.h"
#include "repository_interface/IMarkRepository.h"
#include "repository_interface/IMarkedObjectRepository.h"


class DataFileManager {
public:
    DataFileManager(IImageRepository &image_repository, IMarkRepository &mark_repository, IMarkedObjectRepository &marked_object_repository);
    DataFileManager() = default;

    void SetImageRepository(IImageRepository &image_repository);
    void SetMarkRepository(IMarkRepository &mark_repository);
    void SetMarkedObjectRepository(IMarkedObjectRepository &marked_object_repository);

    void CreateCoordFile(std::string &path);
    void CreateImageFile(std::string &path);
    void CreateMarkedObjectFile(std::string &path);

private:
    IImageRepository *_image_repository;
    IMarkRepository *_mark_repository;
    IMarkedObjectRepository *_marked_object_repository;
};


#endif //SRC_DATAFILEMANAGER_H
