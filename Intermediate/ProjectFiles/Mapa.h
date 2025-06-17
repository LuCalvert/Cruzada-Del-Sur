#pragma once

#include "CartaTropa.h"
#include "CartaReabastecimiento.h"
#include <vector>

class Mapa {
private:
	int Filas = 0;
	int Columnas = 0;
	std::vector<std::vector<int>> tablero;

	std::string JugadorA;
	std::string JugadorB;

	std::vector <std::pair< std::shared_ptr<CartaTropa>, std::pair<int, int>>> cartasJugadorA; // [Carta*, (fila, columna)]
	std::vector <std::pair< std::shared_ptr<CartaTropa>, std::pair<int, int>>> cartasJugadorB; // [Carta*, (fila, columna)]

	bool verificacionTablero(int fila, int columna) const;
public:
    Mapa(std::string jugadorA, std::string jugadorB, int filas, int columnas);

    bool ColocarCarta(int fila, int columna, std::shared_ptr<Carta> carta, std::string jugador);
	void MoverCarta(std::string jugador, int fila, int columna);

	std::shared_ptr<CartaTropa> getCarta(int fila, int columna, std::string jugador) const;
	//std::vector<Carta*> GetCartasJugador(std::string jugador) const;

    void MostrarTablero() const;
	void MostrarCartasJugador(std::string jugador) const;
};
