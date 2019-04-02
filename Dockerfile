FROM alpine

RUN apk add --upgrade alpine-sdk git cmake curl-dev libcurl openblas lapack bash python
WORKDIR app
RUN git clone https://gitlab.com/conradsnicta/armadillo-code.git
WORKDIR /app/armadillo-code
RUN ./configure
WORKDIR /app/armadillo-code/build
RUN cmake ..
WORKDIR /app/armadillo-code
RUN make && make install
WORKDIR /app
RUN rm -rf armadillo-code/

RUN git clone https://github.com/edenhill/librdkafka.git
WORKDIR /app/librdkafka
RUN    ./configure &&\
       make &&\
       make install
ENV LD_LIBRARY_PATH=/usr/lib64/:/usr/local/lib
ADD . /app
WORKDIR /app
RUN make
CMD ["make", "run"]
