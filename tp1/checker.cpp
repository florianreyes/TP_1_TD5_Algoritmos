#include "checker.h"

TaxiAssignmentChecker::TaxiAssignmentChecker(){}//_feasibility_status(std::vector<bool>(3,false)) 

bool TaxiAssignmentChecker::checkFeasibility(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution) {
    return _checkValuesInRange(instance, solution) && _checkPaxUnique(instance, solution) && _checkTaxiUnique(instance, solution);
}

bool TaxiAssignmentChecker::_checkValuesInRange(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution){
    for (int i = 0; i < instance.n; i++)
    {
        if(solution.getAssignedPax(i) >= instance.n || solution.getAssignedTaxi(i) >= instance.n){
            return false;
        }
    }
    
    return true;
}

bool TaxiAssignmentChecker::_checkPaxUnique(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution){
    for (int i = 0; i < instance.n; i++)
    {
        for (int j = 0; j < instance.n; j++)
        {
            if(solution.getAssignedPax(i) == solution.getAssignedPax(j) && i != j){
                return false;
            }
        }
        
    }
    return true;
}
bool TaxiAssignmentChecker::_checkTaxiUnique(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution){
    for (int i = 0; i < instance.n; i++)
    {
        for (int j = 0; j < instance.n; j++)
        {
            if(solution.getAssignedTaxi(i) == solution.getAssignedTaxi(j) && i != j){
                return false;
            }
        }
        
    }
    return true;
}

bool TaxiAssignmentChecker::getSolutionCost(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution) {
    double ret = 0.0;

    return ret;
}
