// Authors: Ahmed Noureldin, Abdellateef, Adel
//  program :   This program is a collection of 3 ciphers required in the assignment  with a menu interface
//  to make the user choose the cipher he wants


#include <cmath>
#include <iostream>
#include <string>
#include <string.h>
#include <map>

using namespace std;
void simpleSubcypharEncrypt();
void simpleSubCypharDecryprtion();
void XOR_ecryption();
void XOR_decryption();
string railFenceCipherEncrypt(string input,int key);
string railFenceCipherDecrypt(string input,int key);

int taking_choice(int range){
    int choice;
    while(true){
        try {
            cout << "Enter your choice:";
            cin >> choice;
            if (cin.fail()) {
                cin.clear(); // Clear the fail state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard remaining characters
                throw runtime_error("Invalid input. Please enter an integer.");
            }
        } catch (exception& e) {
            cout << e.what() << endl; // Print error message
        }
        if(choice < 1 || choice > range){
            cout << "choice must be in range of 1 and " << range << endl;
            continue;
        }
        break;
    }
    return choice;
}

int main(){
    while(true){
        cout << "Choose cipher:" << endl << "1) Rail fence cipher" << endl << "2) Xor cipher" << endl << "3) Simple sub cipher" << endl << "4) End" << endl;
        int choice = taking_choice(4);
        if(choice == 1){
            cout << "Select a choice below " << endl;
            cout << "1) Encrypt" << endl;
            cout << "2) Decrypt" << endl;
            int cypharChoice = taking_choice(2);
            int key;
            while(true){
                cout << "Please enter the key" << endl;
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
                if(key <= 1 || key > 30){
                    cout << "Key must be higher than 1 and smaller than or equal to 30" << endl;
                    continue;
                }
                break;
            }
            if(cypharChoice == 1){
                cout << "Please enter the message" << endl;
                string input;
                cin.ignore();
                getline(cin,input);
                string encrypted = railFenceCipherEncrypt(input,key);
                cout << "Encrypted message is: " <<  encrypted << endl;
            }else{
                cout << "Please enter the encrypted message" << endl;
                string input;
                cin.ignore();
                getline(cin,input);
                string decrypted = railFenceCipherDecrypt(input,key);
                cout << decrypted << endl;
            }
        }else if(choice == 2){
            cout << "Select a choice below " << endl;
            cout << "1) Encrypt" << endl;
            cout << "2) Decrypt" << endl;
            int cypharChoice = taking_choice(2);
            if(cypharChoice == 1){
                XOR_ecryption();
            }else{
                XOR_decryption();
            }
        }else if(choice == 3){
            cout << "Select a choice below " << endl;
            cout << "1) Encrypt" << endl;
            cout << "2) Decrypt" << endl;
            int cypharChoice = taking_choice(2);
            if(cypharChoice == 1){
                simpleSubcypharEncrypt();
            }else{
                simpleSubCypharDecryprtion();
            }
        }else{
            break;
        }

    }
    return 0;
}

string railFenceCipherEncrypt(string input,int key){
    string newS; // Initialize the string to store the encrypted text
    string modInput; // Initialize a modified version of the input string with only alphabetic characters

    // Modify the input string to contain only lowercase alphabetic characters
    for(int i = 0; i < input.size(); i++) {
        if((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) {
            modInput += tolower(input[i]);
        }
    }

    int row = 0;
    int increment = 1;
    char grid[key][modInput.size()]; // Initialize the grid for encryption

    // Populate the grid with '.' characters
    for(int i = 0; i < key; i++) {
        for(int j = 0; j < modInput.size(); j++) {
            grid[i][j] = '.';
        }
    }

    // Fill the grid with characters from the modified input string
    for(int i = 0; i < modInput.size(); i++) {
        grid[row][i] = modInput[i];
        row += increment;
        // Reverse direction when reaching the top or bottom rail
        if(row == key - 1 || row == 0) {
            if(increment == 1) {
                increment = -1;
            } else {
                increment = 1;
            }
        }
    }

    // Read the encrypted characters from the grid to form the encrypted string
    for(int i = 0; i < key; i++) {
        for(int j = 0; j < modInput.size(); j++) {
            if(grid[i][j] != '.') {
                newS += grid[i][j];
            }
        }
    }

    return newS; // Return the encrypted string

}

string railFenceCipherDecrypt(string input,int key) {
    char grid[key][input.size()]; // Initialize the grid for encryption
// Populate the grid with '.' characters
    for(int i = 0; i < key; i++) {
        for(int j = 0; j < input.size(); j++) {
            grid[i][j] = '.';
        }
    }

    int row = key;
    int column = 0;
    int firstWay = row * 2 - 2;
    int secondWay = row * 2 - 2;
    bool choice = false;

// Encrypt the input string using Rail Fence Cipher
    for(int i = 0; i < input.size(); i++) {
        // Check if the current position is empty in the grid
        if(grid[key - row][column] == '.') {
            // Fill the grid with characters from the input string
            grid[key - row][column] = input[i];

            // Update column position and adjust step sizes
            if(!choice) {
                column += firstWay;
            } else {
                column += secondWay;
            }
            choice = !choice;

            // Check if the column is within bounds
            if(column >= input.size()) {
                // Update row and column positions and adjust step sizes
                row--;
                column = key - row;
                if(row == 1) {
                    firstWay = key * 2 - 2;
                    secondWay = key * 2 - 2;
                } else {
                    firstWay = row * 2 - 2;
                    secondWay = (key - row) * 2;
                }
                choice = false;
            }
        } else {
            // Move to the next column if the current position is occupied
            column++;
            i--; // Decrement i to repeat the current iteration
        }
    }
    string newS;
    row = 0;
    int increment = 1;
    // Read the encrypted characters from the grid to form the encrypted string
    for(int i = 0; i < input.size(); i++) {
        newS += grid[row][i];
        row += increment;
        // Reverse direction when reaching the top or bottom rail
        if(row == key - 1 || row == 0) {
            if(increment == 1) {
                increment = -1;
            } else {
                increment = 1;
            }
        }
    }
    return newS; // Return the encrypted string
}

void simpleSubcypharEncrypt(){
    string key;
    cout << "please, enter the key: ";
    cin >> key;

    // validate the key to ensure it contains only alphabetic characters
    while(!isalpha(key[0]) || !isalpha(key[1]) || !isalpha(key[2]) || !isalpha(key[3]) || !isalpha(key[4]))
    {
        cout << "please, enter the key (alphabet letters): ";
        cin >> key;
    }

    // Array to store Alphabet
    char plain_alpha[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    // Array to store cipher Alphabet
    char cipher_alpha[26] = {tolower(key[0]), tolower(key[1]), tolower(key[2]), tolower(key[3]), tolower(key[4])};
    // Add the remaining elements of the cipher alphabet
    int index = 5;
    for(int i = 0; i < 26; i++)
    {
        if( (plain_alpha[i] != cipher_alpha[0]) && (plain_alpha[i] != cipher_alpha[1]) && (plain_alpha[i] != cipher_alpha[2]) && (plain_alpha[i] != cipher_alpha[3]) && (plain_alpha[i] != cipher_alpha[4]))
        {
            cipher_alpha[index] = plain_alpha[i];
            index++;
        }
        else
            continue;
    }

    string plain_text, cipher_text = "", decipher_text = "";

    // Get the message from the user
    cout << "please, enter the message: ";
    cin.ignore();
    getline(cin, plain_text);
    cout <<endl;
    // Map to store the relationship between plain and cipher characters for encryption
    map <char,char> alpha{
            {'a', cipher_alpha[0]},
            {'b', cipher_alpha[1]},
            {'c', cipher_alpha[2]},
            {'d', cipher_alpha[3]},
            {'e', cipher_alpha[4]},
            {'f', cipher_alpha[5]},
            {'g', cipher_alpha[6]},
            {'h', cipher_alpha[7]},
            {'i', cipher_alpha[8]},
            {'j', cipher_alpha[9]},
            {'k', cipher_alpha[10]},
            {'l', cipher_alpha[11]},
            {'m', cipher_alpha[12]},
            {'n', cipher_alpha[13]},
            {'o', cipher_alpha[14]},
            {'p', cipher_alpha[15]},
            {'q', cipher_alpha[16]},
            {'r', cipher_alpha[17]},
            {'s', cipher_alpha[18]},
            {'t', cipher_alpha[19]},
            {'u', cipher_alpha[20]},
            {'v', cipher_alpha[21]},
            {'w', cipher_alpha[22]},
            {'x', cipher_alpha[23]},
            {'y', cipher_alpha[24]},
            {'z', cipher_alpha[25]}};

    // Encrypt each character in the plain text
    for(int i = 0; i < plain_text.length(); i++)
    {
        if(isspace(plain_text[i]))
        {
            cipher_text += ' ';
        }
        else
            cipher_text += alpha[tolower(plain_text[i])];
    }

    // Display the encrypted text
    cout << "cipher text: " << cipher_text << endl;
}

void simpleSubCypharDecryprtion(){
    string key;
    cout << "please, enter the key: ";
    cin >> key;

    // validate the key to ensure it contains only alphabetic characters
    while(!isalpha(key[0]) || !isalpha(key[1]) || !isalpha(key[2]) || !isalpha(key[3]) || !isalpha(key[4]))
    {
        cout << "please, enter the key (alphabet letters): ";
        cin >> key;
    }

    // Array to store Alphabet
    char plain_alpha[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    // Array to store cipher Alphabet
    char cipher_alpha[26] = {tolower(key[0]), tolower(key[1]), tolower(key[2]), tolower(key[3]), tolower(key[4])};
    // Add the remaining elements of the cipher alphabet
    int index = 5;
    for(int i = 0; i < 26; i++)
    {
        if( (plain_alpha[i] != cipher_alpha[0]) && (plain_alpha[i] != cipher_alpha[1]) && (plain_alpha[i] != cipher_alpha[2]) && (plain_alpha[i] != cipher_alpha[3]) && (plain_alpha[i] != cipher_alpha[4]))
        {
            cipher_alpha[index] = plain_alpha[i];
            index++;
        }
        else
            continue;
    }

    string plain_text, cipher_text = "", decipher_text = "";

    // Get the message from the user
    cout << "please, enter the message: ";
    cin.ignore();
    getline(cin, plain_text);
    cout <<endl;
    // Map to store the relationship between cipher and plain characters for decryption
    map <char,char> alpha{
            {cipher_alpha[0],'a'},
            {cipher_alpha[1],'b'},
            {cipher_alpha[2],'c'},
            {cipher_alpha[3],'d'},
            {cipher_alpha[4],'e'},
            {cipher_alpha[5],'f'},
            {cipher_alpha[6],'g'},
            {cipher_alpha[7],'h'},
            {cipher_alpha[8],'i'},
            {cipher_alpha[9],'j'},
            {cipher_alpha[10],'k'},
            {cipher_alpha[11],'l'},
            {cipher_alpha[12],'m'},
            {cipher_alpha[13],'n'},
            {cipher_alpha[14],'o'},
            {cipher_alpha[15],'p'},
            {cipher_alpha[16],'q'},
            {cipher_alpha[17],'r'},
            {cipher_alpha[18],'s'},
            {cipher_alpha[19],'t'},
            {cipher_alpha[20],'u'},
            {cipher_alpha[21],'v'},
            {cipher_alpha[22],'w'},
            {cipher_alpha[23],'x'},
            {cipher_alpha[24],'y'},
            {cipher_alpha[25],'z'}};

    // Decrypt each character in the plain text
    for(int i = 0; i < plain_text.length(); i++)
    {
        if(isspace(plain_text[i]))
        {
            decipher_text += ' ';
        }
        else
            decipher_text += alpha[tolower(plain_text[i])];
    }

    // Display the decrypted text
    cout << "decipher text: " << decipher_text << endl;
}

// Function to perform encryption
void XOR_ecryption() {
    string text, res;
    cout << "Enter the message you want to be Encrypted" << endl;

    // Read the entire line including spaces
    cin.ignore();
    getline(cin, text);

    // Generate the binary representation of the message
    int text_size = text.size();
    int x;
    string Binary_message = "";
    for (int i = 0; i < text_size; i++) {
        x = int(text[i]);
        res = "";
        while (x > 0) {
            res = to_string(x % 2) + res;
            x /= 2;
        }
        while (res.size() < 8) {
            res = '0' + res;
        }
        Binary_message += res;
    }

    // Get the secret key
    string key;
    cout << "Enter the secret key" << endl;
    getline(cin, key);

    // Generate the binary representation of the key
    int cipher_size = key.size();
    string Binary_text = "";
    for (int i = 0; i < cipher_size; i++) {
        x = int(key[i]);
        res = "";
        while (x > 0) {
            res = to_string(x % 2) + res;
            x /= 2;
        }
        while (res.size() < 8) {
            res = '0' + res;
        }
        Binary_text += res;
    }

    // Ensure that the key is at least as long as the message
    while (Binary_message.size() > Binary_text.size()) {
        Binary_text += Binary_text.substr(0, Binary_message.size() - Binary_text.size());
    }

    // Perform XOR operation
    string ans = "";
    string c;
    for (int i = Binary_message.size() - 1; i >= 0; i--) {
        if (Binary_message[i] != Binary_text[i])
            c = "1";
        else
            c = "0";
        ans = c + ans;
    }

    // Convert binary to text
    string letter;
    int sum = 0;
    cout << "The encrypted text: ";
    for (int i = 0; i < ans.size(); i += 8) {
        letter = ans.substr(i, 8);
        sum = 0;
        for (int j = 0; j < 8; j++) {
            sum += (letter[j] - '0') * pow(2, 7 - j);
        }
        cout << char(sum);
    }
    cout << endl;

    // Convert binary to hexadecimal
    string hexa = "0123456789ABCDEF";
    cout << "The text Encrypted in Hexadecimal: ";
    for (int i = 0; i < ans.size(); i += 4) {
        letter = ans.substr(i, 4);
        sum = 0;
        for (int j = 0; j < 4; j++) {
            sum += (letter[j] - '0') * pow(2, 3 - j);
        }
        cout << hexa[sum];
    }
    cout << endl << endl;
}

// Function to perform decryption
void XOR_decryption() {
    string decipher;
    string hex = "0123456789ABCDEF";
    bool flag;
    int x;
    string res, Binary_message;
    cout << "Please enter valid Encrypted hexadecimal text" << endl;

    // Validate the input
    while (cin >> decipher) {
        flag = true;
        for (char c : decipher) {
            if (hex.find(toupper(c)) == string::npos) {
                flag = false;
                break;
            }
        }
        if (flag) {
            break;
        } else {
            cout << "Invalid input!" << endl;
            cout << "Please enter valid Encrypted hexadecimal text" << endl;
        }
    }

    // Convert hexadecimal to binary
    for (char c : decipher) {
        x = hex.find(toupper(c));
        string res = "";
        while (x > 0) {
            res = to_string(x % 2) + res;
            x /= 2;
        }
        while (res.size() < 4) {
            res = '0' + res;
        }
        Binary_message += res;
    }

    // Get the secret key
    string key;
    cout << "Enter the secret key" << endl;

    // Read the entire line including spaces
    cin.ignore();
    getline(cin, key);

    // Generate the binary representation of the key
    int cipher_size = key.size();
    string Binary_text = "";
    for (int i = 0; i < cipher_size; i++) {
        x = int(key[i]);
        res = "";
        while (x > 0) {
            res = to_string(x % 2) + res;
            x /= 2;
        }
        while (res.size() < 8) {
            res = '0' + res;
        }
        Binary_text += res;
    }

    // Ensure that the key is at least as long as the message
    while (Binary_message.size() > Binary_text.size()) {
        Binary_text += Binary_text.substr(0, Binary_message.size() - Binary_text.size());
    }

    // Perform XOR operation
    string ans = "";
    string c;
    for (int i = Binary_message.size() - 1; i >= 0; i--) {
        if (Binary_message[i] != Binary_text[i])
            c = "1";
        else
            c = "0";
        ans = c + ans;
    }

    // Convert binary to text
    string letter;
    int sum = 0;
    cout << "The decrypted message is: ";
    for (int i = 0; i < ans.size(); i += 8) {
        letter = ans.substr(i, 8);
        sum = 0;
        for (int j = 0; j < 8; j++) {
            sum += (letter[j] - '0') * pow(2, 7 - j);
        }
        cout << char(sum);
    }
    cout << endl;

    // Convert binary to hexadecimal
    cout << "The text Decrypted message in Hexadecimal: ";
    for (int i = 0; i < ans.size(); i += 4) {
        letter = ans.substr(i, 4);
        sum = 0;
        for (int j = 0; j < 4; j++) {
            sum += (letter[j] - '0') * pow(2, 3 - j);
        }
        cout << hex[sum];
    }
}