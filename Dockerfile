###############################################
#         Dockerfile for duckshell            #
###############################################

# run the following to build and exec the duckshell
# in a container :)
#
# docker image build -t duckshell:duck .
# docker container run -it --rm duckshell:duck

FROM gcc:10.3.0

ENV USER=root
ENV PWD=/root/duckshell

RUN mkdir /root/duckshell

WORKDIR /root/duckshell

COPY . .

RUN make re
RUN make clean

CMD ["./minishell"]
