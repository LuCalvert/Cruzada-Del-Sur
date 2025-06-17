#include "CartaTropa.h"
#include <iostream>

CartaTropa::CartaTropa(std::shared_ptr<DatosCartaTropa> datosBase)
	: Carta(datosBase->Nombre, ETipoCarta::Tropa, datosBase->CostoEnergiaUso, datosBase->id),
	DatosBase(std::move(datosBase)), Municiones(0), Defensa(datosBase->DefensaInicial) {
}

// ---------------- Getters ----------------

int CartaTropa::getEnergiaAtaque() const {
	return DatosBase->EnergiaAtaque;
}

int CartaTropa::getEnergiaMov() const {
    return DatosBase->EnergiaMov;
}

bool CartaTropa::getMunicionesInfinitas() const {
	return DatosBase->MunicionesInfinitas;
}

int CartaTropa::Atacar() {
    std::cout << Nombre << " ataca con " << DatosBase->Ataque << " de fuerza.\n";
	if (DatosBase->MunicionesInfinitas || Municiones > 0)) {
		Municiones--;
		return DatosBase->Ataque;
	}
	return -1; // Si no tiene municiones, no puede atacar
}

int CartaTropa::MaxMovs() const {
    std::cout << Nombre << " se ha movido a una nueva posición.\n";
	return DatosBase->MaxMovimientos;
}

bool CartaTropa::EstaVivo() const {
	return Defensa > 0;
}

// ---------------- Acciones ----------------

void CartaTropa::RecibirDanio(int daño) {
	Defensa -= daño;
	if (Defensa < 0) Defensa = 0; // No puede tener defensa negativa
	std::cout << Nombre << " recibe " << daño << " de daño. Defensa restante: " << Defensa << ".\n";
}

void CartaTropa::ReestablecerMuniciones(int municiones) {
	if (DatosBase->MunicionesInfinitas) {
		Municiones = -1; // Municiones infinitas
		std::cout << Nombre << " tiene municiones infinitas.\n";
	}
	else {
		Municiones += municiones;
		std::cout << Nombre << " ha reestablecido sus municiones a " << Municiones << ".\n";
	}
}

void CartaTropa::AgregarVida(int vida) {
	Defensa += vida;
	std::cout << Nombre << " ha ganado " << vida << " de defensa. Defensa total: " << Defensa << ".\n";
}

void CartaTropa::MostrarEstado() {
	std::cout << "Carta Tropa: " << Nombre << ", " << "Costo de Uso: " << CostoEnergiaUso << ", "
		<< "Fuerza de Ataque: " << DatosBase->Ataque << ", Defensa: " << Defensa << ", "
		<< "Distancia de Golpe: " << DatosBase->DistanciaDeGolpe << ", Max Movimientos: " << DatosBase->MaxMovimientos << ", "
		<< "Municiones Restantes: " << (DatosBase->MunicionesInfinitas ? "infinitas" : std::to_string(Municiones)) << "\n";
}


