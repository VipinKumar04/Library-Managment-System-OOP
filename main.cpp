
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

