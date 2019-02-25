#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>

//FUNCION PARA TEMPORIZAR EL INPUT DEL USUARIO
int inputUsuario(){
    time_t rawtime;
    struct tm * timeinfo;
    int numTecleado = 0;
    int n,m, diff;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    n =  timeinfo->tm_sec;
    do{
       if(kbhit()){
          scanf("%d",&numTecleado);
          fflush(stdin);
          break;
       }
       time (&rawtime);
       timeinfo = localtime (&rawtime);
       m = timeinfo->tm_sec;
       diff = m - n;
       if(diff < 0 )         // si el minuto termina, los segundos se resetean
          diff += 60;   
    }while( diff <= 2);
    return numTecleado;
}
//FUNCION PARA LIMPIAR LA PANTALLA
void clrscr(){
    system("@cls||clear");
}
//FUNCION PARA COLOREAR TERMINAL
void SetConsoleColour(WORD* Attributes, DWORD Colour){
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &Info);
    *Attributes = Info.wAttributes;
    SetConsoleTextAttribute(hStdout, Colour);
}

void ResetConsoleColour(WORD Attributes){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}

void println(){
     printf("\n");
}
//CREAR BOMBO  ------------------------------------------------------
void llenarBombo(int bombo[90]){
     int cont;
     for(cont=0;cont<90;cont++){
        bombo[cont]=cont+1;
    }
}
//CREAR CARTON   ----------------------------------------------------
void crearCarton(int carton[3][9]){
     WORD Attributes = 0;
     bool existe=false;
     int i,j,cont,numero,aux;
     srand(time(NULL));
     for(i=0;i<3;i++){
        for(j=0;j<9;j++){
               do{
               numero=rand()%9+1;
               numero+=(j*10);  
               }while(numero == carton[0][j] || numero == carton[1][j] || numero == carton[2][j]);
               carton[i][j]=numero;
        }
     }
    for (j=0;j<9;++j){
        for (i=0;i<3;++i){
            for (int k = i + 1; k < 3; ++k){
                if (carton[i][j] > carton[k][j]){
                    aux = carton[i][j];
                    carton[i][j] = carton[k][j];
                    carton[k][j] = aux;
                }
            }
        }
    } 
    for(i=0;i<3;i++){
        for(cont=0;cont<4;cont++){
            do{                      
               numero=rand()%9+1;
               }while(carton[0][numero] == 0 && carton[1][numero] == 0 && carton[2][numero] == 0);
               carton[i][numero] = 0;
        }
    }                   
    Sleep(500);
}
//COMPROBAR SI HAY LINEA       ------------------------------------------
bool hayLinea(int carton[3][9], int cartonVerde[3][9]){
     int i,j,linea;
     bool hayLinea;
     
     for(i=0;i<3;i++){
         linea=0;
         for(j=0;j<9;j++){
             if(carton[i][j] == cartonVerde[i][j] || carton[i][j] == 0){
                linea++;
             }
             if(linea == 9){
                hayLinea=true;
                break;
             }else{
                   hayLinea=false;
                   }
         }
     }
     return hayLinea;
}
//COMPROBAR SI HAY BINGO       ------------------------------------------
bool hayBingo(int carton[3][9], int cartonVerde[3][9]){
     int i,j,bingo;
     bool hayBingo;
     bingo=0;
     
     for(i=0;i<3;i++){
         for(j=0;j<9;j++){
             if(carton[i][j] == 0){
                cartonVerde[i][j]=0;
             }
             if(carton[i][j] == cartonVerde[i][j]){
                bingo++;
             }
         }
     }
     if(bingo == 27){
        hayBingo=true;
     }
     return hayBingo;
}
//MOSTRAR CARTON             -------------------------------------------------
void mostrarCarton(int carton[3][9], int cartonVerde[3][9], int numeroCantado, int numTecleado){
     int i, j, cont;
     WORD Attributes = 0;
     println();
     printf("____________________________");
     printf("\n|");
     for(i=0;i<3;i++){
         for(j=0;j<9;j++){
             if(carton[i][j] == 0){          
                printf("__|");
             }else{
                   if(carton[i][j] == numeroCantado && carton[i][j] == numTecleado){
                      cartonVerde[i][j]=carton[i][j];
                   }
                   if(carton[i][j] == cartonVerde[i][j]){
                      SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
                      printf("%2d|",carton[i][j]);
                      ResetConsoleColour(Attributes);
                   }else{   
                         printf("%2d|",carton[i][j]);   
                         }
                   }
         }
         if(i == 2){
            break;
         }else{
               printf("\n|");
               }  
     }
}
//---------------------------MENU PRINCIPAL-------------------------------------
int abrirMenu(){
    int opcion;
     do{
        clrscr();
        printf("\n-------------------------------------------------------------+\n");
        printf("oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   |\n`888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  |\n 888     888  888   8 `88b.    8  888           888      888 |\n 888oooo888'  888   8   `88b.  8  888           888      888 |\n 888    `88b  888   8     `88b.8  888     ooooo 888      888 |\n 888    .88P  888   8       `888  `88.    .88'  `88b    d88' |\no888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  |");
        printf("\n-------------------------------------------------------------+\n\n");
        Sleep(100);
        printf("\n 1.JUGAR\n");
        Sleep(100);
        printf("\n 2.INSTRUCCIONES\n");
        Sleep(100);
        printf("\n 3.SALIR");
        Sleep(100);
        printf("\n\nSeleccione el numero de la opcion que desea realizar[1-3]: ");
        scanf("%d",&opcion);
        fflush(stdin);
        }while(opcion != 1 && opcion != 2 && opcion != 3);
        return opcion;
}

void instrucciones(){
     clrscr();
     printf("\n-------------------------------------------------------------+\n");
     printf("oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   |\n`888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  |\n 888     888  888   8 `88b.    8  888           888      888 |\n 888oooo888'  888   8   `88b.  8  888           888      888 |\n 888    `88b  888   8     `88b.8  888     ooooo 888      888 |\n 888    .88P  888   8       `888  `88.    .88'  `88b    d88' |\no888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  |");
     printf("\n-------------------------------------------------------------+\n");
     printf("                    GAME MASTER EDITION\n");
     Sleep(100);
     printf("\n                   INSTRUCCIONES DEL JUEGO");
     printf("\n                   -----------------------\n\n");
     printf("      El juego del bingo se compone de un bombo con bolas numeradas, \ncartones con numeros aleatorios impresos y rotuladores o fichas para tachar o tapar estos.\nEl usuario debe introducir su nombre, y podra jugar con un maximo de 4 cartones.\n\n      Una partida consiste en extraer las bolas del bombo al azar \ny cantar su respectiva numeracion. Los jugadores, provistos de cartones, \ndeberan introducir los numeros que hayan salido y tengan en el carton.\nAl completar una linea horizontal en un carton, el jugador debera cantar (LINEA).\nCuando un jugador consigue tachar todos los numeros de su carton, \nel programa automaticamente cantara (BINGO).\n\nIMPORTANTE:\n\nAunque el numero haya salido y este en los cartones\nsi no ha sido introducido, no se cantara el BINGO.");           
     getchar();
}
//---------------------------PROGRAMA PRINCIPAL---------------------------------

int main(){
    system("mode con: cols=100 lines=50");
    bool existe,bingo;
    bool linea = false;
    int opcion=0;
    char nombre[20];
    char ch;
    int carton[3][9];
    int carton2[3][9];
    int carton3[3][9];
    int carton4[3][9];
    int cartonVerde[3][9];
    int cartonVerde2[3][9];
    int cartonVerde3[3][9];
    int cartonVerde4[3][9];
    int confirmados[89];
    int bombo[89];
    int i, j, cont, cuantosCartones, numeroCantado, comprobar, numTecleado;
    numTecleado=0;
    //----------PANTALLA DE INICIO
    Sleep(500);
    printf("\n                                                           .-:::::--.``                              \n                                                      `:+soo++//:--....```                          \n                                ``..-:-:::---.`     .::--.`  `.---.```   ```         ``             \n            ````...`        `..---::://+++oossso+:..:+sssoo+-`   ```       ``    `````.---.`        \n           ```.--:/+++:. `........---:://++ooo+++oosy/.``.:/+/-`   `             ```````..-::.      \n            ``..-:/+oo+:..``   ``...--:://:-`     ``.:/-    `:/:.   ```             ``.--::-.--`    \n   ```      ``.--:/++/-.`        ``..---.`   .-/+ooo+:-.-.`   -:-.```...`````     ````````.-::..`   \n  `-.      `..--:/+/:-.`          ``...   `-/osssyyyyyys/-:/```````............````         `.::.`  \n `:-`    ..---::/+/:-.`           `.`   `-/+ooo+:.```.-/os+-`   ````............-.` ``.`  -::/.-/.  \n -+.``  ...--:/+++/:-`         `````   .:/++/-`         `./s-    ````...........-----:/- ./:`:/`/:  \n /+``   ````````/+/-`        ```..`   -:///-`            `..o:    ``............------/:``:+/++-:/  \n //  `.-++++++/:++/````    `.....`  `-//+/`     ````    -ss-`o- ```.............-------/../+::o+//  \n .-./++/:::://+ooo-````````-----.   ://+/`   .:+ossso:`-yyys`.o`...............--------:/:oo/+s+o-  \n  ./o/.``     `+so.```````-////-   :++++`    +yso++syy+.o:oy-`o...............----------::/+oo+o/   \n   .o-.:::..---oso````````/++++.  `+ooo:     .-````.yyy..`/y+.+-......................--//++oss/    \n    .:/s+/::///syo.```````+ooo+   :ooss`     ``````-yys...:y+.+-...........``          `:ssys+.     \n      .:++oo//+sys.....--:osss/   +ssss  `````````-syy:..-:y+-o........`     ``...-----``oo:.       \n         .-://++yy//+ossyyysss/   +yyyy`````````.+yys:----/y///.....`    `..-------::/++.`          \n                :yyyyyyyyyyyyyo   /yyyy:`````.-/syy+:://::oo+o---.`   `.------..````.-os:           \n                 +yyyyyyyyyyyyy.``.syyys.`...+syyyyyyyy+///+s:--.`  `.----.``     ````.s`           \n                  +yyyyyyyyyyyy+```:yyyyo-..:sssoooo++++/:+s/---   .----.` ```..-:/o.`:`            \n                   :yyyyyyyyyyyy/``.:syyys/--::::///++++/ss:---`  .---.`````./+oooo/..`             \n                    .+yyyyyyyyyyy+-..-oyyyys+////++oo++sy+:::::.``:::-`.....+ss//---`               \n                      .+yyyyyyyyyyy+:--/oyyyyhyyyyyssyy:` .:///:../++----::oyyyys:`                 \n                        `:oyyyyyyyyyyo+///+ssyyyssss+-      `.:++::sy+:////++//-                    \n                           `:+oyyyyyyyyyssoooooo+/.             `.-.:/:----`                        \n                                .-:/+++++++/:-`                                                      \n");
    printf("\n");
    printf("                   oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   \n                   `888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  \n                    888     888  888   8 `88b.    8  888           888      888 \n                    888oooo888'  888   8   `88b.  8  888           888      888 \n                    888    `88b  888   8     `88b.8  888     ooooo 888      888 \n                    888    .88P  888   8       `888  `88.    .88'  `88b    d88' \n                   o888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  ");
    Sleep(2000);
    
do{
    FILE *numCant;
    WORD Attributes = 0;
    llenarBombo(bombo);
    crearCarton(carton);
    opcion=abrirMenu();
//--------SE ABRE LA PANTALLA DE INSTRUCCIONES
    if(opcion == 2){
        do{
           instrucciones();
           opcion=abrirMenu();
        }while(opcion == 2);
     }
//-------------AQUI EMPIEZA EL JUEGO
//PIDE NOMBRE
    if(opcion == 1){
       clrscr(); 
       printf("\n-------------------------------------------------------------+\n");
       printf("oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   |\n`888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  |\n 888     888  888   8 `88b.    8  888           888      888 |\n 888oooo888'  888   8   `88b.  8  888           888      888 |\n 888    `88b  888   8     `88b.8  888     ooooo 888      888 |\n 888    .88P  888   8       `888  `88.    .88'  `88b    d88' |\no888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  |");
       printf("\n-------------------------------------------------------------+\n\n");
       printf("\nIntroduzca su nombre: ");
       scanf("%s",&nombre);
       fflush(stdin);
//PIDE CARTONES
       do{
          printf("\n%s, con cuantos cartones quieres jugar?[1-4]: ",nombre);
          scanf("%d",&cuantosCartones);
          fflush(stdin);
       }while(cuantosCartones <1 || cuantosCartones >4);
       clrscr();
       printf("\n-------------------------------------------------------------+\n");
       printf("oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   |\n`888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  |\n 888     888  888   8 `88b.    8  888           888      888 |\n 888oooo888'  888   8   `88b.  8  888           888      888 |\n 888    `88b  888   8     `88b.8  888     ooooo 888      888 |\n 888    .88P  888   8       `888  `88.    .88'  `88b    d88' |\no888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  |");
       printf("\n-------------------------------------------------------------+\n\n");
       for(cont=0;cont<90;cont++){
           printf("%2d ",bombo[cont]);
           if(bombo[cont]%10 == 0){
                 println();
              }else;
       }
//GENERAR LOS CARTONES
       printf("\n\nGenerando cartones, por favor espere"); printf("."); Sleep(100); printf("."); Sleep(100); printf(".");
       switch (cuantosCartones){
              case 1: 
                   crearCarton(carton);
                   break;
              case 2: 
                   crearCarton(carton);
                   crearCarton(carton2);
                   break;
              case 3: 
                   crearCarton(carton);
                   crearCarton(carton2);
                   crearCarton(carton3);
                   break;
              case 4: 
                   crearCarton(carton);
                   crearCarton(carton2);
                   crearCarton(carton3);
                   crearCarton(carton4);
                   break;
       }
       clrscr();
       printf("\n-------------------------------------------------------------+\n");
       printf("oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   |\n`888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  |\n 888     888  888   8 `88b.    8  888           888      888 |\n 888oooo888'  888   8   `88b.  8  888           888      888 |\n 888    `88b  888   8     `88b.8  888     ooooo 888      888 |\n 888    .88P  888   8       `888  `88.    .88'  `88b    d88' |\no888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  |");
       printf("\n-------------------------------------------------------------+\n\n");
       for(cont=0;cont<90;cont++){
           printf("%2d ",bombo[cont]);
           if(bombo[cont]%10 == 0){
                 println();
              }else;
       }
       printf("\nEl juego comenzara enseguida...");
       Sleep(100);
       printf("\n\n\nPulse ENTER para comenzar...");
       getchar();
       clrscr();
       do{
          printf("\n-------------------------------------------------------------+\n");
          printf("oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   |\n`888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  |\n 888     888  888   8 `88b.    8  888           888      888 |\n 888oooo888'  888   8   `88b.  8  888           888      888 |\n 888    `88b  888   8     `88b.8  888     ooooo 888      888 |\n 888    .88P  888   8       `888  `88.    .88'  `88b    d88' |\no888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  |");
          printf("\n-------------------------------------------------------------+\n\n");
          
//SACAR NUMERO NO REPETIDO PRINTEARLO EN EL TXT Y GUARDARLO PARA SER COLOREADO
          cont=0;
          do{
             numCant=fopen("bombo.txt","r+");
             fscanf(numCant,"%2d",&numeroCantado);
             fclose(numCant);
             confirmados[numeroCantado-1]=numeroCantado;
             for(cont=0;cont<89;cont++){
                 if(confirmados[cont] == numeroCantado){
                    existe=true;
                 }else{
                       existe=false;
                       }
             }
          }while(existe == true);
//MOSTRAR BOMBO Y COLOREAR LOS NUMEROS QUE YA HAN SALIDO
          for(cont=0;cont<90;cont++){
              if(bombo[cont] == confirmados[cont]){
                 SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED);            
                 printf("%2d ", bombo[cont]);
                 ResetConsoleColour(Attributes);
              }else{printf("%2d ", bombo[cont]);}
     
              if(bombo[cont]%10 == 0){
                 println();
              }else;
          } 
       //CANTAR NUMERO EN LA PANTALLA
          println(); println(); printf("EL NUMERO %2d", numeroCantado); println();
       //MOSTRAR CARTON Y BUSCAR SI HAY BINGO O LINEA
       printf("\n      Tablero de %s \n----------------------------",nombre);
       switch (cuantosCartones){
              case 1: 
                   mostrarCarton(carton,cartonVerde,numeroCantado,numTecleado);
                   bingo=hayBingo(carton,cartonVerde);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE BINGO
                   if(bingo == true){
                      FILE *jugBingo;
                      jugBingo=fopen("bingo.txt","w+");
                      fputs(nombre,jugBingo);
                      printf("\nBINGO!!!\nHAS GANADO");
                      fclose(jugBingo);
                      getchar();
                      break;
                   }
                   linea=hayLinea(carton,cartonVerde);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE LINEA
                   if(linea == true){
                      FILE *jugLinea;
                      jugLinea=fopen("linea.txt","w+");
                      fputs(nombre,jugLinea);
                      printf("LINEA!!!");
                      fclose(jugLinea);
                   } 
                   break;
              case 2: 
                   mostrarCarton(carton,cartonVerde,numeroCantado,numTecleado);
                   bingo=hayBingo(carton,cartonVerde);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE BINGO
                   if(bingo == true){
                      FILE *jugBingo;
                      jugBingo=fopen("bingo.txt","w+");
                      fputs(nombre,jugBingo);
                      printf("\nBINGO!!!\nHAS GANADO");
                      fclose(jugBingo);
                      getchar();
                      break;
                   }
                   linea=hayLinea(carton,cartonVerde);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE LINEA
                   if(linea == true){
                      FILE *jugLinea;
                      jugLinea=fopen("linea.txt","w+");
                      fputs(nombre,jugLinea);
                      printf("LINEA!!!");
                      fclose(jugLinea);
                   } 
                   
                   mostrarCarton(carton2,cartonVerde2,numeroCantado,numTecleado);
                   bingo=hayBingo(carton2,cartonVerde2);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE BINGO
                   if(bingo == true){
                      FILE *jugBingo;
                      jugBingo=fopen("bingo.txt","w+");
                      fputs(nombre,jugBingo);
                      printf("\nBINGO!!!\nHAS GANADO");
                      fclose(jugBingo);
                      getchar();
                      break;
                   }
                   linea=hayLinea(carton2,cartonVerde2);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE LINEA
                   if(linea == true){
                      FILE *jugLinea;
                      jugLinea=fopen("linea.txt","w+");
                      fputs(nombre,jugLinea);
                      printf("LINEA!!!");
                      fclose(jugLinea);
                   } 
                   break;
              case 3: 
                   mostrarCarton(carton,cartonVerde,numeroCantado,numTecleado);
                   bingo=hayBingo(carton,cartonVerde);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE BINGO
                   if(bingo == true){
                      FILE *jugBingo;
                      jugBingo=fopen("bingo.txt","w+");
                      fputs(nombre,jugBingo);
                      printf("\nBINGO!!!\nHAS GANADO");
                      fclose(jugBingo);
                      getchar();
                      break;
                   }
                   linea=hayLinea(carton,cartonVerde);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE LINEA
                   if(linea == true){
                      FILE *jugLinea;
                      jugLinea=fopen("linea.txt","w+");
                      fputs(nombre,jugLinea);
                      printf("LINEA!!!");
                      fclose(jugLinea);
                   } 
                   
                   mostrarCarton(carton2,cartonVerde2,numeroCantado,numTecleado);
                   bingo=hayBingo(carton2,cartonVerde2);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE BINGO
                   if(bingo == true){
                      FILE *jugBingo;
                      jugBingo=fopen("bingo.txt","w+");
                      fputs(nombre,jugBingo);
                      printf("\nBINGO!!!\nHAS GANADO");
                      fclose(jugBingo);
                      getchar();
                      break;
                   }
                   linea=hayLinea(carton2,cartonVerde2);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE LINEA
                   if(linea == true){
                      FILE *jugLinea;
                      jugLinea=fopen("linea.txt","w+");
                      fputs(nombre,jugLinea);
                      printf("LINEA!!!");
                      fclose(jugLinea);
                   } 
                   
                   mostrarCarton(carton3,cartonVerde3,numeroCantado,numTecleado);
                   bingo=hayBingo(carton3,cartonVerde3);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE BINGO
                   if(bingo == true){
                      FILE *jugBingo;
                      jugBingo=fopen("bingo.txt","w+");
                      fputs(nombre,jugBingo);
                      printf("\nBINGO!!!\nHAS GANADO");
                      fclose(jugBingo);
                      getchar();
                      break;
                   }
                   linea=hayLinea(carton3,cartonVerde3);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE LINEA
                   if(linea == true){
                      FILE *jugLinea;
                      jugLinea=fopen("linea.txt","w+");
                      fputs(nombre,jugLinea);
                      printf("LINEA!!!");
                      fclose(jugLinea);
                   } 
                   break;
              case 4: 
                   mostrarCarton(carton,cartonVerde,numeroCantado,numTecleado);
                   bingo=hayBingo(carton,cartonVerde);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE BINGO
                   if(bingo == true){
                      FILE *jugBingo;
                      jugBingo=fopen("bingo.txt","w+");
                      fputs(nombre,jugBingo);
                      printf("\nBINGO!!!\nHAS GANADO");
                      fclose(jugBingo);
                      getchar();
                      break;
                   }
                   linea=hayLinea(carton,cartonVerde);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE LINEA
                   if(linea == true){
                      FILE *jugLinea;
                      jugLinea=fopen("linea.txt","w+");
                      fputs(nombre,jugLinea);
                      printf("LINEA!!!");
                      fclose(jugLinea);
                   } 
                   
                   mostrarCarton(carton2,cartonVerde2,numeroCantado,numTecleado);
                   bingo=hayBingo(carton2,cartonVerde2);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE BINGO
                   if(bingo == true){
                      FILE *jugBingo;
                      jugBingo=fopen("bingo.txt","w+");
                      fputs(nombre,jugBingo);
                      printf("\nBINGO!!!\nHAS GANADO");
                      fclose(jugBingo);
                      getchar();
                      break;
                   }
                   linea=hayLinea(carton2,cartonVerde2);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE LINEA
                   if(linea == true){
                      FILE *jugLinea;
                      jugLinea=fopen("linea.txt","w+");
                      fputs(nombre,jugLinea);
                      printf("LINEA!!!");
                      fclose(jugLinea);
                   } 
                   
                   mostrarCarton(carton3,cartonVerde3,numeroCantado,numTecleado);
                   bingo=hayBingo(carton3,cartonVerde3);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE BINGO
                   if(bingo == true){
                      FILE *jugBingo;
                      jugBingo=fopen("bingo.txt","w+");
                      fputs(nombre,jugBingo);
                      printf("\nBINGO!!!\nHAS GANADO");
                      fclose(jugBingo);
                      getchar();
                      break;
                   }
                   linea=hayLinea(carton3,cartonVerde3);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE LINEA
                   if(linea == true){
                      FILE *jugLinea;
                      jugLinea=fopen("linea.txt","w+");
                      fputs(nombre,jugLinea);
                      printf("LINEA!!!");
                      fclose(jugLinea);
                   } 
                   
                   mostrarCarton(carton4,cartonVerde4,numeroCantado,numTecleado);
                   bingo=hayBingo(carton4,cartonVerde4);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE BINGO
                   if(bingo == true){
                      FILE *jugBingo;
                      jugBingo=fopen("bingo.txt","w+");
                      fputs(nombre,jugBingo);
                      printf("\nBINGO!!!\nHAS GANADO");
                      fclose(jugBingo);
                      getchar();
                      break;
                   }
                   linea=hayLinea(carton4,cartonVerde4);
                   //CREAR EL TXT CON EL NOMBRE DEL JUGADOR QUE TIENE LINEA
                   if(linea == true){
                      FILE *jugLinea;
                      jugLinea=fopen("linea.txt","w+");
                      fputs(nombre,jugLinea);
                      printf("LINEA!!!");
                      fclose(jugLinea);
                   } 
                   break;
       }
       //PIDE UN NUMERO Y SI LO TIENE EN EL CARTON Y HA SALIDO LE DEJA PINTARLO
       printf("\n\nIntroduce el numero si lo tienes: ");
       numTecleado=inputUsuario();
       for(cont=0;cont<89;cont++){
           if(numTecleado == confirmados[cont]){
              for(i=0;i<3;i++){
                  for(j=0;j<9;j++){
                      if(numTecleado == carton[i][j]){
                         cartonVerde[i][j]=numTecleado;
                      }
                      if(numTecleado == carton2[i][j]){
                         cartonVerde2[i][j]=numTecleado;
                      }
                      if(numTecleado == carton3[i][j]){
                         cartonVerde3[i][j]=numTecleado;
                      }
                      if(numTecleado == carton4[i][j]){
                         cartonVerde4[i][j]=numTecleado;
                      }
                  }    
              }
           }
       } 
       clrscr();
       }while(bingo != true);
    } 
    //PANTALLA DE CIERRE TEMPORIZADO Y DESPEDIDA 
    if(opcion == 3){
       clrscr();
       printf("\n-------------------------------------------------------------+\n");
       printf("oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   |\n`888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  |\n 888     888  888   8 `88b.    8  888           888      888 |\n 888oooo888'  888   8   `88b.  8  888           888      888 |\n 888    `88b  888   8     `88b.8  888     ooooo 888      888 |\n 888    .88P  888   8       `888  `88.    .88'  `88b    d88' |\no888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  |");
       printf("\n-------------------------------------------------------------+\n\n");
       printf("            GRACIAS POR JUGAR AL BINGO DE APPSMATU!\n\n                       VUELVA PRONTO!\n");
       Sleep(3000);
       system("exit");
    }
}while(opcion != 3);
}
