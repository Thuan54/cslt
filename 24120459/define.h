#ifndef define
#pragma once
#define MEMBERCAPACITY 20
#define ISBNCAPACITY 20

#pragma pack(push,1)
typedef struct Date {
	int day;
	int month;
	int year;
};
typedef struct Member {
	int ID;
	char* fullname;
	char* CCCD;
	char* gender;
	char* email;
	char* address;
	Date* DOB;
	Date* MFG;
	Date* EXP;
};
typedef struct Book {
	char* ISBN;
	char* name;
	char* author;
	char* publisher;
	char* genre;
	int   yearPB;
	float price;
	int	  quantity;
};
typedef struct BorrowCard {
	int memBorrowedID;
	char** booksISBN;
	Date** dateBorrowed;
	Date** expectDateReturn;
	Date** actualDateReturn;
};
typedef struct Members {
	int current;
	int* storeIndex;
	int* storeVacant;
	Member** members;
};
typedef struct Books {
	int current;
	int* storeIndex;
	int* storeVacant;
	Book** books;
};
typedef struct BorrowCardRecords {
	int current;
	BorrowCard** borrowCardRecords;
};
#pragma pack(pop)
#endif