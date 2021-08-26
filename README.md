# Proyecto Final RTOS PADTS 3 y 15 (Armenta y Villanueva)
                     
                     ­ Descripción general ­
El codigo fue generado con la herramienta MCUxpreso IDE v.11.3.1 para la tarjeta de desarrollo Freedoom Development Board K64 kinetis. 
El programa en general es un relog digital , el cual se le puede programar una alarma , este reloj será mostrado por medio de una pantalla LCD Nokia 5110.
El objetivo principal de este codigo es utilizar FreeRTOS para generar el funionamineto del reloj digital por medio de tareas con diferentes prioridades , ya que es un sistema operetivo en tiempo real (RTOS). El programa esta diseñado para NO utilizar ninguna función bloqueante (NonBlocking) y asi poder siempre estar ejecutando las tareas que sean requeridas. 

                     ­  main.c ­

En este archivo se encontrará la inicialización del programa principal, donde se mandarán a llamar las librerias necesarias ,creaciones de tareas y variables requeridas.

Como primera línea de código se manda a llamar una sola librería llamada “Proyecto_Final_RTOS.h” donde este archivo header contiene todo lo necesario para trabajar en el main. 
Después se inicia la función main donde codificaremos todo lo necesario para que el reloj digital funcione. 

•	De la línea 13 a la 19 

Se mandan a llamar funciones de inicialización de los pines, el Clock , los periféricos y de la línea 16 a la 19 si el programa esta em modo debug se inicializa el debug de consola y estos se logra con una macro ifndef y enif. Todas estas funciones son para el inicializar hardware de la tarjeta de desarrollo.

•	De la línea 22 a la 29 

Se crea una estructura estática del tipo Init , esta estructura está declarada en el header, la estructura lleva como nombre Init_Config , donde esta estructura llevara cierto número de variables que nos ayudarán a inicializar el sistema y a el propio funcionamiento de esté. De la línea 26 a la 28 se inicializan 3 parámetros de la estructura que para este caso es la hora en que se desea que la alarma pase. Estos valores están definidos por macros que se encuentra en el header al igual que la estructura.      
   



                     ­PROYECTO_FINAL_RTOS.h ­
                     
En este archivo se encuentra toda la funcionalidad del reloj digital , apoyandonos de otros headers files para su correcto funcionamiento. 






                   
 
 
