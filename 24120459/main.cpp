#include <iostream>
#include "Controller.h"
#include "view.h"
#include "define.h"
#include <iomanip>

using namespace std;
int main() {
    Members* members = new Members;
    Books* books = new Books;
    BorrowCardRecords* borrowCardRecords = new BorrowCardRecords;
    //Start
    appStart(members,books,borrowCardRecords);

    int choice, subChoice;
    do
    {
        renderMenu();
        choice = inputChoice(4);
        switch (choice)
        {
        case 1: {
            do
            {
                renderSubMenu(1);
                subChoice = inputChoice(6);
                void (*feat[6])(Members*) = {renderMems,addMem,updateMem,deleteMem,findMemByCCCD,findMemByFullName};
                feat[subChoice-1](members);
            } while (subChoice != 0);
            break;
        }
        case 2: {
            do
            {
                renderSubMenu(2);
                subChoice = inputChoice(6);
                void (*feat[6])(Books*) = { renderBooks, addBook,updateBook,deleteBook,findBookByISBN,findBookByName };
                feat[subChoice - 1](books);
            } while (subChoice != 0);
            break;
        }
        case 3: {
            do {
                renderSubMenu(3);
                subChoice = inputChoice(3);
                void (*feat[3])(Members*,Books*,BorrowCardRecords*) = { renderBorrowCards,addBorrowCard,deleteBorrowCard };
                feat[subChoice - 1](members, books, borrowCardRecords);
            } while (subChoice != 0);
            break;
        }
        case 4: {
            do {
                renderSubMenu(4);
                subChoice = inputChoice(6);
                int passFeat = 0;
                if (subChoice > 0 && subChoice < 3) {
                    void (*feat[2])(Members*) = { statisticMemInLibrary,statisticMemByGender };
                    feat[subChoice - 1](members);
                }
                else passFeat += 2;
                if (subChoice>=3 && subChoice < 5) {
                    void (*feat[2])(Books*) = { statisticNumberOfBook,statisticBookByGenre };
                    feat[subChoice - passFeat - 1](books);
                }
                else passFeat += 2;
                if (subChoice>=5 && subChoice < 6) {
                    void (*feat[1])(Members*, Books*, BorrowCardRecords*) = { statisticMemOverDue };
                    feat[subChoice - passFeat - 1](members, books, borrowCardRecords);
                }
                else passFeat += 1;
                if (subChoice >= 6 && subChoice < 7) {
                    void (*feat[1])(Books*, BorrowCardRecords*) = { statisticBookBorrowed };
                    feat[subChoice - passFeat - 1](books, borrowCardRecords);
                }
                else passFeat += 1;
            } while (subChoice != 0);
            break;
        }
        }

    } while (choice != 0);

    //End
    appEnd(members,books,borrowCardRecords);
    return 0;
}
