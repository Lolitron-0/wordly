FROM niten01/arch-cpp:latest

WORKDIR /app

COPY . .

RUN ./dev.sh

CMD ./dev.sh run
