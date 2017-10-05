const sync = require('synchronize')
const MiaApiClient = require('./MiaApiClientSync')
const fs = require('fs');
const readlines = require('n-readlines');
const axios = require('axios');

const api = new MiaApiClient('10.21.64.172', 9090);

const callMiaApi = (api) => {
  const PARAM_NAME = 'hello';
  const PARAM_VALUE = 'world';
  
  // test mia api
  api.MILogMsg('Test started...');

  api.MISetTaskParam(PARAM_NAME, PARAM_VALUE);

  const value = api.MIGetTaskParam(PARAM_NAME);
  console.log(`${PARAM_NAME}=${value}`);

  api.MILogMsg(`${PARAM_NAME}=${value}`);
};

const readLinesFromFile = () => {
  const liner = new readlines('./file.in');
  let lineNumber = 0;
  let line;
  while (line = liner.next()) {
      console.log('Line ' + lineNumber + ': ' + line.toString('ascii'));
      lineNumber++;
  }
  console.log('end of line reached');
};

const appendLinesToFile = () => {
  fs.appendFileSync('./file.in', '\nnew line');
  fs.appendFileSync('./file.in', '\nnew line');
  console.log('end of line appending');

  const fd = fs.openSync('./file.in', 'a');
  fs.writeSync(fd, '\nanother new line');
  fs.closeSync(fd);
};

const makeHttpRequests = () => {
  const postmanEcho = axios.create({
    baseURL: 'https://postman-echo.com'
  });
  
  return new Promise((resolve, reject) => {
    // Make a request for a user with a given ID
    postmanEcho.get('/basic-auth', {
      headers: {'Authorization': 'Basic cG9zdG1hbjpwYXNzd29yZA=='}
    })
    .then(response => {
      console.log('data: ' + response.data);
      console.log('status: ' + response.status);
      console.log('status text: ' + response.statusText);
      console.log(response.headers);
    
      return postmanEcho.get('/get', {
        params: {
          test: '123'
        }
      });
    })
    .then(response => {
      console.log('data: ' + response.data);
      console.log('status: ' + response.status);
      console.log('status text: ' + response.statusText);
      console.log(response.headers);

      resolve(response.data);
    })
    .catch(error => {
      reject();
    });
  });
};

sync.fiber(function() {
  try {
    callMiaApi(api);

    // read lines synchronously
    readLinesFromFile();

    // append a new line
    appendLinesToFile();

    // make HTTP requests
    makeHttpRequests()
    .then(data => {
      console.log(data);
    })
    .catch(err => {
      console.log(error);
    })
    .then(() => {
      api.close();
    })
  } catch(err) {
    console.log(err);
    api.close();
  }
});

