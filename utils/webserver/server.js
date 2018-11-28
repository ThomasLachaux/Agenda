var express = require('express');
var http = require('http');
var spawn = require('child_process').spawn;

var app = express();

var server = http.createServer(app);

var io = require('socket.io').listen(server);

// Modification du dossier par défaut des templates
app.set('views', __dirname);

// Lisaison des fichiers js et css
app.use('/', express.static(__dirname));


app.get('/', function(req, res) {
    res.render('main.ejs', {name: 'TA RACE !!!!!'});
});


io.sockets.on('connection', function(socket) {
    console.log('Connexion !!!!!!!');

    child = spawn('cmake-build-debug/Agenda.exe');

    child.stdout.setEncoding('utf-8');
    child.stdin.setEncoding('utf-8');

    child.stdout.on('data', function (data) {
        console.log(data);
        socket.emit('message', data);
    });

    socket.on('input', function(input) {
        console.log('INPUT: ' + input);
        child.stdin.write(input + '\n');
    });

    console.log('Starting subprocess...');

});

server.listen(8080);