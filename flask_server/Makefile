#!/bin/bash

# RFID Access Control System Setup Script
# This script sets up the Python Flask server environment

echo "🔐 RFID Access Control System Setup"
echo "=================================="

# Check if Python3 is installed
if ! command -v python3 &> /dev/null; then
    echo "❌ Python3 is not installed. Please install Python3 first."
    exit 1
fi

# Check if pip3 is installed
if ! command -v pip3 &> /dev/null; then
    echo "❌ pip3 is not installed. Please install pip3 first."
    exit 1
fi

echo "✅ Python3 and pip3 are available"

# Create virtual environment if it doesn't exist
if [ ! -d "venv" ]; then
    echo "🔨 Creating virtual environment..."
    python3 -m venv venv
else
    echo "✅ Virtual environment already exists"
fi

# Activate virtual environment
echo "🚀 Activating virtual environment..."
source venv/bin/activate

# Upgrade pip
echo "📦 Upgrading pip..."
pip install --upgrade pip

# Install requirements
echo "📋 Installing Python packages..."
if [ -f "requirements.txt" ]; then
    pip install -r requirements.txt
    echo "✅ Python packages installed successfully"
else
    echo "❌ requirements.txt not found!"
    exit 1
fi

# Create necessary directories
echo "📁 Creating project directories..."
mkdir -p flask_server/templates
mkdir -p flask_server/static
mkdir -p logs

# Set permissions
echo "🔐 Setting permissions..."
chmod +x flask_server/app.py

echo ""
echo "🎉 Setup completed successfully!"
echo ""
echo "Next steps:"
echo "1. Configure your WiFi credentials in the ESP8266 code"
echo "2. Upload Arduino codes to your hardware"
echo "3. Update RFID card IDs in both Arduino and Python code"
echo "4. Start the Flask server:"
echo "   source venv/bin/activate"
echo "   python flask_server/app.py"
echo ""
echo "Optional Node.js setup:"
echo "1. cd node_server"
echo "2. npm install"
echo "3. npm start"
echo ""
echo "🔗 Server will be available at: http://localhost:5000"
echo "🌐 Web UI will be available at: http://localhost:5000/ui_control/"
echo ""

# Create a simple HTML template if it doesn't exist
if [ ! -f "flask_server/templates/index.html" ]; then
    echo "📄 Creating basic HTML template..."
    cat > flask_server/templates/index.html << 'EOF'
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>RFID Access Control</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 600px;
            margin: 50px auto;
            padding: 20px;
            background-color: #f5f5f5;
        }
        .container {
            background: white;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
            text-align: center;
        }
        h1 {
            color: #333;
            margin-bottom: 30px;
        }
        .button {
            display: inline-block;
            padding: 15px 30px;
            margin: 10px;
            background-color: #00A8A9;
            color: white;
            text-decoration: none;
            border-radius: 25px;
            font-size: 18px;
            border: none;
            cursor: pointer;
            transition: background-color 0.3s;
        }
        .button:hover {
            background-color: #008888;
        }
        .status {
            margin: 20px 0;
            padding: 15px;
            border-radius: 5px;
            font-weight: bold;
        }
        .success { background-color: #d4edda; color: #155724; }
        .error { background-color: #f8d7da; color: #721c24; }
    </style>
</head>
<body>
    <div class="container">
        <h1>🔐 RFID Access Control System</h1>
        <p>Welcome to the RFID Access Control Web Interface</p>
        
        <div>
            <a href="/door_action/?command=open_door" class="button">🚪 Open Door</a>
        </div>
        
        <div style="margin-top: 30px;">
            <h3>System Status</h3>
            <div class="status success">
                ✅ System Online
            </div>
        </div>
        
        <div style="margin-top: 30px; font-size: 14px; color: #666;">
            <p>Hardware: Arduino + ESP8266 + MFRC522</p>
            <p>Server: Python Flask</p>
        </div>
    </div>
    
    <script>
        // Auto-refresh status every 30 seconds
        setInterval(function() {
            // You can add AJAX calls here to check system status
        }, 30000);
    </script>
</body>
</html>
EOF
    echo "✅ Basic HTML template created"
fi

echo "🔧 Setup script completed!"