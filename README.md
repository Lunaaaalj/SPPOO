# Luna's Library System

A console-based library management application developed in C++ that simulates the core functionalities of a digital library system.

## Overview

Luna's Library System is designed to demonstrate object-oriented programming principles, file handling, and menu-driven user interfaces in C++. The system allows users to register, log in, borrow and return various types of library items (books, theses, and magazines), and view their borrowing history. All data is stored persistently using CSV files, ensuring information is retained between sessions.

## Features

- **User Management**
  - User registration with unique username validation
  - Secure login authentication
  - User settings and account management

- **Library Operations**
  - Browse available library items (books, theses, magazines)
  - Borrow and return library items
  - View item information and content fragments
  - Track borrowing history

- **Data Persistence**
  - CSV-based storage for users and library items
  - Automatic data synchronization between sessions
  - Consistent data management

## Project Structure

```
cpp/
├── main.cpp              # Main program logic and menu handling
├── bibliofiles.hpp       # Base class for library items
├── book.hpp              # Book class implementation
├── thesis.hpp            # Thesis class implementation
├── magazine.hpp          # Magazine class implementation
├── user.csv              # User data storage
├── books.csv             # Books data storage
├── thesis.csv            # Theses data storage
└── mags.csv              # Magazines data storage
```

## Key Classes

### BiblioFiles (Base Class)
The base class for all library items, containing common attributes:
- File ID, title, author
- Publication year
- File type and content fragment
- Availability status

### Derived Classes
- **Book**: Extends BiblioFiles with book-specific features
- **Thesis**: Extends BiblioFiles with thesis-specific features
- **Magazine**: Extends BiblioFiles with magazine-specific features

### User Class
Manages user data and operations:
- User authentication
- Borrowing and returning library items
- Borrowing history tracking

## Technologies Used

- **Language**: C++
- **Build System**: CMake
- **Data Storage**: CSV files
- **File I/O**: Standard C++ streams (ifstream, ofstream)

## Installation

### Prerequisites
- C++ compiler (g++, clang++)
- CMake (version 3.10 or higher)
- ncurses library (optional, for enhanced terminal UI)

### Building the Project

```bash
cd cpp
mkdir build
cd build
cmake ..
make
```

### Running the Application

```bash
./main
```

## Usage

1. **First Time Users**
   - Choose "Register" from the main menu
   - Create a unique username and password
   - Log in with your credentials

2. **Browsing and Borrowing**
   - View available library items
   - Search for specific items
   - Borrow items by entering their ID
   - View borrowed items in your history

3. **Returning Items**
   - Select "Return" from the menu
   - Enter the ID of the borrowed item
   - Confirm the return

4. **User History**
   - View your complete borrowing history
   - Track which items you've borrowed

## Object-Oriented Principles Demonstrated

- **Inheritance**: BiblioFiles base class with derived classes (Book, Thesis, Magazine)
- **Encapsulation**: Protected and private member variables with public methods
- **Polymorphism**: Base class pointers for different item types
- **Abstraction**: Separation of interface and implementation

## Future Enhancements

- Additional file types (audiobooks, videos, etc.)
- Advanced search and filtering capabilities
- Graphical User Interface (GUI)
- Multi-user networked support
- Web-based interface
- Database integration for scalability

## Documentation

For detailed documentation including class diagrams, program flow, and implementation details, see the [documentation PDF](./documentation/main.pdf).

## License

This project is developed as an educational tool to demonstrate C++ programming concepts and library management system design.

## Author

Angel E Luna
