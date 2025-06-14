#pragma once

#include "Carta.h"
#include <vector>

class Mapa {
private:
    static const int FILAS = 5;
    static const int COLUMNAS = 5;
    int* tablero[FILAS][COLUMNAS];

	std::string JugadorA;
	std::string JugadorB;

	std::vector <Carta*> cartasJugadorA;
	std::vector <Carta*> cartasJugadorB;

public:
    Mapa(std::string jugadorA, std::string jugadorB);
    bool ColocarCarta(int fila, int columna, Carta* carta, std::string jugador);
    void MostrarTablero() const;
	void MostrarCartasJugadorA() const;
	void MostrarCartasJugadorB() const;

	std::vector<Carta*> GetCartasJugador(std::string jugador) const;
};
