#pragma once

#include "Carta.h"
#include "DatosConstCartaReabast.h"

#include <memory>

class CartaReabastecimiento : public Carta {
private:
	std::shared_ptr<DatosCartaReabast> DatosBase;

public:
	CartaReabastecimiento(std::shared_ptr<DatosCartaReabast> datosBase);

	ETipoReabastecimiento getTipoReabast() const;
	int getReabastecimiento() const;

	void MostrarEstado() override;

	virtual ~CartaReabastecimiento() = default;
};

