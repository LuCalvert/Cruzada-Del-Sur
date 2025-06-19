#include "CampoDeBatalla.h"
#include <iostream>


CampoDeBatalla::CampoDeBatalla(Mapa& mapa, Jugador& jugador1, Jugador& jugador2)
	: mapa(mapa), jugador1(jugador1), jugador2(jugador2), jugadorActual(&jugador1), terminado(false) {
}

void CampoDeBatalla::inicializarAcciones() {
	acciones[COLOCAR_CARTA] = [this]() { colocarCarta(); };
	acciones[MOVER_CARTA] = [this]() { moverCarta(); };
	acciones[ATACAR_CARTA] = [this]() { atacarCarta(); };
	acciones[ROBAR_CARTA] = [this]() { 	jugadorActual->RobarCarta(); };
	acciones[VER_CARTAS_JUGADOR] = [this]() { jugadorActual->MostrarEstado(); };
	acciones[VER_CARTAS_TABLERO] = [this]() { mapa.MostrarCartasJugador(jugadorActual->GetNombre());};
	acciones[PASAR_TURNO] = [this]() { pasarTruno(); };
	acciones[SALIR] = [this]() { terminado = true; };
}

void CampoDeBatalla::imprimirMenu() {
	std::cout << "\nSelecciona una accion:\n";
	std::cout << "1. Colocar carta\n";
	std::cout << "2. Mover carta\n";
	std::cout << "3. Atacar carta\n";
	std::cout << "4. Robar carta\n";
	std::cout << "5. Ver cartas en mano\n";
	std::cout << "6. Ver cartas en el tablero\n";
	std::cout << "7. Pasar turno\n";
	std::cout << "8. Salir (cerrar juego)\n\n";
}

void CampoDeBatalla::colocarCarta() {
	mapa.MostrarTablero();
	acciones[VER_CARTAS_JUGADOR]();

	int idCarta, fila, columna;
	std::cout << "\nSelecciona el ID de la carta a colocar: ";
	std::cin >> idCarta;

	std::shared_ptr <Carta> carta = jugadorActual->GetCarta(idCarta);
	if (!carta) {
		return;
	} 
	
	if (carta->GetTipo() == ETipoCarta::Reabastecimiento) {
		std::shared_ptr<CartaReabastecimiento> reabast = std::dynamic_pointer_cast<CartaReabastecimiento>(carta);
		if (reabast->getTipoReabast() == ETipoReabastecimiento::Energia) { // Energia
			jugadorActual->RegenerarEnergia(reabast->getReabastecimiento());
			return;
		}
	}

	std::cout << "Selecciona la fila y columna para colocar la carta: ";
	std::cin >> fila >> columna;

	if (mapa.ColocarCarta(fila, columna, carta, jugadorActual->GetNombre())) {
		jugadorActual->JugarCarta(idCarta);
		std::cout << "Carta colocada exitosamente.\n";
	}
	mapa.MostrarTablero();
}

void CampoDeBatalla::moverCarta() {
	mapa.MostrarTablero();
	acciones[VER_CARTAS_TABLERO]();

	int fila, columna, nuevaFila, nuevaColumna;
	std::cout << "\nSelecciona la fila y columna de la carta a mover: ";
	std::cin >> fila >> columna;

	std::shared_ptr<CartaTropa> carta = mapa.getCarta(fila, columna, jugadorActual->GetNombre());
	if (!carta) {
		std::cout << "\nNo hay carta de " << jugadorActual->GetNombre() << " en esa posicion.\n";
		return;
	}

	// Caso: energia de mov es total
	if (jugadorActual->GetEnergia() <= carta->getEnergiaMov()) {
		std::cout << "\nNo tienes suficiente energia para mover la carta.\n";
		return;
	}

	std::cout << "Selecciona la nueva fila y columna para mover la carta: ";
	std::cin >> nuevaFila >> nuevaColumna;

	if ((std::abs(fila - nuevaFila) + std::abs(columna - nuevaColumna)) > carta->MaxMovs()) {
		std::cout << "\nNo puedes mover la carta a esa posicion, supera el maximo de movimientos.\n";
		return;
	}

	mapa.MoverCarta(jugadorActual->GetNombre(), fila, columna, nuevaFila, nuevaColumna);
	mapa.MostrarTablero();
}

//revisar
void CampoDeBatalla::atacarCarta() {
	mapa.MostrarTablero();
	acciones[VER_CARTAS_TABLERO]();

	int filaAtacante, columnaAtacante, filaDefensor, columnaDefensor;
	std::cout << "Selecciona la fila y columna de la carta atacante: ";
	std::cin >> filaAtacante >> columnaAtacante;
	std::shared_ptr<CartaTropa> atacante = mapa.getCarta(filaAtacante, columnaAtacante, jugadorActual->GetNombre());
	
	if (jugadorActual->GetEnergia() <= atacante->getEnergiaAtaque()) {
		std::cout << "No tienes suficiente energia para atacar.\n";
		return;
	}
	if (!atacante) {
		std::cout << "No hay carta atacante en esa posicion.\n";
		return;
	}

	std::cout << "Selecciona la fila y columna de la carta defensora: ";
	std::cin >> filaDefensor >> columnaDefensor;

	std::string jugadorDefensor = (jugadorActual == &jugador1) ? jugador2.GetNombre() : jugador1.GetNombre();
	std::shared_ptr<CartaTropa> defensor = mapa.getCarta(filaDefensor, columnaDefensor, jugadorDefensor);

	if (!defensor) {
		std::cout << "No hay carta defensora en esa posicion.\n";
		return;
	}

	if ((std::abs(filaAtacante - filaDefensor) + std::abs(columnaAtacante - columnaDefensor)) > atacante->getDistanciaDelGolpe()) {
		std::cout << "\nNo puedes atacar a esa carta, esta fuera del rango de ataque.\n";
		return;
	}

	int ataque = atacante->Atacar();
	jugadorActual->UsarEnergia(atacante->getEnergiaAtaque());
	defensor->RecibirDanio(ataque);

	if (!defensor->EstaVivo()) {
		mapa.EliminarCarta(jugadorDefensor, filaDefensor, columnaDefensor);  // Elimina la carta del tablero
		std::cout << defensor->GetNombre() << " ha sido destruida.\n";
	}

	mapa.MostrarTablero();
}

void CampoDeBatalla::pasarTruno() {
	jugadorActual->PasarTurno();
	if (jugadorActual == &jugador1) {
		jugadorActual = &jugador2;
	} else {
		jugadorActual = &jugador1;
	}
	std::cout << "Turno de " << jugadorActual->GetNombre() << "\n";
	mapa.MostrarTablero();
}

void CampoDeBatalla::iniciarBatalla() {
	inicializarAcciones();
	std::system("clear");
	
	std::cout << "Iniciando batalla entre " << jugador1.GetNombre() << " y " << jugador2.GetNombre() << "\n";

	mapa.MostrarTablero();
	std::cout << "Turno de " << jugadorActual->GetNombre() << "\n";
	while (!terminado) {
		imprimirMenu();
		
		int accion;
		std::cin >> accion;
		if (!acciones.count(accion)) {
			std::cout << "Accion no valida. Por favor, elige una accion entre las opciones posibles.\n";
			continue;
		}
		std::system("clear"); // Limpia la consola para una mejor visualizacion
		acciones[accion]();

		if (jugadorActual->GetEnergia() <= 0) {
			std::cout << jugadorActual->GetNombre() << " no tiene energia suficiente para realizar acciones.\n";
			pasarTruno();
		}
	}
}

