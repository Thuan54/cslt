#include <iostream>
#include <math.h>
#include "View.h"
#include "model.h"
#include "define.h"
using namespace std;

int inputChoice(int max) {
    int input;
    bool condition = true;
    do
    {
        cout << "Nhap lua chon: ";
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            hold();
            cout << "\033[A\033[K";
            condition = false;
        }
        else if (!(condition = input >= 0 && input <= max)) {

            cout << "Lua chon khong hop le. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
    } while (!condition);
    return input;
}

//Lấy giá trị nhập vào của 1 số
//min, max: giới hạn của số
//Trả về giá trị của số nhập vào
template<typename T> T inputNum(T min = -99999999, T max = 999999999) {
    T input = 0;
    bool condition = true;
    cout << endl;
    do
    {
        cin >> input;
        condition = !cin.fail();
        if (!condition) {
            cin.clear();
            cout << "So nhap khong hop le. Vui long nhap lai. Enter" << endl;
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
        else {
            condition = input >= min && input <= max;
            if (!condition) {
                cin.clear();
                cout << "So nhap khong dung. Vui long nhap lai. Enter" << endl;
                hold();
                cout << "\033[A\033[K";
                cout << "\033[A\033[K";
                cout << "\033[A\033[K";
            }
            else return input;
        }
    } while (!condition);
    return input;
};

//Lấy giá trị ngày nhập vào
//day, month, year: nơi chứa giá trị nhập vào
void inputDate(Date* date) {
    int day, month, year;
    bool condition = true;
    do
    {
        cout << "Nhap ngay: ";
        day = inputNum<int>(1, 31);
        cout << "Nhap thang: ";
        month = inputNum<int>(1, 12);
        cout << "Nhap nam: ";
        year = inputNum<int>();
        switch (month)
        {
        case 1: case 3: case 5: case 7: case 8:case 10: case 12:
            condition = true;
            break;
        case 2:
            if (isLeapYear(year) && day < 30) condition = true;
            if (!isLeapYear(year) && day < 29) condition = true;
            break;
        default:
            if (day > 30) condition = false;
            break;
        }
        if (!condition) {
            cout << "Ngay nhap khong dung. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
    } while (!condition);
    date->day = day;
    date->month = month;
    date->year = year;
    cin.ignore(1000, '\n');
}

//Lấy dữ liệu chuỗi nhập vào
//s: nơi lưu giá trị nhập vào, length: độ dài chuỗi
void getStringInput(char* s, int length) {
    int i = 0;
    char c;
    while ((c = getchar()) != '\n')
    {
        if (i < length - 1) {
            s[i] = c;
            i++;
        }
    }
    s[i] = '\0';
}

void init(Member* member) {
    member->ID = 0;
    member->CCCD = create<char>(1, MEMBERCAPACITY, '\0');
    member->fullname = create<char>( MEMBERCAPACITY,21, '\0');
    member->gender = create<char>(MEMBERCAPACITY,7, '\0');
    member->email = create<char>(MEMBERCAPACITY, 21, '\0');
    member->address = create<char>(MEMBERCAPACITY, 15, '\0');
    member->DOB = new Date;
    member->MFG = new Date;
    member->EXP = new Date;
}
void init(Book* book) {
    book->ISBN = create<char>(MEMBERCAPACITY, 14, '\0');
    book->name = create<char>(MEMBERCAPACITY, 21, '\0');
    book->genre = create<char>(MEMBERCAPACITY, 21, '\0');
    book->author = create<char>(MEMBERCAPACITY, 21, '\0');
    book->publisher = create<char>(MEMBERCAPACITY, 21, '\0');
    book->price = 0;
    book->yearPB = 0;
    book->quantity = 0;
}
void init(BorrowCard* borrowCard) {
    borrowCard->memBorrowedIDIndex = 0;
    borrowCard->booksIndex = create<int>(MEMBERCAPACITY, 7, -1);
    borrowCard->dateBorrowed = create<Date*>(MEMBERCAPACITY,7, NULL);
    borrowCard->expectDateReturn= create<Date*>(MEMBERCAPACITY,7, NULL);
    borrowCard->actualDateReturn= create<Date*>(MEMBERCAPACITY,7, NULL);
}

void appStart(Members* members,Books* books,BorrowCardRecords* borrowCardRecords) {
    members->storeIndex = create<int>(1,MEMBERCAPACITY,-1);
    members->storeVacant = create<int>(1, MEMBERCAPACITY, -1);
    members->members = create<Member*>(1, MEMBERCAPACITY, NULL);
    
    books->storeIndex = create<int>(1, ISBNCAPACITY, -1);
    books->storeVacant = create<int>(1, ISBNCAPACITY, -1);
    books->books = create<Book*>(1, ISBNCAPACITY, NULL);

    borrowCardRecords->borrowCardRecords = create<BorrowCard*>(1, MEMBERCAPACITY, NULL);

    if (!load(members)) cout << "Khong the mo file chua thong tin cac doc gia de doc" << endl;
    if (!load(books)) cout << "Khong the mo file chua thong tin cac sach de doc" << endl;
    if (!load(borrowCardRecords)) cout << "Khong the mo file chua thong tin cac the muon sach de doc" << endl;
}
void appEnd(Members* members, Books* books, BorrowCardRecords* borrowCardRecords) {
    if (!save(members)) cout << "Khong the mo file chua thong tin cac doc gia de ghi" << endl;
    if (!save(books)) cout << "Khong the mo file chua thong tin cac sach de ghi" << endl;
    if(!save(borrowCardRecords)) cout << "Khong the mo file chua thong tin the muon de ghi" << endl;
    
    delete[] members->storeIndex;
    delete[] members->storeVacant;
    for (int i = 0; i < MEMBERCAPACITY; i++)
    {
        if (members->members[i] != NULL) {
            delete[] members->members[i]->CCCD;
            delete[] members->members[i]->fullname;
            delete[] members->members[i]->email;
            delete[] members->members[i]->address;
            delete[] members->members[i]->gender;
            delete members->members[i]->DOB;
            delete members->members[i]->MFG;
            delete members->members[i]->EXP;
            delete members->members[i];
        }
    }
    delete[] members->members;
    delete members;

    delete[] books->storeIndex;
    delete[] books->storeVacant;
    for (int i = 0; i < ISBNCAPACITY; i++)
    {
        if (books->books[i] != NULL) {
            delete[] books->books[i]->ISBN;
            delete[] books->books[i]->name;
            delete[] books->books[i]->publisher;
            delete[] books->books[i]->genre;
            delete[] books->books[i]->author;
            delete books->books[i];
        }
    }
    delete[] books->books;
    delete books;

    for (int i = 0; i < MEMBERCAPACITY; i++)
    {
        if (borrowCardRecords->borrowCardRecords[i] != NULL) {
            delete[] borrowCardRecords->borrowCardRecords[i]->booksIndex;
            for (int j = 0; j < 7; j++)
            {
                if(borrowCardRecords->borrowCardRecords[i]->dateBorrowed[j] != NULL){
                    delete borrowCardRecords->borrowCardRecords[i]->dateBorrowed[j];
                    delete borrowCardRecords->borrowCardRecords[i]->expectDateReturn[j];
                    delete borrowCardRecords->borrowCardRecords[i]->actualDateReturn[j];
                }
            }
            delete[] borrowCardRecords->borrowCardRecords[i]->dateBorrowed;
            delete[] borrowCardRecords->borrowCardRecords[i]->expectDateReturn;
            delete[] borrowCardRecords->borrowCardRecords[i]->actualDateReturn;
            delete borrowCardRecords->borrowCardRecords[i];
        }
    }
    delete borrowCardRecords->borrowCardRecords;
    delete borrowCardRecords;
}

//Member
void renderMems(Members* members){

}
void addMem() {
    int memID, memCCCD;
    char memFullName[20] = "\0";
    char memEmail[20] = "\0";
    char memAddress[20] = "\0";
    char memGender[7] = "\0";
    int* memDOB = new int[3];
    int* memMFG = new int[3];
    int* memEXP = new int[3];
    bool condition = false;
    if (memCurrent >= CAPACITY) {
        cout << "Doc gia day. Vui long nang cap co so du lieu!" << endl;
        hold();
        return;
    }
    do
    {
        cout << "Nhap ma doc gia (8 chu so): ";
        memID = inputNum<int>(9999999, 99999999);
        condition = isExist(storeMemIndex, memIDs, memID, memCurrent) == -1;
        if (condition) {
            do
            {
                cout << "Nhap CCCD doc gia (8 chu so): ";
                memCCCD = inputNum<int>(9999999, 99999999);
                condition = isExist(storeMemIndex, memCCCDs, memCCCD, memCurrent) == -1;
                if (!condition) {
                    cout << "CCCD doc gia da ton tai. Vui long nhap lai. Enter";
                    hold();
                    cout << "\033[A\033[K";
                    cout << "\033[A\033[K";
                }
            } while (!condition);
        }
        else {
            cout << "Ma doc gia da ton tai. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
    } while (!condition);
    int index = findIndexToInsert(storeMemIndex, memCurrent, memIDs, memID);
    insertAt(storeMemIndex, memCurrent, index + 1, storeMemVacant[CAPACITY - memCurrent - 1]);
    storeMemVacant[CAPACITY - memCurrent] = -1;
    int memIndex = storeMemIndex[index + 1];
    PATCH(memCCCDs, memCCCD, memIndex);
    PATCH(memIDs, memID, memIndex);
    while (getchar() != '\n');
    cout << "Nhap ten doc gia: ";
    getStringInput(memFullName, 20);
    PATCH(memFullNames, memFullName, memIndex, 20);

    cout << "Nhap gioi tinh: ";
    getStringInput(memGender, 7);
    PATCH(memGenders, memGender, memIndex, 7);

    cout << "Nhap email doc gia: ";
    getStringInput(memEmail, 20);
    PATCH(memEmails, memEmail, memIndex, 20);

    cout << "Nhap dia chi doc gia: ";
    getStringInput(memAddress, 20);
    PATCH(memAddresses, memAddress, memIndex, 20);

    cout << "Nhap ngay sinh doc gia" << endl;
    inputDate(memDOB[0], memDOB[1], memDOB[2]);
    memDOBs[memIndex] = memDOB;

    cout << "Nhap ngay thanh lap the cho doc gia" << endl;
    inputDate(memMFG[0], memMFG[1], memMFG[2]);
    memMFGs[memIndex] = memMFG;
    memEXP[0] = memMFG[0];
    memEXP[1] = memMFG[1];
    memEXP[2] = memMFG[2];
    if (memEXP[1] == 2 && memEXP[0] == 29) {
        if (isLeapYear(memEXP[2] + 4)) memEXP[2] += 4;
        else {
            memEXP[0] = 1;
            memEXP[1] = 3;
            memEXP[2] += 4;
        }
    }
    else memEXP[2] += 4;
    memEXPs[memIndex] = memEXP;
    cout << endl << "Da them doc gia!";
    hold();
}
void updateMem() {
    int memID, index;
    int element;
    do
    {
        cout << "Nhap ma doc gia can chinh sua (8 chu so): ";
        memID = inputNum<int>(9999999, 99999999);
        index = isExist(storeMemIndex, memIDs, memID, memCurrent);
        if (index == -1) {
            cout << "Ma doc gia khong ton tai. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
    } while (index == -1);
    switch (input)
    {
    case 1: {
        int index2;
        do {
            cout << "Nhap ma doc gia moi (8 chu so): ";
            memID = inputNum<int>(9999999, 99999999);
            index2 = isExist(storeMemIndex, memIDs, memID, memCurrent);
            if (index2 != -1) {
                cout << "Ma doc gia da ton tai. Vui long nhap lai. Enter";
                hold();
                cout << "\033[A\033[K";
                cout << "\033[A\033[K";
            }
            else {
                index2 = findIndexToInsert(storeMemIndex, memCurrent, memIDs, memID);
                PATCH(memIDs, memID, storeMemIndex[index]);
                insertAt(storeMemIndex, memCurrent, index2 + 1, storeMemIndex[index]);
                deleteAt(storeMemIndex, memCurrent, index);
                cout << "Da cap nhat!";
                hold();
                break;
            }
        } while (index2 != -1);
        break;
    }
    case 3: {
        cout << "Nhap CCCD moi (8 chu so): ";
        element = inputNum<int>(9999999, 99999999);
        PATCH(data, element, storeMemIndex[index]);
        cout << "Da cap nhat";
        hold();
        break;
    }
    }

}
void updateMem() {
    int memID, index;
    do
    {
        cout << "Nhap ma doc gia can chinh sua (8 chu so): ";
        memID = inputNum<int>(9999999, 99999999);
        index = isExist(storeMemIndex, memIDs, memID, memCurrent);
        if (index == -1) {
            cout << "Ma doc gia khong ton tai. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
    } while (index == -1);
    cin.ignore();
    switch (input)
    {
    case 2: {
        char memFullName[20];
        cout << "Nhap ten moi (toi da 20 ki tu): ";
        getStringInput(memFullName, 20);
        PATCH(data, memFullName, storeMemIndex[index], 20);
        cout << "Da cap nhat!";
        hold();
        break;
    }
    case 5: {
        char memGender[7];
        cout << "Nhap gioi tinh khac: ";
        getStringInput(memGender, 7);
        PATCH(data, memGender, storeMemIndex[index], 7);
        cout << "Da cap nhat!";
        hold();
        break;
    }
    case 6: {
        char memEmail[20];
        cout << "Nhap email moi (toi da 20 ki tu): ";
        getStringInput(memEmail, 20);
        PATCH(data, memEmail, storeMemIndex[index], 20);
        cout << "Da cap nhat!";
        hold();
        break;
    }
    case 7: {
        char memAddress[20];
        cout << "Nhap dia chi moi (toi da 20 ki tu): ";
        getStringInput(memAddress, 20);
        PATCH(data, memAddress, storeMemIndex[index], 20);
        cout << "Da cap nhat!";
        hold();
        break;
    }
    }
}
void updateMem() {
    int memID, index;
    do
    {
        cout << "Nhap ma doc gia can chinh sua: ";
        memID = inputNum<int>(9999999, 99999999);
        index = isExist(storeMemIndex, memIDs, memID, memCurrent);
        if (index == -1) {
            cout << "Ma doc gia khong ton tai. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
    } while (index == -1);
    int memIndex = storeMemIndex[index];
    cout << "Nhap ngay thang nam moi" << endl;
    inputDate(data[memIndex][0], data[memIndex][1], data[memIndex][2]);
    cout << "Thanh cong!";
    hold();
}
void deleteMem() {
    int memID, index;
    if (memCurrent == 0) {
        cout << "Khong co doc gia de xoa!" << endl;
        hold();
        return;
    }
    do
    {
        cout << "Nhap ma doc gia can xoa (8 chu so): ";
        memID = inputNum<int>(9999999, 99999999);
        index = isExist(storeMemIndex, memIDs, memID, memCurrent);
        if (index == -1) {
            cout << "Ma doc gia khong ton tai. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
    } while (index == -1);
    int memIndex = storeMemIndex[index];
    storeMemVacant[CAPACITY - memCurrent] = memIndex;
    delete[] memDOBs[memIndex];
    delete[] memMFGs[memIndex];
    delete[] memEXPs[memIndex];
    deleteAt(storeMemIndex, memCurrent, index);
    cout << "Thanh cong!";
    hold();
}
void findMemByCCCD() {
    cout << "Nhap CCCD muon tim (8 chu so): ";
    int memCCCD = inputNum<int>(9999999, 99999999);
    int* indexes = FIND(storeMemIndex, memCCCDs, memCCCD, memCurrent);
    renderMemData(indexes, memIDs, memFullnames, memCCCDs, memDOBs, memGenders, memEmails, memAddresses, memMFGs, memEXPs);
    delete[] indexes;
    hold();
}
void findMemByFullName() {
    char memFullName[20];
    while (getchar() != '\n');
    cout << "Nhap ho ten muon tim: ";
    getStringInput(memFullName, 20);
    cout << "Do chinh xac" << endl;
    cout << "1. Chinh xac tuyet doi" << endl;
    cout << "0. Chinh xac den ki tu cuoi" << endl;
    int accuracy = inputChoice(1);
    int* indexes = NULL;
    switch (accuracy)
    {
    case 1:
        indexes = FIND(storeMemIndex, memFullnames, memFullName, memCurrent, 20, 1);
        break;
    case 0:
        indexes = FIND(storeMemIndex, memFullnames, memFullName, memCurrent, 20, 0);
        break;
    }
    renderMemData(indexes, memIDs, memFullnames, memCCCDs, memDOBs, memGenders, memEmails, memAddresses, memMFGs, memEXPs);
    delete[] indexes;
    hold();
}

//Book
void getAllBook() {

}
void addBook() {
    int ISBN;
    char bookName[20] = "\0";
    char bookAuthor[20] = "\0";
    char bookPublisher[20] = "\0";
    char bookGenre[20] = "\0";
    int bookYearPB;
    int bookQuantity;
    float bookPrice;
    bool condition = false;
    if (bookCurrent >= CAPACITY) {
        cout << "Sach day. Vui long nang cap co so du lieu!";
        hold();
        return;
    }
    do
    {
        cout << "Nhap ma sach (8 chu so): ";
        ISBN = inputNum<int>(9999999, 99999999);
        condition = isExist(storeBookIndex, ISBNs, ISBN, bookCurrent) == -1;
        if (!condition) {
            cout << "Ma sach da ton tai. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
    } while (!condition);
    int index = findIndexToInsert(storeBookIndex, bookCurrent, ISBNs, ISBN);
    insertAt(storeBookIndex, bookCurrent, index + 1, storeBookVacant[CAPACITY - bookCurrent - 1]);
    storeBookVacant[CAPACITY - bookCurrent] = -1;
    PATCH(ISBNs, ISBN, storeBookIndex[index + 1]);
    cin.ignore(1000, '\n');
    cout << "Nhap ten sach: ";
    getStringInput(bookName, 20);
    PATCH(bookNames, bookName, storeBookIndex[index + 1], 20);

    cout << "Nhap ten tac gia: ";
    getStringInput(bookAuthor, 20);
    PATCH(bookAuthors, bookAuthor, storeBookIndex[index + 1], 20);

    cout << "Nhap ten nha xuat ban: ";
    getStringInput(bookPublisher, 20);
    PATCH(bookPublishers, bookPublisher, storeBookIndex[index + 1], 20);

    cout << "Nhap ten the loai sach: ";
    getStringInput(bookGenre, 20);
    PATCH(bookGenres, bookGenre, storeBookIndex[index + 1], 20);

    cout << "Nhap nam xuat ban: ";
    bookYearPB = inputNum<int>(999, 9999);
    PATCH(bookYearPBs, bookYearPB, storeBookIndex[index + 1]);

    cout << "Nhap gia sach: ";
    bookPrice = inputNum<float>(0);
    PATCH(bookPrices, bookPrice, storeBookIndex[index + 1]);

    cout << "Nhap so luong sach: ";
    bookQuantity = inputNum<int>(0);
    PATCH(bookQuantities, bookQuantity, storeBookIndex[index + 1]);
    cout << "Da them sach!";
    hold();
}
void updateBook() {
    int ISBN, index;
    int element;
    do
    {
        cout << "Nhap ma sach can chinh sua (8 chu so): ";
        ISBN = inputNum<int>(9999999, 99999999);
        index = isExist(storeBookIndex, ISBNs, ISBN, bookCurrent);
        if (index == -1) {
            cout << "Ma sach khong ton tai. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
    } while (index == -1);
    switch (input)
    {
    case 1: {
        int index2;
        do {
            cout << "Nhap ma sach moi (8 chu so): ";
            ISBN = inputNum<int>(9999999, 99999999);
            index2 = isExist(storeBookIndex, ISBNs, ISBN, bookCurrent);
            if (index2 != -1) {
                cout << "Ma sach da ton tai. Vui long nhap lai. Enter";
                hold();
                cout << "\033[A\033[K";
                cout << "\033[A\033[K";
            }
            else {
                index2 = findIndexToInsert(storeBookIndex, bookCurrent, ISBNs, ISBN);
                PATCH(ISBNs, ISBN, storeBookIndex[index]);
                insertAt(storeBookIndex, bookCurrent, index2 + 1, storeBookIndex[index]);
                deleteAt(storeBookIndex, bookCurrent, index);
                cout << "Da cap nhat!";
                hold();
                break;
            }
        } while (index2 != -1);
        break;
    }
    case 5: {
        cout << "Nhap nam xuat ban moi: ";
        element = inputNum<int>(999, 9999);
        PATCH(data, element, storeBookIndex[index]);
        cout << "Da cap nhat";
        hold();
        break;
    }
    case 8: {
        cout << "Nhap so quyen sach moi: ";
        element = inputNum<int>(0);
        PATCH(data, element, storeBookIndex[index]);
        cout << "Da cap nhat";
        hold();
        break;
    }
    }
}
void updateBook() {
    int ISBN, index;
    float element;
    do
    {
        cout << "Nhap ma sach can chinh sua (8 chu so): ";
        ISBN = inputNum<int>(9999999, 99999999);
        index = isExist(storeBookIndex, ISBNs, ISBN, bookCurrent);
        if (index == -1) {
            cout << "Ma sach khong ton tai. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
    } while (index == -1);
    switch (input)
    {
    case 7: {
        cout << "Nhap gia sach moi: ";
        element = inputNum<float>(0);
        PATCH(data, element, storeBookIndex[index]);
        cout << "Da cap nhat";
        hold();
        break;
    }
    }
}
void updateBook() {
    int ISBN, index;
    do
    {
        cout << "Nhap ma sach can chinh sua (8 chu so) : ";
        ISBN = inputNum<int>(9999999, 99999999);
        index = isExist(storeBookIndex, ISBNs, ISBN, bookCurrent);
        if (index == -1) {
            cout << "Ma sach khong ton tai. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
    } while (index == -1);
    cin.ignore();
    switch (input)
    {
    case 2: {
        char bookName[20];
        cout << "Nhap ten sach moi (toi da 20 ki tu): ";
        getStringInput(bookName, 20);
        PATCH(data, bookName, storeBookIndex[index], 20);
        cout << "Da cap nhat!";
        hold();
        break;
    }
    case 3: {
        char bookAuthor[20];
        cout << "Nhap ten tac gia moi (toi da 20 ki tu): ";
        getStringInput(bookAuthor, 20);
        PATCH(data, bookAuthor, storeBookIndex[index], 20);
        cout << "Da cap nhat!";
        hold();
        break;
    }
    case 4: {
        char bookPublisher[20];
        cout << "Nhap ten nha xuat ban moi (toi da 20 ki tu): ";
        getStringInput(bookPublisher, 20);
        PATCH(data, bookPublisher, storeBookIndex[index], 20);
        cout << "Da cap nhat!";
        hold();
        break;
    }
    case 6: {
        char bookGenre[20];
        cout << "Nhap the loai moi (toi da 20 ki tu): ";
        getStringInput(bookGenre, 20);
        PATCH(data, bookGenre, storeBookIndex[index], 20);
        cout << "Da cap nhat!";
        break;
    }
    }
}
void deleteBook() {
    int ISBN, index;
    if (bookCurrent == 0) {
        cout << "Khong co sach de xoa!";
        hold();
        return;
    }
    do
    {
        cout << "Nhap ma sach can xoa (8 chu so): ";
        ISBN = inputNum<int>(9999999, 99999999);
        index = isExist(storeBookIndex, ISBNs, ISBN, bookCurrent);
        if (index == -1) {
            cout << "Ma sach khong ton tai. Vui long nhap lai. Enter";
            hold();
            cout << "\033[A\033[K";
            cout << "\033[A\033[K";
        }
    } while (index == -1);
    storeBookVacant[CAPACITY - bookCurrent] = storeBookIndex[index];
    deleteAt(storeBookIndex, bookCurrent, index);
    cout << "Thanh cong!";
    hold();
}
void findBookByISBN() {
    cout << "Nhap ISBN muon tim (8 chu so): ";
    int ISBN = inputNum<int>(9999999, 99999999);
    int* indexes = FIND(storeBookIndex, ISBNs, ISBN, bookCurrent);
    renderBookData(indexes, ISBNs, bookNames, bookAuthors, bookPublishers, bookYearPBs, bookGenres, bookPrices, bookQuantities);
    delete[] indexes;
    cout << "Thanh cong!";
    hold();
}
void findBookByName() {
    char bookName[20];
    while (getchar() != '\n');
    cout << "Nhap ten sach muon tim: ";
    getStringInput(bookName, 20);
    cout << "Do chinh xac" << endl;
    cout << "1. Chinh xac tuyet doi" << endl;
    cout << "0. Chinh xac den ki tu cuoi" << endl;
    int accuracy = inputChoice(1);
    int* indexes = NULL;
    switch (accuracy)
    {
    case 1:
        indexes = FIND(storeBookIndex, bookNames, bookName, bookCurrent, 20, 1);
        break;
    case 0:
        indexes = FIND(storeBookIndex, bookNames, bookName, bookCurrent, 20, 0);
        break;
    }
    renderBookData(indexes, ISBNs, bookNames, bookAuthors, bookPublishers, bookYearPBs, bookGenres, bookPrices, bookQuantities);
    delete[] indexes;
    cout << "Thanh cong!";
    hold();
}

//LibCard
void addBorrowCard() {
    int memID, memIndex, bookCount = 0, index = -1;
    bool condition = true;
    do {
        do
        {
            cout << "Nhap ma doc gia (8 chu so): ";
            memID = inputNum<int>(9999999, 99999999);
            index = isExist(storeMemIndex, memIDs, memID, memCurrent);
            if (index == -1) {
                cout << "Ma doc gia khong ton tai. Vui long nhap lai. Enter";
                hold();
            }
        } while (index == -1);
        memIndex = storeMemIndex[index];
        /*for (int i = 0; memBorrowed[i] != -1 && i < currentMemBorrowed; i++) {
            if (memBorrowed[i] == memIndex) {
                int *bookOverDue = isMemOverDue(memIndex, booksBorrowed, ISBNsBorrowed, expectDateReturn, actualDateReturn);
                if (bookOverDue[0] != -1) {
                    cout << "Doc gia can tra sach truoc khi muon sach moi";
                    hold();
                    condition = false;
                }
                else condition = true;
                delete[] bookOverDue;
                break;
            }
        }*/
        for (int i = 0; i < 7 && condition; i++) {
            if (ISBNsBorrowed[memIndex * 7 + i] != -1) bookCount++;
        }
    } while (!condition);
    if (bookCount == 7) {
        cout << "Doc gia da muon toi da 7 cuon" << endl;
        return;
    }
    cout << "Doc gia duoc phep muon " << 7 - bookCount << " quyen sach" << endl;
    cout << "Nhap so luong sach muon: ";
    int bookBorrow = inputNum<int>(0, 7 - bookCount);
    int ISBN, ISBNIndex;
    index = -1;
    if (bookCount == 0) {
        currentMemBorrowed++;
        memBorrowed[currentMemBorrowed - 1] = memIndex;
    }
    for (int i = 0; i < bookBorrow; i++)
    {
        do
        {
            cout << "Nhap ma sach (8 chu so): ";
            ISBN = inputNum<int>(9999999, 99999999);
            index = isExist(storeBookIndex, ISBNs, ISBN, bookCurrent);
            if (index == -1) {
                cout << "Ma sach khong ton tai. Vui long nhap lai. Enter";
                hold();
                cout << "\033[A\033[K";
                cout << "\033[A\033[K";
            }
            else {
                ISBNIndex = storeBookIndex[index];
                condition = bookQuantities[ISBNIndex] > 0;
                if (!condition) {
                    cout << "So luong sach da het. Vui long muon sach khac";
                    hold();
                }
            }
        } while (index == -1 || !condition);
        ISBNsBorrowed[memIndex * 7 + bookCount] = ISBNIndex * 100 + bookQuantities[ISBNIndex] % 20 - 1;
        bookQuantities[ISBNIndex]--;
        int bookIndex = ISBNsBorrowed[memIndex * 7 + bookCount] % 100;
        booksBorrowed[ISBNIndex * 20 + bookIndex] = 1;
        cout << "Nhap ngay muon" << endl;
        int day, month, year;
        inputDate(day, month, year);
        int* Date = new int[3];
        int* DateReturn = new int[3];
        Date[0] = day;
        Date[1] = month;
        Date[2] = year;
        DateReturn[0] = day;
        DateReturn[1] = month;
        DateReturn[2] = year;
        dateBorrowed[ISBNIndex * 20 + bookIndex] = Date;
        expectDateReturn[ISBNIndex * 20 + bookIndex] = DateReturn;
        increaseDate(expectDateReturn[ISBNIndex * 20 + bookIndex], 7);
        booksBorrowed[ISBNIndex * 20 + bookIndex] = 1;
        bookCount++;
    }
    cout << "Muon thanh cong!";
    hold();
}
void deleteBorrowCard() {
    int memID, memIndex, bookBorrowedCount = 0, index = -1;
    bool condition = false;
    float charge = 0;
    do {
        do
        {
            cout << "Nhap ma doc gia (8 chu so): ";
            memID = inputNum<int>(9999999, 99999999);
            index = isExist(storeMemIndex, memIDs, memID, memCurrent);
            if (index == -1) {
                cout << "Ma doc gia khong ton tai. Vui long nhap lai. Enter";
                hold();
            }
        } while (index == -1);
        memIndex = storeMemIndex[index];
        for (int i = 0; i < currentMemBorrowed; i++)
        {
            if (memBorrowed[i] == memIndex) condition = true;
        }
        if (!condition) {
            cout << "Doc gia chua muon sach nao!" << endl;
            cout << "Vui long nhap lai. Enter";
            hold();
        }
        else {
            for (int i = 0; ISBNsBorrowed[memIndex * 7 + i] != -1 && i < 7; i++)
            {
                bookBorrowedCount++;
            }
        }
    } while (!condition);
    cout << "Nhap ngay hom nay" << endl;
    int* dateReturn = new int[3];
    inputDate(dateReturn[0], dateReturn[1], dateReturn[2]);
    cout << "Doc gia da muon " << bookBorrowedCount << " sach" << endl;
    cout << "Nhap so luong sach tra: ";
    int bookReturn = inputNum<int>(1, bookBorrowedCount);
    int ISBN, ISBNIndex;
    index = -1;
    for (int i = 0; i < bookReturn; i++)
    {
        do
        {
            cout << "Nhap ma sach (8 chu so): ";
            ISBN = inputNum<int>(9999999, 99999999);
            index = isExist(storeBookIndex, ISBNs, ISBN, bookCurrent);
            if (index == -1) {
                cout << "Ma sach khong ton tai. Vui long nhap lai. Enter";
                hold();
                cout << "\033[A\033[K";
                cout << "\033[A\033[K";
            }
            else {
                ISBNIndex = storeBookIndex[index];
                for (int i = 0; ISBNsBorrowed[memIndex * 7 + i] != -1 && i < 7; i++)
                {
                    if (ISBNsBorrowed[memIndex * 7 + i] / 100 == ISBNIndex) {
                        condition = true;
                        int bookIndex = ISBNsBorrowed[memIndex * 7 + i] % 100;
                        actualDateReturn[ISBNIndex * 20 + bookIndex] = dateReturn;
                        int overDueDate = diffTwoDates(expectDateReturn[ISBNIndex * 20 + bookIndex], actualDateReturn[ISBNIndex * 20 + bookIndex]);
                        cout << "Mat sach" << endl;
                        cout << "1. Co" << endl;
                        cout << "0. Khong" << endl;
                        int choice = inputChoice(2);
                        if (choice == 1) {
                            charge += booksPrices[ISBNIndex] * 2;
                            ISBNsBorrowed[ISBNIndex * 20 + bookIndex] = -1;
                        }
                        else ISBNsBorrowed[ISBNIndex * 20 + bookIndex] = 0;
                        if (overDueDate > 0) {
                            charge += overDueDate * 2000;
                        }
                        cout << "Tien phat: " << charge << endl;
                        delete[] dateBorrowed[ISBNIndex * 20 + bookIndex];
                        delete[] expectDateReturn[ISBNIndex * 20 + bookIndex];
                        delete[] actualDateReturn[ISBNIndex * 20 + bookIndex];
                        ISBNsBorrowed[memIndex * 7 + i] = -1;
                        bookQuantities[ISBNIndex]++;
                        break;
                    }
                    else condition = false;
                }if (!condition) {
                    cout << "Doc gia chua muon sach nay!" << endl;
                    cout << "Vui long nhap lai. Enter";
                    hold();
                }
            }
        } while (index == -1 || !condition);
    }
    if (bookReturn == bookBorrowedCount) {
        memBorrowed[currentMemBorrowed - 1] = -1;
        currentMemBorrowed--;
    }
    int l = 0, r = 7;
    while (l < r)
    {
        int* index1 = &ISBNsBorrowed[memIndex * 7 + l];
        if (*index1 == -1) {
            r--;
            int* index2 = &ISBNsBorrowed[memIndex * 7 + r];
            swap(*index1, *index2);
        }
        else l++;
    }
    cout << "Tra sach thanh cong!";
    hold();
}

//Statistic
void statisticBookByGenre() {
    int* storeIndexAfterSort = create<int>(current + 1, 1, -1);
    for (int i = 1; i < current + 1; i++)
    {
        storeIndexAfterSort[i] = storeBookIndex[i - 1];
    }
    storeIndexAfterSort[0] = current + 1;
    sortData(storeIndexAfterSort, bookGenres, 1, current - 1, 20);
    renderBookData(storeIndexAfterSort, ISBNs, bookNames, bookAuthors, bookPublishers, bookYearPBs, bookGenres, bookPrices, bookQuantities);
    delete[] storeIndexAfterSort;
    hold();
}
void statisticNumberOfBook() {
    int total = 0;
    for (int i = 0; i < current; i++)
    {
        total += bookQuantities[storeBookIndex[i]];
    }
    cout << "Dang co " << total << " sach trong thu vien" << endl;
    hold();
}
void statisticMemByGender() {
    int* storeIndexAfterSort = create<int>(current + 1, 1, -1);
    for (int i = 1; i < current + 1; i++)
    {
        storeIndexAfterSort[i] = storeMemIndex[i - 1];
    }
    storeIndexAfterSort[0] = current + 1;
    sortData(storeIndexAfterSort, memGenders, 1, current - 1, 7);
    renderMemData(storeIndexAfterSort, memIDs, memFullnames, memCCCDs, memDOBs, memGenders, memEmails, memAddresses, memMFGs, memEXPs);
    delete[] storeIndexAfterSort;
    hold();
}
void statisticBookBorrowed() {
    int bookBorrowedCount = 0;
    for (int i = 0; i < current; i++)
    {
        int bookIndex = bookQuantities[storeBookIndex[i]];
        while (bookBorrowed[storeBookIndex[i] * 20 + bookIndex] > 0) {
            bookBorrowedCount++;
            bookIndex++;
        }
    }
    cout << "Dang co " << bookBorrowedCount << " duoc muon" << endl;
    hold();
}
void statisticMemInLibrary() {
    cout << "Dang co " << memCurrent << " doc gia trong he thong thu vien" << endl;
    hold();
}
void statisticMemOverDue() {
    int ToDay[3] = { 0 };
    int* memOverDue = create<int>(current + 1, 1, -1);
    int* ISBNsOverDue = create<int>(7, current + 1, -1);
    int countMemOverDue = 1;
    bool isOverDue = false;
    cout << "Nhap ngay hien tai" << endl;
    inputDate(ToDay[0], ToDay[1], ToDay[2]);
    for (int i = 0; i < current; i++)
    {
        int memIndex = memBorrowed[i];
        int countBookOverDue = 0;
        for (int j = 0; j < 7 && ISBNsBorrowed[memBorrowed[i] * 7 + j] != -1; j++)
        {
            int ISBNIndex = ISBNsBorrowed[memBorrowed[i] * 7 + j] / 100;
            int bookIndex = ISBNsBorrowed[memBorrowed[i] * 7 + j] % 100;
            int overDueDays = diffTwoDates(ToDay, dateBorrowed[ISBNIndex * 20 + bookIndex]);
            if (overDueDays > 0) {
                ISBNsOverDue[countMemOverDue * 7 + countBookOverDue] = ISBNsBorrowed[memBorrowed[i] * 7 + j];
                countBookOverDue++;
                isOverDue = true;
            }
        }
        if (isOverDue) {
            memOverDue[countMemOverDue] = memIndex;
            countMemOverDue++;
        }
    }
    memOverDue[0] = countMemOverDue - 1;
    renderMemOverDue(ISBNsOverDue, memOverDue, memIDs, ISBNs, dateBorrowed, expectDateReturn);
    delete[] memOverDue;
    delete[] ISBNsOverDue;
    hold();
}
