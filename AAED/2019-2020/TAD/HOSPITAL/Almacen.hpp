/**almacen.hpp**/
/*Una empresa ha robotizado su almacén. Para ello lo ha dividido en 60 estantes de tres tamaños diferentes (pequeño, mediano y grande) 
a partes iguales. A cada estante se le asigna un elemento según su tamaño (en cada estante solo hay elementos de un tipo, pero puede 
haber hasta 50 elementos del mismo tipo).
Se pide diseñar un TAD para el funcionamiento del robot que incluya las siguientes operaciones:
    1. Crear un almacén vacío.
    2. Insertar un elemento en un estante. Si ya hay un estante asignado, y el elemento cabe, se coloca en ese. Si no es así, 
    se busca otro estante del mismo tamaño. Si no hay, se devuelve False. Si se puede colocar se devuelve True.
    3. Comprobar si hay elementos de un tipo determinado.
    4. Sacar un elemento de un tipo dado.
    5. Vaciar el almacén (destructor del TAD).
*/

