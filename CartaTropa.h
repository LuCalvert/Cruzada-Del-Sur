#pragma once

#include "Carta.h"
#include "DatosConstCartaTropa.h"

#include <memory>

class CartaTropa : public Carta {
private:
    std::shared_ptr<DatosCartaTropa> DatosBase;

    int Municiones;
    int Defensa;

public:
    CartaTropa(std::shared_ptr<DatosCartaTropa> datosBase);

    int getEnergiaAtaque() const;
	int getEnergiaMov() const;
    int getDistanciaDelGolpe() const;
    bool getMunicionesInfinitas() const;

    int Atacar();
    int MaxMovs() const;

    bool EstaVivo() const;

    void RecibirDanio(int danio);
    void ReestablecerMuniciones(int municiones);
	void AgregarVida(int vida);

	void MostrarEstado() override;

};
