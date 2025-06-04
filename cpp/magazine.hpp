/*
Header file Bibliofile. Abstract class

Angel Luna

Tecnologico de Monterrey

*/


#include <iostream>

class BiblioFiles {
    private:
    std::string idfile,title,author,filetype,fragment;
    int publicationyear;
    bool availability;
    public:

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