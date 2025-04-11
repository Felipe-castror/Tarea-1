#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_P 201

typedef struct 
{
  int id;
  char problema[MAX_P];
  int prioridad;
  time_t tiempo
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

//funcion para comparar ids, si son iguales retorna 1 y si no -1
int compararID(void *estructura , void *num)
{
  Ticket *t = (Ticket *)estructura;
  int compID = *((int*)num);

  if (t->id == compID)return 0;

  else return 1; 

}

void C_Ticket(List *clientes) //funcion para crear los tickets que tengan a los clientes.
{
  //se crea el struct de tickets y se hace un malloc para la memoria
  Ticket *estructura = (Ticket*)malloc(sizeof(Ticket));
  //se verifica si es que el estruct esta vacio, si es que es NULL esta mal y se termina
  if (estructura == NULL)
  {
    printf("NO HAY DATOS REGISTRADOS");
    return;
  }
  //ahora se registra al cliente accediendo directamente al struct y en la posicion del id, para guardarlo directamente sin uso de un aux
  printf("Registrar nuevo cliente\n");
  printf("\nIngrese id :");
  scanf("%d", &estructura ->id);

  //condicion para ver si el id es valido, si no el programa para de registrar clientes

  if  (estructura ->id < 1 || estructura -> id > 999999)
  {  
    printf("ERROR , NO SE INGRESO UN ID VALIDO");
    return;
  }

  //condicion para ver si ya se registro el ticket 

  int id_busc = estructura -> id;

  Ticket *resultado = (Ticket *)list_find(clientes, compararID, &id_busc);

  if (resultado == NULL) 
  {
    printf("ID ingresado correctamente");
    
    //se hace getchar para limpiar el salto de linea para que el fgets no tenga problemas y no lea vacio
    getchar();

    printf("\nExplique su problema(maximo 200 palabras) :");

    //Se ocupa fgets para leer la linea completa o en este caso el problema
    fgets(estructura -> problema ,MAX_P,stdin);
    
    //se elimina el salto de de linea o vacio
    estructura->problema[strcspn(estructura->problema,"\n")] = 0;

    //la prioridad parte en bajo, luego se le hace un cambio en otra funcion
    estructura ->prioridad = 1;

    /* ocupo la libreria time.h para poder registrar mas eficientemente el tiempo, asi el usuario no tiene que registrar su tiempo
    si no que la funcion lo registra a traves del sistema operativo.
    */
    estructura -> tiempo = time(NULL);

    // ahora ocupo un struct predefinido de la libreria time.h para manejar el tiempo(fecha, dia , hora) para sacar el tiempo del sistema operativo del cliente
    struct tm*tm_info;
    tm_info = localtime(&estructura->tiempo);
    
    /*ahora se utiliza una variable aux de tipo char para poder hacer el traspaso de la hora para poder mostrarla,
    luego utilizo una funcion de la libreria time.h para hacer el traspaso de la hora a texto, con el formato dia,mes
    año  hora y minutos, y al final se muestra la hora.
    */

    char aux_hora[50];
    strftime(aux_hora, sizeof(aux_hora), "%d/%m/%Y %H:%M",tm_info);
    
    printf("Fecha y hora : %s\n",aux_hora);

    list_pushBack(clientes, estructura);
  }

  else 
  {
    printf("TICKET NO VALIDO, ID YA FUE INGRESADO ANTES");
    return;
  }
}

//funcion para ordenar los tickets segun su hora de ingreso
int compararPorHora(void *data1, void *data2) {
  Ticket *ticket1 = (Ticket *)data1;
  Ticket *ticket2 = (Ticket *)data2;

  if (ticket1->tiempo < ticket2->tiempo) return -1;
  if (ticket1->tiempo > ticket2->tiempo) return 1;

  return 0; 
}



//funcion para asignarles prioridad a los tickets
void prioridad_Ticket(List*clientes, List *clientes_B , List *clientes_M , List *clientes_A)
{
  //creo dos variables, para ver el id a modificar, y para ver que prioridad es.
  int id_A_Buscar , N_prioridad;
  Ticket *estructura;

  printf("Inserte ID de su ticket para modificar su prioridad :");
  scanf("%d", &id_A_Buscar);


  //Se busca un puntero con la posicion del id si es que se encontro , en tal caso de que no se termina la funcion
  estructura = (Ticket *)list_find(clientes, &id_A_Buscar, compararID);

  if (estructura == NULL) 
  {
    printf("NO SE ENCONTRO TICKET CON EL ID.\n");
    return; 
  }

  printf("Asigne una prioridad a su ticket (1 = baja, 2 = media, 3 = alta): ");
  scanf("%d", &N_prioridad);
  // viendo si la prioridad es valida
  if (N_prioridad < 1 || N_prioridad > 3)
  {
    printf("ERROR , SE INGRESO UNA PRIORIDAD NO VALIDA \n");
    return;
  }
  //se hace cambio la prioridad del ticket una vez ya todo fue confirmado
  estructura -> prioridad = N_prioridad;

  // ahora se ingresa el ticket en la lista correspondiente, segun su prioridad y hora
  switch (estructura->prioridad) 
  {
    case 1:  // Baja
        list_sortedInsert(clientes_B, estructura, compararPorHora);
        break;
    case 2:  // Media
        list_sortedInsert(clientes_M, estructura, compararPorHora);
        break;
    case 3:  // Alta
        list_sortedInsert(clientes_A, estructura, compararPorHora);
        break;
    default:
        printf("Prioridad no válida\n");
        break;
}

  printf("Prioridad del ticket de id %d fue modificada a %d con exito", estructura -> id , estructura -> prioridad);

}

void mostrar_lista_clientes(List *clientes, List *clientes_B, List *clientes_M , List *clientes_A) 
{
  // Mostrar clientes en la cola de espera
  int Nclientes = list_size(clientes);
  
  //se verifica si hay clientes
  if(Nclientes == 0)
  {
    printf("No hay clientes en espera\n");
    return;
  }

  
  printf("clientes en espera: %d\n", Nclientes);
  printf("-------------------------------------\n");

  Ticket *t;

  printf("\n--- PRIORIDAD ALTA ---\n");
  t = (Ticket *)list_first(clientes_A);
  while (t != NULL) 
  {
    printf("ID: %d | Problema: %s\n", t->id, t->problema);
    t = (Ticket *)list_next(clientes_A);
  }

  
  printf("\n--- PRIORIDAD MEDIA ---\n");
  t = (Ticket *)list_first(clientes_M);
  while (t != NULL) 
  {
    printf("ID: %d | Problema: %s\n", t->id, t->problema);
    t = (Ticket *)list_next(clientes_M);
  }

  printf("\n--- PRIORIDAD BAJA ---\n");
  t = (Ticket *)list_first(clientes_B);
  while (t != NULL) 
  {
    printf("ID: %d | Problema: %s\n", t->id, t->problema);
    t = (Ticket *)list_next(clientes_B);
  }


  

  
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
      C_Ticket(clientes);
      break;
    case '2':
      // Lógica para asignar prioridad
      break;
    case '3':
      mostrar_lista_clientes(clientes, clientes_B , clientes_M , clientes_A);
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
