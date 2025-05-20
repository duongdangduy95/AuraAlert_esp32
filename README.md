# AuraAlert ESP32

**AuraAlert ESP32** là một hệ thống cảnh báo xâm nhập thông minh, sử dụng **ESP32**, **cảm biến chuyển động PIR**, và **module phát âm ISD1820**. Dự án này được thiết kế để phát hiện người đến gần và:

- Phát cảnh báo âm thanh bằng giọng nói đã ghi sẵn
- Gửi thông báo cảnh báo thời gian thực đến ứng dụng điện thoại thông qua **MQTT qua TLS (HiveMQ Cloud)**

## Giới thiệu

Mục tiêu của dự án là xây dựng một hệ thống bảo mật đơn giản nhưng hiệu quả, có khả năng:

- Phát hiện chuyển động bằng cảm biến PIR
- Phát lời cảnh báo qua module ISD1820 khi có người tiếp cận
- Gửi thông báo ngay lập tức đến ứng dụng di động thông qua kết nối MQTT bảo mật
- Kết nối Wi-Fi và hoạt động ổn định với máy chủ đám mây

Dự án tận dụng khả năng kết nối không dây của ESP32 kết hợp với cảnh báo âm thanh cục bộ và thông báo từ xa để tạo ra một giải pháp an ninh tiện lợi, phù hợp cho nhà ở thông minh hoặc văn phòng nhỏ.

Repository này chứa mã nguồn Arduino cho ESP32, bao gồm:

- Cấu hình Wi-Fi
- Kết nối MQTT TLS đến HiveMQ Cloud
- Xử lý sự kiện từ cảm biến PIR
- Kích hoạt phát âm thanh từ ISD1820
## Phần cứng cần thiết

Dưới đây là danh sách các linh kiện cần thiết để xây dựng hệ thống cảnh báo AuraAlert ESP32:

### 1. ESP32 Dev Module

- **Mô tả**: ESP32 là vi điều khiển mạnh mẽ có tích hợp Wi-Fi và Bluetooth, rất phù hợp cho các ứng dụng IoT.
- **Vai trò**: Là bộ não chính điều khiển hệ thống, xử lý dữ liệu từ cảm biến và gửi cảnh báo qua MQTT.

### 2. Cảm biến chuyển động PIR (Passive Infrared)

- **Mô tả**: Cảm biến PIR phát hiện chuyển động của người hoặc vật thể thông qua sự thay đổi bức xạ hồng ngoại.
- **Đặc điểm**: điện áp hoạt động DC 3.8V – 5V, Phạm vi phát hiện: góc 360 độ hình nón, độ xa tối đa 6m.
- **Vai trò**: Dùng để phát hiện khi có người lại gần khu vực giám sát.
- **Lưu ý**: Nên điều chỉnh độ nhạy và thời gian giữ tín hiệu sao cho phù hợp với môi trường sử dụng.

### 3. Module phát âm thanh ISD1820

- **Mô tả**: ISD1820 là module ghi và phát lại âm thanh ngắn (3-5 giây), dễ sử dụng với micro tích hợp và loa nhỏ.
- **Vai trò**: Phát lời cảnh báo (ví dụ: “Vui lòng không tiến lại gần!”) khi có người bị phát hiện.
- **Lưu ý**: Có thể ghi âm trực tiếp bằng micro trên module hoặc sử dụng chân điều khiển để phát từ vi điều khiển.

### 4. Dây nối (jumper wires)

- **Mô tả**: Dây nối loại đực - cái hoặc cái - cái dùng để kết nối các linh kiện trên breadboard hoặc trực tiếp với ESP32.
- **Vai trò**: Kết nối tín hiệu và cấp nguồn giữa ESP32, PIR và ISD1820.
- **Lưu ý**: Nên dùng dây chất lượng tốt để đảm bảo tín hiệu ổn định.

---

> Tổng cộng chi phí phần cứng khá thấp, phù hợp cho các dự án DIY (tự làm) hoặc thử nghiệm hệ thống an ninh thông minh.
## Sơ đồ nối dây

Dưới đây là bảng kết nối các linh kiện chính của hệ thống AuraAlert ESP32:

| Thiết bị          | Chân tín hiệu     | ESP32 GPIO      | Ghi chú                                      |
|-------------------|-------------------|------------------|----------------------------------------------|
| **Cảm biến PIR**  | VCC               | 3.3V hoặc 5V     | Tùy loại PIR, hầu hết hoạt động ở 3.3V       |
|                   | GND               | GND              | Phải nối chung GND với ESP32                 |
|                   | OUT               | GPIO19 (D19)     | Tín hiệu kích hoạt khi phát hiện chuyển động |
| **ISD1820**       | VCC               | 5V               | Giúp module phát âm thanh to và rõ           |
|                   | GND               | GND              | Chung GND với ESP32                          |
|                   | P-E               | GPIO18 (D18)     | Điều khiển phát âm khi có chuyển động        |

---

> 💡 **Lưu ý:**
> - Đảm bảo tất cả các thiết bị chia sẻ **GND chung** để tín hiệu hoạt động ổn định.
> - Cần ghi âm lời cảnh báo vào ISD1820 trước khi sử dụng. ESP32 chỉ gửi xung để phát lại.
> - PIR nên được đặt ở vị trí thoáng, tránh ánh nắng trực tiếp hoặc nguồn nhiệt.

---

### 🖼️ Hình minh họa (nếu có):


## Arduino IDE là gì?

[**Arduino IDE**](https://www.arduino.cc/en/software) (Integrated Development Environment) là một phần mềm miễn phí, mã nguồn mở dùng để lập trình các vi điều khiển như Arduino Uno, ESP8266, ESP32,... với ngôn ngữ lập trình tương tự C/C++.

Đối với dự án **AuraAlert ESP32**, Arduino IDE là công cụ chính để:
- Viết và chỉnh sửa mã nguồn điều khiển ESP32
- Nạp (upload) chương trình vào board ESP32 qua cổng USB
- Theo dõi hoạt động của ESP32 qua Serial Monitor

---

## Hướng dẫn cài đặt Arduino IDE và ESP32

### 🔧 Bước 1: Tải và cài đặt Arduino IDE

- Truy cập trang chính thức: [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)
- Tải về phiên bản phù hợp với hệ điều hành của bạn (Windows, macOS, Linux)
- Tiến hành cài đặt như phần mềm thông thường

---

### 🔌 Bước 2: Cài đặt board ESP32 trong Arduino IDE

1. Mở Arduino IDE, vào menu **File > Preferences**
2. Tìm mục **Additional Board Manager URLs** và thêm đường dẫn sau:https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

3. Nhấn **OK**, sau đó vào **Tools > Board > Boards Manager**
4. Tìm từ khóa `esp32`, chọn **ESP32 by Espressif Systems** và nhấn **Install**

> Sau khi cài đặt xong, bạn sẽ thấy nhiều loại board ESP32 trong menu **Tools > Board**

---

### 📌 Bước 3: Kết nối ESP32 với máy tính

- Dùng cáp USB để kết nối board ESP32 với máy tính.
- Vào **Tools > Port** để chọn đúng cổng COM tương ứng (thường sẽ hiển thị là "Silicon Labs" hoặc "USB to UART").

### 📦 Cài thư viện từ Arduino IDE

1. Mở **Arduino IDE**
2. Vào menu: `Sketch > Include Library > Manage Libraries`
3. Tìm và cài đặt lần lượt các thư viện sau:

| **Thư viện**           | **Ghi chú**                                      |
|------------------------|--------------------------------------------------|
| `WiFi`                 | Có sẵn khi cài **ESP32 core**                   |
| `WiFiClientSecure`     | Có sẵn khi cài **ESP32 core**                   |
| `WebServer`            | Có sẵn khi cài **ESP32 core**                   |
| `Preferences`          | Có sẵn khi cài **ESP32 core**                   |
| `PubSubClient`         | Cần tìm và cài đặt qua **Library Manager**       |
| `time` *(hoặc `time.h`)* | Có sẵn khi cài **ESP32 core**                   |

> 🔍 **Lưu ý:** Các thư viện `WiFi`, `WebServer`, `Preferences`, `WiFiClientSecure`, `time.h` sẽ được cài **tự động** khi bạn cài đặt `ESP32 by Espressif Systems` trong **Boards Manager**.

## ☁️ Hướng dẫn đăng ký và cấu hình máy chủ MQTT trên HiveMQ Cloud

Để sử dụng giao tiếp MQTT giữa **ESP32** và ứng dụng, bạn cần có một máy chủ MQTT. HiveMQ Cloud là một lựa chọn miễn phí, dễ sử dụng và hỗ trợ giao thức bảo mật (TLS/SSL).

### 🔐 Bước 1: Đăng ký tài khoản HiveMQ Cloud

1. Truy cập: [https://www.hivemq.com/cloud/](https://www.hivemq.com/cloud/)
2. Nhấn **Get Started For Free**
3. Tạo tài khoản bằng email và mật khẩu của bạn
4. Xác nhận email để hoàn tất đăng ký

---

### ⚙️ Bước 2: Tạo instance MQTT

1. Sau khi đăng nhập, vào mục **Clusters**
2. Nhấn **Create New Cluster**
3. Đặt tên (ví dụ: `AuraAlertCluster`)
4. Chọn vùng **Europe (eu-central)** hoặc theo mặc định
5. Nhấn **Create Cluster**

> ⏳ Sau vài phút, HiveMQ sẽ tạo xong instance.

---

###  Bước 3: Tạo tài khoản đăng nhập MQTT

1. Chọn cluster bạn vừa tạo → sang tab **Access Management**
2. Chọn **Add New Credentials**
3. Tạo một tài khoản MQTT:
   - **Username**: tuỳ chọn (ví dụ: `esp32_user`)
   - **Password**: tuỳ chọn và bảo mật

---

###  Bước 4: Lấy thông tin kết nối

Vào tab **Overview**, bạn sẽ thấy thông tin sau:

| Thông tin       | Ví dụ                                                |
|------------------|--------------------------------------------------------|
| **Host**         | `xxxxxx.s1.eu.hivemq.cloud` (dùng trong `mqtt_server`) |
| **Port TLS**     | `8883`                                                 |
| **Port WS (WebSocket TLS)** | `8884`                                     |
| **Username**     | Tên đăng nhập bạn đã tạo                              |
| **Password**     | Mật khẩu đã thiết lập                                 |

---

###  Bước 5: Cấu hình trong mã nguồn ESP32

```cpp
const char* mqtt_server = "xxxxxx.s1.eu.hivemq.cloud";
const int mqtt_port = 8883; // sử dụng kết nối TLS
const char* mqtt_user = "esp32_user";
const char* mqtt_password = "your_secure_password";
```
### 🛡️ Công dụng của chứng chỉ CA trong kết nối MQTT bảo mật

Khi ESP32 kết nối tới HiveMQ Cloud qua cổng **8883 (TLS/SSL)**, máy chủ sẽ gửi về một **chứng chỉ số** để xác minh danh tính. Để ESP32 có thể **tin tưởng** máy chủ HiveMQ Cloud là hợp lệ và an toàn, ta cần cung cấp cho ESP32 **chứng chỉ CA** tương ứng.

#### 🔒 Vì sao cần chứng chỉ CA?
- Giúp **xác thực máy chủ** HiveMQ Cloud có thực sự hợp lệ không (phòng chống giả mạo).
- Đảm bảo dữ liệu MQTT gửi/nhận giữa ESP32 và HiveMQ **được mã hóa an toàn** qua SSL/TLS.
- Bảo vệ thiết bị IoT của bạn khỏi các cuộc tấn công man-in-the-middle (MITM).

#### 📌 Cách dùng
- Chèn nội dung chứng chỉ CA vào trong mã ESP32 dưới dạng chuỗi `const char*`
- Cấu hình `WiFiClientSecure` sử dụng CA như sau:
####Bạn có thể tải chứng chỉ CA (dạng PEM) từ liên kết chính thức dưới đây:

[Tải certificate.pem tại đây](https://www.hivemq.com/docs/hivemq-cloud/certificate.pem)

### 





