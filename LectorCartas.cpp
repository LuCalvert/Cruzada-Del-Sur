#include "LectorCartas.h"

#include "CartaTropa.h"
#include "CartaReabastecimiento.h"
#include "json.hpp" // nlohmann::json
#include <fstream>
#include <iostream>

// Para un futuro usare DataTable de Unreal o un binario comprimido, de momento tengo que probar que funcione
using json = nlohmann::json;


// Codigo completamente modularizable y automatizable (lo hare despues de corroborar que funciona el juego)
std::vector<std::shared_ptr<Carta>> LectorCartas::LeerDesdeJSON(const std::string& rutaArchivo) {
    std::vector<std::shared_ptr<Carta>> cartas;

    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << rutaArchivo << "\n";
        return cartas;
    }

    json datos;
    archivo >> datos;

    for (const auto& item : datos) {
        std::string tipo = item.value("tipo", "");
        std::transform(tipo.begin(), tipo.end(), tipo.begin(), ::tolower);
        
        if (tipo == "tropa") {
            auto datosTropa = std::make_shared<DatosCartaTropa>();
        
            datosTropa->Nombre = item["nombre"];
            datosTropa->id = item["id"];
            datosTropa->CostoEnergiaUso = item["costo"];
            datosTropa->Ataque = item["ataque"];
            datosTropa->EnergiaAtaque = item["energiaAtq"]; // Campo correcto del JSON
            datosTropa->DefensaInicial = item["defensa"];
            datosTropa->DistanciaDeGolpe = item["distancia"];
            datosTropa->MaxMovimientos = item["movs"];
            datosTropa->EnergiaMov = item["energiaMovs"];
            datosTropa->MunicionesInfinitas = item["municionesInfinitas"];
        
            int municionesInic = item.value("municionesInic", -1);
        
            int cant = item["cantidadEnMazo"];
            for (int i = 0; i < cant; ++i) {
                auto carta = std::make_shared<CartaTropa>(datosTropa);
                if (municionesInic != -1) {
                    carta->ReestablecerMuniciones(municionesInic);
                }
                cartas.push_back(carta);
                // std::cout << "Carta tropa creada\n";
            }
        }        
        else if (tipo == "reabastecimiento") {
			auto datosReabastecimiento = std::make_shared<DatosCartaReabast>();

			datosReabastecimiento->Nombre = item["nombre"];
			datosReabastecimiento->CostoEnergiaUso = item["costo"];

			datosReabastecimiento->Reabastecimiento = item["reabastecimiento"];

            // Despues lo hare mas automatico(? quizas un switch...
			datosReabastecimiento->Tipo = ETipoReabastecimiento::Energia; // Por defecto, energia
			if (item["tipoReabastecimiento"] == "municiones") {
				datosReabastecimiento->Tipo = ETipoReabastecimiento::Municiones;
			}
			else if (item["tipoReabastecimiento"] == "vida") {
				datosReabastecimiento->Tipo = ETipoReabastecimiento::Vida;
			}

			int cant = item["cantidadEnMazo"];
            for (int i = 0; i < cant; ++i) {
                auto carta = std::make_shared<CartaReabastecimiento>(datosReabastecimiento);
                cartas.push_back(carta);
                // std::cout << "Carta reabastecimiento creada" << std::endl;
            }
        }
    }

    return cartas;
}
