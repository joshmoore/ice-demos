FROM centos:centos7

RUN yum install -y wget
RUN cd /etc/yum.repos.d && wget https://zeroc.com/download/Ice/3.6/el7/zeroc-ice3.6.repo
RUN yum install -y ice-all-runtime ice-all-devel
RUN yum install -y epel-release
RUN yum install -y python-pip
RUN pip install https://github.com/openmicroscopy/zeroc-ice-py-centos7/releases/download/0.0.2/zeroc_ice-3.6.3-cp27-cp27mu-linux_x86_64.whl
RUN yum install -y lsof

RUN mkdir /src
COPY *.py /src/
COPY *.ice /src/
WORKDIR /src
