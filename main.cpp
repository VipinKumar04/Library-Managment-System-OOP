
#include <iostream>
#include <string>
using namespace std;

class book{
private:
    int bookid;
    string title;
    string author;
    int totalCopies;
    int availableCopies;

public:
    book(){
        bookid = 0;
        title = "";
        author = "";
        totalCopies = 0;
        availableCopies = 0;
    }

    book(int bookid,string title,string author,int copies){
        this->bookid = bookid;
        this->title = title;
        this->author = author;
        this->totalCopies = copies;
        this->availableCopies = copies;
    }

    int getBookId(){
        return bookid;
    }

    string getTitle(){
        return title;
    }

    int getAvailableCopies(){
        return availableCopies;
    }

    void issueBook(){
        if(availableCopies > 0){
            availableCopies--;
        }
    }

    void returnBook(){
        if(availableCopies < totalCopies){
            availableCopies++;
        }
    }

    void display(){
        cout << "\nBook ID: " << bookid;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nTotal Copies: " << totalCopies;
        cout << "\nAvailable Copies: " << availableCopies;
    }
};

class member{
private:
    int memberid;
    string name;
    string type;

    int borrowedBookIds[3];
    int issueDays[3];

    int borrowedCount;

public:
    member(){
        memberid = 0;
        name = "";
        type = "";
        borrowedCount = 0;

        for(int i = 0; i < 3; i++){
            borrowedBookIds[i] = 0;
            issueDays[i] = 0;
        }
    }

    member(int memberid,string name,string type){
        this->memberid = memberid;
        this->name = name;
        this->type = type;

        borrowedCount = 0;

        for(int i=0;i<3;i++){
            borrowedBookIds[i] = 0;
            issueDays[i] = 0;
        }
    }

    int getMemberId(){
        return memberid;
    }

    string getName(){
        return name;
    }

    string getType(){
        return type;
    }

    int getBorrowedCount(){
        return borrowedCount;
    }

    bool canBorrowBook(){
        return borrowedCount < 3;
    }

    bool hasBorrowedBook(int bookid){
        for(int i=0;i<borrowedCount;i++){
            if(borrowedBookIds[i] == bookid){
                return true;
            }
        }

        return false;
    }

    bool addBorrowedBook(int bookid,int issueDay){
        if(!canBorrowBook() || hasBorrowedBook(bookid)){
            return false;
        }

        borrowedBookIds[borrowedCount] = bookid;
        issueDays[borrowedCount] = issueDay;

        borrowedCount++;

        return true;
    }

    int getIssueDay(int bookid){
        for (int i=0;i<borrowedCount;i++){
            if(borrowedBookIds[i] == bookid){
                return issueDays[i];
            }
        }
        return -1;
    }

    bool removeBorrowedBook(int bookid){
        for (int i=0;i<borrowedCount;i++){
            if(borrowedBookIds[i] == bookid){

                for(int j=i;j<borrowedCount-1;j++){
                    borrowedBookIds[j] = borrowedBookIds[j + 1];
                    issueDays[j] = issueDays[j + 1];
                }

                borrowedCount--;

                borrowedBookIds[borrowedCount] = 0;
                issueDays[borrowedCount] = 0;

                return true;
            }
        }

        return false;
    }

    void display(){
        cout << "\nMember ID: " << memberid;
        cout << "\nName: " << name;
        cout << "\nType: " << type;
        cout << "\nBorrowed Books: " << borrowedCount;

        cout << "\nBook IDs: ";

        if (borrowedCount == 0){
            cout << "None";
        } else {
            for (int i = 0; i < borrowedCount; i++){
                cout << borrowedBookIds[i] << " ";
            }
        }
    }
};

class Library {
private:
    book books[100];
    member members[100];

    int bookCount;
    int memberCount;

    const int LOAN_DAYS = 14;
    const int FINE_PER_DAY = 5;

    int findBookIndex(int id) {
        for (int i = 0; i < bookCount; i++){
            if (books[i].getBookId() == id){
                return i;
            }
        }

        return -1;
    }

    int findMemberIndex(int id){
        for (int i = 0; i < memberCount; i++) {
            if (members[i].getMemberId() == id) {
                return i;
            }
        }
        return -1;
    }

    int calculateFineAmount(int issueDay,int currentDay){
        int overdueDays = currentDay - issueDay - LOAN_DAYS;

        if (overdueDays > 0) {
            return overdueDays * FINE_PER_DAY;
        }
        return 0;
    }

public:
    Library(){
        bookCount = 0;
        memberCount = 0;
    }

    void addBook(){
        int id, copies;
        string title, author;

        cout << "\nEnter Book ID: ";
        cin >> id;

        if(id <= 0 || findBookIndex(id) != -1){
            cout << "Invalid or duplicate Book ID!\n";
            return;
        }

        cout << "Enter Title : ";
        cin >> title;

        cout << "Enter Author : ";
        cin >> author;

        cout << "Enter Number of Copies: ";
        cin >> copies;

        books[bookCount] = book(id, title, author, copies);
        bookCount++;

        cout << "\nBook added successfully!\n";
    }


    void registerMember(){
        int id;
        string name, type;

        cout << "\nEnter Member ID: ";
        cin >> id;

        if (id <= 0 || findMemberIndex(id) != -1) {
            cout << "Invalid or duplicate Member ID!\n";
            return;
        }

        cout << "Enter Member Name : ";
        cin >> name;

        cout << "Enter Member Type : ";
        cin >> type;

        if (type != "Student" && type != "Faculty") {
            cout << "Invalid member type!\n";
            return;
        }

        if (memberCount >= 100) {
            cout << "Member storage is full!\n";
            return;
        }

        members[memberCount] = member(id, name, type);
        memberCount++;

        cout << "\nMember registered successfully!\n";
    }

    void displayBooks() {
        if (bookCount == 0) {
            cout << "\nNo books available!\n";
            return;
        }

        for (int i = 0; i < bookCount; i++) {
            books[i].display();
        }
    }


    void searchBook() {
        int choice;

        cout << "\n1. Search by Book ID";
        cout << "\n2. Search by Title";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;

            cout << "Enter Book ID: ";
            cin >> id;

            int index = findBookIndex(id);

            if (index != -1) {
                books[index].display();
            }else{
                cout << "Book not found!\n";
            }
        }

        else if (choice == 2) {
            string title;
            bool found = false;

            cout << "Enter Book Title : ";
            cin >> title;

            for (int i = 0; i < bookCount; i++) {
                if (books[i].getTitle() == title) {
                    books[i].display();
                    found = true;
                }
            }

            if(!found){
                cout << "Book not found!\n";
            }
        }

        else {
            cout << "Invalid choice!\n";
        }
    }


    void issueBook() {
        int memberid, bookid, issueDay;

        cout << "\nEnter Member ID: ";
        cin >> memberid;

        int mIndex = findMemberIndex(memberid);

        if (mIndex == -1) {
            cout << "Member not registered!\n";
            return;
        }

        cout << "Enter Book ID: ";
        cin >> bookid;

        int bIndex = findBookIndex(bookid);

        if (bIndex == -1) {
            cout << "Book not found!\n";
            return;
        }

        if (books[bIndex].getAvailableCopies() <= 0) {
            cout << "Book is not available!\n";
            return;
        }

        if (!members[mIndex].canBorrowBook()) {
            cout << "Borrowing limit reached!\n";
            return;
        }

        if (members[mIndex].hasBorrowedBook(bookid)) {
            cout << "Member already has this book!\n";
            return;
        }

        cout << "Enter Issue Day : ";
        cin >> issueDay;

        if (issueDay <= 0) {
            cout << "Invalid issue day!\n";
            return;
        }

        if (members[mIndex].addBorrowedBook(bookid,issueDay)){
            books[bIndex].issueBook();

            cout << "\nBook issued successfully!\n";
            cout << "Due Day: " << issueDay + LOAN_DAYS << "\n";
        }
    }

    void returnBook() {
        int memberid, bookid, returnDay;

        cout << "\nEnter Member ID: ";
        cin >> memberid;

        int mIndex = findMemberIndex(memberid);

        if (mIndex == -1) {
            cout << "Member not registered!\n";
            return;
        }

        cout << "Enter Book ID: ";
        cin >> bookid;

        int bIndex = findBookIndex(bookid);

        if (bIndex == -1) {
            cout << "Book not found!\n";
            return;
        }

        if (!members[mIndex].hasBorrowedBook(bookid)) {
            cout << "This book was not issued to this member!\n";
            return;
        }

        int issueDay = members[mIndex].getIssueDay(bookid);

        cout << "Enter Return Day (day number): ";
        cin >> returnDay;

        if (returnDay < issueDay) {
            cout << "Return day cannot be before issue day!\n";
            return;
        }

        int fine = calculateFineAmount(issueDay, returnDay);

        members[mIndex].removeBorrowedBook(bookid);
        books[bIndex].returnBook();

        cout << "\nBook returned successfully!\n";
        cout << "Fine Amount: Rs. " << fine << "\n";
    }


    // 7. VIEW MEMBER DETAILS

    void viewMemberDetails() {
        int id;

        cout << "\nEnter Member ID: ";
        cin >> id;

        int mIndex = findMemberIndex(id);

        if (mIndex == -1) {
            cout << "Member not found!\n";
            return;
        }

        members[mIndex].display();

        cout << "\nCurrently Borrowed Books:\n";

        if (members[mIndex].getBorrowedCount() == 0) {
            cout << "No books currently borrowed.\n";
            return;
        }

        for (int i = 0; i < bookCount; i++) {
            if (members[mIndex].hasBorrowedBook(books[i].getBookId())) {
                books[i].display();
            }
        }
    }


    // 8. CALCULATE FINE

    void calculateFine() {
        int memberid, bookid, currentDay;

        cout << "\nEnter Member ID: ";
        cin >> memberid;

        int mIndex = findMemberIndex(memberid);

        if (mIndex == -1) {
            cout << "Member not found!\n";
            return;
        }

        cout << "Enter Book ID: ";
        cin >> bookid;

        if (!members[mIndex].hasBorrowedBook(bookid)) {
            cout << "This book is not currently borrowed by this member!\n";
            return;
        }

        int issueDay = members[mIndex].getIssueDay(bookid);

        cout << "Enter Current Day (day number): ";
        cin >> currentDay;

        if (currentDay < issueDay) {
            cout << "Invalid current day!\n";
            return;
        }

        int fine = calculateFineAmount(issueDay, currentDay);

        cout << "\nIssue Day: " << issueDay;
        cout << "\nDue Day: " << issueDay + LOAN_DAYS;
        cout << "\nCurrent Day: " << currentDay;
        cout << "\nFine Amount: Rs. " << fine << "\n";
    }

};


int main() {
    Library library;

    int choice;

    do {
        cout << "\n\n====================================";
        cout << "\n      LIBRARY MANAGEMENT SYSTEM";
        cout << "\n====================================";

        cout << "\n1. Add a Book";
        cout << "\n2. Register a Member";
        cout << "\n3. Display All Books";
        cout << "\n4. Search for a Book";
        cout << "\n5. Issue a Book";
        cout << "\n6. Return a Book";
        cout << "\n7. View Member Details";
        cout << "\n8. Calculate Fine";
        cout << "\n9. Exit";

        cout << "\n====================================";
        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cout << "\nInvalid input! Please enter a number.\n";
            break;
        }

        switch (choice) {
            case 1:
                library.addBook();
                break;

            case 2:
                library.registerMember();
                break;

            case 3:
                library.displayBooks();
                break;

            case 4:
                library.searchBook();
                break;

            case 5:
                library.issueBook();
                break;

            case 6:
                library.returnBook();
                break;

            case 7:
                library.viewMemberDetails();
                break;

            case 8:
                library.calculateFine();
                break;

            case 9:
                cout << "\nThank you for using the Library Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 9);

    return 0;
}

