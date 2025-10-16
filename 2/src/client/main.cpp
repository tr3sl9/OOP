#include <iostream>
#include "dialog.h"

int main() {
    try {
        Dialog::run();
    }
    catch (const std::exception& e) {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}