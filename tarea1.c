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
  time_t tiempo;
}Ticket;




// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Soporte Tecnico");
  puts("========================================");

  puts("1) Registrar id del cliente");
  puts("2) Asignar prioridad a cliente");
  puts("3) Mostrar clientes por prioridad y hora");
  puts("4) Atender al siguiente cliente");
  puts("5) buscar cliente por id");
  puts("6) Salir");
}

//funcion para buscar ids
Ticket *buscarID(List*lista, int id)
{
  if (lista == NULL || list_size(lista)== 0) return NULL;

  Ticket * ticket = (Ticket*)list_first(lista);
  while (ticket != NULL)
  {
    if (ticket -> id == id )return ticket;
    ticket = (Ticket *)list_next(lista);
  }
  
  return NULL;
}


void C_Ticket(List *clientes) //funcion para crear los tickets que tengan a los clientes.
{
  //se crea el struct de tickets y se hace un malloc para la memoria
  Ticket *estructura = NULL;
  estructura = (Ticket*)malloc(sizeof(Ticket));
  //se verifica si es que el estruct esta vacio, si es que es NULL esta mal y se termina
  if (estructura == NULL)
  {
    printf("NO HAY DATOS REGISTRADOS");
    return;
  }
  //ahora se registra al cliente accediendo directamente al struct y en la posicion del id, para guardarlo directamente sin uso de un aux
  printf("Registrar nuevo cliente\n");
  printf("\nIngrese id :");
  int ID;
  scanf("%d", &ID);

  //condicion para ver si el id es valido, si no el programa para de registrar clientes

  if  (ID < 1 || ID > 999999)
  {  
    printf("ERROR , NO SE INGRESO UN ID VALIDO\n");
    free(estructura);
    return;
  }

  //condicion para ver si ya se registro el ticket 

  int id_busc = ID;



//se busca el ticket, si se encuentra se devuelve un ticket, si no null, si no es null es por que se encontro, por lo tanto hayq ue borrar la memoria que se le reservo
  if (buscarID(clientes , ID) != NULL) 
  {
    printf("TICKET NO VALIDO, ID YA FUE INGRESADO ANTES\n");
    free(estructura);
    return;
  }
  estructura -> id = ID;
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

//funcion para ordenar los tickets segun su hora de ingreso
int compararPorHora(void *data1, void *data2) {
  Ticket *ticket1 = (Ticket *)data1;
  Ticket *ticket2 = (Ticket *)data2;
  printf("Insertando ticket con tiempo %ld\n", ((Ticket *)data1)->tiempo);
  if (ticket1->tiempo < ticket2->tiempo) return -1;
  if (ticket1->tiempo > ticket2->tiempo) return 1;

  return 0; 
}



//funcion para asignarles prioridad a los tickets
void prioridad_Ticket(List*clientes, List *clientes_B , List *clientes_M , List *clientes_A)
{
  //creo dos variables, para ver el id a modificar, y para ver que prioridad es.
  int id_A_Buscar , N_prioridad;

  printf("Inserte ID de su ticket para modificar su prioridad :");
  scanf("%d", &id_A_Buscar);


  //Se busca un puntero con la posicion del id si es que se encontro , en tal caso de que no se termina la funcion
  Ticket *estructura = buscarID(clientes, id_A_Buscar);

  if (estructura == NULL) 
  {
    printf("\nNO SE ENCONTRO TICKET CON EL ID.\n");
    return; 
  }

  printf("Asigne una prioridad a su ticket (1 = baja, 2 = media, 3 = alta): ");
  scanf("%d", &N_prioridad);
  // viendo si la prioridad es valida
  if (N_prioridad < 1 || N_prioridad > 3)
  {
    printf("\nERROR , SE INGRESO UNA PRIORIDAD NO VALIDA \n");
    return;
  }
  //se hace cambio la prioridad del ticket una vez ya todo fue confirmado
  estructura -> prioridad = N_prioridad;

  //se hace un list_remove(estructura agregada por mi en list.c y .h) para eliminar cualquier duplicado de este ticket, aun que se modifique en una siguiente funcion.

  list_remove(clientes_B, estructura);
  list_remove(clientes_M, estructura);
  list_remove(clientes_A, estructura);


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
        printf("\nPrioridad no válida\n");
        break;
}

  printf("Prioridad del ticket de id %d fue modificada a %d con exito\n", estructura -> id , estructura -> prioridad);

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

  /*ahora se le hace un aux a cada prioridad con su ticket, asi se recorre la lista y se le asigna el valor de ticket al 
  resultado del list_first, asi con la estructura apropiada se puede ingresar al ticket facilmente, asi haciendo posible el
  extraer los datos de la estructura
  */

  Ticket *auxA = NULL;
  printf("\n--- PRIORIDAD ALTA ---\n");
  auxA = list_first(clientes_A);  
  while (auxA != NULL)
  {
    char hora_EA[50];
    struct tm *tm_info1 = localtime(&auxA->tiempo);
    strftime(hora_EA, sizeof(hora_EA), "%d/%m/%Y %H:%M", tm_info1);
    printf("ID: %d | Problema: %s | Hora: %s\n", auxA->id, auxA->problema, hora_EA);
    auxA = list_next(clientes_A);
  }

  
  Ticket *auxM = NULL;
  printf("\n--- PRIORIDAD MEDIA ---\n");
  auxM = list_first(clientes_M);  
  while (auxM != NULL)
  {
    char hora_EM[50];
    struct tm *tm_info2 = localtime(&auxM->tiempo);
    strftime(hora_EM, sizeof(hora_EM), "%d/%m/%Y %H:%M", tm_info2);
    printf("ID: %d | Problema: %s | Hora: %s\n", auxM->id, auxM->problema, hora_EM);
    auxM = list_next(clientes_M);
  }

  
  Ticket *auxB = NULL;
  printf("\n--- PRIORIDAD BAJA ---\n");
  auxB = list_first(clientes_B);  
  while (auxB != NULL)
  {
    char hora_EB[50];
    struct tm *tm_info3 = localtime(&auxB->tiempo);
    strftime(hora_EB, sizeof(hora_EB), "%d/%m/%Y %H:%M", tm_info3);
    printf("ID: %d | Problema: %s | Hora: %s\n", auxB->id, auxB->problema, hora_EB);
    auxB = list_next(clientes_B);
  }
}

void procesar_ticket(List *clientes ,List *clientes_B , List *clientes_M , List *clientes_A)
{

  printf("procesando tickets pendientes :");

  if (list_size(clientes) == 0)
  {
    printf("NO HAY TICKETS PENDIENTES\n");
    return;

  }

  else
  {
    if (list_size(clientes_A) != 0)
    {
      Ticket *auxA = NULL;
      auxA = list_first(clientes_A);
      char hora_EA[50];
      struct tm *tm_info1 = localtime(&auxA->tiempo);
      strftime(hora_EA, sizeof(hora_EA), "%d/%m/%Y %H:%M", tm_info1);
      printf("ID: %d | Problema: %s | Hora: %s Fue procesado.\n", auxA->id, auxA->problema, hora_EA);
      list_popFront(clientes_A);
      list_remove(clientes , auxA);
      return;

      
    }

    if (list_size(clientes_M) != 0)
    {
      Ticket *auxM = NULL;
      auxM = list_first(clientes_M);
      char hora_EM[50];
      struct tm *tm_info2 = localtime(&auxM->tiempo);
      strftime(hora_EM, sizeof(hora_EM), "%d/%m/%Y %H:%M", tm_info2);
      printf("ID: %d | Problema: %s | Hora: %s Fue procesado.\n", auxM->id, auxM->problema, hora_EM);
      list_popFront(clientes_M);
      list_remove(clientes , auxM);
      return;
    }

    if (list_size(clientes_B) != 0)
    {
      Ticket *auxB = NULL;
      auxB = list_first(clientes_B);
      char hora_EB[50];
      struct tm *tm_info3 = localtime(&auxB->tiempo);
      strftime(hora_EB, sizeof(hora_EB), "%d/%m/%Y %H:%M", tm_info3);
      printf("ID: %d | Problema: %s | Hora: %s Fue procesado.\n", auxB->id, auxB->problema, hora_EB);
      list_popFront(clientes_B);
      list_remove(clientes , auxB);
      return;
      
    }

  }
  



}


//funcion para buscar tickets, se reutilizan codigos de otras funciones para buscarlo.
void buscar_ticket(List *clientes)
{
  if (list_size(clientes) == 0)
  {
    printf("ERROR , NO HAY CLIENTES REGISTRADOS\n");
    return;
  }

  else
  {
    int id;
    scanf("%d", &id);


    Ticket *T_buscado = buscarID(clientes, id);

    char hora[50];
    struct tm *tm_info = localtime(&T_buscado->tiempo);
    strftime(hora, sizeof(hora), "%d/%m/%Y %H:%M", tm_info);
    printf("ID: %d | Problema: %s | Hora: %s Fue procesado.\n", T_buscado->id, T_buscado->problema, hora);



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

    switch (opcion) 
    {
    case '1':
      C_Ticket(clientes);
      break;
    case '2':
      prioridad_Ticket(clientes, clientes_B ,clientes_M , clientes_A);
      break;
    case '3':
      mostrar_lista_clientes(clientes, clientes_B , clientes_M , clientes_A);
      break;
    case '4':
      procesar_ticket(clientes ,clientes_B , clientes_M , clientes_A);
      break;
    case '5':
      buscar_ticket(clientes);
      break;
    case '6':
      puts("Saliendo del sistema de soporte tecnico...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(clientes);

  list_clean(clientes_B);
  list_clean(clientes_M);
  list_clean(clientes_A);
  

  return 0;
}
