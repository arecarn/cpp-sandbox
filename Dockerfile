FROM ubuntu:18.04

RUN echo "Updating Ubuntu"
RUN apt-get update && apt-get upgrade -y

RUN echo "Installing dependencies..."
RUN apt install -y \
            ccache \
            clang \
            clang-format \
            clang-tidy \
            cppcheck \
            curl \
            doxygen \
            gcc \
            git \
            graphviz \
            make \
            ninja-build \
            python3 \
            python3-pip \
            tar \
            unzip\
            libsfml-dev

RUN pip3 install cmake


WORKDIR /home/app
ENTRYPOINT /bin/bash
