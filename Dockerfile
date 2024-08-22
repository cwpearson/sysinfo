FROM debian:buster-20181112-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get --allow-unauthenticated --allow-insecure-repositories update \
 && apt-get --allow-unauthenticated install -y --no-install-suggests --no-install-recommends gnupg

RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 648ACFD622F3D138 \
 && apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 0E98404D386FA1D9 \
 && apt-key adv --keyserver keyserver.ubuntu.com --recv-keys DCC9EFBF77E11517 \
 && apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 112695A0E562B32A \
 && apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 54404762BBB6E853
   
RUN apt-get update \
 && apt-get install -y --no-install-suggests --no-install-recommends \
 cmake make g++
