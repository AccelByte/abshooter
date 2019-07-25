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
    chmod +x LinuxNoEditor/run.sh && \
    chmod +x LinuxNoEditor/register.sh && \
    chown -R shooter .
USER shooter
ENTRYPOINT ["bash", "./LinuxNoEditor/run.sh", "-f", "/dev/null"]
