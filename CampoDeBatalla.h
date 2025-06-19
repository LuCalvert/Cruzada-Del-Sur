#pragma once
#include "Mapa.h"
#include "Jugador.h"
#include <unordered_map>
#include <functional>

enum Accion {
	COLOCAR_CARTA = 1, // num de carta en mano, seguido de fila y col
	MOVER_CARTA, // seguido de espera fila y col, seguido de fila y col nuevos
	ATACAR_CARTA, // seguido de fila y col del atacante, seguido de fila y col del defensor
	ROBAR_CARTA,
	VER_CARTAS_JUGADOR,
	VER_CARTAS_TABLERO,
	PASAR_TURNO,
	SALIR
};

class CampoDeBatalla {
private:
	Mapa& mapa;
	Jugador& jugador1;
	Jugador& jugador2;

	Jugador* jugadorActual;
	bool terminado;

	std::unordered_map<int, std::function<void()>> acciones;
	void inicializarAcciones();
	void imprimirMenu();

	void colocarCarta();
	void moverCarta();
	void atacarCarta();
	void pasarTruno();

public:
	CampoDeBatalla(Mapa& mapa, Jugador& jugador1, Jugador& jugador2);

	void iniciarBatalla();
};

