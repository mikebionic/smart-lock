# RFID Access Control System 🔐

<div align="center">

![Arduino](https://upload.wikimedia.org/wikipedia/commons/8/87/Arduino_Logo.svg)
![Python](https://upload.wikimedia.org/wikipedia/commons/3/31/Python-logo.png)
![NodeJS](https://upload.wikimedia.org/wikipedia/commons/6/67/NodeJS.png)

</div>

A DIY RFID-based access control system for office/building security. This university project eliminates the need for physical keys by using RFID cards for employee access, providing enhanced security and access logging.

## ✨ Features

- **RFID Card Authentication**: Secure access using registered RFID cards
- **Web Interface**: Manual door control and key validation via web UI
- **Real-time Logging**: Track all access attempts and successful entries
- **Multiple Control Methods**: 
  - RFID card scanning
  - Physical button override
  - Web-based remote control
  - Manual key input validation
- **Database Integration**: Employee and access logging with PostgreSQL/MSSQL support
- **WiFi Connectivity**: ESP8266-based wireless communication
- **Automobile Lock Integration**: Uses automobile lock drivers for door mechanism

## 🏗️ System Architecture

The system consists of three main components:

1. **Arduino RFID Scanner**: Hardware interface for card reading and door control
2. **ESP8266 WiFi Module**: Wireless communication bridge
3. **Python Flask Server**: Main control server and web interface
4. **Node.js Backend** (Optional): Database management and API services

## 📋 Hardware Requirements

### Components Needed:
- **Arduino Uno/Nano** - Main microcontroller
- **ESP8266 WiFi Module** - Wireless communication
- **MFRC522 RFID Reader** - Card scanning module
- **RFID Cards/Tags** - Employee access cards
- **Automobile Lock Driver** - Door locking mechanism
- **LED Indicator** - Visual feedback
- **Push Button** - Manual override
- **Breadboard & Jumper Wires** - Connections
- **12V Power Supply** - For lock driver

### Alternative Lock Mechanisms:
- Magnetic door holder
- Servo-controlled locks
- Electric strike plate

![Example2](https://makeradvisor.com/wp-content/uploads/2017/12/dec-6-1024x576.jpg)

## 🔌 Hardware Connection Diagram

```
Arduino Uno Connections:
┌─────────────────┐
│     Arduino     │
│                 │
│  D2  ←→ LED     │
│  D7  ←→ Button  │
│  D9  ←→ RST     │ ←→ MFRC522
│  D10 ←→ SS      │ ←→ MFRC522
│  D11 ←→ MOSI    │ ←→ MFRC522
│  D12 ←→ MISO    │ ←→ MFRC522
│  D13 ←→ SCK     │ ←→ MFRC522
│                 │
│  3.3V ←→ VCC    │ ←→ MFRC522
│  GND  ←→ GND    │ ←→ MFRC522
│                 │
│  TX   ←→ RX     │ ←→ ESP8266
│  RX   ←→ TX     │ ←→ ESP8266
└─────────────────┘

ESP8266 Network Configuration:
- Static IP: 192.168.1.145
- Gateway: 192.168.1.1
- Server: 192.168.1.100:5000
```

![Example](https://upload.wikimedia.org/wikipedia/commons/4/46/WELOCK_smart_door_lock_touca51.png)


## 🚀 Quick Start

### 1. Hardware Setup
1. Connect components according to the wiring diagram above
2. Upload the Arduino code to your Arduino board
3. Configure ESP8266 with your WiFi credentials
4. Connect automobile lock driver to door mechanism

### 2. Software Installation

#### Python Flask Server Setup:
```bash
# Clone the repository
git clone <your-repo-url>
cd rfid-access-system

# Run setup script
chmod +x setup.sh
./setup.sh

# Or manual installation:
pip install -r requirements.txt

# Run the Flask server
python flask_server/app.py
```

#### Node.js Backend Setup (Optional):
```bash
cd node_server
npm install
npm start
```

### 3. Configuration

#### Update WiFi Credentials in ESP8266 code:
```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

#### Register RFID Cards in Arduino code:
```cpp
String registeredCards[] = {
  "46:0C:C8:0A",
  "46:0C:C8:0F", // Employee Name
  "YOUR_CARD_ID"
};
```

#### Update Flask server configuration:
```python
cards = {
"46:0C:C8:0F": "gulbahar",
"26:B8:3C:1E": "mike",
"YOUR_CARD_ID": "employee_name",
}
```

## 📁 Project Structure

```
rfid-access-system/
├── arduino_codes/
│   ├── esp8266_rfid.ino       # ESP8266 WiFi module code
│   ├── esp8266_web.ino        # ESP8266 with web interface
│   └── rfid_scanner.ino       # Arduino RFID scanner code
├── flask_server/
│   ├── app.py                 # Main Flask application
│   └── templates/
│       └── index.html         # Web control interface
├── node_server/
│   ├── src/
│   │   ├── constants.js       # Database configuration
│   │   ├── sequelize.js       # Database connection
│   │   └── models/            # Database models
│   └── package.json
├── requirements.txt           # Python dependencies
├── setup.sh                  # Installation script
└── README.md
```

## 🌐 API Endpoints

### Flask Server (Port 5000):
- `GET /` - Server status
- `GET /esp/door/` - ESP8266 communication endpoint
- `GET /door_action/` - Remote door control
- `GET /ui_control/` - Web control interface

### Node.js Server (Port 3000):
- `GET /api/resources/` - Get all resources
- `GET /api/attendances/` - Get attendance records
- `POST /api/resource` - Add new resource

## 🔧 Configuration Options

### Database Support:
- **PostgreSQL** (default)
- **Microsoft SQL Server**

Update `node_server/src/constants.js` to switch database types.

### Security Settings:
- Device authentication key: `rfid_secret`
- Web validation key: configurable in ESP8266 code
- Network isolation: Static IP configuration

## 🛠️ Troubleshooting

### Common Issues:

1. **RFID not reading**: Check wiring connections and power supply
2. **WiFi connection failed**: Verify credentials and network connectivity
3. **Door not opening**: Check lock driver connections and power supply
4. **Server not responding**: Ensure Flask server is running and accessible

### Debug Mode:
- Monitor Arduino Serial output (9600 baud)
- Check Flask server logs
- Verify ESP8266 connection status

## 📊 Access Logging

The system logs all access attempts including:
- Timestamp of access
- RFID card ID used
- Employee name
- Access result (granted/denied)

Access the attendance records via the Node.js API or database directly.

## 🔒 Security Features

- **Authentication**: Multi-layer security with device keys and RFID validation
- **Access Control**: Only registered cards can open doors
- **Audit Trail**: Complete logging of all access attempts
- **Network Security**: Static IP configuration and device authentication
- **Physical Override**: Manual button for emergency access

## 🚧 Future Enhancements

- [ ] Mobile app integration
- [ ] Face recognition backup
- [ ] Real-time notifications
- [ ] Advanced reporting dashboard
- [ ] Multiple door support
- [ ] Time-based access restrictions
- [ ] Integration with existing security systems

> This is a university project for educational purposes. Feel free to modify and improve upon the design.

## 🤝 Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request


**⚠️ Safety Notice**: This system controls physical access to buildings. Ensure proper testing and backup access methods before deployment in production environments.