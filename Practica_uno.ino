/*
 * Autor: Reyes Solis Miguel Angel 
 * Programa: Sistema alertizador salvaguarda humano-coche
 * Objetivo: Realizar un sistema que simule un Semáforo Interactivo usando Arduino. 
 *           Este debe mostrar un conjunto de semáforos que cambiarán de verde a ámbar a rojo, y viceversa, 
 *           luego de un período de tiempo establecido, utilizando el sistema de cuatro estados de los semáforos en México. 
 *           Este se extiende para incluir un conjunto de luces y un botón peatonal para solicitar cruzar la calle.
 *           Cuando llega el peatón y se dispone a cruzar pulsa el botón que encuentra en la parte baja del semáforo, este reconoce 
 *           la orden y cierra el paso de los vehículos para que el viandante pueda cruzar con seguridad hasta el otro lado de la calle. 
 *           Una vez que se acaba el tiempo estipulado para que el peatón cruce, ese semáforo permanecerá abierto 
 *           para mejorar la movilidad de los vehículos.
 *           El sistema deberá de contener una perilla para controlar el tiempo mínimo en que el semáforo vehicular va a durar en verde.
 *           
 *           Como funcionalidad extra, el semaforo peatonal cumplira la funcion de sonaruna alarma que permita avisar a los invidentes 
 *           cuando el paso este en verde.
*/


#define led_sem_v 13 // Definicion del pin de entrada digital a utilizar para el foco verde del semaforo vehicular
#define led_sem_a 12 // Definicion del pin de entrada digital a utilizar para el foco amarillo del semaforo vehicular
#define led_sem_r 11 // Definicion del pin de entrada digital a utilizar para el foco rojo del semaforo vehicular
#define led_p_v 7    // Definicion del pin de entrada digital a utilizar para el foco verde del semaforo peatonal
#define led_p_r 6    // Definicion del pin de entrada digital a utilizar para el foco rojo del semaforo peatonal
#define boton 3      // Definicion del pin de entrada digital a utilizar para el boton que pedira la peticion de cruce
#define pot 0        // Definicion del pin de entrada analogica a utilizar para el potenciometro que manipulara la duracion del foco verde del semaforo vehicular
#define alarma 8     // DEfinicion del pin de entrada digital a utilizar para la alarma que sonara mientras el paso del peaton este en verde    
int duracion = 0;    // Definicion de la variable que estipula ael tiempo maximo de duracion que tendra el foco verde del semaforo vehicular
int tiempo_transcurrido = 0; // Definicion de la variable que guarda el tiempo que ha trancurrido desde que se encendio el foco verde del semaforo vehicular 

void setup() {
    
    Serial.begin(9600);
  // Asignacion de pines de entrada y salida digitales
    pinMode(led_sem_v, OUTPUT);
    pinMode(led_sem_a, OUTPUT);
    pinMode(led_sem_r, OUTPUT);
        
    pinMode(led_p_v, OUTPUT);
    pinMode(led_p_r, OUTPUT);

    pinMode(alarma, OUTPUT);
    
    pinMode(boton, INPUT);
    
  // El estado inicial del semaforo es con el paso vehicular
    digitalWrite(led_sem_v, HIGH);
    digitalWrite(led_sem_a, LOW);
    digitalWrite(led_sem_r, LOW);
    digitalWrite(led_p_v, LOW);
    digitalWrite(led_p_r, HIGH);
    digitalWrite(alarma, HIGH);
}

void loop() {
  // Lectura del potenciometro para saber cuato tiempo durara el foco verder del semaforo vehicular encendido
  // El valor minimo encendidoson 5 segundos y el maximo son 10
 duracion = (analogRead (pot)*10)+10000;
 Serial.println(duracion);

      // Miestras el boton no este presionado y su tiempo de encendido transcurrido sea menor al que debe durar entonces que siga encendido
      while(digitalRead(boton) != LOW && tiempo_transcurrido <= duracion){
        tiempo_transcurrido += 10;  
        delay(10);
        
        }
      // Si se presiono el boton o termino su tiempo de duracion entonces que empiece a parpadear
      digitalWrite(led_sem_v, LOW);
     
      tiempo_transcurrido = 0;
        for(int i = 0; i <= 3; i++){
            delay(500);
            digitalWrite(led_sem_v, HIGH);
            delay(500);
            digitalWrite(led_sem_v, LOW);
                        
          }
      // Cambio de estado verde del semaforo a ambar con una duracion de un segundo
        digitalWrite(led_sem_a, HIGH);     
        delay(1000);
      // Cambio de estado de ambar a rojo y encendido del foco verde del semaforo peatonal con una duracion de 5 segundos asi como el sonado de la alarma para invidentes
        digitalWrite(led_sem_a, LOW);
        digitalWrite(led_sem_r, HIGH);
        digitalWrite(led_p_r, LOW);
        digitalWrite(led_p_v, HIGH);
        digitalWrite(alarma, LOW);
        delay(10000);
      // Una vez terminado el tiempo de cruce peatonal que regrese al paso vehicular
        digitalWrite(led_sem_r, LOW);
        digitalWrite(led_sem_v, HIGH);
        digitalWrite(led_p_v, LOW);
        digitalWrite(led_p_r, HIGH);
        digitalWrite(alarma, HIGH);
            
}
