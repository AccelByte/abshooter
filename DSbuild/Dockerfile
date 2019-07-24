FROM ubuntu:16.04
COPY . /home/shooter/
WORKDIR /home/shooter/
RUN apt-get update && \
    apt-get install -y nano && \ 
    apt-get install -y curl && \
    apt-get install -y net-tools && \
    chmod u+s /bin/netstat &&\
    groupadd -g 999 shooter && \
    useradd -r -u 999 -g shooter shooter && \
    chmod +x start.sh && \
    chmod +x LinuxNoEditor/run.sh && \
    chown -R shooter .
USER shooter
ENTRYPOINT ["bash", "./start.sh", "-f", "/dev/null"]
