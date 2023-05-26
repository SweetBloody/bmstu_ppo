#include "App.h"

#include <utility>

App::App(Controller &auth_controller, LabelingManager &labeling_manager,
         ImageManager &image_manager, MarkManager &mark_manager, DataFileManager &datafile_manager, Logger &logger)
{
    _controller = &auth_controller;
    _image_manager = &image_manager;
    _mark_manager = &mark_manager;
    _datafile_manager = &datafile_manager;
    _logger = &logger;
}

void App::PrintMenu() {
    std::cout << MENU_ENTRIES;
}

void App::PrintNotCommand()
{
    std::cout << NOT_COMMAND << std::endl;
}

void App::PrintNotRole()
{
    std::cout << NOT_ROLE << std::endl;
}

void App::Menu()
{
    PrintMenu();
    std::string req;
    std::cin >> req;
    REQUEST_KEYS key = GetRequestKey(req);
    HandleReq(key);
}

REQUEST_KEYS App::GetRequestKey(std::string req)
{
    return _req_handler.handle(std::move(req));
}

void App::HandleReq(REQUEST_KEYS key)
{
    switch (key)
    {
        case EXIT:
            std::exit(EXIT);

        case UN_AUTH:
            if (!_state.IsUnAuth()) {
                _state.ToUnAuth();
            } else {
                PrintNotRole();
                _logger->Log(ERROR, "No Priveleges");
            }
            break;

        case AUTH:
            if (_state.IsUnAuth())
            {
                PrivilegeLvl role = _controller->TryToAuthorize();
                switch (role) {
                    case USER:
                        _state.ToUserAuth();
                        break;
                    case ADMIN:
                        _state.ToAdminAuth();
                        break;
                    default:
                        break;
                }
            } else {
                PrintNotRole();
                _logger->Log(ERROR, "No Priveleges");
            }
            break;

        case REGISTER:
            if (_state.IsUnAuth())
            {
                _controller->TryToRegister();
                _state.ToUserAuth();
            }
            else
                PrintNotRole();
            _logger->Log(ERROR, "No Priveleges");
            break;

        case LOAD_IMAGE:
            if (_state.IsAdminAuth()) {
                std::string path;
                std::cout << "Введите путь к изображению: ";
                std::cin >> path;
                _image_manager->LoadImage(path);
            }
            else {
                PrintNotRole();
                _logger->Log(ERROR, "No Priveleges");
            }
            break;

        case DELETE_IMAGE:
            if (_state.IsAdminAuth()) {
                int id;
                std::cout << "Введите id изображения, которое хотите удалить: ";
                std::cin >> id;
                _image_manager->DeleteImage(id);
            }
            else {
                PrintNotRole();
                _logger->Log(ERROR, "No Priveleges");
            }
            break;

        case CREATE_MARK:
            if (_state.IsAdminAuth()) {
                try {
                    std::string name;
                    std::cout << "Введите название метки: ";
                    std::cin >> name;
                    _mark_manager->CreateMark(name);
                }
                catch (const std::exception &e) {
                    std::cout << e.what();
                    _logger->Log(ERROR, e.what());
                }
            }
            else {
                PrintNotRole();
                _logger->Log(ERROR, "No Priveleges");
            }
            break;

        case CREATE_DATA_FILE:
            if (_state.IsAdminAuth()) {
                try {
                    std::string path;
                    std::cout << "Введите путь к файлу:\n";
                    std::cin >> path;
                    _datafile_manager->CreateCoordFile(path);
                    _datafile_manager->CreateMarkedObjectFile(path);
                }
                catch (const std::exception &e) {
                    std::cout << e.what();
                    _logger->Log(ERROR, e.what());
                }
            }
            else {
                PrintNotRole();
                _logger->Log(ERROR, "No Priveleges");
            }
            break;

        case DELETE_MARKED_OBJECT:
            if (_state.IsUserAuth()) {
                try {
                    int id;
                    std::cout << "Введите id изображения, с которого хотите удалить объект:";
                    std::cin >> id;
                    Image image = _image_manager->GetImageById(id);
                    std::cout << "Объекты:\n";
                    _controller->OutputMarkedObjectsOfImage(image);
                    std::cout << "Введите id объекта, который хотите удалить:";
                    std::cin >> id;
                    _image_manager->DeleteMarkedObjectFromImage(image, id);
                }
                catch (const std::exception &e) {
                    std::cout << e.what();
                    _logger->Log(ERROR, e.what());
                }
            }
            else {
                PrintNotRole();
                _logger->Log(ERROR, "No Priveleges");
            }
            break;

        case GET_IMAGES:
            if (_state.IsUserAuth()) {
                try {
                    std::vector<Image> images = _image_manager->GetAllImages();
                    if (!images.empty()) {
                        _controller->OutpuImages(images);
                    }
                    else {
                        std::cout << "Нет изображений";
                    }
                }
                catch (const std::exception &e) {
                    std::cout << e.what();
                    _logger->Log(ERROR, e.what());
                }
            }
            else {
                PrintNotRole();
                _logger->Log(ERROR, "No Priveleges");
            }
            break;

        case LABEL_IMAGE:
            if (_state.IsUserAuth()) {
                try {
                    std::vector<Image> images = _image_manager->GetAllImages();
                    if (!images.empty()) {
                        _controller->OutpuImages(images);
                        int id;
                        std::cout << "Введите id изображения, которое хотите разметить:";
                        std::cin >> id;
                        Image image = _image_manager->GetImageById(id);
                        _controller->LabelImage(image);
                    }
                    else {
                        std::cout << "Нет изображений";
                    }
                }
                catch (const std::exception &e) {
                    std::cout << e.what();
                    _logger->Log(ERROR, e.what());
                }
            }
            else {
                PrintNotRole();
                _logger->Log(ERROR, "No Priveleges");
            }
            break;

        case GET_MARKED_OBJECTS_OF_IMAGE:
            if (_state.IsUserAuth()) {
                try {
                    std::vector<Image> images = _image_manager->GetAllImages();
                    if (!images.empty()) {
                        _controller->OutpuImages(images);
                        int id;
                        std::cout << "Введите id изображения, объекты которого хотите получить:";
                        std::cin >> id;
                        Image image = _image_manager->GetImageById(id);
                        std::cout << "Объекты:\n";
                        _controller->OutputMarkedObjectsOfImage(image);
                    }
                    else {
                        std::cout << "Нет изображений";
                    }

                }
                catch (const std::exception &e) {
                    std::cout << e.what();
                    _logger->Log(ERROR, e.what());
                }
            }
            else {
                PrintNotRole();
                _logger->Log(ERROR, "No Priveleges");
            }
            break;
    }
}