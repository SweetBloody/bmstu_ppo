#include "Image.h"

Image::Image(int id, const std::string &path) {
    try {
        _id = id;
        _image = cv::imread(path, cv::IMREAD_UNCHANGED);
        _path = path;
    }
    catch (cv::Exception& e) {
        std::string msg = "Loading image error";
        throw LoadImageException(msg);
    }
}

Image::Image(int id, const std::string &path, std::vector<MarkedObject> &marked_object) {
    try {
        _id = id;
        _image = cv::imread(path, cv::IMREAD_UNCHANGED);
        _path = path;
        _marked_objects = marked_object;
    }
    catch (cv::Exception& e) {
        std::string msg = "Loading image error";
        throw LoadImageException(msg);
    }
}

int Image::GetImageId() {
    return _id;
}

void Image::SetImageId(int id) {
    _id = id;
}

cv::Mat Image::GetImage() {
    return _image;
}


std::string Image::GetPath() {
    return _path;
}

void Image::SetPath(std::string &path) {
    _path = path;
}

std::vector<MarkedObject> Image::GetMarkedObjects() {
    return _marked_objects;
}

void Image::SetMarkedObjects(std::vector<MarkedObject> marked_objects) {
    _marked_objects = marked_objects;
}

int Image::AddMarkedObject(MarkedObject &object) {
    _marked_objects.push_back(object);
    return _marked_objects.size() - 1;
}

int Image::DeleteMarkedObjectById(int id) {
    _marked_objects.erase(_marked_objects.begin() + id);
    return 0;
}

int Image::DeleteAllMarkedObjects() {
    _marked_objects.clear();
    return 0;
}

int Image::UpdateMarkedObject(int id, MarkedObject &new_object) {
    _marked_objects.at(id) = new_object;
    return 0;
}



