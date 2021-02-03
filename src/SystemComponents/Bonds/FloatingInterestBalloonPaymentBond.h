/**
 * The FloatingInterestBalloonPaymentBond sub-class for the Bond class.
 * 
 * @author Bernardo Trindade
 * @date 04/17/2018
 */

#ifndef TRIANGLEMODEL_FLOATINGINTERESTBOND_H
#define TRIANGLEMODEL_FLOATINGINTERESTBOND_H


#include "Base/Bond.h"

class FloatingInterestBalloonPaymentBond : public Bond {
private:

    /**
     * Interest time series beginning from week 0 of simulation.
     */
    vector<double> interest_rate_series;

    /** 
     * Repayment delay for a floating interest bond.
     * If bond is to start being paid for at issuance, set repayment delay to 0.
     * Otherwise, begin bond repayment at issuance.
     */
    const int begin_repayment_after_n_years;

    /**
     * Number of payments already made on an issued floating interest bond.
     * Default value set at 0.
     */
    int n_payments_made = 0;

public:

    /** 
     * FloatingInterestBalloonPaymentBond constructor.
     * 
     * @param id Floating interest bond identification number.
     * @param cost_of_capital Construction cost of capital for the floating interest bond.
     * @param n_payments Number of payments to be made on an issued floating interest bond.
     * @param interest_rate_series Interest time series beginning from week 0 of simulation.
     * @param pay_on_weeks Weeks on which floating interest bond payments are issued.
     */ 
    FloatingInterestBalloonPaymentBond(const int id, const double cost_of_capital, const double n_payments,
                         const vector<double> interest_rate_series, vector<int> pay_on_weeks);

    /**
     * FloatingInterestBalloonPaymentBond constructor.
     * 
     * @param id Floating interest bond identification number.
     * @param cost_of_capital Construction cost of capital for the floating interest bond.
     * @param n_payments Number of payments to be made on an issued floating interest bond.
     * @param interest_rate_series Interest time series beginning from week 0 of simulation.
     * @param pay_on_weeks Weeks on which floating interest bond payments are issued.
     * @param starts_paying_after_n_years Year in which floating interest bond payments begin issuance.
     */
    FloatingInterestBalloonPaymentBond(const int id, const double cost_of_capital, double n_payments,
                         const vector<double> interest_rate_series, vector<int> pay_on_weeks,
                         const int starts_paying_after_n_years);

    /**
     * Calculates debt service payments for a floating interest bond for a given week.
     * 
     * @param week Week of floating interest bond issuance.
     * 
     * @returns Value of debt service payments for a given week.
     * If there are still payments to be made, repayment has begun.
     * If repayment has begun and the week is a payment week, issue bond.
     * If repayment has begun and the week is the last payment week, pay principal and last interest.
     * Else, return 0.
     * 
     * @throws out_of_range error if floating interest bond with interest time series shorter than number of weeks prior
     */
    double getDebtService(int week) override;

    /**
     * Gets the net present value of the floating interest bond at the date of issuance.
     * 
     * @param discount_rate Interest rate paid on the floating interest bond.
     * @param week Week of floating interest bond issuance.
     * 
     * @returns Net present value of floating interest bond at date of issuance.
     */
    double getNetPresentValueAtIssuance(double yearly_discount_rate, int week) const override;

    /**
     * Sets the date to begin repayment of the floating interest bond.
     * Multiplies entire interest time series by the RDM factor.
     * 
     * @param week Week in the of floating interest bond issuance.
     * @param construction_time Duration of infrastructure construction.
     * @param bond_term_multiplier Number of payments to be made as a function of 
     * the floating interest bond maturity date.
     * @param bond_interest_rate_multiplier Coupon rate as a function of the interest
     * paid on the floating interest bond.
     */
    void issueBond(int week, int construction_time, double bond_term_multiplier, double bond_interest_rate_multiplier) override;
};


#endif //TRIANGLEMODEL_FLOATINGINTERESTBOND_H
