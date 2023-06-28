FROM ghcr.io/rikorose/gcc-cmake:latest

COPY . /usr/src/big2
WORKDIR /usr/src/big2

RUN mkdir build_big2 && cd build_big2 && cmake .. && make

WORKDIR /usr/src/big2/build_big2
CMD ["./DEMO_PROGRAM"]

# docker build . -t big2_docker
# docker run -it --rm --name big2_docker big2_docker