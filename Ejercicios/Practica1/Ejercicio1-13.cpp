#include <iostream>
#include <vector>
#include <algorithm>

int maxParejas(std::vector<int>& conjunto1, std::vector<int>& conjunto2)
{
    int parejas = 0;
    int i = 0;
    int j = 0;

    while (i < conjunto1.size() && j < conjunto2.size())
    {
        if (abs(conjunto1[i] - conjunto2[j]) <= 1)
        {
            parejas++;
            i++;
            j++;
        }
        else if (conjunto1[i] < conjunto2[j])
        {
            i++;
        }
        else
        {
            j++;
        }
    }

    return parejas;
}

//int main()
//{
//    std::vector<int> conjunto1 = { 1, 2, 4, 6 };
//    std::vector<int> conjunto2 = { 1, 5, 5, 7, 9 };
//
//    int parejas = maxParejas(conjunto1, conjunto2);
//
//    std::cout << "La máxima cantidad de parejas de baile es: " << parejas << std::endl;
//
//    return 0;
//}


// A) Dado que ambos multiconjuntos de habilidades están ordenados en forma creciente, podemos recorrer los multiconjuntos en orden para realizar los emparejamientos.
// Esto se debe a que al ordenarlos, garantizamos que las habilidades más cercanas estarán juntas, lo que facilita la formación de parejas.
// 
// B) Algoritmo goloso :
// 
// 1) Inicializar dos punteros, uno para cada conjunto de habilidades, apuntando al inicio de cada uno.
// 2) Iniciar un contador para llevar la cuenta de las parejas formadas.
// 3) Recorrer ambos conjuntos simultáneamente :
// 4) Comparar las habilidades apuntadas por los dos punteros.
// 5) Si la diferencia es menor o igual a 1, formar una pareja y avanzar ambos punteros.
// 6) Si no, avanzar el puntero de la persona con habilidad menor.
// 7) Repetir hasta que se recorra todo el conjunto.
// 8) Devolver el contador de parejas formadas.
//
// Complejidad temporal: El algoritmo recorre ambos conjuntos una sola vez, lo que tiene una complejidad lineal en la cantidad total de personas en ambos conjuntos.
//                       Por lo tanto, la complejidad temporal es O(n + m), donde n es el tamaño del primer conjunto y m es el tamaño del segundo conjunto.
//
// Complejidad espacial auxiliar: El algoritmo utiliza solo unas pocas variables auxiliares, por lo que la complejidad espacial auxiliar es O(1).
//
// C) Para demostrar que el algoritmo es correcto, podemos observar que en cada paso, 
// el algoritmo forma una pareja de baile utilizando la persona con la habilidad más baja disponible en ambos conjuntos 
// que cumpla con la condición de tener una diferencia de habilidad menor o igual a 1. Dado que los conjuntos están ordenados,
// esta estrategia garantiza que formaremos la mayor cantidad de parejas posibles sin violar la restricción de diferencia de habilidad.
// Como el algoritmo no revisita ninguna persona y siempre elige la mejor opción disponible en cada paso, termina formando la máxima cantidad de parejas posible.
