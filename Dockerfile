FROM gcc:11

ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update && apt-get install -y cmake git libgtest-dev ruby ruby-dev ruby-bundler build-essential python3-pip && rm -rf /var/lib/apt/lists/*
RUN gem install bundler
RUN python3 -m pip install conan
RUN git clone https://github.com/conan-io/conan-center-index
RUN cd conan-center-index/recipes/openssl/1.x.x && conan create . 1.1.1i@

RUN mkdir -p /app/
WORKDIR /app/
COPY . .

RUN cd /app/ && bundler && make installDeps
