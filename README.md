# Websrv
This project is here to help you write your own HTTP server. You will be able to test it with a real browser. HTTP is one of the most widely used protocols on the internet. Understanding its intricacies will be useful, even if you won't be working on a website.

[What is a web server?](https://developer.mozilla.org/en-US/docs/Learn/Common_questions/What_is_a_web_server)

## How it Works

Web servers follow a client-server model. In this structure, one program, also known as the client, requests a resource or service from another program, the server.

When a web user wants to load the content of a website, their web browser sends an [HTTP request](https://www.ibm.com/docs/en/cics-ts/5.3?topic=protocol-http-requests) to the web server, which then responds with an [HTTP response](https://www.ibm.com/docs/en/cics-ts/5.2?topic=protocol-http-responses).

![Web Server](./public/img/web-server.png)

## Usage

Build the project using: `make`

Run the program using: `./Webserv [your config file]` or `./Webserv` to use the default config file.

To configure the server, you will need to modify `config.conf`, which is located in the `/conf` directory, or create a new config file and pass it as an argument.

This server is compatible with Chrome only!

## Tech Stack Used

![Shell](https://img.shields.io/badge/Shell-FFD500?style=for-the-badge&logo=gnu-bash&logoColor=black)
![C++](https://img.shields.io/badge/C++-blue?style=for-the-badge&logo=c%2B%2B)
![PHP](https://img.shields.io/badge/PHP-lightgrey?style=for-the-badge&logo=php)
![HTML](https://img.shields.io/badge/HTML-orange?style=for-the-badge&logo=html5)
![C](https://img.shields.io/badge/C-brightgreen?style=for-the-badge&logo=c)
![Makefile](https://img.shields.io/badge/Makefile-yellow?style=for-the-badge&logo=cmake)
![Python](https://img.shields.io/badge/Python-blueviolet?style=for-the-badge&logo=python)

## Contributors

- [Imad abid](https://github.com/imabid99)
- [Ousama beaj](https://github.com/BEAJousama)
- [Hicham bel houcin](https://github.com/Hicham-BelHoucin)

## Useful Resources

- [Understanding how Select and its equivalent work](https://youtu.be/Y6pFtgRdUts)
- [Understanding the difference between blocking file descriptors and non-blocking](https://youtu.be/wB9tIg209-8)
- [Example of socket usage in C](https://www.binarytides.com/socket-programming-c-linux-tutorial/)
