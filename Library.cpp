#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <sstream>
using namespace std;

// ===================== BOOK CLASS =====================
class Book {
private:
    int id;
    string title;
    string author;
    string category;
    bool isIssued;

public:
    Book() {
        id = 0;
        title = "";
        author = "";
        category = "General";
        isIssued = false;
    }
    
    Book(int i, string t, string a, string cat) {
        id = i;
        title = t;
        author = a;
        category = cat;
        isIssued = false;
    }

    void display() {
        cout << id << "\t" << title << "\t\t" << author << "\t\t" << category << "\t\t" << (isIssued ? "Issued" : "Available") << endl;
    }

    void displaySimple() {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author << ", Category: " << category << ", Status: " << (isIssued ? "Issued" : "Available") << endl;
    }

    void issueBook() { isIssued = true; }
    void returnBook() { isIssued = false; }

    int getId() { return id; }
    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getCategory() { return category; }
    bool getStatus() { return isIssued; }
    
    void setTitle(string t) { title = t; }
    void setAuthor(string a) { author = a; }
    void setCategory(string c) { category = c; }
};

// ===================== USER CLASS =====================
class User {
private:
    int userId;
    string name;
    vector<Book> borrowedBooks;

public:
    User(int id, string n) {
        userId = id;
        name = n;
    }

    void displayUser() {
        cout << "\n--- User Details ---\n";
        cout << "User ID: " << userId << ", Name: " << name << endl;
        cout << "Borrowed Books: " << borrowedBooks.size() << endl;

        if (borrowedBooks.size() == 0) {
            cout << "No borrowed books.\n";
        }
        else {
            cout << "\nBorrowed Books List:\n";
            cout << "------------------------------------------------\n";
            cout << "ID\tTitle\t\t\tAuthor\n";
            cout << "------------------------------------------------\n";
            for (int i = 0; i < borrowedBooks.size(); i++) {
                cout << borrowedBooks[i].getId() << "\t" 
                     << borrowedBooks[i].getTitle() << "\t\t"
                     << borrowedBooks[i].getAuthor() << endl;
            }
            cout << "------------------------------------------------\n";
        }
    }

    void borrowBook(Book book) {
        borrowedBooks.push_back(book);
    }

    void returnBook(int bookId) {
        for (int i = 0; i < borrowedBooks.size(); i++) {
            if (borrowedBooks[i].getId() == bookId) {
                borrowedBooks.erase(borrowedBooks.begin() + i);
                cout << "Book ID " << bookId << " removed from user's borrowed list.\n";
                return;
            }
        }
        cout << "Book not found in user's borrowed list.\n";
    }

    int getUserId() { return userId; }
    string getName() { return name; }
};

// ===================== LIBRARY CLASS =====================
class Library {
private:
    vector<Book> books;

public:
    void addBook(Book book) {
        books.push_back(book);
    }

    void displayBooks() {
        if (books.size() == 0) {
            cout << "No books in library.\n";
        }
        else {
            cout << "\n======================================================================================\n";
            cout << "ID\tTitle\t\t\tAuthor\t\t\tCategory\t\tStatus\n";
            cout << "======================================================================================\n";
            for (int i = 0; i < books.size(); i++) {
                books[i].display();
            }
            cout << "======================================================================================\n";
            cout << "Total Books: " << books.size() << endl;
        }
    }

    int searchBookById(int id) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getId() == id) {
                return i; 
            }
        }
        return -1;
    }

    void searchBookByTitle(string title) {
        cout << "\nSearch Results for Title containing: \"" << title << "\"\n";
        cout << "------------------------------------------------\n";
        bool found = false;
        for (int i = 0; i < books.size(); i++) {
            string bookTitle = books[i].getTitle();
            // Convert both to lowercase for case-insensitive search
            transform(bookTitle.begin(), bookTitle.end(), bookTitle.begin(), ::tolower);
            transform(title.begin(), title.end(), title.begin(), ::tolower);
            
            if (bookTitle.find(title) != string::npos) {
                books[i].displaySimple();
                found = true;
            }
        }
        if (!found) {
            cout << "No books found with that title.\n";
        }
    }

    void searchBookByAuthor(string author) {
        cout << "\nSearch Results for Author: \"" << author << "\"\n";
        cout << "------------------------------------------------\n";
        bool found = false;
        for (int i = 0; i < books.size(); i++) {
            string bookAuthor = books[i].getAuthor();
            // Convert both to lowercase for case-insensitive search
            transform(bookAuthor.begin(), bookAuthor.end(), bookAuthor.begin(), ::tolower);
            transform(author.begin(), author.end(), author.begin(), ::tolower);
            
            if (bookAuthor.find(author) != string::npos) {
                books[i].displaySimple();
                found = true;
            }
        }
        if (!found) {
            cout << "No books found by that author.\n";
        }
    }

    Book getBook(int index) {
        return books[index];
    }

    void issueBook(int index) {
        books[index].issueBook();
    }

    void returnBook(int index) {
        books[index].returnBook();
    }

    void updateBook(int index) {
        int choice;
        cout << "\nWhat do you want to update?\n";
        cout << "1. Update Title\n";
        cout << "2. Update Author\n";
        cout << "3. Update Category\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string newTitle;
            cout << "Enter new title: ";
            getline(cin, newTitle);
            books[index].setTitle(newTitle);
            cout << "Title updated successfully!\n";
        }
        else if (choice == 2) {
            string newAuthor;
            cout << "Enter new author: ";
            getline(cin, newAuthor);
            books[index].setAuthor(newAuthor);
            cout << "Author updated successfully!\n";
        }
        else if (choice == 3) {
            string newCategory;
            cout << "Enter new category: ";
            getline(cin, newCategory);
            books[index].setCategory(newCategory);
            cout << "Category updated successfully!\n";
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    void deleteBook(int index) {
        if (index >= 0 && index < books.size()) {
            cout << "Deleting book: " << books[index].getTitle() << endl;
            books.erase(books.begin() + index);
            cout << "Book deleted successfully!"<<endl;
        }
    }

    int getTotalBooks() {
        return books.size();
    }

    void sortBooksById() {
        for (int i = 0; i < books.size() - 1; i++) {
            for (int j = 0; j < books.size() - i - 1; j++) {
                if (books[j].getId() > books[j + 1].getId()) {
                    swap(books[j], books[j + 1]);
                }
            }
        }
        cout << "Books sorted by ID!"<<endl;
    }

    void sortBooksByTitle() {
        for (int i = 0; i < books.size() - 1; i++) {
            for (int j = 0; j < books.size() - i - 1; j++) {
                if (books[j].getTitle() > books[j + 1].getTitle()) {
                    swap(books[j], books[j + 1]);
                }
            }
        }
        cout << "Books sorted by Title!"<<endl;
    }

    void sortBooksByAuthor() {
        for (int i = 0; i < books.size() - 1; i++) {
            for (int j = 0; j < books.size() - i - 1; j++) {
                if (books[j].getAuthor() > books[j + 1].getAuthor()) {
                    swap(books[j], books[j + 1]);
                }
            }
        }
        cout << "Books sorted by Author!\n";
    }

    void saveToFile() {
        ofstream file("library_data.txt");
        if (file.is_open()) {
            for (int i = 0; i < books.size(); i++) {
                file << books[i].getId() << ","
                     << books[i].getTitle() << ","
                     << books[i].getAuthor() << ","
                     << books[i].getCategory() << ","
                     << books[i].getStatus() << "\n";
            }
            file.close();
            cout << "Data saved to file successfully!\n";
        }
        else {
            cout << "Unable to open file for saving.\n";
        }
    }

    void loadFromFile() {
        ifstream file("library_data.txt");
        if (file.is_open()) {
            books.clear(); // Clear existing books
            string line;
            int count = 0;
            
            while (getline(file, line)) {
                int id, status;
                string title, author, category;
                size_t pos1 = line.find(',');
                size_t pos2 = line.find(',', pos1 + 1);
                size_t pos3 = line.find(',', pos2 + 1);
                size_t pos4 = line.find(',', pos3 + 1);
                
                if (pos1 != string::npos && pos2 != string::npos && 
                    pos3 != string::npos && pos4 != string::npos) {
                    
                    id = stoi(line.substr(0, pos1));
                    title = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    author = line.substr(pos2 + 1, pos3 - pos2 - 1);
                    category = line.substr(pos3 + 1, pos4 - pos3 - 1);
                    status = stoi(line.substr(pos4 + 1));
                    
                    Book book(id, title, author, category);
                    if (status == 1) {
                        book.issueBook();
                    }
                    books.push_back(book);
                    count++;
                }
            }
            file.close();
            cout << "Loaded " << count << " books from file.\n";
        }
    }
          bool isBookIdExists(int id) {
          for (int i = 0; i < books.size(); i++) {
          if (books[i].getId() == id) {
            return true;
        }
    }
    return false;
}

};

// Function to show loading animation
void showLoading() {
    cout << "Processing";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        cout.flush();
        // Simple delay
        for (int j = 0; j < 10000000; j++);
    }
    cout << " Done!\n";
}

// Function to press enter
void pressEnterToContinue() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// Function to clear screen
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// ===================== MAIN FUNCTION =====================
int main() {
    Library library;
    vector<User> users;

    // Load data from file at start
    cout << "Loading library data";
    showLoading();
    library.loadFromFile();

    int choice;

    do {
        clearScreen();
        cout << "\n========================================\n";
        cout << "     LIBRARY MANAGEMENT SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Update Book Information\n";
        cout << "5. Delete Book\n";
        cout << "6. Sort Books\n";
        cout << "7. Show Total Books Count\n";
        cout << "8. Add User\n";
        cout << "9. Display All Users\n";
        cout << "10. Issue Book\n";
        cout << "11. Return Book\n";
        cout << "12. Save Data to File\n";
        cout << "0. Exit\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: { // ADD BOOK
                int id;
                string title, author, category;
                
                cout << "\n--- Add New Book ---\n";
                cout << "Enter Book ID: ";
                cin >> id;
                
                cin.ignore();
                cout << "Enter Title: ";
                getline(cin, title);
                
                cout << "Enter Author: ";
                getline(cin, author);
                
                cout << "Enter Category (Novel/Science/History/Programming/General): ";
                getline(cin, category);
                
                if (category == "") category = "General";
                
                if (library.isBookIdExists(id)) {
                 cout << "❌ ID already exists!\n";
}
              else {
                     Book book(id, title, author, category);
                 library.addBook(book);
}

                
                showLoading();
                cout << "Book added successfully!\n";
                pressEnterToContinue();
                break;
            }
            
            case 2: { // DISPLAY ALL BOOKS
                library.displayBooks();
                pressEnterToContinue();
                break;
            }
            
            case 3: { // SEARCH BOOK
                int searchChoice;
                cout << "\n--- Search Book ---\n";
                cout << "1. Search by ID\n";
                cout << "2. Search by Title\n";
                cout << "3. Search by Author\n";
                cout << "Enter choice: ";
                cin >> searchChoice;
                cin.ignore();
                
                if (searchChoice == 1) {
                    int id;
                    cout << "Enter Book ID to search: ";
                    cin >> id;
                    int index = library.searchBookById(id);
                    if (index != -1) {
                        cout << "\nBook Found:\n";
                        library.getBook(index).displaySimple();
                    }
                    else {
                        cout << "Book not found.\n";
                    }
                }
                else if (searchChoice == 2) {
                    string title;
                    cout << "Enter title to search: ";
                    getline(cin, title);
                    library.searchBookByTitle(title);
                }
                else if (searchChoice == 3) {
                    string author;
                    cout << "Enter author to search: ";
                    getline(cin, author);
                    library.searchBookByAuthor(author);
                }
                else {
                    cout << "Invalid choice!\n";
                }
                pressEnterToContinue();
                break;
            }
            
            case 4: { // UPDATE BOOK
                int id;
                cout << "\n--- Update Book Information ---\n";
                cout << "Enter Book ID to update: ";
                cin >> id;
                
                int index = library.searchBookById(id);
                if (index != -1) {
                    cout << "Current Book Information:\n";
                    library.getBook(index).displaySimple();
                    library.updateBook(index);
                }
                else {
                    cout << "Book not found.\n";
                }
                pressEnterToContinue();
                break;
            }
            
            case 5: { // DELETE BOOK
                int id;
                cout << "\n--- Delete Book ---\n";
                cout << "Enter Book ID to delete: ";
                cin >> id;
                
                int index = library.searchBookById(id);
                if (index != -1) {
                    library.deleteBook(index);
                }
                else {
                    cout << "Book not found.\n";
                }
                pressEnterToContinue();
                break;
            }
            
            case 6: { // SORT BOOKS
                int sortChoice;
                cout << "\n--- Sort Books ---\n";
                cout << "1. Sort by ID\n";
                cout << "2. Sort by Title\n";
                cout << "3. Sort by Author\n";
                cout << "Enter choice: ";
                cin >> sortChoice;
                
                showLoading();
                if (sortChoice == 1) {
                    library.sortBooksById();
                }
                else if (sortChoice == 2) {
                    library.sortBooksByTitle();
                }
                else if (sortChoice == 3) {
                    library.sortBooksByAuthor();
                }
                else {
                    cout << "Invalid choice!\n";
                }
                pressEnterToContinue();
                break;
            }
            
            case 7: { // SHOW TOTAL BOOKS
                cout << "\n--- Library Statistics ---\n";
                cout << "Total Books in Library: " << library.getTotalBooks() << endl;
                pressEnterToContinue();
                break;
            }
            
            case 8: { // ADD USER
                int userId;
                string name;
                
                cout << "\n--- Add New User ---\n";
                cout << "Enter User ID: ";
                cin >> userId;
                
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, name);
                
                User user(userId, name);
                users.push_back(user);
                
                showLoading();
                cout << "User added successfully!\n";
                pressEnterToContinue();
                break;
            }
            
            case 9: { // DISPLAY USERS
                if (users.size() == 0) {
                    cout << "No users registered.\n";
                }
                else {
                    cout << "\n--- Registered Users ---\n";
                    cout << "Total Users: " << users.size() << "\n\n";
                    for (int i = 0; i < users.size(); i++) {
                        users[i].displayUser();
                        cout << endl;
                    }
                }
                pressEnterToContinue();
                break;
            }
            
            case 10: { // ISSUE BOOK
                int userId, bookId;
                
                cout << "\n--- Issue Book ---\n";
                cout << "Enter User ID: ";
                cin >> userId;
                cout << "Enter Book ID: ";
                cin >> bookId;
                
                int userIndex = -1;
                for (int i = 0; i < users.size(); i++) {
                    if (users[i].getUserId() == userId) {
                        userIndex = i;
                        break;
                    }
                }
                
                int bookIndex = library.searchBookById(bookId);
                
                if (userIndex != -1 && bookIndex != -1) {
                    Book book = library.getBook(bookIndex);
                    
                    if (!book.getStatus()) {
                        showLoading();
                        library.issueBook(bookIndex);
                        users[userIndex].borrowBook(book);
                        cout << "Book issued successfully to " << users[userIndex].getName() << "!\n";
                    }
                    else {
                        cout << "Book is already issued to someone else.\n";
                    }
                }
                else {
                    cout << "User or Book not found.\n";
                }
                pressEnterToContinue();
                break;
            }
            
            case 11: { // RETURN BOOK
                int userId, bookId;
                
                cout << "\n--- Return Book ---\n";
                cout << "Enter User ID: ";
                cin >> userId;
                cout << "Enter Book ID: ";
                cin >> bookId;
                
                int userIndex = -1;
                for (int i = 0; i < users.size(); i++) {
                    if (users[i].getUserId() == userId) {
                        userIndex = i;
                        break;
                    }
                }
                
                int bookIndex = library.searchBookById(bookId);
                
                if (userIndex != -1 && bookIndex != -1) {
                    showLoading();
                    library.returnBook(bookIndex);
                    users[userIndex].returnBook(bookId);
                    cout << "Book returned successfully!\n";
                }
                else {
                    cout << "User or Book not found.\n";
                }
                pressEnterToContinue();
                break;
            }
            
            case 12: { // SAVE TO FILE
                showLoading();
                library.saveToFile();
                pressEnterToContinue();
                break;
            }
            
            case 0: { // EXIT
                cout << "\nSaving data before exit";
                showLoading();
                library.saveToFile();
                cout << "\nThank you for using Library Management System!\n";
                break;
            }
            
            default: {
                cout << "Invalid choice! Please try again.\n";
                pressEnterToContinue();
                break;
            }
        }
        
    } while (choice != 0);

    return 0;
}