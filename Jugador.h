#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Carta.h"

class Jugador {
private:
    std::string Nombre;
    int Vida;
    int Energia;
    int EnergiaMax;

    std::vector<std::shared_ptr<Carta>> Mazo;
    std::vector<std::shared_ptr<Carta>> Mano;
    std::vector<std::shared_ptr<Carta>> Descarte;

public:
    Jugador(std::string nombre);

    void RobarCartas(int cantidad);

    void RobarCarta();
    void JugarCarta(int indice);
    void RecibirDanio(int cantidad);
    void UsarEnergia(int cantidad);
    void RegenerarEnergia(int cantidad);

    void PasarTurno();
    void PasarBatalla();

    void AgregarCartaAMazo(std::shared_ptr<Carta> carta);

    bool EstaVivo() const;
    std::string GetNombre() const;
	int GetVida() const;
	int GetEnergia() const;
    std::shared_ptr<Carta> GetCarta(int indice) const;

    void MostrarEstado() const;
};
