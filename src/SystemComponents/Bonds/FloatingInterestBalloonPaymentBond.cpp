/**
 * The FloatingInterestBalloonPaymentBond sub-class for the Bond class.
 * 
 * @author Bernardo Trindade
 * @date 04/17/2018
 */

#include <cmath>
#include <algorithm>
#include "FloatingInterestBalloonPaymentBond.h"
#include "../../Utils/Utils.h"


FloatingInterestBalloonPaymentBond::FloatingInterestBalloonPaymentBond(const int id, const double cost_of_capital, const double n_payments,
                                           const vector<double> interest_rate_series, vector<int> pay_on_weeks) :
        Bond(id, cost_of_capital, n_payments, pay_on_weeks, LEVEL_DEBT_SERVICE), interest_rate_series(interest_rate_series),
        begin_repayment_after_n_years(NONE) {}


FloatingInterestBalloonPaymentBond::FloatingInterestBalloonPaymentBond(const int id, const double cost_of_capital, double n_payments,
                                           const vector<double> interest_rate_series, vector<int> pay_on_weeks,
                                           const int starts_paying_after_n_years) :
        Bond(id, cost_of_capital, n_payments, pay_on_weeks, LEVEL_DEBT_SERVICE), interest_rate_series(interest_rate_series),
        begin_repayment_after_n_years(starts_paying_after_n_years) {}


double FloatingInterestBalloonPaymentBond::getDebtService(int week) {

    if (n_payments_made < n_payments &&
        week > week_issued + begin_repayment_after_n_years * WEEKS_IN_YEAR  - 1 &&
        std::find(pay_on_weeks.begin(), pay_on_weeks.end(), Utils::weekOfTheYear(week)) != pay_on_weeks.end()) {

        n_payments_made++;
        try {
            return cost_of_capital * interest_rate_series.at((unsigned long) n_payments_made - 1);
        } catch(out_of_range &e) {
            e.what();
            throw out_of_range("Floating interest bond with interest time series shorter than number of weeks prior "
                                 "to payments -- too short of an interest time series.");
        }
    } else {
        return 0.;
    }
}


double FloatingInterestBalloonPaymentBond::getNetPresentValueAtIssuance(double yearly_discount_rate, int week) const {
    return cost_of_capital * (1. + interest_rate_series[week]) / (1. + yearly_discount_rate);
}


void FloatingInterestBalloonPaymentBond::issueBond(int week, int construction_time, double bond_term_multiplier,
                                                   double bond_interest_rate_multiplier) {
    Bond::issueBond(week, 0, bond_term_multiplier, bond_interest_rate_multiplier);

    for (double &i : interest_rate_series) {
        i *= bond_interest_rate_multiplier;
    }
}

