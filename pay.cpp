#include "person.cpp"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

vector<Person> readData(ifstream& iFile,vector<Person>& emp);
vector<string> getCompanies(vector<string>& compName, vector<Person>& emp);
void printHighestPaid(vector<Person>& emp);
void separateAndSave(vector<string>& compName, vector<Person>& emp );

int main(int argc, char *argv[])
{vector <Person> employees;
 vector <string> companyNames;
 ifstream inFile("input.txt");
 readData(inFile, employees);
 inFile.close();
 getCompanies(companyNames,employees);
 printHighestPaid(employees);
 separateAndSave(companyNames, employees);
 return 0;

}

vector<Person> readData(ifstream& iFile,vector<Person>& emp)
{ 
  string fname;
  string lname;
  int id;
  float hour;
  float pay;
  string comName;
  int count = 0;
  Person person;

        while(iFile >> fname >> lname >> id >> comName >> pay >> hour)
        {      
		person.setFirstName(fname);
		person.setLastName(lname);
		person.setEmployeeId(id);
		person.setCompanyName(comName);
		person.setPayRate(pay);
		person.setHoursWorked(hour);
		emp.push_back(person);
		count++;
	}
	return emp; 

} 

vector<string> getCompanies(vector<string>& compName, vector<Person>& emp)
	{	
		for(int i =0; i < emp.size(); i++)
		{
			compName.push_back(emp[i].getCompanyName());
		}
		sort(compName.begin(), compName.end());
		compName.erase(unique(compName.begin(), compName.end()), compName.end());
	return compName;	
	}
void printHighestPaid(vector<Person>& emp)
{	float high = 0.00;

	for(int i= 0; i < emp.size(); i++)
	{
		if(high < emp[i].totalPay())
		{
			high = emp[i].totalPay();
		}
	}
	for(int i = 0; i < emp.size(); i++)
	{
		if(high == emp[i].totalPay())
		{
			cout << "Highest paid:  "<<  emp[i].fullName() << endl;
			cout <<"Employee ID: "<< emp[i].getEmployeeId() << endl;
			cout << "Employer: " << emp[i].getCompanyName() << endl;
			cout <<"Total Pay: "<< "$" << fixed << setprecision(2) << emp[i].totalPay() << endl;
		}
	}

}

void separateAndSave(vector<string>& compName, vector<Person>& emp)
{	
	string fileName;
	for(int i= 0; i < compName.size(); i++)
	{	float totalPay = 0.00;
		fileName = compName[i];
		ofstream outFile(fileName + ".txt");
		outFile << "____Employee Name____________Employee ID____________Company Name______________Pay_______" << endl;
		outFile << endl;
		for(int j = 0; j < emp.size(); j++)
		{
			if(emp[j].getCompanyName() == fileName)
			{
				outFile << emp[j].fullName() << "\t\t\t"
				       	<< emp[j].getEmployeeId() << "\t\t\t "
				       	<< emp[j].getCompanyName() << "\t\t"
					<< " $"<< fixed << setprecision(2) << emp[j].totalPay() << endl;
				totalPay += emp[j].totalPay();
			}
				
		}
		outFile << endl;
		outFile << "\tTotal Pay: $" << fixed << setprecision(2) << totalPay;
		outFile.close();
	}
  

}

