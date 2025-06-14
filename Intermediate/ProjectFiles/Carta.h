#pragma once

#include <string>

enum class ETipoCarta {
    Tropas,
    Reabastecimiento,
    Especial
};

class Carta {
protected:
    std::string Nombre;
    ETipoCarta Tipo;
    int CostoEnergiaMov;
	int CostoEnergiaAtaque;
    int CostoEnergiaUso;

public:
    Carta(std::string nombre, ETipoCarta tipo, int costoEnergiaMov, int costoEnergiaAtaque, int costoEnergiaUso);
    virtual ~Carta() = default;

    std::string GetNombre() const;
    ETipoCarta GetTipo() const;
    int GetCostoMov() const;
	int GetCostoAtaque() const;
	int GetCostoUso() const;

    virtual void AplicarEfecto(); // Podés hacer esto puro (virtual = 0) más adelante
	
};
