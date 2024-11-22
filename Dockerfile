FROM debian:bullseye


# Set working directory
WORKDIR /app

# Install necessary tools
RUN apt-get update && apt-get install -y \
    gcc \
    libc6-dev \
    make \
    && rm -rf /var/lib/apt/lists/*

# Copy the client and server source code into the working directory
COPY tcp_client.c /app/
COPY tcp_server.c /app/

# Compile the client and server programs
RUN gcc -o tcp_client tcp_client.c
RUN gcc -o tcp_server tcp_server.c

# Expose the port for the server
EXPOSE 9602

# Set the default command (optional)
CMD ["/bin/bash"]

# 1. Build the Docker Image
#     docker build -t tcp_app .
# 2. Create a custom network
#    docker network create tcp_net
# 2. Run the Server
#     docker run -it --rm --network tcp_net tcp_app bash
#     ./tcp_server
# 3. Run the Client
#     docker run -it --rm --network tcp_net tcp_app bash
#     ./tcp_client


# OR
# Open PowerShell as Administrator and run:
# wsl --list --verbose
# wsl -d Ubuntu-20.04
# sudo apt-get update
# sudo apt-get install gcc make
# gcc -o tcp_server tcp_server.c
# ./tcp_server


