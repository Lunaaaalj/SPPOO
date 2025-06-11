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
    // I love spagetti code, don't you?
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
        //This works, for now.
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
                        User* currentUser = users[i]; // Store the logged-in user
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
                        
                        // main application loop after successful login
                        std::string mainResponse;
                        std::string secondResp;
                        std::string thirdResp;
                        std::string fourthResp;
                        bool loggedIn = true;

                        while (loggedIn) {
                            showmenu_1();
                            std::getline(std::cin, mainResponse);
                            
                            if (mainResponse == "E") {
                                loggedIn = false;
                            } else if (mainResponse == "V") {
                                // Handle view menu
                                while (true) {
                                    showmenu_V();
                                    std::getline(std::cin, secondResp);
                                    if (secondResp == "E") {
                                        break;
                                    }
                                    else if (secondResp == "B") {
                                        while (true) {
                                        std::cout << "======================================" << std::endl;
                                        for (size_t j = 0; j < library.size(); j++) {
                                            if (library[j]->getfiletype() == "book") {
                                                std::cout << "---------------------------------------" << std::endl;
                                                std::cout << library[j]->getidfile() << " - " << library[j]->gettitle() << " by " << library[j]->getauthor() << std::endl;
                                                std::cout << "---------------------------------------" << std::endl;
                                            }
                                        }
                                        std::cout << "======================================" << std::endl;
                                        std::cout << "Enter the ID of the book to view details or 'E' to exit: ";
                                        std::getline(std::cin, thirdResp);
                                        if (thirdResp == "E") {
                                            break;
                                        }
                                        else {
                                            bool found = false;
                                            // In the book details section
                                            for (size_t k = 0; k < library.size(); k++) {
                                                if (library[k]->getidfile() == thirdResp && library[k]->getfiletype() == "book") {
                                                    std::string fileResponse;
                                                    while (true) {
                                                        found = true;
                                                        library[k]->showinfo();
                                                        showfilemenu();
                                                        std::getline(std::cin, fileResponse);
                                                        if (fileResponse == "B") {
                                                            currentUser->borrowfile(library[k]);
                                                            std::cout << "File borrowed successfully!" << std::endl;
                                                            break; // Exit after borrowing
                                                        } else if (fileResponse == "R") {
                                                            currentUser->returnfile(library[k]);
                                                            std::cout << "File returned successfully!" << std::endl;
                                                            break; // Exit after returning
                                                        } else if (fileResponse == "S") {
                                                            library[k]->showinfo();
                                                            // Don't break - allow user to see info and choose another action
                                                        } else if (fileResponse == "F") {
                                                            library[k]->showfragment();
                                                            // Don't break - allow user to see fragment and choose another action
                                                        } else if (fileResponse == "G") {
                                                            if (library[k]->getfiletype() == "magazine") {
                                                                static_cast<Magazine*>(library[k])->showgeneralcontent();
                                                            } else {
                                                                std::cout << "This file does not have general content." << std::endl;
                                                            }
                                                            // Don't break - allow user to choose another action
                                                        } else if (fileResponse == "E") {
                                                            break;
                                                        } else {
                                                            std::cout << "Invalid option! Please try again." << std::endl;
                                                            // Don't break - show menu again for invalid input
                                                        }
                                                    }
                                                    break; // Exit the library search loop after handling the file
                                                }
                                            }
                                            if (!found) {
                                                std::cout << "File not found! Please try again." << std::endl;
                                            }
                                        
                                        }
                                        }
                                    } else if (secondResp == "T") {
                                        // Handle thesis viewing (similar pattern)
                                        while (true) {
                                        std::cout << "======================================" << std::endl;
                                        for (size_t j = 0; j < library.size(); j++) {
                                            if (library[j]->getfiletype() == "thesis") {
                                                std::cout << "---------------------------------------" << std::endl;
                                                std::cout << library[j]->getidfile() << " - " << library[j]->gettitle() << " by " << library[j]->getauthor() << std::endl;
                                                std::cout << "---------------------------------------" << std::endl;
                                            }
                                        }
                                        std::cout << "======================================" << std::endl;
                                        std::cout << "Enter the ID of the thesis to view details or 'E' to exit: ";
                                        std::getline(std::cin, thirdResp);
                                        if (thirdResp == "E") {
                                            break;
                                        }
                                        else {
                                            bool found = false;
                                            for (size_t k = 0; k < library.size(); k++) {
                                                if (library[k]->getidfile() == thirdResp && library[k]->getfiletype() == "thesis") {
                                                    found = true;
                                                    std::string fileResponse;
                                                    while (true) {
                                                        library[k]->showinfo();
                                                        static_cast<Thesis*>(library[k])->showbibliography();
                                                        static_cast<Thesis*>(library[k])->seeabstract();
                                                        showfilemenu();
                                                        std::getline(std::cin, fileResponse);
                                                        if (fileResponse == "B") {
                                                            currentUser->borrowfile(library[k]);
                                                        } else if (fileResponse == "R") {
                                                            currentUser->returnfile(library[k]);
                                                            std::cout << "File returned successfully!" << std::endl;
                                                        } else if (fileResponse == "S") {
                                                            library[k]->showinfo();
                                                        } else if (fileResponse == "F") {
                                                            library[k]->showfragment();
                                                        } else if (fileResponse == "G") {
                                                            std::cout << "This file does not have general content." << std::endl;
                                                        } else if (fileResponse == "E") {
                                                            break;
                                                        } else {
                                                            std::cout << "Invalid option! Please try again." << std::endl;
                                                        }
                                                    }
                                                    break; // Exit the thesis search loop after handling the file
                                                }
                                            }
                                            if (!found) {
                                                std::cout << "File not found! Please try again." << std::endl;
                                            }
                                        }
                                        }
                                        break;
                                    }
                                    else if (secondResp == "M") {
                                        // Handle magazine viewing (similar pattern)
                                        while (true) {
                                        std::cout << "======================================" << std::endl;
                                        for (size_t j = 0; j < library.size(); j++) {
                                            if (library[j]->getfiletype() == "magazine") {
                                                std::cout << "---------------------------------------" << std::endl;
                                                std::cout << library[j]->getidfile() << " - " << library[j]->gettitle() << " by " << library[j]->getauthor() << std::endl;
                                                std::cout << "---------------------------------------" << std::endl;
                                            }
                                        }
                                        std::cout << "======================================" << std::endl;
                                        std::cout << "Enter the ID of the magazine to view details or 'E' to exit: ";
                                        std::getline(std::cin, thirdResp);
                                        if (thirdResp == "E") {
                                            break;
                                        }
                                        else {
                                            bool found = false;
                                            for (size_t k = 0; k < library.size(); k++) {
                                                if (library[k]->getidfile() == thirdResp && library[k]->getfiletype() == "magazine") {
                                                    found = true;
                                                    std::string fileResponse;
                                                    while (true) {
                                                        library[k]->showinfo();
                                                        static_cast<Magazine*>(library[k])->showgeneralcontent();
                                                        showfilemenu();
                                                        std::getline(std::cin, fileResponse);
                                                        if (fileResponse == "B") {
                                                            currentUser->borrowfile(library[k]);
                                                        } else if (fileResponse == "R") {
                                                            currentUser->returnfile(library[k]);
                                                            std::cout << "File returned successfully!" << std::endl;
                                                        } else if (fileResponse == "S") {
                                                            library[k]->showinfo();
                                                        } else if (fileResponse == "F") {
                                                            library[k]->showfragment();
                                                        } else if (fileResponse == "G") {
                                                            static_cast<Magazine*>(library[k])->showgeneralcontent();
                                                        } else if (fileResponse == "E") {
                                                            break;
                                                        } else {
                                                            std::cout << "Invalid option! Please try again." << std::endl;
                                                        }
                                                    }
                                                    break; // Exit the magazine search loop after handling the file
                                                }
                                            }
                                            if (!found) {
                                                std::cout << "File not found! Please try again." << std::endl;
                                            }
                                        }
                                        }
                                        break;
                                    }
                                    else if (secondResp == "A") {
                                        std::cout << "======================================" << std::endl;
                                        std::cout << "All files in the library:" << std::endl;
                                        for (size_t j = 0; j < library.size(); j++) {
                                            std::cout << "---------------------------------------" << std::endl;
                                            std::cout << library[j]->getidfile() << " - " << library[j]->gettitle() << " by " << library[j]->getauthor() << std::endl;
                                            std::cout << "---------------------------------------" << std::endl;
                                        }
                                        std::cout << "======================================" << std::endl;
                                        std::cout << "Enter the ID of the file to view details or 'E' to exit: ";
                                        std::getline(std::cin, thirdResp);
                                        if (thirdResp == "E") {
                                            break;
                                        } else {
                                            for (size_t k = 0; k < library.size(); k++) {
                                                if (library[k]->getidfile() == thirdResp) {
                                                    std::string fileResponse;
                                                    while (true) {
                                                        library[k]->showinfo();
                                                        showfilemenu();
                                                        std::getline(std::cin, fileResponse);
                                                        if (fileResponse == "B") {
                                                            currentUser->borrowfile(library[k]);
                                                        } else if (fileResponse == "R") {
                                                            currentUser->returnfile(library[k]);
                                                            std::cout << "File returned successfully!" << std::endl;
                                                        } else if (fileResponse == "S") {
                                                            library[k]->showinfo();
                                                        } else if (fileResponse == "F") {
                                                            library[k]->showfragment();
                                                        } else if (fileResponse == "G") {
                                                            if (library[k]->getfiletype() == "magazine") {
                                                                static_cast<Magazine*>(library[k])->showgeneralcontent();
                                                            } else {
                                                                std::cout << "This file does not have general content." << std::endl;
                                                            }
                                                        } else if (fileResponse == "E") {
                                                            break;
                                                        } else {
                                                            std::cout << "Invalid option! Please try again." << std::endl;
                                                        }
                                                    }
                                                    break; // Exit the all files viewing loop after handling the file
                                                }
                                            }
                                        }
                                        if (thirdResp.empty()) {
                                            std::cout << "No file selected. Returning to the main menu." << std::endl;
                                        }
                                        // In the all files viewing section
                                        bool found = false; 
                                        // Handle all files viewing
                                        break;
                                    }
                                    else if (secondResp == "R") {
                                        std::cout << "Returning to the main menu..." << std::endl;
                                        break; // Return to main menu
                                    }
                                    else {
                                        std::cout << "Invalid option! Please try again." << std::endl;
                                    }
                                }
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
                std::cout << "User not found! Please try again." << std::endl;
            }

        }
        // I have officialy lost my sanity, so I will now implement the registration menu.
        if (response == "R") {
            showregistermenu();
            std::string username, password;
            std::cout << "Enter new username: ";
            std::getline(std::cin, username);
            for (size_t userIdx = 0; userIdx < users.size(); userIdx++) { // Changed from 'i' to 'userIdx'
                if (users[userIdx]->getName() == username) {
                    std::cout << "Username already exists! Please choose a different username." << std::endl;
                    username.clear();
                    response = "R";
                    break;
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