#include "Jugador.h"
#include <iostream>

#define MAX_VIDA 30
#define ENERGIA_INI 10

Jugador::Jugador(std::string nombre) : Nombre(nombre), Vida(MAX_VIDA), Energia(ENERGIA_INI), EnergiaMax(ENERGIA_INI) {}


// -------------- Setters --------------

void Jugador::RobarCarta() {
    if (!Mazo.empty()) {
        Carta* carta = Mazo.back();
        Mano.push_back(carta);
        Mazo.pop_back();
    }
    else {
		std::cout << "El mazo esta vacio, no puedes robar mas cartas.\n";
    }
}

void Jugador::JugarCarta(int indice) {
    if (indice < 0 || indice >= Mano.size()) return;
    Carta* carta = Mano[indice];
    if (carta->GetCostoUso() <= Energia) {
        Energia -= carta->GetCostoUso();
        carta->AplicarEfecto();
        Descarte.push_back(carta);
        Mano.erase(Mano.begin() + indice);
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

void Jugador::RegenerarEnergia(int cantidad) {
    Energia += cantidad;
}

// -------------- Funciones de turno y batalla --------------

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

// -------------- Getters --------------

bool Jugador::EstaVivo() const {
    return Vida > 0;
}

std::string Jugador::GetNombre() const {
	return Nombre;
}

void Jugador::MostrarEstado() const {
    std::cout << "Jugador: " << Nombre << ", Vida: " << Vida << ", Energia: " << Energia << "\n";
	std::cout << "Cartas en mano: " << Mano.size() << ", Cartas en mazo: " << Mazo.size() << ", Cartas en descarte: " << Descarte.size() << "\n";
	std::cout << "Cartas en mano:\n";
    int i = 0;
	for (const auto& carta : Mano) {
		std::cout << i << "- " << carta->GetNombre() << " Costo: " << carta->GetCostoUso() << " Costo Ataque: " << carta->GetCostoAtaque() 
            << " Costo Mov: " << carta->GetCostoMov() << "\n";
		i++;
	}
}
