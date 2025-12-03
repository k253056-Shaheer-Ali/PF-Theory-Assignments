#include<stdio.h>

float calculateRepayment(float loan, float interestRate, int years, float extraPayment){
	if(loan<=0 || years<=0){
		return 0;
	}
	float installment = 40000; //assuming fixed installment each year
	
	loan = (loan*interestRate) + loan;
	loan = loan - (installment+extraPayment);
	printf("Year %d: Remaining loan = %.2f\n", 4-years, loan);  //i minus 4 because years=3 
	
	return installment + extraPayment + calculateRepayment(loan, interestRate, years-1, extraPayment);
}

int main(){
	float loan = 100000;
	float interestRate = 0.05; //5%
	int years = 3;
	float extraPayment = 10000;   //just to fulfil question additional requiremnet
	
	float totalPaid = calculateRepayment(loan, interestRate, years, extraPayment);
	
	printf("\nTotal repayment over %d years = %.2f", years, totalPaid);
	return 0;
}

//last part of question:
//Extend the function logically to handle extra yearly payments and discuss why recursion is suitable for such incremental calculations.

//ANS: recursion is suitable for such incremental calculations because Each year's loan depends on the previous year's loan

//NOTE: I hardcoded extraPayment and installment (as it was not given in Q)

