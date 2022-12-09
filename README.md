# Websrv

**This project is here to make you write your own HTTP server. You will be able to test it with a real browser. HTTP is one of the most used protocol on internet. Knowing its arcane will be useful, even if you won't be working on a website.**

[What is web server ?](https://developer.mozilla.org/en-US/docs/Learn/Common_questions/What_is_a_web_server)
# How it Works ?

**Web servers follow a client-server model. In this structure, one program, also known as the client, requests a resource or service from another program, the server.**

**when a web user wants to load a website content, his web browser send's an [`Http request`](https://www.ibm.com/docs/en/cics-ts/5.3?topic=protocol-http-requests) to the web server then it anwsers with a [`Http response`](https://www.ibm.com/docs/en/cics-ts/5.2?topic=protocol-http-responses)**

![web server image](./public/img/web-server.png)

# Usage

**Build project using : ``` make ```**

**Run the program using : ``` ./Webserv [your config file] ``` or ``` ./Webserv``` to use default config file**

**To configure the server you will need to modify ```config.conf``` which is located on ```/conf``` or create a new config file and pass it as argument**

**This server is compatible with `Firefox` only !!!!!!**

# Contributors :

[Imad abid](https://github.com/imabid99)
[Ousama beaj](https://github.com/BEAJousama)
[Hicham bel houcin](https://github.com/Hicham-BelHoucin)

# Some useful resources :

[Understand how Select and it's equivalent work .](https://youtu.be/Y6pFtgRdUts)
[Understand difference between blocking file descriptor and non-blocking](https://youtu.be/wB9tIg209-8)
[Exmaple of socket usage in c](https://www.binarytides.com/socket-programming-c-linux-tutorial/)