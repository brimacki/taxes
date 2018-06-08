//Make a function to convert double to dollar amount

#include<iostream>
#include<cmath>
#include<fstream>
#include<vector>

double medicareRate = 0.0145;
double socialSecurityRate = 0.062;
double personalExemption = 0;
double standardDeduction = 12000;
double maximumIncome = 1.0e9;

using namespace std;

int main(){

	cout << "What is your gross income to the nearest cent?" << endl;
	double grossIncome;
	cin >> grossIncome;
	cout << "This is your gross income: $" << grossIncome << endl;

	//The following function is a cool function to write eventually.
	/*int billions = grossIncome/1.0e9;
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
	}*/

	double medicareTaxes = medicareRate*grossIncome;
	cout << "These are your medicare taxes: $" << medicareTaxes << endl;
	double socialSecurityTaxes = socialSecurityRate*grossIncome;

	
	cout << "These are your social security taxes: $" << socialSecurityTaxes << endl;

	double federalTaxable = grossIncome - personalExemption - standardDeduction;
	cout << "This is your federal taxable income: $" << federalTaxable << endl;

	//Input federal brackets
	vector <string> familyTypes(4);
	familyTypes.at(0) = "Single";
	familyTypes.at(1) = "MFS";
	familyTypes.at(2) = "MFJ";
	familyTypes.at(3) = "HoH";
	cout << "Under what family classification are you filing? You must enter (case sensitive): 'Single', 'MFS', 'MFJ', or 'HoH'." << endl;
	string familyType;
	cin >> familyType;
	int familyID = -1;
	if(familyType == "Single"){
		familyID = 0;
	}
	else if(familyType == "MFS"){
		familyID = 1;
	}
	else if(familyType == "MFJ"){
		familyID = 2;
	}
	else if(familyType == "HoH"){
		familyID = 3;
	}
	else{
		cout << "You have failed to enter the correct family status identifier. Exiting now..." << endl;
	}

	cout << "familyID: " << familyID << endl;

	ifstream federalBrackets;
	federalBrackets.open("taxBrackets/federal2018.txt");
	if(!federalBrackets.is_open()){
		cout << "Could not open bracket definitions! Exiting now..." << endl;
	}

	int numBrackets;
	vector<double> minimum;
	vector<double> maximum;
	vector<double> percentage;
	for(int i = 0; i < familyID + 1; ++i){
		if(i == familyID){
			federalBrackets >> numBrackets;
			for(int j = 0; j < numBrackets; ++j){
				for(int k = 0; k < 3; ++k){
				}
			}
		}
		else{
			federalBrackets >> numBrackets;
			int numLoops = numBrackets*3;
			for(int j = 0; j < numBrackets*3; ++j){
			}
		}
	}

	//Calculate federal income tax

	return 0;
}
