/*
Header file for Book class
Derived class from BiblioFiles

Angel Luna
Tecnologico de Monterrey

*/


#include <iostream>
#include <vector>
#include <string>
#include "bibliofiles.hpp"

class Book : public BiblioFiles {
    private:
    std::string ISBN,genre,publisher;
    int pages;
    public:
    Book(std::string id, std::string t, std::string a, int year, std::string type, std::string frag, std::string isbn, std::string gen, std::string pub, int p)
        : BiblioFiles(id, t, a, year, type, frag), ISBN(isbn), genre(gen), publisher(pub), pages(p) {}
    void showfragment() const {
        std::cout << fragment << std::endl;
    }
    void showinfo() const override {
        BiblioFiles::showinfo();
        std::cout << "ISBN: " << ISBN << std::endl;
        std::cout << "Genre: " << genre << std::endl;
        std::cout << "Publisher: " << publisher << std::endl;
        std::cout << "Pages: " << pages << std::endl;
        std::cout << "=======================================" << std::endl;
    }
};