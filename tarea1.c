#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_P 201
#define MAX_H 24

typedef struct 
{
  int id;
  char problema[MAX_P];
  int Prioridad;
  char D_M_Y_H[MAX_H];
}Ticket;




// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Soporte Tecnico");
  puts("========================================");

  puts("1) Registrar id del cliente");
  puts("2) Asignar prioridad a cliente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente cliente");
  puts("5) Mostrar clientes por prioridad");
  puts("6) Salir");
}

void C_Ticket(List *clientes) //funcion para crear los tickets que tengan a los clientes.
{
  printf("Registrar nuevo cliente\n");
  printf("\nIngrese id :");
  int num;
  scanf("%d", &num);
  printf("\nExplique su problema con un maximo de 200 palabras :");
  char prob[MAX_P];
  scanf("%c" , &prob);
  printf("\n ingrese su nivel de urgencia/prioridad : bajo(1) , medio(2) , alto(3)");
  int P;
  scanf("%d", &P);

  printf("\n ingrese la fecha de ingreso  por dia-mes-año-hora : ejm 02-10-2025-10:48");
  char hora[MAX_H];
  scanf("%c" , &hora);


  






  // Aquí implementarías la lógica para registrar un nuevo paciente

}

void mostrar_lista_pacientes(List *clientes) {
  // Mostrar clientes en la cola de espera
  printf("clientes en espera: \n");
  // Aquí implementarías la lógica para recorrer y mostrar los pacientes
}

int main() {
  char opcion;
  List *clientes = list_create(); // puedes usar una lista para gestionar los pacientes

  List *clientes_B = list_create();// lista de prioridad Baja
  List *clientes_M = list_create();// lista prioridad Media
  List *clientes_A = list_create();//lista prioridad Alta


  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_clientes(clientes);
      break;
    case '2':
      // Lógica para asignar prioridad
      break;
    case '3':
      mostrar_lista_clientes(clientes);
      break;
    case '4':
      // Lógica para atender al siguiente clientes
      break;
    case '5':
      // Lógica para mostrar clientes por prioridad
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(clientes);

  return 0;
}
