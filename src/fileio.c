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
    /* TODO:
     * Gọi lần lượt: loadCustomers(), loadServices(), loadOrders()
     * Nếu muốn, in thông báo "Đã tải dữ liệu: X khách, Y phiếu, Z dịch vụ"
     */
}

void saveAllData(void) {
    /* TODO:
     * Gọi lần lượt: saveCustomers(), saveServices(), saveOrders()
     */
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
    return 0; /* placeholder */
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
    return 0; /* placeholder */
}

/* =========================================================
 * PHIẾU SỬA
 * ========================================================= */

int saveOrders(void) {
    /* TODO:
     * Tương tự saveCustomers nhưng cho orders[] và FILE_ORDERS
     */
    return 0; /* placeholder */
}

int loadOrders(void) {
    /* TODO:
     * Tương tự loadCustomers nhưng cho orders[] và FILE_ORDERS
     */
    return 0; /* placeholder */
}

/* =========================================================
 * DANH MỤC DỊCH VỤ
 * ========================================================= */

int saveServices(void) {
    /* TODO:
     * Tương tự saveCustomers nhưng cho services[] và FILE_SERVICES
     */
    return 0; /* placeholder */
}

int loadServices(void) {
    /* TODO:
     * Tương tự loadCustomers nhưng cho services[] và FILE_SERVICES
     */
    return 0; /* placeholder */
}
