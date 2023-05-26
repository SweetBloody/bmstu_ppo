#include "ImageRepository.h"


//Image ImageRepository::LoadImage(std::string &path) {
//    return Image()
//}

int ImageRepository::AddImage(Image &image) {
    _images.push_back(image);
    return _images.size() - 1;
}

Image ImageRepository::GetImageById(int id) {
    if (_images.empty()) {
        std::string msg = "No data";
        throw NoDataException(msg);
    }
    return _images.at(id);
}

Image ImageRepository::UpdateImageById(int id, Image &new_image) {
    _images.at(id) = new_image;
    return _images.at(id);
}

std::vector<Image> ImageRepository::GetAllImages() {
    return _images;
}

int ImageRepository::DeleteImage(int id) {
    _images.erase(_images.begin() + id);
    return 0;
}