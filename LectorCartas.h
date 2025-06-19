#pragma once

#include <vector>
#include <memory>
#include "Carta.h"

class LectorCartas {
public:
    static std::vector<std::shared_ptr<Carta>> LeerDesdeJSON(const std::string& rutaArchivo);
};
