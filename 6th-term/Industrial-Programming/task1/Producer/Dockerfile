FROM python:3

ADD requirements.txt requirements.txt
RUN pip install --upgrade pip
RUN pip install -r requirements.txt

ADD producer.py producer.py

CMD [ "python", "producer.py" ]