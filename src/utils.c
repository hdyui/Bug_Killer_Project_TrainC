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
    if ( phone != NULL && strlen(phone) == 10 ){
     	for ( int i = 0;  i < strlen(phone); i++){
     		if ( !isdigit(phone[i])) return 0;
		 }
		 return 1;
	 }
    return 0; 
}

int isValidPlate(const char *plate) {
    /* TODO:
     * 1. Kiểm tra plate không NULL và không rỗng
     * 2. Kiểm tra độ dài hợp lý (ví dụ 6-12 ký tự)
     * 3. Trả về 1 nếu hợp lệ, 0 nếu không
     */
    if (plate == NULL) return 0;
    /* 65AA-123.45 => độ dài = 10 */
    if (strlen(plate) != 11) return 0;
    if (!isdigit(plate[0])) return 0;
    if (!isdigit(plate[1])) return 0;
    if (!isalpha(plate[2])) return 0;
    if (!isalpha(plate[3])) return 0;
    if (plate[4] != '-')    return 0;
    if (!isdigit(plate[5])) return 0;
    if (!isdigit(plate[6])) return 0;
    if (!isdigit(plate[7])) return 0;
    if (plate[8] != '.')    return 0;
    if (!isdigit(plate[9])) return 0;
    return 1;
}
int isValidName(const char *name) {
	if (name == NULL || *name == '\0')
        return 0;

    while (*name)
    {
        if (!isalpha(*name) && *name != ' ')
            return 0;
        name++;
    }
    return 1;
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
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') { 
        char ca = tolower((unsigned char)a[i]);
        char cb = tolower((unsigned char)b[i]);
        if (ca != cb) {
            return ca - cb;  // khác nhau → trả về độ lệch
        }
        i++;
    }
    return tolower((unsigned char)a[i]) - tolower((unsigned char)b[i]); // Nếu cả 2 chuỗi có độ dài bằng nhau thì lúc này nó sẽ tương đương return 0

}

void strTrim(char *str) {
    /* TODO:
     * 1. Tìm vị trí ký tự đầu tiên không phải khoảng trắng (isspace)
     * 2. Dịch chuyển chuỗi về đầu nếu có khoảng trắng phía trước
     * 3. Tìm từ cuối về, cắt bỏ khoảng trắng cuối bằng cách đặt '\0'
     */
    if (str == NULL) return;

    char *start = str;

    // 1. Bỏ khoảng trắng đầu
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }

    // 2. Dồn chuỗi về đầu (nếu có khoảng trắng đầu)
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
		/* 
		- memmove là copy từ chỗ A sang chỗ B; và dù A và B có ghi đè lên nhau cũng không làm hỏng dữ liệu
        - memmove sẽ sao chép toàn bộ nội dung chuỗi mà start trỏ tới (bao gồm cả ký tự '\0') vào vùng nhớ bắt đầu tại str 
		(nếu không có + 1 thì sẽ không thể lấy ký tự '\0' điều này gây ra việc in rác khi mà chuỗi ko có ký tự kết thúc chuỗi) 
        - Dùng memmove là vì str và start có thể bị ghi chồng lên vùng nhớ của nhau và memmove đảm bảo copy đúng dữ liệu dù bị chồng lấp*/
    }

    // 3. Xoá khoảng trắng cuối
    char *end = str + strlen(str) - 1;

    while (end >= str && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }
}

void readLine(char *buffer, int maxLen) {
    /* TODO:
     * 1. Dùng fgets(buffer, maxLen, stdin) để đọc cả dòng
     * 2. Tìm ký tự '\n' cuối và thay bằng '\0'
     * 3. Nếu fgets trả về NULL, gán buffer[0] = '\0'
     * 4. Gọi strTrim để xoá khoảng trắng thừa
     */
    if (fgets(buffer, maxLen, stdin) == NULL) {
        buffer[0] = '\0'; // nếu lỗi → chuỗi rỗng
        return;
    }

    // 2. Tìm ký tự '\n' và thay bằng '\0'
    buffer[strcspn(buffer, "\n")] = '\0';

    // 3. Xoá khoảng trắng đầu/cuối
    strTrim(buffer);
}

/* =========================================================
 * SINH ID
 * ========================================================= */

void generateCustomerId() {
    sprintf(customers[customerCount].customerId, "CU%06d", customerCount+1);

}

void generateOrderId() {
    sprintf(orders[orderCount].orderId,"RO%06d", orderCount + 1);
}

void generateServiceId() {
    sprintf(services[serviceCount].serviceId, "SV%06d", serviceCount + 1);
}


/* =========================================================
 * THỜI GIAN
 * ========================================================= */

void formatDateTime(time_t t, char *buffer) {
    /* TODO:
     * 1. Dùng localtime(&t) để lấy struct tm *
     * 2. Dùng strftime để định dạng "%d/%m/%Y %H:%M" vào buffer
     */
    struct tm *tm_info = localtime(&t);
    strftime(buffer, 20, "%d/%m/%Y %H:%M", tm_info);
}

void getTodayString(char *buffer) {
    /* TODO:
     * 1. Lấy time(NULL) để có time_t hiện tại
     * 2. Dùng localtime và strftime định dạng "%d/%m/%Y" vào buffer
     */
    time_t now = time(NULL);                 // lấy thời gian hiện tại
    struct tm *tm_info = localtime(&now);    // chuyển sang dạng ngày giờ dễ đọc
    strftime(buffer, 12, "%d/%m/%Y", tm_info); // format thành chuỗi
    
}
char * getStatusString(int status){
    char * message;
    switch(status){
        case STATUS_RECEIVED:
            message = "Tiep nhan";
            break;
        case STATUS_REPAIRING:
            message =  "Dang sua";
            break;
        case STATUS_DONE:
            message = "Hoan thanh";
            break;
        default:
            message = "Khong xac dinh";
    }
    return message;
}

/* =========================================================
 * HIỂN THỊ
 * ========================================================= */

void printDivider(void) {
    /* TODO:
     * In một dòng gồm 60 ký tự '-' rồi xuống dòng
     */
    for (int i = 0; i < 60; i++) {
        printf("-");
    }
    printf("\n");
}

void printHeader(const char *title) {
    /* TODO:
     * 1. Gọi printDivider()
     * 2. In COLOR_BOLD, COLOR_CYAN rồi in title căn giữa (tính padding)
     * 3. Reset màu, xuống dòng
     * 4. Gọi printDivider() lần nữa
     */
    printDivider();  // dòng kẻ trên

    printf(COLOR_BOLD COLOR_CYAN "  %s\n" COLOR_RESET, title);
    // in tiêu đề với màu + in đậm

    printDivider(); 
}

void printSuccess(const char *msg) {
    /* TODO:
     * In "[OK] " + msg với màu COLOR_GREEN, sau đó reset màu
     */
    printf(COLOR_GREEN "[OK] %s\n" COLOR_RESET, msg);
}

void printError(const char *msg) {
    /* TODO:
     * In "[LỖI] " + msg với màu COLOR_RED, sau đó reset màu
     */
    printf(COLOR_RED "[LOI] %s\n" COLOR_RESET, msg);
}

void printStatus(int status) {
    /* TODO:
     * Dùng switch(status):
     *   STATUS_RECEIVED  -> in COLOR_GRAY  + "Tiếp nhận"
     *   STATUS_REPAIRING -> in COLOR_YELLOW + "Đang sửa"
     *   STATUS_DONE      -> in COLOR_GREEN  + "Hoàn thành"
     * Sau đó reset màu
     */
    switch (status) {
        case STATUS_RECEIVED:
            printf(COLOR_GRAY "Tiep nhan" COLOR_RESET);
            break;
        case STATUS_REPAIRING:
            printf(COLOR_YELLOW "Dang sua" COLOR_RESET);
            break;
        case STATUS_DONE:
            printf(COLOR_GREEN "Hoan thanh" COLOR_RESET);
            break;
        default:
            printf(COLOR_RED "Khong xac dinh" COLOR_RESET);
    }
}

void formatMoney(double amount, char *buffer) {
    /* TODO:
     * 1. Chuyển amount thành long long để dễ xử lý
     * 2. Tách từng nhóm 3 chữ số từ phải sang, chèn dấu ','
     * 3. Gắn thêm " VNĐ" vào cuối
     * Gợi ý: xây chuỗi ngược rồi đảo lại
     */
    long long num = (long long) amount; // Tiền Việt Nam không có phần lẻ nên tạo 1 biến num và ép kiểu amount lên long long để chứa số nguyên dài hơn

    char temp[30]; // Chuỗi temp này để lưu số tiền ngược (cụ thể thì cứ xem ở dưới)
    int i = 0, count = 0;

    if (num == 0) {
        strcpy(buffer, "0 VND");
        return;
    }

    // build ngược
    while (num > 0) {
        if (count == 3) {
            temp[i++] = ',';
            count = 0;
        }
        temp[i++] = (num % 10) + '0';
       
        num /= 10;
        count++;
    }
    temp[i] = '\0';


    int len = strlen(temp); // Lấy độ dài của chuỗi ký tự số của tiền
    for (int j = 0; j < len; j++) {
        buffer[j] = temp[len - j - 1]; // Lấy ký tự cuối của temp và ghi vào đầu buffer
    }
    buffer[len] = '\0'; // Kết thúc chuỗi bằng '\0'
    

    strcat(buffer, " VND"); // Dùng strcat để nối cụm " VND" vào sau số tiền từ buffer
}

