#include <cstdlib>
#include <stdio.h>
#include <string.h>
using namespace std;

void error(int cod){
    if (cod==1)
        printf("\nDebe ingresar al menos un parametro...\n");
    else
        printf("\nParametros invalidos o inexistentes (%d)\n", cod);
}
void informacion(){
    printf("\nIntegrantes: \nAlejandra Munoz\nMarcial Jara\nHenry Sepulveda\n\nFecha de compilacion: 2014-03-30\n");
}
signed long stringAint(char *cadena){
    int i;
    cadena[0]='0';
    i=strlen(cadena);
    cadena[i-3]='0';
    return((atoi(cadena))/10);
}
int numerodemes(char *fecha){
    char numero[2];
    numero[0]=fecha[6];
    numero[1]=fecha[7];
    return (atoi(numero));
}


void suma_total(char *archivo_in){
        char buffer[51], tienda[13];//, nombre[50],fecha[50], numero[50];
        char *monto_string;
        unsigned long long monto;
        unsigned long long ventas;
        FILE *archivo;
        ventas=0;
        archivo=fopen(archivo_in, "r"); //abre para lectura ("r") - r/w
        if(archivo==NULL) //comprobaciÃ³n de apertura
                printf("\n el archivo no se pudo abrir\n");
        while (feof(archivo)==0){
                fgets(buffer, 50, archivo); 
                if (feof(archivo)==0){      //condicion necesaria para evitar punteros a vacÃ­os
                        strtok(buffer,";");
                        strtok(NULL,";");
                        monto_string=strtok(NULL,";");
                        monto=stringAint(monto_string);
                        ventas=ventas+monto;
                }
        }
        printf("\nMonto total de venta de todas las tiendas: $%llu%llu\n fin",ventas, ventas%100);
        //printf("\nMonto total de venta de todas las tiendas: \n");
        fclose(archivo);
}

void eliminarcomillas(char *nombre){
    int i,j;
    j=strlen(nombre);
    nombre[j-1]='\0'; //Borra comillas del final
    for(i=0;i<j;i++)
        nombre[i]=nombre[i+1];
}
void mesenplabras(int num,char *messtr){
    switch(num){
        case 0: strcpy(messtr,"Enero"); break;
        case 1: strcpy(messtr,"Febrero"); break;
        case 2: strcpy(messtr,"Marzo"); break;
        case 3: strcpy(messtr,"Abril"); break;
        case 4: strcpy(messtr,"Mayo"); break;
        case 5: strcpy(messtr,"Junio"); break;
        case 6: strcpy(messtr,"Julio"); break;
        case 7: strcpy(messtr,"Agosto"); break;
        case 8: strcpy(messtr,"Septiembre"); break;
        case 9: strcpy(messtr,"Octubre"); break;
        case 10: strcpy(messtr,"Noviembre"); break;
        case 11: strcpy(messtr,"Diciembre"); break;
        
    }
}

void suma_mensual(char *tienda, char *archivo_in){
        char buffer[51], mes_str[13];
        char *monto_string, *nombre, *fecha;
        unsigned long monto;
        unsigned long long ventas[12];
        int mes;
        FILE *archivo;
        for (mes=0;mes<=11;mes++)
                ventas[mes]=0;
   
        archivo=fopen(archivo_in, "r"); //abre para lectura ("r") - r/w
        if(archivo==NULL) //comprobaciÃ³n de apertura
                printf("\n el archivo no se pudo abrir\n");
        while (feof(archivo)==0){
                fgets(buffer, 50, archivo);  //se toma una fila del archivo
                if (feof(archivo)==0){      //condicion necesaria para evitar punteros a vacÃ­os
                        nombre=strtok(buffer,";");  //Se separan los campos nombre, fecha, monto de venta
                        fecha=strtok(NULL,";");
                        monto_string=strtok(NULL,";");
                        eliminarcomillas(nombre);   //Se eliminan comillas 
                        mes = numerodemes(fecha);    //Se filtra numero de mes
                        monto=stringAint(monto_string); //Se convierte la cadena monto en un entero 
                        if(strcmp(tienda,nombre)==0)   
                            ventas[mes-1]=ventas[mes-1]+monto;
                }
        }
        printf("\nTienda: %s\n\n",tienda);
        for (mes=0; mes<=11; mes++){
            mesenplabras(mes,mes_str);
            printf("%s: $%llu\n",mes_str,ventas[mes]);
            }
        fclose(archivo);
            
}

int main(int argc, char** argv) {
    if (argc==1)
        error(1);
    if (argc==2){
        if (strcmp(argv[1],"-v")==0)
            informacion();
        else
            error(2);
    }
    if (argc==3){
        if (strcmp(argv[1],"-s")==0)
            suma_total(argv[2]);
        else
            error(3);
    }
     if (argc==4){
        if (strcmp(argv[1],"-a")==0)
            suma_mensual(argv[2],argv[3]);
        else
            error(4);
    }
    return 0;
}