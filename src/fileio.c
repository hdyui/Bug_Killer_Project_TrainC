/* =========================================================
 * fileio.c - Đọc/ghi dữ liệu ra file nhị phân
 * ========================================================= */

#include <stdio.h>
#include <sys/stat.h>
#include "fileio.h"
#include "customer.h"
#include "repair.h"
#include "service.h"
#include "utils.h"
#include "constants.h"

/* =========================================================
 * TIỆN ÍCH
 * ========================================================= */

void ensureDataDir(void) {
    /* TODO:
     * Gọi mkdir("data", 0755) để tạo thư mục data/ nếu chưa có.
     * (Trên Windows dùng _mkdir("data"), trên Linux/Mac dùng mkdir với mode)
     * Bỏ qua lỗi nếu thư mục đã tồn tại (errno == EEXIST).
     */
}

void loadAllData(void) {
    loadCustomers();
    loadServices();
    loadOrders();
}

void saveAllData(void) {
    saveCustomers(); 
    saveServices();  
    saveOrders();  
}

/* =========================================================
 * KHÁCH HÀNG
 * ========================================================= */

int saveCustomers(void) {
    /* TODO:
     * 1. Mở FILE_CUSTOMERS với fopen("...", "wb") - write binary
     * 2. Nếu mở thất bại -> gọi printError, return 0
     * 3. fwrite(&customerCount, sizeof(int), 1, fp)
     * 4. fwrite(customers, sizeof(Customer), customerCount, fp)
     * 5. fclose(fp)
     * 6. return 1
     */
    FILE *fp = fopen(FILE_CUSTOMERS, "w");

    if (!fp) {
        printError("Khong the ghi file khach hang.");
        return 0;
    }

    fprintf(fp, "%d\n", customerCount);

    for (int i = 0; i < customerCount; i++) {
        fprintf(fp, "%s|%s|%s|%s|%s|%d\n",
            customers[i].customerId,
            customers[i].fullName,
            customers[i].phoneNumber,
            customers[i].carPlate,
            customers[i].carType,
            customers[i].orderCount
        );
    }

    fclose(fp);
    return 1;
}

int loadCustomers(void) {
    /* TODO:
     * 1. Mở FILE_CUSTOMERS với fopen("...", "rb") - read binary
     * 2. Nếu file không tồn tại (fp == NULL) -> return 0 (bình thường, lần đầu chạy)
     * 3. fread(&customerCount, sizeof(int), 1, fp)
     * 4. fread(customers, sizeof(Customer), customerCount, fp)
     * 5. fclose(fp)
     * 6. return 1
     */
    FILE *fp = fopen(FILE_CUSTOMERS, "r");
    if (!fp) return 0;

    fscanf(fp, "%d\n", &customerCount);

    for (int i = 0; i < customerCount; i++) {
        fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d\n",
            customers[i].customerId,
            customers[i].fullName,
            customers[i].phoneNumber,
            customers[i].carPlate,
            customers[i].carType,
            &customers[i].orderCount
        );
    }

    fclose(fp);
    return 1;
}

/* =========================================================
 * PHIẾU SỬA
 * ========================================================= */

int saveOrders(void) {
    /* TODO:
     * Tương tự saveCustomers nhưng cho orders[] và FILE_ORDERS
     */
    FILE *fp = fopen(FILE_ORDERS, "w");

    if (!fp) {
        printError("Khong the ghi file phieu sua.");
        return 0;
    }

    fprintf(fp, "%d\n", orderCount);

    for (int i = 0; i < orderCount; i++) {
        RepairOrder *o = &orders[i];

        fprintf(fp, "%s|%s|%s|%d|%ld|%ld|%d|%.2f\n",
            o->orderId,
            o->customerPhone,
            o->symptom,
            o->status,
            o->createdDate,
            o->updatedDate,
            o->itemCount,
            o->totalAmount
        );

        for (int j = 0; j < o->itemCount; j++) {
            RepairItem *it = &o->items[j];

            fprintf(fp, "%s|%s|%d|%.2f|%.2f\n",
                it->serviceId,
                it->serviceName,
                it->quantity,
                it->unitPrice,
                it->subtotal
            );
        }
    }

    fclose(fp);
    return 1;
}

int loadOrders(void) {
    /* TODO:
     * Tương tự loadCustomers nhưng cho orders[] và FILE_ORDERS
     */
    FILE *fp = fopen(FILE_ORDERS, "r");
    if (!fp) return 0;

    fscanf(fp, "%d\n", &orderCount);

    for (int i = 0; i < orderCount; i++) {
        RepairOrder *o = &orders[i];

        fscanf(fp, "%[^|]|%[^|]|%[^|]|%d|%ld|%ld|%d|%lf\n",
            o->orderId,
            o->customerPhone,
            o->symptom,
            &o->status,
            &o->createdDate,
            &o->updatedDate,
            &o->itemCount,
            &o->totalAmount
        );

        for (int j = 0; j < o->itemCount; j++) {
            RepairItem *it = &o->items[j];

            fscanf(fp, "%[^|]|%[^|]|%d|%lf|%lf\n",
                it->serviceId,
                it->serviceName,
                &it->quantity,
                &it->unitPrice,
                &it->subtotal
            );
        }
    }

    fclose(fp);
    return 1; /* placeholder */
}

/* =========================================================
 * DANH MỤC DỊCH VỤ
 * ========================================================= */

int saveServices(void) {
    /* TODO:
     * Tương tự saveCustomers nhưng cho services[] và FILE_SERVICES
     */
    FILE *fp = fopen(FILE_SERVICES, "w");
    // Mở file ở chế độ ghi text (xóa nội dung cũ, ghi mới)

    if (!fp) {
        printError("Khong the ghi file dich vu.");
        return 0;
    }

    for (int i = 0; i < serviceCount; i++) {
        // Ghi từng service theo đúng format

        fprintf(fp, "Service ID  : %s\n", services[i].serviceId);
        // In mã dịch vụ

        fprintf(fp, "Name        : %s\n", services[i].name);
        // In tên dịch vụ

        fprintf(fp, "Unit Price  : %.2f\n", services[i].unitPrice);
        // In giá, giữ 2 số sau dấu phẩy

        fprintf(fp, "Is Active   : %d\n", services[i].isActive);
        // In trạng thái (1 = hoạt động, 0 = ngưng)

        fprintf(fp, "-----------------------------------\n");
        // Dòng phân cách (QUAN TRỌNG: phải giống format load)
    }

    fclose(fp);
    // Đóng file

    return 1;
}

int loadServices(void) {
    /* TODO:
     * Tương tự loadCustomers nhưng cho services[] và FILE_SERVICES
     */
    FILE *fp = fopen(FILE_SERVICES, "r");
    if (!fp) return 0;

    char line[256];
    serviceCount = 0;

    while (fgets(line, sizeof(line), fp)) {

        // Tìm dòng bắt đầu của 1 service
        if (strncmp(line, "Service ID", 10) == 0) {

            if (serviceCount >= MAX_SERVICES) break;

            Service *s = &services[serviceCount];

            // --- Service ID ---
            sscanf(line, "Service ID  : %s", s->serviceId);

            // --- Name ---
            if (fgets(line, sizeof(line), fp)) {
                sscanf(line, "Name        : %[^\n]", s->name);
            }

            // --- Unit Price ---
            if (fgets(line, sizeof(line), fp)) {
                sscanf(line, "Unit Price  : %lf", &s->unitPrice);
            }

            // --- Is Active ---
            if (fgets(line, sizeof(line), fp)) {
                sscanf(line, "Is Active   : %d", &s->isActive);
            }

            // --- Skip dòng gạch ---
            fgets(line, sizeof(line), fp);

            serviceCount++;
        }
    }

    fclose(fp);
    return 1;
}
