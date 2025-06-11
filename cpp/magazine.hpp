/*
Header file magazine. derived class from BiblioFiles

This class represents a magazine in the library system, including attributes such as issue number, periodicity, main theme, editorial, and articles.
It also includes methods to display magazine-specific information and a fragment of the magazine.

Angel Luna

Tecnologico de Monterrey

*/

#pragma once
#include <iostream>
#include <string>
#include "bibliofiles.hpp"

class Magazine : public BiblioFiles {
    private:
    int issueNumber;
    std::string periodicity, maintheme, editorial;
    std::string articles;  // Changed from vector to string
    public:
    Magazine(std::string id, std::string t, std::string a, int year, std::string type, std::string frag, int issueNum, std::string period, std::string theme, std::string edit, std::string arts)
        : BiblioFiles(id, t, a, year, type, frag), issueNumber(issueNum), periodicity(period), maintheme(theme), editorial(edit), articles(arts) {}
    void showfragment() const {
        std::cout << fragment << std::endl;
    }
    void showinfo() const override {
        BiblioFiles::showinfo();
        std::cout << "Issue Number: " << issueNumber << std::endl;
        std::cout << "Periodicity: " << periodicity << std::endl;
        std::cout << "Main Theme: " << maintheme << std::endl;
        std::cout << "Editorial: " << editorial << std::endl;
        std::cout << "=======================================" << std::endl;
    }
    void showgeneralcontent() const {
        std::cout << "======================================" << std::endl;
        std::cout << "General Content of the Magazine:" << std::endl;
        std::cout << articles << std::endl;  // Simply print the string
        std::cout << "======================================" << std::endl;
    }
};

