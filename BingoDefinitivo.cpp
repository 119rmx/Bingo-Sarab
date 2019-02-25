#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>

void clrscr()
{
    system("@cls||clear");
}

void SetConsoleColour(WORD* Attributes, DWORD Colour)
{
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &Info);
    *Attributes = Info.wAttributes;
    SetConsoleTextAttribute(hStdout, Colour);
}

void ResetConsoleColour(WORD Attributes)
{
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
    int i,j,cont,numero;
    srand(time(NULL));
    for(i=0;i<3;i++){
        for(j=0;j<9;j++){
            numero=rand()%9+1;
            carton[i][j]=numero+(j*10);
        }
    }
    for(i=0;i<3;i++){
            for(cont=0;cont<4;cont++){
                do{                      
                   numero=rand()%9+1;
                }while(carton[i][numero] == 0);
                       carton[i][numero] = 0;
            }
    }
    Sleep(1000);
}
//MOSTRAR CARTON   -------------------------------------------------
void mostrarCarton(int carton[3][9], int cartonVerde[3][9], int numeroCantado){
     int i, j;
     WORD Attributes = 0;
          printf("\n--------CARTON---------");
          println();
          printf("____________________________");
          printf("\n|");
          for(i=0;i<3;i++){
              for(j=0;j<9;j++){
                  if(carton[i][j] == 0){          
                  printf("__|");
                  }else{
                        if(carton[i][j] == numeroCantado){
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

}
//---------------------------PROGRAMA PRINCIPAL---------------------------------

int main(){
    bool existe;
    int opcion=0;
    char nombre[20];
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
    int i, j, cont, cuantosCartones, contBucle, numeroCantado, comprobar;
    contBucle=0;
    WORD Attributes = 0;
    llenarBombo(bombo);
    crearCarton(carton);
//----------PANTALLA DE INICIO
   /* Sleep(500);
    printf("\n                                                           .-:::::--.``                              \n                                                      `:+soo++//:--....```                          \n                                ``..-:-:::---.`     .::--.`  `.---.```   ```         ``             \n            ````...`        `..---::://+++oossso+:..:+sssoo+-`   ```       ``    `````.---.`        \n           ```.--:/+++:. `........---:://++ooo+++oosy/.``.:/+/-`   `             ```````..-::.      \n            ``..-:/+oo+:..``   ``...--:://:-`     ``.:/-    `:/:.   ```             ``.--::-.--`    \n   ```      ``.--:/++/-.`        ``..---.`   .-/+ooo+:-.-.`   -:-.```...`````     ````````.-::..`   \n  `-.      `..--:/+/:-.`          ``...   `-/osssyyyyyys/-:/```````............````         `.::.`  \n `:-`    ..---::/+/:-.`           `.`   `-/+ooo+:.```.-/os+-`   ````............-.` ``.`  -::/.-/.  \n -+.``  ...--:/+++/:-`         `````   .:/++/-`         `./s-    ````...........-----:/- ./:`:/`/:  \n /+``   ````````/+/-`        ```..`   -:///-`            `..o:    ``............------/:``:+/++-:/  \n //  `.-++++++/:++/````    `.....`  `-//+/`     ````    -ss-`o- ```.............-------/../+::o+//  \n .-./++/:::://+ooo-````````-----.   ://+/`   .:+ossso:`-yyys`.o`...............--------:/:oo/+s+o-  \n  ./o/.``     `+so.```````-////-   :++++`    +yso++syy+.o:oy-`o...............----------::/+oo+o/   \n   .o-.:::..---oso````````/++++.  `+ooo:     .-````.yyy..`/y+.+-......................--//++oss/    \n    .:/s+/::///syo.```````+ooo+   :ooss`     ``````-yys...:y+.+-...........``          `:ssys+.     \n      .:++oo//+sys.....--:osss/   +ssss  `````````-syy:..-:y+-o........`     ``...-----``oo:.       \n         .-://++yy//+ossyyysss/   +yyyy`````````.+yys:----/y///.....`    `..-------::/++.`          \n                :yyyyyyyyyyyyyo   /yyyy:`````.-/syy+:://::oo+o---.`   `.------..````.-os:           \n                 +yyyyyyyyyyyyy.``.syyys.`...+syyyyyyyy+///+s:--.`  `.----.``     ````.s`           \n                  +yyyyyyyyyyyy+```:yyyyo-..:sssoooo++++/:+s/---   .----.` ```..-:/o.`:`            \n                   :yyyyyyyyyyyy/``.:syyys/--::::///++++/ss:---`  .---.`````./+oooo/..`             \n                    .+yyyyyyyyyyy+-..-oyyyys+////++oo++sy+:::::.``:::-`.....+ss//---`               \n                      .+yyyyyyyyyyy+:--/oyyyyhyyyyyssyy:` .:///:../++----::oyyyys:`                 \n                        `:oyyyyyyyyyyo+///+ssyyyssss+-      `.:++::sy+:////++//-                    \n                           `:+oyyyyyyyyyssoooooo+/.             `.-.:/:----`                        \n                                .-:/+++++++/:-`                                                      \n");
    printf("\n");
    printf("                   oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   \n                   `888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  \n                    888     888  888   8 `88b.    8  888           888      888 \n                    888oooo888'  888   8   `88b.  8  888           888      888 \n                    888    `88b  888   8     `88b.8  888     ooooo 888      888 \n                    888    .88P  888   8       `888  `88.    .88'  `88b    d88' \n                   o888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  ");
    Sleep(2000);
    */
    opcion=abrirMenu();
//--------SE ABRE LA PANTALLA DE INSTRUCCIONES
    if(opcion == 2){
        do{
           clrscr();
           printf("\n-------------------------------------------------------------+\n");
           printf("oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   |\n`888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  |\n 888     888  888   8 `88b.    8  888           888      888 |\n 888oooo888'  888   8   `88b.  8  888           888      888 |\n 888    `88b  888   8     `88b.8  888     ooooo 888      888 |\n 888    .88P  888   8       `888  `88.    .88'  `88b    d88' |\no888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  |");
           printf("\n-------------------------------------------------------------+\n\n");
           Sleep(100);
           printf("                   INSTRUCCIONES DEL JUEGO");
           printf("\n                   -----------------------\n\n");
           printf("         El juego del bingo se compone de un bombo con bolas numeradas, cartones con numeros aleatorios impresos y rotuladores o fichas para tachar o tapar estos.\n   Una partida consiste en extraer las bolas del bombo al azar y cantar su respectiva numeracion.\n   Los jugadores, provistos de cartones, tacharan el numero cuando sea cantado por el cajero (persona que se encarga de la extracción de las bolas).\n   Al completar una linea horizontal en un carton, el jugador debera cantar (LINEA).\n   Cuando un jugador consigue tachar todos los numeros de su carton,\n   tendra que gritar (BINGO) y se convertira en el ganador de la partida.\n");
           getchar();
           opcion=abrirMenu();
        }while(opcion == 2);
     }
//-------------AQUI EMPIEZA EL JUEGO
//PIDE NOMBRE Y NUMERO DE CARTONES
    if(opcion == 1){
       clrscr(); 
       printf("\n-------------------------------------------------------------+\n");
       printf("oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   |\n`888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  |\n 888     888  888   8 `88b.    8  888           888      888 |\n 888oooo888'  888   8   `88b.  8  888           888      888 |\n 888    `88b  888   8     `88b.8  888     ooooo 888      888 |\n 888    .88P  888   8       `888  `88.    .88'  `88b    d88' |\no888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  |");
       printf("\n-------------------------------------------------------------+\n\n");
       printf("\nIntroduzca su nombre: ");
       scanf("%s",&nombre);
       fflush(stdin);
       do{
          printf("\nCon cuantos cartones quieres jugar?[1-4]: ");
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
       printf("\nEl juego comenzara enseguida...");
       clrscr();
       do{
          printf("\n-------------------------------------------------------------+\n");
          printf("oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   |\n`888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  |\n 888     888  888   8 `88b.    8  888           888      888 |\n 888oooo888'  888   8   `88b.  8  888           888      888 |\n 888    `88b  888   8     `88b.8  888     ooooo 888      888 |\n 888    .88P  888   8       `888  `88.    .88'  `88b    d88' |\no888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  |");
          printf("\n-------------------------------------------------------------+\n\n");
       
       //colorear numero y si ya ha salido repite
          cont=0;
          do{
             srand(time(NULL));
             numeroCantado=rand()%89+1;
             confirmados[numeroCantado-1]=numeroCantado;
             for(cont=0;cont<89;cont++){
                 if(confirmados[cont] == numeroCantado){
                    existe=true;
                 }else{
                       existe=false;
                       }
             }
          }while(existe == true);
          
       //mostrar bombo
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
       //CANTAR NUMERO
          println(); println(); printf("EL NUMERO %2d", numeroCantado); println();
       //MOSTRAR CARTON
       switch (cuantosCartones){
              case 1: 
                   mostrarCarton(carton,cartonVerde,numeroCantado);
                   break;
              case 2: 
                   mostrarCarton(carton,cartonVerde,numeroCantado);
                   mostrarCarton(carton2,cartonVerde2,numeroCantado);
                   break;
              case 3: 
                   mostrarCarton(carton,cartonVerde,numeroCantado);
                   mostrarCarton(carton2,cartonVerde2,numeroCantado);
                   mostrarCarton(carton3,cartonVerde3,numeroCantado);
                   break;
              case 4: 
                   mostrarCarton(carton,cartonVerde,numeroCantado);
                   mostrarCarton(carton2,cartonVerde2,numeroCantado);
                   mostrarCarton(carton3,cartonVerde3,numeroCantado);
                   mostrarCarton(carton4,cartonVerde4,numeroCantado);
                   break;
       }
          
       
       getchar();
       contBucle++;
       if(contBucle == 99){
          break;
       }
       clrscr();
       }while(contBucle<=99);
    } 
         
    if(opcion == 3){
       clrscr();
       printf("\n-------------------------------------------------------------+\n");
       printf("oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   |\n`888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  |\n 888     888  888   8 `88b.    8  888           888      888 |\n 888oooo888'  888   8   `88b.  8  888           888      888 |\n 888    `88b  888   8     `88b.8  888     ooooo 888      888 |\n 888    .88P  888   8       `888  `88.    .88'  `88b    d88' |\no888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  |");
       printf("\n-------------------------------------------------------------+\n\n");
       printf("            GRACIAS POR JUGAR AL BINGO DE APPSMATU!\n\n                       VUELVA PRONTO!\n");
       Sleep(3000);
       system("exit");
    }
}
