/*
header file for thesis class.
This class is derived from BiblioFiles and represents a thesis in the library system.
It includes attributes such as the degree, university, and advisor, along with methods to display thesis-specific information.

Angel Luna

Technologico de Monterrey
*/

#pragma once
#include <iostream>
#include <string>
#include "bibliofiles.hpp"

class Thesis : public BiblioFiles {
    private:
    std::string degree, institution, advisor, abstract;
    std::string biblio;
    public:
    Thesis(std::string id, std::string t, std::string a, int year, std::string type, std::string frag, std::string deg, std::string inst, std::string adv, std::string bib, std::string abs)
        : BiblioFiles(id, t, a, year, type, frag), degree(deg), institution(inst), advisor(adv), abstract(abs), biblio(bib) {}
    void showinfo() const override {
        BiblioFiles::showinfo();
        std::cout << "Degree: " << degree << std::endl;
        std::cout << "Institution: " << institution << std::endl;
        std::cout << "Advisor: " << advisor << std::endl;
        std::cout << "=======================================" << std::endl;
    }
    void showbibliography() const {
        std::cout << "=======================================" << std::endl;
        std::cout << "Bibliography:" << std::endl;
        std::cout << biblio << std::endl;
        std::cout << "=======================================" << std::endl;
    }
    void seeabstract() const {
        std::cout << "=======================================" << std::endl;
        std::cout << abstract << std::endl;
        std::cout << "=======================================" << std::endl;
    }
};