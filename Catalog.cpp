#include <iostream>
#include <vector>
#include <string>
#include <map>
 #include <jsoncpp/json/json.h>
#include <cmath>
#include<bits/stdc++.h>
using namespace std;
using json = nlohmann::json;

// Function to convert a number from a given base to decimal
int convertToDecimal(const string& value, int base) {
    int decimalValue = 0;
    int power = 1;

    for (int i = value.size() - 1; i >= 0; --i) {
        char digit = value[i];
        int digitValue = (digit >= '0' && digit <= '9') ? (digit - '0') : (digit - 'a' + 10);
        decimalValue += digitValue * power;
        power *= base;
    }

    return decimalValue;
}



// Function to calculate the constant term using Lagrange interpolation
int calculateConstantTerm(const json Data) {
    int l=0;
    int n = Data["keys"]["n"];
    int c = 0; // The constant term

    vector<pair<float,float>> cordinates(n);

    for(auto i:Data)
    {
        if(i.isMember("Base"))
        {
            coordinates[l].first = stoi(i["Base"]);
            string hexString = i["Value"]; // Example hexadecimal string
            try {
                // Convert hex string to unsigned long long integer
                unsigned long long integerValue = stoull(hexString, nullptr, 16);
            }
            catch (const std::invalid_argument& e) {
                cerr << "Invalid argument: " << e.what() << endl;
            }
            catch (const std::out_of_range& e) {
                    cerr << "Out of range: " << e.what() << endl;
            }
            l++;
        }
    }

    // Evaluate polynomial at x = 0 using Lagrange interpolation formula
    for(auto i:coordinates)
    {
        float xi = i.first;
        float yi = i.second;

        float yi = log(yi)/log(xi);
        int term = yi;

        for (auto j:coordinates) {
            if (!(i.isEquals(j))) {
                term *= -j.first;
                term /= (xi - j.first);
            }
        }

        c += term;
    }
    return c;
}

int main() {
    // Sample JSON input
    /*string jsonString = R"({
        "keys": {
            "n": 4,
            "k": 3
        },
        "1": {
            "base": "10",
            "value": "4"
        },
        "2": {
            "base": "2",
            "value": "111"
        },
        "3": {
            "base": "10",
            "value": "12"
        },
        "6": {
            "base": "4",
            "value": "213"
        }
    })";*/

    // Parse JSON
    ifstream catalog_file("Enter_File_Name",ifstream::binary);
    json catalog;
    catalog_file >> catalog;

    // Calculate the constant term
    int constantTerm = calculateConstantTerm(catalog);

    // Output the result
   cout << "The constant term is: " << constantTerm <<endl;

    return 0;
}
