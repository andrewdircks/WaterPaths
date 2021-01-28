//
// Created by bernardo on 1/13/17.
//

#ifndef TRIANGLEMODEL_CATCHMENT_H
#define TRIANGLEMODEL_CATCHMENT_H

#include <vector>
#include "../Utils/Constants.h"

using namespace std;
using namespace Constants;

class Catchment {
protected:

    /**
     * Null pointer to a matriz of doubles for the streamflows from
     * all realizations.
     */ 
    vector<vector<double>> *streamflows_all = nullptr;

    /**
     * Initialization of a vector of doubles containing values for
     * the streamflows of the realization of interest.
     */ 
    vector<double> streamflows_realization;

    /**
     * Uninitialized length of the time series of the realization
     * of interest.
     */ 
    int series_length = NON_INITIALIZED;

    /**
     * True if the object is the original Catchment object.
     * False if the object is a copy of the Catchment object.
     */ 
    bool parent = true;
    /**
     * Number of historical years of data.
     * Used to set week delta_week to week 0.
     */ 
    int delta_week = (int) std::round(
            Constants::WEEKS_IN_YEAR * Constants::NUMBER_REALIZATIONS_ROF);
 

public:
    /**
     * The default Catchment constructor.
     */
    Catchment();

    /**
     * The parameterized constructor for the Catchment class.
     * @param streamflows_all Reference to the matrix containing
     * streamflows from all realizations.
     * @param series_length Length of the timeseries of the realization 
     * of interest
     */ 
    Catchment(vector<vector<double>> &streamflows_all, int series_length);

    /**
     * Copy constructor for the Catchment class.
     * @param catchment Reference to the original Catchment object.
     */
    Catchment(const Catchment &catchment);

    /**
     * Destructor
     */
    virtual ~Catchment();

    /**
     * Copy assignment operator.
     * @param catchment Reference to the original Catchment object.
     * @return pointer to the original Catchment object. 
     */
    Catchment &operator=(const Catchment &catchment);

    /**
     * Gets the streamflow for a given week. 
     * This function assures that the number of past inflows used for 
     * ROF calculations are reserved in the beginning of the time series 
     * for ROF calculations.
     * @param week The week corresponding to the streamflow of interest.
     * @return the streamflows for the given week.
     */
    double getStreamflow(int week) const;

    /**
     * Gets the time series corresponding to realization index 
     * and eliminate reference to comprehensive streamflow data set.
     * @param r The realization of interest.
     * @param rdm_factors Reference to the set of policies corresponding to the realization.
     */
    virtual void setRealization(unsigned long r, const vector<double> &rdm_factors);

    /**
     * Gets the length of the time series corresponding to 
     * a particular realization.
     * @return the length of the time series of interest.
     */
    int getSeriesLength() const;
};


#endif //TRIANGLEMODEL_CATCHMENT_H
