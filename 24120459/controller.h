#pragma once

void appStart(Members*, Books*, BorrowCardRecords*);
void appEnd(Members*, Books*, BorrowCardRecords*);

//lấy lựa chọn người dùng nhập vào
//max: số lựa chọn tối da
//trả về lựa chọn người dùng nhập vào
int inputChoice(int max);

//Member

//
void getAllMem(Members*);

//Thêm độc giả
void addMem(Members*);

//Cập nhật dữ liệu số nguyên độc giả
void updateMem(Members*);

//Xóa độc giả
void deleteMem(Members*);

//Tìm độc giả bằng CCCD
void findMemByCCCD(Members*);

////Tìm độc giả bằng têm
void findMemByFullName(Members*);

//Book

//
void getAllBook(Books*);

//Thêm sách
void addBook(Books*);

//Cập nhật dữ liệu số nguyên cho sách
void updateBook(Books*);

//Xóa sách
void deleteBook(Books*);

//Tìm kiếm sách theo ISBN
void findBookByISBN(Books*);

//Tìm kiếm sách theo tên sách
void findBookByName(Books*);

//BorrowCard

//
void getBorrowCardRecords(Members*,Books*,BorrowCardRecords*);

//Mượn sách
void addBorrowCard(Members*, Books*, BorrowCardRecords*);

//Trả sách
void deleteBorrowCard(Members*, Books*, BorrowCardRecords*);

//Statistic

//Thống kê số lượng độc giả trong thư viện
void statisticMemInLibrary(Members*);

//Thống kê số lượng độc giả theo giới tính
void statisticMemByGender(Members*);

//Thống kê độc giả quá hạn trả sách
void statisticMemOverDue(Members*,Books*,BorrowCardRecords*);

//Thống kê số lượng sách đang trong thư viện
void statisticNumberOfBook(Books*);

//Thống kê số lượng sách theo thể loại
void statisticBookByGenre(Books*);

//Thống kê số sách được mượn
void statisticBookBorrowed(Books*,BorrowCardRecords*);