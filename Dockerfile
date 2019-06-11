FROM ubuntu:xenial

# Instalar ferramentas básicas
RUN apt-get update \ 
    && apt-get -y --no-install-recommends install wget unzip software-properties-common
# Instalar ferramentas para desenvolvimento C/C++
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test && apt-get update
RUN apt-get install -y dpkg-dev libc-dev make gdb valgrind lcov cmake clang-format clang-tidy gcc-8 g++-8
ENV CC=gcc-8 CXX=g++-8

# Instalar dependências do projeto
RUN apt-get -y --no-install-recommends install \
    libfreetype6-dev \ 
    libjpeg-dev \ 
    libx11-dev \ 
    libxrandr-dev \ 
    libx11-xcb-dev \ 
    libxcb-randr0-dev \ 
    libxcb-image0-dev \ 
    libxcb1-dev \ 
    libgl1-mesa-dev \ 
    libudev-dev \ 
    libopenal-dev \ 
    libflac-dev \ 
    libvorbis-dev

# Compila bibliotecas
WORKDIR /tmp/lib
RUN wget --no-check-certificate https://www.sfml-dev.org/files/SFML-2.5.1-sources.zip \
    && unzip SFML-2.5.1-sources.zip \
    && cd SFML-2.5.1 \
    && cmake -DCMAKE_BUILD_TYPE=Release -DSFML_BUILD_EXAMPLES=FALSE -DSFML_BUILD_DOC=FALSE \
    && make \
    && make install \
    && ldconfig
RUN wget --no-check-certificate https://github.com/texus/TGUI/archive/v0.8.5.zip \
    && unzip v0.8.5.zip \
    && cd TGUI-0.8.5 \
    && cmake -DCMAKE_BUILD_TYPE=Release -DTGUI_BUILD_GUI_BUILDER=FALSE \
    && make \
    && make install \
    && ldconfig

WORKDIR /

# Clean up
RUN rm -rf /tmp/lib \
    && apt-get clean -y \
    && apt-get autoremove -y
