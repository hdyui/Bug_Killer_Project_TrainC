/* =========================================================
 * suaxe_all.c - Quản Lý Tiệm Sửa Xe (bản gộp 1 file)
 * Nhóm: Bug Killer | Mentor: Nguyễn Đức Bảo Lâm
 * CLB F-Code - Trường ĐH FPT TP.HCM
 *
 * Build: gcc -Wall -std=c99 -o suaxe suaxe_all.c
 * Run  : ./suaxe
 * ========================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>

/* =========================================================
 * SECTION 1: HẰNG SỐ & ĐỊNH NGHĨA
 * ========================================================= */

/* --- Giới hạn hệ thống --- */
#define MAX_CUSTOMERS       10000
#define MAX_REPAIR_ORDERS   50000
#define MAX_SERVICES        200
#define MAX_ITEMS_PER_ORDER 10

/* --- Độ dài chuỗi --- */
#define ID_LEN           10
#define NAME_LEN         100
#define PHONE_LEN        15
#define PLATE_LEN        15
#define CAR_TYPE_LEN     30
#define SYMPTOM_LEN      200
#define SERVICE_NAME_LEN 100

/* --- Trạng thái phiếu sửa --- */
#define STATUS_RECEIVED  0   /* Tiếp nhận  */
#define STATUS_REPAIRING 1   /* Đang sửa   */
#define STATUS_DONE      2   /* Hoàn thành */

/* --- Đường dẫn file --- */
#define FILE_CUSTOMERS "data/customers.dat"
#define FILE_ORDERS    "data/orders.dat"
#define FILE_SERVICES  "data/services.dat"

/* --- Màu ANSI --- */
#define COLOR_RESET  "\033[0m"
#define COLOR_GREEN  "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_GRAY   "\033[90m"
#define COLOR_CYAN   "\033[36m"
#define COLOR_RED    "\033[31m"
#define COLOR_BOLD   "\033[1m"

/* =========================================================
 * SECTION 2: STRUCT (MODELS)
 * ========================================================= */

typedef struct {
    char   serviceId[ID_LEN];
    char   serviceName[SERVICE_NAME_LEN];
    int    quantity;
    double unitPrice;
    double subtotal;
} RepairItem;

typedef struct {
    char   serviceId[ID_LEN];
    char   name[SERVICE_NAME_LEN];
    double unitPrice;
    int    isActive;
} Service;

typedef struct {
    char customerId[ID_LEN];
    char fullName[NAME_LEN];
    char phoneNumber[PHONE_LEN];
    char carPlate[PLATE_LEN];
    char carType[CAR_TYPE_LEN];
    int  orderCount;
} Customer;

typedef struct {
    char       orderId[ID_LEN];
    char       customerPhone[PHONE_LEN];
    char       symptom[SYMPTOM_LEN];
    int        status;
    time_t     createdDate;
    time_t     updatedDate;
    RepairItem items[MAX_ITEMS_PER_ORDER];
    int        itemCount;
    double     totalAmount;
} RepairOrder;

/* =========================================================
 * SECTION 3: BIẾN TOÀN CỤC
 * ========================================================= */

Customer   customers[MAX_CUSTOMERS];
int        customerCount = 0;

RepairOrder orders[MAX_REPAIR_ORDERS];
int         orderCount = 0;

Service    services[MAX_SERVICES];
int        serviceCount = 0;

/* =========================================================
 * SECTION 4: KHAI BÁO TRƯỚC (FORWARD DECLARATIONS)
 * ========================================================= */

/* utils */
int    isValidPhone(const char *phone);
int    isValidPlate(const char *plate);
int    strCmpIgnoreCase(const char *a, const char *b);
void   strTrim(char *str);
void   readLine(char *buffer, int maxLen);
void   generateCustomerId(int n, char *buffer);
void   generateOrderId(int i);
void   generateServiceId(int n, char *buffer);
void   formatDateTime(time_t t, char *buffer);
void   getTodayString(char *buffer);
void   printDivider(void);
void   printHeader(const char *title);
void   printSuccess(const char *msg);
void   printError(const char *msg);
void   printStatus(int status);
void   formatMoney(double amount, char *buffer);

/* fileio */
void   ensureDataDir(void);
int    saveCustomers(void);
int    loadCustomers(void);
int    saveOrders(void);
int    loadOrders(void);
int    saveServices(void);
int    loadServices(void);
void   loadAllData(void);
void   saveAllData(void);

/* customer */
void   initCustomers(void);
int    addCustomer(void);
int    editCustomer(void);
int    findCustomerByPhone(const char *phone);
int    findCustomerByPlate(const char *plate);
void   searchCustomerMenu(void);
void   printCustomer(const Customer *c);
void   listAllCustomers(void);

/* service */
void   initServices(void);
int    addService(void);
int    editService(void);
int    findServiceById(const char *serviceId);
void   listAllServices(void);

/* repair */
void   initOrders(void);
int    createRepairOrder(void);
int    addItemToOrder(int idx);
int    updateOrderStatus(void);
int    findOrderById(const char *orderId);
int    findOrdersByPhone(const char *phone, int *result, int maxResult);
int    findOrdersByPlate(const char *plate, int *result, int maxResult);
void   printOrder(const RepairOrder *o);
void   listOrders(int statusFilter);
void   viewCustomerHistory(void);
void   searchOrderMenu(void);

/* report */
void   reportDailyRevenue(void);
void   reportTopServices(void);
int    exportInvoice(const char *orderId);
void   reportMenu(void);

/* menus */
static void menuCustomer(void);
static void menuRepair(void);
static void menuService(void);

/* =========================================================
 * SECTION 5: UTILS
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
     * 2. Kiểm tra độ dài hợp lý (6-12 ký tự)
     * 3. Trả về 1 nếu hợp lệ, 0 nếu không
     */
    return 0; /* placeholder */
}

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

void generateCustomerId(int n, char *buffer) {
    /* TODO: snprintf(buffer, ID_LEN, "CU%06d", n); */
}

void generateOrderId(int i) {
    sprintf(orders[i].orderId,"RO%06d", ++orderCount);
}

void generateServiceId(int n, char *buffer) {
    /* TODO: snprintf(buffer, ID_LEN, "SV%06d", n); */
    
}

void formatDateTime(time_t t, char *buffer) {
    /* TODO:
     * struct tm *tm_info = localtime(&t);
     * strftime(buffer, 20, "%d/%m/%Y %H:%M", tm_info);
     */
}

void getTodayString(char *buffer) {
    /* TODO:
     * time_t now = time(NULL);
     * struct tm *tm_info = localtime(&now);
     * strftime(buffer, 12, "%d/%m/%Y", tm_info);
     */
}

void printDivider(void) {
    /* TODO: In 60 ký tự '-' rồi xuống dòng */
}

void printHeader(const char *title) {
    /* TODO:
     * printDivider();
     * printf(COLOR_BOLD COLOR_CYAN "  %s\n" COLOR_RESET, title);
     * printDivider();
     */
}

void printSuccess(const char *msg) {
    /* TODO: printf(COLOR_GREEN "[OK] %s\n" COLOR_RESET, msg); */
}

void printError(const char *msg) {
    /* TODO: printf(COLOR_RED "[LOI] %s\n" COLOR_RESET, msg); */
}

void printStatus(int status) {
    /* TODO:
     * switch(status):
     *   0 -> COLOR_GRAY  "Tiep nhan"
     *   1 -> COLOR_YELLOW "Dang sua"
     *   2 -> COLOR_GREEN  "Hoan thanh"
     * Sau đó COLOR_RESET
     */
}

void formatMoney(double amount, char *buffer) {
    /* TODO:
     * Chuyển amount thành chuỗi có dấu phân cách hàng nghìn + " VND"
     * VD: 1500000 -> "1,500,000 VND"
     */
}

/* =========================================================
 * SECTION 6: FILE I/O
 * ========================================================= */

void ensureDataDir(void) {
    /* TODO:
     * mkdir("data", 0755) trên Linux/Mac
     * hoặc _mkdir("data") trên Windows
     * Bỏ qua lỗi nếu thư mục đã tồn tại
     */
}

int saveCustomers(void) {
    /* TODO:
     * FILE *fp = fopen(FILE_CUSTOMERS, "wb");
     * if (!fp) { printError("Khong the ghi file khach hang."); return 0; }
     * fwrite(&customerCount, sizeof(int), 1, fp);
     * fwrite(customers, sizeof(Customer), customerCount, fp);
     * fclose(fp);
     * return 1;
     */
    return 0; /* placeholder */
}

int loadCustomers(void) {
    /* TODO:
     * FILE *fp = fopen(FILE_CUSTOMERS, "rb");
     * if (!fp) return 0;  -- lần đầu chạy, bình thường
     * fread(&customerCount, sizeof(int), 1, fp);
     * fread(customers, sizeof(Customer), customerCount, fp);
     * fclose(fp);
     * return 1;
     */
    return 0; /* placeholder */
}

int saveOrders(void) {
    /* TODO: Tương tự saveCustomers cho orders[] / FILE_ORDERS */
    return 0; /* placeholder */
}

int loadOrders(void) {
    /* TODO: Tương tự loadCustomers cho orders[] / FILE_ORDERS */
    return 0; /* placeholder */
}

int saveServices(void) {
    /* TODO: Tương tự saveCustomers cho services[] / FILE_SERVICES */
    return 0; /* placeholder */
}

int loadServices(void) {
    /* TODO: Tương tự loadCustomers cho services[] / FILE_SERVICES */
    return 0; /* placeholder */
}

void loadAllData(void) {
    /* TODO: Gọi loadCustomers(), loadServices(), loadOrders() */
}

void saveAllData(void) {
    /* TODO: Gọi saveCustomers(), saveServices(), saveOrders() */
}

/* =========================================================
 * SECTION 7: CUSTOMER
 * ========================================================= */

void initCustomers(void) {
    /* TODO: customerCount = 0; memset(customers, 0, sizeof(customers)); */
}

int addCustomer(void) {
    /* TODO:
     * 1. Kiểm tra customerCount < MAX_CUSTOMERS
     * 2. Customer *c = &customers[customerCount];
     * 3. Nhập và validate fullName (không rỗng)
     * 4. Nhập phoneNumber, gọi isValidPhone(); kiểm tra trùng findCustomerByPhone()
     * 5. Nhập carPlate, gọi isValidPlate()
     * 6. Nhập carType (không rỗng)
     * 7. generateCustomerId(customerCount + 1, c->customerId)
     * 8. c->orderCount = 0; customerCount++;
     * 9. saveCustomers(); printSuccess("Da them khach hang.");
     * 10. return 1;
     */
    return 0; /* placeholder */
}

int editCustomer(void) {
    /* TODO:
     * 1. Nhập SĐT cần sửa
     * 2. int idx = findCustomerByPhone(phone); if (idx == -1) { lỗi; return 0; }
     * 3. printCustomer(&customers[idx]);
     * 4. Menu: [1] Sửa tên  [2] Sửa biển số  [3] Sửa loại xe  [0] Huỷ
     * 5. Nhập và validate giá trị mới, gán vào customers[idx]
     * 6. saveCustomers(); printSuccess(); return 1;
     */
    return 0; /* placeholder */
}

int findCustomerByPhone(const char *phone) {
    /* TODO:
     * for (int i = 0; i < customerCount; i++)
     *     if (strcmp(customers[i].phoneNumber, phone) == 0) return i;
     * return -1;
     */
    return -1; /* placeholder */
}

int findCustomerByPlate(const char *plate) {
    /* TODO:
     * for (int i = 0; i < customerCount; i++)
     *     if (strCmpIgnoreCase(customers[i].carPlate, plate) == 0) return i;
     * return -1;
     */
    return -1; /* placeholder */
}

void searchCustomerMenu(void) {
    /* TODO:
     * Hiển thị: [1] Tìm theo SĐT  [2] Tìm theo biển số
     * Nhập từ khoá, gọi hàm tìm tương ứng
     * In printCustomer nếu tìm thấy, printError nếu không
     */
}

void printCustomer(const Customer *c) {
    /* TODO:
     * printf("  Ma KH    : %s\n", c->customerId);
     * printf("  Ho ten   : %s\n", c->fullName);
     * ... các trường còn lại
     */
}

void listAllCustomers(void) {
    /* TODO:
     * if (customerCount == 0) { puts("Chua co khach hang."); return; }
     * In header bảng: STT | Mã KH | Họ tên | SĐT | Biển số | Loại xe | Phiếu
     * Duyệt vòng for in từng dòng
     */
}

/* =========================================================
 * SECTION 8: SERVICE
 * ========================================================= */

void initServices(void) {
    /* TODO: serviceCount = 0; memset(services, 0, sizeof(services)); */
}

int addService(void) {
    /* TODO:
     * 1. Kiểm tra serviceCount < MAX_SERVICES
     * 2. Nhập tên dịch vụ (không rỗng)
     * 3. Nhập đơn giá (phải > 0)
     * 4. generateServiceId(serviceCount + 1, services[serviceCount].serviceId)
     * 5. Gán isActive = 1; serviceCount++;
     * 6. saveServices(); printSuccess(); return 1;
     */
    return 0; /* placeholder */
}

int editService(void) {
    /* TODO:
     * 1. listAllServices()
     * 2. Nhập serviceId cần sửa
     * 3. int idx = findServiceById(id); if (idx == -1) { lỗi; return 0; }
     * 4. Menu: [1] Sửa tên  [2] Sửa đơn giá  [0] Huỷ
     * 5. Cập nhật, saveServices(), printSuccess(), return 1
     */
    return 0; /* placeholder */
}

int findServiceById(const char *serviceId) {
    /* TODO:
     * for (int i = 0; i < serviceCount; i++)
     *     if (strcmp(services[i].serviceId, serviceId) == 0 && services[i].isActive)
     *         return i;
     * return -1;
     */
    return -1; /* placeholder */
}

void listAllServices(void) {
    /* TODO:
     * In header: STT | Mã DV | Tên dịch vụ | Đơn giá
     * Duyệt for, chỉ in isActive == 1; dùng formatMoney cho đơn giá
     */
}

/* =========================================================
 * SECTION 9: REPAIR ORDER
 * ========================================================= */

void initOrders(void) {
    /* TODO: orderCount = 0; memset(orders, 0, sizeof(orders)); */
}

int createRepairOrder(void) {
    /* TODO:
     * 1. Kiểm tra orderCount < MAX_REPAIR_ORDERS
     * 2. Nhập SĐT, findCustomerByPhone() -> nếu -1 báo lỗi return 0
     * 3. printCustomer để xác nhận
     * 4. Nhập symptom (không rỗng)
     * 5. Khởi tạo RepairOrder mới:
     *    generateOrderId(orderCount+1, o->orderId)
     *    strcpy(o->customerPhone, phone)
     *    o->status = STATUS_RECEIVED
     *    o->createdDate = time(NULL)
     *    o->itemCount = 0; o->totalAmount = 0
     * 6. Vòng lặp thêm dịch vụ:
     *    listAllServices(); hỏi "[1] Them  [0] Xong"
     *    nếu 1 -> addItemToOrder(orderCount)
     * 7. orderCount++; customers[cIdx].orderCount++;
     * 8. saveOrders(); saveCustomers(); printSuccess(); return 1
     */
    return 0; /* placeholder */
}

int addItemToOrder(int idx) {
    /* TODO:
     * 1. Kiểm tra orders[idx].itemCount < MAX_ITEMS_PER_ORDER
     * 2. Nhập serviceId; findServiceById() -> nếu -1 báo lỗi return 0
     * 3. Nhập quantity (> 0)
     * 4. Tạo RepairItem: sao chép serviceId, serviceName, unitPrice
     *    subtotal = quantity * unitPrice
     * 5. Gán vào orders[idx].items[itemCount++]
     * 6. orders[idx].totalAmount += subtotal
     * 7. return 1
     */
    return 0; /* placeholder */
}

int updateOrderStatus(void) {
    /* TODO:
     * 1. Nhập orderId
     * 2. findOrderById() -> nếu -1 báo lỗi return 0
     * 3. Nếu status == STATUS_DONE -> cảnh báo "Phieu da hoan thanh", return 0
     * 4. In trạng thái hiện tại và kế tiếp, hỏi xác nhận
     * 5. status++; updatedDate = time(NULL)
     * 6. saveOrders(); printSuccess(); return 1
     */
    return 0; /* placeholder */
}

int findOrderById(const char *orderId) {
    /* TODO:
     * for (int i = 0; i < orderCount; i++)
     *     if (strcmp(orders[i].orderId, orderId) == 0) return i;
     * return -1;
     */
    return -1; /* placeholder */
}

int findOrdersByPhone(const char *phone, int *result, int maxResult) {
    /* TODO:
     * int count = 0;
     * for (int i = 0; i < orderCount && count < maxResult; i++)
     *     if (strcmp(orders[i].customerPhone, phone) == 0)
     *         result[count++] = i;
     * return count;
     */
    return 0; /* placeholder */
}

int findOrdersByPlate(const char *plate, int *result, int maxResult) {
    /* TODO:
     * int cIdx = findCustomerByPlate(plate);
     * if (cIdx == -1) return 0;
     * return findOrdersByPhone(customers[cIdx].phoneNumber, result, maxResult);
     */
    return 0; /* placeholder */
}

void printOrder(const RepairOrder *o) {
    /* TODO:
     * printDivider();
     * printf("  Ma phieu   : %s\n", o->orderId);
     * printf("  SDT KH     : %s\n", o->customerPhone);
     * printf("  Trieu chung: %s\n", o->symptom);
     * char dtBuf[20]; formatDateTime(o->createdDate, dtBuf);
     * printf("  Ngay tao   : %s\n", dtBuf);
     * printf("  Trang thai : "); printStatus(o->status); puts("");
     * printDivider();
     * --- In bảng dịch vụ ---
     * for (int i = 0; i < o->itemCount; i++) { ... }
     * --- Tổng tiền ---
     * char monBuf[30]; formatMoney(o->totalAmount, monBuf);
     * printf("  TONG TIEN  : %s\n", monBuf);
     * printDivider();
     */
}

void listOrders(int statusFilter) {
    /* TODO:
     * In header: STT | Mã phiếu | SĐT KH | Ngày tạo | Trạng thái | Tổng tiền
     * Duyệt for; nếu statusFilter == -1 hoặc == orders[i].status thì in
     */
}

void viewCustomerHistory(void) {
    /* TODO:
     * 1. Nhập SĐT; findCustomerByPhone() -> nếu -1 báo lỗi return
     * 2. printCustomer
     * 3. int indices[MAX_REPAIR_ORDERS];
     *    int n = findOrdersByPhone(phone, indices, MAX_REPAIR_ORDERS);
     * 4. if (n == 0) puts("Chua co lich su sua chua.");
     * 5. else for (int i = 0; i < n; i++) printOrder(&orders[indices[i]]);
     */
}

void searchOrderMenu(void) {
    /* TODO:
     * [1] Tìm theo mã phiếu -> findOrderById -> printOrder
     * [2] Tìm theo biển số  -> findOrdersByPlate -> printOrder từng phiếu
     */
}

/* =========================================================
 * SECTION 10: REPORT (NÂNG CAO)
 * ========================================================= */

void reportDailyRevenue(void) {
    /* TODO:
     * 1. Lấy ngày hôm nay qua localtime(time(NULL))
     * 2. Duyệt orders[], chỉ xét STATUS_DONE và createdDate trùng ngày hôm nay
     * 3. Cộng totalAmount, đếm số phiếu
     * 4. In kết quả
     */
}

void reportTopServices(void) {
    /* TODO:
     * 1. Tạo mảng đếm theo serviceId
     * 2. Duyệt tất cả orders[].items[], cộng quantity vào bộ đếm tương ứng
     * 3. Sắp xếp giảm dần
     * 4. In top 5
     */
}

int exportInvoice(const char *orderId) {
    /* TODO:
     * 1. findOrderById(orderId) -> nếu -1 báo lỗi return 0
     * 2. Tạo tên file "invoice_XXXXXXX.txt"
     * 3. fopen(filename, "w")
     * 4. Ghi thông tin hóa đơn đầy đủ vào file
     * 5. fclose; printSuccess("Da xuat hoa don: filename"); return 1
     */
    return 0; /* placeholder */
}

void reportMenu(void) {
    int choice;
    do {
        printHeader("THONG KE & HOA DON");
        printf("  [1] Doanh thu trong ngay\n");
        printf("  [2] Dich vu ban chay nhat\n");
        printf("  [3] Xuat hoa don phieu sua\n");
        printf("  [0] Quay lai\n");
        printDivider();
        printf("  Lua chon: ");
        scanf(" %d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1: reportDailyRevenue(); break;
            case 2: reportTopServices();  break;
            case 3: {
                char oid[ID_LEN];
                printf("  Nhap ma phieu: ");
                readLine(oid, ID_LEN);
                exportInvoice(oid);
                break;
            }
            case 0: break;
            default: printError("Lua chon khong hop le.");
        }
    } while (choice != 0);
}

/* =========================================================
 * SECTION 11: MENU CON
 * ========================================================= */

static void menuCustomer(void) {
    int choice;
    do {
        printHeader("QUAN LY KHACH HANG");
        printf("  [1] Them khach hang moi\n");
        printf("  [2] Sua thong tin khach hang\n");
        printf("  [3] Tim kiem khach hang\n");
        printf("  [4] Xem danh sach tat ca khach hang\n");
        printf("  [0] Quay lai\n");
        printDivider();
        printf("  Lua chon: ");
        scanf(" %d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1: addCustomer();        break;
            case 2: editCustomer();       break;
            case 3: searchCustomerMenu(); break;
            case 4: listAllCustomers();   break;
            case 0: break;
            default: printError("Lua chon khong hop le.");
        }
    } while (choice != 0);
}

static void menuRepair(void) {
    int choice;
    do {
        printHeader("QUAN LY PHIEU SUA CHUA");
        printf("  [1] Tao phieu sua moi\n");
        printf("  [2] Cap nhat trang thai phieu\n");
        printf("  [3] Xem chi tiet phieu\n");
        printf("  [4] Xem tat ca phieu\n");
        printf("  [5] Loc phieu theo trang thai\n");
        printf("  [6] Lich su sua chua cua khach hang\n");
        printf("  [7] Tim kiem phieu\n");
        printf("  [0] Quay lai\n");
        printDivider();
        printf("  Lua chon: ");
        scanf(" %d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1: createRepairOrder();   break;
            case 2: updateOrderStatus();   break;
            case 3: {
                char oid[ID_LEN];
                printf("  Nhap ma phieu: ");
                readLine(oid, ID_LEN);
                int idx = findOrderById(oid);
                if (idx == -1) printError("Khong tim thay phieu.");
                else printOrder(&orders[idx]);
                break;
            }
            case 4: listOrders(-1);        break;
            case 5: {
                int st;
                printf("  Trang thai [0=Tiep nhan, 1=Dang sua, 2=Hoan thanh]: ");
                scanf(" %d", &st);
                while (getchar() != '\n');
                listOrders(st);
                break;
            }
            case 6: viewCustomerHistory(); break;
            case 7: searchOrderMenu();     break;
            case 0: break;
            default: printError("Lua chon khong hop le.");
        }
    } while (choice != 0);
}

static void menuService(void) {
    int choice;
    do {
        printHeader("QUAN LY DANH MUC DICH VU");
        printf("  [1] Them dich vu moi\n");
        printf("  [2] Sua dich vu\n");
        printf("  [3] Xem danh sach dich vu\n");
        printf("  [0] Quay lai\n");
        printDivider();
        printf("  Lua chon: ");
        scanf(" %d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1: addService();      break;
            case 2: editService();     break;
            case 3: listAllServices(); break;
            case 0: break;
            default: printError("Lua chon khong hop le.");
        }
    } while (choice != 0);
}

/* =========================================================
 * SECTION 12: MAIN
 * ========================================================= */

int main(void) {
    int choice;

    initCustomers();
    initServices();
    initOrders();

    ensureDataDir();
    loadAllData();

    do {
        printHeader("QUAN LY TIEM SUA XE - NHOM BUG KILLER");
        printf("  [1] Quan ly khach hang\n");
        printf("  [2] Quan ly phieu sua chua\n");
        printf("  [3] Quan ly danh muc dich vu\n");
        printf("  [4] Thong ke & Hoa don\n");
        printf("  [0] Thoat chuong trinh\n");
        printDivider();
        printf("  Lua chon: ");
        scanf(" %d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1: menuCustomer(); break;
            case 2: menuRepair();   break;
            case 3: menuService();  break;
            case 4: reportMenu();   break;
            case 0:
                saveAllData();
                printSuccess("Da luu du lieu. Tam biet!");
                break;
            default:
                printError("Lua chon khong hop le. Vui long thu lai.");
        }
    } while (choice != 0);

    return 0;
}
