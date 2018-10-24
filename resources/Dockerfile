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
RUN wget https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-3.2.0.1227-linux.zip && \
    unzip sonar-scanner-cli-3.2.0.1227-linux.zip && \
    rm sonar-scanner-cli-3.2.0.1227-linux.zip && \
    mv sonar-scanner-3.2.0.1227-linux /opt && \
    wget https://sonarcloud.io/static/cpp/build-wrapper-linux-x86.zip && \
    unzip build-wrapper-linux-x86.zip && \
    rm build-wrapper-linux-x86.zip && \
    mv build-wrapper-linux-x86 /opt && \
    ln -s /opt/build-wrapper-linux-x86/libinterceptor-x86_64.so /opt/build-wrapper-linux-x86/libinterceptor-haswell.so

# Criterion
RUN wget https://github.com/Snaipe/Criterion/releases/download/v2.3.2/criterion-v2.3.2-linux-x86_64.tar.bz2 && \
    tar xf criterion-v2.3.2-linux-x86_64.tar.bz2 && \
    mv criterion-v2.3.2/include/criterion /usr/include && \
    mv criterion-v2.3.2/lib/* /usr/lib


WORKDIR /code
