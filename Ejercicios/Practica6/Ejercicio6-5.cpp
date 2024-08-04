// Ejercicios.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <queue>

struct Cell
{
    int x;
    int y;
    int value;

    Cell(int _x, int _y, int _value) : x(_x), y(_y), value(_value) {}
};

int minMovementsToTransform(std::vector<std::vector<int>>& grid, int m, int n, int k, int x1, int y1, int target)
{
    std::vector<std::vector<int>> distances(m, std::vector<int>(n, -1)); // Distancias mínimas desde la celda inicial
    std::queue<Cell> q;

    // Inicializar BFS desde la celda inicial
    q.push(Cell(x1, y1, grid[x1][y1]));
    distances[x1][y1] = 0;

    // Movimientos posibles: arriba, abajo, izquierda, derecha
    std::vector<std::pair<int, int>> moves = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    // Aplicar BFS
    while (!q.empty()) {
        Cell current = q.front();
        q.pop();

        // Verificar las celdas adyacentes
        for (const auto& move : moves) {
            int nextX = current.x + move.first;
            int nextY = current.y + move.second;

            // Verificar si la celda adyacente está dentro de la grilla
            if (nextX >= 0 && nextX < m && nextY >= 0 && nextY < n) {
                // Calcular el próximo valor en la secuencia
                int nextValue = (current.value + grid[nextX][nextY]) % k;

                // Si la celda no ha sido visitada y es alcanzable desde la celda actual
                if (distances[nextX][nextY] == -1) {
                    distances[nextX][nextY] = distances[current.x][current.y] + 1;
                    q.push(Cell(nextX, nextY, nextValue));
                }
            }
        }
    }

    // Devolver la distancia mínima hasta el objetivo
    return distances[target / n][target % n];
}

//int main()
//{
//    int m;
//    int n;
//    int k;
//
//    std::cin >> m >> n >> k;
//
//    std::vector<std::vector<int>> grid(m, std::vector<int>(n));
//
//    for (int i = 0; i < m; ++i)
//    {
//        for (int j = 0; j < n; ++j)
//        {
//            std::cin >> grid[i][j];
//        }
//    }
//
//    int x1;
//    int y1;
//    int w;
//
//    std::cin >> x1 >> y1 >> w;
//
//    int minMovements = minMovementsToTransform(grid, m, n, k, x1, y1, w);
//
//    std::cout << minMovements << std::endl;
//
//    return 0;
//}
