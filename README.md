# FungiBox

Sistema de control ambiental de bajo costo, basado en un microcontrolador **ESP32**, que automatiza y facilita el cultivo de hongos adaptógenos en un entorno controlado y sanitizado.

## Descripción

El cultivo de hongos adaptógenos depende de variables ambientales críticas —temperatura, humedad relativa y concentración de CO2— que normalmente requieren intervención manual constante, generando errores y pérdida de eficiencia.

**FungiBox** integra sensores y actuadores para monitorear en tiempo real el microclima de la cámara de cultivo y accionar automáticamente los equipos necesarios (calefacción, humidificación, ventilación) para mantener las variables estables en sus rangos óptimos, reduciendo el contacto humano y el riesgo de contaminación.

## Objetivo general

Diseñar y automatizar un sistema de control ambiental de bajo costo que permita facilitar y optimizar el cultivo de hongos adaptógenos en un entorno controlado y sanitizado.

## Objetivos específicos

- **O1.** Implementar un monitoreo ambiental preciso.
- **O2.** Desarrollar un registro de datos.
- **O3.** Implementar los actuadores.
- **O4.** Desarrollar una interfaz de usuario intuitiva.

## Hardware

| Componente | Detalle |
|---|---|
| Microcontrolador | ESP32 |
| Sensor de CO2 | SCD30 |
| Sensor de temperatura | DS18B20 |
| Sensor de humedad | DHT22 |
| Control de actuadores | Módulos relé 5V, MOSFETs IRFZ44N (PWM) |
| Calefacción | Cama calefactora |
| Humidificación | Atomizador ultrasónico 5V |
| Ventilación | Ventiladores 12V |

## Software

- **Arduino IDE** — programación del ESP32, lectura de sensores, control de actuadores y servicio web para comunicación en red local.
- **QT** — interfaz gráfica de usuario y gestión de datos históricos.
- **SQLite** — almacenamiento del registro histórico de variables, eventos y configuraciones.

## Estructura del repositorio

```
FungiBox/
├── pruebas/
│   ├── Interaz/         # Interfaz gráfica (Qt): mainwindow, CMakeLists, UI
│   ├── base_datos/      # Base de datos SQLite y scripts SQL
│   ├── sensores/        # Lectura de sensores (temperatura, humedad, estado del hongo)
│   └── POC_calculadora_co2.cpp
└── README.md
```

## Arquitectura del sistema

El sistema se organiza en tres capas:

1. **Componentes físicos** — sensores (entrada) y actuadores (salida) que interactúan con el ambiente de cultivo.
2. **Módulos del microcontrolador** — lectura de sensores, algoritmos de activación, control de actuadores, almacenamiento en base de datos y comunicación con la app.
3. **Módulos de la aplicación (interfaz de usuario)** — ingreso de datos, visualización (dashboard), control manual y comunicación con el microcontrolador.

## Instalación y uso

Las instrucciones detalladas de instalación (conexión de hardware, carga de firmware y primer encendido) y de uso (navegación de la interfaz, control manual y configuración de parámetros) están disponibles en:

- [Manual de Instalación](./docs/Manual_Instalacion_FungiBox.docx)
- [Manual de Usuario](./docs/Manual_Usuario_FungiBox.docx)

## Equipo

- Joaquín Carey
- Tomás Carvajal
- Gabriel Nieto

## Estado del proyecto

Proyecto finalizado — entrega final el 02-07-2026.
