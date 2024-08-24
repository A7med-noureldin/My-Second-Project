// Author: Ahmed Noureldin

//  program :   This program is a collection of 3 ciphers required in the assignment  with a menu interface
//  to make the user choose the cipher he wants

//CODE

#include <bits/stdc++.h>

using namespace std;

// Function declarations
void simpleSubcypharEncrypt();
void simpleSubCypharDecryprtion();
void XOR_ecryption();
void XOR_decryption();
string railFenceCipherEncrypt(string input, int key);
string railFenceCipherDecrypt(string input, int key);

// Function to handle user input and choice validation
int taking_choice(int range) {
    int choice;
    while (true) {
        try {
            cout << "Enter your choice: ";
            cin >> choice;
            if (cin.fail()) {
                cin.clear(); // Clear the fail state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard remaining characters
                throw runtime_error("Invalid input. Please enter an integer.");
            }
        } catch (exception& e) {
            cout << e.what() << endl; // Print error message
        }
        if (choice < 1 || choice > range) {
            cout << "Choice must be in range of 1 and " << range << endl;
            continue;
        }
        break;
    }
    return choice;
}

// Main function with menu interface
int main() {
    while (true) {
        // Display menu options
        cout << "Choose cipher:" << endl
             << "1) Rail fence cipher" << endl
             << "2) XOR cipher" << endl
             << "3) Simple sub cipher" << endl
             << "4) End" << endl;

        // Take user's choice for cipher type
        int choice = taking_choice(4);
        if (choice == 1) {
            // Rail fence cipher option
            cout << "Select a choice below: " << endl
                 << "1) Encrypt" << endl
                 << "2) Decrypt" << endl;

            // Take user's choice for encrypting or decrypting
            int cypharChoice = taking_choice(2);
            int key;
            while (true) {
                cout << "Please enter the key: ";
                try {
                    cin >> key;
                    if (cin.fail()) {
                        cin.clear(); // Clear the fail state
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard remaining characters
                        throw runtime_error("Invalid input. Please enter an integer.");
                    }
                } catch (exception& e) {
                    cout << e.what() << endl; // Print error message
                }
                if (key <= 1 || key > 30) {
                    cout << "Key must be higher than 1 and smaller than or equal to 30" << endl;
                    continue;
                }
                break;
            }
            if (cypharChoice == 1) {
                cout << "Please enter the message: ";
                string input;
                cin.ignore();
                getline(cin, input);
                string encrypted = railFenceCipherEncrypt(input, key);
                cout << "Encrypted message is: " << encrypted << endl;
            } else {
                cout << "Please enter the encrypted message: ";
                string input;
                cin.ignore();
                getline(cin, input);
                string decrypted = railFenceCipherDecrypt(input, key);
                cout << "Decrypted message is: " << decrypted << endl;
            }
        } else if (choice == 2) {
            // XOR cipher option
            cout << "Select a choice below: " << endl
                 << "1) Encrypt" << endl
                 << "2) Decrypt" << endl;

            // Take user's choice for encrypting or decrypting
            int cypharChoice = taking_choice(2);
            if (cypharChoice == 1) {
                XOR_ecryption();
            } else {
                XOR_decryption();
            }
        } else if (choice == 3) {
            // Simple substitution cipher option
            cout << "Select a choice below: " << endl
                 << "1) Encrypt" << endl
                 << "2) Decrypt" << endl;

            // Take user's choice for encrypting or decrypting
            int cypharChoice = taking_choice(2);
            if (cypharChoice == 1) {
                simpleSubcypharEncrypt();
            } else {
                simpleSubCypharDecryprtion();
            }
        } else {
            // End the program
            break;
        }
    }
    return 0;
}

// Rail Fence Cipher Encryption Function
string railFenceCipherEncrypt(string input, int key) {
    string newS; // String to store the encrypted text
    string modInput; // Modified input string with only alphabetic characters

    // Modify the input string to contain only lowercase alphabetic characters
    for (int i = 0; i < input.size(); i++) {
        if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) {
            modInput += tolower(input[i]);
        }
    }

    int row = 0;
    int increment = 1;
    char grid[key][modInput.size()]; // Initialize the grid for encryption

    // Populate the grid with '.' characters
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < modInput.size(); j++) {
            grid[i][j] = '.';
        }
    }

    // Fill the grid with characters from the modified input string
    for (int i = 0; i < modInput.size(); i++) {
        grid[row][i] = modInput[i];
        row += increment;
        // Reverse direction when reaching the top or bottom rail
        if (row == key - 1 || row == 0) {
            increment = -increment;
        }
    }

    // Read the encrypted characters from the grid to form the encrypted string
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < modInput.size(); j++) {
            if (grid[i][j] != '.') {
                newS += grid[i][j];
            }
        }
    }

    return newS; // Return the encrypted string
}

// Rail Fence Cipher Decryption Function
string railFenceCipherDecrypt(string input, int key) {
    char grid[key][input.size()]; // Initialize the grid for decryption

    // Populate the grid with '.' characters
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < input.size(); j++) {
            grid[i][j] = '.';
        }
    }

    int row = key;
    int column = 0;
    int firstWay = row * 2 - 2;
    int secondWay = row * 2 - 2;
    bool choice = false;

    // Fill the grid with characters from the input string
    for (int i = 0; i < input.size(); i++) {
        if (grid[key - row][column] == '.') {
            grid[key - row][column] = input[i];
            if (!choice) {
                column += firstWay;
            } else {
                column += secondWay;
            }
            choice = !choice;

            if (column >= input.size()) {
                row--;
                column = key - row;
                if (row == 1) {
                    firstWay = key * 2 - 2;
                    secondWay = key * 2 - 2;
                } else {
                    firstWay = row * 2 - 2;
                    secondWay = (key - row) * 2;
                }
                choice = false;
            }
        } else {
            column++;
            i--;
        }
    }

    string newS;
    row = 0;
    int increment = 1;
    // Read the encrypted characters from the grid to form the decrypted string
    for (int i = 0; i < input.size(); i++) {
        newS += grid[row][i];
        row += increment;
        if (row == key - 1 || row == 0) {
            increment = -increment;
        }
    }
    return newS; // Return the decrypted string
}

// Simple Substitution Cipher Encryption Function
void simpleSubcypharEncrypt() {
    string key;
    cout << "Please enter the key (5 alphabet letters): ";
    cin >> key;

    // Validate the key to ensure it contains only alphabetic characters
    while (key.size() != 5 || !all_of(key.begin(), key.end(), ::isalpha)) {
        cout << "Please enter a valid key (5 alphabet letters): ";
        cin >> key;
    }

    // Arrays to store alphabet and cipher alphabet
    char plain_alpha[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char cipher_alpha[26] = {tolower(key[0]), tolower(key[1]), tolower(key[2]), tolower(key[3]), tolower(key[4])};

    // Add the remaining elements of the cipher alphabet
    int index = 5;
    for (int i = 0; i < 26; i++) {
        if (find(begin(cipher_alpha), end(cipher_alpha), plain_alpha[i]) == end(cipher_alpha)) {
            cipher_alpha[index++] = plain_alpha[i];
        }
    }

    string message;
    cout << "Please enter the message: ";
    cin.ignore();
    getline(cin, message);

    // Convert the message to lowercase and encrypt it
    transform(message.begin(), message.end(), message.begin(), ::tolower);
    string encrypted_message;
    for (char ch : message) {
        if (isalpha(ch)) {
            encrypted_message += cipher_alpha[ch - 'a'];
        } else {
            encrypted_message += ch; // Non-alphabetic characters remain unchanged
        }
    }
    cout << "Encrypted message: " << encrypted_message << endl;
}

// Simple Substitution Cipher Decryption Function
void simpleSubCypharDecryprtion() {
    string key;
    cout << "Please enter the key (5 alphabet letters): ";
    cin >> key;

    // Validate the key to ensure it contains only alphabetic characters
    while (key.size() != 5 || !all_of(key.begin(), key.end(), ::isalpha)) {
        cout << "Please enter a valid key (5 alphabet letters): ";
        cin >> key;
    }

    // Arrays to store alphabet and cipher alphabet
    char plain_alpha[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char cipher_alpha[26] = {tolower(key[0]), tolower(key[1]), tolower(key[2]), tolower(key[3]), tolower(key[4])};

    // Add the remaining elements of the cipher alphabet
    int index = 5;
    for (int i = 0; i < 26; i++) {
        if (find(begin(cipher_alpha), end(cipher_alpha), plain_alpha[i]) == end(cipher_alpha)) {
            cipher_alpha[index++] = plain_alpha[i];
        }
    }

    string encrypted_message;
    cout << "Please enter the encrypted message: ";
    cin.ignore();
    getline(cin, encrypted_message);

    // Convert the encrypted message to lowercase and decrypt it
    transform(encrypted_message.begin(), encrypted_message.end(), encrypted_message.begin(), ::tolower);
    string decrypted_message;
    for (char ch : encrypted_message) {
        if (isalpha(ch)) {
            auto pos = find(begin(cipher_alpha), end(cipher_alpha), ch);
            decrypted_message += plain_alpha[pos - begin(cipher_alpha)];
        } else {
            decrypted_message += ch; // Non-alphabetic characters remain unchanged
        }
    }
    cout << "Decrypted message: " << decrypted_message << endl;
}

// XOR Cipher Encryption Function
void XOR_ecryption() {
    string message;
    cout << "Enter your message: ";
    cin.ignore();
    getline(cin, message);

    char key;
    cout << "Enter key: ";
    cin >> key;

    string encrypted_message;
    // Perform XOR encryption
    for (char ch : message) {
        encrypted_message += ch ^ key;
    }

    cout << "Encrypted message: " << encrypted_message << endl;
}

// XOR Cipher Decryption Function
void XOR_decryption() {
    string encrypted_message;
    cout << "Enter encrypted message: ";
    cin.ignore();
    getline(cin, encrypted_message);

    char key;
    cout << "Enter key: ";
    cin >> key;

    string decrypted_message;
    // Perform XOR decryption
    for (char ch : encrypted_message) {
        decrypted_message += ch ^ key;
    }

    cout << "Decrypted message: " << decrypted_message << endl;
}
