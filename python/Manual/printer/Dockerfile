FROM centos:centos7

RUN curl -o /etc/yum.repos.d/zeroc-ice-el7.repo \
    http://download.zeroc.com/Ice/3.5/el7/zeroc-ice-el7.repo \
 && yum -y install gcc-c++ \
 && yum -y install ice ice-python ice-servers \
 && yum -y install lsof

RUN mkdir /src
COPY *.py /src/
COPY *.ice /src/
WORKDIR /src
