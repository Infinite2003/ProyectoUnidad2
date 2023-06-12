# ProyectoUnidad2

Para este programa utilice tres clases con las que trabajar: 

Guardian: defino los parametros de cada guardian, nombre, poder, villa de origen, maestro del guardian, y una clase hijos del guardian para
indicar los alumnos del guardian referente.

ArbolGuardianes: Arbol general que utilizo para almacenar todos los guardianes o algunos guardianes en sus repsectivas aldeas.
Defino un vector de guardianes para poder almacenarlos todos los que ingrese, ademas de un guardian root para marcar la 
raiz del arbol general de guardianes, o sea, el guardian mas fuerte o el maestro de todos los guardianes. Tambien declaro funciones para 
buscar guardianes, ingresar guardianes al arbol manteniendo la jerarquia de poder, una funcion para imprimir un maestro y sus alumnos junto con
otra funcion para imprimir todos los guardianes del arbol que llama a la funcion antes mencionada. 

Aldeas: clase de tipo grafo que utilizo para generar las villas del mundo del juego, ademas de generar una relacion entre las mismas, cada una
con sus guardianes respectivos y una cantidad de puntos iniciales que ha ganado el jugador en la misma. Aqui declaro funciones con el fin 
de agregar guardianes a una aldea especifica dentro del grafo, imprimir las aldeas vecinas de una aldea en especifico y una para mostrar 
al guardian con menor nivel de poder dentro de una aldea especifica. 

Tambien declaro funciones separadas de las estructuras para poder cargar las aldeas y los guardianes del mundo del juego desde dos archivos
separados de tipo csv. En estas tomo el nombre del archivo, reviso si existe o no, y si existe, en el de aldeas ingreso el nombre de la 
aldea en un grafo y defino sus aldeas vecinas y los puntos base, ademas de ingresar las aldeas totales por separado a un vector de string, 
para poder hacer un recorrido de este vector mas adelante. En la funcion para agregar guardianes realizo la misma busqueda del archivo, y si
existe, ingreso los datos del guardian a un arbolGuardianes, genero una aldea temporal para igualarla a la aldea actual y poder ingresarle sus
guardianes respectivos y genero un arbol local dentro de la misma Aldea respentando la jerarquia de poder. 

Tambien declaro una funcion que recorre un unordered_map de llaves string y de valores Aldeas, que utilizo para relacionar una aldea con las 
demas que tiene conexion y poder ingresar a sus guardianes por el parametro tipo ArbolGuardianes que declaro en la clase Aldeas, para imprimir
todas las aldeas y sus adyacencias.

Genero otra funcion para imrpimir el vector string en el que almaceno las distintas aldeas del mundo del juego, con el fin de mostrarle las
opciones al usuario de a cual villa puede pertenecer su personaje si es que llega elegir crear uno. 

En la funcion crear guardian permito al usuario crear su guardian, pidiendole nombre y aldea a la que pertenece, defino su nivel de poder base
segun lo requerido y indico que no tiene maestro, que es independiente. Despues lo inserto al arbol general y al arbol de su villa de origen
para mantener la jerarquia.

Con la funcion mostrarAdyacencia recorro el unordered_map de string y Aldeas para poder enseñar las aldeas vecinas de la aldea correspondiente.

En combate genero el sistema de combate del jugador contra algun guardian o el maestro de la aldea. Primero le indico cual le recomendamos
pelear debido a su nivel de poder, luego le pedimos que seleccione a quien elige enfrentarse, y asegurarnos de que se enfrente a algun
guardian que exista, si no existe no pasa nada y debe seleccionar de nuevo realizar un combate. Despues empieza el combate, genero un numero
random entre 1 y 100, y si el resultado es mayor que su nivel de poder, entonces pierde, pero si no lo es, entonces gana el combate. Despues 
de que gane,compruebo si gano a Stormheart, ya que al ganarle en un combate, uno gana el juego. Si no se gano a Stormheart, 
comprobamos los puntos que a resivido de la aldea, y si los puntos de la aldea son menor que 4, el jugador gana un punto de poder
y actualizamos los puntos de la aldea, si son 4 o si el jugador tiene 100 puntos entonces no se le agrega nada.

En la funcion Alquimia realizo una conexion entre dos aldeas que antes no tenia una. Pido el nombre de la aldea en la que me encuentro y
la aldea que quiero conectar. Entonces si ambas aldeas existen dentro del unordered_map de string y Aldeas, genera dos Aldeas temporales, 
una de origen y otra de destino, agrego ambas aldeas a la lista de vecinos de cada aldea respectiva, y despues le indico al usuario que 
se realizo una conexion entre la aldea en la que se encuentra y la aldea destino que queria conectar. Y si no existe alguna de las aldeas,
entonces le indica que quiza ingreso algun dato mal y que intente de nuevo.

Con viajar le doy al usuario las aldeas adyacentes a la aldea a la que se encuentra, despues le indico que ingrese la aldea a la que desee
viajar, si el dato ingresado es una aldea que tiene conexion con la actual, entonces viaja, si no existe conexion con la que ingresa, entonces
se le indica que no existe conexion, pero si quiere puede realizar alquimia para generar una. Si selecciona que si, entonces realiza alquimia,
y si elige no, entonces no pasa nada y debe elegir una opcion general de nuevo. 

Despues en el main cargo los archivos a los datos y estructuras respectivas, le doy la bienvenida, le indico si desea crear o elegir un 
personaje, empiezo el bucle y empieza lo que es el juego, indicandole sus opciones de combatir o viajar a otras aldeas.   
