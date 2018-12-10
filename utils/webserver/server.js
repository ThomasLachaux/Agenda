var express = require('express');
var http = require('http');
var spawn = require('child_process').spawn;
var opn = require('opn');
var path = require('path');

var app = express();

var server = http.createServer(app);

var io = require('socket.io').listen(server);

// Modification du dossier par défaut des templates
app.set('views', __dirname);

// Lisaison des fichiers js et css
app.use('/', express.static(__dirname));


app.get('/', function(req, res) {
    res.sendFile(path.join(__dirname, 'index.html'));
});

io.sockets.on('connection', function(socket) {
    console.log('Navigateur connecté au serveur local');

    console.log('Démarrage du programme');
    var child = spawn('Agenda', ['0'], {'cwd': 'cmake-build-debug/'});

    child.stdin.setEncoding('utf-8');

    child.stdout.on('data', function (buffer) {

        var data = buffer.toString();
        console.log('Reception du programme: ' + data.toString())

        var buff = "";

        console.log(buff);

        socket.emit('message', data.toString());
    });

    socket.on('input', function(input) {
        console.log('Envoi au programme ' + input);
        child.stdin.write(input + '\n');
    });

    socket.on('disconnect', function() {
        console.log('Navigateur fermé. Arrêt du programme');
        child.kill('SIGINT');
    });
});

console.log("Bienvenue sur l'interface graphique...");
server.listen(8080);
console.log("Serveur local en écoute sur http://127.0.0.1:8080...");
console.log("Ouverture du navigateur...");
//opn("http://127.0.0.1:8080");