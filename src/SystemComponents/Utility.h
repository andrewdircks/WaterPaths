//
// Created by bernardo on 1/13/17.
//

#ifndef TRIANGLEMODEL_UTILITY_H
#define TRIANGLEMODEL_UTILITY_H


#include <map>
#include "WaterSources/Reservoir.h"
#include "../Utils/Constants.h"

class Utility {
private:
    double *demand_series;
    double total_storage_capacity;
    double total_stored_volume;
    map<int, WaterSource *> water_sources;
    map<int, double> split_demands_among_sources;

public:
    const int id;
    const int number_of_week_demands;
    const string name;

    Utility(string const name, int id, char const *demand_file_name, int number_of_week_demands);

    Utility(Utility &utility);

    ~Utility();

    Utility &operator=(const Utility &utility);

    double getDemand(int water_source_id);

    void updateTotalStoredVolume();

    const map<int, WaterSource *> &getWaterSource() const;

    void addWaterSource(WaterSource *water_source);

    double getStorageToCapacityRatio() const;

    void splitDemands(int week);

    double getTotal_storage_capacity() const;
};


#endif //TRIANGLEMODEL_UTILITY_H