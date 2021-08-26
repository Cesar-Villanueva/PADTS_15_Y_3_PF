# Proyecto Final RTOS PADTS 3 y 15 (Armenta y Villanueva)
                     
                     ­ Descripción general ­
El codigo fue generado con la herramienta MCUxpreso IDE v.11.3.1 para la tarjeta de desarrollo Freedoom Development Board K64 kinetis. 
El programa en general es un relog digital , el cual se le puede programar una alarma , este reloj será mostrado por medio de una pantalla LCD Nokia 5110.
El objetivo principal de este codigo es utilizar FreeRTOS para generar el funionamineto del reloj digital por medio de tareas con diferentes prioridades , ya que es un sistema operetivo en tiempo real (RTOS). El programa esta diseñado para NO utilizar ninguna función bloqueante (NonBlocking) y asi poder siempre estar ejecutando las tareas que sean requeridas. 

                     ­  main.c ­

Como primera línea de código se manda a llamar una sola librería llamada “Proyecto_Final_RTOS.h” donde este archivo header contiene todo lo necesario para trabajar en el main. 
Después se inicia la función main donde codificaremos todo lo necesario para que el reloj digital funcione. 

_•	De la línea 13 a la 19_ 

Se mandan a llamar funciones de inicialización de los pines, el Clock , los periféricos y de la línea 16 a la 19 si el programa esta em modo debug se inicializa el debug de consola y estos se logra con una macro ifndef y enif. Todas estas funciones son para el inicializar hardware de la tarjeta de desarrollo.

_•	De la línea 22 a la 29_ 

Se crea una estructura estática del tipo Init , esta estructura está declarada en el header, la estructura lleva como nombre Init_Config , donde esta estructura llevara cierto número de variables que nos ayudarán a inicializar el sistema y a el propio funcionamiento de esté. De la línea 26 a la 28 se inicializan 3 parámetros de la estructura que para este caso es la hora en que se desea que la alarma pase. Estos valores están definidos por macros que se encuentra en el header al igual que la estructura.
      
_•	De la línea 31 a la 33_ 

Se inicializan 3 parámetros de la estructura   estos 3 parámetros son para poner una hora fija al reloj cuando comience el programa y el sistema completo, estos valores están definidos por macros que se encuentran en el archivo header. 

_•	Línea 38_

Se inicia un parámetro de la estructura y ese parámetro esta igualado a la creación de un event group 

_•	De la línea  40 a la 45_

Se iguala una variable llamada LCD a la creación de  un semáforo binario y en la siguiente línea se da este semáforo, esta variable LCD está declarada en el header. Después se inician 2 parámetros de la estructura , estos 2 parámetros se igualan a la creación de 2 semáforos binarios . 

_•	De la línea 48 a la 52_ 

De la línea 48 a la 48 se crea una Queue que esta igualada a una variable mailbox , esta variable  es de tipo Queue y está declarada en el header. Despues se registra la Queue para poder visualizarla en modo debug en el apartado de Task_FreeRTOS.  Y despues se una variable llamada mutex a la creación de un MUTEX , esta variable mutex es de tipo semáforo y esta declarada en el header. 

_•	De la línea 58 a la 63_

En esta parte de código es donde se crean todas las tareas que tendremos en el sistema. Toda la funcionalidad de la tarea se encuentra en el archivo header. En ese apartado del archivo se explicara a detalla porque las prioridades asignadas así como el usos de la estructura que se ha estado declarando hasta el momento. 
La primera tarea creada es una tarea llamda seconds_task y tendrá como nombre identificador Function seconds , tendrá un Stack con el valor de una macro que esta declarada en el header, se le pasará como parámetros la estructura antes creada , las prioridad de esta tarea es igual a 2 y por ultimo se le pasa un valor Null al ultimo parametro.   Al igual función minutes_task , hours_task , alarm_task, y LCD_init , se les pasa los mismos parámetros , Stack y el Null , con la diferencia que tienen identificadores de nombres diferentes y el numero de prioridad , donde minutes_task tiene prioridad de 3 , hours_task tiene prioridad de 4 , alarm_task tiene prioridad de 1, y LCD_init tiene la prioridad mas alta , y por ultimo tenemos la tarea print_task que igual en diferencia de las demás , esta no recibe ningún parámetro, y su prioridad es de 1. 
    
   




                     ­PROYECTO_FINAL_RTOS.h ­
                     
En este archivo se encuentra toda la funcionalidad del reloj digital , apoyandonos de otros headers files para su correcto funcionamiento. 






                   
 
 
