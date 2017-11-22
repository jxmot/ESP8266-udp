// https://nodejs.org/api/dgram.html

const dgram = require('dgram');
const client = dgram.createSocket('udp4');

//const host = '0.0.0.0';
//const host = '192.168.0.7';
const host = '192.168.0.14';
//const port = 41100;
const port = 48431;

const message = new Buffer('Hello Server');

client.on('message', (message, remote) => {
//    console.log('Server: ' + message);
    console.log(`client got: ${message} from ${remote.address}:${remote.port}`);
});

client.send(message, 0, message.length, port, host, (err, bytes) => {
    if (err) {
        throw err;
    }
    console.log('Message sent');
});

