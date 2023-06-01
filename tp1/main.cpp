#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "checker.h"
#include "greedy_solver.h"
#include "taxi_assignment_batching_solver.h"
#include "min_cost_flow_solver.h"
#include <cmath>

bool writeToCsv(std::string filename, std::string zb, std::string zg, std::string gap, std::string tb, std::string tg, std::string fileInput)
{
    std::ofstream myfile;
    myfile.open(filename, std::ios_base::app);
    myfile << zb << "," << zg << "," << gap << "," << tb << "," << tg << "," << fileInput << std::endl;
    myfile.close();
    return true;
};

int main(int argc, char **argv)
{
    std::vector<std::string> names = {"small_0.csv", "small_1.csv", "small_2.csv", "small_3.csv", "small_4.csv", "small_5.csv", "small_6.csv", "small_7.csv", "small_8.csv", "small_9.csv", "medium_0.csv", "medium_1.csv", "medium_2.csv", "medium_3.csv", "medium_4.csv", "medium_5.csv", "medium_6.csv", "medium_7.csv", "medium_8.csv", "medium_9.csv", "large_0.csv", "large_1.csv", "large_2.csv", "large_3.csv", "large_4.csv", "large_5.csv", "large_6.csv", "large_7.csv", "large_8.csv", "large_9.csv", "xl_0.csv", "xl_1.csv", "xl_2.csv", "xl_3.csv", "xl_4.csv", "xl_5.csv", "xl_6.csv", "xl_7.csv", "xl_8.csv", "xl_9.csv"};

    std::cout << "Corriendo" << std::endl;
    bool result = writeToCsv("greedy_vs_batching.csv", "zb", "zg", "gap", "time_batching", "time_greedy", "filename");
    for (auto elem : names)
    {
        std::string filename = "input/" + elem;

        TaxiAssignmentInstance instance(filename);
        // std::cout << filename << std::endl;

        TaxiAssignmentSolution solution(instance.n);

        GreedySolver solver_1(instance);

        BatchingSolver solver_2(instance);

        solver_1.solve();
        solver_2.solve();

        double zg = solver_1.getObjectiveValue();
        double zb = solver_2.getObjectiveValue();

        double tg = solver_1.getSolutionTime();
        double tb = solver_2.getSolutionTime();

        double gap_greedy = (zg - zb) / zg;

        bool result = writeToCsv("greedy_vs_batching.csv", std::to_string(zb), std::to_string(zg), std::to_string(gap_greedy), std::to_string(tb), std::to_string(tg), elem);
    };
    return 0;
}