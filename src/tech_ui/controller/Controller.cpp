#include "Controller.h"

Controller::Controller(AccountManager &account_manager, LabelingManager &labeling_manager, MarkManager &mark_manager, Logger &logger)
{
    _account_manager = &account_manager;
    _labeling_manager = &labeling_manager;
    _mark_manager = &mark_manager;
    _login = std::string();
    _password = std::string();
    _logger = &logger;
}

Controller::Controller() {}

bool Controller::IsAuthorized(std::string login)
{
    return _account_manager->UserExist(login);
}

PrivilegeLvl Controller::TryToAuthorize()
{
    PrivilegeLvl result = NOT_AUTH;
    std::cout << "Введите логин:";
    std::cin >> _login;
    try
    {
        if (_account_manager->UserExist(_login))
        {
            std::cout << "Введите пароль:";
            std::cin >> _password;
            User tmpUser = _account_manager->GetUserByLogin(_login);
            if (tmpUser.GetPassword() == _password)
            {
                result = tmpUser.GetPrivilegeLvl();
                _logger->Log(INFO, "Authentification success");
                std::cout << "Успешно вошли";
            }
            else {
                std::string msg = "Wrong password";
                _logger->Log(WARNING, msg);
                throw WrongPasswordException(msg);
            }
        }
        else{
            std::string msg = "Wrong login";
            _logger->Log(WARNING, msg);
            throw UserNotExistException (msg);
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
        _logger->Log(ERROR, e.what());
    }
    return result;
}

PrivilegeLvl Controller::TryToRegister()
{
    PrivilegeLvl result = NOT_AUTH;
    std::cout << "Введите логин:";
    std::cin >> _login;
    try
    {
        if (!_account_manager->UserExist(_login))
        {
            std::cout << "Введите пароль:";
            std::cin >> _password;
            User tmpUser = _account_manager->CreateUser(_login, _password);
            result = tmpUser.GetPrivilegeLvl();
            std::cout << "Успешно зарегистрировались и вошли";
        }
        else{
            std::string msg = "User already exist";
            _logger->Log(WARNING, msg);
            throw UserNotExistException (msg);
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
        _logger->Log(ERROR, e.what());
    }
    return result;
}

int Controller::ChooseShape()
{
    int res = -1;
    while (res < 0 || res > 2) {
        std::cout << CHOOSE_SHAPE;
        std::cin >> res;
    }
    return res;
}

Mark Controller::ChooseMark()
{
    std::vector<Mark> marks = _mark_manager->GetAllMarks();
    if (marks.empty()) {
        std::string msg = "";
        _logger->Log(WARNING, "No Marks");
        throw NoDataException(msg);
    }
    else {
        std::cout << "Выберите нужную метку:\n";
    }
    for (auto & mark : marks) {
        std::cout << mark.GetMarkId() << ". " << mark.GetName() << std::endl;
    }
    int id = -1;
    while (id < 1 || id > marks.size()) {
        std::cout << "Введите id нужной метки: ";
        std::cin >> id;
    }
    return _mark_manager->GetMarkById(id);
}

void Controller::OutputImage(Image &image) {
    cv::startWindowThread();
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display Image", image.GetImage());
    cv::waitKey(5);
}

void Controller::OutputMarkedObjectsOfImage(Image &image) {
    std::vector<MarkedObject> marked_objects = image.GetMarkedObjects();
    std::vector<Dot> coords;
    for (int i = 0; i < marked_objects.size(); i++) {
        std::cout << marked_objects[i].GetMarkedObjectId() << ". " << marked_objects[i].GetMark().GetName() << std::endl;
        coords = marked_objects[i].GetCoords();
        for (int j = 0; j < coords.size(); j++) {
            std::cout << "    (" << coords[j].GetX() << "; " << coords[j].GetY() << ")" << std::endl;
        }
    }
}

void Controller::OutpuImages(std::vector<Image> &images) {
    for (auto & image : images) {
        std::cout << image.GetImageId() << ". " << image.GetPath() << std::endl;
    }
}


void Controller::LabelImage(Image &image)
{
    int res = ChooseShape();
    int x, y, r;
    Mark mark{};
    std::vector<Dot> coords;
    Dot center, radius;

    switch (res)
    {
        case CIRC:
            std::cout << "Введите координату x центра:";
            std::cin >> x;
            std::cout << "Введите координату y центра:";
            std::cin >> y;
            std::cout << "Введите радиус:";
            std::cin >> r;
            center.SetX(x);
            center.SetY(y);
            radius.SetX(r);
            radius.SetY(r);
            try {
                mark = ChooseMark();
            }
            catch (const Exception &e) {
                std::cout << "Нет меток!";
                _logger->Log(ERROR, "No marks");
                return;
            }
            _labeling_manager->LabelImageCircle(image, center, radius, mark);

            break;

        case SQUARE:
            std::cout << "Введите координаты двух диагональных точек прямоугольника:\n";
            std::cout << "Введите координату x 1 точки:";
            std::cin >> x;
            std::cout << "Введите координату y 1 точки:";
            std::cin >> y;
            coords.emplace_back(x, y);
            std::cout << "Введите координату x 2 точки:";
            std::cin >> x;
            std::cout << "Введите координату y 2 точки:";
            std::cin >> y;
            coords.emplace_back(x, y);

            try {
                mark = ChooseMark();
            }
            catch (const Exception &e) {
                std::cout << "Нет меток!";
                _logger->Log(ERROR, "No marks");
                return;
            }
            _labeling_manager->LabelImagePolygon(image, coords, mark);
            break;

        case POLYG:
            int n;
            std::cout << "Введите желаемое количество точек для выделения:\n";
            std::cin >> n;
            for (int i = 0; i < n; i++) {
                std::cout << "Введите координату x " << i << " точки:";
                std::cin >> x;
                std::cout << "Введите координату y " << i << " точки:";
                std::cin >> y;
                coords.emplace_back(x, y);
            }
            try {
                mark = ChooseMark();
            }
            catch (const Exception &e) {
                std::cout << "Нет меток!";
                _logger->Log(ERROR, "No marks");
                return;
            }
            _labeling_manager->LabelImagePolygon(image, coords, mark);
            break;
    }
}

std::string Controller::GetLogin()
{
    return _login;
}
