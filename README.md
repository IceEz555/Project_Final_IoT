🏠 HOME ENERGY USAGE TRACKING SYSTEM USING IOT
ระบบติดตามการใช้พลังงานภายในบ้าน โดยใช้เทคโนโลยี IoT และแสดงผลบน Web Application

📌 Project Description | รายละเอียดโปรเจกต์
This project aims to monitor home energy consumption using IoT devices, specifically a CT Sensor connected to a microcontroller (e.g., ESP32). The collected energy data is sent to the cloud via AWS services and visualized on a web application.

โปรเจกต์นี้มีเป้าหมายเพื่อ ตรวจสอบการใช้พลังงานไฟฟ้าภายในบ้านแบบ Real-time โดยใช้เซนเซอร์วัดกระแสไฟ (CT Sensor) เชื่อมต่อกับบอร์ดไมโครคอนโทรลเลอร์ จากนั้นส่งข้อมูลขึ้น Cloud (AWS) และนำเสนอผ่าน Web Application ให้สามารถดูข้อมูลได้จากทุกที่

🧰 Tools & Technologies | เครื่องมือที่ใช้
⚡ CT Sensor – สำหรับวัดกระแสไฟฟ้า

🧠 ESP32 / ESP8266 – บอร์ดไมโครคอนโทรลเลอร์สำหรับประมวลผล

☁️ AWS IoT / AWS Cloud – สำหรับจัดเก็บและประมวลผลข้อมูลบน Cloud

🌐 Web Application – สำหรับแสดงผลการใช้พลังงานในรูปแบบกราฟและข้อมูล

🔧 Features | ฟีเจอร์ของระบบ
Real-time Energy Monitoring

Cloud Data Storage using AWS

Data Visualization via Web App

Portable and Scalable Design

🚀 Getting Started | เริ่มต้นใช้งาน
Hardware Setup:
เชื่อมต่อ CT Sensor เข้ากับบอร์ด ESP32/ESP8266

ทำการ Calibration เพื่อความแม่นยำของค่ากระแส

Software Setup:
Clone this repository:

bash
คัดลอก
แก้ไข
git clone https://github.com/IceEz555/Project_Final_IoT.git
เปิดโค้ดใน Arduino IDE หรือ VS Code PlatformIO

แก้ไขค่า WiFi และ AWS Credentials ในไฟล์ config.h

Upload โค้ดเข้าสู่บอร์ด

Cloud & Dashboard:
ตั้งค่า AWS IoT Core สำหรับรับข้อมูลจากอุปกรณ์

สร้าง Lambda Function หรือใช้ AWS API Gateway สำหรับดึงข้อมูล

สร้าง Web Dashboard (HTML/CSS/JS) เพื่อแสดงผล

📊 Example Output | ตัวอย่างการแสดงผล
(คุณสามารถใส่ภาพ screenshot หรือกราฟการแสดงผลไว้ตรงนี้ได้)

🙋‍♂️ Authors | ผู้จัดทำ
Apivit Yingyaithanasak and Rapeepon Kampha (GitHub: IceEz555)
