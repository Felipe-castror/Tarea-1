# 🛠️ Sistema de Soporte Técnico - Tarea 1

1 ) Este programa implementa un sistema de gestión de tickets para soporte técnico.
en este se puede registrar clientes, asignar prioridades, listar y atender solicitudes de acuerdo con su prioridad, fecha y hora,
buscar clientes por id.

## ✅ principales funciones del programa:

- Registrar clientes con su nombre, problema, prioridad (Alta, Media o Baja) y hora de registro.
- Mostrar la lista de espera de clientes ordenada por prioridad y hora.
- Atender al cliente con la prioridad más alta, considerando el tiempo de registro (en desarrollo).
- Menú interactivo para facilitar la navegación por las opciones del sistema.
- Validación de entradas para garantizar datos consistentes.

---

## 🚀 Compilación y Ejecución del Programa

2 ) Para compilar y ejecutar el programa, sigue estos pasos:

1. Asegúrate de tener un compilador de C instalado en tu sistema (como GCC).
2. Descarga los archivos del proyecto y colócalos en un mismo directorio.
3. Compila el programa utilizando el siguiente comando:
   ```bash
   gcc -o tarea1.exe tarea1.c tdas\extra.c tdas\list.c
   ```
4. Ejecuta el programa con:
   ```bash
   ./tarea1.exe
   ```
   
**Nota:** hay que Asegurarse de que los archivos `list.h` y `list.c` estén en el mismo directorio que `tarea1.c`, y que se este ocupando
el directorio de `extra.c`

---

## 📂 Estructura del Proyecto

El proyecto incluye los siguientes archivos principales:

- **`tarea1.c`:** Archivo principal que contiene la lógica del programa y el menú interactivo.
- **`list.c`:** Implementación de una lista enlazada genérica para gestionar los tickets.
- **`list.h`:** Cabecera que define las funciones y estructuras utilizadas en `list.c`.
- **`extra.c`:** implementacione de funciones que hacen capaces la lectura de lineas de archivo(en este caso no se utiliza),
limpiar la pantalla y ayudar con la lectura de datos.
---

## 🗂️ Estructuras y TDAs Utilizados

  3 )
  El sistema utiliza los siguientes tipos de datos:

### **Estructura `Ticket`**
```c
typedef struct {
  int id;                // Identificador único del cliente
  char problema[201];    // Descripción del problema reportado
  int prioridad;         // Prioridad del ticket: 1 (Baja), 2 (Media), 3 (Alta)
  time_t tiempo;         // Hora de registro del ticket
} Ticket;
```

### **TDA Lista Enlazada**
```c
typedef struct Node {
  void *data;            // Apunta al dato almacenado
  struct Node *next;     // Apunta al siguiente nodo
} Node;

typedef struct List {
  Node *head;            // Primer nodo de la lista
  Node *tail;            // Último nodo de la lista
  Node *current;         // Nodo actual para iteraciones
  int size;              // Tamaño de la lista
} List;
```

---

## 🔧 Funciones Implementadas

### Funciones Principales (Tarea 1)
4)
- **Registrar Cliente:**
  Registra un nuevo cliente con su ID, problema, prioridad y hora de registro, se registra el id en una variable aux y se verifica si es que cumple con las condiciones de que no sea menor a 1, y mayor a 999 999 y de que sea un int, ademas se verifica si es que el id esta ya en la lista, si esta no se puede registrar de nuevo, y luego de confirmar eso, se registra el id en el ticket y desde ahi el cliente ingresa su problema(que no se verifica si sea un problema real o que sean solo palabras) y despues se pone su prioridad en bajo y se ingresa la hora verificando su sistema operativo gracias a la libreria time.h
  
- **Asignar Prioridad:**
  Cambia la prioridad de un ticket existente y lo reordena en la lista correspondiente, se vrifica que se ingrese un id existente y luego se modifica su prioridad, al modificar su prioridad se agrega a una de las 3 listas de prioridad, ademas si es que ya estaba en una de las tres listas se remueve para luego introducirse a la correspondiente.

- **Mostrar Clientes:**
  Muestra la lista de espera ordenada por prioridad y hora, se hacen variables aux para cada lista y se verifica que hayan clientes, si no hay no se muestra nada, en cambio si hay se muestra lo anteriormente mencionado, pero con el cambio de esta ordenado por id en vez de por hora, no se sabe la razon del por que.

- **Atender Cliente:**
  Atiende al cliente con la prioridad más alta y el tiempo de registro más antiguo, cosa que se intento pero parece que la funcion list_sortedInsert no parece reconocer la variable del tiempo o parece que no se registro bien, no se pudo saber que variable era la que afectaba esto, pero en verdad funciona segun prioridad y luego se verifica que tan alto es su id, la hora esta mal por ahora.

- **Buscar Cliente por ID:**
  Permite buscar un ticket específico por su ID único, se verifica que sea id valido, y que este en la lista principal que es la contiene las tres otras listas, osea la de todos los clientes.

### Funciones de la Lista Enlazada
- **`list_create`**: Crea una nueva lista enlazada.
- **`list_remove`**: Elimina un nodo específico de la lista.(esta funcion fue agregada, no venia en los archivos originales)
- **`list_sortedInsert`**: Inserta un nodo en una posición ordenada según una función de comparación.
- **`list_clean`**:limina todos los nodos de la lista, liberando la memoria asociada a cada uno.
- **`list_size`**:Devuelve el tamaño de la lista (número de elementos almacenados).
- **`list_first`**: Elimina todos los nodos de la lista.
- **`list_popCurrent`**:Elimina el nodo actualmente seleccionado (current) de la lista y devuelve un puntero al dato almacenado en ese nodo.
- **`list_pushCurrent`**:nserta un nuevo elemento después del nodo actual (current) de la lista.
- **`list_pushFront`**: Inserta un nodo al inicio de la lista.
- **`list_popFront`**:Elimina el primer elemento de la lista y devuelve un puntero al dato almacenado en ese nodo.
- **`list_pushBack`**: Inserta un nodo al final de la lista.
- **`list_popBack`**:Elimina el último elemento de la lista y devuelve un puntero al dato almacenado en ese nodo.

---

## ⚠️ Problemas Conocidos

- **Orden Incorrecto:** En algunos casos, los tickets no se ordenan correctamente por hora después de cambiar su prioridad.
- **Validación Limitada:** Las entradas del usuario no están completamente validadas, lo que puede llevar a errores si se ingresan datos no válidos.
- **Función de Búsqueda:** `list_find` puede retornar `NULL` en algunos casos, lo que no siempre está bien manejado.
- **Carga y Guardado de Archivos:** El programa aún no implementa correctamente la funcionalidad de carga y guardado a archivos.

---

EXTRA )
## 📈 Mejoras Planeadas

- Implementar la funcionalidad de carga y guardado de datos en archivos CSV.
- Mejorar la validación de entradas del usuario para evitar errores.
- Optimizar la función de búsqueda y manejo de errores en caso de datos no encontrados.
- Diseñar pruebas automáticas para verificar el correcto funcionamiento de las funciones.

---

 5 )
 ## 👥 Contribuciones

- **[Felipe Castro]:**
  - Implementó las funciones principales del programa (`C_Ticket`, `prioridad_Ticket`, `mostrar_lista_clientes`, `procesar_ticket` , `buscar_ticket`)
  - implemente funciones secundarias ocupadas en las funciones principales.
  - Implementó la estructura `Ticket` y su integración con la lista enlazada.
  - Autoevaluación: 3 (Aporte excelente).


** CONTRIBUCIÓN DESTACADA** 
- **[Copilot]:**
- ayudo con la resolucion de algunos problemas en el codigo.
- vio comas y ; que habian pasado desapercibidos.
- recalco que el archivo tarea1.exe tenia que actualizarse para que se pudieran ver
los cambios hechos al programa.

---

## 🧪 Ejemplo de Uso

```bash
$ ./tarea1.exe
Bienvenido al sistema de soporte técnico
1. Registrar nuevo cliente
2. Cambiar prioridad de ticket
3. Mostrar los clientes según su prioridad y hora
4. Atender al siguiente cliente
5. Buscar cliente por ID
6. Salir

Ingrese una opción: 1
Ingrese ID: 12345
Problema: Pantalla azul
Prioridad: baja(se cambia con la opcion 2)
Ticket registrado con éxito.
```