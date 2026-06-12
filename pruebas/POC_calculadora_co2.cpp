#include <iostream>
#include <vector>
#include <cmath>

struct FaseIncubacion {
    int numeroFase;
    float diaInicio;
    float porcentajeColonizado;
    float segVentilacion;
};

// Calcula la ventilación necesaria según etapa (CO2 objetivo)
std::vector<FaseIncubacion> calcularPlan(float dCol, float dFru, float pesoG, float caudal, int pwm) {
    std::vector<FaseIncubacion> plan;
    float dTotal = dCol + dFru;
    float caudalReal = caudal * (pwm / 100.0f);
    int nFases = 8;
    float deltaT = dTotal / nFases;

    for (int i = 0; i < nFases; i++) {
        FaseIncubacion f;
        f.numeroFase = i + 1;
        f.diaInicio = i * deltaT;

        // Estimar colonización (Funcion Sigmoide)
        float k = 9.19f / dCol;
        f.porcentajeColonizado = (f.diaInicio < dCol) ? 100.0f / (1.0f + std::exp(-k * (f.diaInicio - dCol / 2.0f))) : 100.0f;

        // Lógica de CO2: 8000ppm en colonización, 800ppm en fructificación
        float co2Obj = (f.diaInicio < dCol) ? 8000.0f : 800.0f;
        float factorDilucion = 1.0f / ((co2Obj - 400.0f) / 1000000.0f);

        // Cálculo de segundos por hora
        float mgCO2hora = 0.15f * pesoG * (f.porcentajeColonizado / 100.0f);
        f.segVentilacion = (mgCO2hora / 1800.0f * factorDilucion / caudalReal) * 60.0f;

        if (f.segVentilacion > 3600.0f) f.segVentilacion = 3600.0f;
        plan.push_back(f);
    }
    return plan;
}

int main() {
    float col, fru, peso;
    std::cout << "Dias colonizacion: "; std::cin >> col;
    std::cout << "Dias fructificacion: "; std::cin >> fru;
    std::cout << "Peso sustrato (g): "; std::cin >> peso;

    auto receta = calcularPlan(col, fru, peso, 850.0f, 25);

    for (auto &f : receta) {
        std::cout << "Dia " << f.diaInicio << " | " 
                  << (f.diaInicio < col ? "Colonizacion: " : "Fructificacion: ") 
                  << f.segVentilacion << " seg/hora" << std::endl;
    }
    return 0;
}
