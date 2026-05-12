#pragma once
#include <string>
#include <vector>

class ModeSelect {
private:
    int selectedButton = 0;
    int selectedCustomMap = 0;
    std::string story  = "История";
    std::string custom = "Кастомная карта";
    std::string sym    = "<";

    void showMode();
    void selectCustomMap(const std::vector<std::string>& maps);
    void selectAndEditCustomMap(const std::vector<std::string>& maps);

public:
    int getInputMode();
    int getInputCustomMap(const std::vector<std::string>& maps, bool flag);
};
