## Estructura de Datos

La **Estructura de Datos** es la forma de almacenar y organizar los datos en la memoria de un computador de modo que puedan ser utilizados de forma eficiente. Pueden ser homogéneas o heterogéneas.

Las **homogéneas** son conjuntos formados por datos del mismo tipo: Vectores, Matrices y Cadenas de caracteres.

Las **heterogéneas** son conjuntos formados por tipos de datos diferentes: Registros (Estructuras).

---

## TAD - Tipo Abstracto de Datos

Un **Tipo Abstracto de Datos**, o **TAD**, es un conjunto de datos estructurados y las operaciones que pueden ser ejecutadas sobre esos datos.

Los datos almacenados pueden ser manipulados solo por las operaciones/métodos.

### Ventajas:
- Ocultamiento de los detalles de representación e implementación, solo las funcionalidades son conocidas;
- **Encapsulamiento**: La implementación es oculta, solo proporciona la interfaz/operaciones posibles del TAD;
- **Seguridad**: Acceso solo a las interfaces/operaciones, y no directamente a los datos;
- **Reutilización y flexibilidad**: El TAD puede ser usado en diferentes aplicaciones.

### Operaciones más comunes utilizadas:
- Creación de la estructura;
- Inclusión/Actualización de un elemento;
- Búsqueda de un elemento;
- Eliminación de un elemento;
- Destrucción de la estructura;

### Modularización:
- Por convención, los TADs son construidos en archivos separados. Se utilizan archivos de cabecera (.h) y de código fuente (.c) para modularizar;
- El archivo de cabecera y el archivo de código fuente deben tener el mismo nombre, cambiando solo la extensión. `vector_dinamico.h` y `vector_dinamico.c`;
- Posibilidad de "ocultar" la implementación de quienes usan el TAD;
- Quienes utilizan el TAD solo necesitan conocer las funcionalidades que implementa;
- Archivo .h: definición de los nuevos tipos de datos, prototipos de las funciones y variables globales;
- Archivo .c: declaración de los nuevos tipos de datos e implementación de las funciones.

![TAD](https://github.com/edersonschmeing/estrutura-de-dados-em-c-1/blob/main/tad-e-vetor-dinamico/tad.png)

<!-- ### Patrones Creacionales

#### - Factory Method -->
