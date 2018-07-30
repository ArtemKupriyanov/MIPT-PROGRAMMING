import sys
import pika

connection = pika.BlockingConnection(pika.URLParameters("amqp://guest:guest@localhost:5672"))

channel = connection.channel()
channel.queue_declare(queue='hello')

while True:
    data = sys.stdin.readline()
    channel.basic_publish(exchange='', routing_key='hello', body=data.encode())
