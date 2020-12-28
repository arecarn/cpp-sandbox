FROM ubuntu:18.04


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
        python3 \
        python3-pip \
        tar \
        unzip \
        libsfml-dev \
        python3.8

RUN apt install -y \
    x11-apps \
    gosu


RUN python3.8 -m pip install \
        cmake \
        gersemi

COPY entrypoint.sh /usr/local/bin/entrypoint.sh
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
CMD ["/bin/bash"]
