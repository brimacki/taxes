//Make a function to convert double to dollar amount

#include<iostream>
#include<cmath>

double medicareRate = 0.0145;
double socialSecurityRate = 0.062;
double personalExemption = 0;
double standardDeduction = 12000;

using namespace std;

int main(){

	cout << "What is your gross income to the nearest cent?" << endl;
	double grossIncome;
	cin >> grossIncome;
	cout << "This is your gross income: $";
	int billions = grossIncome/1.0e9;
	if(billions > 0){
		cout << billions << ",";
	}
	int millions = (grossIncome - billions*1.0e9)/1.0e6;
	if(millions > 0){
		cout << millions << ",";
	}
	int thousands = (grossIncome - billions*1.0e9 - millions*1.0e6)/1.0e3;
	if(thousands > 0){
		cout << thousands << ",";
	}
	int ones = (grossIncome - billions*1.0e9 - millions*1.0e6 - thousands*1.0e3)/1.0e0;
	if(ones > 0){
		cout << ones << ".";
	}
	double cents = (grossIncome - billions*1.0e9 - millions*1.0e6 - thousands*1.0e3 - ones)*100;
	if(cents > 0){
		cout << cents << "." << endl;
	}

	double federalTaxable = grossIncome - personalExemption - standardDeduction;

	cout << "This is your federal taxable income: " << federalTaxable << endl;

	double medicareTaxes = medicareRate*grossIncome;
	double socialSecurityTaxes = socialSecurityRate*grossIncome;

	cout << "These are your medicare taxes: " << medicareTaxes << endl;
	cout << "These are your social security taxes: " << socialSecurityTaxes << endl;

	return 0;
}
