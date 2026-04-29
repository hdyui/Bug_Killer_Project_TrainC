# =========================================================
# Makefile - Build hệ thống Quản Lý Tiệm Sửa Xe
# =========================================================

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -g
TARGET  = suaxe
SRCS    = main.c customer.c service.c repair.c fileio.c report.c utils.c
OBJS    = $(SRCS:.c=.o)

# Build mặc định
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile từng file .c thành .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Xoá file object và binary
clean:
	rm -f $(OBJS) $(TARGET)

# Xoá cả dữ liệu (dùng cẩn thận!)
clean-data:
	rm -f data/*.dat data/*.txt

# Chạy chương trình
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean clean-data run
