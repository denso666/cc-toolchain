from debian:10

RUN apt-get update
RUN apt-get install -y build-essential gcc-arm-linux-gnueabihf

WORKDIR /src

ENTRYPOINT make
