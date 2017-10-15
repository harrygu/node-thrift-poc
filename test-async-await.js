const fs = require('fs');
const readlines = require('n-readlines');
const axios = require('axios');
const MiaApiClient = require('./MiaApiClient')

var backendHost = '10.21.64.172';
backendHost = 'localhost';
const api = new MiaApiClient(backendHost, 9090);

////// Call MIA API asynchronously
const callMiaApiPromise = async function(api) {
// const callMiaApiPromise = async (api) => {
  const PARAM_NAME = 'hello';
  const PARAM_VALUE = 'world';
  
  await api.MILogMsg('Test started...');

  await api.MISetTaskParam(PARAM_NAME, PARAM_VALUE);

  const value = await api.MIGetTaskParam(PARAM_NAME);
  console.log(`========== ${PARAM_NAME}=${value}\n\n`);
      
  await api.MILogMsg(`${PARAM_NAME}=${value}`);

  api.close();
};

////// Make HTTP requests asynchronously
async function makeHttpRequests() {
  try {
    const postmanEcho = await axios.create({
      baseURL: 'https://postman-echo.com'
    });
  
    // Make a request for a user with a given ID
    let response = await postmanEcho.get('/basic-auth', {
        headers: {'Authorization': 'Basic cG9zdG1hbjpwYXNzd29yZA=='}
      });
    // console.log('data: ' + response.data);
    // console.log('status: ' + response.status);
    // console.log('status text: ' + response.statusText);
    // console.log(response.headers);
      
    response = await postmanEcho.get('/get', {
        params: {
          test: '123'
        }
      });
    // console.log('data: ' + JSON.stringify(response.data));
    // console.log('status: ' + response.status);
    // console.log('status text: ' + response.statusText);
    // console.log(response.headers);

    return response.data;
  } catch(err) {
    throw err;
  }
};


////// Read lines from file synchronously
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

////// Append lines to file synchronously
const appendLinesToFile = () => {
  fs.appendFileSync('./file.in', '\nnew line');
  fs.appendFileSync('./file.in', '\nnew line');
  console.log('end of line appending');

  const fd = fs.openSync('./file.in', 'a');
  fs.writeSync(fd, '\nanother new line');
  fs.closeSync(fd);
};

////// Main flow
const mainFunc = async () => {
  try {
    await callMiaApiPromise(api);
    
    // make HTTP requests
    const data = await makeHttpRequests();
    console.log('data: ' + JSON.stringify(data, false, 2));

    // read lines synchronously
    //readLinesFromFile();
    
    // append a new line
    //appendLinesToFile();
  } catch(err) {
    console.log(err);
  }
};

mainFunc();
