FROM ghcr.io/rikorose/gcc-cmake:latest

COPY . /usr/src/big2
WORKDIR /usr/src/big2

RUN mkdir build_big2 && cd build_big2 && cmake .. && make

WORKDIR /usr/src/big2/build_big2
CMD ["./DEMO_PROGRAM"]

