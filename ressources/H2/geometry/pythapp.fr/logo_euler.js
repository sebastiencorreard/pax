<script>
function logoOEFTitle(){
  var elt=document.querySelector("h1.oeftitle");
  var elChild = document.createElement("IMG");
  elChild.setAttribute("src","$imagedir/logo_euler.png");
  elChild.setAttribute("width","48");
  elChild.setAttribute("height","36");
  elChild.setAttribute("style","float:right;margin-left:0.5em;margin-right:0.2em;");
  elChild.setAttribute("alt","Logo Euler Académie de Versailles");
  elChild.setAttribute("title","Euler Académie de Versailles");
  elt.insertBefore(elChild,elt.firstChild);
}

document.addEventListener("DOMContentLoaded", function(){
  logoOEFTitle();
});
</script>
