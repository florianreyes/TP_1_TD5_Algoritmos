#include "taxi_assignment_batching_solver.h"

BatchingSolver::BatchingSolver() {}

BatchingSolver::BatchingSolver(TaxiAssignmentInstance &instance)
{
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_status = 0;
    this->_solution_time = 0;
}

void BatchingSolver::setInstance(TaxiAssignmentInstance &instance)
{
    this->_instance = instance;
}

void BatchingSolver::solve()
{
    auto start = std::chrono::high_resolution_clock::now();

    //  creo el grafo de min cost flow
    this->_createMinCostFlowNetwork();
    // resuelvo el problema de min cost flow
    int status = this->_min_cost_flow.Solve();

    auto stop = std::chrono::high_resolution_clock::now();

    TaxiAssignmentSolution solucion(_instance.n);

    // Obtain the solution, construct the corresponding object and record de desired parameters.
    if (status == operations_research::MinCostFlow::OPTIMAL)
    {
        for (std::size_t i = 0; i < this->_min_cost_flow.NumArcs(); ++i)
        {
            int64_t flow = this->_min_cost_flow.Flow(i);
            if (flow == 0)
                continue;
            int64_t cost = this->_min_cost_flow.Flow(i) * this->_min_cost_flow.UnitCost(i);
            if (this->_min_cost_flow.Tail(i) != 0 && this->_min_cost_flow.Head(i) != 2 * _instance.n + 1)
            {
                solucion.assign(this->_min_cost_flow.Tail(i) - 1, this->_min_cost_flow.Head(i) - _instance.n - 1);
            }
        }
    }
    else
    {
        std::cout << "Solving the min cost flow problem failed. Solver status: "
                  << status << std::endl;
    }
    // guardamos en la variable _solution_time el tiempo de ejecucion de asignacion de taxis a pasajeros
    this->_solution_time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    // obtenemos el minimo costo de la solucion del problema de min cost flow
    this->_objective_value = this->_min_cost_flow.OptimalCost() / 10.0;
    // guardamos el status de la solucion, es decir si fue optima o no
    this->_solution_status = status;
    // guardamos la solucion obtenida del problema de min cost flow
    this->_solution = solucion;
}

double BatchingSolver::getObjectiveValue() const
{
    return this->_objective_value;
}

TaxiAssignmentSolution BatchingSolver::getSolution() const
{
    return this->_solution;
}

int BatchingSolver::getSolutionStatus() const
{
    return this->_solution_status;
}

double BatchingSolver::getSolutionTime() const
{
    return this->_solution_time;
}

void BatchingSolver::_createMinCostFlowNetwork()
{

    // Inicializar el grafo
    int n = this->_instance.n;
    std::vector<int64_t> start_nodes((n * n) + (2 * n), -1);
    std::vector<int64_t> end_nodes((n * n) + (2 * n), -1);
    std::vector<int64_t> capacities((n * n) + (2 * n), 1);
    std::vector<int64_t> unit_costs((n * n) + (2 * n), -1);

    // Inicializar los nodos fuente y sumidero
    for (int i = 0; i < n; i++)
    {
        // El nodo s es el 0 y conecta con los taxis que van desde 1 hasta n (n nodos)
        start_nodes[i] = 0;
        // Cada end node son los taxis que van desde 1 hasta n (n nodos)
        // Cada taxi ahora es tambien end node de un nuevo start node
        end_nodes[i] = i + 1;
        unit_costs[i] = 0;
        // Cada nuevo start node son los pasajeros que van desde n+1 hasta 2n (n nodos)
        // Los agregamos como nuevos start nodes al sumidero, luego, van desde n*n+n hasta n*n+2n (n nodos)
        start_nodes[n * n + n + i] = n + i + 1;
        // Agregamos el sumidero como end node
        end_nodes[n * n + n + i] = 2 * n + 1;
        unit_costs[n + i + 1] = 0;
    }

    // Inicializar los nodos intermedios (los que conectan taxis con pasajeros)
    int cnt = n;
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = n + 1; j < (2 * n) + 1; j++)
        {
            start_nodes[cnt] = i;
            end_nodes[cnt] = j;
            unit_costs[cnt] = 10 * this->_instance.dist[i - 1][j - n - 1] + (10 * this->_instance.dist[i - 1][j - n - 1] - this->_instance.pax_trip_dist[j - n - 1]);
            cnt++;
        }
    }

    int source = 0;
    int sink = 2 * n + 1;
    // Inicializar los supplies de los nodos
    std::vector<int64_t> supplies(2 * n + 2, 0);
    supplies[source] = n;
    supplies[sink] = -n;

    for (int i = 0; i < start_nodes.size(); ++i)
    {
        // Agregar un arco con capacidad y costo unitario
        int arc = this->_min_cost_flow.AddArcWithCapacityAndUnitCost(start_nodes[i], end_nodes[i], capacities[i], unit_costs[i]);
        if (arc != i)
            LOG(FATAL) << "Internal error";
    }

    for (int i = 0; i < supplies.size(); ++i)
    {
        // Establecer el valor de supply para el nodo i
        this->_min_cost_flow.SetNodeSupply(i, supplies[i]);
    }
}