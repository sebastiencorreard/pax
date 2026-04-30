<div class="encadre">
<div id="boiteg">
<img src="\imagedir/blog.jpg" alt="Blog" />
</div>
<div id="boited">
<img src="\imagedir/blog2.jpg" alt="Blog" />
</div>
<p class="problematique"> \pro</p>
<div class="enonce">\enonce

<table id="mytable" class="wimscenter">
<tr>
<th>Semaines</th>
\for{j=1 to 8}{<th>\j</th>}
</tr>
\for{jj=0 to 5}{
<tr>
<td>Nombre de visiteurs sur le blog de <span onclick="nuage(\jj)" style="color:\ccc[\jj+1];font-weight:bold;cursor:pointer">\pre[\jj+1]</span></td>
\for{jjj=1 to 8}{<td>\xy[\jj+2;\jjj]</td>}
</tr>}
</table>