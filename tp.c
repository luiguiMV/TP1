#include <stdio.h>

main(){
  int opc;
  printf("Escriba el número de la acción que desea ejecutar y presione Enter...\n1.Agregar Contactos\n2.Enviar Mensaje\n3.Salir\n");
  scanf("%d", &opc);
  if (opc==1){
    agregarC();
  }
  else if(opc==3){
    return 0;
  }
  return 0;
}

agregarC(){
  char nombre[50];
  int puerto;
  int ip;
  printf("Nombre del contacto: ");
  scanf("%s", nombre);
  printf("Puerto:");
  scanf("%d", &puerto);
  printf("IP:");
  scanf("%d", &ip);
  printf("\nCONTACTO AGREGADO\n\n");
  main();
}
