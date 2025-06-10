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

int main() {

    std::vector<BiblioFiles*> library;
    std::ifstream file("books.csv");
    std::cout << "Loading library data..." << std::endl;
    
    if (file.is_open()) {
        std::string line;
        std::getline(file, line); // Skip header line
        while (std::getline(file, line)) {
            std::vector<std::string> fields = parseCSVLine(line);
            
            if (fields.size() == 10) {
                std::string id = fields[0];
                std::string title = fields[1];
                std::string author = fields[2];
                int publicationyear = std::stoi(fields[3]);
                std::string filetype = fields[4];
                std::string fragment = fields[5];
                std::string isbn = fields[6];
                std::string genre = fields[7];
                std::string publisher = fields[8];
                int pages = std::stoi(fields[9]);
                
                Book* book = new Book(id, title, author, publicationyear, filetype, fragment, isbn, genre, publisher, pages);
                library.push_back(book);
            }
        }
        std::ifstream file2("thesis.csv");
        if (file2.is_open()) {
            std::getline(file2, line); // Skip header line
            while (std::getline(file2, line)) {
                std::vector<std::string> fields= parseCSVLine(line);
                if (fields.size() == 11) {
                    std::string id = fields[0];
                    std::string title = fields[1];
                    std::string author = fields[2];
                    int publicationyear = std::stoi(fields[3]);
                    std::string filetype = fields[4];
                    std::string fragment = fields[5];
                    std::string degree = fields[6];
                    std::string institution = fields[7];
                    std::string advisor = fields[8];
                    std::string biblio = fields[9];  // Changed to string
                    std::string abstract = fields[10]; // Added abstract field
                    
                    Thesis* thesis = new Thesis(id, title, author, publicationyear, filetype, fragment, degree, institution, advisor, biblio, abstract);
                    library.push_back(thesis);
                }
            }
        }
    }
    else {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }
    file.close();
}