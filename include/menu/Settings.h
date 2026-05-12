#pragma once
#include <string>

class Settings {
public:
    static int selectedSpeed;
    static int selectedQuantity;
    static bool selectedRender;

private:
    int selectedButton = 0;
    int width;
    int height;

    std::string speedString(int sp);
    std::string renderString(bool val);

public:
    Settings();
    void showSettings();
    int getInputSettings();
};
