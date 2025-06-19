#pragma once
#include <string>

enum class ETipoReabastecimiento {
	Energia,
	Municiones,
	Vida
};

struct DatosCartaReabast {
	std::string Nombre;
	int CostoEnergiaUso;

	ETipoReabastecimiento Tipo;

	int Reabastecimiento;
};