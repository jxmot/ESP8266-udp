# NodeJS UDP-Test Server

This document will describe some JavaScript files that are run on Node. So at this point I'll assume that you're familiar with Node and can run a script.

## History

While I was working on my UDP sketch and encountering problems I realized that I needed a working *end-to-end* UDP server and client. This would allow me to use *Wireshark* to observe a properly working UDP packet exchange.

## Requirements

* A *local* Node installation. This can be on your PC (*Linux, Mac or Windows*), or on any other node-capable computer on your network.
* The JavaScript files in this repository at `/nodejs`, place copies where your Node installation is available or run them from the `/nodejs` folder.

### `server-udp-cfg.js` Optional Modification

The file currently contains - 

```javascript
module.exports = {
     host : '0.0.0.0',
     port : 48000
};
```

Which tells the UDP server to listen on all *network interfaces* on the current machine, and use port number `48000`.

### `client-udp-cfg.js` Modification

The file currently contains - 

```javascript
module.exports = {
    host : '192.168.0.7',
    port : 48000,
    repeat: 5
};
```

Which tells the UDP client to send packets to `192.168.0.7` on port `48000`, and `repeat` tells it to send the packet 5 times. 

**NOTE :** The `repeat` setting is multi-purpose, and works like this - 

* With values from **0** through **500** : This is the quantity of packets that the client will send.
* With values greater than **500** : This will represent time *in milliseconds* between each packet sent. It will repeat an infinite number of times.

## First Test

I recommend running the server and the client just to make sure that everything is working properly. To do that you will first have to change the `host` in `client-udp-cfg.js`. Edit the IP address so that it matches the IP address machine where you are running the server. Please note that both the server and client can be ran on the same machine. 

Run the first test by starting the server *first* - 

`>node server-udp.js`

Then start the client (*from a different command-line instance*) - 

`>node client-udp.js`

### Sample Output

The server - 
```
>node server-udp.js
server listening 0.0.0.0:48000
server reply: REPLY>> #1  Got [Hello Server]
server reply: REPLY>> #2  Got [Hello Server]
server reply: REPLY>> #3  Got [Hello Server]
server reply: REPLY>> #4  Got [Hello Server]
server reply: REPLY>> #5  Got [Hello Server]
```

The client - 

```
>node client-udp.js
sending first of 5 messages now
Message sent
client got reply : [REPLY>> #1  Got [Hello Server]] from 192.168.0.7:48000
sending 2 of 5 messages now
Message sent
client got reply : [REPLY>> #2  Got [Hello Server]] from 192.168.0.7:48000
sending 3 of 5 messages now
Message sent
client got reply : [REPLY>> #3  Got [Hello Server]] from 192.168.0.7:48000
sending 4 of 5 messages now
Message sent
client got reply : [REPLY>> #4  Got [Hello Server]] from 192.168.0.7:48000
sending 5 of 5 messages now
Message sent
client got reply : [REPLY>> #5  Got [Hello Server]] from 192.168.0.7:48000
```



<br>
<br>
<br>
&copy; 2017 James Motyl

