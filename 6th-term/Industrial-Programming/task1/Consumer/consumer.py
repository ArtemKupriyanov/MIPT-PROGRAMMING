import pika
import psycopg2 as ps

connection_to_db = ps.connect(database='mydb', user='login', password='pass', host='database')
cursor.execute("CREATE TABLE Task1(TEXT varchar(800))")
connection.commit()
cursor.close()

def callback(ch, method, properties, body):
    text_from_queue = (body.decode())
    cursor = connection_to_db.cursor()
    line = "INSERT INTO Task1 VALUES('" + text_from_queue + "')"
    cursor.execute(line)
    connection.commit()
    cursor.close()

connection = pika.BlockingConnection(pika.URLParameters("amqp://guest:guest@queue:5672"))
channel = connection.channel()
channel.queue_declare(queue='hello')
channel.basic_consume(callback, queue='hello', no_ack=True)
while True:
    channel.start_consuming()
