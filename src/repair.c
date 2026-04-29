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
    return 0; /* placeholder */
}

int addItemToOrder(int idx) {
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
    return 0; /* placeholder */
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
    return 0; /* placeholder */
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
    return -1; /* placeholder */
}

int findOrdersByPhone(const char *phone, int *result, int maxResult) {
    /* TODO:
     * Duyệt for; nếu strcmp(orders[i].customerPhone, phone) == 0
     * và count < maxResult thì gán result[count++] = i
     * Trả về count
     */
    return 0; /* placeholder */
}

int findOrdersByPlate(const char *plate, int *result, int maxResult) {
    /* TODO:
     * 1. Gọi findCustomerByPlate(plate) để lấy cIdx
     * 2. Nếu cIdx == -1 -> return 0
     * 3. Lấy customers[cIdx].phoneNumber
     * 4. Gọi findOrdersByPhone(...) với số điện thoại đó
     * 5. Trả về kết quả
     */
    return 0; /* placeholder */
}

/* =========================================================
 * HIỂN THỊ
 * ========================================================= */

void printOrder(const RepairOrder *o) {
    /* TODO:
     * In theo bố cục:
     *   ----------------------------------------
     *   Mã phiếu  : RO000001
     *   SĐT KH    : ...
     *   Triệu chứng: ...
     *   Ngày tạo  : DD/MM/YYYY HH:MM  (dùng formatDateTime)
     *   Trạng thái: ... (dùng printStatus)
     *   ----------------------------------------
     *   Dịch vụ:
     *   STT | Mã DV | Tên | SL | Đơn giá | Thành tiền
     *   (duyệt items[], dùng formatMoney)
     *   ----------------------------------------
     *   TỔNG TIỀN : 1,500,000 VNĐ
     */
}

void listOrders(int statusFilter) {
    /* TODO:
     * 1. Đếm số phiếu thoả điều kiện lọc (statusFilter == -1 hoặc == status)
     * 2. Nếu không có -> in thông báo, return
     * 3. In header: STT | Mã phiếu | SĐT KH | Ngày tạo | Trạng thái | Tổng tiền
     * 4. Duyệt for, in từng phiếu thoả điều kiện; dùng printStatus cho trạng thái
     */
}

void viewCustomerHistory(void) {
    /* TODO:
     * 1. Nhập SĐT khách hàng
     * 2. Gọi findCustomerByPhone(); nếu -1 -> báo lỗi, return
     * 3. In thông tin khách (printCustomer)
     * 4. Gọi findOrdersByPhone() -> mảng indices
     * 5. Nếu không có phiếu nào -> in "Chưa có lịch sử sửa chữa."
     * 6. Duyệt indices, gọi printOrder cho từng phiếu
     * 7. Gợi ý bảo dưỡng định kỳ (in thông điệp cố định hoặc dựa vào số phiếu)
     */
}

void searchOrderMenu(void) {
    /* TODO:
     * 1. Hiển thị lựa chọn: [1] Tìm theo mã phiếu  [2] Tìm theo biển số xe
     * 2. Nhận lựa chọn
     * 3. Nếu [1]: nhập orderId, gọi findOrderById, in printOrder nếu tìm thấy
     * 4. Nếu [2]: nhập biển số, gọi findOrdersByPlate, in từng phiếu tìm thấy
     */
}
