# Build stage
FROM debian:trixie-slim
ARG BUILD_DIRECTORY=/home/user/src

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libasio-dev \
    meson \
    libcurlpp-dev \
    libpsl-dev \
    libgrpc++-dev && rm -rf /var/lib/apt/lists/*
RUN mkdir -p $BUILD_DIRECTORY
WORKDIR $BUILD_DIRECTORY

# run these in container
#RUN make --install .

#WORKDIR /opt
ENV LD_LIBRARY_PATH=/opt/lib:$LD_LIBRARY_PATH
CMD ["/opt/todoui-cpp"]

# debug
#CMD ["/usr/bin/bash"]
