#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>

void clrscr(){
    system("@cls||clear");
}

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
//---------------------------MENU PRINCIPAL-------------------------------------
int abrirMenu(){
    int opcion;
     do{
     clrscr();
     printf("\n-------------------------------------------------------------+\n");
     printf("oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   |\n`888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  |\n 888     888  888   8 `88b.    8  888           888      888 |\n 888oooo888'  888   8   `88b.  8  888           888      888 |\n 888    `88b  888   8     `88b.8  888     ooooo 888      888 |\n 888    .88P  888   8       `888  `88.    .88'  `88b    d88' |\no888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  |");
     printf("\n-------------------------------------------------------------+\n");
     printf("                    GAME MASTER EDITION\n");
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
    FILE *numBombo;
    bool existe;
    int opcion=0;
    char nombre[20];
    int confirmados[89];
    int bombo[89];
    int i, j, cont, numeroCantado, comprobar,bucle;
    //----------PANTALLA DE INICIO
    Sleep(500);
    printf("\n                                                           .-:::::--.``                              \n                                                      `:+soo++//:--....```                          \n                                ``..-:-:::---.`     .::--.`  `.---.```   ```         ``             \n            ````...`        `..---::://+++oossso+:..:+sssoo+-`   ```       ``    `````.---.`        \n           ```.--:/+++:. `........---:://++ooo+++oosy/.``.:/+/-`   `             ```````..-::.      \n            ``..-:/+oo+:..``   ``...--:://:-`     ``.:/-    `:/:.   ```             ``.--::-.--`    \n   ```      ``.--:/++/-.`        ``..---.`   .-/+ooo+:-.-.`   -:-.```...`````     ````````.-::..`   \n  `-.      `..--:/+/:-.`          ``...   `-/osssyyyyyys/-:/```````............````         `.::.`  \n `:-`    ..---::/+/:-.`           `.`   `-/+ooo+:.```.-/os+-`   ````............-.` ``.`  -::/.-/.  \n -+.``  ...--:/+++/:-`         `````   .:/++/-`         `./s-    ````...........-----:/- ./:`:/`/:  \n /+``   ````````/+/-`        ```..`   -:///-`            `..o:    ``............------/:``:+/++-:/  \n //  `.-++++++/:++/````    `.....`  `-//+/`     ````    -ss-`o- ```.............-------/../+::o+//  \n .-./++/:::://+ooo-````````-----.   ://+/`   .:+ossso:`-yyys`.o`...............--------:/:oo/+s+o-  \n  ./o/.``     `+so.```````-////-   :++++`    +yso++syy+.o:oy-`o...............----------::/+oo+o/   \n   .o-.:::..---oso````````/++++.  `+ooo:     .-````.yyy..`/y+.+-......................--//++oss/    \n    .:/s+/::///syo.```````+ooo+   :ooss`     ``````-yys...:y+.+-...........``          `:ssys+.     \n      .:++oo//+sys.....--:osss/   +ssss  `````````-syy:..-:y+-o........`     ``...-----``oo:.       \n         .-://++yy//+ossyyysss/   +yyyy`````````.+yys:----/y///.....`    `..-------::/++.`          \n                :yyyyyyyyyyyyyo   /yyyy:`````.-/syy+:://::oo+o---.`   `.------..````.-os:           \n                 +yyyyyyyyyyyyy.``.syyys.`...+syyyyyyyy+///+s:--.`  `.----.``     ````.s`           \n                  +yyyyyyyyyyyy+```:yyyyo-..:sssoooo++++/:+s/---   .----.` ```..-:/o.`:`            \n                   :yyyyyyyyyyyy/``.:syyys/--::::///++++/ss:---`  .---.`````./+oooo/..`             \n                    .+yyyyyyyyyyy+-..-oyyyys+////++oo++sy+:::::.``:::-`.....+ss//---`               \n                      .+yyyyyyyyyyy+:--/oyyyyhyyyyyssyy:` .:///:../++----::oyyyys:`                 \n                        `:oyyyyyyyyyyo+///+ssyyyssss+-      `.:++::sy+:////++//-                    \n                           `:+oyyyyyyyyyssoooooo+/.             `.-.:/:----`                        \n                                .-:/+++++++/:-`                                                      \n");
    printf("\n");
    printf("                   oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   \n                   `888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  \n                    888     888  888   8 `88b.    8  888           888      888 \n                    888oooo888'  888   8   `88b.  8  888           888      888 \n                    888    `88b  888   8     `88b.8  888     ooooo 888      888 \n                    888    .88P  888   8       `888  `88.    .88'  `88b    d88' \n                   o888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  ");
    Sleep(2000);
    
do{   
    bucle=0;
    WORD Attributes = 0;
    llenarBombo(bombo);
    opcion=abrirMenu();
    //--------SE ABRE LA PANTALLA DE INSTRUCCIONES
    if(opcion == 2){
        do{
           instrucciones();
           opcion=abrirMenu();
        }while(opcion == 2);
     }

//-------------AQUI EMPIEZA EL JUEGO
    if(opcion == 1){
       clrscr();
       srand(time(NULL));
       printf("\n-------------------------------------------------------------+\n");
       printf("oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   |\n`888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  |\n 888     888  888   8 `88b.    8  888           888      888 |\n 888oooo888'  888   8   `88b.  8  888           888      888 |\n 888    `88b  888   8     `88b.8  888     ooooo 888      888 |\n 888    .88P  888   8       `888  `88.    .88'  `88b    d88' |\no888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  |");
       printf("\n-------------------------------------------------------------+\n");
       printf("                    GAME MASTER EDITION\n\n");
       for(cont=0;cont<90;cont++){
           Sleep(20);
           printf("%2d ",bombo[cont]);
           if(bombo[cont]%10 == 0){
                 println();
           }else;
       }
       Sleep(100);
       printf("\nPulse ENTER para comenzar la partida...");
       getchar();
       do{
          clrscr();
          numBombo=fopen("bombo.txt","w+");
          printf("\n-------------------------------------------------------------+\n");
          printf("oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   |\n`888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  |\n 888     888  888   8 `88b.    8  888           888      888 |\n 888oooo888'  888   8   `88b.  8  888           888      888 |\n 888    `88b  888   8     `88b.8  888     ooooo 888      888 |\n 888    .88P  888   8       `888  `88.    .88'  `88b    d88' |\no888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  |");
          printf("\n-------------------------------------------------------------+\n");
          printf("                    GAME MASTER EDITION\n\n");
       //GENERA UN NUMERO ALEATORIO MIENTRAS SEA REPETIDO Y LO GUARDA EN EL FICHERO
          cont=0;
          do{
             numeroCantado=rand()%89+1; 
             for(cont=0;cont<89;cont++){
                 if(confirmados[cont] == numeroCantado){
                    existe=true;
                    numeroCantado=rand()%89+1; 
                 }else{
                       existe=false;
                       break;
                       }
             }
          }while(existe == true);
          confirmados[numeroCantado-1]=numeroCantado;
          fprintf(numBombo,"%d",numeroCantado);
          fclose(numBombo);
       //MUESTRA EL BOMBO Y COLOREA LOS NUMEROS QUE YA HAN SALIDO
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
       //PRINTEA EL NUMERO CANTADO
          println(); println(); printf("EL NUMERO %2d", numeroCantado); println();
       
          FILE *ganador;
          if(ganador=fopen("bingo.txt","rb")){
             fgets(nombre,20,ganador);
             printf("%s TIENE BINGO!",nombre);
             fclose(ganador);
             remove("bingo.txt");
             remove("bombo.txt");
             break;
          }else;
       
       getchar();
       clrscr();
       bucle++;
       }while(bucle<300);
    
       printf("\nFin de la partida!\nPulse enter para volver al menu...");
       getchar();
    }
     
     //PANTALLA DE CIERRE TEMPORIZADO Y DESPEDIDA 
     if(opcion == 3){
       clrscr();
       printf("\n-------------------------------------------------------------+\n");
       printf("oooooooooo.  ooooo ooooo      ooo   .oooooo.      .oooooo.   |\n`888'   `Y8b `888' `888b.     `8'  d8P'  `Y8b    d8P'  `Y8b  |\n 888     888  888   8 `88b.    8  888           888      888 |\n 888oooo888'  888   8   `88b.  8  888           888      888 |\n 888    `88b  888   8     `88b.8  888     ooooo 888      888 |\n 888    .88P  888   8       `888  `88.    .88'  `88b    d88' |\no888bood8P'  o888o o8o        `8   `Y8bood8P'    `Y8bood8P'  |");
       printf("\n-------------------------------------------------------------+\n");
       printf("            GRACIAS POR JUGAR AL BINGO DE APPSMATU!\n\n                       VUELVA PRONTO!\n");
       Sleep(3000);
       system("exit");
       break;
     } 
}while(opcion !=3);
}
