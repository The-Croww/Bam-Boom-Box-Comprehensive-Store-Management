#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <ctime>

using namespace std;

struct Product {
    string name;
    double storePrice;
    double marketPrice;
    string category;
    int Stock;
};

//Limiter
Product products[100];

int n = 0;
string currentFile;

//Newlines and Tabs
void pNewlineTabs(int numNewlines, int numTabs) {
    for (int i = 0; i < numNewlines; i++) {
        cout << endl;
    }
    for (int i = 0; i < numTabs; i++) {
        cout << "\t";
    }
}

//Use Menu
int UserMenu() {
    int choice;

    system("CLS");
    pNewlineTabs(10, 7); cout << "|============================================|\n";
    pNewlineTabs(0,7); cout << "|                 User Menu                  |\n";
    pNewlineTabs(0,7); cout << "|============================================|\n";
    pNewlineTabs(0,7); cout << "|                                            |\n";
    pNewlineTabs(0,7); cout << "| 1. View Products & Prices                  |\n";
    pNewlineTabs(0,7); cout << "| 2. Search Products by Category             |\n";
    pNewlineTabs(0,7); cout << "| 3. Search Products by Price Range          |\n";
    pNewlineTabs(0,7); cout << "| 4. Compare Products                        |\n";
    pNewlineTabs(0,7); cout << "| 5. Exit                                    |\n";
    pNewlineTabs(0,7); cout << "|                                            |\n";
    pNewlineTabs(0,7); cout << "|============================================|\n";
    pNewlineTabs(2,7); cout << " Enter your choice: ";

    while (!(cin >> choice)) {
                cin.clear(); cin.ignore();
                pNewlineTabs(0, 7); cout << "|--------------------------------------------|\n";
                pNewlineTabs(0, 7); cout << " Invalid input! Please enter a integer type: ";
            }

    system("CLS");
    if (choice > 5) {
        pNewlineTabs(3, 7); cout << " Invalid choice. Please choose a valid option.\n";
        pNewlineTabs(1,7); cout << " Press any key to try again: ";
        cin.ignore(); cin.get(); system("CLS");
        return UserMenu();
    } else {
        return choice;
    }
}

//Admin Menu
int AdminMenu() {
    int choice;

    system("CLS");
    pNewlineTabs(10,7); cout << "|============================================|\n";
    pNewlineTabs(0, 7); cout << "|                Admin Menu                  |\n";
    pNewlineTabs(0, 7); cout << "|============================================|\n";
    pNewlineTabs(0, 7); cout << "|                                            |\n";
    pNewlineTabs(0, 7); cout << "| 1. Add New Product                         |\n";
    pNewlineTabs(0, 7); cout << "| 2. Change Product                          |\n";
    pNewlineTabs(0, 7); cout << "| 3. Delete Product                          |\n";
    pNewlineTabs(0, 7); cout << "| 4. Exit                                    |\n";
    pNewlineTabs(0, 7); cout << "|                                            |\n";
    pNewlineTabs(0, 7); cout << "|============================================|\n";
    pNewlineTabs(2, 7); cout << " Enter your choice: ";

    while (!(cin >> choice)) {
                cin.clear(); cin.ignore();
                pNewlineTabs(0, 7); cout << "|--------------------------------------------|\n";
                pNewlineTabs(0, 7); cout << " Invalid input! Please enter a integer type: ";
            }

    if (choice < 1 || choice > 4) {
        pNewlineTabs(3, 7); cout << " Invalid choice. Please choose a valid option.\n";
        pNewlineTabs(1,7);cout << " Press any key to try again: ";
        cin.ignore(); cin.get(); system("CLS");
        return AdminMenu();
    } else {
        return choice;
    }
}

//File for user's activity
void userActivity(string& filename, string line) {
    time_t now = time(nullptr); // for real time

    ofstream file(filename, ios::app);
    if(file.is_open()) {
        file << line << " - " << ctime(&now) << endl;
        file.close();
    }
}

//Function to save users data
void saveUsers(string usersName[], string usersPassword[], int userCount) {
    ofstream file("users_data.txt");
    if(file.is_open()) {
        file << userCount << endl;
         for(int i = 0; i < userCount; i++) {
            file << usersName[i] << endl;
            file << usersPassword[i] << endl;
        }
        file.close();
    }
}

//Function to load users data
void loadUsers(string usersName[], string usersPassword[], int& userCount) {
    ifstream file("users_data.txt");
    if(file.is_open()) {
        file >> userCount;
        file.ignore();
         for(int i = 0; i < userCount; i++) {
            getline(file, usersName[i]);
            getline(file, usersPassword[i]);
        }
        file.close();
    }
}

int signUp(Product& user, string usersName[], string usersPassword[], int& userCount) {
    string name, password;
    int check;

    pNewlineTabs(2, 4); cout << "|---------------------------------------------------------------------------------------|\n";
    pNewlineTabs(0, 4); cout << "|                                                                                       |\n";
    pNewlineTabs(0, 4); cout << "|                              Enter The Following Data                                 |\n";
    pNewlineTabs(0, 4); cout << "|                                                                                       |\n";

    // Loop until a unique username is entered
    while(true) {
        check = 0;
        pNewlineTabs(0, 4); cout << "|---------------------------------------------------------------------------------------|\n";
        pNewlineTabs(0, 4); cout << " Username: ";
        getline(cin >> ws, name);
        pNewlineTabs(0, 4); cout << "|---------------------------------------------------------------------------------------|\n";

        // Check if the entered username already exists in the system
        for(int i = 0; i < userCount; i++) {
            if(name == usersName[i]) {
                check++; // increment the check variable if the username is found
            }
        }

        // If the username is unique, break out of the loop
        if(check == 0) {
            break;
        } else {
            pNewlineTabs(1,2); cout << "Username Not Available." << endl;
        }
    }

    // Prompt the user to enter a password
    pNewlineTabs(0,4); cout << " Password: ";
    getline(cin, password);

    pNewlineTabs(2,4); cout << " Type Any Key to Exit: ";
    cin.ignore(); cin.get();

    usersName[userCount] = name;
    usersPassword[userCount] = password;

    // Create a file for the new user's data
    currentFile = name + "_data.txt";

    // Increment the user count
    userCount++;

    saveUsers(usersName, usersPassword, userCount);

    return 0;
}

//Function for log in
int login(Product& user, string usersName[], string usersPassword[], int userCount) {
    string name, password;
    int choice = 1;
    while(true) {
        pNewlineTabs(1, 4); cout << "|---------------------------------------------------------------------------------------|\n";
        pNewlineTabs(0, 4); cout << " Username: ";
        getline(cin >> ws, name);
        pNewlineTabs(0, 4); cout << "|---------------------------------------------------------------------------------------|\n";
        for(int i = 0; i < userCount; i++) {
            if(name == usersName[i]) {
                while(true) {
                    pNewlineTabs(0, 4); cout << " Password: ";
                    getline(cin >> ws, password);
                    pNewlineTabs(0, 4); cout << "|---------------------------------------------------------------------------------------|\n";
                    pNewlineTabs(2,4); cout << " Type Any Key to Log In: ";
                    cin.ignore(); cin.get();
                     if(password == usersPassword[i]) {
                        currentFile = name + "_data.txt";
                        return 0;
                    } else {
                       pNewlineTabs(1, 4); cout << " Incorrect Password Please Try Again.\n" << endl;
                    }
                  }
                break;
            }
          }
       pNewlineTabs(1, 4); cout << " Username Not Found." << endl;
       pNewlineTabs(0, 4); cout << " [1] Log Again [2] No Account? Sign Up: ";
       cin >> choice;
       if(choice == 2){
            signUp(user, usersName, usersPassword, userCount);
            }
    }
}


//Function to load admin data
void loadAdminData(string& adminUsername, string& adminPassword) {
    ifstream file("admin_data.txt");
    if (file.is_open()) {
        getline(file, adminUsername);
        getline(file, adminPassword);
        file.close();
    }
}

//Function to save admin data
void saveAdminData(string& adminUsername, string& adminPassword) {
    ofstream file("admin_data.txt");
    if (file.is_open()) {
        file << adminUsername << endl;
        file << adminPassword << endl;
        file.close();
    }
}

// Function to handle admin login
int adminLogin(string& adminUsername, string& adminPassword) {
    string username, password;

    pNewlineTabs(1, 4); cout << "|---------------------------------------------------------------------------------------|\n";
    pNewlineTabs(0, 4); cout << " Username: ";
    getline(cin, username);
    pNewlineTabs(0, 4); cout << "|---------------------------------------------------------------------------------------|\n";
    pNewlineTabs(0, 4); cout << " Password: ";
    getline(cin, password);
    pNewlineTabs(0, 4); cout << "|---------------------------------------------------------------------------------------|\n";
    pNewlineTabs(2,4); cout << " Type Any Key to Log In: ";
    cin.ignore(); cin.get();

    // Check if the entered credentials match the admin username and password
    if (username == adminUsername && password == adminPassword) {
        // If valid, return 0 to indicate success
        return 0;
    } else {
        // If invalid, display an error message and call the function to try again
        pNewlineTabs(0, 4); cout << " Invalid admin credentials. Please try again." << endl;
        return adminLogin(adminUsername, adminPassword);
    }
}

//Log in and Sign Up Function
int Login_SignUp(Product& user, string usersName[], string usersPassword[], int& userCount) {
    string name, password;
    loadUsers(usersName, usersPassword, userCount);
    while(true) {
        system("cls");
        int choice;

        pNewlineTabs(10, 4); cout << "=========================================================================================\n";
        pNewlineTabs(0, 4); cout << "|                                         |                                             |\n";
        pNewlineTabs(0, 4); cout << "|                  An                     |               1. Login                      |\n";
        pNewlineTabs(0, 4); cout << "|      Enhanced Product Organization,     |                                             |\n";
        pNewlineTabs(0, 4); cout << "|        Time, and Cost Efficiency        |=============================================|\n";
        pNewlineTabs(0, 4); cout << "|               Program                   |             No account yet?                 |\n";
        pNewlineTabs(0, 4); cout << "|                                         |               2. Sign Up                    |\n";
        pNewlineTabs(0, 4); cout << "|                                         |                                             |\n";
        pNewlineTabs(0, 4); cout << "=========================================================================================\n";
        pNewlineTabs(0, 4); cout << "                                                 Enter Here: ";

         while (!(cin >> choice)) {
                cin.clear(); cin.ignore();
                pNewlineTabs(0, 4); cout << "|---------------------------------------------------------------------------------------|\n";
                pNewlineTabs(0, 4); cout << " Invalid input! Please enter a integer type: ";
            }

        switch(choice) {
        case 1: //Log in
            login(user ,usersName, usersPassword, userCount);
            return 0;
        case 2: // Sign Up
            signUp(user, usersName, usersPassword, userCount);
            break;
        default:
            cout << "Invalid Please Please Try Again! ";
            if(choice <= 0 && choice >= 3){
                break;
            }
        }
    }
}

//Function to view products
void viewProducts() {
    userActivity(currentFile, "You Viewed Product in the Program");

    if (n == 0) {
        cout << "No products to display.\n";
        return;
    }

    pNewlineTabs(10, 9); cout << "PRODUCTS IN YOUR STORE:\n\n";
    cout << left;
    pNewlineTabs(0, 4); cout << "|------|--------------------------------|-------------------|-------------|--------------|----------|\n";
    pNewlineTabs(0, 4);cout << "| No.  | Name                           | Category          | Store Price | Market Price | Stock    |\n";
    pNewlineTabs(0, 4);cout << "|------|--------------------------------|-------------------|-------------|--------------|----------|\n";

    for (int i = 0; i < n; i++) {
        pNewlineTabs(0, 4); cout << "| " << setw(4) << i + 1 << " | "
             << setw(30) << products[i].name << " | "
             << setw(17) << products[i].category << " | "
             << setw(11) << products[i].storePrice << " | "
             << setw(12) << products[i].marketPrice << " | "
             << setw(8) << products[i].Stock << " |\n";
    }
    pNewlineTabs(0, 4); cout << "|------|--------------------------------|-------------------|-------------|--------------|----------|\n";

    pNewlineTabs(2, 4); cout << "Press any key to exit: ";
    cin.ignore(); cin.get(); system("CLS");
}

//Insertion sort function to keep categories in group alphabetically
void insertionSort() {
   for (int i = 1; i < n; i++) {
        Product keyProduct = products[i];
        int j = i - 1;

        while (j >= 0 && products[j].category > keyProduct.category) {
            products[j + 1] = products[j];
            j = j - 1;
        }
        products[j + 1] = keyProduct;
    }
}

//Function to search by category
void search_Category() {
    userActivity(currentFile, "You Searched a Product by Category in the Program");

    if (n == 0) {
        pNewlineTabs(10,8); cout << "No products to search.\n";
        return;
    }

    string Pcategory;
    pNewlineTabs(10, 4); cout << " Enter the Category of the Product to Search: ";
    getline(cin >> ws, Pcategory);

    bool found = false;
    for (int i = 0; i < n; i++) {
        if (products[i].category == Pcategory) {
            if (!found) {
                pNewlineTabs(3,10); cout << "Product found!\n";
                cout << left;
                pNewlineTabs(1,4); cout << "|------|--------------------------------|-------------------|-------------|--------------|----------|--------------|\n";
                pNewlineTabs(0,4); cout << "| No.  | Name                           | Category          | Store Price | Market Price | Stock    | Store Profit |\n";
                pNewlineTabs(0,4); cout << "|------|--------------------------------|-------------------|-------------|--------------|----------|--------------|\n";
                found = true;
                       }
            double profit = products[i].storePrice - products[i].marketPrice; // formula to get the store profit

            //for printing landscape and to keep it align
            pNewlineTabs(0,4); cout << "| " << setw(4) << i + 1 << " | "
                 << setw(30) << products[i].name << " | "
                 << setw(17) << products[i].category << " | "
                 << setw(11) << products[i].storePrice << " | "
                 << setw(12) << products[i].marketPrice << " | "
                 << setw(8) << products[i].Stock << " | "
                 << setw(12) << profit << " |\n";
        }
    }
     pNewlineTabs(0,4); cout << "|------|--------------------------------|-------------------|-------------|--------------|----------|--------------|\n";
    //If not found
    if (!found) {
       pNewlineTabs(0,9); cout << "Product not found! Please try again.\n";
    }
    pNewlineTabs(2,4); cout << " Press any key to continue: ";
    cin.ignore(); cin.get(); system("CLS");
}

void PriceRange_search() {

    userActivity(currentFile, "You searched for a product by price range in the program");

    if (n == 0) {
        pNewlineTabs(10,8); cout << "No products to search.\n";
        return;
    }

    double minPrice, maxPrice;
    pNewlineTabs(10, 4); cout << "|---------------------------------------------------------------------------------------------------|\n";
    pNewlineTabs(0, 4); cout << " Enter the Minimum Price of the Product to Search: ";
    cin >> minPrice;
    pNewlineTabs(0, 4); cout << "|---------------------------------------------------------------------------------------------------|\n";
    pNewlineTabs(0, 4); cout << " Enter the Maximum Price of the Product to Search: ";
    cin >> maxPrice;
    pNewlineTabs(0, 4); cout << "|---------------------------------------------------------------------------------------------------|\n";

    bool found = false;
    for (int i = 0; i < n; i++) {
        if (products[i].storePrice >= minPrice && products[i].storePrice <= maxPrice) {
            if (!found) {
               pNewlineTabs(3, 9); cout << "Product found!\n";
                cout << left;
                pNewlineTabs(1,4); cout << "|------|--------------------------------|-------------------|-------------|--------------|----------|--------------|\n";
                pNewlineTabs(0,4); cout << "| No.  | Name                           | Category          | Store Price | Market Price | Stock    | Store Profit |\n";
                pNewlineTabs(0,4); cout << "|------|--------------------------------|-------------------|-------------|--------------|----------|--------------|\n";
                found = true;
            }
            double profit = products[i].storePrice - products[i].marketPrice;
            pNewlineTabs(0,4); cout << "| " << setw(4) << i + 1 << " | "
                 << setw(30) << products[i].name << " | "
                 << setw(17) << products[i].category << " | "
                 << setw(11) << products[i].storePrice << " | "
                 << setw(12) << products[i].marketPrice << " | "
                 << setw(8) << products[i].Stock << " | "
                 << setw(12) << profit << " |\n";
        }
    }
     pNewlineTabs(0,4); cout << "|------|--------------------------------|-------------------|-------------|--------------|----------|--------------|\n";
    if (!found) {
        pNewlineTabs(3, 10); cout << "Product not found! Please try again.\n";
    }
    pNewlineTabs(1, 4); cout << "Press any key to continue: ";
    cin.ignore(); cin.get(); system("CLS");
}

// Function to compare two products
void compareProducts() {
    userActivity(currentFile, "You Compared a Product in The Program");

    if (n < 2) {
        pNewlineTabs(10,8); cout << "Not enough products to compare.\n";
        return;
    }

    string Pname1, Pname2;

    pNewlineTabs(10,5); cout << "|------------------------------------------------------------------------|\n";
    pNewlineTabs(0,5); cout << " Enter Name of First Product to Compare: ";
    getline(cin >> ws, Pname1);
    pNewlineTabs(0,5); cout << "|------------------------------------------------------------------------|\n";
    pNewlineTabs(0,5); cout << " Enter Name of Second Product to Compare: ";
    getline(cin >> ws, Pname2);
    pNewlineTabs(0,5); cout << "|------------------------------------------------------------------------|\n";

    // Initialize variables to store the indices of the two products
    int i1 = -1, i2 = -1;

    // Loop through the products array to find the indices of the two products
    for (int i = 0; i < n; i++) {
        if (products[i].name == Pname1) {
            i1 = i;
        }
        if (products[i].name == Pname2) {
            i2 = i;
        }
    }

    // Check if one or both products were not found
    if (i1 == -1 || i2 == -1) {
        pNewlineTabs(3,5); cout << " One or both products not found! Please try again.\n";
        pNewlineTabs(1,5);cout << " Press any key to exit: ";
        cin.ignore(); cin.get(); system("CLS");
        return;
    }

    // Calculate the profit for each product
    double profit1 = products[i1].storePrice - products[i1].marketPrice;
    double profit2 = products[i2].storePrice - products[i2].marketPrice;

    pNewlineTabs(3,8); cout << "Product Comparison\n";
    cout << left;
    pNewlineTabs(1,5); cout << "|------------------|---------------------------|-------------------------|\n";
    pNewlineTabs(0,5); cout << "| Names            | " << setw(25) << products[i1].name << " | " << setw(23) << products[i2].name << " |\n";
    pNewlineTabs(0,5); cout << "|                  |                           |                         |\n";
    pNewlineTabs(0,5); cout << "|------------------|---------------------------|-------------------------|\n";
    pNewlineTabs(0,5); cout << "| Category         | " << setw(25) << products[i1].category << " | " << setw(23) << products[i2].category << " |\n";
    pNewlineTabs(0,5); cout << "|------------------|---------------------------|-------------------------|\n";
    pNewlineTabs(0,5); cout << "| Store Price      | " << setw(25) << products[i1].storePrice << " | " << setw(23) << products[i2].storePrice << " |\n";
    pNewlineTabs(0,5); cout << "|------------------|---------------------------|-------------------------|\n";
    pNewlineTabs(0,5); cout << "| Market Price     | " << setw(25) << products[i1].marketPrice << " | " << setw(23) << products[i2].marketPrice << " |\n";
    pNewlineTabs(0,5); cout << "|------------------|---------------------------|-------------------------|\n";
    pNewlineTabs(0,5); cout << "| Stock            | " << setw(25) << products[i1].Stock << " | " << setw(23) << products[i2].Stock << " |\n";
    pNewlineTabs(0,5); cout << "|------------------|---------------------------|-------------------------|\n";
    pNewlineTabs(0,5); cout << "|                  |                           |                         |\n";
    pNewlineTabs(0,5); cout << "| Store Profit     | " << setw(25) << profit1 << " | " << setw(23) << profit2 << " |\n";
    pNewlineTabs(0,5); cout << "|------------------|---------------------------|-------------------------|\n";

    pNewlineTabs(2,5);cout << " Press any key to exit: ";
    cin.ignore(); cin.get(); system("CLS");
}

void addProduct() {
    string Pname, Pcategory, input;
    double Sprice, Mprice;
    int PStock;

    int con = 3;

    while (true) {
        system("CLS");
        pNewlineTabs(10, 7); cout << "|===========================================|\n";
        pNewlineTabs(0, 7); cout << " To Exit Please Type (E)\n";
        pNewlineTabs(0, 7); cout << "|===========================================|\n";
        pNewlineTabs(0, 7); cout << "|                                           |\n";
        pNewlineTabs(0, 7); cout << " Enter New Product Name: ";
        getline(cin >> ws, Pname);
        if (Pname == "E" || Pname == "e") break; // Exit if user types 'E' or 'e'

        pNewlineTabs(0, 7); cout << "|-------------------------------------------|\n";
        pNewlineTabs(0, 7); cout << " Enter Product Category: ";
        getline(cin >> ws, Pcategory);
        if (Pcategory == "E" || Pcategory == "e") break;

        pNewlineTabs(0, 7); cout << "|-------------------------------------------|\n";
        pNewlineTabs(0, 7); cout << " Enter Store Price: ";
        // Get store price and validate input
        while (!(cin >> Sprice)) {
            cin.clear();
            cin >> input;
            if (input == "E" || input == "e") break;
            pNewlineTabs(0, 7); cout << " Invalid input. Please enter a valid price: ";
        }
        if (input == "E" || input == "e") break;

        pNewlineTabs(0, 7); cout << "|-------------------------------------------|\n";
        pNewlineTabs(0, 7); cout << " Enter Market Price: ";
        // Get market price and validate input
        while (!(cin >> Mprice)) {
            cin.clear();
            cin >> input;
            if (input == "E" || input == "e") break;
            pNewlineTabs(0, 7); cout << " Invalid input. Please enter a valid price: ";
        }
        if (input == "E" || input == "e") break;

        pNewlineTabs(0, 7); cout << "|-------------------------------------------|\n";
        pNewlineTabs(0, 7); cout << " Enter Product Stock: ";
        // Get product stock and validate input
        while (!(cin >> PStock)) {
            cin.clear();
            cin >> input;
            if (input == "E" || input == "e") break;
            pNewlineTabs(0, 7); cout << " Invalid input. Please enter a valid stock: ";
        }
        if (input == "E" || input == "e") break;

        // Save product details to the products array
        products[n].name = Pname;
        products[n].storePrice = Sprice;
        products[n].marketPrice = Mprice;
        products[n].category = Pcategory;
        products[n].Stock = PStock;

        n++; // Increment the product count
        pNewlineTabs(3, 7); cout << " Product added successfully!\n";
        pNewlineTabs(1, 7); cout << " [1] Add More [2] View Products [3] Exit: "; cin >> con; system("CLS");

        if (con == 1) {
            // If user chooses to add more products
            addProduct();
        } else if (con == 2) {
            // If user chooses to view products
            viewProducts();
            pNewlineTabs(10, 9); cout << " [1] Go Back [2] Exit: "; cin >> con;
            if (con == 1) {
                // Go back to adding products
                addProduct();
            } else {
                // Save products to file and exit
                ofstream outFile("Products_Profile.txt");
                if (outFile.is_open()) {
                    outFile << n << endl;
                    for (int i = 0; i < n; i++) {
                        outFile << products[i].name << endl;
                        outFile << products[i].storePrice << endl;
                        outFile << products[i].marketPrice << endl;
                        outFile << products[i].category << endl;
                        outFile << products[i].Stock << endl;
                    }
                    outFile.close();
                }
                return;
            }
        } else {
            // Save products to file and exit
            ofstream outFile("Products_Profile.txt");
            if (outFile.is_open()) {
                outFile << n << endl;
                for (int i = 0; i < n; i++) {
                    outFile << products[i].name << endl;
                    outFile << products[i].storePrice << endl;
                    outFile << products[i].marketPrice << endl;
                    outFile << products[i].category << endl;
                    outFile << products[i].Stock << endl;
                }
                outFile.close();
            }
            return;
        }
    }
}

void changeProduct() {
    string productName, input;

    int con = 3;

    while(true){

    system("CLS");
    pNewlineTabs(10, 7); cout << "|===========================================|\n";
    pNewlineTabs(0, 7); cout << " To Exit Please Type (E)\n";
    pNewlineTabs(0, 7); cout << "|===========================================|\n";
    pNewlineTabs(0, 7); cout << "|                                           |\n";
    pNewlineTabs(0, 7); cout << " Enter Current Product Name: ";
    getline(cin >> ws, productName);

    if (productName == "E" || productName == "e") break;

    bool productFound = false;

    for (int i = 0; i < n; i++) {
        if (products[i].name == productName) {
            productFound = true;
            pNewlineTabs(0, 7); cout << "|                                           |\n";
            pNewlineTabs(0, 7); cout << "|-------------------------------------------|\n";
            pNewlineTabs(0,7); cout << " Enter New Product Name: ";
            getline(cin >> ws, products[i].name);
            if (products[i].name == "E" || products[i].name == "e") {
                pNewlineTabs(3, 7); cout << " Operation cancelled.\n";
                pNewlineTabs(1, 7); cout << " Press any key to continue: ";
                cin.ignore(); cin.get(); system("CLS");
                return;
            }
            pNewlineTabs(0, 7); cout << "|-------------------------------------------|\n";
            pNewlineTabs(0,7); cout << " Enter New Product Category: ";
            getline(cin >> ws, products[i].category);
            if (products[i].category == "E" || products[i].category == "e") {
                pNewlineTabs(3, 7); cout << " Operation cancelled.\n";
                pNewlineTabs(1, 7); cout << " Press any key to continue: ";
                cin.ignore(); cin.get(); system("CLS");
                return;
            }
            pNewlineTabs(0, 7); cout << "|-------------------------------------------|\n";
            pNewlineTabs(0,7); cout << " Enter New Store Price: ";
            while (!(cin >> products[i].storePrice)) {
                cin.clear(); cin.ignore();
                pNewlineTabs(0, 7); cout << " Invalid input. Please enter a valid price: ";
            }
            pNewlineTabs(0, 7); cout << "|-------------------------------------------|\n";
            pNewlineTabs(0,7); cout << " Enter New Market Price: ";
            while (!(cin >> products[i].marketPrice)) {
                cin.clear(); cin.ignore();
                pNewlineTabs(0, 7); cout << " Invalid input. Please enter a valid price: ";
            }
            pNewlineTabs(0, 7); cout << "|-------------------------------------------|\n";
            pNewlineTabs(0,7); cout << " Enter New Stock: ";
            while (!(cin >> products[i].Stock)) {
                cin.clear(); cin.ignore();
                pNewlineTabs(0, 7); cout << " Invalid input. Please enter a valid stock: ";
            }

            pNewlineTabs(3, 7); cout << " Product updated successfully!\n";
            pNewlineTabs(1, 7); cout << " [1] Change More [2] View Products [3] Exit: "; cin >> con; system("CLS");
            if(con == 1){
                changeProduct();
            }else if(con == 2){
                viewProducts();
                pNewlineTabs(10, 9); cout << " [1] Go Back [2] Exit: "; cin >> con;
                if(con == 1 ){
                    changeProduct();
                } else {
                    ofstream outFile("Products_Profile.txt");
                    if (outFile.is_open()) {
                        outFile << n << endl;
                        for (int i = 0; i < n; i++) {
                            outFile << products[i].name << endl;
                            outFile << products[i].storePrice << endl;
                            outFile << products[i].marketPrice << endl;
                            outFile << products[i].category << endl;
                            outFile << products[i].Stock << endl;
                        }
                        outFile.close();
                    }
                    return;
                }
            } else {
                ofstream outFile("Products_Profile.txt");
                if (outFile.is_open()) {
                    outFile << n << endl;
                    for (int i = 0; i < n; i++) {
                        outFile << products[i].name << endl;
                        outFile << products[i].storePrice << endl;
                        outFile << products[i].marketPrice << endl;
                        outFile << products[i].category << endl;
                        outFile << products[i].Stock << endl;
                    }
                    outFile.close();
                }
                return;
            }
        }
    }

    if (!productFound) {
        pNewlineTabs(3,7); cout << " Product not found! Please try again.\n";
        pNewlineTabs(1,7); cout << " Press any key to continue: ";
        cin.ignore(); cin.get(); system("CLS");
    }
  }
}

void deleteProduct() {
    string productName;

    int con = 3; // variable to store the user's choice

    while(true){ // infinite loop until the user chooses to exit
        system("CLS");
        pNewlineTabs(10, 6); cout << "|===============================================================|\n";
        pNewlineTabs(0, 6); cout << " To Exit Please Type (E)\n";
        pNewlineTabs(0, 6); cout << "|===============================================================|\n";
        pNewlineTabs(0, 6); cout << "|                                                               |\n";
        pNewlineTabs(0,6); cout << " Enter the Name of the Product to Delete: ";
        getline(cin >> ws, productName); // get the product name from the user

        if (productName == "E" || productName == "e") break; // if the user wants to exit, break the loop

        bool productFound = false; // flag to indicate if the product is found

        for (int i = 0; i < n; i++) { // iterate through the products array
            if (products[i].name == productName) { // if the product is found
                productFound = true;
                for (int j = i; j < n - 1; j++) { // shift the products array to remove the deleted product
                    products[j] = products[j + 1];
                }
                n--; // decrement the number of products
                pNewlineTabs(0, 6); cout << "|===============================================================|\n";
                pNewlineTabs(2, 6); cout << " Product Deleted Successfully!\n";
                pNewlineTabs(1, 6); cout << " [1] Delete More [2] View Products [3] Exit: "; cin >> con; system("CLS");
                if(con == 1){ // if the user wants to delete more products
                    deleteProduct();
                }else if(con == 2){ // if the user wants to view products
                    viewProducts();
                    pNewlineTabs(10, 9); cout << " [1] Go Back [2] Exit: "; cin >> con;
                    if(con == 1 ){ // if the user wants to go back
                        deleteProduct();
                    } else {
                        ofstream outFile("Products_Profile.txt"); // save the updated products to the file
                        if (outFile.is_open()) {
                            outFile << n << endl;
                            for (int i = 0; i < n; i++) {
                                outFile << products[i].name << endl;
                                outFile << products[i].storePrice << endl;
                                outFile << products[i].marketPrice << endl;
                                outFile << products[i].category << endl;
                                outFile << products[i].Stock << endl;
                            }
                            outFile.close();
                        }
                        return; // exit the function
                    }
                } else { // if the user wants to exit
                    ofstream outFile("Products_Profile.txt"); // save the updated products to the file
                    if (outFile.is_open()) {
                        outFile << n << endl;
                        for (int i = 0; i < n; i++) {
                            outFile << products[i].name << endl;
                            outFile << products[i].storePrice << endl;
                            outFile << products[i].marketPrice << endl;
                            outFile << products[i].category << endl;
                            outFile << products[i].Stock << endl;
                        }
                        outFile.close();
                    }
                    return; // exit the function
                }
            }
        }

        if (!productFound) { // if the product is not found
            pNewlineTabs(0,6); cout << " Product not found! Please try again.\n";
            pNewlineTabs(2,6); cout << " Press any key to try again: ";
            cin.ignore(); cin.get(); system("CLS"); // wait for the user to press a key and clear the screen
        }
    }
}

int main() {

    string fileName = "UserCountFile.txt";
    int count = 0;

    // Open the file and read the current count
    ifstream inFile(fileName);
    if (inFile.is_open()) {
        inFile >> count;
        inFile.close();
    }

    // Increment the count
    count++;

    // Write the new count back to the file
    ofstream outFile(fileName);
    if (outFile.is_open()) {
        outFile << count;
        outFile.close();
    }
    pNewlineTabs(10,4); cout << "|=======================================================================================|\n";
    pNewlineTabs(0,4); cout << "|" << setw(83) << "| NUMBER OF TIMES USERS RUN THIS PROGRAM: " << count << " |" << endl;

    // Open and read product profile data
    ifstream pFile("Products_Profile.txt");
    if (pFile.is_open()) {
        pFile >> n;
        for (int i = 0; i < n; i++) {
            getline(pFile >> ws, products[i].name);
            pFile >> products[i].storePrice;
            pFile >> products[i].marketPrice;
            getline(pFile >> ws, products[i].category);
            pFile >> products[i].Stock;
        }
        pFile.close();
    }

    int choice;
    do {
        int menu;
        string usersName[10];
        string usersPassword[10];
        int userCount = 0;
        Product user;
        string adminUserName, adminPassword;

        pNewlineTabs(0, 4); cout << "|=======================================================================================|\n";
        pNewlineTabs(0, 4); cout << "|                                                                                       |\n";
        pNewlineTabs(0, 4); cout << "|                                  Hello! Welcome To                                    |\n";
        pNewlineTabs(0, 4); cout << "|             Bam! Boom! Box! A Comprehensive Inventory Management System               |\n";
        pNewlineTabs(0, 4); cout << "|                                                                                       |\n";
        pNewlineTabs(0, 4); cout << "|=======================================================================================|\n";
        pNewlineTabs(0, 4); cout << "|                                     Are You A:                                        |\n";
        pNewlineTabs(0, 4); cout << "|              1. User?                                2. Administrator?                |\n";
        pNewlineTabs(0, 4); cout << "|=======================================================================================|\n";
        pNewlineTabs(0, 4); cout << "                                                                   Enter Here: ";
        while (!(cin >> menu)) {
                cin.clear(); cin.ignore();
                pNewlineTabs(0, 4); cout << "|---------------------------------------------------------------------------------------|\n";
                pNewlineTabs(0, 4); cout << " Invalid input! Please enter a integer type: ";
            }


        // For user or admin menu selection
        switch (menu) {
            case 1:
                // User menu
                cin.ignore();
                Login_SignUp(user, usersName, usersPassword, userCount);
                int userChoice;
                do {
                    userChoice = UserMenu();
                    switch (userChoice) {
                        case 1:
                            insertionSort();
                            viewProducts();
                            break;
                        case 2:
                            search_Category();
                            break;
                        case 3:
                            PriceRange_search();
                            break;
                        case 4:
                            compareProducts();
                            break;
                        case 5:
                            // Exit user menu
                            system("CLS");
                            pNewlineTabs(10,8); cout << "|-------------------------|\n";
                            pNewlineTabs(0,8); cout << "|   Exiting user menu     |\n";
                            pNewlineTabs(0,8); cout << "|-------------------------|\n";
                            break;
                        default:
                            // Invalid choice
                            pNewlineTabs(10,8); cout << " Invalid choice! Please try again.\n";
                            pNewlineTabs(2,8); cout << " Press any key to continue: ";
                            cin.ignore(); cin.get(); system("CLS");
                    }
                } while (userChoice != 5);
                break;

            case 2:
                // Admin menu
                cin.ignore();
                loadAdminData(adminUserName, adminPassword);
                adminLogin(adminUserName, adminPassword);
                int adminChoice;
                do {
                    adminChoice = AdminMenu();
                    switch (adminChoice) {
                        case 1:
                            addProduct();
                            break;
                        case 2:
                            changeProduct();
                            break;
                        case 3:
                            deleteProduct();
                            break;
                        case 4:
                            // Exit admin menu
                            system("CLS");
                            pNewlineTabs(10,8); cout << "|-------------------------|\n";
                            pNewlineTabs(0,8); cout << "|   Exiting admin menu    |\n";
                            pNewlineTabs(0,8); cout << "|-------------------------|\n";
                            break;
                        default:
                            // Invalid choice
                            pNewlineTabs(10,8); cout << " Invalid choice! Please try again.\n";
                            pNewlineTabs(2,8); cout << " Press any key to exit: ";
                            cin.ignore(); cin.get(); system("CLS");
                    }
                } while (adminChoice != 4);
                break;

            default:
                // Invalid choice
                pNewlineTabs(10,8); cout << " Invalid choice! Please try again.\n";
                pNewlineTabs(2,8); cout << " Press any key to continue: ";
                cin.ignore(); cin.get(); system("CLS");
        }

        // Return to the main menu or exit
        pNewlineTabs(0, 8); cout << "| 1. Return to Main Menu  |\n";
        pNewlineTabs(0,8);  cout << "|-------------------------|\n";
        pNewlineTabs(0, 8); cout << "| 7. Exit Program         |\n";
        pNewlineTabs(0,8);  cout << "|-------------------------|\n";
        pNewlineTabs(1,8); cout << " Enter your choice: ";
        cin >> choice; system("CLS"); pNewlineTabs(10,0);
    } while (choice != 7);

    // Ending
    pNewlineTabs(0,7); cout << "|===========================================|\n";
    pNewlineTabs(0, 7); cout << "|                Thank You!                 |\n";
    pNewlineTabs(0, 7); cout << "|                For Using                  |\n";
    pNewlineTabs(0, 7); cout << "|            Bam!  Boom!  Box!              |\n";
    pNewlineTabs(0,7); cout << "|===========================================|\n";

    return 0;
}
