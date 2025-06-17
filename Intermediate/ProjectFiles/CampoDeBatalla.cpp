#include "CampoDeBatalla.h"
#include <iostream>

CampoDeBatalla::CampoDeBatalla(Mapa& mapa, Jugador& jugador1, Jugador& jugador2)
	: mapa(mapa), jugador1(jugador1), jugador2(jugador2), jugadorActual(jugador1), terminado(false) {
}

void CampoDeBatalla::inicializarAcciones() {
	acciones[COLOCAR_CARTA] = [this]() { colocarCarta(); };
	acciones[MOVER_CARTA] = [this]() { moverCarta(); };
	acciones[ATACAR_CARTA] = [this]() { atacarCarta(); };
	acciones[VER_CARTAS_JUGADOR] = [this]() { jugadorActual.MostrarEstado(); };
	acciones[VER_CARTAS_TABLERO] = [this]() { mapa.MostrarCartasJugador(jugadorActual.GetNombre());};
	acciones[VER_TABLERO] = [this]() { mapa.MostrarTablero(); };
	acciones[PASAR_TURNO] = [this]() { pasarTruno(); };
	acciones[SALIR] = [this]() { terminado = true; };
}

void CampoDeBatalla::imprimirMenu() {
	std::cout << "Selecciona una acción:\n";
	std::cout << "1. Colocar carta (ver tablero y cartas en mano previamente)\n";
	std::cout << "2. Mover carta (ver tabler y cartas en tablero previamente)\n";
	std::cout << "3. Atacar carta (ver tabler y cartas en tablero previamente)\n";
	std::cout << "4. Ver cartas en mano\n";
	std::cout << "5. Ver cartas en el tablero\n";
	std::cout << "6. Ver tablero\n";
	std::cout << "7. Pasar turno\n";
	std::cout << "8. Salir (cerrar juego)\n";
}

void CampoDeBatalla::colocarCarta() {
	int idCarta, fila, columna;
	std::cout << "Selecciona el ID de la carta a colocar: ";
	std::cin >> idCarta;
	std::cout << "Selecciona la fila y columna para colocar la carta: ";
	std::cin >> fila >> columna;
	std::shared_ptr <Carta> carta = jugadorActual.GetCarta(idCarta);
	if (!carta) {
		return;
	}
	if (mapa.ColocarCarta(fila, columna, carta, jugadorActual.GetNombre())) {
		jugadorActual.JugarCarta(idCarta);
		std::cout << "Carta colocada exitosamente.\n";
	}
}

void CampoDeBatalla::moverCarta() {
	int fila, columna, nuevaFila, nuevaColumna;
	std::cout << "Selecciona la fila y columna de la carta a mover: ";
	std::cin >> fila >> columna;
	std::cout << "Selecciona la nueva fila y columna para mover la carta: ";
	std::cin >> nuevaFila >> nuevaColumna;
	if (mapa.getCarta(fila, columna, jugadorActual.GetNombre())) {
		mapa.MoverCarta(jugadorActual.GetNombre(), nuevaFila, nuevaColumna);
	}
}

void CampoDeBatalla::atacarCarta() {
	int filaAtacante, columnaAtacante, filaDefensor, columnaDefensor;
	std::cout << "Selecciona la fila y columna de la carta atacante: ";
	std::cin >> filaAtacante >> columnaAtacante;
	std::shared_ptr<CartaTropa> atacante = mapa.getCarta(filaAtacante, columnaAtacante, jugadorActual.GetNombre());
	
	if (jugadorActual.GetEnergia() <= atacante->getEnergiaAtaque()) {
		std::cout << "No tienes suficiente energía para atacar.\n";
		return;
	}

	std::cout << "Selecciona la fila y columna de la carta defensora: ";
	std::cin >> filaDefensor >> columnaDefensor;
	std::shared_ptr<CartaTropa> defensor = mapa.getCarta(filaDefensor, columnaDefensor, 
		jugadorActual.GetNombre() == jugador1.GetNombre() ? jugador2.GetNombre() : jugador1.GetNombre());

	if (!atacante) {
		std::cout << "No hay carta atacante en esa posición.\n";
		return;
	}
	if (!defensor) {
		std::cout << "No hay carta defensora en esa posición.\n";
		return;
	}

	int ataque = atacante->Atacar();
	jugadorActual.UsarEnergia(atacante->getEnergiaAtaque());
	defensor->RecibirDanio(ataque);

	if (!defensor->EstaVivo()) {
		mapa.MoverCarta(jugadorActual.GetNombre(), filaDefensor, columnaDefensor); // Elimina la carta del tablero
		std::cout << defensor->GetNombre() << " ha sido destruida.\n";
	}
}

void CampoDeBatalla::pasarTruno() {
	jugadorActual.PasarTurno();
	if (jugadorActual.GetNombre() == jugador1.GetNombre()) {
		jugadorActual = jugador2;
	} else {
		jugadorActual = jugador1;
	}
	std::cout << "Turno de " << jugadorActual.GetNombre() << "\n";
	mapa.MostrarTablero();
}

void CampoDeBatalla::iniciarBatalla() {
	inicializarAcciones();
	
	std::cout << "Iniciando batalla entre " << jugador1.GetNombre() << " y " << jugador2.GetNombre() << "\n";

	mapa.MostrarTablero();
	std::cout << "Turno de " << jugadorActual.GetNombre() << "\n";
	while (!terminado) {
		imprimirMenu();
		
		int accion;
		std::cin >> accion;
		if (!acciones.count(accion)) {
			std::cout << "Acción no válida. Por favor, elige una acción entre las opciones posibles.\n";
			continue;
		}
		acciones[accion]();

		if (jugadorActual.GetEnergia() <= 0) {
			std::cout << jugadorActual.GetNombre() << " no tiene energía suficiente para realizar acciones.\n";
			pasarTruno();
		}
	}
}

