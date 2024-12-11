#ifndef model
#pragma once
#include "define.h"
template <typename T> T* create(int rows, int cols, T initVal) {
	int size = rows * cols;
	T* arr = new T[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = initVal;
	}
	return arr;
}
int toInt(char* s);
float toFloat(char* s);
Date* toDate(char* s);

bool load(Members* members);
bool load(Books* books);
bool load(BorrowCardRecords* borrowCardRecords);

bool save(Members* members);
bool save(Books* books);
bool save(BorrowCardRecords* borrowCardRecords);


//Hoán đổi 2 số
// a,b: 2 số cần hoán đổi
void swap(int& a, int& b);

//Cập nhật dữ liệu số nguyên
//data: nơi lưu dữ liệu, element: dữ liệu cần cập nhật, i: cập nhật tại (index)
void PATCH(int* data, int element, int i);

//Cập nhật dữ liệu số thực
//data: nơi lưu dữ liệu, element: dữ liệu cần cập nhật, i: cập nhật tại (index)
void PATCH(float* data, float element, int i);

//Cập nhật dữ liệu chuỗi
//data: nơi lưu dữ liệu, element: dữ liệu cần cập nhật, row: cập nhật tại (index), length: chiều dài dữ liệu chuỗi
void PATCH(char* data, char* element, int row, int length);

//Tìm kiếm dữ liệu số nguyên
//storeIndex: lấy chỉ mục(index) của dữ liệu, data: nơi lưu dữ liệu, element: dữ liệu, current: số lượng hiện tại
//Trả về mảng cấp phát động chứa các chỉ mục(index) của dữ liệu(element)
int* FIND(int* storeIndex, int* data, int element, int current);

//Tìm kiếm dữ liệu số thực
//storeIndex: lấy chỉ mục(index) của dữ liệu, data: nơi lưu dữ liệu, element: dữ liệu, current: số lượng hiện tại
//Trả về mảng cấp phát động chứa các chỉ mục(index) của dữ liệu(element)
int* FIND(int* storeIndex, float* data, float element, int current);

//Tìm kiếm dữ liệu chuỗi
//storeIndex: nơi lưu chỉ mục(index) của dữ liệu, data: nơi lưu dữ liệu, element: dữ liệu, current: số lượng hiện tại, length: độ dài dữ liệu chuỗi
// accuracy: độ chính xác để tìm. 1: chính xác tuyệt đối, 0: đúng cho tới kí tự cuối của element
//Trả về mảng cấp phát động chứa các chỉ mục(index) của dữ liệu(element)
int* FIND(int* storeIndex, char* data, char* element, int current, int length, int accuracy);

//Kiểm tra năm nhuận
//year: năm cần kiểm tra
//Trả về kiểu bool cho biết có phải năm nhuận không
bool isLeapYear(int year);

//Sắp xếp dữ liệu chuỗi
//storeIndex: nơi lưu chỉ mục(index) của dữ liệu, data: nơi lưu dữ liệu, low: chỉ mục đầu tiên của storeIndex, high: chỉ mục cuối cùng của storeIndex hay current -1, length: chiều dài chuỗi
void sortData(int* storeIndex, Member** data, int low, int high);
void sortData(int* storeIndex, Book** data, int low, int high);

//Khoảng cách giữa 2 ngày
//date1, date2: lấy dữ liệu để tính toán khoảng cách giữa 2 ngày
//Trả về số lượng ngày là khoảng cách giữa 2 ngày
int diffTwoDates(int* date1, int* date2);

//Tăng ngày lên k ngày
//Date: lấy dữ liệu để tăng lên k ngày, k: số lượng ngày muốn tăng
void increaseDate(int* Date, int k);

//Kiểm tra độc giả có mượn sách quá hạn
//memIndex: chỉ mục của độc giả
// ISBNsBorrowed: lấy chỉ mục của ISBN mượn
// bookBorrowed: Lấy chỉ mục của sách mượn
// expectDateReturn,actualDateReturn: lấy dữ liệu để tính toán
//Trả về mảng cấp phát động chứa cách chỉ mục của sách mà độc giả quá hạn
int* isMemOverDue(int memIndex, int* booksBorrowed, int* ISBNsBorrowed, int** expectDateReturn, int** actualDateReturn);

//Tìm kiếm nơi để chèn theo thứ tự tăng dần
//storeIndex: lấy chỉ mục của dữ liệu ,current: số lượng hiện tại để tính số lần lặp
//IDs: lấy mã độc giả hoặc mã sách, ID: mã độc giả hoặc mã sách cần thêm vào
//Trả về chỉ mục của storeIndex mà ID nhỏ hơn số phía sau và lớn hơn số phía trước
int findIndexToInsert(int* storeIndex, int current, int* IDs, int ID);

//Tìm kiếm ID trong nơi lưu trữ ID
//storeIndex: lấy chỉ mục của dữ liệu, current: số lượng hiện tại
//IDs: lấy dữ liệu so sánh với ID,ID: mã độc giả hoặc mã sách cần tìm
//Trả về chỉ mục của storeIndex của ID có trong IDs, nếu không có trả về -1;
int isExist(int* storeIndex, int* IDs, int ID, int current);

//Xóa phần chỉ mục tại i
//storeIndex: nơi lưu chỉ mục dữ liệu, current: số lượng hiện tại, i: nơi cần xóa
void deleteAt(int* storeIndex, int& current, int i);

//Thêm chỉ mục vào tại i
//storeIndex: nơi lưu các chỉ mục dữ liệu, current: số lượng hiện tại, i: chỉ mục nơi cần thêm, element: chỉ mục dữ liệu cần thêm
void insertAt(int* storeIndex, int& current, int i, int elemnet);
#endif