/**
 * @author Bernardo Trindade
 * @date 04/12/2018
 */

#ifndef TRIANGLEMODEL_BONDFINANCING_H
#define TRIANGLEMODEL_BONDFINANCING_H

#include <vector>
#include "../../../Utils/Constants.h"

using namespace std;
using namespace Constants;

class Bond {
private:

    /**
     * False while the bond is not issued. True when the bond is issued.
     */ 
    bool issued = false;

protected:
    /**
     * Week in which the bond is issued.
     */
    int week_issued;

    /** 
     * Repayment delay.
     * If bond is to start being paid for at issuance, set repayment delay to 0.
     * Otherwise, begin bond repayment at issuance.
     */
    int begin_repayment_after_n_years = NON_INITIALIZED;

    /** 
     * Yield paid on a bond by its issuer.
     */
    double coupon_rate;

    /**
     * Construction cost of capital for the bond.
     */
    double cost_of_capital;

    /**
     * Number of payments to be made on an issued bond.
     */
    int n_payments;

public:
    /**
     * Type of bond issued.
     */
    const int type;

    /**
     * Weeks on which bonds payments are issued.
     */
    const vector<int> pay_on_weeks;

    /** 
     * Bond identification number.
     */
    const int id;

    /** 
     * Bond object constructor.
     * 
     * @param id Bond identification number.
     * @param cost_of_capital Construction cost of capital for the bond.
     * @param n_payments Number of payments to be made on an issued bond.
     * @param pay_on_weeks Weeks on which bond payments are issued.
     * @param type Type of bond.
     * @param begin_repayment_at_issuance Repayment delay. 
     * If bond is to start being paid for at issuance, set repayment delay to 0.
     * Otherwise, begin bond repayment at issuance.
     * 
     * @throws invalid_argument(error.c_str()) Thrown if construction cost of capital 
     * for the bond is invalid.
     */
    Bond(const int id, const double cost_of_capital, const int n_payments, vector<int> pay_on_weeks,
                  const int type, bool begin_repayment_at_issuance = false);


    /** 
     * Bond object constructor.
     * 
     * @param id Bond identification number.
     * @param cost_of_capital Construction cost of capital for the bond.
     * @param n_payments Number of payments to be made on an issued bond.
     * @param pay_on_weeks Weeks on which bond payments are issued.
     * @param coupon_rate Yield paid on a bond by its issuer.
     * @param type Type of bond.
     * @param begin_repayment_at_issuance Repayment delay. 
     * If bond is to start being paid for at issuance, set repayment delay to 0.
     * Otherwise, begin bond repayment at issuance.
     * 
     * @throws invalid_argument(error.c_str()) Thrown if construction cost of capital 
     * for the bond is invalid.
     */
    Bond(const int id, const double cost_of_capital, const int n_payments, vector<int> pay_on_weeks,
         const double coupon_rate, const int type, bool begin_repayment_at_issuance = false);

    /**
     * Default constructor.
     */
    Bond();

    /**
     * Destructor.
     */
    virtual ~Bond();

    /**
     * Reference to the default Bond object.
     */
    Bond(const Bond&) = default;

    /**
     * Gets the debt service ratio for a given week.
     * @param week Week of bond issuance.
     * 
     * @returns The debt service ratio.
     */
    virtual double getDebtService(int week) = 0;

    /**
     * Gets the net present value of the bond at the date of issuance.
     * Has default value of 0. 
     * @param discount_rate Interest rate paid on the bond.
     * @param week Week of bond issuance.
     * 
     * @returns The net present value of the bond at the date of issuance.
     */
    virtual double getNetPresentValueAtIssuance(double discount_rate, int week) const = 0;

    /**
     * Sets the date to begin repayment of the bond.
     * 
     * @param week Week in the of bond issuance.
     * @param construction_time Duration of infrastructure construction.
     * @param bond_term_multiplier The number of payments to be made as a function of 
     * the bond maturity date.
     * @param bond_interest_rate_multiplier The coupon rate as a function of the interest
     * paid on the bond.
     */
    virtual void
    issueBond(int week, int construction_time, double bond_term_multiplier, double bond_interest_rate_multiplier);

    /**
     * Sets the cost of capital based on the RDM table of the corresponding state of the world.
     * Only cost of capital RDM multiplier is applied here because in a joint project, 
     * it is assumed any cost overruns would be split among the utilities. 
     * Interest and bond term, on the other hand, are utility dependent are set at issuance, 
     * in function issueBond.
     * 
     * @param r Realization or state of the world.
     * @param rdm_factors Vector of rdm factors corresponding to realization r. 
     */
    virtual void setRealizationWaterSource(unsigned long r, vector<double> &rdm_factors);

    /**
     * Obtains the bond issuance status.
     * 
     * @returns True if the bond has been issued. False otherwise.
     */
    bool isIssued() const;

    /**
     * Sets the bond issuance status to true.
     */
    void setIssued();

    /**
     * Gets the bond coupon rate.
     * 
     * @returns The bond coupon rate.
     */
    double getCouponRate() const;

    /**
     * Gets the construction cost of capital for the bond.
     * 
     * @returns The costruction cost of capital for the bond.
     */
    double getCostOfCapital() const;

    /**
     * Gets the number of payments to be made to the bond.
     * 
     * @returns The number of payments to be made to the bond.
     */
    int getNPayments() const;

};


#endif //TRIANGLEMODEL_BONDFINANCING_H
