#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

//VARIABLES GLOBALES
struct contacto{
	char nombre[50];
	char ip[16];
	int puerto;
}listaContactos[100];//arreglo de structs contacto con capacidad para 100 contactos

int ultimoCont;//variable tipo int que guarda el numero de la posicion del ultimo contacto introducido


/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/


//Funcion main basicamente llama a la funcion menu y llena el struct
void main(){
	leerTxt();//llena el struct con los datos del txt
	menu();
}

/*Funcion muestra el menu al inicio*/
int menu(){
	int opc;
	printf("\n\nEscriba el número de la acción que desea ejecutar y presione Enter...\n1.Agregar Contactos\n2.Enviar Mensaje\n3.Ver lista de contactos\n4.Salir\n");
	scanf("%d", &opc);
	if (opc==1){
		datosContacto();
	}
	else if(opc==3){
		imprimeContactos();
	}
	else if(opc==2){
		enviarMensaje();
	}
	return 0;
}

int enviarMensaje(){
	char ip[16];
	char *ptr;
	system("clear");
	printf("\nEnviar mensaje a:\n");
	int opc = 0;
	imprimeContactos_aux();
	printf("Escriba el numero del cliente y presione Enter...\n");
	scanf("%d", &opc);
	//printf(listaContactos[opc-1].ip);
	servidor(listaContactos[opc-1].puerto);
	//cliente(li)
	
}



int ff(int argc, char *argv[]){
int estado;
if(fork()){
wait(estado);
cliente();
}

else{

servidor(20000);}



}

int servidor(int puerto)
{
//Definir variables,estructuras
struct sockaddr_in server;
struct sockaddr_in client;
int fd,fd2,longitud_cliente,numbytes;
char buf[1024]; //Para recibir mensaje
char enviar2[1024]; //Para enviar mensaje
char enviar[1024]; //Para enviar mensaje

system("clear");
 printf("La direccion del servidor es 127.0.0.1\n\n");
 /*printf("Por favor introduzca el puerto de escucha: \n\n");*/
 /*scanf("%d",&puerto);*/

 server.sin_family= AF_INET;
 server.sin_port = htons(puerto);
 server.sin_addr.s_addr = INADDR_ANY;
 bzero(&(server.sin_zero),8);

 //Definicion de socket
 if (( fd=socket(AF_INET,SOCK_STREAM,0) )<0){
 perror("Error de apertura de socket");
 exit(-1);
 }

 //Avisar al sistema que se creo un socket
 if(bind(fd,(struct sockaddr*)&server, sizeof(struct sockaddr))==-1) {
 printf("error en bind() \n");
 exit(-1);
 }

 //Establecer el socket en modo escucha
 if(listen(fd,5) == -1) {
 printf("error en listen()\n");
 exit(-1);
 }

 printf("SERVIDOR EN ESPERA...\n");
 longitud_cliente= sizeof(struct sockaddr_in);
 if ((fd2 = accept(fd,(struct sockaddr *)&client,&longitud_cliente))==-1) {
 printf("error en accept()\n");
 exit(-1);
 }

 printf("------SESION INICIADA------\n");
 printf("CLIENTE CONECTADO\n");
 strcpy(enviar,"SERVIDOR CONECTADO...");
 send(fd2, enviar, 1024,0);

//Ciclo para enviar y recibir mensajes
 while(1){
 //El servidor espera el primer mensaje
 recv(fd2,buf,1024,0);
 if(strcmp(&buf,"salir")==0){
 break;
 }
 printf("Cliente: %s\n",buf);

 //El cliente recibe el mensaje del servidor
 printf("Escribir mensaje: ");
 scanf("%*c%[^\n]",enviar2);
 send(fd2,enviar2,1024,0);
 if(strcmp(enviar2,"salir")==0){
 break;
 }
}
 close(fd2);
 close(fd);

}



 cliente(int puerto1)
{
 //Definir variables,estructuras
 struct sockaddr_in server;
 char ip[16];
 int fd, numbytes,puerto;
 char buf[1024];
 char enviar[1024];

 system("clear");

printf("ingrese la ip del servidor\n");
 scanf("%s",ip);

//printf("ingrese el puerto de conexion\n");
 //scanf("%d",&puerto);
 puerto = puerto1;

 //Socket
 if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){
 printf("socket() error\n");
 exit(-1);
 }

 //Datos del servidor
 server.sin_family = AF_INET;
 server.sin_port = htons(puerto);
 server.sin_addr.s_addr=inet_addr(ip);
 bzero(&(server.sin_zero),8);

//Conectarse al servidor
 if(connect(fd, (struct sockaddr *)&server,
 sizeof(struct sockaddr))==-1){
 printf("connect() error\n");
 exit(-1);
 }
 //Recibir mensaje de bienvenida
 if ((numbytes=recv(fd,buf,1024,0)) == -1){
 printf("Error en recv() \n");
 exit(-1);
 }
 printf("%s\n",buf);
//Ciclo para enviar y recibir mensajes
while(1){
 //El servidor espera el primer mensaje
 printf("Escribir mensaje: ");
 scanf("%*c%[^\n]",enviar);
 send(fd,enviar,1024,0);
 if(strcmp(enviar,"salir")==0){
 break;
 }

 //El cliente recibe el mensaje del servidor
 recv(fd,buf,1024,0);
 if(strcmp(buf,"salir")==0){
 break;
 }
 printf("Servidor: %s\n",buf);
}
 close(fd);
}

/*Funcion que pregunta al usuario el nombre, ip y puerto, guarda esta info en un struct 
*/
void datosContacto(){
	system("clear");
	struct contacto nuevo;
	printf("\nAgregando nuevo contacto\nNombre: ");
	scanf("%s", nuevo.nombre);
	printf("Ip: ");
	scanf("%s", nuevo.ip);
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
	
	printf("\nLista de Contactos\n\n");
	imprimeContactos_aux();
	
	menu();
}

void imprimeContactos_aux(){
	int e = 0;//para recorrer listaContactos
	while (listaContactos[e].puerto != 0){//while para mostrar en pantalla los contactos,
		printf("%d) Nombre = %s, Ip = %s,  Puerto = %d\n", e+1, listaContactos[e].nombre, listaContactos[e].ip, listaContactos[e].puerto);
		e++;
	}
}

/*Funcion que  guarda un contacto en la ultima linea del txt
 * */
int guardarTxt(char nombre[], char ip[], int puerto){
	FILE *contactos;
	contactos = fopen("contactos.txt", "a");
	fprintf(contactos, "%s %s %d\n", nombre, ip, puerto);
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
	
	while(fscanf(contactos, "%s %s %d", nuevo.nombre, nuevo.ip, &(nuevo.puerto))!=EOF){
		agregarContacto(&nuevo);
		fgets(line, 100, contactos);//para saltar la linea
	}
	fclose(contactos);
	return 0;
}
