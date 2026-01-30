# Suma de arreglos en paralelo con OpenMP

Este proyecto implementa la suma de dos arreglos utilizando OpenMP en C++,
comparando la ejecución serial contra la ejecución paralela.

## Requisitos
- Visual Studio (con soporte para C++)
- OpenMP habilitado (/openmp)

## Configuración
1. Abrir el proyecto en Visual Studio.
2. Activar OpenMP en:
   Proyecto > Propiedades > C/C++ > Lenguaje > Soporte de OpenMP = Sí (/openmp)

## Ejecución
- Compilar y ejecutar el proyecto (Ctrl + F5).

## Descripción
El programa:
- Inicializa dos arreglos de tamaño N.
- Calcula la suma de manera serial y paralela.
- Mide y compara tiempos de ejecución.
- Imprime una muestra del arreglo resultante para verificar la correcta suma.

