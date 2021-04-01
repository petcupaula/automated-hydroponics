import paho.mqtt.client as mqtt
import json
import time
import logging
import sys
import traceback
import ssl
import datetime
import serial

url = "178.128.42.0"
ca = "certificate-collection/ca/ca.pem"
cert = "certificate-collection/certificates/paulas_client.pem"
private = "certificate-collection/certificates/paulas_client.key"
logger = logging.getLogger()
logger.setLevel(logging.DEBUG)
handler = logging.StreamHandler(sys.stdout)
log_format = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
handler.setFormatter(log_format)
logger.addHandler(handler)

def ssl_alpn():
    try:
        #debug print opnessl version
        logger.info("open ssl version:{}".format(ssl.OPENSSL_VERSION))
        ssl_context = ssl.create_default_context()
        ssl_context.load_verify_locations(cafile=ca)
        ssl_context.load_cert_chain(certfile=cert, keyfile=private)
        return  ssl_context
    except Exception as e:
        print("exception ssl_alpn()")
        raise e

if __name__ == '__main__':
    topic = "paula/hydroponics"

    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.flush()

    try:
        mqttc = mqtt.Client()
        ssl_context = ssl_alpn()
        mqttc.tls_set_context(context=ssl_context)
        logger.info("start connect")
        mqttc.tls_insecure_set(True)
        mqttc.connect("178.128.42.0", 8883, 60)
        logger.info("connect success")
        mqttc.loop_start()
        while True:
            ser.write(b"READ\n")
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
            if (line != ""):
                datadict = eval(line)
                now = datetime.datetime.utcnow().strftime('%Y-%m-%dT%H:%M:%S')
                logger.info("try to publish:{}".format(now))
                datadict['time'] = now
                print(datadict)
                mqttc.publish(topic, json.dumps(datadict))
            time.sleep(5)

    except Exception as e:
        logger.error("exception main()")
        logger.error("e obj:{}".format(vars(e)))
        logger.error("message:{}".format(e.message))
        traceback.print_exc(file=sys.stdout)
