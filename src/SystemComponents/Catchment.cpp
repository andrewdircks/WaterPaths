//
// Created by bernardo on 1/13/17.
//

#include <cmath>
#include "Catchment.h"


Catchment::Catchment(vector<vector<double>> &streamflows_all, int series_length)
        : streamflows_all(&streamflows_all), series_length(series_length) {

    if (series_length <
        Constants::WEEKS_IN_YEAR * Constants::NUMBER_REALIZATIONS_ROF)
        throw std::length_error("Series in catchment is " 
			        + to_string(series_length) + " weeks long and "
					"therefore shorter than required for ROF"
					" calculations. The streamflow series "
					"must be greater the number of ROF ("
                                + to_string(Constants::NUMBER_REALIZATIONS_ROF)
                                + ") realizations times the number of "
                                        "weeks in a year ("
                                + to_string(Constants::WEEKS_IN_YEAR) + ").");

    if (streamflows_all.empty() || streamflows_all.at(0).empty()) {
        throw std::length_error("Empty time series.");
    }
}

Catchment::Catchment(const Catchment &catchment) :
        streamflows_all(catchment.streamflows_all),
        streamflows_realization(catchment.streamflows_realization),
        series_length(catchment.series_length),
        parent(false) {}


Catchment &Catchment::operator=(const Catchment &catchment) {
    streamflows_all = catchment.streamflows_all;
    series_length = catchment.series_length;
    return *this;
}

Catchment::Catchment() = default;


Catchment::~Catchment() {
    streamflows_all = nullptr;
}


double Catchment::getStreamflow(int week) const {
    int adjusted_week = week + delta_week;
    return streamflows_realization[adjusted_week];
}


void Catchment::setRealization(unsigned long r, const vector<double> &rdm_factors) {
    streamflows_realization = vector<double>(streamflows_all->at(r));
}

int Catchment::getSeriesLength() const {
    return series_length;
}



