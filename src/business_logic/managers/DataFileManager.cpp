#include "DataFileManager.h"

DataFileManager::DataFileManager(IImageRepository &image_repository, IMarkRepository &mark_repository, IMarkedObjectRepository &marked_object_repository) {
    _image_repository = &image_repository;
    _marked_object_repository = &marked_object_repository;
    _mark_repository = &mark_repository;
}


void DataFileManager::SetImageRepository(IImageRepository &image_repository) {
    _image_repository = &image_repository;
}

void DataFileManager::SetMarkRepository(IMarkRepository &mark_repository) {
    _mark_repository = &mark_repository;
}

void DataFileManager::SetMarkedObjectRepository(IMarkedObjectRepository &marked_object_repository) {
    _marked_object_repository = &marked_object_repository;
}

void DataFileManager::CreateCoordFile(std::string &path) {
    std::ofstream file(path + "/coords.txt");
    std::vector<Dot> coords;
    coords = _marked_object_repository->GetAllCoords();
    std::string delimeter = ";";

    for (auto & coord : coords) {
        file << coord.GetId() << delimeter
             << coord.GetX() << delimeter
             << coord.GetY() << delimeter
             << coord.GetMarkedObjectId() << std::endl;
    }

    file.close();
}

void DataFileManager::CreateImageFile(std::string &path) {
    std::ofstream file(path);
    std::vector<Image> images;
    images = _image_repository->GetAllImages();
    std::string delimeter = ";";

    for (auto & image : images) {
        file << image.GetImageId() << delimeter << std::endl;
    }

    file.close();
}

void DataFileManager::CreateMarkedObjectFile(std::string &path) {
    std::ofstream file(path + "/marked_objects.txt");
    std::vector<MarkedObject> marked_objects;
    marked_objects = _marked_object_repository->GetAllMarkedObjects();
    std::string delimeter = ";";

    for (auto & marked_object : marked_objects) {
        file << marked_object.GetMarkedObjectId() << delimeter
             << marked_object.GetMark().GetName() << delimeter
             << marked_object.GetType() << delimeter
             << marked_object.GetImageId() << std::endl;
    }

    file.close();
}