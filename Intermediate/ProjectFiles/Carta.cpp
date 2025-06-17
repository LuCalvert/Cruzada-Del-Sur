#include "Carta.h"

Carta::Carta(std::string nombre, ETipoCarta tipo, int costoEnergiaUso, int id)
    : Nombre(nombre), Tipo(tipo), id(id), CostoEnergiaUso(costoEnergiaUso) {
}

std::string Carta::GetNombre() const { return Nombre; }
ETipoCarta Carta::GetTipo() const { return Tipo; }
int Carta::GetCostoUso() const { return CostoEnergiaUso; }
int Carta::getId() const { return id; }

