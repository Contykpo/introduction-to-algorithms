// Ejercicios.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

// Función para calcular la distancia entre dos secuencias
int distance(const vector<int>& X, const vector<int>& Y)
{
    int dist = 0;
    for (size_t i = 0; i < X.size(); ++i)
    {
        dist += abs(X[i] - Y[i]);
    }

    return dist;
}

// Función para encontrar el árbol generador mínimo usando el algoritmo de Prim
vector<vector<int>> minimumSpanningTree(const vector<vector<int>>& sequences)
{
    int n = sequences.size(); // Número de secuencias
    vector<vector<int>> graph(n, vector<int>(n)); // Grafo completo con distancias entre secuencias

    // Calcular las distancias entre todas las secuencias y llenar el grafo completo
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            graph[i][j] = graph[j][i] = distance(sequences[i], sequences[j]);
        }
    }

    vector<bool> selected(n, false); // Para marcar las secuencias seleccionadas
    vector<vector<int>> tree(n, vector<int>(n, INF)); // Árbol generador mínimo

    // Elegir arbitrariamente la primera secuencia como raíz del árbol
    selected[0] = true;

    // Construir el árbol generador mínimo
    for (int i = 1; i < n; ++i)
    {
        int minDist = INF;
        int minIndex = -1;

        // Encontrar la secuencia más cercana al conjunto de secuencias seleccionadas
        for (int j = 0; j < n; ++j)
        {
            if (!selected[j] && graph[j][i] < minDist)
            {
                minDist = graph[j][i];
                minIndex = j;
            }
        }

        // Agregar la arista al árbol generador mínimo
        tree[minIndex][i] = tree[i][minIndex] = minDist;
        selected[minIndex] = true;
    }

    return tree;
}

int main()
{
    int n, k; // Número de secuencias y tamaño de cada secuencia
    cin >> n >> k;

    vector<vector<int>> sequences(n, vector<int>(k)); // Conjunto de secuencias

    // Leer las secuencias
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < k; ++j)
        {
            cin >> sequences[i][j];
        }
    }

    // Encontrar el árbol generador mínimo del grafo asociado
    vector<vector<int>> minimumTree = minimumSpanningTree(sequences);

    // Imprimir el árbol generador mínimo
    cout << "Árbol generador mínimo:" << endl;
    
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (minimumTree[i][j] != INF)
            {
                cout << "Secuencia " << i + 1 << " - Secuencia " << j + 1 << ": " << minimumTree[i][j] << endl;
            }
        }
    }

    return 0;
}
