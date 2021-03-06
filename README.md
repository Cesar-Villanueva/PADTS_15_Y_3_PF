# Proyecto Final RTOS PADTS 3 y 15 (Armenta y Villanueva)

Este codigo es el proyecto final de la materia de ___RTOS para microcontroladores___ en el diplomado de __Sistemas Electrónicos__ impartido por el __Cinvestav Unidad Guadalajara__ y el __IECA__.  

## _Resumen_ 

Se codifico un programa para hacer la funcionalidad de un reloj digital con FreeRTOS mostrando el reloj en una pantalla LCD. 

## Tabla de contenido 

* [Generalidades](#Introducción)
* [Explicación del Codigo](#Descripción )
    * [Main File](#Main)
    * [Header File](#Header)
      * [Funciones](#Funciones)
      * [Tasks](#Tasks)
      * [¿Como funciona ?](#Example)
* [Resultados](#Resultados)





# Generalidades 
## Introducción
                     
                     ­ Descripción general ­
El codigo fue generado con la herramienta MCUxpreso IDE v.11.3.1 para la tarjeta de desarrollo Freedoom Development Board K64 kinetis. 
El programa en general es un relog digital , el cual se le puede programar una alarma , este reloj será mostrado por medio de una pantalla LCD Nokia 5110.
El objetivo principal de este codigo es utilizar FreeRTOS para generar el funionamineto del reloj digital por medio de tareas con diferentes prioridades , ya que es un sistema operetivo en tiempo real (RTOS). El programa esta diseñado para NO utilizar ninguna función bloqueante (NonBlocking) y asi poder siempre estar ejecutando las tareas que sean requeridas.

                     ­  Conexiones Fisicas ­
                     
![Schematic RTOS Armenta   Villanueva](https://user-images.githubusercontent.com/78750676/131023909-1952f561-399b-4331-a811-ded4e411bbc6.jpg)

                     ­  Diagrama de flujo propuesto ­
                     
![image](https://user-images.githubusercontent.com/78750676/131033808-fbea2066-dc73-45f9-850e-9b1e8dbb71d1.png)



# Descripción 

Se describira la funcionalidad de todo el codigo implementado

## Main 
 
                     ­ main.c ­

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
    
   

## Header 


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


### Funciones 

#### _Int_to_char_
------------------------------------------------------

Solo creo una función en este programa, esta función se utiliza de la siguiente manera , la función pide como argumento un entero sin signo de 8 bits y retorno una estructura de tipo Int_to_Char de la línea de condigo 96, ahora apuntando a la línea 344 podemos ver que se empieza por inicializar una estructura llamada LCD y después de la línea 348  a la 371 se encuentran varias condicionales que lo que van a hacer esta estar preguntando en que rango de valores se encuentra el numero de entrada , y dependiendo del valor de entrada se le asignaran valores a la estructura en la variable de unidades y de decenas , que pasa el fragmento de las condicionales retornara como valor la estructura creada  pero ya con valores establecidos para poder acceder a ellos. Teniendo en cuenta que los valores que regresa son valores que en hexadecimal corresponde a un número en código ASIC .  Esta función está personalizada a este programa y se puede sustituir por cualquier otra siempre y cuando se respete la lógica de las tareas que ocupan esta función. 

------------------------------------------------------

###  Tasks

#### _seconds_task_

------------------------------------------------------ 
Esta tarea llamada seconds_task será la tarea encargada de llevar el conteo en segundos del segundero del reloj digital, esto se logrará haciendo que la tarea dure exactamente 1 segundo en ejecutarse por completo. Esta función servirá como base de tiempo para todo el sistema , ya que esta función estará ligada a otras por medio de semáforos. Dicho lo anterior: 

•	_De la línea  129 a la 132_ 

Antes de entrar al ciclo de la tarea en la línea 129 se declara un puntero de una estructura tipo Init y se iguala esta declaración a un casteo de puntero de la estructura Init a los argumentos tipo void de entrada a la tarea , esto se hace para poder tener toda la configuración que se hizo en la main y tenerlos en el Stack de la tarea por medio de esta asignación. En la siguiente línea se declara una variable de tipo Tick Type y la llamamos xLastWaitTime , después se declara una variable constante de tipo Tick Type que se llama xDelay1s y se igualara a una función que nos convierte los milisegundos ingresados a Ticks del systick y de la línea 134 a la 135 se declaran 2 variables de tipo Time msg que si recordamos es una estructura que contiene un valor de tipo enumerado y un valor entero sin signo de 8 bits. Estas dos variables nos servirán para poder enviar un dato a la Queue mailbox creada en el main. Para este caso haremos una copia del dato y la enviaremos. 

•	_De la línea 137 a la línea 161 

Una vez que se declara todo lo inicial en la tarea , en la línea 137 entramos al ciclo for infinito de la tarea , una vez dentro del ciclo de la tarea es donde tendremos la funcionalidad , empezando, teniendo una validación en la línea 140, esta validación por medio de un if estará preguntando si el valor configurado para la alarma es igual al valor actual del del contador que es el segundero. Si esta condición es cierta se da un set del bit que le corresponde a los segundos , este set se hace por medio del evento group y se utiliza una mascara , esta mascara esta en una macro ya antes explicada.  Ahora bien, si la condicional no se cumple sigue la siguiente línea 143 donde el valor actual del segundo se le suma un 1 esto se hace desde la referencia que tenemos de la estructura inicial, pero en el Stack de la tarea , en pocas palabras tenemos una copia de la original la cual iremos modificando al paso del tiempo. Después Se le darán valores a la estructura de time msg , donde al parámetro time Type se le pasa un tipo enumerado que bien esta representado por el numero 0 y esto representa que es un dato de tipo segundos  y después se le pasa el valor a el parámetro value y se iguala al valor actual del segundo , entonces , se puede observar que esta estructura toma el tipo y el valor actual. después en la línea 146  se utilizará memoria dinámica liberando un espacio de memoria y asignándolo a la variable Send que es un puntero de una estructura , esto  de no hacerse con memoria dinámica podría perderse el valor actual mandado con la Queue , si se hace con memoria dinámica , se asegura que el valor es el enviado. Luego de liberar el espacio de memoria  en la línea 147 se tiene una condicional que estará preguntando si la macro SECONDS_MAX con un valor de 60 es igual al valor actual del segundero , si esta condición es cierta pasa lo siguiente, en la línea 149 el  segundero actual se iguala a cero , al parámetro de la estructura Time second en el value se iguala al valor del segundero actual , después el valor de la estructura de time second se iguala al puntero de estructura Send , esto para hacer una copia de los valores , este paso se puede quitar en futuros códigos , ya que no es necesario y se puede pasar la referencia directa siempre y cuando se haya liberado un espacio de memoria. Una ves que se hizo la copia a send , se manda estra estructura por medio de una Queue  y a la Queue que se manda el dato es la Queue mailbox antes declarada en el main y después se da un semáforo binario , este semáforo es el minutes semaphore . Si la condición de la línea 147 no se cumple , se iguala la estructura puntero Send a la estructura Time second y después se envía la estructura Send por medio de la Queue malibox. Por último, en la línea 161 se llama a una delay until , este delay lo que hace es asegurarse que la tarea dure 1 segundo exacto en toda su ejecución y requiero como parámetros la referencia de cuantos tick lleva la tarea y cuanto es el delay , en este caso el delay tienen que ser de 1 s. 

------------------------------------------------------ 

#### _minutes_task_

------------------------------------------------------

Esta tarea es parcialmente idéntica a la tarea de __seconds_task__ en cuestión a funcionalidad y tipos de variables , solo los nombres son diferentes para poder entender el contexto de la tarea , lo que lo diferencia es que en la línea 175 y 176 primero se limpia el bit del event group de segundos esto se hace por el que ese bit se va a estar en Set una gran cantidad de veces y solo nos importan una en especifico y en la siguiente línea se da un set al bit de ahora de los minutos , otra diferencia es la línea 178 donde va a tomar un semáforo , en este caso se quiere tomar el semáforo binario minutes_semaphore , este semáforo es el que va a darlo la tarea de segundos cada que se cumplan 60 segundos, si este semáforo no se puede tomar la tarea si blockeara por un tiempo infinito esperando hasta que alguien de ese semáforo y por ultimo esta tarea no se bloquea suspende en ningún momento , esto porque depende completamente de la tarea __seconds_task__ es por eso que al principio se dice que la tarea __seconds_task__ es la base de tiempo del sistema . 


------------------------------------------------------

#### _hours_task_

------------------------------------------------------

Esta tarea es parcialmente idéntica a la tarea de __minutes_task__ en cuestión a funcionalidad y tipos de variables , solo los nombres son diferentes para poder entender el contexto de la tarea , lo que lo diferencia es que en la línea 175 y 176 primero se limpia el bit del event group de minutos esto se hace por el que ese bit se va a estar en Set una gran cantidad de veces y solo nos importan una en específico y en la siguiente línea se da un set al bit de ahora de los horas , otra diferencia es la línea 178 donde va a tomar un semáforo , en este caso se quiere tomar el semáforo binario hours_semaphore , este semáforo es el que va a darlo la tarea de minutos cada que se cumplan 60 minutos , si este semáforo no se puede tomar la tarea si blockeara por un tiempo infinito esperando hasta que alguien de ese semáforo y por ultimo esta tarea no se bloquea suspende en ningún momento , esto porque depende completamente de la tarea __minutes_task__ .


------------------------------------------------------



#### _alarm_task_

------------------------------------------------------

•	_De la línea 236 a la 241_ 

Antes de entrar al ciclo de la tarea se tiene los siguiente, en la línea 236 se declará una variable de un puntero de tipo estructura Init y se iguala a un casteo de puntero estructura tipo Init del argumento de entrada tipo void de la tarea , esto se hace para tener esa copia de valores es el Stack de la tarea . En la línea 237 se declara una constante de tipo EvenBits_t y que se llama xBitsToWaitFor y esta variable estará igualadad a una compuerta OR de bitwise de 3 macros , que estas macros son las tres mascaras de bits que se dan al evento group en cada tarea correspondiente. Despues se declara una variable de tipo EventBits_t que se llamará xEventGroupValue, en la siguiente línea se declara una constante de tipo Tick Type y estará igualdad al numero de tick que son en 1 segundo como se hizo en la tarea uno al inicio.  Y por último  en la línea 240 y 241 se declaran 2 variables tipo char y se igualan a cadenas de caracteres , donde la primera en un mensaje que dice ALARM y el otro es una cadena con espacios del tamaño de ALARM. 

•	_De la línea 243 a la 266_

Si inicia el ciclo de la tarea , después se manda a llamar una variable xEventeGroupValue y se iguala a una función de xEvenetGruopWaitBits , esta función lo que hace es de un grupo de eventos dado , va a esperar ciertos bits o un solo bits seteados de ese grupo dado, entonces como primer argumento se da el grupo que se declaro en el main , y los bits que tiene son los que las tareas __seconds_task__ , __minutes_task__,  __hours_task__ dan como set , después se pasa la variable xBitsWaitFor que es la OR de las macros , esto significa que estamos diciendo que bits en mascaras estamos esperando , despues se pasa pdTRUE estos significa que cada que se cumpla esta función queremos que los bits se limpien , después se pasa pdTRUE esto significa que queremos esperar a todos los bits si fuera pdFALSE con que un bit este en 1 la función se da, para este caso queremos tener los 3 bits en 1 , y por ultimo si no se cumple esta función se bloquea la tarea hasta que estos 3 bits se den , si es el caso que se den, se pasa a la siguiente línea que es una condicional, que está preguntando si el retorno de la función es diferente de cero , ya que si se cumple esta función arroja cualquier valor excepto el cero, una vez que se cumple esta condición se pasa a la línea 246 donde se toma un semáforo , para este caso no se toma un semáforo binario , si no un mutex , recordando que el mutex lo pueden tomar y liberar la misma tarea , si este semáforo es disponible se toma y se pasa a la siguiente línea donde se mandaran a llamar funciones de la pantalla LCD Nokia 5110, donde de la línea 247 a la 250 lo que hará el LCD es prender el backligth imprimirá que la alarma ocurrió , actualizara la pantalla y se ira a un delay de 1ms , esto se repetirá otra 2 veces mas y por ultimo se limpia somo ese mensaje en especifico con el char de cadenas de espacios y se libera el mutex que se tomo al principio.   


------------------------------------------------------


#### _print_task_

------------------------------------------------------

Antes de entrar al ciclo de la tarea se declara una variable puntero estructura de tipo Time_msg_t que tendrá como nombre Recived y un variable de tipo estructura Int_to_char con el nombre Init. 

•	_De la línea 273 a la 303 

Estando dentro del ciclo de la tarea  en la línea 274 se manda a llamar una función para recibir una Queue la Queue que se va a recibir es  la mailbox creada en el main, si llegara  tener un dato esta mailbox se guardara en la variable Recived , recordando que los datos enviados en la mailbox son de tipo time_msg_t , si la mailbox esta vacía la tarea se bloqueara por un tiempo indefinido hasta que reciba algo el mailbox , si es el caso que reciba lago pasa a la siguiente línea en la cual se toma el mutex declarado en el main , si este está libre toma y sigue la ejecución y si alguien mas tomo el mutex la tarea se bloquea indefinidamente hasta que se libere el mutex , cuando este libre el mutex, pasa a la siguientes línea , en la línea 276 esta una condicional IF es está preguntando el parámetro de tipo de dato de la estructura que se recibió de la Queue mailbox es igual se un tipo enumerado, si esta condición se cumple para a la siguiente línea, donde se mostrarán los segundos en la pantalla en la LCD , en la línea 278 la estructura Init se iguala a el retorno de la función INT_CHAR  y como argumento de entrada es parámetro de valor de la estructura obtenida de la Queue mailbox , como esta función regresa una estructura con 2 valores en hexadecimal que son unidades y decenas , entonces de la línea 279 a la 281 se imprimirán las unidades y las decenas de los segundos y el e la línea 282 se libera el espacio de memoria del mensaje recibido. De la linea 284 a la 301 se repite lo anterior , pero para los minutos y horas si las condiciones se cumplen y por último en la línea 302 se libera el mutex tomado al principio de la tarea. 



------------------------------------------------------

## Example 


¿Pero qué es lo que pasa en ejecución  ?
Se mostrará un ejemplo y ser ira desglosando que es lo que está pasando en todo el sistema y porque se asignaron las prioridades en el archivo main de esa manera. 
Ahora bien, vamos a suponer lo siguiente 
•	Se pondrá el reloj inicialmente en 00:00:00
•	Y una alarma en 00:00:23 
•	Y todo lo demás se deja en default 

Una vez que se cargue el programa a la tarjeta se pone en RUN y pasa lo siguiente, recordando que las tareas se ejecutaran de la siguiente manera de acuerdo a las prioridades , desde la mas alta a la más baja:
•	Fuction LCD
•	Fuction Hours
•	Fuction Minutes 
•	Fuction Seconds 
•	Fuction Alarm 
•	Fuction print
Imagen 
Entonces se inicia el programa , todo el main se inicializa , se crean las tareas y se inicia el Scheduler. 

```
Primera tarea en ejecutarse es LCD_init 
```
Toma el semáforo binario dado en el main  e  inicializa toda la pantalla.

```
Segunda tarea en ejecutarse es  LCD_init 
```
Aunque parezca extraño , esta tarea una vez que se ejecuta , se vuelve a ejecutar , esto debido a que es ningún momento se bloquea y suspende , entonces siempre esta en estado ready , y aunque otras tareas también estén listas para ejecutarse , esta función tiene la prioridad mas alta , cuando se vuelve a ejecutar la función y llegar a la parte de tomar el semáforo binario , esta función se bloqueara , debido a que ya fue tomado una vez , y ninguna tarea ha dado un nuevo set a este semáforo, entonces esta tarea se bloquea en toda la ejecución restante , porque ninguna función pone en set este semáforo , esto se hizo con la intención , de no mandar a suspender la función por si se llegara a ampliar el código y se quieta volver a inicializar la pantalla solo se necesitaría dar un set al semáforo correspondiente . 
```
Tercera tarea en ejecutarse  puede ser minutes _task o hours_task
```
Puede ejecutarse cualquiera de la 2 porque tiene las mismas prioridades , vamos a suponer que se ejecuta hours_task, entonces, inicia los parámetros antes de entrar al ciclo de la tarea , entra al ciclo de la tarea , donde realiza la primera validación que será True , porque si se cumple el valor de la alarma con el valor actual de las horas 0=0, entonces limpia el bit de los minutos de evento group , que en un inicio está limpio , y da un set al bit de las horas del event group
__Bits del event group__ = [1,0,0]  
Después pasa a la siguiente línea donde quiere tomar un semáforo binario, que en este momento no se ha dado un set , entonces la tarea pasa a bloquearse esperando ese semáforo. 
 ```
Cuarta tarea en ejecutarse  es minutes _task 
```
Esta es la tarea que siguen en ejecutarse por la prioridad , entonces se inicializa todo lo necesario antes de entrar al ciclo de la tarea , entra al ciclo de la tarea y primer se verifica una condicional que pregunta si el valor de la alarma es igual al actual , lo cual es True , entonces se da un set del bit los minutes y se limpia el bit de los segundos que en un principio esta limpio todo esto del evento group que todos comparten porque es global la variable. 
__Bits del event group__ = [1,1,0]  
Después pasa a la siguiente línea donde quiere tomar un semáforo binario, que en este momento no se ha dado un set , entonces la tarea pasa a bloquearse esperando ese semáforo. 

```
Quinta tarea en ejecutarse  es seconds_task
```
Esta es la tarea que siguen en ejecutarse por la prioridad , entonces se inicializa todo lo necesario antes de entrar al ciclo de la tarea , entra al ciclo de la tarea y primer se verifica una condicional que pregunta si el valor de la alarma es igual al actual , lo cual es False porque 0 no es igual a 23  
__Bits del event group__ = [1,1,0]  
Después sigue ejecutándose donde se le hace una suma contador que, en el set de la hora actual , entonces tenemos que 0+1 es el valor actual del segundo. Este valor y el tipo de valor se le pasan a una estructura , se libera memoria para poder enviar la estructura con los datos de interés, despues se verifica una condicional que pregunta de  si 60 = 1 , donde esto es falso , en este caso pasa al else , donde en este se da el valor de la estructura a un puntero de estructura de mismo tipo y se envia los datos por la Queue mailbox . Por último, se bloquea la tarea con un delay , este delay tiene que ser de un tiempo para que el dure un segundo toda la ejecución general de la tarea , como ejemplo si para cuando se llega a la línea 161 pasaron 3us entonces el delay tiene que durar lo restante para llegar a 1 s.   

```
Sexta tarea en ejecutarse  puede ser alarm_task o print_task 
```
Puede ser ejecutable cualquiera de las 2 tareas ya que tiene la misma prioridad, supongamos que inicia la tarea alarm_task , entonces inicializa los lo necesario antes de entrar al ciclo de la tarea , entra al ciclo de la tarea , donde lo primero que hará es verificar un event gruop que esta esperando por todos los bits indicados , en este caso esta esperando 3 bits 
 
__Bits esperados__ = [1,1,1] 
Pero los bits están 
__Bits del event group__ = [1,1,0]  
Entonces la tarea de bloquea y se queda esperando todos los bits . 

```
Séptima  tarea en ejecutarse  es print_task
```
Para este momento es la única tarea que esta en ready , y se supone que aun no pasa el delay de la tarea de seconds_task, entonces se ejecuta la tarea se inicia todo lo necesario antes de entrar al ciclo de la tarea , se entra al ciclo de la tarea y lo primero que hace es verificar si hay algo recibido en al Queue mailbox , lo cual es cierto , porque la tarea se seconds_task envio el valor de 1 y el tipo enumerado , se pasa a la siguiente línea donde se toma un mutex y ese mutex no lo ha tomado nadie entonces sigue la ejecución , después entra en la primera verificación de un if , donde esta preguntado si el tipo enumerado de la estructura es de seconds_type , lo cual es True , entonces entra a la condicional , donde se iguala una estructura de tipo Int_to_char a la función que regresa una estructura que tiene unidades y decenas de parámetros de acuerdo a un numero ingresado . en este caso se ingreso el 1 , lo cual regresa un 1 en unidades y un 0 en decenas y lo imprime en la LCD Nokia y libera la memoria del mensaje de la Queue mailbox. Sale de la condicional , por obviedad las demás condiciones no se cumplen y por ultimo libera el mutex que tomo. 
 
```
Octava  tarea en ejecutarse  es  print_task
```
Ya que no se bloquea esta tarea , está en ready , vuelve a entrar a la tarea y lo primero es verificar si existe un mensaje en al Queue mailbox , lo cual esta vacia , entonces la tarea se bloquea  indefinidamente esperando a que envíen un dato por el mailbox. 




```
Novena  tarea en ejecutarse  puede ser IDLE o seconds_task
```
En este punto todas las tareas están bloqueadas , supongamos que la tarea seconds_task aun le falta 1ms para completar el delay entonces el IDLE se ejecutara 1ms aprox porque ninguna tarea se desbloqueara , ya que todas depende de una cadenita que viene desde seconds_task.  

```
¿Qué sigue ? 
```
Las únicas tareas que se estarán desbloqueando son seconds_task , print_task y el IDLE, una ves que los segundos llegue a 23 pasa lo siguiente. 
 Los bits se completan 
  
__Bits del event group__ = [1,1,1] 

Y se desbloquea alarm_task , luego se envia a al mailbox el 23 y se desbloquea print_task. Supongamos que alarm toma el control , se ejecuta toma el mutex   e imprime en la lcd Nokia el string de __ ALARM !!!__ , luego se da un delay de 1s , se bloquea la tarea , entonces la tarea print_task se ejecuta porque tiene un mailbox , pero al momento de tomar el mutex se bloquea , porque el mutex lo tomo la tarea de alarm_task , entonces lo único que se ejecuta es las tarea seconds_task y IDLE.  Esto se puede invertir ya que tiene las mismas prioridades. Una vez que termina de ejecutarse alarm_task y que libera el mutex , la tarea print_task va y se ejecuta con el valor actual del reloj y no en el que se quedó. Esto demuestra que no se interrumpen las impresiones de la pantalla lcd  y que el sistema de las demás tareas  sigue funcionando. 


# Resultados

```
Los resultados en la LCD nokia 5110 se tienen que ver de la sigueinte manera 
```

## Inicio de la Pantalla 
![20210826_195052](https://user-images.githubusercontent.com/78750676/131056226-c5d713a2-a960-4829-a23f-9faae1ff06eb.jpg)


## Alarma activada 

![20210826_195132](https://user-images.githubusercontent.com/78750676/131056233-9d0ba1b9-7fc5-42df-a8d7-8f986f6ccd3f.jpg)



                   
 
 
