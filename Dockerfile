FROM ubuntu:latest

ENV TZ=Europe/Kiev
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && \
    apt-get -y install gcc \
        g++ \
        git \
        build-essential \
        gdb \
        cmake \
        bash \
        curl \
        libz-dev \
        libcurl4-openssl-dev \
        sudo \
        cppcheck \
        googletest

WORKDIR /home/html2pdf/
