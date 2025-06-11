#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "magazine.hpp"
#include "bibliofiles.hpp"
#include "book.hpp"
#include "thesis.hpp"


std::vector<std::string> parseCSVLine(const std::string& line) {
    std::vector<std::string> result;
    std::string field;
    bool inQuotes = false;
    
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            result.push_back(field);
            field.clear();
        } else {
            field += c;
        }
    }
    result.push_back(field); // Add the last field
    return result;
}

void showmenu_1() {
    std::cout << "Library data loaded successfully!" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| Welcome to Luna's Library System!          |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| [V] View all files in the library           |" << std::endl;
    std::cout << "| [L] Search for a file (ID/author/title)     |" << std::endl;
    std::cout << "| [B] Borrow a file                           |" << std::endl;
    std::cout << "| [R] Return a file                           |" << std::endl;
    std::cout << "| [S] Show user history                       |" << std::endl;
    std::cout << "| [U] User settings                           |" << std::endl;
    std::cout << "| [E] Exit                                    |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << ": ";
}

void showmenu_V() {
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| View all files in the library              |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| [B] Books                                   |" << std::endl;
    std::cout << "| [T] Thesis                                  |" << std::endl;
    std::cout << "| [M] Magazines                               |" << std::endl;
    std::cout << "| [A] All files                               |" << std::endl;
    std::cout << "| [R] Return to main menu                     |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << ": ";
}

void showmenu_L() {
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| Search for a file (ID/author/title)        |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| [I] Search by ID                            |" << std::endl;
    std::cout << "| [A] Search by author                        |" << std::endl;
    std::cout << "| [T] search by title                         |" << std::endl;
    std::cout << "| [R] Return to main menu                     |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << ": ";
}

void showmenu_B() {
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| Borrow a file                               |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| Enter the ID of the file to borrow:        |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << ": ";
}
void showmenu_R() {
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| Return a file                               |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| Enter the ID of the file to return:        |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << ": ";
}
void showmenu_S() {
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| Show user history                           |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| [H] Show borrowing history                  |" << std::endl;
    std::cout << "| [R] Return to main menu                     |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << ": ";
}
void showmenu_U() {
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| User settings                               |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| [C] Change user name                        |" << std::endl;
    std::cout << "| [D] Delete user                             |" << std::endl;
    std::cout << "| [R] Return to main menu                     |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << ": ";
}

void showmenu() {
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| Luna's Library System                       |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| [L] Login                                    |" << std::endl;
    std::cout << "| [R] Register                                 |" << std::endl;
    std::cout << "| [E] Exit                                     |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << ": ";
}

void showloginmenu() {
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| Luna's Library System - Login              |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
}

void showregistermenu() {
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "| Luna's Library System - Register            |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
}

void showfilemenu() {
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "[B] Borrow                                    | " << std::endl;
    std::cout << "[R] Return                                    | " << std::endl;
    std::cout << "[S] Show info                                 | " << std::endl;
    std::cout << "[F] Show fragment                             | " << std::endl;
    std::cout << "[G] Show general content                      | " << std::endl;
    std::cout << "[E] Exit                                      | " << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << ": ";

}

int main() {
    std::vector<BiblioFiles*> library;
    std::vector<User*> users;
    std::cout << "Loading User data..." << std::endl;

    std::ifstream userFile("user.csv");
    if (userFile.is_open()) {
        std::string line;
        std::getline(userFile, line); // Skip header line
        while (std::getline(userFile, line)) {
            std::vector<std::string> fields = parseCSVLine(line);
            
            if (fields.size() >= 4) {
                User* user = new User(fields[0], fields[1], fields[2], fields[3]);
                users.push_back(user);
            } else {
                std::cerr << "FATAL ERROR: Invalid user data in line: " << line << std::endl;
                userFile.close();
                return 2; // Exit on invalid user data format
            }
        }
    } else {
        std::cerr << "FATAL ERROR: Could not open user.csv file." << std::endl;
        return 1; // Exit if user data cannot be loaded
    }
    userFile.close();
    std::cout << "User data loaded successfully!" << std::endl;

    std::string response;
    bool exitprogram = false;
    while (!exitprogram) {
        showmenu();
        std::getline(std::cin, response);
        if (response == "E") {
            std::cout << "Exiting the program. Goodbye!" << std::endl;
            exitprogram = true;
            break;
        }
        if (response == "L") {
            showloginmenu();
            std::string username, password;
            std::cout << "Enter username: ";
            std::getline(std::cin, username);
            for (size_t i = 0; i < users.size(); i++) {
                if (users[i]->getName() == username) {
                    std::cout << "Enter password: ";
                    std::getline(std::cin, password);
                    if (users[i]->verifyPassword(password)) {
                        std::cout << "Login successful!" << std::endl;
                        std::cout << "Loading library data..." << std::endl;

                        // Books processing
                        std::ifstream file("books.csv");
                        if (file.is_open()) {
                            std::string line;
                            std::getline(file, line); // Skip header line
                            while (std::getline(file, line)) {
                                std::vector<std::string> fields = parseCSVLine(line);
                                
                                if (fields.size() >= 10) {
                                    try {
                                        Book* book = new Book(fields[0], fields[1], fields[2], std::stoi(fields[3]), 
                                                            fields[4], fields[5], fields[6], fields[7], fields[8], std::stoi(fields[9]));
                                        library.push_back(book);
                                    } catch (const std::exception& e) {
                                        std::cerr << "FATAL ERROR: Invalid book data format - " << e.what() << std::endl;
                                        file.close();
                                        return 3;
                                    }
                                } else {
                                    std::cerr << "FATAL ERROR: Invalid book data format in line: " << line << std::endl;
                                    file.close();
                                    return 4;
                                }
                            }
                            file.close();
                        } else {
                            std::cerr << "FATAL ERROR: Could not open books.csv file." << std::endl;
                            return 5;
                        }
                        
                        // Thesis processing
                        std::ifstream file2("thesis.csv");
                        if (file2.is_open()) {
                            std::string line;
                            std::getline(file2, line); // Skip header line
                            while (std::getline(file2, line)) {
                                std::vector<std::string> fields = parseCSVLine(line);
                                if (fields.size() >= 11) {
                                    try {
                                        Thesis* thesis = new Thesis(fields[0], fields[1], fields[2], std::stoi(fields[3]), 
                                                                  fields[4], fields[5], fields[6], fields[7], fields[8], fields[9], fields[10]);
                                        library.push_back(thesis);
                                    } catch (const std::exception& e) {
                                        std::cerr << "FATAL ERROR: Invalid thesis data format - " << e.what() << std::endl;
                                        file2.close();
                                        return 6;
                                    }
                                } else {
                                    std::cerr << "FATAL ERROR: Invalid thesis data format in line: " << line << std::endl;
                                    file2.close();
                                    return 7;
                                }
                            }
                            file2.close();
                        } else {
                            std::cerr << "FATAL ERROR: Could not open thesis.csv file." << std::endl;
                            return 8;
                        }

                        // Magazine processing
                        std::ifstream file3("mags.csv");  
                        if (file3.is_open()) {
                            std::string line;
                            std::getline(file3, line); 
                            while (std::getline(file3, line)) {
                                std::vector<std::string> fields = parseCSVLine(line);
                                if (fields.size() >= 11) {
                                    try {
                                        Magazine* magazine = new Magazine(fields[0], fields[1], fields[2], std::stoi(fields[3]), 
                                                                        fields[4], fields[5], std::stoi(fields[6]), fields[7], 
                                                                        fields[8], fields[9], fields[10]);
                                        library.push_back(magazine);
                                    } catch (const std::exception& e) {
                                        std::cerr << "FATAL ERROR: Invalid magazine data format - " << e.what() << std::endl;
                                        file3.close();
                                        return 9;
                                    }
                                } else {
                                    std::cerr << "FATAL ERROR: Invalid magazine data format in line: " << line << std::endl;
                                    file3.close();
                                    return 10;
                                }
                            }
                            file3.close();  
                        } else {
                            std::cerr << "FATAL ERROR: Could not open mags.csv file." << std::endl;
                            return 11;
                        }
                        
                        std::cout << "All library data loaded successfully!" << std::endl;
                        
                        // Main application loop after successful login
                        std::string mainResponse;
                        bool loggedIn = true;
                        while (loggedIn) {
                            showmenu_1();
                            std::getline(std::cin, mainResponse);
                            
                            if (mainResponse == "E") {
                                loggedIn = false;
                                exitprogram = true;
                            } else if (mainResponse == "V") {
                                // Handle view menu
                            } else if (mainResponse == "L") {
                                // Handle search menu
                            } else if (mainResponse == "B") {
                                // Handle borrow menu
                            } else if (mainResponse == "R") {
                                // Handle return menu
                            } else if (mainResponse == "S") {
                                // Handle user history
                            } else if (mainResponse == "U") {
                                // Handle user settings
                            } else {
                                std::cout << "Invalid option! Please try again." << std::endl;
                            }
                        }
                        break; // Exit the user search loop after successful login
                    } else {
                        std::cout << "Incorrect password!" << std::endl;
                    }
                    break; // Exit the user search loop (user found but wrong password)
                } 
            }
                    std::cout << "User not found! Please try again." << std::endl;
        }
        if (response == "R") {
            showregistermenu();
            std::string username, password;
            std::cout << "Enter new username: ";
            std::getline(std::cin, username);
            for (size_t i = 0; i < users.size(); i++) {
                if (users[i]->getName() == username) {
                    std::cout << "Username already exists! Please choose a different username." << std::endl;
                    username.clear();
                    response = "R"; // Reset response to allow re-entry
                    break; // Exit the loop if username already exists
                }
            }
            if (!username.empty()) {
                std::cout << "Enter new password: ";
                std::getline(std::cin, password);
                User* newUser = new User(username, password, "","");
                users.push_back(newUser);
                std::ofstream userFile("user.csv", std::ios::app);
                if (userFile.is_open()) {
                    userFile << username << "," << password << ",," << std::endl;
                }
                else {
                    std::cerr << "FATAL ERROR: Could not open user.csv file for writing." << std::endl;
                    return 12; // Exit if user data cannot be saved
                }
                userFile.close();
                std::cout << "Registration successful! You can now log in." << std::endl;
            }
        }
        exitprogram = false; // Reset exit flag to allow re-entry into the main menu
    }

}