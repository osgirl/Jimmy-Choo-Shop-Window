console.log('Starting App...');

const fs = require('fs');
const os = require('os');
const notes = require('./notes.js');

//fs.appendFile('greetings.txt', "Hello world!");

var user = os.userInfo();

//console.log(user);

//fs.appendFile('greetings.txt', "Hello " + user.username + "!");
//fs.appendFile('greetings.txt', `Hello ${user.username}!`);