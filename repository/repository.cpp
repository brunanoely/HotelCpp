#include <filesystem>
#include <iostream>
#include <string>
#include <repository.h>

void verificarDiretorio() {
    if (!std::filesystem::exists(REPOSITORIO)) {
        std::filesystem::create_directory(REPOSITORIO);
    }
}
