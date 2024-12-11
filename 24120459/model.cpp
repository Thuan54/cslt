#include <string.h>
#include <stdio.h>
#include "define.h"
#include "model.h"

int toInt(char* s) {
	int res = 0;
	while (*s != '\0')
	{
		res = res + 10 + *s - '0';
		s++;
	}
	return res;
}

bool load(Members* members) {
	char fileName[] = "member.txt";
	FILE* memFile;
	memFile= fopen(fileName, "r");
	if (memFile == NULL) return false;
	char line[256] = "\0";
	fscanf_s(memFile, "%*[\n ]");
	for (int i = 0; i < MEMBERCAPACITY && fscanf_s(memFile, "%s", line, sizeof(line)) != EOF; i++) {
		char* token = strtok(line, ",.-");
		int tokenCount = 0;
		members->current = i + 1;
		int index = members->storeVacant[MEMBERCAPACITY - members->current];
		members->storeVacant[MEMBERCAPACITY - members->current] = -1;
		members->storeIndex[i] = index;

		int* intAttribute[1] = { &members->members[index]->ID };
		char* stringAttribute[5] = { members->members[index]->CCCD,members->members[index]->fullname,members->members[index]->gender, members->members[index]->email ,members->members[index]->address };
		Date* dateAttribute[3] = { members->members[index]->DOB,members->members[index]->MFG, members->members[index]->EXP };

		while (token != NULL && tokenCount < 15) {
			int passToken = 0;
			if (tokenCount >= 0 && tokenCount < 1) {
				*intAttribute[tokenCount - passToken] = toInt(token);
			}
			else passToken += 1;
			if (tokenCount >= 1 && tokenCount < 6) {
				strcpy_s(stringAttribute[tokenCount - passToken], sizeof(stringAttribute[tokenCount - passToken]), token);
			}
			else passToken += 5;
			if (tokenCount >= 6 && tokenCount < 9) {
				dateAttribute[tokenCount - passToken] = toDate(token);
			}
			else passToken += 3;
			token = strtok(NULL, ",");
			tokenCount++;
		}
		fscanf_s(memFile, "%*[\n ]");
	}
	sortData(members->storeIndex, members->members, 0, members->current - 1);
	fclose(memFile);
	return true;
}
bool load(Books* books) {
	char fileName[] = "book.txt";
	FILE* bookFile = fopen(fileName, "r");
	if (bookFile == NULL) return false;
	char line[256] = "\0";

	fscanf_s(bookFile, "%*[\n ]");
	for (int i = 0; i < ISBNCAPACITY && fscanf_s(bookFile, "%s", line, sizeof(line)) != EOF; i++)
	{
		char* token = strtok(line, ",.-");
		int tokenCount = 0;
		books->current = i + 1;
		int index = books->storeVacant[ISBNCAPACITY - books->current];
		books->storeVacant[ISBNCAPACITY - books->current] = -1;
		books->storeIndex[i] = index;
		int* intAttribute[2] = { &books->books[index]->yearPB, &books->books[index]->quantity };
		float* floatAttribute[1] = { &books->books[index]->price };
		char* stringAttribute[5] = { books->books[index]->ISBN,books->books[index]->name,books->books[index]->author,books->books[index]->publisher,books->books[index]->genre };
		while (token != NULL && tokenCount < 15) {
			int passToken = 0;
			if (tokenCount >= 0 && tokenCount < 5) {
				strcpy_s(stringAttribute[tokenCount - passToken], sizeof(stringAttribute[tokenCount - passToken]), token);
			}
			else passToken += 5;
			if (tokenCount >= 5 && tokenCount < 6) {
				*floatAttribute[tokenCount - passToken] = toFloat(token);
			}
			else passToken += 1;
			if (tokenCount >= 6 && tokenCount < 8) {
				*intAttribute[tokenCount - passToken] = toInt(token);
			}
			else passToken += 2;
			token = strtok(NULL, ",");
			tokenCount++;
		}
		fscanf_s(bookFile, "%*[\n ]");
	}
	sortData(books->storeIndex, books->books, 0, books->current);
	fclose(bookFile);
	return true;
}
bool load(BorrowCardRecords* borrowCardRecords) {
	char fileName[] = "borrowCardRecords.txt";
	FILE* borrowCardFile = fopen(fileName, "r");
	char line[256] = "\0";

	fscanf_s(borrowCardFile, "%*[\n ]");
	for (int i = 0; i < MEMBERCAPACITY; i++)
	{
		borrowCardRecords->current = i + 1;
		fscanf_s(borrowCardFile, "%*[\n ]");
		fscanf_s(borrowCardFile, "%d",&borrowCardRecords->borrowCardRecords[i]->memBorrowedID);
		fscanf_s(borrowCardFile, "%*[\n ]");
		for (int j = 0; j < 7 ; j++)
		{
			char* stringAttribute[5] = { borrowCardRecords->borrowCardRecords[i]->booksISBN[j]};
			Date* dateAttribute[2] = { borrowCardRecords->borrowCardRecords[i]->dateBorrowed[j],borrowCardRecords->borrowCardRecords[i]->expectDateReturn[j] };
			while (token != NULL && tokenCount < 15) {
				int passToken = 0;
				if (tokenCount >= 0 && tokenCount < 5) {
					strcpy_s(stringAttribute[tokenCount - passToken], sizeof(stringAttribute[tokenCount - passToken]), token);
				}
				else passToken += 5;
				if (tokenCount >= 5 && tokenCount < 6) {
					*floatAttribute[tokenCount - passToken] = toFloat(token);
				}
				else passToken += 1;
				if (tokenCount >= 6 && tokenCount < 8) {
					*intAttribute[tokenCount - passToken] = toInt(token);
				}
				else passToken += 2;
				token = strtok(NULL, ",");
				tokenCount++;
			}
		}
		fscanf_s(borrowCardFile, "%*[\n ]");
	}
	sortData(books->storeISBNIndex, books->books, 0, books->bookCurrent);
	fclose(borrowCardFile);
}

bool save(Members* members) {
	char fileName[] = "member.txt";
	FILE* file;
	file = fopen(fileName, "w");
	if (file == NULL) return false;

	for (int i = 0; i < members->current; i++)
	{
		int index = members->storeIndex[i];
		fprintf_s(file, "%d,", members->members[index]->ID);
		fprintf_s(file, "%s,", members->members[index]->CCCD);
		fprintf_s(file, "%s,", members->members[index]->fullname);
		fprintf_s(file, "%s,", members->members[index]->gender);
		fprintf_s(file, "%s,", members->members[index]->email);
		fprintf_s(file, "%s,", members->members[index]->address);
		fprintf_s(file, "%d,", members->members[index]->DOB->day);
		fprintf_s(file, "%d,", members->members[index]->DOB->month);
		fprintf_s(file, "%d,", members->members[index]->DOB->year);
		fprintf_s(file, "%d,", members->members[index]->MFG->day);
		fprintf_s(file, "%d,", members->members[index]->MFG->month);
		fprintf_s(file, "%d,", members->members[index]->MFG->year);
		fprintf_s(file, "%d,", members->members[index]->EXP->day);
		fprintf_s(file, "%d,", members->members[index]->EXP->month);
		fprintf_s(file, "%d\n", members->members[index]->EXP->year);
	}
	fclose(file);
	return true;
}
bool save(Books* books) {
	char fileName[] = "book.txt";
	FILE* file;
	file = fopen(fileName, "w");
	if (file == NULL) return false;

	for (int i = 0; i < books->current; i++)
	{
		int index = books->storeIndex[i];
		fprintf_s(file, "%s,", books->books[index]->ISBN);
		fprintf_s(file, "%s,", books->books[index]->name);
		fprintf_s(file, "%s,", books->books[index]->author);
		fprintf_s(file, "%s,", books->books[index]->publisher);
		fprintf_s(file, "%s,", books->books[index]->genre);
		fprintf_s(file, "%f,", books->books[index]->price);
		fprintf_s(file, "%d,", books->books[index]->yearPB);
		fprintf_s(file, "%d,", books->books[index]->quantity);
	}
	fclose(file);
	return true;
}
bool save(BorrowCardRecords* borrowCardRecords) {

}

void add(Member& member) {
	int low = 0;
	int high = memCurrent - 1;
	if (memCurrent == 0 || member.ID < members[low]->ID) {
		members[low] = &member;
	}
	else if (member.ID > members[high]->ID) {
		members[high] = &member;
	}
	else {
		if (IDs[storeIndex[0]] > ID) return -1;
		if (IDs[storeIndex[current - 1]] < ID) return current - 1;
		while (low <= high) {
			int mid = low + (high - low) / 2;
			if (mid == current - 1) return mid;
			if (IDs[storeIndex[mid]] < ID && IDs[storeIndex[mid + 1]]>ID) return mid;
			if (IDs[storeIndex[mid]] > ID && IDs[storeIndex[mid - 1]] < ID) return mid - 1;
			else if (IDs[storeIndex[mid]] < ID) low = mid + 1;
			else high = mid - 1;
		}
	}
}

remove(Member& member) {

}

find(Member& book) {



//Kiểm tra năm nhuận
//year: năm cần kiểm tra
//Trả về true: năm nhuận, false: năm không nhuận
bool isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}

//Ngày trong tháng
//month, year: dùng để tính toán ngày trong 1 tháng
//Trả về 31 nếu tháng 1,3,5,7,8,10,12
//Trả về 30 nếu tháng 4,6,9,11
//Trả về 29 nếu tháng 2 và năm nhuận, trả về 28 nếu tháng 2 và không phải năm nhuận
int daysInMonth(int month, int year) {
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		return isLeapYear(year) ? 29 : 28;
	}
	return 30;
}

//Lấy kí tự chữ thường
//c: kí tự muốn trích xuất chữ thường
//Trả về kí tự thường của c
char tolower(char c) {
	if (c >= 65 && c <= 90) c += 32;
	return c;
}

//Tổng cộng ngày từ 1900 của 1 ngày
//day, month, year: Tính toán cộng ngày từ 1-1-1900 đến ngày nhập vào
//Trả về tổng cộng ngày
int totalDays(int day, int month, int year) {
	int totalDays = 0;
	for (int i = 1900; i < year; i++) {
		totalDays += isLeapYear(i) ? 366 : 365;
	}
	for (int i = 1; i < month; i++) {
		totalDays += daysInMonth(i, year);
	}
	totalDays += day;
	return totalDays;
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

//Chia mảng làm 2 phần lớn hơn và bé hơn 1 số
//storeIndex: lấy chỉ mục của dữ liệu, high: vị trí xa nhất của mảng, low: vị trí thấp nhất của mảng
//data: mảng cần chia, length: chiều dài của dữ liệu trong mảng
int partition(int* storeIndex,const Member** data, int low, int high) {
	int pivot = data[storeIndex[high]]->ID;
	int i = low - 1;
	for (int j = low; j <= high; j++)
	{
		int index = storeIndex[j];
		if (data[index]->ID < pivot) {
			i++;
			swap(storeIndex[i], storeIndex[j]);
		}
	}
	return i;
}

int isExist(int* storeIndex, int* IDs, int ID, int current) {
	int low = 0;
	int high = current - 1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (IDs[storeIndex[mid]] == ID) return mid;
		else if (IDs[storeIndex[mid]] < ID) low = mid + 1;
		else high = mid - 1;
	}
	return -1;
}

void PATCH(int* data, int element, int i) {
	data[i] = element;
}
void PATCH(float* data, float element, int i) {
	data[i] = element;
}
void PATCH(char* data, char* element, int row, int length) {
	for (int i = 0; i < length; i++)
	{
		data[i + row * length] = element[i];
	}
}

int* FIND(int* storeIndex, int* data, int element, int current) {
	int* arr = create<int>(current + 1, 1, -1);
	int size = 1;
	for (int i = 0; i < current; i++)
	{
		if (data[storeIndex[i]] == element) {
			arr[size] = storeIndex[i];
			size++;
		}
	}
	arr[0] = size;
	return arr;
}
int* FIND(int* storeIndex, float* data, float element, int current) {
	int* arr = create<int>(current + 1, 1, -1);
	int size = 1;
	for (int i = 0; i < current; i++)
	{
		if (data[storeIndex[i]] == element) {
			arr[size] = storeIndex[i];
			size++;
		}
	}
	arr[0] = size;
	return arr;
}
int* FIND(int* storeIndex, char* data, char* element, int current, int length, int accuracy) {
	int* resultIndex = create<int>(current + 1, 1, -1);
	int size = 1;
	for (int i = 0; i < current && storeIndex[i] != -1; i++)
	{
		int isEqual = true;
		for (int j = 0; j < length; j++)
		{
			if (data[storeIndex[i] * length + j] == '\0' || element[j] == '\0') {
				if (accuracy && (data[storeIndex[i] * length + j] != '\0' || element[j] != '\0')) isEqual = false;
				break;
			}
			if (tolower(data[storeIndex[i] * length + j]) != tolower(element[j])) {
				isEqual = false;
				break;
			}
		}
		if (isEqual) {
			resultIndex[size] = storeIndex[i];
			size++;
		}
	}
	resultIndex[0] = size;
	return resultIndex;
}

void sortData(int* storeIndex, const Member **data,int low, int high) {
	if (low < high) {
		int pi = partition(storeIndex,data, low, high);
		sortData(storeIndex, data, low, pi - 1);
		sortData(storeIndex, data, pi + 1, high);
	}
}

int diffTwoDates(int* date1, int* date2) {
	return totalDays(date1[0], date1[1], date1[2]) - totalDays(date2[0], date2[1], date2[2]);
}
void increaseDate(int* Date, int k) {
	while (k != 0)
	{
		if (Date[0] + k > daysInMonth(Date[1], Date[2])) {
			k = k - (daysInMonth(Date[1], Date[2]) - Date[0]);
			if (Date[1] + 1 > 12) {
				Date[2]++;
				Date[1] = 1;
				Date[0] = 1;
			}
			else {
				Date[1]++;
				Date[0] = 1;
			}
		}
		else Date[0] += 1;
		k--;
	}
}

int* isMemOverDue(int index, int* booksBorrowed, int* ISBNsBorrowed, int** expectDateReturn, int** actualDateReturn) {
	int* booksBorrowedOverDue = create<int>(7, 1, -1);
	for (int i = 0; booksBorrowed[index * 7 + i] != -1 && i < 7; i++)
	{
		int ISBNIndex = booksBorrowed[index * 7 + i] / 100;
		int bookIndex = booksBorrowed[index * 7 + i] % 100;
		if (diffTwoDates(expectDateReturn[ISBNIndex * 20 + bookIndex], actualDateReturn[ISBNIndex * 20 + bookIndex]) > 7) {
			booksBorrowedOverDue[index * 7 + i] = ISBNIndex;
		}
	}
	return booksBorrowedOverDue;
}



int findIndexToInsert(int* storeIndex, int current, char* IDs, char ID) {
	int low = 0;
	int high = current - 1;
	if (current == 0) return -1;
	if (IDs[storeIndex[0]] > ID) return -1;
	if (IDs[storeIndex[current - 1]] < ID) return current - 1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (mid == current - 1) return mid;
		if (IDs[storeIndex[mid]] < ID && IDs[storeIndex[mid + 1]]>ID) return mid;
		if (IDs[storeIndex[mid]] > ID && IDs[storeIndex[mid - 1]] < ID) return mid - 1;
		else if (IDs[storeIndex[mid]] < ID) low = mid + 1;
		else high = mid - 1;
	}
	return -1;
}


void deleteAt(int* storeIndex, int& current, int i) {
	if (i == current - 1) {
		storeIndex[i] = -1;
		current--;
		return;
	}
	current--;
	for (; i < current; i++)
	{
		storeIndex[i] = storeIndex[i + 1];
	}
	storeIndex[current] = -1;
}
void insertAt(int* storeIndex, int& current, int i, int elemnet) {
	current++;
	for (int j = current - 1; j > i; j--)
	{
		storeIndex[j] = storeIndex[j - 1];
	}
	storeIndex[i] = elemnet;
}