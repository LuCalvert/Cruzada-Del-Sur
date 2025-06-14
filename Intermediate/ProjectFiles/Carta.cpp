#include "Carta.h"

Carta::Carta(std::string nombre, ETipoCarta tipo, int costoEnergiaMov, int costoEnergiaAtaque, int costoEnergiaUso)
    : Nombre(nombre), Tipo(tipo), CostoEnergiaMov(costoEnergiaMov), CostoEnergiaAtaque(costoEnergiaAtaque), CostoEnergiaUso(costoEnergiaUso) {
}

std::string Carta::GetNombre() const { return Nombre; }
ETipoCarta Carta::GetTipo() const { return Tipo; }
int Carta::GetCostoMov() const { return CostoEnergiaMov; }
int Carta::GetCostoAtaque() const { return CostoEnergiaAtaque; }
int Carta::GetCostoUso() const { return CostoEnergiaUso; }

void Carta::AplicarEfecto() {
    // Implementación genérica (o vacía)
}
