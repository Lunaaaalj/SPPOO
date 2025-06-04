/*
Header file Bibliofile. Abstract class

Angel Luna

Tecnologico de Monterrey

*/


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
    void borrow() {
        availability=false; //pendiente: integrar con la clase usuario
        std::cout << "The file has been borrowed." << std::endl;
    }
    void returnfile() {
        availability=true;
        std::cout << "The file has been retrieved." << std::endl;
    }
    void isavailable() const {
        switch(availability) {
            case true:
            std::cout << "AVAILABLE" << std::endl;
            break;
            case false:
            std::cout << "UNAVAILABLE" << std::endl;
            break; 
        }
    }
    std::string getfiletype() const {
        return filetype;
    }
     void showfragment() const {
        std::cout << fragment << std::endl;
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