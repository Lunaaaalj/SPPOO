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
        availability=false;
        std::cout << "The file has been borrowed." << std::endl;
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
    std::vector<BiblioFiles*> history;
    std::string id,name;
    std::vector<BiblioFiles*> borrowedfiles;
    public:
    User(std::string userId, std::string userName) : id(userId), name(userName) {}
    void borrowfile(BiblioFiles* file) {
        borrowedfiles.push_back(file);
        history.push_back(file);
        file->borrow();
    }
    void returnfile(BiblioFiles* file) { 
        for (auto it = borrowedfiles.begin(); it != borrowedfiles.end(); ++it) {
            if (*it == file) {
                borrowedfiles.erase(it);
                file->returnfile();
                break;
            }
            else {
                std::cout << "The file is not borrowed by this user." << std::endl;
            }   
        }
    }
    void showborrowedfiles() const {
        std::cout << "Borrowed files by " << name << ":" << std::endl;
        for (const auto& file : borrowedfiles) {
            file->showinfo();
        }
    }
    void showhistory() const {
        std::cout << "=======================================" << std::endl;
        std::cout << "Borrowing history for " << name << ":" << std::endl;
        for (const auto& file : history) {
            file->showinfo();
        }
        std::cout << "=======================================" << std::endl;
    }
};