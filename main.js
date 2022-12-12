var net = require('node:net');
var cluster = require('node:cluster');

var BACKLOG = 1024;
var arg = process.argv[2];

if (cluster.isPrimary) {
  arg.split(',').forEach(function(mapping) {
    let worker = cluster.fork();
    worker.send(mapping);
  });
} else {
  process.on('message', function(mapping) {
    const [FROM_PORT, TO_ADDR] = mapping.split('>');
    const [TO_HOST, TO_PORT] = TO_ADDR.split(':');
    var server = net.createServer(function(socket) {
      let client = net.createConnection({ host: TO_HOST, port: TO_PORT });
      socket.pipe(client);
      client.pipe(socket);
    });

    server.on('error', console.error);

    server.listen(parseInt(FROM_PORT), '127.0.0.1', BACKLOG, function() {
      console.log(mapping);
    });
  });
}
