var express = require('express');
var http = require('http');
var spawn = require('child_process').spawn;
var opn = require('opn');
var path = require('path');

var app = express();

var server = http.createServer(app);

var io = require('socket.io').listen(server);

// Detecté par pkg comme assets et les ajouter à l'executable
path.join(__dirname, 'bootstrap.min.css');
path.join(__dirname, 'index.html');
path.join(__dirname, 'jquery.min.js');
path.join(__dirname, 'script.js');
path.join(__dirname, 'styles.css');

// Modification du dossier par défaut des templates
app.set('views', __dirname, '/');

// Lisaison des fichiers js et css
app.use('/', express.static(__dirname));

// Routage du serveur
app.get('/', function(req, res) {
    res.sendFile(path.join(__dirname, 'index.html'));
});

// Quand un client se connecte
io.sockets.on('connection', function(socket) {
    console.log('Navigateur connecté au serveur local');

    console.log('Démarrage du programme');

    // Lancement de l'agenda en un processus enfant
    var child = spawn('Agenda', ['0']);

    child.stdin.setEncoding('utf-8');

    child.stdout.on('data', function (buffer) {
        var data = buffer.toString();
        console.log('Reception du programme: ' + data.toString())

        var buff = "";

        console.log(buff);

        socket.emit('message', data.toString());
    });

    child.on('error', (err) => {

        var error = "Erreur: impossible d'executer le programme !\n" +
            "Verifiez-bien que Agenda.exe est dans le même dossier que ce programme";

        // Ecriture de l'erreur sur console et dans le navigateur
        console.error(error);
        socket.emit('message', error);
    });

    // Lors d'un clic d'un bouton ou d'une validation de texte
    socket.on('input', function(input) {
        console.log('Envoi au programme ' + input);
        child.stdin.write(input + '\n');
    });

    // Lors de la fermeture du navigateur
    socket.on('disconnect', function() {
        console.log('Navigateur fermé. Arrêt du programme');
        child.kill('SIGINT');
    });
});

console.log('Bienvenue sur l\'interface graphique...');
server.listen(8080);
console.log('Serveur local en écoute sur http://127.0.0.1:8080...');
console.log('Ouverture du navigateur...');
opn('http://127.0.0.1:8080');