<script>
//<!--
var Onglet_afficher = 1;
function Affiche(Nom)
{
document.getElementById('affiche-contenu-'+Onglet_afficher).className = 'inactif onglet';
document.getElementById('affiche-contenu-'+Nom).className = 'affiche-contenu-1 onglet';
document.getElementById('contenu_'+Onglet_afficher).style.display = 'none';
document.getElementById('contenu_'+Nom).style.display = 'block';
Onglet_afficher = Nom;
}
//-->
</script>
