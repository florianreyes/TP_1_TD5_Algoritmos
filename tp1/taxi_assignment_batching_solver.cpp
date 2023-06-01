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
    this->_createMinCostFlowNetwork();

    // Obtain the solve the problem.
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
            solucion.assign(this->_min_cost_flow.Tail(i), this->_min_cost_flow.Head(i) - _instance.n);
        }
    }
    else
    {
        std::cout << "Solving the min cost flow problem failed. Solver status: "
                  << status << std::endl;
    }
    // guardamos en la variable _solution_time el tiempo de ejecucion de asignacion de taxis a pasajeros
    this->_solution_time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    this->_objective_value = this->_min_cost_flow.OptimalCost() / 10.0;
    this->_solution_status = status;
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
    std::vector<int64_t> start_nodes(n * n, -1);
    std::vector<int64_t> end_nodes(n * n, -1);
    std::vector<int64_t> capacities(n * n, 1);
    std::vector<int64_t> unit_costs(n * n, -1);

    int cnt = 0;
    for (int i = 0; i < this->_instance.n; i++)
    {
        for (int j = this->_instance.n; j < 2 * this->_instance.n; j++)
        {
            start_nodes[cnt] = i;
            end_nodes[cnt] = j;
            unit_costs[cnt] = 10 * this->_instance.dist[i][j - n];
            cnt++;
        }
    }

    std::vector<int64_t> supplies(2 * n, 0);
    for (int i = 0; i < this->_instance.n; i++)
    {
        supplies[i] = 1;
        supplies[n + i] = -1;
    }

    for (int i = 0; i < start_nodes.size(); ++i)
    {
        int arc = this->_min_cost_flow.AddArcWithCapacityAndUnitCost(start_nodes[i], end_nodes[i], capacities[i], unit_costs[i]);
        if (arc != i)
            LOG(FATAL) << "Internal error";
    }

    for (int i = 0; i < supplies.size(); ++i)
    {
        this->_min_cost_flow.SetNodeSupply(i, supplies[i]);
    }
}