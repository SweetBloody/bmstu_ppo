#include "State.h"


AppState::AppState() {
    _appState = NO_AUTH;
}

STATES AppState::GetState() {
    return _appState;
}

void AppState::ToUserAuth() {
    if (_appState == NO_AUTH)
    {
        _appState = USER_AUTH;
    }
}

void AppState::ToAdminAuth() {
    if (_appState == NO_AUTH)
    {
        _appState = ADMIN_AUTH;
    }
}

void AppState::ToUnAuth() {
    if (_appState != NO_AUTH)
    {
        _appState = NO_AUTH;
    }
}

bool AppState::IsUserAuth() {
    return _appState == USER_AUTH;
}

bool AppState::IsAdminAuth() {
    return _appState == ADMIN_AUTH;
}

bool AppState::IsUnAuth() {
    return _appState == NO_AUTH;
}