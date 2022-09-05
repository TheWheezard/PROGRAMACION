var botonSelec = $('body').getElementsByClassName("dropdown-trigger style-scope ytd-menu-renderer")
var botonDel = $('body').getElementsByTagName("ytd-menu-service-item-renderer")

function eliminarVideos(i){
    setInterval(function() {
        botonSelec[i+1].click();
        botonDel[i+2].click();
    }, 300);
}

for (var i = 0; i < 1; ++i){
    eliminarVideos(i);
}