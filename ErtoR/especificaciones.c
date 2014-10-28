Especificaciones del programa
Este programa se encarga de transformar un modelo entidad relacion al modelo relacional, 
recive como entrada un archivo con su extencion.
La estructura del archivo es la siguiente:

E-nombre de la entidad
s-atributo simple1,atributo simple2,....,atributo simpleN
d-atributo derivado1,atributo derivado2,...,atributo derivadoN
c-nombre atributo compuesto-s-atributo simple1,...atributo simpleN.d-atributo derivado1...atributo derivadoN.c-nombre atributo compuesto-s-atributos simples.d-atributos derivados.m-atributo multivaluado1...atributo multivaluado N
m-atributo multivaluado1,atributo multivaluado2,...,atributo multivaluadoN
k-atributo llave 1,atributo llave 2...atributo llave N
;

El nombre de la los atributos simples,compuestos,devidados,multivaluados y de entidades solo puede contener letras miniusculas,mayusculas,numeros y guion bajo. Al terminar cada entidad deve ir separada por un punto y coma.
Primero se escrive el nombre de la entidad despues los atributos que no sean multivaluados ni llave, es decir 
puedes escrivir atributos simples, despues derivados, despues compuestos que no contengan multivaluados, y despues la llave, esto es porque en la llave deves escrivir los atributos que ya "declaraste" antes 
y asta el ultimo los multivaluados, porque los multivaluados nesesitan primero saver cual es la llave.

Al poner las relaciones debemos poner primero las relaciones que influllan dos entidades fuertes, despues las que influllan una entidad fuerte y una devil, despues se ponene las que sean deviles. Pero estas ultimas deven de llevar en orden de modo que las entidades deviles se vallan convirtiendo en fuetes.
la sintanxis para las relaciones es la siguiente:
r-nombre de la relacion,-< o >nombre de la entidad uno,< o >nombre de la entidad dos|cardinalidad de entidad uno:cardinalidad de la entidad dos|partisipacion de la entidad uno:participacion de la entidad dos|s-atributos simples

el nombre de las entidades deven tener al principio el caracter < o > para definir si son fueretes o deviles
>entidad x, quiere desir que entidad x es devil
<entidad y, quiere desir que entidad y es fuerte

las cardinalidades solo pueden ser la siguientes
1:1
1:n
n:1
m:n
n:m
 
las participaciones pueden ser la siguientes
p:p , que se ignifica parcial:parcial
t:t , que se ignifica total:total
p:t , que se ignifica parcial:total
t:p , que se ignifica total:parcial

despues los atributos que estan en la relacion si no tiene entonses no pones nada.

La salida del programa es un fichero llamado relacional.dat
en donde vienen las tablas con sus atributos
que tiene la siguiente estructura:
|nombre entidad
|atributo 1|atributo 2|...|atributo N

Cuando un atributo tiene el signo de * se ignifica que es parte de la llave,
Cuando tiene el simbolo de & se ignifica que la entidad es propietaria de ese atributo
Cuando tiene el simbolo de $ se ignifica que el atributo no es de la entidad si no que otra entidad se lo paso,
el numero de $ tiene que ver mucho cuando son entidades deviles que se relacionan con entidades deviles
devido a que si una entidad devil le pasaron una llave la entidad devil tendra entre sus atributos el simbolo de $ pero si esa entidad devil le pasa su llave a otra entidad devil la entidad devil dos tendria doble signo de $
esto te dice de quien es propietaria el atributo.


