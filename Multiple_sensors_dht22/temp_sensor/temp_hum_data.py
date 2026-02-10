import serial
import time
import sqlite3
from datetime import datetime

# === Serial Setup ===
ser = serial.Serial('COM4', 9600)
time.sleep(2)  # give Arduino time to reset

# === Database Setup ===
conn = sqlite3.connect('arduino_data.db')
cursor = conn.cursor()

cursor.execute("DROP TABLE IF EXISTS sensor_data;")

# Create a table if it doesn’t exist yet
cursor.execute('''
CREATE TABLE sensor_data (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    timestamp TEXT,
    h1 REAL,
    t1 REAL,
    h2 REAL,
    t2 REAL
)
''')
conn.commit()

# === Continuous Read + Log ===
print("Logging data from Arduino... Press Ctrl+C to stop.")
try:
    while True:
        line = ser.readline().decode('utf-8', errors='ignore').strip()
        if not line:
            continue

        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        print(f"{timestamp} | {line}")

        # Parse sample format: H1: 55.3  H2: 49.8  T2: 55.0 *F
        try:
            parts = line.replace("*F", "").replace(":", "").split()
            h1 = float(parts[1])
            t1 = float(parts[3])
            h2 = float(parts[5])
            t2 = float(parts[7])
        except Exception:
            h1 = t1 = h2 = t2 = None  # if parse fails, skip values

        cursor.execute(
            "INSERT INTO sensor_data (timestamp, h1, t1, h2, t2) VALUES (?, ?, ?, ?, ?)",
            (timestamp, h1, t1, h2, t2)
        )
        conn.commit()

except KeyboardInterrupt:
    print("\nStopped logging.")
    ser.close()
    conn.close()
