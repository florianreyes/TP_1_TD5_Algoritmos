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
    int n_pasajeros = _instance.n;
    //instaciamos la solucion
    TaxiAssignmentSolution solucion(n_pasajeros);
    //comenzamos el cronometro
    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < n_pasajeros; j++)
    {
        // buscamos el taxi con menor distancia
        double menor_distancia = std::numeric_limits<double>::infinity();
        int mejor_taxi = -1;
        for (int i = 0; i < n_pasajeros; i++)
        {
            if (!solucion.isTaxiAssigned(i) && this->_instance.dist[i][j] < menor_distancia)
            {
                menor_distancia = this->_instance.dist[i][j];
                mejor_taxi = i;
            }
        }
        //asignamos el mejor taxi disponible para el pasajero
        solucion.assign(mejor_taxi, j);
        //sumamos distancia al valor objetivo
        this->_objective_value += this->_instance.dist[mejor_taxi][j];
    }
    auto stop = std::chrono::high_resolution_clock::now();
    // guardamos en la variable _solution_time el tiempo de ejecucion de asignacion de taxis a pasajeros
    this->_solution_time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    // guardamos en la variable _solution la solucion
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
