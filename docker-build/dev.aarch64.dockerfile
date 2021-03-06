FROM arm64v8/ubuntu:18.04

ENV DEBIAN_FRONTEND=noninteractive
ENV PATH /opt/apollo/sysroot/bin:$PATH
ARG GEOLOC

LABEL version="1.2"

COPY installers /tmp/installers
COPY rcfiles /opt/apollo/rcfiles
COPY scripts /opt/apollo/scripts

# Pre-downloaded tarballs
COPY archive /tmp/archive

RUN bash /tmp/installers/install_minimal_environment.sh ${GEOLOC}
RUN bash /tmp/installers/install_cmake.sh

RUN bash /tmp/installers/post_install.sh

WORKDIR /apollo
