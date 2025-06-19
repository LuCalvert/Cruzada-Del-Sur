#pragma once
#include <string>

struct DatosCartaTropa {
    std::string Nombre;
    int CostoEnergiaUso;

    int id;

    int EnergiaAtaque;
	int EnergiaMov;
	
    int DistanciaDeGolpe;
    int MaxMovimientos;
    bool MunicionesInfinitas;
    
    int Ataque;
    int DefensaInicial;
};
