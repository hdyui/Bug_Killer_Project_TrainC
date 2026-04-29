/* =========================================================
 * utils.c - Cài đặt các hàm tiện ích dùng chung
 * ========================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "utils.h"
#include "constants.h"
#include "models.h"
extern Customer customers[MAX_CUSTOMERS];
extern int customerCount;

/* =========================================================
 * VALIDATE
 * ========================================================= */

int isValidPhone(const char *phone) {
    /* TODO:
     * 1. Kiểm tra phone không NULL và không rỗng
     * 2. Duyệt từng ký tự, đảm bảo tất cả là chữ số (isdigit)
     * 3. Kiểm tra độ dài nằm trong khoảng [9, 11]
     * 4. Trả về 1 nếu thoả tất cả, 0 nếu không
     */
    return 0; /* placeholder */
}

int isValidPlate(const char *plate) {
    /* TODO:
     * 1. Kiểm tra plate không NULL và không rỗng
     * 2. Kiểm tra độ dài hợp lý (ví dụ 6-12 ký tự)
     * 3. Trả về 1 nếu hợp lệ, 0 nếu không
     */
    return 0; /* placeholder */
}

/* =========================================================
 * CHUỖI
 * ========================================================= */

int strCmpIgnoreCase(const char *a, const char *b) {
    /* TODO:
     * 1. Duyệt từng ký tự của a và b cùng lúc
     * 2. So sánh tolower(a[i]) với tolower(b[i])
     * 3. Nếu khác nhau, trả về hiệu của hai ký tự đó
     * 4. Nếu đến cuối cả hai, trả về 0
     */
    return 0; /* placeholder */
}

void strTrim(char *str) {
    /* TODO:
     * 1. Tìm vị trí ký tự đầu tiên không phải khoảng trắng (isspace)
     * 2. Dịch chuyển chuỗi về đầu nếu có khoảng trắng phía trước
     * 3. Tìm từ cuối về, cắt bỏ khoảng trắng cuối bằng cách đặt '\0'
     */
}

void readLine(char *buffer, int maxLen) {
    /* TODO:
     * 1. Dùng fgets(buffer, maxLen, stdin) để đọc cả dòng
     * 2. Tìm ký tự '\n' cuối và thay bằng '\0'
     * 3. Nếu fgets trả về NULL, gán buffer[0] = '\0'
     * 4. Gọi strTrim để xoá khoảng trắng thừa
     */
}

/* =========================================================
 * SINH ID
 * ========================================================= */

void generateCustomerId(int n, char *buffer) {
    sprintf(customers[customerCount].customerId, "CU%06d", customerCount+1);

}

void generateOrderId(int n, char *buffer) {
    /* TODO:
     * Dùng snprintf để định dạng: "RO%06d" với n
     * VD: n=1 -> "RO000001"
     */
}

void generateServiceId(int n, char *buffer) {
    /* TODO:
     * Dùng snprintf để định dạng: "SV%06d" với n
     * VD: n=1 -> "SV000001"
     */
}

/* =========================================================
 * THỜI GIAN
 * ========================================================= */

void formatDateTime(time_t t, char *buffer) {
    /* TODO:
     * 1. Dùng localtime(&t) để lấy struct tm *
     * 2. Dùng strftime để định dạng "%d/%m/%Y %H:%M" vào buffer
     */
}

void getTodayString(char *buffer) {
    /* TODO:
     * 1. Lấy time(NULL) để có time_t hiện tại
     * 2. Dùng localtime và strftime định dạng "%d/%m/%Y" vào buffer
     */
}

/* =========================================================
 * HIỂN THỊ
 * ========================================================= */

void printDivider(void) {
    /* TODO:
     * In một dòng gồm 60 ký tự '-' rồi xuống dòng
     */
}

void printHeader(const char *title) {
    /* TODO:
     * 1. Gọi printDivider()
     * 2. In COLOR_BOLD, COLOR_CYAN rồi in title căn giữa (tính padding)
     * 3. Reset màu, xuống dòng
     * 4. Gọi printDivider() lần nữa
     */
}

void printSuccess(const char *msg) {
    /* TODO:
     * In "[OK] " + msg với màu COLOR_GREEN, sau đó reset màu
     */
}

void printError(const char *msg) {
    /* TODO:
     * In "[LỖI] " + msg với màu COLOR_RED, sau đó reset màu
     */
}

void printStatus(int status) {
    /* TODO:
     * Dùng switch(status):
     *   STATUS_RECEIVED  -> in COLOR_GRAY  + "Tiếp nhận"
     *   STATUS_REPAIRING -> in COLOR_YELLOW + "Đang sửa"
     *   STATUS_DONE      -> in COLOR_GREEN  + "Hoàn thành"
     * Sau đó reset màu
     */
}

void formatMoney(double amount, char *buffer) {
    /* TODO:
     * 1. Chuyển amount thành long long để dễ xử lý
     * 2. Tách từng nhóm 3 chữ số từ phải sang, chèn dấu ','
     * 3. Gắn thêm " VNĐ" vào cuối
     * Gợi ý: xây chuỗi ngược rồi đảo lại
     */
}
