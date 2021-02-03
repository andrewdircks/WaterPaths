/**
 * The LevelDebtServiceBond sub-class for the Bond class.
 * 
 * @author Bernardo Trindade
 * @date 04/12/2018
 */

#ifndef TRIANGLEMODEL_LEVELDEBTSERVICEBOND_H
#define TRIANGLEMODEL_LEVELDEBTSERVICEBOND_H


#include "Base/Bond.h"

class LevelDebtServiceBond : public Bond {
private:

    /**
     * Level debt bond service payment.
     */
    double level_debt_service_payment;

    /**
     * Number of payments already made to the level debt service bond.
     */
    int n_payments_made = 0;

public:

    /** 
     * LevelDebtServiceBond constructor.
     * If level debt service bond is to start being paid for at issuance, set repayment delay to 0.
     * Otherwise, begin bond repayment at issuance.
     * 
     * @param id Bond identification number.
     * @param cost_of_capital Construction cost of capital for the level debt service bond.
     * @param n_payments Number of payments to be made on the level debt service bond.
     * @param coupon_rate Yield paid on a level debt service bond by its issuer.
     * @param pay_on_weeks Weeks on which level debt service bond payments are issued.
     * @param begin_repayment_at_issance Repayment delay. 
     */
    LevelDebtServiceBond(const int id, const double cost_of_capital, const int n_payments,
                             const double coupon_rate, vector<int> pay_on_weeks, bool begin_repayment_at_issuance = false);

    /**
     * LevelDebtServiceBond destructor.
     */
    ~LevelDebtServiceBond() override;

    /**
     * Calculates debt service payments for a given week for the LevelDebtServiceBond object.
     * If there are still payments to be made, repayment has begun.
     * If repayment has begun and the week is a payment week, issue level debt service bond.
     * If repayment has begun and the week is the last payment week, 
     * pay bond principal and last interest.
     * 
     * @param week Week of level debt service bond issuance.
     * 
     * @returns Value of level debt service payments for a given week.
     */
    double getDebtService(int week) override;

    /**
     * Gets the level debt service bond net present value at its date of issuance.
     * 
     * @param yearly_discount_rate Yearly discount rate paid on the level debt service bond.
     * @param week Week of level debt service bond issuance.
     * 
     * @returns Net present value of the level debt service bond at the date of issuance.
     */
    double getNetPresentValueAtIssuance(double yearly_discount_rate, int week) const override;

    /**
     * Sets the level debt service payment value.
     * 
     * @param week Week in the of level debt service bond issuance.
     * @param construction_time Duration of infrastructure construction.
     * @param bond_term_multiplier Number of payments to be made as a function of 
     * level debt service bond maturity date.
     * @param bond_interest_rate_multiplier Coupon rate as a function of the interest
     * paid on the level debt service bond.
     */
    void issueBond(int week, int construction_time, double bond_term_multiplier, double bond_interest_rate_multiplier) override;
};


#endif //TRIANGLEMODEL_LEVELDEBTSERVICEBOND_H
