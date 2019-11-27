//
// Created by Bernardo on 11/25/2019.
//

#include "AllocatedReservoirParser.h"
#include "../../SystemComponents/WaterSources/AllocatedReservoir.h"
#include "../Exceptions/MissingParameter.h"

AllocatedReservoirParser::AllocatedReservoirParser() : ReservoirParser() {}

WaterSource *
AllocatedReservoirParser::generateSource(int id, vector<vector<string>> &block, int line_no, int n_realizations,
                                         int n_weeks) {

    parseVariables(block, n_realizations, n_weeks);
    checkMissingOrExtraParams(line_no, block);
    //TODO: ADD EXCEPTION HANDLING FOR MISSING VARIABLES.

    if (existing_infrastructure && variable_area) {
        return new AllocatedReservoir(name, id, catchments, capacity,
                                      treatment_capacity, evaporation_series,
                             storage_vs_area_curves,
                             utilities_with_allocations, allocated_fractions,
                             allocated_treatment_fractions);
    } else if (existing_infrastructure) {
        return new AllocatedReservoir(name, id, catchments, capacity,
                                      treatment_capacity, evaporation_series, storage_area,
                                      utilities_with_allocations,
                                      allocated_fractions,
                                      allocated_treatment_fractions);
    } else if (!existing_infrastructure && variable_area) {
        return new AllocatedReservoir(name, id, catchments, capacity,
                                      treatment_capacity, evaporation_series,
                             storage_vs_area_curves, construction_time,
                             permitting_time, *bonds.back(),
                                      utilities_with_allocations,
                                      allocated_fractions,
                                      allocated_treatment_fractions);
    } else if (!existing_infrastructure) {
        return new AllocatedReservoir(name, id, catchments, capacity,
                                      treatment_capacity, evaporation_series,
                             storage_area, construction_time,
                             permitting_time, *bonds.back(),
                                      utilities_with_allocations,
                                      allocated_fractions,
                                      allocated_treatment_fractions);
    } else {
        throw invalid_argument("Really weird error in AllocatedReservoirParser. Please "
                               "report this to bct52@cornell.edu");
    }
}


void AllocatedReservoirParser::checkMissingOrExtraParams(int line_no, vector<vector<string>> &block) {
    ReservoirParser::checkMissingOrExtraParams(line_no, block);

    if (utilities_with_allocations.empty()) {
        throw MissingParameter("utilities_with_allocations", tag_name, line_no);
    } else if (allocated_fractions.empty()) {
        throw MissingParameter("allocated_fractions", tag_name, line_no);
    } else if (allocated_treatment_fractions.empty()) {
        throw MissingParameter("allocated_treatment_fractions", tag_name, line_no);
    }
}
