FROM ubuntu:22.04 AS build

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /ws

COPY . .

RUN rm -rf binaries && mkdir binaries

RUN rm -rf build && mkdir build && cd build && \
    cmake .. && \
    make

FROM ubuntu:22.04

WORKDIR /ws

COPY --from=build /ws/build/posix_build ./posix_build

EXPOSE 52002
EXPOSE 52003

CMD ["./posix_build"]
