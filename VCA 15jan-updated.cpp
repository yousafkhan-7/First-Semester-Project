#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <limits>
using namespace std;

int carYear, tireChanges, rechargeFrequency, exteriorChoice, rating = 100;
int menuChoice;
string province, exteriorCondition;
int fuelEfficiency;
char servicedRegularly, accidentHistory;

// Functions to handle input validation
int valid_numInput(int min, int max, string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < min || value > max) {
            cout << "\nERROR!! Please enter a valid number between " << min << " and " << max << endl;
            cin.clear(); // Used to clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discards unwanted characters
        } else {
            return value;
        }
    }
}

char valid_charInput(string& prompt, char opt1, char opt2) {
    char value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (value != opt1 && value != opt2 || cin.fail()) {
            cout << "\nERROR!! Please enter a valid option i.e, " << opt1 << " or " << opt2 << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else return value;
    }
}

string valid_strInput(string& prompt, string validOpt[], int optCount) {
    string value;
    while (true) {
        cout << prompt;
        cin >> value;
        for (int i = 0; i < optCount; i++) {
            if (value == validOpt[i])
                return value;
        }
        cout << "\nERROR!! Please enter a valid option:";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Function to show a progress bar
void ProgressBar() {
    cout << "\nAnalyzing your car's condition:\n";
    for (int i = 0; i <= 100; i += 10) {
        cout << "\033[93m["; // Yellow color
        for (int j = 0; j < 10; ++j) {
            if (j < i / 10)
                cout << "=";
            else
                cout << " ";
        }
        cout << "] " << i << "%\033[0m\r"; // Reset color
        this_thread::sleep_for(chrono::milliseconds(250));
    }
    cout << endl;
}

// Input
void userInput(int& carYear, int& tireChanges, int& rechargeFrequency, int& exteriorChoice, string& exteriorCondition, int& fuelEfficiency, char& accidentHistory, char& servicedRegularly) {

    // Declaring strings of variables
    string carYear_prompt = "\nEnter car model year: ";
    string fuelEfficiency_prompt = "\nEnter car average (fuel efficiency in km/L): ";
    string tireChanges_prompt = "\nEnter the number of tire changes: ";
    string rechargeFrequency_prompt = "\nHow often do you recharge the battery?\n[1] Every few days\n[2] Weekly\n[3] Monthly\n[4] Rarely\n \nEnter your choice: ";
    string accidentHistory_prompt = "\nHas the car experienced any accidents? (y/n): ";
    string servicedRegularly_prompt = "\nDo you service the car regularly? (y/n): ";
    string exteriorChoice_prompt = "\nWhat is the exterior condition of the car?\n[1] Rusted\n[2] Scratched\n[3] Excellent\n\nEnter your choice (1-3): ";
    cout << "\n----------------------------------------\n" << endl;

    // Assigning all the variables the validation function
    carYear = valid_numInput(1990, 2024, carYear_prompt);  // input car year with error validation
    cout << "\n----------------------------------------\n" << endl;
    fuelEfficiency = valid_numInput(1, 30, fuelEfficiency_prompt);
    cout << "\n----------------------------------------\n" << endl;
    tireChanges = valid_numInput(0, 10, tireChanges_prompt);
    cout << "\n----------------------------------------\n" << endl;
    rechargeFrequency = valid_numInput(1, 4, rechargeFrequency_prompt);
    cout << "\n----------------------------------------\n" << endl;
    accidentHistory = valid_charInput(accidentHistory_prompt, 'y', 'n');
    cout << "\n----------------------------------------\n" << endl;
    servicedRegularly = valid_charInput(servicedRegularly_prompt, 'y', 'n');
    cout << "\n----------------------------------------\n" << endl;
    exteriorChoice = valid_numInput(1, 3, exteriorChoice_prompt);
    cout << "\n----------------------------------------\n" << endl;
    if (exteriorChoice == 1)
        exteriorCondition = "rusted";
    else if (exteriorChoice == 2)
        exteriorCondition = "scratched";
    else
        exteriorCondition = "excellent";
}

// Function to calculate car rating
int calculateRating(int& carYear, int& tireChanges, int& rechargeFrequency, int& exteriorChoice, string& exteriorCondition, int& fuelEfficiency, char& accidentHistory, char& servicedRegularly, int rating) {

    ProgressBar(); // display progress bar function
    // Evaluate fuel efficiency
    if (fuelEfficiency > 20) {
        // No deduction
    } else if (fuelEfficiency >= 15) {
        rating -= 4;
    } else if (fuelEfficiency >= 10) {
        rating -= 8;
    } else {
        rating -= 13;
    }

    // Evaluate tire changes
    if (tireChanges > 1)
        rating -= 5;
    else if (tireChanges > 3)
        rating -= 8;

    // Evaluate recharge frequency
    switch (rechargeFrequency) {
        case 1: rating -= 0; break;
        case 2: rating -= 3; break;
        case 3: rating -= 6; break;
        case 4: rating -= 10; break;
    }

    // Evaluate accident history and service records
    if (accidentHistory == 'y') rating -= 10;
    if (servicedRegularly == 'n') rating -= 10;

    // Evaluate exterior condition
    if (exteriorCondition == "rusted")
        rating -= 10;
    else if (exteriorCondition == "scratched")
        rating -= 5;

    // Evaluate car year
    if (carYear >= 1990 && carYear <= 2000)
        rating -= 12;
    else if (carYear > 2000 && carYear <= 2010)
        rating -= 8;
    else if (carYear > 2010 && carYear <= 2020)
        rating -= 4;
    else if (carYear > 2020 && carYear <= 2022)
        rating -= 2;

    return max(rating, 0); // Ensure rating doesn't go below 0
}

// Function to display results
void displayResults(int rating) {
    char suggest;
    string tier;
    // Determine car tier based on rating
    if (rating >= 80)
        tier = "Excellent";
    else if (rating >= 70)
        tier = "Good";
    else if (rating >= 50)
        tier = "Average";
    else
        tier = "Poor";

    // Analyze and display result
    cout << "\n\033[1;36m----------------------------------------" << endl;
    cout << "\tVIRTUAL CAR ANALYSIS\t" << endl;
    cout << "----------------------------------------\033[0m" << endl;

    cout << "\nYour car rating: ";
    if (tier == "Excellent" || tier == "Good") {
        cout << "\033[1;32m" << rating << "/100 (" << tier << ")\033[0m\n";
    } else if (tier == "Average") {
        cout << "\033[1;34m" << rating << "/100 (" << tier << ")\033[0m\n";
    } else {
        cout << "\033[1;31m" << rating << "/100 (" << tier << ")\033[0m\n";
    }
    cout << "\n----------------------------------------\n" << endl;
    cout << "\nDo you want suggestions to improve your car's condition? (y/n): ";
    cin >> suggest;
    cout << "\n----------------------------------------\n" << endl;

    if (suggest == 'y') {
        // Suggestions based on user's choices
        cout << "\nSuggestions to improve your car's condition:\n";
        if (rating < 89) {
            if (carYear < 2020) {
                cout << "\033[95m- Upgrade your car model for a better rating.\n";
            }
            if (servicedRegularly == 'n') {
                cout << "- Regularly service your car.\n";
            }
            if (rechargeFrequency == 3 || rechargeFrequency == 4) {
                cout << "- Recharge the battery more frequently.\n";
            }
            if (fuelEfficiency < 10) {
                cout << "- Improve fuel efficiency by maintaining the engine and driving efficiently.\n";
            }
            if (exteriorCondition == "rusted" || exteriorCondition == "scratched") {
                cout << "- Address exterior issues like rust or scratches.\n";
            }
            if (tireChanges > 3) {
                cout << "- Replace tires if worn.\n";
            }
        } else {
            cout << "- Your car is in excellent condition! Keep maintaining it.\n";
        }
    }

    cout << "\n----------------------------------------\n" << endl;
}

// Location Services
void locationServices(string& province) {
    cout << "\n----------------------------------------\n" << endl;
    // Declaring string variables for validity function
    string province_prompt = "\nEnter your province: ";
    string validprovs[] = { "Punjab", "punjab", "Sindh", "sindh", "Balochistan", "balochistan", "Khyber pakhtunkhwa", "khyber pakhtunkhwa" };
    province = valid_strInput(province_prompt, validprovs, 8);
    cout << "\n----------------------------------------\n" << endl;
    // Displaying workshops
    cout << "\nNearest Workshops in " << province << ":\033[0m" << endl;
    if (province == "Punjab" || province == "punjab") {
        cout << "\033[3m1. Royal Auto.PK Auto Workshop (31.569865708839302, 74.42972078898427)" << endl;
        cout << "2. IQwheels (31.472021636352054, 74.29475626715406)" << endl;
        cout << "3. Tahir Motor Workshop (31.42890627002953, 73.09110428249656)" << endl;
    } else if (province == "Sindh" || province == "sindh") {
        cout << "1. Usama Automotive Workshop (24.907252079432062, 67.06093424686144)" << endl;
        cout << "2. Cars Garage (24.862806198179836, 67.08632315155356)" << endl;
        cout << "3. RoadRunner AutoService (24.845444251115154, 67.05265352456938)\033[0m" << endl;
    } else if (province == "Balochistan" || province == "balochistan") {
        cout << "1. Rahuf Ustad Workshop (30.33650477629199, 68.5750062756085)" << endl;
        cout << "2. Sarwan Workshop (30.41957578029219, 66.93792540474018)" << endl;
        cout << "3. Kech AutoGarage (26.224831569726696, 63.02547058541784)\033[0m" << endl;
    } else if (province == "Khyber Pakhtunkhwa" || province == "khyber pakthunkhwa") {
        cout << "1. Hazara Autos Workshop (34.04167865544165, 72.94499144919025)" << endl;
        cout << "2. Iftikhar Automechanic (34.07137601788552, 71.60460020198447)" << endl;
        cout << "3. Wajid Khan Auto Workshop (34.03496652517371, 71.56065488942957)\033[0m" << endl;
    }
}

// Main menu
int menu(int menuChoice) {
    menuChoice = 0;
    cout << "\nWelcome!!!! What do you want to do" << endl;
    string menuChoice_prompt = "\n1. Virtual Car Analysis \n2. Location Services \n3. Exit \nPlease enter your choice: ";
    menuChoice = valid_numInput(1, 3, menuChoice_prompt);

    switch (menuChoice) {
        case 1:
            cout << "\nWelcome to Car Analysis!! Please enter the following details to calculate your car rating." << endl;
            // Calls 3 functions
            userInput(carYear, tireChanges, rechargeFrequency, exteriorChoice, exteriorCondition, fuelEfficiency, accidentHistory, servicedRegularly);
            // Stores return type value of calculateRating function in rating variable which is then passed to displayRating function
            rating = calculateRating(carYear, tireChanges, rechargeFrequency, exteriorChoice, exteriorCondition, fuelEfficiency, accidentHistory, servicedRegularly, rating);
            displayResults(rating);
            break;
        case 2:
            locationServices(province);
            break;
        case 3:
            return 0;
    }
    return 1;
}

// Main function
int main() {
    while (true) {
        cout << "\n\033[1;93m----------------------------------------" << endl;
        cout << "\tVIRTUAL CAR ANALYST\t" << endl;
        cout << "----------------------------------------\033[0m\n";
        // User inputs
        menu(menuChoice);

        // Restart or exit
        char choice;
        string choice_prompt = "Do you want to restart? (y/n): ";
        choice = valid_charInput(choice_prompt, 'y', 'n');
        if (choice != 'y')
            break;
    }

    return 0;
}

