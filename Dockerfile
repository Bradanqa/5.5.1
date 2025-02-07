FROM ubuntu:jammy

RUN apt-get update && \
    apt-get install -y g++ cmake make

WORKDIR /app

COPY . .

RUN mkdir build \
    && cd build \
    && cmake .. \
    && cmake --build .

CMD ["./build/app"]