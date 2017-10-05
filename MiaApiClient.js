const thrift = require('thrift');
const MIATypes = require('./gen-nodejs/mia_types');
const MIAScriptAPI = require('./gen-nodejs/MIAScriptAPI');
const sync = require('synchronize')

module.exports = class MiaApiClient {
  constructor(host, port) {
    this.connection = createConnection(host, port);
    this.client = createClient(this.connection);

    // sync(this.client, 'MILogMsg', 'MIGetTaskParam', 'MISetTaskParam');
  }

  MILogMsg(message) {
    // sync.await(this.client.MILogMsg(message, sync.defer()));
    return this.client.MILogMsg(message);
  }

  MISetTaskParam(paramName, paramValue) {
    // sync.await(this.client.MISetTaskParam(paramName, paramValue, sync.defer()));
    return this.client.MISetTaskParam(paramName, paramValue);
  }

  MIGetTaskParam(paramName) {
    // return sync.await(this.client.MIGetTaskParam(paramName, sync.defer()));
    return this.client.MIGetTaskParam(paramName);
  }

  close() {
    if (this.connection) {
      this.connection.end();
    }
  }
};

const createConnection = (host, port) => {
  const connection = thrift.createConnection(host, port);
  
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

  return connection;
}

const createClient = (connection) => {
  // Create a client with the connection
  const client = thrift.createClient(MIAScriptAPI, connection);
  return client;
}
