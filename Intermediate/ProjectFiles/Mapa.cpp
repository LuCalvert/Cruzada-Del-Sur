#include "Mapa.h"
#include <iostream>

Mapa::Mapa(std::string jugadorA, std::string jugadorB, int filas, int columnas) : 
	Filas(filas), Columnas(columnas), JugadorA(jugadorA), JugadorB(jugadorB) {
	tablero.resize(Filas, std::vector<int>(Columnas, 0));
}

// ---------------- Func Aux ----------------

bool verificacionCarta(std::pair<std::shared_ptr<CartaTropa>, std::pair<int, int>> carta, int id, int fila, int columna) {
	return carta.first->getId() == id && carta.second.first == fila && carta.second.second == columna;
}

bool Mapa::verificacionTablero(int fila, int columna) const {
	return (fila < 0 || fila >= Filas || columna < 0 || columna >= Columnas);
}

void mostrarCartas(const std::vector<std::pair<std::shared_ptr<CartaTropa>, std::pair<int, int>>>& cartas, bool enemigo) {
	for (const auto& par : cartas) {
		std::cout << "- ";
		if (enemigo) {
			std::cout << par.first->GetNombre() << " (ID: " << par.first->getId() << ") ";
		} else {
			par.first->MostrarEstado();
		}
		std::cout << "Posición: (" << par.second.first << ", " << par.second.second << ")\n";
	}
}

// ---------------- Acciones ----------------

bool Mapa::ColocarCarta(int fila, int columna, std::shared_ptr<Carta> carta, std::string jugador) {
    if (verificacionTablero(fila, columna)) return false;
    if (tablero[fila][columna] != 0 && carta->GetTipo() == ETipoCarta::Tropa) return false;

	std::vector <std::pair<std::shared_ptr<CartaTropa>, std::pair<int, int>>>& cartasJugador = (jugador == JugadorA) ? cartasJugadorA : cartasJugadorB;

	if (carta->GetTipo() == ETipoCarta::Tropa) {
		std::shared_ptr<CartaTropa> tropa = dynamic_pointer_cast<CartaTropa>(carta);
		if (tropa) {
			cartasJugador.push_back(std::make_pair(tropa, std::make_pair(fila, columna)));
			tablero[fila][columna] = carta->getId();
		}
	
	} else if (carta->GetTipo() == ETipoCarta::Reabastecimiento) {
		
		std::shared_ptr<CartaTropa> recibidor = getCarta(fila, columna, jugador);
		std::shared_ptr<CartaReabastecimiento> reabast = dynamic_pointer_cast<CartaReabastecimiento>(carta);
		if (reabast) {
			int reabastecimiento = (reabast)->getReabastecimiento();

			// se podria mejorar(?
			if (reabast->getTipoReabast() == ETipoReabastecimiento::Municiones) {
				recibidor->ReestablecerMuniciones(reabastecimiento);
			} else if (reabast->getTipoReabast() == ETipoReabastecimiento::Vida) {
				recibidor->AgregarVida(reabastecimiento);
			}
		}
	}
	
    return true;
}

// se puede mejorar
void Mapa::MoverCarta(std::string jugador, int fila, int columna) {  
   if (verificacionTablero(fila, columna)) {
       std::cout << "Movimiento fuera de los límites del tablero.\n";  
       return;  
   }  

   std::shared_ptr<CartaTropa> carta = getCarta(fila, columna, jugador);
   if (!carta) {  
       std::cout << "No hay carta en la posición especificada.\n";  
       return;  
   }  

   auto& cartas = (jugador == JugadorA) ? cartasJugadorA : cartasJugadorB;  
   for (auto& par : cartas) {  
	   if (verificacionCarta(par, carta->getId(), fila, columna)) {
           tablero[par.second.first][par.second.second] = 0; // limpio  
		   par.second = std::make_pair(fila, columna); // actualizo
           break;  
       }  
   }  

   tablero[fila][columna] = carta->getId();  

   std::cout << "Moviendo carta: " << carta->GetNombre() << " de " << jugador << " a (" << fila << ", " << columna << ").\n";  
}

// ---------------- Getters ----------------

std::shared_ptr<CartaTropa> Mapa::getCarta(int fila, int columna, std::string jugador) const {
	if (verificacionTablero(fila, columna)) return nullptr;

	int cartaId = tablero[fila][columna];
	if (cartaId == 0) return nullptr; // No hay carta en esa posición

	const auto& cartas = (jugador == JugadorA) ? cartasJugadorA : cartasJugadorB;
	for (const auto& par : cartas) {
		if (verificacionCarta(par, cartaId, fila, columna)) {
			return par.first;
		}
	}
	return nullptr; // Carta no encontrada
}

// ---------------- Visualizacion por consola ----------------

void Mapa::MostrarTablero() const {
    for (int i = 0; i < Filas; ++i) {
        for (int j = 0; j < Columnas; ++j) {
            std::cout << tablero[i][j] << " | ";
        }
        std::cout << "\n";
		for (int j = 0; j < Columnas; ++j) {
			std::cout << "----";
		}
    }
}

void Mapa::MostrarCartasJugador(std::string jugador) const {
	std::cout << "Cartas de " << jugador << ":\n";
	if (jugador == JugadorA) {
		mostrarCartas(cartasJugadorA, false);
		mostrarCartas(cartasJugadorB, true);
	} else if (jugador == JugadorB) {
		mostrarCartas(cartasJugadorB, false);
		mostrarCartas(cartasJugadorA, true);
	} else {
		std::cout << "Jugador no reconocido: " << jugador << "\n";
	}
}



