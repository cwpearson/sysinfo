FROM gcc:4.9.4

ENV DEBIAN_FRONTEND=noninteractive

RUN wget --no-check-certificate https://github.com/Kitware/CMake/archive/refs/tags/v3.5.2.tar.gz

RUN tar -xf v3.5.2.tar.gz

RUN cd CMake-3.5.2 \
 && ./bootstrap --parallel=$(nproc) \
 && make -j $(nproc) \
 && make install
