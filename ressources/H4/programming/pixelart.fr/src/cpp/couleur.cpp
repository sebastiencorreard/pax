target=couleur couleur02

\text{theme=[ambiance,neat]}
#if defined TARGET_couleur
\title{Couleur primaire}
\integer{nnn=randint(1..3)}
\text{lcol=rouge,vert,bleu}
\text{col=\lcol[\nnn]}
\text{lcola=255,0,0;0,255,0;0,0,255;255,255,0}
\text{cola=\lcola[\nnn;]}
\text{coldef=0,0,0}
\text{ps=primaires}
\text{rvb=le rouge, le vert et le bleu.}
\text{codeco=p.getRed()==?? and p.getGreen()==?? and p.getBlue()==??}
\text{affich=}
#endif
#if defined TARGET_couleur02
\title{Couleur secondaire}
\integer{nn=randint(1..3)}
\text{lcol=rouge,vert,bleu}
\text{col=\lcol[\nn]}
\text{mm=(\nn==1)?randint(1..2)}
\text{mm=(\nn==2)?randitem(1,3)}
\text{mm=(\nn==3)?randint(2..3)}
\text{lcola=255,255,0;255,0,255;0,255,255}
\text{cola=\lcola[\mm;]}
\integer{nnn=(\nn==1 && \mm==1)?2}
\integer{nnn=(\nn==1 && \mm==2)?3}
\integer{nnn=(\nn==2 && \mm==1)?1}
\integer{nnn=(\nn==2 && \mm==3)?3}
\integer{nnn=(\nn==3 && \mm==2)?1}
\integer{nnn=(\nn==3 && \mm==3)?2}
\text{coldef=(\nn==1)?255,0,0}
\text{coldef=(\nn==2)?0,255,0}
\text{coldef=(\nn==3)?0,0,255}

\text{ps=secondaires}
\text{rvb=le jaune, le majenta et le cyan.<div class="wimscenter">
<img src="\imagedir/synthese_additive.png" alt="Synthèse additive"/></div>}
\text{codeco=(p.getRed()==?? and p.getGreen()==?? and p.getBlue()==??) or (p.getRed()==?? and p.getGreen()==?? and p.getBlue()==??)}
\text{affich=,p.getRed(),p.getGreen(),p.getBlue()}
#endif

\text{code=
import image

trouve=False
img = image.Image('dalle')
for ligne in range(img.getHeight()):
    for colonne in range(img.getWidth()):
        p = img.getPixel( colonne, ligne)
        if \codeco:
            print(colonne,ligne\affich)
            trouve=True
      
if not trouve:
  print('Modifier les valeurs car l\\'algorithme n\\'a pas pu trouver le pixel défectueux.')
}

\text{A=slib(runcode [python,[\code]],id1,init theme=\theme fullscreen,Jouer le code !)}

\integer{pxd=randint(1..599)}
\integer{pyd=randint(1..399)}

\text{BB=draw(600,400
frect 0,0,600,400,\cola
frect \pxd,\pyd,\pxd,\pyd,\coldef)}


\integer{rh=randint(0..255)}
\integer{gh=randint(0..255)}
\integer{bh=randint(0..255)}


\statement{
<div class="encadre">
<p class="problematique">Chercher le pixel défectueux</p>
<div id="boited">
<img src="\imagedir/pixel.png" alt="Pixels" id="test"/>
</div>
<div class="enonce">
Un écran de téléphone en couleur est un tableau composé de lignes et de colonnes dans
 lequelle chaque pixel comporte 3 informations rouge, vert et bleu. L'image ci-contre
 illustre cette représentation. Chaque couleur est codée sur 8 bits donc il est possible
 d'avoir \(2^8=256\) nuances. Par conséquent les valeurs des 3 différentes couleurs
 varient entre 0 et 255.
<div class="wims_instruction">
Modifier la position des 3 curseurs afin d'obtenir des couleurs différentes. Par exemple
 essayer d'obtenir \rvb
</div>
<table class="wimscenter wimsborder">
  <tr><td>Red</td>
      <td><input type="range" min="0" max="255" value="\rh" id="rouge"></td>
      <td id="rv">\rh</td>
  </tr>
  <tr>
      <td>Green</td>
      <td><input type="range" min="0" max="255" value="\bh" id="vert"></td>
      <td id="gv">\gh</td>
  </tr>
  <tr>
      <td>Blue</td>
      <td><input type="range" min="0" max="255" value="\gh" id="bleu"></td>
      <td id="bv">\bh</td>
   </tr>
</table>
<div id="boule"></div>

<p>Un pixel sur une dalle est constitué de trois lampes:  une rouge, une verte et une bleue.
<br/>Afin de tester l'ensemble des pixels d'une dalle,
 on met la dalle dans une des 3 couleurs \ps et on vérifie  que tous les pixels s'allument.
La dalle suivante possède un pixel défectueux. Essayer de trouver le pixel.</p>
<div class="wims_instruction">
Utiliser la fonction zoom de votre navigateur en appuyant sur les touches \(\text{Ctrl}\) et \( \text{+} ) pour zoomer.
Appuyer sur les touches \(\text{Ctrl}\) et \( - \) pour dézoomer.
</div>
<div class="wimscenter wimsborder">
<img src="\BB" alt="Dalle" id="dalle"/>
</div>

Modifier cet algorithme afin qu'il recherche le pixel défectueux sur la dalle de smartphone
 ci-dessus.
<div>
\A
</div>
<img src="\imagedir/attention.png" alt="Attention" /> : L'algorithme proposé est lent et il
 met plusieurs secondes à s'exécuter. Si votre navigateur vous propose d'arrêter le
 script, suivre son conseil et recommencer l'exercice.
 <br/>
Le pixel défectueux a donc pour coordonnées : \special{mathmlinput [\left( reply1 ;reply2 \right)],3 answer
reply1,,color:blue;text-align:center;
reply2,,color:blue;text-align:center;}
et la couleur de la lampe défectueuse est : \embed{reply3}
</div>
</div>
<script>
var bouboule=document.getElementById("boule");
var sliderRed=document.getElementById("rouge");
sliderRed.oninput=function(){document.getElementById("rv").innerHTML=this.value;coul();};
var sliderGreen = document.getElementById("vert");
sliderGreen.oninput = function (){document.getElementById("gv").innerHTML = this.value;coul();};
var sliderBlue = document.getElementById("bleu");
sliderBlue.oninput = function (){document.getElementById("bv").innerHTML = this.value;coul();};
function coul(){
  var r = document.getElementById("rv").innerHTML;
  var g = document.getElementById("gv").innerHTML;
  var b = document.getElementById("bv").innerHTML;
  bouboule.style.backgroundColor = "rgb("+r+","+g+","+b+")";
}
coul();
</script>
}

\answer{}{\pxd}{type=numeric}{option=absolute}
\answer{}{\pyd}{type=numeric}{option=absolute}
\answer{}{\nnn;\lcol}{type=menu}{option=}
