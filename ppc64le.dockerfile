FROM gcc:4.9.4

ENV DEBIAN_FRONTEND=noninteractive

RUN wget --no-check-certificate https://github.com/Kitware/CMake/archive/refs/tags/v3.1.3.tar.gz

RUN tar -xf v3.1.3.tar.gz

RUN cd CMake-3.1.3 \
 && ./bootstrap --parallel=$(nproc) \
 && make -j $(nproc) \
 && make install
