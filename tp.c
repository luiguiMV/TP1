#include <stdio.h>
#include <string.h>

//VARIABLES GLOBALES
struct contacto{
	char nombre[50];
	int puerto;
	int ip;
}listaContactos[100];//arreglo de structs contacto con capacidad para 100 contactos

int ultimoCont, cont;//variable tipo int que guarda el numero de la posicion del ultimo contacto introducido


/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/


//Funcion main basicamente llama a la funcion menu.
void main(){
	leerTxt();//llena el struct con los datos del txt
	menu();
}

/*Funcion muestra el menu al inicio*/
int menu(){
	int opc;
	printf("\n\nEscriba el número de la acción que desea ejecutar y presione Enter...\n1.Agregar Contactos\n2.Enviar Mensaje\n3.Ver lista de contactos\n");
	scanf("%d", &opc);
	if (opc==1){
		datosContacto();
	}
	else if(opc==3){
		imprimeContactos();
	}
	return 0;
}

/*Funcion que pregunta al usuario el nombre, ip y puerto, guarda esta info en un struct 
*/
void datosContacto(){
	system("clear");
	struct contacto nuevo;
	printf("\nAgregando nuevo contacto\nNombre: ");
	scanf("%s", nuevo.nombre);
	printf("Ip: ");
	scanf("%d", &(nuevo.ip));
	printf("Puerto: ");
	scanf("%d", &(nuevo.puerto));
	agregarContacto(&nuevo);//envia el nuevo struct para ser agregado al arreglo
	guardarTxt(nuevo.nombre, nuevo.ip, nuevo.puerto);//guarda en el txt
	printf("\nCONTACTO AGREGADO!!");
	menu();
}

/*Funcion para agregar contactos en el arreglo de structs */
int agregarContacto(struct contacto *nuevo){
	listaContactos[ultimoCont]=*nuevo;
	ultimoCont++;
	return 0;
}

void imprimeContactos(){
	system("clear");
	int e = 0;//para recorrer listaContactos
	printf("\nLista de Contactos\n\n");
	while (listaContactos[e].ip != 0){//while para mostrar en pantalla los contactos,
		printf("%d) Nombre = %s, Ip = %d,  Puerto = %d\n", e+1, listaContactos[e].nombre, listaContactos[e].ip, listaContactos[e].puerto);
		e++;
	}
	menu();
}

/*Funcion que  guarda un contacto en la ultima linea del txt
 * */
int guardarTxt(char nombre[], int ip, int puerto){
	FILE *contactos;
	contactos = fopen("contactos.txt", "a");
	fprintf(contactos, "%s %d %d\n", nombre, ip, puerto);
	fclose(contactos);
	return 0;
}

/*funcion que lee los contactos del txt y los va guardando en el struct
*/
int leerTxt(){
	struct contacto nuevo;
	char line[100];//linea del txt
	
	FILE *contactos;//var a * tipo FILE llamado contactos
	contactos = fopen("contactos.txt", "r");//
	if (contactos == NULL){
		printf("No existe fichero contactos.txt\n");
		return 0;
	}
	
	while(fscanf(contactos, "%s %d %d", nuevo.nombre, &(nuevo.puerto), &(nuevo.ip))!=EOF){
		agregarContacto(&nuevo);
		fgets(line, 100, contactos);//para saltar la linea
	}
	fclose(contactos);
	return 0;
}
