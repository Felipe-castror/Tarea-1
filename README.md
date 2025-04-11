 🛠️ Sistema de Soporte Técnico - Tarea 1

Este programa implementa un sistema de gestión de tickets para soporte técnico, permitiendo registrar clientes, asignar prioridades, listar y atender solicitudes de acuerdo a su prioridad, fecha y hora.

Este proyecto utiliza una lista enlazada genérica implementada en C para gestionar la fila de espera de tickets.

IMPORTANTE:
si se ingresa un dato que no este en las condiciones o que se considere no apto, ejm: caracteres especiales, numero negativos en id, y y prioridades mayores a 3 o menores a 1, el programa para de registrar y pasa a la siguiente función

## ✅ Funcionalidades principales

- Registrar clientes con su nombre, problema y prioridad (Alta, Media o Baja) y hora de registro.
- Mostrar la lista de espera de clientes por prioridad.
- Atender al cliente con la prioridad más alta, ordenandolos por este orden: prioridad - fecha y hora(menor tiempo == el primero).** (aun en desarrollo)
- Guardar y cargar los datos desde archivos.** 
- Menú interactivo por consola.** (aun en desarrollo).

---

## ⚠️ Funciones con problemas conocidos

- Guardado y carga desde archivo puede tener errores si los datos contienen caracteres especiales.
- Validaciones en los campos del cliente aún no son exhaustivas y pueden tener problemas a la hora de probar.
- En ciertos casos, `list_find` puede retornar NULL y no está bien manejado en todas las funciones.
- no se puede probar casos para comprobar las funciones.
- problemas con el struct, ya que la funcion de mostrar no muestra todos los id bien, si no que muestra el id mas reciente.
---

## 🧪 Ejemplo de uso

```bash
$ ./tarea1.exe
Bienvenido al sistema de soporte técnico
1. Registrar nuevo cliente
2. cambiar prioridad de ticket
3. mostrar los clientes segun su prioridad y hora
4. atender al sig cliente
5. mostrar clientes por prioridad
6. salir

Ingrese una opción: 1
id : 12345
Problema: Pantalla azul
Prioridad (Alta, Media, Baja): Alta
Cliente registrado con éxito.
