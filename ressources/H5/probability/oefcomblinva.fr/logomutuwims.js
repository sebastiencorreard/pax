<script>
function logoOEFTitle(){
  var elt=document.querySelector("h1.oeftitle");
  var elChild = document.createElement("IMG");
  elChild.setAttribute("src","https://wimsedu.info/wp-content/uploads/2019/06/logo.png");
  elChild.setAttribute("width","60");
  elChild.setAttribute("height","61");
  elChild.setAttribute("style","float:right;margin-left:0.5em;margin-right:0.2em;");
  elChild.setAttribute("alt","Logo MutuWIMS");
  elt.insertBefore(elChild,elt.firstChild);
}
document.addEventListener("DOMContentLoaded", function(){
  logoOEFTitle();
});
</script>
