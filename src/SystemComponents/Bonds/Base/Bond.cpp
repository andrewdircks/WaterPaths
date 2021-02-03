/**
 * @author Bernardo Trindade
 * @date 04/12/2018
 */

#include "Bond.h"

Bond::Bond(const int id, const double cost_of_capital, const int n_payments,
           vector<int> pay_on_weeks, const int type,
           bool begin_repayment_at_issuance) :
        id(id), cost_of_capital(cost_of_capital), n_payments(n_payments),
        pay_on_weeks(pay_on_weeks), type(type) {

    if (begin_repayment_at_issuance) {
        begin_repayment_after_n_years = 0;
    }

    if (std::isnan(cost_of_capital) || cost_of_capital < 0) {
        string error = "Invalid construction cost of capital for bond "
                       + to_string(id);
        throw invalid_argument(error.c_str());
    }
}


Bond::Bond(const int id, const double cost_of_capital, const int n_payments,
           vector<int> pay_on_weeks, const double coupon_rate, const int type,
           bool begin_repayment_at_issuance) :
        id(id), cost_of_capital(cost_of_capital), n_payments(n_payments),
        pay_on_weeks(pay_on_weeks),
        coupon_rate(coupon_rate), type(type) {

    if (begin_repayment_at_issuance) {
        begin_repayment_after_n_years = 0;
    }

    if (std::isnan(cost_of_capital) || cost_of_capital < 0) {
        string error = "Invalid construction cost of capital for bond "
                       + to_string(id);
        throw invalid_argument(error.c_str());
    }
}


Bond::Bond() : id(NON_INITIALIZED), n_payments(NON_INITIALIZED),
               cost_of_capital(NON_INITIALIZED), type(NON_INITIALIZED) {}


Bond::~Bond() = default;


void Bond::setRealizationWaterSource(unsigned long r,
                                     vector<double> &rdm_factors) {
    cost_of_capital *= rdm_factors[0];
}


void Bond::issueBond(int week, int construction_time,
                     double bond_term_multiplier,
                     double bond_interest_rate_multiplier) {

    if (begin_repayment_after_n_years == NON_INITIALIZED) {
        begin_repayment_after_n_years =
                (int) (construction_time / WEEKS_IN_YEAR) + 1;
    }

    week_issued = week;
    n_payments *= bond_term_multiplier;
    coupon_rate *= bond_interest_rate_multiplier;
    setIssued();
}


bool Bond::isIssued() const {
    return issued;
}


void Bond::setIssued() {
    Bond::issued = true;
}


double Bond::getCouponRate() const {
    return coupon_rate;
}


double Bond::getCostOfCapital() const {
    return cost_of_capital;
}


int Bond::getNPayments() const {
    return n_payments;
}
