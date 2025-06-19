#include "CartaReabastecimiento.h"
#include <iostream>

CartaReabastecimiento::CartaReabastecimiento(std::shared_ptr<DatosCartaReabast> datosBase)
	: Carta(datosBase->Nombre, ETipoCarta::Reabastecimiento, datosBase->CostoEnergiaUso, -1), DatosBase(datosBase) {
}

ETipoReabastecimiento CartaReabastecimiento::getTipoReabast() const {
	return DatosBase->Tipo;
}

int CartaReabastecimiento::getReabastecimiento() const {
	return DatosBase->Reabastecimiento;
}

void CartaReabastecimiento::MostrarEstado() {
	std::cout << "Carta de Reabastecimiento: " << DatosBase->Nombre << ", " << "Costo de uso: " << DatosBase->CostoEnergiaUso << ", "
		<< "Reabastece: " << DatosBase->Reabastecimiento << "\n";
}


