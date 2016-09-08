#include <EEPROM.h>

/****************************************************************
*(ELC103)TOPICOS AVANZADOS DE PROGRAMACION ALGORITMOS GENERICOS *
*****************************************************************/
#include <Servo.h>//Libreria para usar los servo-motores
#include <Wire.h>   
unsigned int _ABVAR_1_distancia = 0 ;   



Servo servo_der; //Servo derecho  -PIN 8-ADELANTE 180 - ATRAS   0
Servo servo_izq; //Servo izquierdo-PIN 9-ADELANTE   0 - ATRAS 180

//Constantes de movimientos de los servo-motores
const int SD_ADELANTE = 180;//***Velocidad en intervalo de*******
const int SD_ATRAS    =   80;//*************0 - 180***************
const int SI_ADELANTE =   80;//*Donde:****************************  
const int SI_ATRAS    = 180;//*(0)  vel máx sentido antihorario.*
const int S_QUIETO    =  90;//*(180)vel máx sentido horario.*****
const int VEL         =  60;//*(90) sin movimiento.**************
boolean DIS=false;
boolean CONNECT =false;
char   dato='x';
  
  
  
////////////////////////////////////////////////////////////////////////////////////////////////
// Función encargada de hacer la lectura de la distancia
////////////////////////////////////////////////////////////////////////////////////////////////
int readDistance()
{
int c;                                                               //Variable para guardar la distancia
Wire.requestFrom( 2 , 1 );                    //  Se hace el requerimiento del dispositivo con la dirección ’2′.
//  donde el tamaño de información requerida sera de ’1 BYTE’.
//  Por lo tanto la dirección del modulo Ultrasonico es 2.

while( Wire.available() )                     //  Verificamos si llego información por el puerto I2c.
{
c = Wire.read();                                   //  Entonces mientras nos llegue un valor de distancia lo
//  guardamos en c.
}
return c;                                                 //  Retornamos el valor de la distancia actual a la función principal.
}

void setup()
{
  //Pin donde conectamos el led para ver el correcto funcionamiento del modulo
   pinMode(13,OUTPUT);
   //Configuracion de la velocidad del modulo 9600 por defecto, se puede cambiar
   //mediante comandos AT
   Serial1.begin(9600);
   Serial.begin(9600);
   Wire.begin();                                  // Se inicializa la librería de funciones para la comunicación I2C.
}
  
void loop()
{
    _ABVAR_1_distancia =  readDistance()  ;  // Medimos la distancia
     Serial.print("distancia" );
       Serial.println( _ABVAR_1_distancia);
  //  Serial.print(_ABVAR_1_distancia);
 
   //Mientras el puerto serie del modulo bluetooth esta disponible
   
   if (( ( ( _ABVAR_1_distancia ) <= ( 7 ) ) && ( ( _ABVAR_1_distancia ) > ( 1 ) ) )){
   servo_izq.write(90);
   servo_der.write(90);
   servo_izq.detach();
   servo_der.detach();
   DIS=true;
 }
 else
 {   
    if(DIS==true){
   while (Serial1.available())
   {
      //Guardamos en la variable dato el valor leido por el modulo bluetooth
        dato= Serial1.read();
       //Comprobamos el dato
      
       switch(dato)
       {
         // Mueve hacia Arriba
         case '0':
         {
             servo_der.attach(8);
             servo_izq.attach(9);
             servo_izq.write(65.77);
             servo_der.write(180);  
             delay(100);  
             dato=10; 
           break;
         }
        
         case '1':
         {
           //ATRAS
            servo_der.attach(8);
            servo_izq.attach(9);
            servo_izq.write(180);
            servo_der.write(0);  
            delay(100);
            dato=10;
           break;
         }
          case '2':
         {
           //DERECHA
             servo_der.attach(8);
             servo_izq.attach(9);
             servo_izq.write(0);
             servo_der.write(0);  
             delay(100); 
             dato=10;
           break;
         }
          case '3':
         {
            //IZQUIERDA
             servo_der.attach(8);
             servo_izq.attach(9);
             servo_izq.write(180); //85
             servo_der.write(180);  
             delay(100);
             dato=10;
            // mover(SI_ATRAS,SD_ADELANTE,2,2);  
           break;
         }
        // Se detiene
         case '4':
         {
            servo_izq.detach();
            servo_der.detach();
            dato=10;
            break;
         }
         
          // Busca Alternativas
         case '5':
         {
            servo_izq.detach();
            servo_der.detach();
            dato=10;
            break;
         }
         
         case '6':
         {
           //DERECHA
             servo_der.attach(8);
             servo_izq.attach(9);
             servo_izq.write(0);
             servo_der.write(95);  
             delay(100); 
             dato=10;
           break;
         }
          case '7':
         {
            //IZQUIERDA
             servo_der.attach(8);
             servo_izq.attach(9);
             servo_izq.write(81); //85
             servo_der.write(180);  
             delay(100);
            dato=10; 
           break;
         }
    //     DIS=false;
       }   
       } 
   }else{
      while(Serial1.available() && DIS==false){
       dato= Serial1.read();
       servo_der.attach(8);
       servo_izq.attach(9);
       servo_izq.write(65.77);
       servo_der.write(180);  
       delay(100);       
       }
 }
}
}

void mover(int movSI, int movSD, long tMove, long tWait)
{
 
   servo_der.attach(8);
  servo_izq.attach(9);
  servo_izq.write(movSI);
  servo_der.write(movSD);  
  delay(tMove * 50);
}
