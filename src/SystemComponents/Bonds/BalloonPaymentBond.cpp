/**
 * @author Bernardo Trindade
 * @date 04/17/2018
 */ 

#include <cmath>
#include <algorithm>
#include "BalloonPaymentBond.h"
#include "../../Utils/Utils.h"


BalloonPaymentBond::BalloonPaymentBond(const int id, const double cost_of_capital, const int n_payments,
                                       const double coupon_rate, vector<int> pay_on_weeks) :
    Bond(id, cost_of_capital, n_payments, pay_on_weeks, coupon_rate, BALLOON_PAYMENT),
    begin_repayment_after_n_years(NONE) {}


BalloonPaymentBond::BalloonPaymentBond(const int id, const double cost_of_capital, const int n_payments,
                                       const double coupon_rate, vector<int> pay_on_weeks,
                                       const int begin_repayment_after_n_years) :
        Bond(id, cost_of_capital, n_payments, pay_on_weeks, coupon_rate, BALLOON_PAYMENT),
        begin_repayment_after_n_years(begin_repayment_after_n_years) {}


double BalloonPaymentBond::getDebtService(int week) {
    if (n_payments_made < n_payments - 1 &&
          week > week_issued + begin_repayment_after_n_years * WEEKS_IN_YEAR &&
          std::find(pay_on_weeks.begin(), pay_on_weeks.end(), Utils::weekOfTheYear(week)) != pay_on_weeks.end()) {

        n_payments_made++;
        return interest_payments;
    } else if (n_payments_made == n_payments - 1) {

        n_payments_made++;
        return interest_payments + cost_of_capital;
    } else {
        return 0.;
    }
}


double BalloonPaymentBond::getNetPresentValueAtIssuance(double yearly_discount_rate, int week) const {
    double npv_at_first_payment_date = interest_payments *
                                       (1. - pow(1. + (yearly_discount_rate / pay_on_weeks.size()), -n_payments)) /
                                       (yearly_discount_rate / pay_on_weeks.size());

    return npv_at_first_payment_date / pow(1. + yearly_discount_rate, begin_repayment_after_n_years);
}


void BalloonPaymentBond::issueBond(int week, int construction_time, double bond_term_multiplier,
                                   double bond_interest_rate_multiplier) {
    Bond::issueBond(week, 0, bond_term_multiplier, bond_interest_rate_multiplier);

    interest_payments = coupon_rate * cost_of_capital;
}
