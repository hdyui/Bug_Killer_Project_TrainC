/* =========================================================
 * service.c - Cài đặt quản lý danh mục dịch vụ
 * ========================================================= */

#include <stdio.h>
#include <string.h>
#include "service.h"
#include "fileio.h"
#include "utils.h"
#include "constants.h"

/* --- Định nghĩa bộ nhớ toàn cục --- */
Service services[MAX_SERVICES];
int     serviceCount = 0;

/* =========================================================
 * KHỞI TẠO
 * ========================================================= */

void initServices(void) {
    /* TODO:
     * Gán serviceCount = 0
     * memset mảng services về 0
     */
}

/* =========================================================
 * THÊM DỊCH VỤ
 * ========================================================= */

int addService(void) {
    /* TODO:
     * 1. Kiểm tra serviceCount < MAX_SERVICES
     * 2. Nhập tên dịch vụ (không được rỗng)
     * 3. Nhập đơn giá: dùng scanf hoặc readLine rồi atof; đảm bảo > 0
     * 4. Sinh serviceId bằng generateServiceId(serviceCount + 1, ...)
     * 5. Gán isActive = 1
     * 6. Tăng serviceCount
     * 7. Gọi saveServices()
     * 8. In thành công, return 1
     */
    return 0; /* placeholder */
}

/* =========================================================
 * SỬA DỊCH VỤ
 * ========================================================= */

int editService(void) {
    /* TODO:
     * 1. Hiển thị danh sách dịch vụ (listAllServices)
     * 2. Nhập serviceId cần sửa
     * 3. Gọi findServiceById() -> lấy index; nếu -1 báo lỗi, return 0
     * 4. Hiển thị menu:
     *    [1] Sửa tên dịch vụ
     *    [2] Sửa đơn giá
     *    [0] Huỷ
     * 5. Nhập và validate giá trị mới
     * 6. Gọi saveServices()
     * 7. In thành công, return 1
     */
    return 0; /* placeholder */
}

/* =========================================================
 * TÌM KIẾM
 * ========================================================= */

int findServiceById(const char *serviceId) {
    /* TODO:
     * Duyệt for từ 0 đến serviceCount - 1
     * Nếu strcmp(services[i].serviceId, serviceId) == 0 VÀ services[i].isActive == 1
     *   -> return i
     * Nếu không tìm thấy, return -1
     */
    return -1; /* placeholder */
}

/* =========================================================
 * HIỂN THỊ
 * ========================================================= */

void listAllServices(void) {
    /* TODO:
     * 1. Kiểm tra không có dịch vụ nào isActive == 1 -> in thông báo rồi return
     * 2. In header: STT | Mã DV | Tên dịch vụ | Đơn giá
     * 3. Duyệt for, chỉ in các services[i].isActive == 1
     * 4. Dùng formatMoney để in đơn giá đẹp
     */
}
