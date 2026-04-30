target=Ocean1 Ocean2 Ocean3 Ocean4 Ocean5 Ocean6 Ocean7 Ocean8
\language{fr}
\range{-5..5}
\author{Julien LYOTARD}
\email{Julien.Lyotard@ac-dijon.fr}

\computeanswer{no}
\format{html}
\precision{100000}

\text{lien_video=https://tube-sciences-technologies.apps.education.fr/download/videos}

\text{mkm=7.1,8.1,7.5,7.5,7.75,7.1,7,7.6,7.55,7.7,7.45,6.5,6.55,7.35,6.3,7.3,6.1,7.8,7.05,6.5,6.4,6.6,6.9,5.9,6.35,6.3,5.5}

Pour transformer des données US en données FR 
\matrix{mkmf=wims(replace internal , by ; in \mkm)} 
\matrix{mmm=wims(replace internal . by , in \mkmf)} 

\text{alea=shuffle(27)}
\text{aleaa=item([1..23],\alea)}

\integer{limg=480}
\integer{Limg=1080}

\text{poi=}
\text{rpoi=}
\text{seg=}
\text{rseg=}
\text{list=}

\for{l=1 to 27}{
\integer{x=(\l+3)*5}
\real{y=(\mkm[\l]-5)/0.5*10+10}
\text{rseg=wims(append item \x,\y to \rseg)}
\integer{date=1979+\l}
\real{mkmm=\mkm[\l]-5}
\text{rpoi=wims(append item \date,\mkmm to \rpoi)}
\if{\l isitemof \aleaa}{\text{poi=wims(append item \date,\mkmm to \poi)}}{
\integer{xx=(\l/2+1.5)*60+3}
\integer{yy=480-(63+(\mkm[\l]-5)*60/0.5)}
\text{list=wims(append item \xx,\yy to \list)}
}
}

\text{axey=}
\for{l=2 to 7}{
\integer{pp=\l*10}
\integer{ppp=\pp+1}
\real{grad=\l*0.5+4.5}
\text{ligne=segment 9,\pp,11,\pp,128,128,128}
\text{txt=text blue,5,\ppp,medium,\grad}
\text{axey=\axey
\ligne
\txt}
}

text{axey=\axey
\ligne
\txt}

\text{point=slib(graphpaper/millimetre 18,8,-988,1,2,0.5,[255,255,255],[190,190,190],,style:grad=xy,\poi)}
\text{rpoint=slib(graphpaper/millimetre 18,8,-988,1,2,0.5,[255,255,255],[190,190,190],,style:grad=xy,\rpoi)}
\text{rrpoint=slib(graphpaper/millimetre 18,8,-988,1,2,0.5,[255,255,255],[190,190,190],,style:grad=xy,\rpoi)}


\text{fle=linewidth 3
arrow 10,0,10,80,20,128,128,128
\axey}

\text{rfle=linewidth 3
arrow 10,0,10,80,20,128,128,128
\axey
polyline blue,\rseg}

\text{flgra=\point
\fle}
\text{rflgra=\rpoint
\rfle}
\text{rrflgra=\rpoint
\rfle
fcircle 85,49,12,red}

\text{urlpoint = draw(\Limg,\limg
\flgra)}
\text{rurlpoint = draw(\Limg,\limg
\rflgra)}
\text{rrurlpoint = draw(\Limg,\limg
\rrflgra)}

\text{pro=Quelle serait l’étendue minimale de la glace de mer en Arctique durant l’été 2050 ?}

\text{enonce=A l'aide d'images satellites, un groupe d'expert a relevé la surface minimum de la banquise
 en Arctique.
Source : Nations Unies – GIEC (Groupe d’experts intergouvernemental sur l’évolution du climat – IPCC en anglais)
 rapport 2007
<br><br>}

#if #TARGET(Ocean1)
\title{1.1 (C1)Activité Formatrice}
\statement{
# include "intro_oceanartique.inc"
<div class="question">
A l'aide du tableau, placer les 4 points manquants pour compléter le nuage de points.
 Un clic sur le graphique permet le placement des points :
</div>
<div class="jsxgraph">
\embed{reply1,\Limg x \limg}
</div>
</div>}
\answer{}{\urlpoint;points,\list}{type=jsxgraphcurve}{option=color1=blue color2=red}
#endif

#if #TARGET(Ocean2)
\title{1.2 (C1)Activité Formatrice}
\statement{
# include "intro_oceanartique.inc"
<div class="solution">
Le résultat suivant était attendu :
<div class="wims_scrollable">
<img src="\rurlpoint" alt="nuage de points">
</div>
</div>
<div class="question">
Existe-t-il une manière plus rapide pour réaliser ce nuage de points?
<ul class="wims_nopuce">
\for{h = 1 to 2}{<li>\embed{reply1,\h}</li>}
</ul>
Parmi la liste proposée, donnez le(s) outil(s) dont l'utilisation vous paraît pertinente:
<br>
\embed{reply2}
</div>
</div>}
\answer{Il existe un outil plus rapide.}{2;non,oui}{type=radio}{option=shuffle split analyzeprint}
\answer{Vos réponses sont : }{1,2,3,4;Tableur,Open Office,Libre Office,Excel,TICE,Word,Facebook,MSN,Google,Skype}{type=checkbox}{option=split shuffle analyzeprint}
#endif

#if #TARGET(Ocean3)
\title{1.3 (C2)Activité Formatrice}
\text{flash=slib(media/video [mp4="\lien_video/939e90d1-8e85-4320-8772-a714021b029e-708.mp4"])}
\text{flash2=slib(media/video [mp4="\lien_video/5839da9c-7b8f-4e50-8b01-0b32a101e1c8-708.mp4"])}
\statement{
# include "intro_oceanartique.inc"
<div class="solution">
<p>Il existe bien une manière plus rapide pour construire le nuage de points.</p>
La liste complète des outils est la suivante :
<ul><li>Tableur</li><li>Open Office</li><li>Libre Office</li><li>Excel</li></ul>
</div>
<div class="consigne">
Pour gagner en efficacité, on utilise un tableur :
<br>
<div class="wimscenter">\flash</div>
<br>
<div class="wimscenter">\flash2</div>
</div>
<div class="question">
Réalisez un graphique similaire à celui proposé dans la vidéo. Vous êtes libre de choisir les différentes couleurs.
<br>
Vous devez avoir un graphique comme ci-dessous :
<br>
<div class="wimscenter">
<img src="\imagedir/graphique.png" alt="Graphique">
</div>

Quelle est la forme du nuage de point?
<ul class="wims_nopuce">
\for{h = 1 to 4}{<li>\embed{reply1,\h}</li>}
</ul>

Quelle fonction d'ajustement peut-on utiliser?
<ul class="wims_nopuce">
\for{h = 1 to 4}{<li>\embed{reply2,\h}</li>}
</ul>
</div>
</div>}
\answer{La forme du nuage est allongée.}{1;allongée,parabolique,linéaire,affine}{type=radio}{option=shuffle split}
\answer{On réalise un ajustement affine.}{4;allongée,polynôme du second degré,linéaire,affine}{type=radio}{option=shuffle split}
#endif

#if #TARGET(Ocean4)
\title{1.4 (C3)Activité Formatrice}
\text{flash3=slib(media/video [mp4="\lien_video/e48476e3-27fc-4441-b58a-7225be982cf8-708.mp4"])}
\text{flash4=slib(media/video [mp4="\lien_video/ca9b9b7b-6bdc-442a-b44a-465fec1968cb-708.mp4"])}
\statement{
# include "intro_oceanartique.inc"
<div class="solution">
La forme du nuage de points est bien allongée.
On réalise donc un ajustement affine.
</div>
<div class="consigne">
Calculez les coordonnées du points G à l'aide du tableur :
<br>
<div class="wimscenter">\flash3</div>
Placez le point G à l'aide du tableur :
<br>
<div class="wimscenter">\flash4</div>
</div>
<div class="question">
Par conséquent les coordonnées du point moyen G sont :
<br>
<div class="wimscenter"> G (\embed{reply1,4};\embed{reply2,4})</div>
</div>
</div>}
\answer{xG}{1993}{type=numeric}
\answer{yG}{6.95}{type=numeric}{option=comma}
#endif

#if #TARGET(Ocean5)
\title{1.5 (C4)Activité Formatrice}
\statement{
# include "intro_oceanartique.inc"
<div class="solution">
Les coordonnées du points G sont (1993;6,95).
</div>
<div class="question">
Placez le point G sur le graphique.
</div>
<div class="jsxgraph">
\embed{reply1,\Limg x \limg}
</div>
</div>}
\answer{}{\rurlpoint;points,513,183}{type=jsxgraphcurve}{option=color1=blue color2=red}
#endif

#if #TARGET(Ocean6)
\title{1.6 (C3)Activité Formatrice}
\text{flash5=slib(media/video [mp4="\lien_video/e4b486fb-0071-46af-a21f-06cb84e28fe1-708.mp4"])}
\statement{
# include "intro_oceanartique.inc"
<div class="consigne">
Construisez la droite d'ajustement affine à l'aide du tableur :
<br>
<div class="wimscenter">\flash5</div>
</div>
<div class="question">
Par conséquent l'équation de la droite d'ajustement arrondi à 0.01 est :
<br>
<div class="wimscenter"> y=\embed{reply1,4}x+\embed{reply2,4}</div>
</div>
</div>}
\answer{a}{-0.06}{type=numeric}{option=comma}
\answer{b}{126.56}{type=numeric}{option=comma}
#endif

#if #TARGET(Ocean7)
\title{1.7 (C4)Activité Formatrice}
\statement{
# include "intro_oceanartique.inc"
<div class="consigne">
L'équation de la droite d'ajustement est : \(y=-0.06x+126.56\)
</div>
<div class="question">
Réalisez la construction de cette droite en cliquant 2 fois sur le graphique.
<br>
 Vous devez réaliser au préalable un tableau de valeurs pour connaître les coordonnées de 2 points à placer.
<br>
<table class="wimscenter">
<tr>
<td class="wimscenter"><b>x</b></td>
<td class="wimscenter">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
<td class="wimscenter">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
<td class="wimscenter"><= Choisir des valeurs de x comprises entre l'intervalle [1978;2010].</td>
</tr>
<tr>
<td class="wimscenter"><b>y=-0.06 x + 126.56</b></td>
<td class="wimscenter">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
<td class="wimscenter">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
<td class="float_left"><= Calculer avec l'équation de droite et en remplaçant x par la valeur choisie.</td>
</tr>
</table>
Une utilisation du tableur est possible. Placer très précisément les coordonnées des points calculés sur le graphique.
</div>
<div class="jsxgraph">\embed{reply1,\Limg x \limg}</div>
</div>}
\answer{}{\rrurlpoint;line,513,183,303,129}{type=jsxgraphcurve}{option=color1=blue color2=red precision=32}
#endif

#if #TARGET(Ocean8)
\title{1.8 (C4)Activité Formatrice}
\statement{
# include "intro_oceanartique.inc"
<div class="wimscenter"><img src="\imagedir/graphique2.png" alt="Graphique Final"></div>
<div class="question">
Pour répondre aux 3 questions qui suivent, vous devez utiliser l'équation de la droite
 de tendance. Une utilisation du tableur est possible mais non obligatoire. Une précision à 10<sup>-2</sup> est attendue
 donc la lecture graphique permet simplement de vérifier vos résultats.
<ul><li>Si la tendance observée se maintient, quelle serait l’étendue minimale de la glace de mer en Arctique
 durant l’été 2050 ?
<div class="wimscenter">\embed{reply1,4}</div></li>
<li>Si la tendance observée se maintient, en quelle année n’y aurait-il plus de glace de mer en Arctique en été ?
<div class="wimscenter">\embed{reply2,4}</div></li>
<li>Est-il vrai que « la tendance est à une perte de 60 000 km<sup>2</sup> de banquise par an » ?
<ul class="wims_nopuce">
\for{h = 1 to 2}{<li>\embed{reply3,\h}</li>}
</ul></li>
</ul>
</div>
</div>}
\answer{Superfie de la banquise l'été 2050}{3.56}{type=numeric}{option=comma}
\answer{Année de diparition de la banquise}{2110}{type=numeric}
\answer{Perte de 60 000 km2 de banquise par an}{2;non,oui}{type=radio}{option=shuffle split }
#endif
