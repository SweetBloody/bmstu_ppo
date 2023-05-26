#include "ImageManager.h"

ImageManager::ImageManager(IImageRepository &image_repository, IMarkedObjectRepository &marked_object_repository) {
    _image_repository = &image_repository;
    _marked_object_repository = &marked_object_repository;
}

std::vector<Image> ImageManager::GetAllImages() {
    std::vector<Image> images = _image_repository->GetAllImages();
    if (images.empty()) {
        std::string msg = "No images";
        throw NoDataException(msg);
    }
    return images;
}

Image ImageManager::GetImageById(int id) {
    Image image;
    image = _image_repository->GetImageById(id);
    return image;
}

Image ImageManager::LoadImage(std::string &path) {
    Image image(0, path);
    int id = _image_repository->AddImage(image);
    image.SetImageId(id);
    return image;
}

Image ImageManager::UpdateImageById(int id, Image &new_image) {
    new_image = _image_repository->UpdateImageById(id, new_image);
    return new_image;
}

int ImageManager::DeleteImage(int id) {
    if (_marked_object_repository->DeleteAllMarkedObjectsOfImage(id))
        return 0;
    if (_image_repository->DeleteImage(id))
        return 0;
    return 1;
}

int ImageManager::AddMarkedObjectToImage(Image &image, MarkedObject &marked_object) {
    image.AddMarkedObject(marked_object);
    return 0;
}

int ImageManager::DeleteMarkedObjectFromImage(Image &image, int id) {
    image.DeleteMarkedObjectById(id);
    _marked_object_repository->DeleteMarkedObject(id);
    return 0;
}



std::vector<MarkedObject> ImageManager::GetAllMarkedObjectsOfImage(Image &image) {
    std::vector<MarkedObject> marked_objects;
    marked_objects = image.GetMarkedObjects();
    if (marked_objects.empty()) {
        std::string msg = "No marked objects";
        throw NoDataException(msg);
    }

    return image.GetMarkedObjects();
}