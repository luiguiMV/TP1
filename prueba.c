#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int servidor(int puerto)
{
//Definir variables de las estructuras
struct sockaddr_in servidor;
struct sockaddr_in cliente;
int socketservidor,socket2,longitud_cliente,numbytes;
char buf[1000]; //Para recibir mensaje
char enviar2[1000]; //Para enviar mensaje
char enviar[1000]; //Para enviar mensaje

system("clear");
 printf("La direccion del servidor es 127.0.0.1\n\n");
 /*printf("Por favor introduzca el puerto de escucha: \n\n");*/
 /*scanf("%d",&puerto);*/

 servidor.sin_family= AF_INET;
 servidor.sin_port = htons(puerto);
 servidor.sin_addr.s_addr = INADDR_ANY;
 bzero(&(servidor.sin_zero),8);

 //Definicion de socket
 if (( socketservidor=socket(AF_INET,SOCK_STREAM,0) )<0){
 perror("Error de apertura de socket");
 exit(-1);
 }

 //Avisar al sistema que se creo un socket
 if(bind(socketservidor,(struct sockaddr*)&servidor, sizeof(struct sockaddr))==-1) {
 printf("error en bind() \n");
 exit(-1);
 }

 //Establecer el socket en modo escucha
 if(listen(socketservidor,5) == -1) {
 printf("error en listen()\n");
 exit(-1);
 }

 printf("SERVIDOR EN ESPERA...\n");
 longitud_cliente= sizeof(struct sockaddr_in);
 if ((socket2 = accept(socketservidor,(struct sockaddr *)&cliente,&longitud_cliente))==-1) {
 printf("error en accept()\n");
 exit(-1);
 }

 printf("------SESION INICIADA------\n");
 printf("CLIENTE CONECTADO\n");
 strcpy(enviar,"SERVIDOR CONECTADO...");
 send(socket2, enviar, 1000,0);

//Ciclo para enviar y recibir mensajes
 while(1){
 //El servidor espera el primer mensaje
 recv(socket2,buf,1000,0);
 if(strcmp(&buf,"salir")==0){
 break;
 }
 printf("\033[2K\r\033[01;37m""Cliente:\033[00;37m %s\n",buf);

 //El cliente recibe el mensaje del servidor
 printf("Escribir mensaje: ");
 scanf("%*c%[^\n]",enviar2);
 send(socket2,enviar2,1024,0);
 if(strcmp(enviar2,"salir")==0){
 break;
 }
}
 close(socket2);
 close(socketservidor);

}



 cliente()
{
 //Definir variables,estructuras
 struct sockaddr_in servidor;
 char ip[16];
 int socketservidor, numbytes,puerto;
 char buf[1024];
 char enviar[1024];

 system("clear");

printf("ingrese la ip del servidor\n");
 scanf("%s",ip);

printf("ingrese el puerto de conexion\n");
 scanf("%d",&puerto);

 //Socket
 if ((socketservidor=socket(AF_INET, SOCK_STREAM, 0))==-1){
 printf("socket() error\n");
 exit(-1);
 }

 //Datos del servidor
 servidor.sin_family = AF_INET;
 servidor.sin_port = htons(puerto);
servidor.sin_addr.s_addr=inet_addr(ip);
 bzero(&(servidor.sin_zero),8);

//Conectarse al servidor
 if(connect(socketservidor, (struct sockaddr *)&servidor,
 sizeof(struct sockaddr))==-1){
 printf("connect() error\n");
 exit(-1);
 }
 //Recibir mensaje de bienvenida
 if ((numbytes=recv(socketservidor,buf,1024,0)) == -1){
 printf("Error en recv() \n");
 exit(-1);
 }
 printf("%s\n",buf);
//Ciclo para enviar y recibir mensajes
while(1){
 //El servidor espera el primer mensaje
 printf("Escribir mensaje: ");
 scanf("%*c%[^\n]",enviar);
 send(socketservidor,enviar,1000,0);
 if(strcmp(enviar,"salir")==0){
 break;
 }

 //El cliente recibe el mensaje del servidor
 recv(socketservidor,buf,1000,0);
 if(strcmp(buf,"salir")==0){
 break;
 }
 printf("\034[2K\r\034[01;38m""Servidor:\034[00;38m %s\n",buf);
}
 close(socketservidor);
}


int main(int argc, char *argv[]){
int estado;
if(fork()){
wait(estado);
cliente();
}

else{

servidor(20000);}



}



