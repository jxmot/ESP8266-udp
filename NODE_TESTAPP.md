# NodeJS UDP-Test Server

This document will describe some JavaScript files that are run on Node. So at this point I'll assume that you're familiar with Node and can run a script.

## History

While I was working on my UDP sketch and encountering problems I realized that I needed a working *end-to-end* UDP server and client. This would allow me to use *Wireshark* to observe a properly working UDP packet exchange.

## Requirements

* A *local* Node installation. This can be on your PC (*Linux, Mac or Windows*), or on any other node-capable computer on your network.
* The JavaScript files in this repository at `/nodejs`, place copies where your Node installation is available.

### `server-udp-cfg.js` Optional Modification

The file currently contains - 

```javascript
module.exports = {
     host : '0.0.0.0',
     port : 48431
};
```

Which tells the UDP server to listen on all IP addresses on the current machine, and use port number `48431`.

Modifying either the address or the port is *optional*. You can use them as-is, as long as the client-side `/data/servercfg.dat` and the `/data/_servercfg.dat` files match appropriately.

## Running the test

Just as usual - 

`>node server-udp.js`

That's it! No additional packages are needed.

### Sample Output

While the sketch is running...

```
>node server-udp.js
server listening 0.0.0.0:48431
server reply: >> #1  Got [this is a test 1 2 3 4]
server reply: >> #2  Got [this is a test 1 2 3 4]
server reply: >> #3  Got [this is a test 1 2 3 4]
server reply: >> #4  Got [this is a test 1 2 3 4]
```

And in the Arduino serial console - 

```
initUDP() - success = 1

sendUDP() - len = 22
sendUDP(75) - sending to 192.168.0.7:48431

loop() - sent = 75  data = this is a test 1 2 3 4

recvUDP() - packetLen = 35  readLen = 35

loop() - rcvd = 35

loop() - data = >> #1  Got [this is a test 1 2 3 4]

sendUDP() - len = 22
sendUDP(75) - sending to 192.168.0.7:48431

loop() - sent = 75  data = this is a test 1 2 3 4

recvUDP() - packetLen = 35  readLen = 35

loop() - rcvd = 35

loop() - data = >> #2  Got [this is a test 1 2 3 4]

sendUDP() - len = 22
sendUDP(75) - sending to 192.168.0.7:48431

loop() - sent = 75  data = this is a test 1 2 3 4

recvUDP() - packetLen = 35  readLen = 35

loop() - rcvd = 35

loop() - data = >> #3  Got [this is a test 1 2 3 4]

sendUDP() - len = 22
sendUDP(75) - sending to 192.168.0.7:48431

loop() - sent = 75  data = this is a test 1 2 3 4

recvUDP() - packetLen = 35  readLen = 35

loop() - rcvd = 35

loop() - data = >> #4  Got [this is a test 1 2 3 4]

```

## More Than One

If you have the need to run more than one instance of the test server, and on different ports or even addresses the try this - 

* Make a copy of `/nodejs/server-udp-cfg.js` and give it a new name.
* Edit the new file and make your changes, save it.
* Then run with this command : `>node server-udp.js new-file.js`

You could run multiple instances of Node and the server each with different configuration files.

<br>
<br>
&copy; 2017 James Motyl

