#pragma once

#include <string>
#include <vector>
#include "Carta.h"

class Jugador {
private:
    std::string Nombre;
    int Vida;
    int Energia;
    int EnergiaMax;

    std::vector<Carta*> Mazo;
    std::vector<Carta*> Mano;
    std::vector<Carta*> Descarte;

public:
    Jugador(std::string nombre);

    void RobarCarta();
    void JugarCarta(int indice); // por ahora sin mapa
    void RecibirDanio(int cantidad);
    void RegenerarEnergia(int cantidad);

    void PasarTurno();
    void PasarBatalla();

    bool EstaVivo() const;
    std::string GetNombre() const;

    void MostrarEstado() const;
};
