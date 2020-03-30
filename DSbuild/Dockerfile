FROM ubuntu:16.04
COPY . /home/shooter/
WORKDIR /home/shooter/
RUN apt-get update && \
    apt-get install -y curl && \
    groupadd -g 999 shooter && \
    useradd -r -u 999 -g shooter shooter && \
    chmod +x LinuxNoEditor/ShooterGame/Binaries/Linux/ShooterGameServer && \
    chown -R shooter .
USER shooter
ENTRYPOINT ["./LinuxNoEditor/ShooterGame/Binaries/Linux/ShooterGameServer"]
