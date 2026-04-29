/* =========================================================
 * repair.c - Cài đặt quản lý phiếu sửa chữa
 * ========================================================= */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "repair.h"
#include "customer.h"
#include "service.h"
#include "fileio.h"
#include "utils.h"
#include "constants.h"

/* --- Định nghĩa bộ nhớ toàn cục --- */
RepairOrder orders[MAX_REPAIR_ORDERS];
int         orderCount = 0;

/* =========================================================
 * KHỞI TẠO
 * ========================================================= */

void initOrders(void) {
    /* TODO:
     * Gán orderCount = 0
     * memset mảng orders về 0
     */
}

/* =========================================================
 * TẠO PHIẾU SỬA
 * ========================================================= */

int createRepairOrder(void) {
    /* TODO:
     * 1. Kiểm tra orderCount < MAX_REPAIR_ORDERS
     * 2. Nhập SĐT khách hàng
     * 3. Gọi findCustomerByPhone(); nếu -1 -> báo lỗi "Không tìm thấy khách", return 0
     * 4. In thông tin khách để xác nhận (printCustomer)
     * 5. Nhập symptom (không được rỗng)
     * 6. Khởi tạo phiếu mới: sinh orderId, gán customerPhone, symptom
     *    status = STATUS_RECEIVED, createdDate = time(NULL), itemCount = 0, totalAmount = 0
     * 7. Vòng lặp thêm dịch vụ:
     *    a. Hiển thị danh mục (listAllServices)
     *    b. Hỏi "Thêm dịch vụ? [1] Có  [0] Xong"
     *    c. Nếu chọn 1 -> gọi addItemToOrder(orderCount) với phiếu tạm
     *    d. Lặp cho đến khi chọn 0 hoặc đạt MAX_ITEMS_PER_ORDER
     * 8. Tăng orderCount
     * 9. Tăng customers[cIdx].orderCount
     * 10. Gọi saveOrders() và saveCustomers()
     * 11. In thông báo thành công + tóm tắt phiếu, return 1
     */
    int status = 1;
    int index; //vị trí khách hàng trong mảng 
    char phoneNumber[PHONE_LEN];
    int isConfirm;
    if(orderCount >= MAX_REPAIR_ORDERS){
        printf("So luong vuot muc toi da\n");
        status = 0;
        return status;
    }
   
    do{
        printf("Nhap so dien thoai khach hang: ");
        scanf("%[^\n]", phoneNumber);
        
        printf("Xac nhan so dien thoai ban muon tim: %s\n", phoneNumber);
        printf("[1] Xac nhan\n");
        printf("[0] Nhap lai\n");
        printf("Nhap lua chon: ");
        scanf("%d", &isConfirm);
        while (getchar() != '\n');
        if(findCustomerByPhone(phoneNumber) == -1){
            printf("Khong ton tai so dien nay nay: %s\n", phoneNumber);
        }
        else{
            printf("%-20s %-20s %-20s %-20s %-20s %-20s\n",
            "ID", "Name", "Phone", "Car plate", "Car type", "Order count");
            index = findCustomerByPhone(phoneNumber);
            printf("%-20s %-20s %-20s %-20s %-20s %-20d\n",
                customers[index].customerId, customers[index].fullName,
                customers[index].phoneNumber, customers[index].carPlate,
                customers[index].carType, customers[index].orderCount);
        }
        if(isConfirm != 1){
                printf("Vui long nhap [1] hoac [0]\n");
        }
    }
    while(isConfirm != 1 || findCustomerByPhone(phoneNumber) == -1);
    generateOrderId();
    strcpy(orders[orderCount].customerPhone, customers[index].phoneNumber);
    char symptom[SYMPTOM_LEN];
    do{
        printf("Nhap tinh trang xe cua ban: ");
        scanf("%[^\n]", symptom);
        while (getchar() != '\n');
    }
    while(strlen(symptom) == 0);
    strcpy(orders[orderCount].symptom, symptom);
    orders[orderCount].status = STATUS_RECEIVED;
    orders[orderCount].createdDate = time(NULL);
    orders[orderCount].itemCount = 0;
    orders[orderCount].totalAmount = 0;


    listAllServices();
    char serviceId[ID_LEN];
    do{
        printf("Nhap ma dich vu can them vao phieu (VD: SV000001), nhap 0 de ket thuc: ");
        scanf("%[^\n]", serviceId);
        while (getchar() != '\n');
        
        int serviceIdx = findServiceById(serviceId);
        if(serviceIdx == -1 || services[serviceIdx].isActive == 0){
            printf("Khong tim thay dich vu hoac dich vu khong hoat dong.\n");
            continue;
        }
        addItemToOrder(orderCount, serviceIdx);
        
    }
    while(strcmp(serviceId, "0") != 0);
        
    orderCount++;
    customers[index].orderCount++;


    

    printf("Tao phieu thanh cong\n");
    return status;
}

int addItemToOrder(int orderIdx, int serviceIdx) {
    /* TODO:
     * 1. Kiểm tra orders[idx].itemCount < MAX_ITEMS_PER_ORDER; nếu đầy -> báo lỗi, return 0
     * 2. Nhập serviceId
     * 3. Gọi findServiceById(); nếu -1 -> báo lỗi, return 0
     * 4. Nhập quantity (phải > 0)
     * 5. Tạo RepairItem: sao chép serviceId, serviceName, unitPrice từ services[]
     *    gán quantity, tính subtotal = quantity * unitPrice
     * 6. Gán item vào orders[idx].items[orders[idx].itemCount]
     * 7. Tăng orders[idx].itemCount
     * 8. Cộng subtotal vào orders[idx].totalAmount
     * 9. return 1
     */
    int status = 1; 
    if(orders[orderIdx].itemCount >= MAX_ITEMS_PER_ORDER){
        printf("So luong dich vu vuot muc toi da\n");
        status = 0;
        return status;
    }   
    int quantity;
    do{
        printf("Nhap so luong: ");
        scanf("%d", &quantity);
        while(getchar () != '\n');
    }
    while(quantity <= 0);
    int itemIdx = orders[orderIdx].itemCount;

    strcpy(orders[orderIdx].items[itemIdx].serviceId,
                    services[serviceIdx].serviceId);

    strcpy(orders[orderIdx].items[itemIdx].serviceName,
            services[serviceIdx].name);

    orders[orderIdx].items[itemIdx].unitPrice =
           services[serviceIdx].unitPrice;

    orders[orderIdx].items[itemIdx].quantity = quantity;

    orders[orderIdx].items[itemIdx].subtotal = 
            quantity * services[serviceIdx].unitPrice;
    
    orders[orderIdx].totalAmount += orders[orderIdx].items[itemIdx].subtotal;


    orders[orderIdx].itemCount++;
    return status;
}

/* =========================================================
 * CẬP NHẬT TRẠNG THÁI
 * ========================================================= */

int updateOrderStatus(void) {
    /* TODO:
     * 1. Nhập orderId cần cập nhật
     * 2. Gọi findOrderById(); nếu -1 -> báo lỗi, return 0
     * 3. Lấy status hiện tại
     * 4. Nếu status == STATUS_DONE -> báo "Phiếu đã hoàn thành, không thể cập nhật", return 0
     * 5. In trạng thái hiện tại và trạng thái kế tiếp, hỏi xác nhận
     * 6. Nếu xác nhận: status++ (tiến một bước), gán updatedDate = time(NULL)
     * 7. Gọi saveOrders()
     * 8. In thành công, return 1
     */
    char orderId[ID_LEN];
    
    printf("Nhap ma phieu: ");
    readLine(orderId, ID_LEN);

    int idx = findOrderById(orderId);
    if (idx == -1) {
        printError("Khong tim thay phieu!");
        return 0;
    }

    RepairOrder *o = &orders[idx];

    // Nếu đã hoàn thành thì chặn
    if (o->status == STATUS_DONE) {
        printError("Phieu da hoan thanh, khong the cap nhat.");
        return 0;
    }

    // Hiển thị trạng thái hiện tại
    printf("Trang thai hien tai: ");
    printStatus(o->status);
    printf("\n");

    // Hiển thị trạng thái tiếp theo
    printf("Trang thai ke tiep: ");
    printStatus(o->status + 1);
    printf("\n");

    // Xác nhận
    int confirm;
    do {
        printf("Ban co chac chan cap nhat? [1: Yes | 0: No]: ");
        scanf("%d", &confirm);
        while (getchar() != '\n');

        if (confirm != 0 && confirm != 1) {
            printError("Nhap 0 hoac 1.");
        }
    } while (confirm != 0 && confirm != 1);

    if (confirm == 0) {
        printf("Da huy cap nhat.\n");
        return 0;
    }

    // Update trạng thái
    o->status++;
    o->updatedDate = time(NULL);

    // Lưu file
    if (!saveOrders()) {
        printError("Loi khi luu du lieu.");
        return 0;
    }

    printSuccess("Cap nhat trang thai thanh cong.");
    return 1;
}

/* =========================================================
 * TÌM KIẾM
 * ========================================================= */

int findOrderById(const char *orderId) {
    /* TODO:
     * Duyệt for từ 0 đến orderCount - 1
     * Nếu strcmp(orders[i].orderId, orderId) == 0 -> return i
     * Nếu không tìm thấy -> return -1
     */
    int left = 0, right = orderCount - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(strcmp(orderId, orders[mid].orderId) < 0){
            right = mid - 1;
        }
        else if(strcmp(orderId, orders[mid].orderId) > 0){
            left = mid + 1;
        }
        else{
            return mid;
        }
    }
    return -1;
}

int findOrdersByPhone(const char *phone, int *result, int maxResult) {
    /* TODO:
     * Duyệt for; nếu strcmp(orders[i].customerPhone, phone) == 0
     * và count < maxResult thì gán result[count++] = i
     * Trả về count
     */
    int count = 0;

    for (int i = 0; i < orderCount; i++) {
        if (count >= maxResult){
            break; 
        }

        if (strcmp(orders[i].customerPhone, phone) == 0) {
            result[count] = i; 
            count++;          
        }
    }
    return count; 
}

int findOrdersByPlate(const char *plate, int *result, int maxResult) {
    /* TODO:
     * 1. Gọi findCustomerByPlate(plate) để lấy cIdx
     * 2. Nếu cIdx == -1 -> return 0
     * 3. Lấy customers[cIdx].phoneNumber
     * 4. Gọi findOrdersByPhone(...) với số điện thoại đó
     * 5. Trả về kết quả
     */
    int cIdx = findCustomerByPlate(plate);
    if(cIdx == -1) {
        return 0;
    }
}

/* =========================================================
 * HIỂN THỊ
 * ========================================================= */

void printOrder(const RepairOrder *o) {
    printDivider();

    printf("  CHI TIET PHIEU SUA CHUA\n");
    printDivider();

    printf("  Ma phieu   : %s\n", o->orderId);
    printf("  SDT KH     : %s\n", o->customerPhone);
    printf("  Trieu chung: %s\n", o->symptom);

    char dtBuf[20]; // dtBuf (Date time buffer): là cái mảng chứa chuỗi kết quả sau khi format thời gian 
    formatDateTime(o->createdDate, dtBuf); // Lấy thời gian dạng số (time_t) → convert → ghi vào dtBuf
    printf("  Ngay tao   : %s\n", dtBuf); // In ra thời gian

    printf("  Trang thai : ");
    printStatus(o->status);
    printf("\n");

    // thông tin khách
    int cIdx = findCustomerByPhone(o->customerPhone);
    // cIdx (Customer index): Vị trí của khách hàng trong mảng, giá trị của biến này được trả về khi gọi hàm findCustomerByPhone
    if (cIdx != -1) {
        printDivider();
        printf("  THONG TIN KHACH HANG\n");
        printCustomer(&customers[cIdx]);
    }

    printDivider();

    // bảng dịch vụ
    printf("  DANH SACH DICH VU\n");
    printDivider();

    printf("  %-4s %-25s %-5s %-15s %-15s\n", "STT", "Ten DV", "SL", "Don gia", "Thanh tien");
    printDivider();

    for (int i = 0; i < o->itemCount; i++) { // Vòng lặp này dùng để duyệt từng dịch vụ trong phiếu
        char priceBuf[30], subBuf[30]; // priceBuf để lưu giá tiền 1 lần làm dịch vụ và subBuf để lưu tổng giá tiền của 1 dịch vụ

        formatMoney(o->items[i].unitPrice, priceBuf);
        formatMoney(o->items[i].subtotal, subBuf);

        printf("  %-4d %-25s %-5d %-15s %-15s\n",
               i + 1, // i + 1 là số thứ tự
               o->items[i].serviceName, // Tên dịch vụ
               o->items[i].quantity, // Số lượng lần làm cái dịch vụ đó
               priceBuf, // Số tiền 1 lần làm dịch vụ đó
               subBuf); // Tổng số tiền làm dịch vụ đó (Ví dụ như thay bánh xe thì thay 2 bánh thì tổng số tiền sẽ là 2 * số tiền thay 1 bánh
    }

    printDivider();

    // tổng tiền
    char totalBuf[30];
    formatMoney(o->totalAmount, totalBuf);
    printf("  TONG TIEN: %s\n", totalBuf);
    printDivider();
}

void listOrders(int statusFilter) {
    printDivider();
    printf("  %-4s %-10s %-15s %-20s %-15s %s\n",
           "STT", "Ma phieu", "SDT KH", "Ngay tao", "Trang thai", "Tong tien");
    printDivider();
    for(int i = 0; i < orderCount; i ++){
        if(statusFilter == -1 || statusFilter == orders[i].status){
            char dateFormatted[20];
            char moneyFormatted[30];
            formatDateTime(orders[i].createdDate, dateFormatted);
            formatMoney(orders[i].totalAmount, moneyFormatted);
            printf("  %-4d %-10s %-15s %-20s %-15s %s\n",
                   i + 1, orders[i].orderId, orders[i].customerPhone,
                   dateFormatted, getStatusString(orders[i].status), moneyFormatted);
        }
    }
}

void viewCustomerHistory(void) {
    char phone[PHONE_LEN];
    printf("Nhap so dien thoai khach hang: ");
    scanf("%[^\n]", phone);
    int index_array[MAX_REPAIR_ORDERS];
    int n = findOrdersByPhone(phone, index_array, MAX_REPAIR_ORDERS);
    if (n == 0) {
        printf("Khach hang chua co lich su sua chua.\n");
    }
    else{
        for(int i = 0; i < n; i++){
            printOrder(&orders[index_array[i]]);
        }
    }
}

void searchOrderMenu(void) {
    int choice;
    do{
        printf("Lua chon tim kiem:\n");
        printf("[1] Tim theo ma phieu\n");
        printf("[2] Tim theo bien so xe\n");
        printDivider();
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        if(choice != 1 && choice != 2){
            printf("Vui long nhap [1] hoac [2]\n");
        }
        
    }
    while(choice != 1 && choice != 2);
    if(choice == 1){
        char OrderId[ID_LEN];
        printf("Nhap ma phieu: ");
        scanf("%[^\n]", OrderId);
        int idx = findOrderById(OrderId); 
        if(idx == -1){
            printf("Khong tim thay phieu\n");
        }
        else{
            printOrder(&orders[idx]);
        }
    }
    else if(choice == 2){
        char plate[PLATE_LEN];
        printf("Nhap bien so xe: ");
        scanf("%[^\n]", plate);
        int idxArr[MAX_REPAIR_ORDERS];
        int n = findOrdersByPlate(plate, idxArr, MAX_REPAIR_ORDERS);
        if(n == 0){
            printf("Khong tim thay phieu nao voi bien so xe nay\n");
        }
        else{
            for(int i = 0; i < n; i++){
                printOrder(&orders[idxArr[i]]);
            }
        }
    }
}
