/* ************************************************************************ */
/*
    multi-udp.js - listens and waits for a UDP multi-cast.

    This test has been specifically created for testing a mulit-cast
    message used for requesting the IP address of the server that
    received the message. It will reply to the multi-cast sender (if
    the incoming message is correct) with a message containing the
    IP address on the Ethernet interface.

    NOTE: Prior to starting this application edit the file named 
    /ESP8266-udp/udp-defs.h and make sure that USE_MCAST is defined.

*/
// an option argument can specify an alternative configuration file. 
var mcastCfgFile = process.argv[2];

// we're assuming that if there's an argument present then it's going to be
// "path + filename.ext". It's not checked for validity.
if((mcastCfgFile === undefined) || (mcastCfgFile === ''))
    mcastCfgFile = './multi-udp-cfg.js';

/*

    Obtain our IP address(IPv4) associated with the Ethernet
    interface. Typically this code will be ran on a platform
    that uses a wired network connnection. The array below
    represents the object that is returned by accessing
    os.networkInterfaces().Ethernet.

    Ethernet: 
        [ 
            { 
                address: 'fe80::e5a8:81ea:b43f:459',
                netmask: 'ffff:ffff:ffff:ffff::',
                family: 'IPv6',
                mac: '30:5a:3a:e1:30:3c',
                scopeid: 3,
                internal: false 
            },
            { 
                address: '192.168.0.7',
                netmask: '255.255.255.0',
                family: 'IPv4',
                mac: '30:5a:3a:e1:30:3c',
                internal: false 
            } 
        ]
*/
const os = require( 'os' );
const nifs = os.networkInterfaces();
var hostIP;

// interate through the available addesses in the
// Ethernet interface and find the one that is IPv4.
for(var ix = 0;ix < nifs.Ethernet.length;ix++){
    if(nifs.Ethernet[ix].family === 'IPv4') {
        hostIP = nifs.Ethernet[ix].address;
        break;
    }
}

// read the IP address and port # that we'll be listening
// on for multi-cast messages
const cfg = require(mcastCfgFile);

// create a socket to listen on...
const dgram = require('dgram');
const mcast = dgram.createSocket('udp4');

// finish setting up for multi-cast after we've
// begun listening...
mcast.on('listening', () => {
    mcast.setBroadcast(true)
    mcast.setMulticastTTL(128); 
    mcast.addMembership(cfg.addr);
    console.log('UDP Multi-Cast - listening on ' + cfg.addr + ":" + cfg.port);
});

/*
    Reply Received Event Handler
*/
mcast.on('message', (payload, remote) => {
    // the correct way to extract a string from the payload is this - 
    var message = payload.filter(letter => letter !== 0);
    console.log(`multicast received : [${message}] from ${remote.address}:${remote.port}`);

    var msg = JSON.parse(message.toString());
    if(msg.status === 'REQ_IP') {
        // reply with our IP, return the sequence number to the caller.
        var temp = JSON.stringify({reply: 'IP_ADDR', hostip: hostIP, seq: msg.seq});
        console.log(`REQ_IP reply - ${temp}`);

        var reply = new Buffer(temp);
        mcast.send(reply, 0, reply.length, remote.port, remote.address, (err, bytes) => {
            if(err) console.log(err.stack);
        });
    }
});

// all interfaces
//mcast.bind({address:cfg.addr, port:cfg.port});
mcast.bind(cfg.port);
