/**
 * The BalloonPaymentBond sub-class of the Bond base class.
 * 
 * @author Bernardo Trindade
 * @date 04/17/2018
 */ 

#ifndef TRIANGLEMODEL_BALLOONPAYMENTBOND_H
#define TRIANGLEMODEL_BALLOONPAYMENTBOND_H

#include <vector>
#include "Base/Bond.h"

class BalloonPaymentBond : public Bond {
private:

    /**
     * Amount of interest to be paid on the balloon payment bond.
     */
    double interest_payments;

    /**
     * Repayment delay for the balloon payment bond.
     * If bond is to start being paid for at issuance, set repayment delay to 0.
     * Otherwise, begin bond repayment at issuance.
     */
    const int begin_repayment_after_n_years;

    /**
     * Number of payments to be made on an issued balloon payment bond.
     * Default value set at 0.
     */ 
    int n_payments_made = 0;

public:

    /**
     * BalloonPaymentBond object constructor.
     * Balloon payment at maturity corresponding to the sum of face value and last interest payment.
     * 
     * @param id Balloon payment bond identification number.
     * @param cost_of_capital Construction cost of capital for the balloon payment bond.
     * @param n_payments Number of payments to be made on an issued balloon payment bond.
     * @param coupon_rate Yield paid on a balloon payment bond by its issuer.
     * @param pay_on_weeks Weeks on which balloon payment bond payments are issued.
     */ 
    BalloonPaymentBond(const int id, const double cost_of_capital, const int n_payments,
                         const double coupon_rate, vector<int> pay_on_weeks);

    /**
     * BalloonPaymentBond object constructor.
     * Balloon payment at maturity corresponding to the sum of face value and last interest payment.
     * 
     * @param id Balloon payment bond identification number.
     * @param cost_of_capital Construction cost of capital for the balloon payment bond.
     * @param n_payments Number of payments to be made on an issued balloon payment bond.
     * @param coupon_rate Yield paid on a balloon payment bond by its issuer.
     * @param pay_on_weeks Weeks on which balloon payment bond payments are issued.
     * @param begin_repayment_after_n_years Repayment delay for the balloon payment bond.
     * If bond is to start being paid for at issuance, set repayment delay to 0.
     * Otherwise, begin bond repayment at issuance.
     */ 
    BalloonPaymentBond(const int id, const double cost_of_capital, const int n_payments, const double coupon_rate,
                       vector<int> pay_on_weeks, const int begin_repayment_after_n_years);

    /**
     * Calculates debt service payments of a balloon payment bond for a given week.

     * 
     * @param week Week of balloon payment bond issuance.
     * 
     * @returns Value of interest payments to be made on a balloon payment bond for a given week.
     * If there are still payments to be made, repayment has begun.
     * If repayment has begun and the week is a payment week, issue bond.
     * If repayment has begun and the week is the last payment week, pay principal and last interest.
     * Else, return 0.
     */
    double getDebtService(int week) override;

    /**
     * Gets the net present value of the balloon payment bond at the date of issuance.
     * 
     * @param discount_rate Interest rate paid on the balloon payment bond.
     * @param week Week of balloon payment bond issuance.
     * 
     * @returns Net present value of the balloon payment bond at the date of issuance.
     */ 
    double getNetPresentValueAtIssuance(double discount_rate, int week) const override;
    
    /**
     * Sets the date to begin repayment of the balloon payment bond and 
     * the interest to be paid every pay period.
     * 
     * @param week Week in the of balloon payment bond issuance.
     * @param construction_time Duration of infrastructure construction.
     * @param bond_term_multiplier Number of payments to be made as a function of 
     * the balloon payment bond maturity date.
     * @param bond_interest_rate_multiplier Coupon rate as a function of the interest
     * paid on the balloon payment bond.
     */
    void issueBond(int week, int construction_time, double bond_term_multiplier, double bond_interest_rate_multiplier) override;
};


#endif //TRIANGLEMODEL_BALLOONPAYMENTBOND_H
