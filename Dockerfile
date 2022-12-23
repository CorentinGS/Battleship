FROM gcc:latest

COPY . /usr/src/myapp

WORKDIR /usr/src/myapp

RUN NOVISU=1 make re

CMD ["./Battleship"]
