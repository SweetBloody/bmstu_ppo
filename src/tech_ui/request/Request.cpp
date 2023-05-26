#include "Request.h"

bool RequestHandler::check_is_number(std::string req)
{
    return !req.empty() && std::all_of(req.begin(), req.end(), ::isdigit);
}

REQUEST_KEYS RequestHandler::handle(std::string req)
{
    REQUEST_KEYS result = NOT_A_COMMAND;
    if (req.size() < 3 && check_is_number(req))
    {
        int num = std::stoi(req);
        if (num < NOT_A_COMMAND)
        {
            result = (REQUEST_KEYS) num;
        }
    }
    return result;
}