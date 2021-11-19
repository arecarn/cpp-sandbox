FROM ubuntu:20.04

RUN echo "Updating Ubuntu"
RUN apt-get update --fix-missing && \
        apt-get upgrade -y && \
        apt-get install -y software-properties-common && \
        apt-get update --fix-missing && \
        apt-add-repository ppa:git-core/ppa && \
        apt-get update --fix-missing

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
        python \
        python3-pip \
        tar \
        unzip \
        libsfml-dev

RUN apt install -y \
    x11-apps \
    gosu


RUN python -m pip install \
        cmake \
        gersemi
