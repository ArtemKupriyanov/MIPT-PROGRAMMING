FROM python:3

ADD requirements.txt requirements.txt
RUN pip install --upgrade pip
RUN pip install -r requirements.txt

ADD consumer.py consumer.py

CMD [ "python", "consumer.py" ]