#ifndef CUSTOMER_H
#define CUSTOMER_H

/* =========================================================
 * customer.h - Khai báo hàm quản lý khách hàng
 * ========================================================= */

#include "models.h"

/* --- Bộ nhớ toàn cục (khai báo extern, định nghĩa trong customer.c) --- */
extern Customer customers[MAX_CUSTOMERS];
extern int      customerCount;

/* --- Khởi tạo --- */

/*
 * Khởi tạo mảng customers về trạng thái trống.
 * Gọi một lần khi bắt đầu chương trình (trước khi load file).
 */
void initCustomers(void);

/* --- CRUD --- */

/*
 * Thêm khách hàng mới vào hệ thống.
 * Hỏi người dùng nhập: họ tên, SĐT, biển số, loại xe.
 * Validate SĐT trùng lặp trước khi thêm.
 * Lưu file ngay sau khi thêm thành công.
 * Trả về 1 nếu thành công, 0 nếu thất bại.
 */
int addCustomer(void);

/*
 * Sửa thông tin khách hàng (tên, biển số, loại xe).
 * KHÔNG cho phép sửa SĐT.
 * Tìm khách theo SĐT trước khi cho sửa.
 * Lưu file sau khi sửa thành công.
 * Trả về 1 nếu thành công, 0 nếu không tìm thấy.
 */
int editCustomer(void);

/* --- Tìm kiếm --- */

/*
 * Tìm vị trí (index) trong mảng của khách hàng có phoneNumber == phone.
 * Trả về index nếu tìm thấy, -1 nếu không.
 */
int findCustomerByPhone(const char *phone);

/*
 * Tìm vị trí (index) của khách hàng theo biển số xe (carPlate).
 * Tìm kiếm không phân biệt hoa thường.
 * Trả về index nếu tìm thấy, -1 nếu không.
 */
int findCustomerByPlate(const char *plate);

/*
 * Hỏi người dùng nhập SĐT hoặc biển số rồi hiển thị kết quả tìm kiếm.
 */
void searchCustomerMenu(void);

/* --- Hiển thị --- */

/*
 * In thông tin chi tiết của một khách hàng ra màn hình.
 */
void printCustomer(const Customer *c);

/*
 * In danh sách tất cả khách hàng dạng bảng (có STT, tên, SĐT, biển số).
 */
void listAllCustomers(void);

#endif /* CUSTOMER_H */
