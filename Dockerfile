FROM ubuntu:jammy as build

RUN apt-get update && \
    apt-get install -y \
        binutils-mips-linux-gnu \
        bsdmainutils \
        build-essential \
        libcapstone-dev \
        pkgconf \
        python3 \
        libz-dev \
        libcurl4-openssl-dev

RUN mkdir /sm64
WORKDIR /sm64
ENV PATH="/sm64/tools:${PATH}"

RUN make -j HEADLESS=1

FROM ubuntu:jammy
COPY --from=build  /sm64/build/sm64coopdx /bin

ENTRYPOINT "/bin/sm64coopdx"

CMD "--server 7777"
