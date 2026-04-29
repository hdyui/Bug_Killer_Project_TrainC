/* =========================================================
 * report.c - Thống kê doanh thu và xuất hóa đơn
 * (Tính năng nâng cao - có điểm cộng)
 * ========================================================= */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "report.h"
#include "repair.h"
#include "customer.h"
#include "service.h"
#include "utils.h"
#include "constants.h"

/* =========================================================
 * THỐNG KÊ DOANH THU NGÀY
 * ========================================================= */

void reportDailyRevenue(void) {
    /* TODO:
     * 1. Lấy ngày hôm nay bằng time(NULL) và localtime
     * 2. Duyệt tất cả orders[]:
     *    - Chỉ xét phiếu có status == STATUS_DONE
     *    - Dùng localtime(&orders[i].createdDate) để lấy ngày tạo
     *    - So sánh tm_year, tm_mon, tm_mday với ngày hôm nay
     *    - Nếu khớp: cộng totalAmount vào biến tổng, tăng biến đếm
     * 3. In kết quả:
     *    "Hôm nay (DD/MM/YYYY): X phiếu hoàn thành | Doanh thu: Y VNĐ"
     */
}

/* =========================================================
 * TOP DỊCH VỤ BÁN CHẠY
 * ========================================================= */

void reportTopServices(void) {
    /* TODO:
     * 1. Tạo mảng tally[MAX_SERVICES] để đếm tổng quantity của từng dịch vụ
     *    (hoặc dùng mảng cặp {serviceId, totalQty} để tiện sort)
     * 2. Duyệt tất cả orders[], duyệt items bên trong
     *    Tìm vị trí serviceId trong mảng tally và cộng quantity
     * 3. Sắp xếp tally theo totalQty giảm dần (bubble sort hoặc selection sort)
     * 4. In top 5 (hoặc ít hơn nếu không đủ):
     *    STT | Mã DV | Tên dịch vụ | Tổng số lần
     */
}

/* =========================================================
 * XUẤT HÓA ĐƠN
 * ========================================================= */

int exportInvoice(const char *orderId) {
    /* TODO:
     * 1. Gọi findOrderById(orderId); nếu -1 -> báo lỗi, return 0
     * 2. Tìm thông tin khách qua orders[idx].customerPhone
     * 3. Tạo tên file "invoice_XXXXXXX.txt"
     * 4. fopen(filename, "w")
     * 5. Ghi vào file:
     *    ====================================
     *    TIỆM SỬA XE CHÚ TÁM
     *    HÓA ĐƠN DỊCH VỤ
     *    Ngày xuất: DD/MM/YYYY HH:MM
     *    ====================================
     *    Mã phiếu   : ...
     *    Khách hàng : ...
     *    SĐT        : ...
     *    Biển số    : ...
     *    Loại xe    : ...
     *    Triệu chứng: ...
     *    ------------------------------------
     *    Dịch vụ:
     *    (từng item: tên, SL, đơn giá, thành tiền)
     *    ------------------------------------
     *    TỔNG TIỀN  : X VNĐ
     *    ====================================
     * 6. fclose(fp)
     * 7. In thông báo "Đã xuất hóa đơn ra file: filename", return 1
     */
    return 0; /* placeholder */
}

/* =========================================================
 * MENU THỐNG KÊ
 * ========================================================= */

void reportMenu(void) {
    /* TODO:
     * Hiển thị menu vòng lặp:
     *   [1] Doanh thu trong ngày
     *   [2] Dịch vụ bán chạy nhất
     *   [3] Xuất hóa đơn phiếu sửa
     *   [0] Quay lại
     * Nhận lựa chọn và gọi hàm tương ứng
     */
}
