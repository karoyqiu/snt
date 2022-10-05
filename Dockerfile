# syntax=docker/dockerfile:1
# 构建
FROM alpine as build
RUN sed -i "s/dl-cdn.alpinelinux.org/mirrors.aliyun.com/g" /etc/apk/repositories \
    && apk add --no-cache build-base cmake ninja zip unzip curl git pkgconfig openssl-dev linux-headers
ENV VCPKG_FORCE_SYSTEM_BINARIES=1
RUN git clone --depth=1 https://kgithub.com/microsoft/vcpkg.git /vcpkg && /vcpkg/bootstrap-vcpkg.sh -disableMetrics
RUN mkdir /src /out && /vcpkg/vcpkg install spdlog yaml-cpp libuuid

COPY . /src
RUN cmake -GNinja -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release -DMUSL=ON -S /src -B /out && cmake --build /out 

# 运行
FROM alpine
COPY --from=build /out/sntd /usr/bin
CMD ["/usr/bin/sntd"]
