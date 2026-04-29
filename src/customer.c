/* =========================================================
 * customer.c - Cài đặt quản lý khách hàng
 * ========================================================= */

#include <stdio.h>
#include <string.h>
#include "customer.h"
#include "fileio.h"
#include "utils.h"
#include "constants.h"
#include "models.h"

/* --- Định nghĩa bộ nhớ toàn cục --- */

extern Customer customers[MAX_CUSTOMERS];
extern int customerCount;


/* =========================================================
 * KHỞI TẠO
 * ========================================================= */

void initCustomers(void) {
    /* TODO:
     * Gán customerCount = 0
     * Dùng memset để xoá toàn bộ mảng customers về 0
     */
}

/* =========================================================
 * THÊM KHÁCH HÀNG
 * ========================================================= */

int addCustomer(void) {
    /* TODO:
     * 1. Kiểm tra customerCount < MAX_CUSTOMERS (báo lỗi nếu đầy)
     * 2. Tạo con trỏ c = &customers[customerCount]
     * 3. Nhập và validate từng trường:
     *    a. Nhập fullName (không được rỗng)
     *    b. Nhập phoneNumber, gọi isValidPhone(); nếu không hợp lệ thì báo lỗi và hỏi lại
     *    c. Gọi findCustomerByPhone() để kiểm tra trùng; nếu trùng báo lỗi và return 0
     *    d. Nhập carPlate, gọi isValidPlate()
     *    e. Nhập carType (không được rỗng)
     * 4. Sinh customerId bằng generateCustomerId(customerCount + 1, ...)
     * 5. Gán c->orderCount = 0
     * 6. Tăng customerCount
     * 7. Gọi saveCustomers() để lưu file
     * 8. In thông báo thành công, return 1
     */
    /* Biến tạm để nhập trước, sau khi hợp lệ mới gán vào mảng */
    char tempName[NAME_LEN];
    char tempPhone[PHONE_LEN];
    char tempPlate[PLATE_LEN];
    char tempType[CAR_TYPE_LEN];
    int  foundIdx;
 
    /* Kiểm tra hệ thống còn chỗ không */
    if (customerCount >= MAX_CUSTOMERS) {
        printError("He thong da day, khong the them khach hang moi.");
        return 0;
    }
    /* --- Nhập họ tên --- */
    /* Lặp cho đến khi người dùng nhập tên không rỗng */
    do {
        printf("  Ho va ten: ");
        scanf(" %99[^\n]", tempName);   
        while (getchar() != '\n');      
        if ( !isValidName(tempName) ) {
            printError("Ho ten khong hop le.");
        }
    } while ( !isValidName(tempName) );
 
    /* --- Nhập số điện thoại --- */
    while (1) {
        printf("  So dien thoai: ");
        scanf(" %10s", tempPhone);      
        while (getchar() != '\n');
        if (isValidPhone(tempPhone) == 0) {
            printError("SDT khong hop le (chi chua so, 10 ky tu).");
            continue;
        }
        foundIdx = findCustomerByPhone(tempPhone);
        if (foundIdx != -1) {
            printError("SDT nay da ton tai trong he thong.");
            return 0; 
        }
        break;
    }
    /* --- Nhập biển số xe --- */
    while (1) {
        printf("  Bien so xe (VD: 51F-123.45): ");
        scanf(" %14s", tempPlate);
        while (getchar() != '\n');
        if (isValidPlate(tempPlate) == 0) {
            printError("Bien so khong hop le.");
            continue;
        }
        break;
    }
    /* --- Nhập loại xe --- */
    do {
        printf("  Loai xe (VD: Xe may, O to, Xe dap dien): ");
        scanf(" %29[^\n]", tempType);
        while (getchar() != '\n');
        if (!isValidName(tempType)) {
            printError("Loai xe khong hop le.");
        }
    } while (!isValidName(tempType));
    /* --- Ghi dữ liệu vào ô mảng tại vị trí customerCount --- */
    strcpy(customers[customerCount].fullName,    tempName);
    strcpy(customers[customerCount].phoneNumber, tempPhone);
    strcpy(customers[customerCount].carPlate,    tempPlate);
    strcpy(customers[customerCount].carType,     tempType);
    customers[customerCount].orderCount = 0;
    generateCustomerId();
    customerCount++;
    saveCustomers();
    printSuccess("Da them khach hang thanh cong!");
    printf("  Ma KH duoc cap: %s\n", customers[customerCount - 1].customerId);
    return 1;/* placeholder */
}

/* =========================================================
 * SỬA KHÁCH HÀNG
 * ========================================================= */

int editCustomer(void) {
    /* TODO:
     * 1. Nhập SĐT cần sửa
     * 2. Gọi findCustomerByPhone() -> lấy index; nếu -1 thì báo không tìm thấy, return 0
     * 3. In thông tin hiện tại của khách (gọi printCustomer)
     * 4. Hiển thị menu chọn trường muốn sửa:
     *    [1] Sửa họ tên
     *    [2] Sửa biển số xe
     *    [3] Sửa loại xe
     *    [0] Huỷ
     * 5. Nhập giá trị mới cho trường được chọn (validate trước khi gán)
     * 6. Cập nhật dữ liệu trong mảng
     * 7. Gọi saveCustomers() để lưu file
     * 8. In thông báo thành công, return 1
     */
    char phone[PHONE_LEN];
    int  idx;
    int  choice;
 
    /* Bước 1: nhập SĐT cần sửa */
    do {
    	printf("  Nhap SDT khach hang can sua: ");
    	scanf(" %14s", phone);
    	if( !isValidPhone(phone) ){
    		printError("  SDT khong hop le, xin hay nhap lai!");
		}
	}
    while (!isValidPhone(phone));
 
    /* Bước 2: tìm khách theo SĐT */
    idx = findCustomerByPhone(phone);
    if (idx == -1) {
        printError("Khong tim thay khach hang voi SDT nay.");
        return 0;
    }
 
    /* Bước 3: in thông tin hiện tại để người dùng xem trước khi sửa */
    printCustomer(&customers[idx]);
 
    /* Bước 4: hiển thị menu chọn trường muốn sửa */
    printf("  [1] Sua ho ten\n");
    printf("  [2] Sua bien so xe\n");
    printf("  [3] Sua loai xe\n");
    printf("  [0] Huy\n");
    printf("  Lua chon: ");
    scanf(" %d", &choice);
    while (getchar() != '\n');
 
    /* Bước 5: nhập giá trị mới, validate rồi gán vào customers[idx] */
    if (choice == 1) {
        do {
            printf("  Ho ten moi: ");
            scanf(" %99[^\n]", customers[idx].fullName);
            while (getchar() != '\n');
            if (!isValidName(customers[idx].fullName)) {
                printError("Ho ten khong hop le.");
            }
        } while (!isValidName(customers[idx].fullName));
 
    } else if (choice == 2) {
 
        /* Sửa biển số*/
        char newPlate[PLATE_LEN];
        while (1) {
            printf("  Bien so xe moi: ");
            scanf(" %14s", newPlate);
            while (getchar() != '\n');
            if (isValidPlate(newPlate) == 0) {
                printError("Bien so khong hop le.");
                continue;
            }
            break;
        }
        strcpy(customers[idx].carPlate, newPlate);
 
    } else if (choice == 3) {
 
        /* Sửa loại xe - không được rỗng */
        do {
            printf("  Loai xe moi: ");
            scanf(" %29[^\n]", customers[idx].carType);
            while (getchar() != '\n');
            if (!isValidName(customers[idx].carType) ) {
                printError("Loai xe khong hop le.");
            }
        } while (!isValidName(customers[idx].carType));
 
    } else if (choice == 0) {
        puts("  Da huy thao tac.");
        return 0;
 
    } else {
        printError("Lua chon khong hop le.");
        return 0;
    }
 
    /* Bước 6: lưu file và thông báo thành công */
    saveCustomers();
    printSuccess("Da cap nhat thong tin khach hang.");
    return 1;
}

/* =========================================================
 * TÌM KIẾM
 * ========================================================= */

int findCustomerByPhone(const char *phone) {
    /* TODO:
     * Duyệt vòng for từ 0 đến customerCount - 1
     * Nếu strcmp(customers[i].phoneNumber, phone) == 0 thì return i
     * Nếu không tìm thấy, return -1
     */
    int index = -1;
    for (int i = 0; i < customerCount; i++){
        if (strcmp(customers[i].phoneNumber, phone) == 0){
            index = i;
            break;
        }
    }
    return index;
}

int findCustomerByPlate(const char *plate) {
    /* TODO:
     * Duyệt vòng for từ 0 đến customerCount - 1
     * Dùng strCmpIgnoreCase(customers[i].carPlate, plate) == 0 thì return i
     * Nếu không tìm thấy, return -1
     */
    int i;
    for (i = 0; i < customerCount; i++) {
        if (strCmpIgnoreCase(customers[i].carPlate, plate) == 0) {
            return i;
        }
    }
    return -1; 
}

void searchCustomerMenu(void) {
    /* TODO:
     * 1. Hiển thị lựa chọn: [1] Tìm theo SĐT  [2] Tìm theo biển số
     * 2. Nhận lựa chọn và nhập từ khoá tương ứng
     * 3. Gọi findCustomerByPhone hoặc findCustomerByPlate
     * 4. Nếu tìm thấy: gọi printCustomer(&customers[index])
     * 5. Nếu không: gọi printError("Không tìm thấy khách hàng.")
     */
    int choice;
    int idx;
 
    /* Hiển thị lựa chọn tìm kiếm */
    printf("  [1] Tim theo SDT\n");
    printf("  [2] Tim theo bien so xe\n");
    printf("  [0] Quay lai\n");
    printf("  Lua chon: ");
    scanf(" %d", &choice);
    while (getchar() != '\n');
 
    idx = -1;
 
    if (choice == 1) {
    	char phone[PHONE_LEN];
        do {
        	printf("  Nhap SDT: ");
        	scanf(" %11s", phone);
        	if (!isValidPhone(phone)) {
                printError("SDT khong hop le.");
            }
		}
        while(!isValidPhone(phone));
		idx = findCustomerByPhone(phone);
 
    } else if (choice == 2) {
    	char plate[PLATE_LEN];
        do {
			printf("  Nhap bien so xe: ");
        	scanf(" %11s", plate);
        	if (!isValidPlate(plate)) {
                printError("Bien so khong hop le.");
            }
    	}
        while(!isValidPlate(plate));
        idx = findCustomerByPlate(plate);
 
    } else {
        //printError("Lua chon khong hop le.");
        return;
    }
 
    /* In kết quả */
    if (idx == -1) {
        printError("Khong tim thay khach hang.");
    } else {
        printCustomer(&customers[idx]);
    }
}

/* =========================================================
 * HIỂN THỊ
 * ========================================================= */

void printCustomer(const Customer *c) {
    /* TODO:
     * In từng trường của Customer theo định dạng gọn, có nhãn:
     *   Mã KH      : CU000001
     *   Họ tên     : ...
     *   SĐT        : ...
     *   Biển số    : ...
     *   Loại xe    : ...
     *   Số phiếu   : ...
     */
    printDivider();
    printf("  Ma KH     : %s\n", c->customerId);
    printf("  Ho ten    : %s\n", c->fullName);
    printf("  SDT       : %s\n", c->phoneNumber);
    printf("  Bien so   : %s\n", c->carPlate);
    printf("  Loai xe   : %s\n", c->carType);
    printf("  So phieu  : %d\n", c->orderCount);
    printDivider();
}

void listAllCustomers(void) {
    /* TODO:
     * 1. Kiểm tra customerCount == 0 -> in "Chưa có khách hàng nào." rồi return
     * 2. In header bảng: STT | Mã KH | Họ tên | SĐT | Biển số | Loại xe | Số phiếu
     * 3. Duyệt vòng for, in từng dòng theo định dạng bảng (%-width)
     * 4. In tổng số ở cuối
     */
    if (customerCount == 0) {
        puts("  Chua co khach hang nao trong he thong.");
        return;
    }
 
    /* In header bảng */
    printDivider();
    printf("  %-4s %-10s %-25s %-12s %-12s %-15s %s\n",
           "STT", "Ma KH", "Ho ten", "SDT", "Bien so", "Loai xe", "Phieu");
    printDivider();
 
    /* Duyệt vòng for in từng dòng */
    for (int i = 0; i < customerCount; i++) {
        printf("  %-4d %-10s %-25s %-12s %-12s %-15s %d\n",
               i + 1,
               customers[i].customerId,
               customers[i].fullName,
               customers[i].phoneNumber,
               customers[i].carPlate,
               customers[i].carType,
               customers[i].orderCount);
    }
    printDivider();
    printf("  Tong so khach hang: %d\n", customerCount);
}
