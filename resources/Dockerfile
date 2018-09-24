FROM debian:buster-slim

ENV LANG C.UTF-8
ENV PATH /bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:/opt/sonar-scanner-3.2.0.1227-linux/bin:/opt/build-wrapper-linux-x86

# Base packages
RUN apt update && \
    apt install -y libgit2-dev libgit2-27 curl apt-transport-https ca-certificates gnupg2 software-properties-common unzip gcc g++ make cmake bzip2 wget rpm valgrind python3 ca-certificates libjansson-dev doxygen lcov python-sphinx python-breathe python-sphinx-rtd-theme python3-requests python3-distutils --no-install-recommends && \
    curl -fsSL https://download.docker.com/linux/debian/gpg | apt-key add - && \
    add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/debian $(lsb_release -cs) stable" && \
    apt-get update && \
    apt-get install -y docker-ce && \
    rm -rf /var/lib/apt/lists/*

# Sonar
RUN wget https://sonarsource.bintray.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-3.2.0.1227-linux.zip && \
    unzip sonar-scanner-cli-3.2.0.1227-linux.zip && \
    rm sonar-scanner-cli-3.2.0.1227-linux.zip && \
    mv sonar-scanner-3.2.0.1227-linux /opt && \
    wget https://sonarcloud.io/static/cpp/build-wrapper-linux-x86.zip && \
    unzip build-wrapper-linux-x86.zip && \
    rm build-wrapper-linux-x86.zip && \
    mv build-wrapper-linux-x86 /opt && \
    ln -s /opt/build-wrapper-linux-x86/libinterceptor-x86_64.so /opt/build-wrapper-linux-x86/libinterceptor-haswell.so

# Criterion
RUN wget "https://launchpad.net/~snaipewastaken/+archive/ubuntu/ppa/+files/criterion-dev_2.3.2-5-ubuntu1~bionic1_amd64.deb" -O criterion-dev.deb && \
    dpkg --force-all -i ./criterion-dev.deb && \
    rm criterion-dev.deb && \
    wget "https://launchpad.net/~snaipewastaken/+archive/ubuntu/ppa/+files/criterion_2.3.2-5-ubuntu1~bionic1_amd64.deb" -O criterion.deb && \
    dpkg --force-all -i  ./criterion.deb && \
    rm criterion.deb && \
    ln -s /usr/lib/x86_64-linux-gnu/libgit2.so.27 /usr/lib/x86_64-linux-gnu/libgit2.so.26

WORKDIR /code
