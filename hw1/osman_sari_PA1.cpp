#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

// Function declarations
void randomNumberGenerate(int numberOfDigits);
void game(int number[], int numberOfDigits);

int main(int argc, char* argv[])
{
    // Check if the first argument is missing
    if (argv[1] == nullptr || argv[2] == nullptr) {
        cout <<"E0" << endl; // Print error message
        exit(1); // Exit the program
    }
    // Check if the second argument is not a number
    if (argv[2][0] <='0' || argv[2][0]>'9') {
        cout <<"E0" << endl; // Print error message
        exit(1); // Exit the program
    }
    
    int numberOfDigits, i, j;
    // Generate a random number
    if (argv[1][0] == '-' && argv[1][1] == 'r') {
        numberOfDigits = atoi(argv[2]); // Convert string to integer
        randomNumberGenerate(numberOfDigits); // Call the function to generate a random number
    }
    // Play the game with a user-defined number
    else if (argv[1][0] == '-' && argv[1][1] == 'u') {
        numberOfDigits = strlen(argv[2]); // Get the length of the user-defined number
        // Check if the user-defined number contains non-digit characters
        for (i = 0; i < numberOfDigits; i++) {
            if (argv[2][i] < '0' || argv[2][i] > '9') {
                cout <<"E0" << endl; // Print error message
                exit(1); // Exit the program
            }
            // Check if the user-defined number contains duplicate digits
            for (j = numberOfDigits - 1; j > i; j--) {
                if (argv[2][i] == argv[2][j]) {
                    cout <<"E0" << endl; // Print error message
                    exit(1); // Exit the program
                }
            }
        }
        int number[numberOfDigits];
        // Convert the user-defined number to an array of integers
        for (i = 0; i < numberOfDigits; i++)
            number[i] = int(argv[2][i] - 48);
        // Call the game function with the user-defined number
        game(number, numberOfDigits);
    }
    // Print error message for invalid argument
    else {
        cout <<"E0" << endl;
        exit(1);
    }
    
    return 0;
}

// Function to generate a random number
void randomNumberGenerate(int numberOfDigits) {
    int const N = 10;
    int i, j;
    srand(time(NULL));
    int number[numberOfDigits];
    // Check if the number of digits is greater than 9
    if (numberOfDigits > 9) {
        cout <<"E0" << endl; // Print error message
        exit(1); // Exit the program
    }
    // Generate a random number without duplicates
    for (i = 0; i < numberOfDigits; i++) {
        number[i] = rand() % N;
        if (number[0] == 0)
            number[0] = rand() % N;
        if (i > 0) {
            j = i - 1;
            while (j >= 0) {
                if (number[i] == number[j]) {
                    number[i] = rand() % N;
                    j = i;
                }
                j--;
            }
        }
    }
    game(number,numberOfDigits);
}
// Function to play the game
void game(int number[],int numberOfDigits){
    int i,j,count1=0,count2=0,gameCount=0,userLen,spaceCounter=0;
    char userNumber[10];
    int uNumber[numberOfDigits];
    do {
        // Prompt the user to enter a number
        cin >> userNumber;
        userLen = strlen(userNumber);
        gameCount++;

        // Remove leading spaces from user input
        for (i = 0; i < userLen; i++) {
            if (userNumber[i] == ' ') {
                userNumber[i] = userNumber[i + 1];
                spaceCounter++;
            } else
                break;
        }

        numberOfDigits -= spaceCounter;

        // Check for errors in user input
        if (userNumber[0] == '0' || userNumber[0] == '-') {
            cout << "E0" << endl;
            exit(1);
        }

        for (i = 0; i < userLen; i++) {
            if (userNumber[i] < '0' || userNumber[i] > '9') {
                cout << "E2" << endl;
                exit(1);
            }
        }

        if (userLen != numberOfDigits) {
            cout << "E1" << endl;
            exit(1);
        } else if (userLen = numberOfDigits) {
            // Convert user input into an integer array
            count1 = 0;
            count2 = 0;

            for (i = 0; i < numberOfDigits; i++) {
                uNumber[i] = int(userNumber[i] - 48);
            }

            // Check for duplicate digits in user input
            for (i = numberOfDigits - 1; i > -1; i--) {
                for (j = 0; j < i; j++) {
                    if (uNumber[i] == uNumber[j]) {
                        cout << "E0" << endl;
                        exit(1);
                    }
                }
            }

            // Calculate count1 and count2
            for (i = 0; i < numberOfDigits; i++) {
                if (uNumber[i] == number[i]) {
                    count1++;
                }

                for (int j = 0; j < numberOfDigits; j++) {
                    if (uNumber[i] == number[j] && i != j)
                        count2++;
                }
            }

            // Check if the user has guessed the correct number or not
            if (count1 == numberOfDigits)
                cout << "FOUND " << gameCount << endl;
            else
                cout << count1 << " " << count2 << endl;

            // Check if the user has exceeded the maximum number of tries
            if (gameCount == 100)
                cout << "FAILED" << endl;
        } else {
            cout << "E1" << endl;
            exit(1);
        }
    } while (count1 != numberOfDigits || gameCount == 100);
}

