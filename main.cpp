#include "CampoDeBatalla.h"
#include "LectorCartas.h"

int main() {

    // Cargar cartas desde el archivo
    LectorCartas lector;
    std::vector<std::shared_ptr<Carta>> cartasTropas = lector.LeerDesdeJSON("cartasTropas.json");
    std::vector<std::shared_ptr<Carta>> cartasReabast = lector.LeerDesdeJSON("cartasReabastecimiento.json");

    // Crear jugadores
    Jugador jugador1("RataA");
    Jugador jugador2("RataB");

    // Agregar cartas de tropas alternando entre jugadores
    for (size_t i = 0; i < cartasTropas.size(); ++i) {
        if (i % 2 == 0) {
            jugador1.AgregarCartaAMazo(cartasTropas[i]);
        } else {
            jugador2.AgregarCartaAMazo(cartasTropas[i]);
        }
    }

    // Agregar cartas de reabastecimiento alternando entre jugadores
    for (size_t i = 0; i < cartasReabast.size(); ++i) {
        if (i % 2 == 0) {
            jugador1.AgregarCartaAMazo(cartasReabast[i]);
        } else {
            jugador2.AgregarCartaAMazo(cartasReabast[i]);
        }
    }

    // Robar cartas iniciales
    jugador1.RobarCartas(4);
    jugador2.RobarCartas(4);

    // Crear mapa de 5x5
    Mapa mapa(jugador1.GetNombre(), jugador2.GetNombre(), 5, 5);

    // Crear campo de batalla
    CampoDeBatalla campo(mapa, jugador1, jugador2);

    // Iniciar la batalla
    campo.iniciarBatalla();

    return 0;
}
