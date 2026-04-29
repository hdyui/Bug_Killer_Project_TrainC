📋 Project Overview
A terminal-based management system built in pure C for a motorbike repair shop. The system replaces manual paper records with a structured program that manages customers, repair orders, and service catalogs — with full data persistence across sessions.
Team: Bug Killer
Mentor: Nguyễn Đức Bảo Lâm
Timeline: 17/04/2026 – 17/05/2026
Language: C (C99 standard, no external libraries)

✨ Features
Customer Management

Add new customers with name, phone number, license plate, and vehicle type
Edit customer information (name, plate, vehicle type)
Search by phone number or license plate
View full customer list

Repair Order Management

Create repair orders linked to a customer phone number
Add services from catalog to each order (up to 10 services per order)
Auto-generate order ID (RO000001, RO000002, ...)
Update order status: Received → Repairing → Done (one-way only)
View order details with full service breakdown and total amount
Filter orders by status
View full repair history of a customer
Search orders by order ID or license plate

Service Catalog

Add and edit services with name and unit price
Auto-generate service ID (SV000001, SV000002, ...)
View all active services

Reports (bonus features)

Daily revenue summary from completed orders
Top services ranked by usage count
Export invoice to .txt file

Data Persistence

All data saved to binary files after every operation
Auto-loaded on startup — no data loss on unexpected shutdown

