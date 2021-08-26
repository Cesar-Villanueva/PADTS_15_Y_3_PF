# Proyecto Final RTOS PADTS 3 y 15 (Armenta y Villanueva)
                     
                     ­ Descripción general ­
El codigo fue generado con la herramienta MCUxpreso IDE v.11.3.1 para la tarjeta de desarrollo Freedoom Development Board K64 kinetis. 
El programa en general es un relog digital , el cual se le puede programar una alarma , este reloj será mostrado por medio de una pantalla LCD Nokia 5110.
El objetivo principal de este codigo es utilizar FreeRTOS para generar el funionamineto del reloj digital por medio de tareas con diferentes prioridades , ya que es un sistema operetivo en tiempo real (RTOS). El programa esta diseñado para NO utilizar ninguna función bloqueante (NonBlocking) y asi poder siempre estar ejecutando las tareas que sean requeridas.

                     ­  Conexiones Fisicas ­
                     
![Schematic RTOS Armenta   Villanueva](https://user-images.githubusercontent.com/78750676/131023909-1952f561-399b-4331-a811-ded4e411bbc6.jpg)


# Explicación del Codigo 

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

Como todo programa en un inicio se mandan a llamar las librerías que sean necesarias, para este proyecto se mandan a llamar las librerías  , como estamos en un archivo header file , primero se tiene que codificar las macros para que el proyecto completo reconozca la librería , después se inicializan todas las librerías relacionadas con la tecnología de ARM y de la propia tarjeta. Estas librerías son las que cualquier ejemplo del SDK ensambla en un proyecto por defecto en la herramienta MCUxpresso.   

•	_De la línea 22 a la línea 27_ 

En la línea 22 se manda a llamar a la librería FreeRTOS , ya que este proyecto es implementado un sistema operativo en tiempo real esta es la librería más importante. En las líneas siguientes se declaran librerías que complementan a FreeRTOS para utilizar tarea , semáforos , colas  y eventos. En la línea 27 se declara una librería que se llama nokiaLCD , esta librería contiene todas las funciones que se pueden utilizar en la LCD , y el método de transmisión es por SPI NonBlocking , estas librerías son personalizadas. 

•	_De la línea 31 a la línea 44_ 

En este fragmento de código se define todas mas macros que utilizan en este Header file tanto como en el archivo main , En la línea 31 se define el tamaño del Stack que tendrán las tareas cuando esta se crean, de la línea 32 a la 34 se defiene los valores de la alarma del reloj, de la línea 35 a la 37 se define los valores de set del reloj estos valores son usados para mostrara el reloj en un inicio en cierta hora específica, de la línea 38  a la 40 se definen 3 mascaras de 3 bits diferentes , cada bit corresponde a una bandera de cada tarea especifica , estas macros sirven para la recepción del event group de la alarma , de la línea 41 a la 43 se definen los valores máximos de conteo para los contadores internos de las tareas para simular los segundos , minutos y horas y por último se define el valor del tamaño de la Queue. 

•	_De la línea 46 a la 55_ 

Se inician 2 arreglos con valores en hexadecimal , estos 2 arreglos son imágenes de 84x48 pixeles que servirán como un marco para la pantalla y el reloj se vean más formal y presentable. Estos arreglos se declaran como constantes para que no ocupe memoria RAM.  (Se puede utilizar cualquier marco, es dado caso de no querer marco ir a comentar la línea 319). 



•	_De la línea 65 a la línea 84_ 

Se define una estructura con un typedef, esta estatura tiene un identificador llamado Init , este tipo de estructura se declaro en el main , aquí se explicará el porqué de cada miembro de esta estructura. 
Esta estructura se hizo con el fin de que, al momento de crear las tareas , se puedera pasar una referencia única de tamaño de 32 bits de palabra (Que es el que maneja este microcontrolador) y no pasar una copia de todos los datos. 
De la línea 67 a la 69 se declaran 3 variables de tipo entero sin signo de 8 bits , este tipo de variables son reconocidas en la librería #include <stdint.h> y esta librería viene incluida una la librería en el proyecto y no se tiene que volver a declarar. Estas 3 variables servirán para poner un valor de set de la alarma , en este caso se le paso una macro en el main. De la línea 72 a la línea 74  se declaran 3 variables tipo entero sin signo de 8 bits, estas 3 variables serán utilizadas para le set de la hora en  la que tiene que empezar el reloj, en la línea 77 se y clara una variable de tipo event group handle  para poder utilizar un grupo de eventos y en las líneas  80 y 81 se declaran 2 variables de tipo semaphore handle que servirán para poder crear y utilizar los semáforos. 

•	_De la línea 85 a la línea 99_ 

De la línea 85 a la 89 de declara un tipo enumerado para contar con 3 identificadores que servirán para la estructura de tipo time_msg_t declarada de la línea 91 a la 94 , esta estructura servirá para poder pasar la información en una Queue donde necesitaremos un identificador y el valor, es por eso por lo que en la estructura se declara una variable de tipo enumerado y una variable de tipo entero sin signo de 8 bits. Despues de la línea 96 a la 99 se declara una estructura que se llamará Int_to_char esta estructura tendrá declarado 2 variables de tipo entero sin signo de 8 bits que serán las unidades y las decenas , esta estructura nos servirá al momento de imprimir valores en la pantalla. 

•	_De la línea 101 a la 104_ 

En la línea 101 se declara una variable de tipo Queue Handle para crear una Queue , esta Queue tiene el nombre de mailbox , esta Queue ya fue creada en el main. En las siguientes líneas se declaran 2 variables de tipo semaphore handle con los nombres de mutex y LCD , estas 2 variables ya fueron utilizadas en el main , la de LCD es un semáforo binario y la de mutex es un Mutex. 

•	_Funciones_

------------------------------------------------------

_Int_to_char_

Solo creo una función en este programa, esta función se utiliza de la siguiente manera , la función pide como argumento un entero sin signo de 8 bits y retorno una estructura de tipo Int_to_Char de la línea de condigo 96, ahora apuntando a la línea 344 podemos ver que se empieza por inicializar una estructura llamada LCD y después de la línea 348  a la 371 se encuentran varias condicionales que lo que van a hacer esta estar preguntando en que rango de valores se encuentra el numero de entrada , y dependiendo del valor de entrada se le asignaran valores a la estructura en la variable de unidades y de decenas , que pasa el fragmento de las condicionales retornara como valor la estructura creada  pero ya con valores establecidos para poder acceder a ellos. Teniendo en cuenta que los valores que regresa son valores que en hexadecimal corresponde a un número en código ASIC .  Esta función está personalizada a este programa y se puede sustituir por cualquier otra siempre y cuando se respete la lógica de las tareas que ocupan esta función. 

------------------------------------------------------

•	_Funcionalidad de las tareas (Task)_

# Simon 

_seconds_task_
  






                   
 
 
