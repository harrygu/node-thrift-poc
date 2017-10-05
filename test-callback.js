const thrift = require('thrift');
const MIATypes = require('./gen-nodejs/mia_types');
const MIAScriptAPI = require('./gen-nodejs/MIAScriptAPI');

process.env.BACKEND_HOST='10.21.64.172';

const connection = thrift.createConnection(process.env.BACKEND_HOST || 'localhost', process.env.BACKEND_PORT || 9090);

connection.on('error', function(error) {
    console.error(error);
    console.error('Thrift connection error. Check whether the backend server is running.');
    process.exit(1);
});

process.on('SIGINT', function() {
    console.log('Closing connection.');
    connection.end();
    console.log('Closing connection: Done.');
    process.exit(0);
});

console.log('Connected to the server');

// Create a client with the connection
const client = thrift.createClient(MIAScriptAPI, connection);

const PARAM_NAME = 'hello';
const PARAM_VALUE = 'world';

client.MILogMsg('Test started...', function(err) {
  if (err) {
    console.log(`MILogMsg() failed - ${err}`);
  } else {
    console.log(`MILogMsg() succeeded`);

    client.MISetTaskParam(PARAM_NAME, 'world', function(err, message) {
      if (err) {
        console.log(`MISetTaskParam(${PARAM_NAME}, ${PARAM_VALUE}) failed - ${err}`);
      } else {
        console.log(`MISetTaskParam(${PARAM_NAME}, ${PARAM_VALUE}) succeeded`);

        client.MIGetTaskParam(PARAM_NAME, function(err, response) {
          if (err) {
            console.log(`MIGetTaskParam(${PARAM_NAME}) failed - ${err}`);
          } else {
            console.log(`MIGetTaskParam(${PARAM_NAME}) returned ${response}`);

            const msg = `${PARAM_NAME}, ${response} - Test succeeded`;
            client.MILogMsg(msg, function(err) {
              if (err) {
                console.log(`MILogMsg() failed - ${err}`);
              } else {
                console.log(msg);
              }
            });
          }

          connection.end();
        });
      }
    });
  }
});