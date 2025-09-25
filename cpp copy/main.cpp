#include <ncurses.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "magazine.hpp"
#include "bibliofiles.hpp"
#include "book.hpp"
#include "thesis.hpp"

//this code is just straight up spaghetti code, I know. But i wanted to make it work first, and I DO NOT have the time to refactor it.

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
    result.push_back(field);
    return result;
}

void changeusername(User* user,std::string newname) {
    std::ifstream userFileIn("user.csv");
    if (userFileIn.is_open()) {
        std::string line;
        std::vector<std::string> lines;
        while (std::getline(userFileIn, line)) {
            if (line.find(user->getName()) == 0) {
                lines.push_back(newname + "," + user->getPassword() + "," + user->getborrowedfiles() + "," + user->gethistory());
            } else {
                lines.push_back(line);
            }
        }
        userFileIn.close();
        std::ofstream userFileOut("user.csv", std::ios::out | std::ios::trunc);
        for (const auto& l : lines) {
            userFileOut << l << std::endl;
        }
        userFileOut.close();
    } else {
        printw("FATAL ERROR: Could not open user.csv file for reading.\n");
    }
}

void deleteuser(User* user) {
    std::ifstream userFileIn("user.csv");
    if (userFileIn.is_open()) {
        std::string line;
        std::vector<std::string> lines;
        while (std::getline(userFileIn, line)) {
            if (line.find(user->getName()) != 0) {
                lines.push_back(line);
            }
        }
        userFileIn.close();
        std::ofstream userFileOut("user.csv", std::ios::out | std::ios::trunc);
        for (const auto& l : lines) {
            userFileOut << l << std::endl;
        }
        userFileOut.close();
    } else {
        printw("FATAL ERROR: Could not open user.csv file for reading.\n");
    }
}

void showmenu_1(WINDOW* win, int width) {
    wclear(win);
    int y = 1;
    mvwprintw(win, y++, 2, "Library data loaded successfully!");
    mvwprintw(win, y++, 2, "+--------------------------------------------+");
    mvwprintw(win, y++, 2, "| Welcome to Luna's Library System!          |");
    mvwprintw(win, y++, 2, "+--------------------------------------------+");
    mvwprintw(win, y++, 2, "| [V] View all files in the library           |");
    mvwprintw(win, y++, 2, "| [L] Search for a file (ID/author/title)     |");
    mvwprintw(win, y++, 2, "| [B] Borrow a file                           |");
    mvwprintw(win, y++, 2, "| [R] Return a file                           |");
    mvwprintw(win, y++, 2, "| [S] Show user history                       |");
    mvwprintw(win, y++, 2, "| [F] Show user borrowed files                |");
    mvwprintw(win, y++, 2, "| [U] User settings                           |");
    mvwprintw(win, y++, 2, "| [E] Exit                                    |");
    mvwprintw(win, y++, 2, "+--------------------------------------------+");
    mvwprintw(win, y++, 2, ": ");
    wrefresh(win);
}

void showmenu_V(WINDOW* win) {
    wclear(win);
    int y = 1;
    mvwprintw(win, y++, 2, "+--------------------------------------------+");
    mvwprintw(win, y++, 2, "| View all files in the library              |");
    mvwprintw(win, y++, 2, "+--------------------------------------------+");
    mvwprintw(win, y++, 2, "| [B] Books                                   |");
    mvwprintw(win, y++, 2, "| [T] Thesis                                  |");
    mvwprintw(win, y++, 2, "| [M] Magazines                               |");
    mvwprintw(win, y++, 2, "| [A] All files                               |");
    mvwprintw(win, y++, 2, "| [R] Return to main menu                     |");
    mvwprintw(win, y++, 2, "+--------------------------------------------+");
    mvwprintw(win, y++, 2, ": ");
    wrefresh(win);
}

void showmenu_L(WINDOW* win) {
    wclear(win);
    int y = 1;
    mvwprintw(win, y++, 2, "+--------------------------------------------+");
    mvwprintw(win, y++, 2, "| Search for a file (ID/author/title)        |");
    mvwprintw(win, y++, 2, "+--------------------------------------------+");
    mvwprintw(win, y++, 2, "| [I] Search by ID                            |");
    mvwprintw(win, y++, 2, "| [A] Search by author                        |");
    mvwprintw(win, y++, 2, "| [T] search by title                         |");
    mvwprintw(win, y++, 2, "| [R] Return to main menu                     |");
    mvwprintw(win, y++, 2, "+--------------------------------------------+");
    mvwprintw(win, y++, 2, ": ");
    wrefresh(win);
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
    initscr();
    cbreak();
    noecho();
    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);
    int win_height = 16, win_width = 48;
    int starty = (term_height - win_height) / 2;
    int startx = (term_width - win_width) / 2;
    WINDOW* mainwin = newwin(win_height, win_width, starty, startx);
    box(mainwin, 0, 0);
    wrefresh(mainwin);
    std::vector<BiblioFiles*> library;
    std::vector<User*> users;
    mvwprintw(mainwin, 1, 2, "Loading User data...");
    wrefresh(mainwin);

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
            printw("FATAL ERROR: Invalid user data in line: %s\n", line.c_str());
            userFile.close();
            endwin();
            return 2;
            }
        }
    } else {
        printw("FATAL ERROR: Could not open user.csv file.\n");
        endwin();
        return 1;
    }
    // I love spagetti code, don't you?
    userFile.close();
    mvwprintw(mainwin, 2, 2, "User data loaded successfully!");
    wrefresh(mainwin);

    std::string response;
    bool exitprogram = false;
    while (!exitprogram) {
        showmenu_1(mainwin, win_width);
        char response_buf[100];
        mvwgetnstr(mainwin, 14, 4, response_buf, 99);
        response = response_buf;
        if (response == "E") {
            wclear(mainwin);
            mvwprintw(mainwin, 2, 2, "Exiting the program. Goodbye!");
            wrefresh(mainwin);
            exitprogram = true;
            break;
        }
        //This works, for now.
        if (response == "L") {
            showloginmenu();
            std::string username, password;
            printw("Enter username: ");
            refresh();
            char username_buf[100];
            getnstr(username_buf, 99);
            username = username_buf;
            bool userFound = false;
            for (size_t i = 0; i < users.size(); i++) {
                if (users[i]->getName() == username) {
                    userFound = true;
                    printw("Enter password: ");
                    refresh();
                    char password_buf[100];
                    getnstr(password_buf, 99);
                    password = password_buf;
                    if (users[i]->verifyPassword(password)) {
                        User* currentUser = users[i];
                        printw("Login successful!\n");
                        printw("Loading library data...\n");
                        refresh();

                        // Books processing
                        std::ifstream file("books.csv");
                        if (file.is_open()) {
                            std::string line;
                            std::getline(file, line);
                            while (std::getline(file, line)) {
                                std::vector<std::string> fields = parseCSVLine(line);
                                if (fields.size() >= 10) {
                                    try {
                                        Book* book = new Book(fields[0], fields[1], fields[2], std::stoi(fields[3]),
                                                            fields[4], fields[5], fields[6], fields[7], fields[8], std::stoi(fields[9]));
                                        library.push_back(book);
                                    } catch (const std::exception& e) {
                                        printw("FATAL ERROR: Invalid book data format - %s\n", e.what());
                                        file.close();
                                        endwin();
                                        return 3;
                                    }
                                } else {
                                    printw("FATAL ERROR: Invalid book data format in line: %s\n", line.c_str());
                                    file.close();
                                    endwin();
                                    return 4;
                                }
                            }
                            file.close();
                        } else {
                            printw("FATAL ERROR: Could not open books.csv file.\n");
                            endwin();
                            return 5;
                        }

                        // Thesis processing
                        std::ifstream file2("thesis.csv");
                        if (file2.is_open()) {
                            std::string line;
                            std::getline(file2, line);
                            while (std::getline(file2, line)) {
                                std::vector<std::string> fields = parseCSVLine(line);
                                if (fields.size() >= 11) {
                                    try {
                                        Thesis* thesis = new Thesis(fields[0], fields[1], fields[2], std::stoi(fields[3]),
                                                                  fields[4], fields[5], fields[6], fields[7], fields[8], fields[9], fields[10]);
                                        library.push_back(thesis);
                                    } catch (const std::exception& e) {
                                        printw("FATAL ERROR: Invalid thesis data format - %s\n", e.what());
                                        file2.close();
                                        endwin();
                                        return 6;
                                    }
                                } else {
                                    printw("FATAL ERROR: Invalid thesis data format in line: %s\n", line.c_str());
                                    file2.close();
                                    endwin();
                                    return 7;
                                }
                            }
                            file2.close();
                        } else {
                            printw("FATAL ERROR: Could not open thesis.csv file.\n");
                            endwin();
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
                                        printw("FATAL ERROR: Invalid magazine data format - %s\n", e.what());
                                        file3.close();
                                        endwin();
                                        return 9;
                                    }
                                } else {
                                    printw("FATAL ERROR: Invalid magazine data format in line: %s\n", line.c_str());
                                    file3.close();
                                    endwin();
                                    return 10;
                                }
                            }
                            file3.close();
                        } else {
                            printw("FATAL ERROR: Could not open mags.csv file.\n");
                            endwin();
                            return 11;
                        }

                        printw("All library data loaded successfully!\n");
                        refresh();

                        // main application loop after successful login
                        std::string mainResponse;
                        std::string secondResp;
                        std::string thirdResp;
                        std::string fourthResp;
                        bool loggedIn = true;

                        while (loggedIn) {
                            showmenu_1(mainwin, win_width);
                            std::getline(std::cin, mainResponse);

                            if (mainResponse == "E") {
                                loggedIn = false;
                            } else if (mainResponse == "V") {
                                // Handle view menu
                                while (true) {
                                    showmenu_V(mainwin);
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
                                while (true) {
                                    showmenu_L(mainwin);
                                    std::getline(std::cin, secondResp);
                                    if (secondResp == "R") {
                                        break;
                                    } else if (secondResp == "I") {
                                        while (true) {
                                            std::cout << "======================================" << std::endl;
                                            std::cout << "Enter the ID of the file to search or 'R' to return: ";
                                            std::getline(std::cin, thirdResp);
                                            if (thirdResp == "R") {
                                                break; // Return to search menu
                                            }
                                            bool found = false;
                                            for (size_t k = 0; k < library.size(); k++) {
                                                if (library[k]->getidfile() == thirdResp) {
                                                    found = true;
                                                    std::string fileResponse;
                                                    while (true) {
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
                                                        } else if (fileResponse == "F") {
                                                            library[k]->showfragment();
                                                        } else if (fileResponse == "G") {
                                                            if (library[k]->getfiletype() == "magazine") {
                                                                static_cast<Magazine*>(library[k])->showgeneralcontent();
                                                            } else {
                                                                std::cout << "This file does not have general content." << std::endl;
                                                            }
                                                        } else if (fileResponse == "E") {
                                                            break; // Exit the file handling loop
                                                        } else {
                                                            std::cout << "Invalid option! Please try again." << std::endl;
                                                        }
                                                    }
                                                    break; // Exit the file search loop after handling the file
                                                }
                                            }
                                            if (!found) {
                                                std::cout << "File not found! Please try again." << std::endl;
                                            }
                                        }

                                    } else if (secondResp == "A") {
                                        while (true) {
                                            std::cout << "======================================" << std::endl;
                                            std::cout << "Enter the author name to search or 'R' to return: ";
                                            std::getline(std::cin, thirdResp);
                                            if (thirdResp == "R") {
                                                break; // Return to search menu
                                            }
                                            bool found = false;
                                            for (size_t k = 0; k < library.size(); k++) {
                                                if (library[k]->getauthor() == thirdResp) {
                                                    found = true;
                                                    std::string fileResponse;
                                                    while (true) {
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
                                                        } else if (fileResponse == "F") {
                                                            library[k]->showfragment();
                                                        } else if (fileResponse == "G") {
                                                            if (library[k]->getfiletype() == "magazine") {
                                                                static_cast<Magazine*>(library[k])->showgeneralcontent();
                                                            } else {
                                                                std::cout << "This file does not have general content." << std::endl;
                                                            }
                                                        } else if (fileResponse == "E") {
                                                            break; // Exit the file handling loop
                                                        } else {
                                                            std::cout << "Invalid option! Please try again." << std::endl;
                                                        }
                                                    }
                                                }
                                            }
                                            if (!found) {
                                                std::cout << "No files found by that author! Please try again." << std::endl;
                                            }
                                        }

                                    } else if (secondResp == "T") {

                                    }


                                }
                            } else if (mainResponse == "B") {
                                // Handle borrow menu
                                while (true) {
                                    showmenu_B();
                                    std::getline(std::cin, secondResp);
                                    if (secondResp == "R") {
                                        break;
                                    } else {
                                        bool found = false;
                                        for (size_t j = 0; j < library.size(); j++) {
                                            if (library[j]->getidfile() == secondResp) {
                                                found = true;
                                                // Only show borrow confirmation, not the full file menu
                                                library[j]->showinfo();
                                                std::cout << "Do you want to borrow this file? [Y/N]: ";
                                                std::string confirm;
                                                std::getline(std::cin, confirm);
                                                if (confirm == "Y" || confirm == "y") {
                                                    currentUser->borrowfile(library[j]);
                                                    std::cout << "File borrowed successfully!" << std::endl;
                                                } else {
                                                    std::cout << "Borrowing cancelled." << std::endl;
                                                }
                                                break; // Exit the borrow menu loop after handling the file
                                            }
                                        }
                                        if (!found) {
                                            std::cout << "File not found! Please try again." << std::endl;
                                        }
                                    }
                                }
                            } else if (mainResponse == "R") {
                                // Handle return menu
                                while (true) {
                                    showmenu_R();
                                    std::getline(std::cin, secondResp);
                                    if (secondResp == "R") {
                                        break; // Return to main menu
                                    } else {
                                        bool found = false;
                                        for (size_t j = 0; j < library.size(); j++) {
                                            if (library[j]->getidfile() == secondResp) {
                                                found = true;
                                                currentUser->returnfile(library[j]);
                                                std::cout << "File returned successfully!" << std::endl;
                                                break; // Exit after returning
                                            }
                                        }
                                        if (!found) {
                                            std::cout << "File not found! Please try again." << std::endl;
                                        }
                                    }
                                }
                            } else if (mainResponse == "S") {
                                // Handle user history
                                currentUser->showhistory();
                                std::cout << "Press Enter to return to the main menu." << std::endl;
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Wait for user input
                            } else if (mainResponse == "U") {
                                // Handle user settings
                                showmenu_U();
                                std::string userResponse;
                                std::getline(std::cin, userResponse);
                                if (userResponse == "C") {
                                    std::string newusername;
                                    while (true) {
                                        std::cout << "Enter new username: ";
                                        std::getline(std::cin, newusername);
                                        bool usernameExists = false;
                                        for (const auto& user : users) {
                                            if (user->getName() == newusername) {
                                                usernameExists = true;
                                                break;
                                            }
                                        }
                                        if (!usernameExists) {
                                            changeusername(currentUser, newusername);
                                            std::cout << "Username changed successfully!" << std::endl;
                                            break; // Exit the loop after successful change
                                        } else {
                                            std::cout << "Username already exists! Please choose a different username." << std::endl;
                                        }
                                    }
                                } else if (userResponse == "D") {
                                    std::cout << "Are you sure you want to delete your account? [Y/N]: ";
                                    std::string confirmDelete;
                                    std::getline(std::cin, confirmDelete);
                                    if (confirmDelete == "Y" || confirmDelete == "y") {
                                        deleteuser(currentUser);
                                        std::cout << "Account deleted successfully. Exiting program." << std::endl;
                                        return 0; // Exit the program after deletion
                                    } else {
                                        std::cout << "Account deletion cancelled." << std::endl;
                                    }
                                }

                            }  else if (mainResponse == "F") {
                                // show borrowed files
                                currentUser->showborrowedfiles();
                            }
                            else {
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
            if (!userFound) {
                std::cout << "User not found! Please try again." << std::endl;
            }
        }
        // I have officialy lost my sanity, so I will now implement the registration menu.
        if (response == "R") {
            showregistermenu();
            std::string username, password;
            std::cout << "Enter new username: ";
            std::getline(std::cin, username);
            for (size_t userIdx = 0; userIdx < users.size(); userIdx++) {
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
                    return 12;
                }
                userFile.close();
                std::cout << "Registration successful! You can now log in." << std::endl;
            }
        }
        exitprogram = false;
    }

    // Free dynamically allocated memory before exiting
    for (auto ptr : users) {
        delete ptr;
    }
    for (auto ptr : library) {
        delete ptr;
    }
    delwin(mainwin);
    endwin();
    return 0;
}
