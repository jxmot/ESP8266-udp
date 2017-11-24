/* ************************************************************************ */
/*
    client-udp.js - A companion script to server-udp.js, which is used in 
    the ESP8266-udp project to aid in developing and testing UDP packet 
    exchange between a client (ESP8266-udp) and a server running this 
    script under NodeJS.

    The code in this script was developed based on code found at - 

        UDP / Datagram Sockets | Node.js v6.9.3 Documentation
            https://nodejs.org/docs/v6.9.3/api/dgram.html

    However, there have been some modifications.

    NOTE: This script assumes that it is exchanging strings of text with
    a server.
*/
// an option argument can specify and alternative client configuration file. 
var clientCfgFile = process.argv[2];

// we're assuming that if there's an argument present then it's going to be
// "path + filename.ext". It's not checked for validity.
if((clientCfgFile === undefined) || (clientCfgFile === ''))
    clientCfgFile = './client-udp-cfg.js';

// read the IP address and port # that we'll be using
const cfg = require(clientCfgFile);
const host = cfg.host;
const port = cfg.port;

// create a socket to listen on...
const dgram = require('dgram');
const client = dgram.createSocket('udp4');

// the message
const message = new Buffer('Hello Server');

/*
    Set up for events if they're needed. And that's
    determined by whether or not `repeat` exists
    in the config file.

    Here's how `repeat` affects the behavior :

        repeat = undefined : Only one UDP packet will be sent

        repeat > 500 : A packet will be sent "repeat" milliseconds after
                       a reply to the previous packet has been received.

        repeat < 500 : Counts down for each packet sent and a reply is
                       received. Stops when 0 is reached.
*/
const events = require('events');
const triggerUDP = new events.EventEmitter();

// Will send UDP packets until it reaches 0
var countdown;

triggerUDP.on('sendUDP', () => {
    sendUDP();
});

/*
    Reply Received Event Handler
*/
client.on('message', (message, remote) => {
    console.log(`client got reply : ${message} from ${remote.address}:${remote.port}`);
    
    if(cfg.repeat === undefined) process.exit();
    else {
        if(countdown > 0) {
            console.log(`sending ${(cfg.repeat - countdown) + 1} of ${cfg.repeat} messages now`);
            countdown -= 1;
            setTimeout( () => {
                triggerUDP.emit('sendUDP');
            }, 1000);
        } else {
            if(countdown === 0) process.exit();
        }
    }
});

/*
*/
if(cfg.repeat === undefined) {
    sendUDP();
} else{
    if((cfg.repeat > 0) && (cfg.repeat <= 500)) {
        countdown = (cfg.repeat - 1);
        console.log(`sending first of ${cfg.repeat} messages now`);
        sendUDP();
    } else {
        if(cfg.repeat > 500) {
            setInterval( () => {
                sendUDP();
            }, cfg.repeat);
        }
    }
}

/*
*/
function sendUDP() {
    // send one message...
    client.send(message, 0, message.length, port, host, (err, bytes) => {
        if(err) throw err;
        console.log('Message sent');
    });
};
