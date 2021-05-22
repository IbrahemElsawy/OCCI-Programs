/*
-- ***********************
-- Name: Ibrahem Elsawy
-- ID: 157888199
-- Date: March 15, 2021
-- Purpose: Lab 06 DBS211
-- ***********************
*/

// SYSTEM HEADER FILES
#include <iostream>
#include <occi.h>
#include <iomanip>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

int main(void)
{
    /* OCCI Variables */
    Environment* env = nullptr;
    Connection* conn = nullptr;
    Statement* stmt = nullptr;

    /* Used Variables */
    string user = "dbs211_211c30";
    string pass = "17438101";
    string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";
    try {

        // OPEN SQL ENVIRONMENT 
        env = Environment::createEnvironment(Environment::DEFAULT);
        // OPEN SQL CONNECTION
        conn = env->createConnection(user, pass, constr);

        // OPEN STATEMENT
        stmt = conn->createStatement();
        // EXECUTES THE QUERY AND ASSIGNS IT TO rs
        ResultSet* rs = stmt->executeQuery("SELECT EMPLOYEENUMBER, FIRSTNAME, LASTNAME, PHONE, EXTENSION FROM EMPLOYEES LEFT JOIN OFFICES ON EMPLOYEES.OFFICECODE = OFFICES.OFFICECODE WHERE CITY = 'San Francisco' ORDER BY EMPLOYEENUMBER ASC FETCH FIRST 6 ROWS ONLY");

        // PRINTS THE HEADER OF THE QUERY RESULT
        cout << "-------------------------" << " Report 1 (Employee Report) " << "----------------------------------" << endl;

        cout << "Employee ID   " << "First Name         " << "Last Name          " << "Phone             " << "Extension         " << endl;

        cout << "------------  " << "-----------------  " << "-----------------  " << "----------------  " << "---------" << endl;

        // CONVERTS COLUMNS TO VARIABLES OF TYPE AND PRINTS THEM IN A CERTAIN ORDER
        while (rs->next()) {

            int empId = rs->getInt(1);
            string fname = rs->getString(2);
            string lname = rs->getString(3);
            string pNum = rs->getString(4);
            string exten = rs->getString(5);
            cout << left << setw(sizeof(empId) + 10) << empId << setfill(' ')
                << setw(sizeof(fname) - 13) << fname << setfill(' ')
                << setw(sizeof(lname) - 13) << lname << setfill(' ')
                << setw(sizeof(pNum) - 14) << pNum << setfill(' ')
                << exten << endl;
        }

        cout << endl; // PRINTS A NEW LINE

        // EXECUTES A QUERY AND ASSIGNS IT TO rs2
        ResultSet* rs2 = stmt->executeQuery("SELECT EMPLOYEENUMBER, FIRSTNAME, LASTNAME, PHONE, EXTENSION FROM EMPLOYEES LEFT JOIN OFFICES ON EMPLOYEES.OFFICECODE = OFFICES.OFFICECODE WHERE EMPLOYEENUMBER IN (1002, 1056, 1088, 1102, 1143, 1621) ORDER BY EMPLOYEENUMBER ASC FETCH FIRST 6 ROWS ONLY");

        // PRINTS THE HEADER OF THE QUERY RESULT
        cout << "-------------------------" << " Report 2 (Manager Report) " << "----------------------------------" << endl;

        cout << "Employee ID   " << "First Name         " << "Last Name          " << "Phone             " << "Extension         " << endl;

        cout << "------------  " << "-----------------  " << "-----------------  " << "----------------  " << "---------" << endl;

        // CONVERTS COLUMNS TO VARIABLES OF TYPE AND PRINTS THEM IN A CERTAIN ORDER
        while (rs2->next()) {

            int empId = rs2->getInt(1);
            string fname = rs2->getString(2);
            string lname = rs2->getString(3);
            string pNum = rs2->getString(4);
            string exten = rs2->getString(5);
            cout << left << setw(sizeof(empId) + 10) << empId << setfill(' ')
                << setw(sizeof(fname) - 13) << fname << setfill(' ')
                << setw(sizeof(lname) - 13) << lname << setfill(' ')
                << setw(sizeof(pNum) - 14) << pNum << setfill(' ')
                << exten << endl;
        }
    
        // TERMINATES STATEMENT
        conn->terminateStatement(stmt);
        // TERMINATES CONNECTION
        env->terminateConnection(conn);
        // TERMINATES ENVIRONMENT
        Environment::terminateEnvironment(env);
}

    // PRINTS THE ERROR IF THERE IS ONE
    catch (SQLException& sqlExcp) {

        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();

    }
        return 0;
}


