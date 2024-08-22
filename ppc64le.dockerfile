FROM debian:bullseye-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
 && apt-get install -y --no-install-suggests --no-install-recommends \
 ca-certificates cmake make g++
