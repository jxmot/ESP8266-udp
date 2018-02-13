/* ************************************************************************ */
/*
    server-udp.js - Used in the ESP8266-udp project to aid in developing and
    testing UDP packet exchange between a client (ESP8266-udp) and a server
    running this script under NodeJS.

    The code in this script was developed based on code found at - 

        UDP / Datagram Sockets | Node.js v6.9.3 Documentation
            https://nodejs.org/docs/v6.9.3/api/dgram.html

    However, there have been some modifications.

    NOTE: This script assumes that it is exchanging strings of text with
    a client.
*/
// an option argument can specify and alternative server configuration file. 
var serverCfgFile = process.argv[2];

// we're assuming that if there's an argument present then it's going to be
// "path + filename.ext". It's not checked for validity.
if((serverCfgFile === undefined) || (serverCfgFile === ''))
    serverCfgFile = './server-udp-cfg.js';

// read the IP address and port # that we'll be using
const cfg = require(serverCfgFile);
const host = cfg.host;
const port = cfg.port;

// create a socket to listen on...
const server = require('dgram').createSocket('udp4');
// a running count of packets received
var count = 0;

/*
    If an error occurs announce it and close the server.
*/
server.on('error', (err) => {
    console.log(err.stack);
    server.close();
});

/*
    Message Received Event Handler
*/
server.on('message', (msg, rinfo) => {
    // got one, bump the counter!
    count += 1;
    // start the announcement...
    var temp = `REPLY>> #${count.toString()}  Got [`;
    /*
        Strings arrive as a "string of character codes". They
        have to be converted to ASCII strings.
    */
    msg.filter(charcode => {
        if(charcode !== 0) {
            temp = temp + String.fromCharCode(charcode);
            return true;
        }
    });
    // finish the announcement
    temp += ']';
    // put a reply together...
    const reply = new Buffer(temp);
    console.log(`server reply: ${reply.toString()}`);
    // send it back to the sender of the message...
    server.send(reply, 0, reply.length, rinfo.port, rinfo.address, (err, bytes) => {
        if(err) console.log(err.stack);
    });
});

/*
    Server Listening has begun
*/
server.on('listening', () => {
    const address = server.address();
    console.log(`server listening ${address.address}:${address.port}`);
});

// must tell the server to listen on the port and address
server.bind(port, host);

