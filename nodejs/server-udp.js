// https://nodejs.org/api/dgram.html

const dgram = require('dgram');
const server = dgram.createSocket('udp4');

const host = '0.0.0.0';
//const port = 41100;
const port = 48431;

server.on('error', (err) => {
    console.log(err.stack);
    server.close();
});

server.on('message', (msg, rinfo) => {

    var temp = ">>Got [";
    msg.filter(charcode => {
        if(charcode !== 0) {
            temp = temp + String.fromCharCode(charcode);
            return true;
        }
    });
    temp += ']';

    const reply = new Buffer(temp);
    console.log(`server reply: ${reply.toString()}`);
    server.send(reply, 0, reply.length, rinfo.port, rinfo.address, (err, bytes) => {
        if (err){
            console.log(err.stack);
        }
    });
});

server.on('listening', () => {
    const address = server.address();
    console.log(`server listening ${address.address}:${address.port}`);
});

server.bind(port, host);

