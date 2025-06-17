#pragma once

#include "Carta.h"
#include "DatosConstCartaTropa.h"

class CartaTropa : public Carta {
private:
    std::shared_ptr<DatosCartaTropa> DatosBase;

    int Defensa;
    int Municiones;
    int id;

public:
    CartaTropa(std::shared_ptr<DatosCartaTropa> datosBase);

    int getEnergiaAtaque() const;
	int getEnergiaMov() const;
    bool getMunicionesInfinitas() const;

    int Atacar();
    int MaxMovs() const;

    bool EstaVivo() const;

    void RecibirDanio(int daño);
    void ReestablecerMuniciones(int municiones);
	void AgregarVida(int vida);

	void MostrarEstado() override;

};
