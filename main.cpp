
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


