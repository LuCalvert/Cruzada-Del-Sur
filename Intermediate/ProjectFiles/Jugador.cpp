#include "Jugador.h"
#include <iostream>

#define MAX_VIDA 30
#define ENERGIA_INI 10

Jugador::Jugador(std::string nombre) : Nombre(nombre), Vida(MAX_VIDA), Energia(ENERGIA_INI), EnergiaMax(ENERGIA_INI) {}

// -------------- Acciones --------------

void Jugador::RobarCarta() {
    if (!Mazo.empty()) {
		int random = rand() % Mazo.size(); // Genera un indice aleatorio dentro del rango del mazo
		std::shared_ptr<Carta> carta = Mazo[random];
        Mano.push_back(carta);
		Mazo.erase(Mazo.begin() + random);
    }
    else {
		std::cout << "El mazo esta vacio, no puedes robar mas cartas.\n";
    }
}

void Jugador::JugarCarta(int indice) {
	if (indice < 0 || indice >= Mano.size()) {
		std::cout << "Indice de carta invalido.\n";
		return;
	}
	std::shared_ptr<Carta> carta = Mano[indice];
	if (carta->GetCostoUso() <= Energia) {
		Energia -= carta->GetCostoUso();
		Descarte.push_back(carta);
		Mano.erase(Mano.begin() + indice);
		std::cout << "Has jugado la carta: " << carta->GetNombre() << "\n";
	}
	else {
		std::cout << "No tienes suficiente energia para jugar la carta: " << carta->GetNombre() << "\n";
	}
}

void Jugador::RecibirDanio(int cantidad) {
    Vida -= cantidad;
	if (Vida < 0) {
		Vida = 0; // Asegurarse de que la vida no sea negativa
		std::cout << Nombre << " ha sido derrotado.\n";
	}
	else {
		std::cout << Nombre << " recibio " << cantidad << " puntos de daño. \n Vida restante: " << Vida << "\n";
	}
}

void Jugador::UsarEnergia(int cantidad) {
	if (cantidad > Energia) {
		std::cout << "No tienes suficiente energia para usar esa cantidad.\n";
	}
	else {
		Energia -= cantidad;
		if (Energia < 0) {
			Energia = 0;
		}
		std::cout << Nombre << " ha usado " << cantidad << " puntos de energia. Energia restante: " << Energia << "\n";
	}
}

void Jugador::RegenerarEnergia(int cantidad) {
    Energia += cantidad;
}

void Jugador::PasarTurno() {
    EnergiaMax++;
    Energia = EnergiaMax;
}

void Jugador::PasarBatalla() {
	Vida = MAX_VIDA; 
	Energia = ENERGIA_INI; 
	Mazo.clear(); 
	Mano.clear();
	Descarte.clear();
}

void Jugador::AgregarCartaAMazo(std::shared_ptr<Carta> carta) {
	Mazo.push_back(carta);
}

// -------------- Getters --------------

bool Jugador::EstaVivo() const {
    return Vida > 0;
}

std::string Jugador::GetNombre() const {
	return Nombre;
}

int Jugador::GetVida() const {
	return Vida;
}

int Jugador::GetEnergia() const {
	return Energia;
}

std::shared_ptr<Carta> Jugador::GetCarta(int indice) const {
    if (indice < 0 || indice >= Mano.size()) return nullptr;
	std::shared_ptr<Carta> carta = Mano[indice];
    if (carta->GetCostoUso() <= Energia) {
        return carta;
    } else {
		std::cout << "No tienes suficiente energia para jugar la carta: " << carta->GetNombre() << "\n";
		return nullptr;
    }
}

// -------------- Visulizacion por consola --------------

void Jugador::MostrarEstado() const {
    std::cout << "Jugador: " << Nombre << ", Vida: " << Vida << ", Energia: " << Energia << "\n";
	std::cout << "Cartas en mano: " << Mano.size() << ", Cartas en mazo: " << Mazo.size() << ", Cartas en descarte: " << Descarte.size() << "\n";
	std::cout << "Cartas en mano:\n";
    int i = 0;
	for (const auto& carta : Mano) {
        std::cout << i << "- ";
        carta->MostrarEstado();
		i++;
	}
}
