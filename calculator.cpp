//Make a function to convert double to dollar amount

#include<iostream>
#include<cmath>
#include<fstream>
#include<vector>

double medicareRate = 0.0145;
double socialSecurityRate = 0.062;
double personalExemption = 0.0;
double standardDeduction = 12000.0;
double maximumIncome = 1.0e9;

using namespace std;

int main(){

	cout << "What is your gross earned income to the nearest cent?" << endl;
	double grossIncome;
	cin >> grossIncome;
	//cout << "This is your gross income: $" << grossIncome << endl;

	//The following is a cool function to write eventually.
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
	if(federalTaxable < 0){
		federalTaxable = 0;
		cout << "You owe no taxes this year because your deductions and exemptions exceed your earned income." << endl;
		exit(-1);
	}
	cout << "This is your federal taxable income: $" << federalTaxable << endl;

	//Determine family status
	vector <string> familyTypes(4);
	familyTypes.at(0) = "Single";
	familyTypes.at(1) = "MFS";
	familyTypes.at(2) = "MFJ";
	familyTypes.at(3) = "HoH";
	cout << "Under what family classification are you filing? You must enter (case sensitive): 'Single', 'MFS', 'MFJ', or 'HoH'." << endl;
	string familyType;
	cin >> familyType;
	int familyID;
	if(familyType == "Single"){
		familyID = 0;
		cout << "Your tax bracket will be determined based on the single marital status." << endl;
	}
	else if(familyType == "MFS"){
		familyID = 1;
		cout << "Your tax bracket will be determined based on the married filing separately status." << endl;
	}
	else if(familyType == "MFJ"){
		familyID = 2;
		cout << "Your tax bracket will be determined based on the married filing jointly status." << endl;
	}
	else if(familyType == "HoH"){
		familyID = 3;
		cout << "Your tax bracket will be determined based on the Head of Household status." << endl;
	}
	else{
		cout << "You have failed to enter the correct family status identifier. Exiting now..." << endl;
	}

	//Determine tax brackets
	ifstream federalBrackets;
	federalBrackets.open("taxBrackets/federal2018.txt");
	if(!federalBrackets.is_open()){
		cout << "Could not open bracket definitions! Exiting now..." << endl;
	}

	int numBrackets;
	vector<double> minimum;
	vector<double> maximum;
	vector<double> percentage;
	double value;
	for(int i = 0; i < familyID + 1; ++i){
		if(i == familyID){
			federalBrackets >> numBrackets;
			for(int j = 0; j < numBrackets; ++j){
				federalBrackets >> value;
				minimum.push_back(value);
				if(j < numBrackets - 1){
					federalBrackets >> value;
					maximum.push_back(value);
				}
				federalBrackets >> value;
				percentage.push_back(value);					
			}
		}
		else{
			federalBrackets >> numBrackets;
			int numLoops = numBrackets*3;
			for(int j = 0; j < numLoops - 1; ++j){
				federalBrackets >> value;
			}
		}
	}

	int index;
	for(int i = 0; i < maximum.size(); ++i){
		if(maximum.at(i) > federalTaxable){
			index = i;
			break;
		}
	}

	cout << "This is your marginal tax percentage: " << percentage.at(index)*100.0 << "%" << endl;

	double federalIncomeTax = 0.0;
	for(int i = 0; i < index; ++i){
		federalIncomeTax += percentage.at(i)*(maximum.at(i) - minimum.at(i));
	}
	federalIncomeTax += percentage.at(index)*(federalTaxable - minimum.at(index));
	cout << "This is your federal income tax: $" << federalIncomeTax << endl;

	return 0;
}
