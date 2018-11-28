var express = require('express');
var http = require('http');
var spawn = require('child_process').spawn;
var exec = require('child_process').exec;

var app = express();

var server = http.createServer(app);

var io = require('socket.io').listen(server);

// Modification du dossier par défaut des templates
app.set('views', __dirname);

// Lisaison des fichiers js et css
app.use('/', express.static(__dirname));


app.get('/', function(req, res) {
    res.render('main.ejs', {});
});


io.sockets.on('connection', function(socket) {
    console.log('Connexion !!!!!!!');

    //child = spawn('dir');
    //
    var child = spawn('cmake-build-debug/Agenda', ['0']);

    //child.stdout.setEncoding('utf-8');
    //child.stdin.setEncoding('utf-8');

    child.stdout.on('data', function (data) {
        console.log(data.toString())
        socket.emit('message', data.toString());
    });

    child.stderr.on('data', function (data) {
        console.error(data.toString());
    });


    child.stdout.end();

    socket.on('input', function(input) {
        console.log('INPUT: ' + input);
        child.stdin.write(input + '\n');
    });

    /*socket.on('disconnect', function () {
        console.log('Deconnexion du navigateur');
        console.log('Arrêt de l\'application...');
        child.kill('SIGINT');
    });*/

    console.log('Childprocess started');

});

server.listen(8080);