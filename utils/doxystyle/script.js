$(function() {
    $('.footer small').html('Généré par Doxygen 1.8.14</br>Stylisé par Thomas de Lachaux');

    $('table.directory').wrap('<div class="table-border"></div>');

    //$('div.header, #nav-path ul').wrapInner('<div class="max-width"></div>');
    $('.fragment .line:first-child').each(function(index) {
        if($(this).text() == "mermaid") {

            mermaid.initialize({theme: 'default'});
            var parent = $(this).parent();

            parent.removeClass('fragment');
            parent.children().contents().unwrap();
            parent.appendTo('body');
            parent.addClass('mermaid');
        }
    });
});