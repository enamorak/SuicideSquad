FROM ubuntu:20.04

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && \
    apt-get install -y gnupg && \
    apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 3B4FE6ACC0B21F32 && \
    apt-get update

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y software-properties-common && \
    add-apt-repository ppa:beineri/opt-qt-5.15.2-focal -y && \
    apt-get update && \
    apt-get install -y qt5-default

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y qt5-default \
                        qtbase5-dev \
                        qtdeclarative5-dev \
                        qtmultimedia5-dev \
                        libqt5serialport5-dev \
                        libqt5sql5-mysql \
                        libqt5sql5-psql \
                        libqt5sql5-sqlite \
                        libqt5sql5-odbc \
                        libqt5sql5-tds \
                        build-essential \
                        cmake \
                        git

RUN git clone https://github.com/qt/qtbase.git && \
    cd qtbase && \
    git checkout 5.15 && \
    ./configure -opensource -confirm-license -no-gui -no-widgets -no-opengl -no-openssl -no-sql-mysql -no-sql-psql -no-sql-sqlite -no-sql-odbc -no-sql-tds -nomake examples -nomake tests && \
    make -j$(nproc) && \
    make install && \
    cd .. && \
    rm -rf qtbase

WORKDIR /root/
RUN mkdir server
WORKDIR /root/server/
COPY *.cpp /root/server/
COPY *.h /root/server/
COPY *.pro /root/server/

RUN qmake SERV_351_SS.pro && make

CMD ["./mytcpserver"]
