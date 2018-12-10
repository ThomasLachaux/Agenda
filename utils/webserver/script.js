$(function() {
    var socket = io.connect('127.0.0.1:8080');

    controlOutput(socket);
    controlInput(socket);
});


function controlOutput(socket) {
    socket.on('message', function (message) {

        // Affichage du contenu en fondu
        $('.buffer')
            .hide()
            .html('<div class="instruction">' + message + '</div>')
            .fadeIn('slow');

        // Mise en forme du texte
        $('.instruction')
            .contents()
            .filter(function() {
                // Mise en forme du texte si le texte est dans le tag courant et qu'il n'est pas vide (sans compter les \n...)
                return this.nodeType == Node.TEXT_NODE && $(this).text().replace(/(\r\n|\n|\r)/gm,"") != "";
            })
            .wrap('<h1 class="display-4 instruction-text"/>');

        // Alignement et mise en forme des boutons
        $('.instruction button').wrapAll('<div class="button-group"/>')
        $('button').addClass('btn btn-outline-primary btn-lg');

        // Gestions des champs
        $('form').submit(false);
        $('form input[type=text]').focus();
        $('form').on('submit', function(e) {
            e.preventDefault();
            socket.emit('input', $('.input').val().toString());
        });

    });
}

function controlInput(socket) {


    // Gestions des boutons
    $('.buffer').on('click', 'button', function () {
        socket.emit('input', $(this).val());
    });
}