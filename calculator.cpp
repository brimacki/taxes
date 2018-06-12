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

int getFamilyType();
double federalTax(double federalTaxable, int familyID);
double flatStateTax(double grossIncome);
int reporting(double gross, double medicare, double socialSecurity, double federalIncome, double federal, double state);

int main(){

	//Gross income
	cout << "What is your gross earned income to the nearest cent?" << endl;
	double grossIncome;
	cin >> grossIncome;

	//Other deductions
	cout << "How much are you contributing to a pre-tax retirement account?" << endl;
	double retirementDeductions;
	cin >> retirementDeductions;

	//Regressive taxes
	double medicareTaxes = medicareRate*grossIncome;
	double socialSecurityTaxes = socialSecurityRate*grossIncome;

	//Filing status
	double federalTaxable = grossIncome - personalExemption - standardDeduction - retirementDeductions;
	int familyID = getFamilyType();

	//Progressive taxes
	double federalTaxes = federalTax(federalTaxable, familyID);
	double stateTaxes = flatStateTax(grossIncome);

	//Report results
	int status = reporting(grossIncome, medicareTaxes, socialSecurityTaxes, federalTaxable, federalTaxes, stateTaxes);

	return 0;
}

int getFamilyType(){
	vector <string> familyTypes;
	familyTypes.push_back("Single");
	familyTypes.push_back("MFS");
	familyTypes.push_back("MFJ");
	familyTypes.push_back("HoH");

	cout << "Under what family classification are you filing? You must enter (case sensitive): 'Single', 'MFJ', 'MFS', or 'HoH'." << endl;
	string familyType;
	cin >> familyType;
	int status;
	if(familyType == "Single"){
		status = 0;
	}
	else if(familyType == "MFJ"){
		status = 1;
	}
	else if(familyType == "MFS"){
		status = 2;
	}
	else if(familyType == "HoH"){
		status = 3;
	}
	else{
		cout << "You have failed to enter the correct family status identifier. Exiting now..." << endl;
	}
	return status;
}

double federalTax(double income, int familyID){
	ifstream federalBrackets;
	federalBrackets.open("taxBrackets/federal2018.txt");
	if(!federalBrackets.is_open()){
		cout << "Could not open bracket definitions! Check that the 'taxBrackets/federal2018.txt' file exists. Exiting now..." << endl;
		exit(-1);
	}
	int numBrackets;
	vector<double> minimum, maximum, percentage;
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
	federalBrackets.close();

	int index;
	for(int i = 0; i < maximum.size(); ++i){
		if(maximum.at(i) > income){
			index = i;
			break;
		}
	}

	cout << "This is your marginal tax percentage: " << percentage.at(index)*100.0 << "%" << endl;

	double federalIncomeTax = 0.0;
	for(int i = 0; i < index; ++i){
		federalIncomeTax += percentage.at(i)*(maximum.at(i) - minimum.at(i));
	}
	federalIncomeTax += percentage.at(index)*(income - minimum.at(index));

	return federalIncomeTax;
}

double flatStateTax(double income){
	char state[2], filename[50];
	double statePercentage, personalStateExemption;
	int numExemptions;
	cout << "Enter the two character acronym for your state. For example, if you live in Illinois enter 'IL'." << endl;
	cin >> state;
	sprintf(filename, "taxbrackets/%s2018.txt", state);
	ifstream stateInfo;
	stateInfo.open(filename);
	if(!stateInfo.is_open()){
		cout << "Could not open bracket definitions! Check that the 'taxBrackets/[state]2018.txt' file exists. Exiting now..." << endl;
		exit(-1);
	}
	stateInfo >> personalStateExemption;
	stateInfo >> statePercentage;
	stateInfo.close();
	cout << "How many personal state exemptions will you claim?" << endl;
	cin >>  numExemptions;
	return statePercentage*(income - numExemptions*personalStateExemption);
}

int reporting(double gross, double medicare, double socialSecurity, double federalIncome, double federal, double state){

	ofstream report("Tax Info.txt");
	report << "This is your gross income: $" << gross << endl;
	report << "These are your medicare taxes: $" << medicare << endl;
	report << "These are your social security taxes: $" << socialSecurity << endl;
	report << "This is your federal taxable income: $" << federalIncome << endl;
	report << "This is your household's federal income tax: $" << federal << endl;
	report << "This is your household's state income tax: $" << state << endl;
	report << "These are the total taxes you will pay: $" << medicare + socialSecurity + federal + state << endl;
	report << "... and as a percentage of your gross income: " << (medicare + socialSecurity + federal + state)/gross*100.0 << "%" << endl;
	report.close();

	return 0;
}
