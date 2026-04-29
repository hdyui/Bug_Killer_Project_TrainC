#ifndef SERVICE_H
#define SERVICE_H

/* =========================================================
 * service.h - Khai báo hàm quản lý danh mục dịch vụ
 * ========================================================= */

#include "models.h"

/* --- Bộ nhớ toàn cục --- */
extern Service services[MAX_SERVICES];
extern int     serviceCount;

/* --- Khởi tạo --- */
void initServices(void);

/* --- CRUD --- */

/*
 * Thêm dịch vụ mới vào danh mục.
 * Nhập: tên dịch vụ, đơn giá.
 * Sinh serviceId tự động.
 * Lưu file sau khi thêm.
 * Trả về 1 thành công, 0 thất bại.
 */
int addService(void);

/*
 * Sửa tên hoặc đơn giá của một dịch vụ theo serviceId.
 * Lưu file sau khi sửa.
 * Trả về 1 thành công, 0 không tìm thấy.
 */
int editService(void);

/* --- Tìm kiếm --- */

/*
 * Tìm vị trí dịch vụ theo serviceId.
 * Trả về index nếu tìm thấy và isActive == 1, ngược lại -1.
 */
int findServiceById(const char *serviceId);

/* --- Hiển thị --- */

/*
 * In danh sách dịch vụ đang hoạt động dạng bảng.
 */
void listAllServices(void);

#endif /* SERVICE_H */
