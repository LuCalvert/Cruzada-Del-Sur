#pragma once

#include <string>

enum class ETipoCarta {
    Tropa,
    Reabastecimiento,
    Especial
};

class Carta {
protected:
    std::string Nombre;
    ETipoCarta Tipo;
    int id;
    int CostoEnergiaUso;

public:
    Carta(std::string nombre, ETipoCarta tipo, int costoEnergiaUso, int id);
    virtual ~Carta() = default;

    std::string GetNombre() const;
    ETipoCarta GetTipo() const;
	int GetCostoUso() const;
    int getId() const;
    
    virtual void MostrarEstado() = 0;
	
};
