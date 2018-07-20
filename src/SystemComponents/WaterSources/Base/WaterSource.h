//
// Created by bernardo on 1/22/17.
//

#ifndef TRIANGLEMODEL_WATERSOURCE_H
#define TRIANGLEMODEL_WATERSOURCE_H

#include <string>
#include "../../Catchment.h"
#include "../../../Utils/Constants.h"
#include "../../Bonds/Base/Bond.h"

using namespace std;
using namespace Constants;

class WaterSource {
protected:
    double available_volume = 0;
    double total_outflow = 0;
    double upstream_source_inflow = 0;
    double wastewater_inflow = 0;
    double upstream_catchment_inflow = 0;
    double total_demand = 0;
    double policy_added_demand = 0;
    double permitting_time = NON_INITIALIZED;
    vector<Bond *> bonds;
    double upstream_min_env_inflow = 0;
    double capacity = NON_INITIALIZED;

    vector<int> built_in_sequence;
    vector<double> available_allocated_volumes;
    vector<double> allocated_capacities;
    vector<double> allocated_treatment_capacities;
    vector<double> allocated_treatment_fractions;
    vector<double> allocated_fractions;
    vector<double> supply_allocated_fractions;
    vector<double> adjusted_allocated_treatment_capacities;

    vector<double> parent_reservoir_treatment_capacities;
    double unallocated_supply_capacity = 0;
    double unallocated_supply_fraction = 0;

    vector<int> *utilities_with_allocations = nullptr;
    int wq_pool_id = NON_INITIALIZED;
    double total_allocated_fraction = NON_INITIALIZED;
    bool online;
    vector<Catchment> catchments;
    double min_environmental_outflow = 0;
    double evaporated_volume = 0;
    double total_treatment_capacity = 0;
    int highest_alloc_id = NON_INITIALIZED;

    double base_wq_pool_fraction = 0.0;
    vector<double> fraction_of_treatment_capacity_for_use;

    virtual void applyContinuity(int week, double upstream_source_inflow,
                                     double wastewater_inflow,
                                     vector<double> &demand_outflow) = 0;

    void bypass(int week, double total_upstream_inflow);

public:
    const int id;
    const char *name;
    int source_type;
    const double construction_time;

    WaterSource(const char *name, const int id, const vector<Catchment *> &catchments,
                    const double capacity, vector<int> connected_sources, double treatment_capacity,
                    const int source_type);

    WaterSource(const char *name, const int id, const vector<Catchment *> &catchments,
                const double capacity, double treatment_capacity, vector<int> connected_sources,
                const int source_type, vector<double> *allocated_treatment_fractions,
                vector<double> *allocated_fractions, vector<int> *utilities_with_allocations);

    WaterSource(const char *name, const int id, const vector<Catchment *> &catchments,
                const double capacity, double treatment_capacity, vector<int> connected_sources,
                const int source_type, const vector<double> construction_time_range,
                double permitting_period, Bond &bond);

    WaterSource(const char *name, const int id, const vector<Catchment *> &catchments, const double capacity,
                double treatment_capacity, vector<int> connected_sources, const int source_type,
                const vector<double> construction_time_range, double permitting_period, vector<Bond *> bonds);

    WaterSource(const char *name, const int id, const vector<Catchment *> &catchments,
                    const double capacity, double treatment_capacity, vector<int> built_in_sequence,
                    const int source_type, vector<double> *allocated_treatment_fractions,
                    vector<double> *allocated_fractions, vector<int> *utilities_with_allocations,
                    const vector<double> construction_time_range, double permitting_period,
                Bond &bond);

    WaterSource(const char *name, const int id, const vector<Catchment *> &catchments,
                const double capacity, double treatment_capacity, vector<int> built_in_sequence,
                const int source_type, vector<double> *allocated_treatment_fractions,
                vector<double> *allocated_fractions, vector<int> *utilities_with_allocations,
                const vector<double> construction_time_range, double permitting_period,
                vector<Bond *> bonds);

    WaterSource(const WaterSource &water_source);

    virtual ~WaterSource();

    WaterSource &operator=(const WaterSource &water_source);

    bool operator<(const WaterSource *other);

    bool operator>(const WaterSource *other);

    bool operator==(const WaterSource *other);

    void continuityWaterSource(int week, double upstream_source_inflow,
                                   double wastewater_inflow,
                                   vector<double> &demand_outflow);

    virtual void addTreatmentCapacity(const double added_treatment_capacity, int utility_id);

    virtual void addAllocatedTreatmentCapacity(double added_allocated_treatment_capacity, int utility_id);

    virtual void setAllocatedSupplyCapacity(double capacity_allocation_fraction, int utility_id);

    virtual void removeWater(int allocation_id, double volume);

    virtual void addCapacity(double capacity);

    virtual void setOnline();

    virtual bool skipConstruction(int utility_id) const;

    virtual double getAvailableAllocatedVolume(int utility_id);

    double getMin_environmental_outflow() const;

    void setMin_environmental_outflow(double min_environmental_outflow);

    double getAvailableVolume() const;

    const vector<int> &getBuilt_in_sequence() const;

    double getTotal_outflow() const;

    bool isOnline() const;

    virtual void setFull();

    void setOutflow_previous_week(double outflow_previous_week);

    virtual double getSupplyCapacity();

    double getUpstream_source_inflow() const;

    double getDemand() const;

    double getUpstreamCatchmentInflow() const;

    static bool compare(WaterSource *lhs, WaterSource *rhs);

    virtual void setRealization(unsigned long r, vector<double> &rdm_factors);

    virtual double getAllocatedCapacity(int utility_id);

    virtual double getAllocatedFraction(int utility_id);

    double getEvaporated_volume() const;

    virtual double getAllocatedTreatmentCapacity(int utility_id) const;

    double getTotal_treatment_capacity(int utility_id) const;

    void setAllocations(
            vector<int> *utilities_with_allocations,
            vector<double> *allocated_fractions,
            vector<double> *allocated_treatment_fractions);

    void resetAllocations(const vector<double> *new_allocated_fractions);

    void setAvailableAllocatedVolumes(
            vector<double> available_allocated_volumes, double available_volume);

    vector<double> getAvailable_allocated_volumes() const;

    vector<int> *getUtilities_with_allocations() const;

    double getWastewater_inflow() const;

    double getPermitting_period() const;

    double getAvailableSupplyVolume() const;

    double getAllocatedInflow(int utility_id) const;

    virtual double getSupplyAllocatedFraction(int utility_id);

    Bond &getBond(int utility_id);

    void checkForInputErrorsConstruction();



    virtual void addWater(int allocation_id, double volume);

    void setCapacity(double new_capacity);

    void resetTreatmentAllocations(const vector<double> *new_allocated_treatment_fractions);

    virtual void updateTreatmentAndCapacityAllocations(int week);

    virtual void updateTreatmentAllocations(int week,
                                            vector<vector<vector<double>>> weekly_demands,
                                            vector<vector<vector<double>>> weekly_supply_based_demands);

    virtual double calculateJointWTPDebtServiceFraction(int utility_id, int week);

    virtual int getParentSourceID();

    virtual void addTotalTreatmentCapacity(const double added_plant_treatment_capacity);

    virtual double getAllocationAdjustment(const int utility_id);

    virtual void setAllocationAdjustment(const int utility_id, const double allocation_adjustment);

    virtual double getAllocatedTreatmentFraction(int utility_id) const;

    virtual void normalizeAllocations();

    virtual void setAllocatedTreatmentCapacity(const int year, const int utility_id);

    virtual void setExternalAllocatedTreatmentCapacity(const int year);

    virtual void recordParentReservoirTreatmentCapacity(const int utility_id, const double capacity_value);

    virtual void increaseAllocatedSupplyCapacity(double capacity_allocation_fraction, int utility_id);

    virtual vector<double> getPreviousPeriodAllocatedCapacities() const;

    virtual double getAllocatedTreatmentCapacityFractionalPlantAvailability(int utility_id) const;
};


#endif //TRIANGLEMODEL_WATERSOURCE_H
