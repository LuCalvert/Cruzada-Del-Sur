#include "Mapa.h"
#include <iostream>

Mapa::Mapa(std::string jugadorA, std::string jugadorB) : JugadorA(jugadorA), JugadorB(jugadorB) {
    for (int i = 0; i < FILAS; ++i)
        for (int j = 0; j < COLUMNAS; ++j)
            tablero[i][j] = nullptr;
}

bool Mapa::ColocarCarta(int fila, int columna, Carta* carta, std::string jugador) {
    if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS) return false;
    if (tablero[fila][columna] != nullptr) return false;

	if (jugador == JugadorA) {
		cartasJugadorA.push_back(carta);
	}
	else if (jugador == JugadorB) {
		cartasJugadorB.push_back(carta);
	}
	else {
		std::cout << "Jugador no reconocido: " << jugador << "\n";
		return false;
	}

    tablero[fila][columna] = (int *)carta->GetTipo(); //a chequear conversion
    return true;
}

void Mapa::MostrarTablero() const {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            std::cout << (tablero[i][j] ? "X" : ".") << " ";
        }
        std::cout << "\n";
    }
}

void Mapa::MostrarCartasJugadorA() const {
	std::cout << "Cartas de " << JugadorA << ":\n";
	for (const auto& carta : cartasJugadorA) {
		std::cout << "- " << carta->GetNombre() << "\n";
	}
}

void Mapa::MostrarCartasJugadorB() const {
	std::cout << "Cartas de " << JugadorB << ":\n";
	for (const auto& carta : cartasJugadorB) {
		std::cout << "- " << carta->GetNombre() << "\n";
	}
}

std::vector<Carta*> Mapa::GetCartasJugador(std::string jugador) const {
	if (jugador == JugadorA) {
		return cartasJugadorA;
	}
	else if (jugador == JugadorB) {
		return cartasJugadorB;
	}
	else {
		std::cout << "Jugador no reconocido: " << jugador << "\n";
		return {};
	}
}
