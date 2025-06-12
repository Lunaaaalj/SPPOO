/*
================================================================================
    File: bibliofiles.hpp

    Description:
        This header file defines the abstract class `BiblioFiles` and the `User` class
        for a library management system. The `BiblioFiles` class represents a generic
        bibliographic file (such as books, magazines, or theses) with attributes like
        ID, title, author, publication year, file type, and a text fragment. It provides
        methods for borrowing, returning, checking availability, and displaying information.
        The `User` class models a library user, maintaining their borrowing history and
        currently borrowed files.

    Classes:
        - BiblioFiles: Abstract base class for library files.
        - User: Represents a library user with borrowing capabilities.

    Author:
        Angel Luna

    Institution:
        Tecnologico de Monterrey

    Note:
        This code was not made entirely by AI. It was developed by a human author,
        with the assistance of AI tools for suggestions and improvements.
================================================================================
*/

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept> // For std::runtime_error

class BiblioFiles {
    protected:
    std::string idfile,title,author,filetype,fragment;
    int publicationyear;
    bool availability;
    public:
    BiblioFiles(std::string id, std::string t, std::string a, int year, std::string type, std::string frag) {
        idfile = id;
        title = t;
        author = a;
        publicationyear = year;
        filetype = type;
        fragment = frag;
        availability = true;
    }
    virtual ~BiblioFiles() {
        std::cout << "BiblioFiles object with ID " << idfile << " is being destroyed." << std::endl;
    } // Virtual destructor for proper cleanup of derived classes
    void borrow() {
        if (!availability) {
            std::cout << "The file is currently unavailable." << std::endl;
            return;
        }
        else {
        availability=false;
        std::cout << "The file has been borrowed." << std::endl;
        }
    }
    void returnfile() {
        availability=true;
        std::cout << "The file has been retrieved." << std::endl;
    }
    void isavailable() const {
        if (availability)
            std::cout << "AVAILABLE" << std::endl;
        else
            std::cout << "UNAVAILABLE" << std::endl;
    }
    std::string getfiletype() const {
        return filetype;
    }
    std::string getidfile() const {
        return idfile;
    }
    std::string gettitle() const {
        return title;
    }
    std::string getauthor() const {
        return author;
    }
     void showfragment() const {
        std::cout << "======================================" << std::endl;
        std::cout << fragment << std::endl;
        std::cout << "======================================" << std::endl;
     };
    virtual void showinfo() const {
        std::cout << "======================================" << std::endl;
        std::cout << "BOOK TITLE: " << title << std::endl;
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "Library ID: " << idfile << std::endl;
        std::cout << "Author: " << author << std::endl;
        std::cout << "Year of publication: " << publicationyear << std::endl;
        std::cout << "Availability: ";
        isavailable();
        std::cout << "File type: " << getfiletype() << std::endl;
    }
};

class User {
    protected:
    std::string history;        // String to store history of borrowed files
    std::string name, password; // User credentials
    std::string borrowedfiles;  // String to store currently borrowed files
    public:
    User(std::string userName, std::string userPassword, std::string borrowedFiles, std::string userHistory) 
        : name(userName), password(userPassword) {}
    
    void borrowfile(BiblioFiles* file) {
        // Add to borrowed files list
        if (!borrowedfiles.empty()) {
            borrowedfiles += ";";  // Use semicolon as separator
        }
        borrowedfiles += file->getidfile();
        
        // Add to history
        if (!history.empty()) {
            history += ";";
        }
        history += file->getidfile();
        
        std::ifstream userFileIn("user.csv");
        if (userFileIn.is_open()) {
            std::string line;
            std::vector<std::string> lines;
            while (std::getline(userFileIn, line)) {
                if (line.find(name) == 0) { // Check if the line starts with the username
                    lines.push_back(name + "," + password + "," + borrowedfiles + "," + history);
                } else {
                    lines.push_back(line);
                }
            }
            userFileIn.close();
            
            // Rewrite the file with updated data
            std::ofstream userFileOut("user.csv", std::ios::out | std::ios::trunc);
            for (const auto& l : lines) {
                userFileOut << l << std::endl;
            }
            userFileOut.close();
        } else {
            std::cerr << "FATAL ERROR: Could not open user.csv file for reading." << std::endl;
        }
        
        file->borrow();
    }
    
    void returnfile(BiblioFiles* file) {
        std::string fileId = file->getidfile();
        size_t pos = borrowedfiles.find(fileId);
        
        if (pos != std::string::npos) {
            // Remove from borrowed files
            if (pos == 0) {
                // File is at the beginning
                if (borrowedfiles.length() == fileId.length()) {
                    borrowedfiles.clear();  // Only file in the list
                } else {
                    borrowedfiles = borrowedfiles.substr(fileId.length() + 1);  // Remove file and semicolon
                }
            } else {
                // File is in the middle or end
                borrowedfiles.erase(pos - 1, fileId.length() + 1);  // Remove semicolon and file
            }
            
            file->returnfile();
        } else {
            std::cout << "The file is not borrowed by this user." << std::endl;
        }
    }
    
    void showborrowedfiles() const {
        std::cout << "=======================================" << std::endl;
        std::cout << "Borrowed files by " << name << ":" << std::endl;
        if (borrowedfiles.empty()) {
            std::cout << "No files currently borrowed." << std::endl;
        } else {
            std::cout << borrowedfiles << std::endl;
        }
        std::cout << "=======================================" << std::endl;
    }
    
    void showhistory() const {
        std::cout << "=======================================" << std::endl;
        std::cout << "Borrowing history for " << name << ":" << std::endl;
        if (history.empty()) {
            std::cout << "No borrowing history." << std::endl;
        } else {
            std::cout << history << std::endl;
        }
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "NOTE: History shown from last session." << std::endl;
        std::cout << "=======================================" << std::endl;
    }
    
    // Getter methods
    std::string getName() const { return name; }
    bool verifyPassword(const std::string& pass) const { return password == pass; }
    std::string getborrowedfiles() const { return borrowedfiles; }
    std::string gethistory() const { return history; }
    std::string getPassword() const { return password; }
    std::string getUserInfo() const {
        return name + "," + password + "," + borrowedfiles + "," + history;
    }

    
    // Password management
    void changePassword(const std::string& newPassword) { password = newPassword; }
};