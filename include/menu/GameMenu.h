#pragma once
#include <string>

class GameMenu {
private:
    int selectedButton = 0;
    std::string play     = "Играть";
    std::string settings = "Настройки";
    std::string quit     = "Выйти";
    std::string redactor = "Редактор";
    std::string symbol   = "<";

    int width;
    int height;

    const char* menus[5][14] = {
        {"#"," ","#"," ","#","#"," ","#","#","#"," ","#"," ","#"},
        {"#","#","#"," ","#"," "," ","#"," ","#"," ","#"," ","#"},
        {"#","#","#"," ","#","#"," ","#"," ","#"," ","#"," ","#"},
        {"#"," ","#"," ","#"," "," ","#"," ","#"," ","#"," ","#"},
        {"#"," ","#"," ","#","#"," ","#"," ","#"," ","#","#","#"}
    };

    void showMenuWord();
    void showMenu();

public:
    GameMenu();
    int getInputMenu();
};
