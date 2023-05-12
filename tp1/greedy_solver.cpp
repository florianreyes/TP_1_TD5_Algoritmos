#include "greedy_solver.h"

GreedySolver::GreedySolver() {}

GreedySolver::GreedySolver(TaxiAssignmentInstance &instance)
{
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_status = 0;
    this->_solution_time = 0;
}

void GreedySolver::setInstance(TaxiAssignmentInstance &instance)
{
    this->_instance = instance;
}

void GreedySolver::solve()
{
    // definimos cantidad de pasajeros para iterar
    int n_pasajeros = instance.n;
    TaxiAssignmentSolution solucion(n_pasajeros);
    // agarrar cada pasajero
    // buscar el taxi con menor distancia
    // asignar ese taxi a ese pasajero
    // guardar en la variable _solution la solucion
    vector<bool> taxi_usado(n_pasajeros, false);
    for (int j = 0; j < n_pasajeros; j++)
    {
        double menor_distancia = INFINITY;
        int mejor_taxi = -1;
        for (int i = 0; i < n_pasajeros; i++)
        {
            if (!taxi_usado && this->instance.dist[i][j] < menor_distancia)
            {
                menor_distiancia = this->instance.dist[i][j];
                mejor_taxi = i;
            }
        }
        taxi_usado[mejor_taxi] = true;
        solucion.assign(mejor_taxi, j);
    }
    this->_solution = solucion;
}

double GreedySolver::getObjectiveValue() const
{
    return this->_objective_value;
}

TaxiAssignmentSolution GreedySolver::getSolution() const
{
    return this->_solution;
}

int GreedySolver::getSolutionStatus() const
{
    return this->_solution_status;
}

double GreedySolver::getSolutionTime() const
{
    return this->_solution_time;
}
