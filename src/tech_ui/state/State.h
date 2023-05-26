#ifndef SRC_STATE_H
#define SRC_STATE_H

enum STATES {
    NO_AUTH,
    USER_AUTH,
    ADMIN_AUTH
};

class AppState {
public:
    AppState();
    ~AppState() = default;
    STATES GetState();
    void ToUserAuth();
    void ToAdminAuth();
    void ToUnAuth();
    bool IsUnAuth();
    bool IsUserAuth();
    bool IsAdminAuth();
private:
    STATES _appState;
};


#endif //SRC_STATE_H
