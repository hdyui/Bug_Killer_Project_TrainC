#ifndef UTILS_H
#define UTILS_H

#include <time.h>

/* =========================================================
 * utils.h - Khai báo các hàm tiện ích dùng chung
 * ========================================================= */

/* --- Validate --- */

/*
 * Kiểm tra SĐT hợp lệ (chỉ chứa chữ số, độ dài 9-11 ký tự).
 * Trả về 1 nếu hợp lệ, 0 nếu không.
 */
int isValidPhone(const char *phone);

/*
 * Kiểm tra biển số xe theo định dạng cơ bản (không rỗng, độ dài hợp lý).
 * Trả về 1 nếu hợp lệ, 0 nếu không.
 */
int isValidPlate(const char *plate);

/* --- Chuỗi --- */

/*
 * So sánh hai chuỗi không phân biệt hoa thường.
 * Trả về 0 nếu bằng nhau (tương tự strcmp).
 */
int strCmpIgnoreCase(const char *a, const char *b);

/*
 * Xoá khoảng trắng đầu và cuối chuỗi (in-place).
 */
void strTrim(char *str);

/*
 * Đọc một dòng từ stdin, loại bỏ '\n' cuối, giới hạn maxLen ký tự.
 */
void readLine(char *buffer, int maxLen);

/* --- Sinh ID --- */

/*
 * Sinh mã khách hàng dạng "CU000001" từ số thứ tự n.
 * Ghi kết quả vào buffer (cần ít nhất ID_LEN bytes).
 */
void generateCustomerId();

/*
 * Sinh mã phiếu sửa dạng "RO000001" từ số thứ tự n.
 */
void generateOrderId(int n, char *buffer);

/*
 * Sinh mã dịch vụ dạng "SV000001" từ số thứ tự n.
 */
void generateServiceId(int n, char *buffer);

/* --- Thời gian --- */

/*
 * Định dạng time_t thành chuỗi "DD/MM/YYYY HH:MM".
 * Ghi kết quả vào buffer (cần ít nhất 20 bytes).
 */
void formatDateTime(time_t t, char *buffer);

/*
 * Lấy chuỗi ngày hôm nay dạng "DD/MM/YYYY".
 * Ghi vào buffer (cần ít nhất 12 bytes).
 */
void getTodayString(char *buffer);

/* --- Hiển thị --- */

/*
 * In đường kẻ ngang cho menu/bảng.
 */
void printDivider(void);

/*
 * In tiêu đề có màu và căn giữa.
 */
void printHeader(const char *title);

/*
 * In thông báo thành công (màu xanh).
 */
void printSuccess(const char *msg);

/*
 * In thông báo lỗi (màu đỏ).
 */
void printError(const char *msg);

/*
 * In chuỗi trạng thái phiếu có màu ANSI tương ứng.
 * 0 = xám (Tiếp nhận), 1 = vàng (Đang sửa), 2 = xanh (Hoàn thành).
 */
void printStatus(int status);

/* --- Số --- */

/*
 * Định dạng số tiền thành chuỗi có dấu phân cách hàng nghìn.
 * VD: 1500000 -> "1,500,000 VNĐ"
 * Ghi vào buffer (cần ít nhất 30 bytes).
 */
void formatMoney(double amount, char *buffer);

#endif /* UTILS_H */
