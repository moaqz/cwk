# Web Server

In this task, you will have to develop a simple web server in Python that is capable of processing a single request. Specifically, the web server should (i) create a connection socket when contacted by a client (browser); (ii) receive the HTTP request through said connection; (iii) parse the request to determine which specific file is being requested; (iv) obtain the requested file from the server's file system; (v) create an HTTP response message consisting of the requested file, preceded by a series of header lines, and (vi) send the response to the requesting browser through the TCP connection. If a browser requests a file that is not present on your server, the web server must return a "404 Not Found" error message.

Source: Kurose & Ross, Computer Networking: A Top-Down Approach
