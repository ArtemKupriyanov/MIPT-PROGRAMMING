FROM python:3
ENV PYTHONUNBUFFERED 1
RUN mkdir /code/django & mkdir /code/react & mkdir /npm
WORKDIR /npm
RUN curl -sL https://deb.nodesource.com/setup_9.x | bash -
RUN apt-get install -y nodejs
RUN npm install create-react-app react react-scripts mini-signals
WORKDIR /code
ADD requirements.txt /code/
RUN pip install -r requirements.txt
EXPOSE 8000:8000
EXPOSE 3000:3000
ENTRYPOINT bash init.sh