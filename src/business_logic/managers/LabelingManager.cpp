#include "LabelingManager.h"

LabelingManager::LabelingManager(ImageManager &image_manager, IMarkedObjectRepository &marked_object_repository) {
    _image_manager = &image_manager;
    _marked_object_repository = &marked_object_repository;
}


void LabelingManager::SetImageManager(ImageManager &image_manager) {
    _image_manager = &image_manager;
}

void LabelingManager::SetMarkedObjectRepository(IMarkedObjectRepository &marked_object_repository) {
    _marked_object_repository = &marked_object_repository;
}

Image LabelingManager::LabelImagePolygon(Image &image, std::vector<Dot> &coords, Mark &mark) {
    int id;
    MarkedObject polygon_mo = MarkedObject(0, image.GetImageId(), POLYGON, coords, mark);
    id = _marked_object_repository->AddMarkedObject(polygon_mo);
    polygon_mo.SetMarkedObjectId(id);

    image.AddMarkedObject(polygon_mo);
    return image;
}

Image LabelingManager::LabelImageCircle(Image &image, Dot &center, Dot &radius, Mark &mark) {
    int id;
    std::vector<Dot> coords{center, radius};

    MarkedObject circle_mo = MarkedObject(0, image.GetImageId(), CIRCLE, coords, mark);
    id = _marked_object_repository->AddMarkedObject(circle_mo);
    circle_mo.SetMarkedObjectId(id);
    image.AddMarkedObject(circle_mo);
    return image;
}

void LabelingManager::DeleteMarkedObject(Image &image, MarkedObject &marked_object) {
    image.DeleteMarkedObjectById(marked_object.GetMarkedObjectId());
    _image_manager->UpdateImageById(image.GetImageId(), image);
    _marked_object_repository->DeleteMarkedObject(marked_object.GetMarkedObjectId());
}

void LabelingManager::DeleteAllMarkedObjects(Image &image) {
    image.DeleteAllMarkedObjects();
    _image_manager->UpdateImageById(image.GetImageId(), image);
    _marked_object_repository->DeleteAllMarkedObjectsOfImage(image.GetImageId());
}

void LabelingManager::SaveImageInfo(Image &image) {
    _image_manager->UpdateImageById(image.GetImageId(), image);
    std::vector<MarkedObject> marked_objects = image.GetMarkedObjects();
    _marked_object_repository->AddAllMarkedObjectsOfImage(marked_objects);
}

