import paho.mqtt.client as mqtt
import mysql.connector
from dotenv import load_dotenv
import os

load_dotenv()

AIO_USERNAME = os.getenv("AIO_USERNAME")
AIO_KEY = os.getenv("AIO_KEY")

BROKER = "io.adafruit.com"
PORT = 8883  

TOPIC_TEMP = f"{AIO_USERNAME}/feeds/temperature"
TOPIC_HUM = f"{AIO_USERNAME}/feeds/humidity"

db = mysql.connector.connect(
    host=os.getenv("MYSQL_HOST"),
    user=os.getenv("MYSQL_USER"),
    password=os.getenv("MYSQL_PASSWORD"),
    database=os.getenv("MYSQL_DB")
)

cursor = db.cursor()

latest_temp = None
latest_hum = None


def save_to_db(temp, hum):
    sql = "INSERT INTO measurements (temperature, humidity) VALUES (%s, %s)"
    cursor.execute(sql, (temp, hum))
    db.commit()
    print("Saved to DB:", temp, hum)


def on_connect(client, userdata, flags, rc):
    print("Connected with result code:", rc)
    client.subscribe([(TOPIC_TEMP, 0), (TOPIC_HUM, 0)])

def on_message(client, userdata, msg):
    global latest_temp, latest_hum

    value = float(msg.payload.decode())

    if msg.topic == TOPIC_TEMP:
        latest_temp = value
        print("Temperature:", value)

    elif msg.topic == TOPIC_HUM:
        latest_hum = value
        print("Humidity:", value)

    if latest_temp is not None and latest_hum is not None:
        save_to_db(latest_temp, latest_hum)
        latest_temp = None
        latest_hum = None


client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION1)
client.username_pw_set(AIO_USERNAME, AIO_KEY)

client.tls_set()

client.on_connect = on_connect
client.on_message = on_message

client.connect(BROKER, PORT, 60)
client.loop_forever()