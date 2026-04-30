target=abc ordonne efonction ederive
\language{fr}
\range{-5..5}
\author{Laurent,Gallien;Julien,Lyotard;Moïse,Muller;Jean-Luc,Pernette;Irem de Dijon}
\email{Julien.Lyotard@ac-dijon.fr}
ordonne  etudefonction etudederive
\computeanswer{no}
\format{html}
\precision{100000}

\text{pro=LA VIDÉO PROPOSÉE EST-ELLE TRUQUÉE ?}
\text{pro1=QUELLE SERA LA HAUTEUR MAXIMALE DU SAUT SI ON RESPECTE LES LOIS DE LA PHYSIQUE ?}

\text{enonce=La trajectoire du saut pourrait donc être une courbe parabolique
 définie par la fonction :
<br />
<div class="wimscenter">\(f(x)) = – 0,01x<sup>2</sup>+ 0,58x + 5.9 sur l'intervalle [ 0 ; 70 ]</div>}

\text{ordonne=Compléter un tableau de valeurs, Construire la représentation graphique,
 Déterminer les variation de la fonction, Compléter un tableau de variations, Conclure}
\text{size=150x60x1}
text{geo=<iframe scrolling="no" src="http://tube.geogebra.org/material/iframe/id/98031/width/1050/height/598/border/888888/rc/false/ai/true/sdz/false/smb/false/stb/false/stbh/true/ld/false/sri/true/at/preferhtml5" width="1050px" height="598px" style="border:0px;"> </iframe>}
\text{geo=<iframe scrolling="no" title="" src="https://www.geogebra.org/material/iframe/id/yVSWrGBf/width/1050/height/598/border/888888/sfsb/true/smb/false/stb/false/stbh/false/ai/false/asb/false/sri/false/rc/false/ld/false/sdz/false/ctl/false" width="1050px" height="598px" style="border:0px;"> </iframe>}
text{blabla=\special{help problematique, Problématique}}


#if #TARGET(abc)
\title{2.1 Coefficient}
\statement{
<div class="encadre">
<div id="haut"><div class="wimscenter">
<img src="\imagedir/panorama1.png" alt="Saut de ouf !" /></div>
</div>
<p class="problematique"> \pro</p>
<div class="wimscenter"><a class="bouton" \special{help problematique, Problématique}</a></div>
<div class="enonce">Les ressources suivantes sont mises à disposition.
 <br />
<div class="wimscenter"><a class="bouton" \special{help videotableur, Vidéo Open Office}</a>
<a class="bouton" \special{help videogeogebra, Vidéo GeoGebra}</a>
</div>
<br />

<div class="question">
<div class="wimscenter">
\geo
</div>
<br />
Déterminer les valeurs de a, b et c en déplaçant les curseurs pour que la courbe représentative
 de la fonction f correspond à la trajectoire du saut.
<div class="wimscenter">a = \embed{reply1,4}    b =\embed{reply2,4}    c = \embed{reply3,4}</div>
<br />
Les lois de la mécanique sont-elles respectées ? \embed{reply4,1} \embed{reply4,2}
<br />
La vidéo est-elle truquée ? \embed{reply5,1} \embed{reply5,2}
<br />
Pourquoi ?
<div class="wimscenter">\embed{reply6}</div>
</div>
</div>}
\answer{a}{-0.01}{type=numeric}
\answer{b}{0.57,0.61,0.58}{type=range}{option= nonstop}
\answer{c}{4.5,7,5.9}{type=range}{option= nonstop}

\answer{Lois de la mécanique}{2;Oui,Non}{type=radio}{option=shuffle split nonstop noanalyzeprint}
\answer{Vidéo truquée}{1;Oui,Non}{type=radio}{option=shuffle split nonstop noanalyzeprint}
\answer{}{\kgkgg}{type=symtext}{option= nopunct nocs nomath noparentheses noquote}
\condition{La trajectoire réalisée par le sauteur n'est pas parabolique.}{courbe représentative de la fonction f isin \kgkgg or parabole isin \kgkgg or parabolique isin \kgkgg}
#endif

#if #TARGET(ordonne)
\title{2.2 Méthode de résolution}
\statement{
<div class="encadre">
<div id="haut"><div class="wimscenter">
<img src="\imagedir/panorama1.png" alt="Saut de ouf !" /></div>
</div>
<p class="problematique"> \pro1</p>
<div class="wimscenter"><a class="bouton" \special{help problematique, Problématique}</a></div>
<div class="enonce">\enonce </div>
<br/>
Les ressources suivantes sont mises à disposition.
 <br />
<div class="wimscenter"><a class="bouton" \special{help videotableur, Vidéo Open Office}</a>
<a class="bouton" \special{help videogeogebra, Vidéo GéoGébra}</a>
</div>
 <br /><br/>
<div class="question">
<div class="wimscenter">
\geo
</div>
<br />
Ordonner les différentes propositions pour réaliser une étude de fonction :

<table class="wimscenter wimsborder" style="width:1000px;">
<tr>
<td style="text-align: center;">1<sup>er</sup> étape</td>
<td style="text-align: center;">2<sup>e</sup> étape</td>
<td style="text-align: center;">3<sup>e</sup> étape</td>
<td style="text-align: center;">4<sup>e</sup> étape</td>
<td style="text-align: center;">5<sup>e</sup> étape</td>
</tr>
<tr>
<td style="text-align: center;">\embed{reply1,\size}</td>
<td style="text-align: center;">\embed{reply2,\size}</td>
<td style="text-align: center;">\embed{reply3,\size}</td>
<td style="text-align: center;">\embed{reply4,\size}</td>
<td style="text-align: center;">\embed{reply5,\size}</td>
</tr>
</table>
</div>
</div>}
\answer{}{Réaliser un tableau de valeurs}{type=dragfill}
\answer{}{Construire la représentation graphique}{type=dragfill}
\answer{}{Déterminer les variation de la fonction}{type=dragfill}
\answer{}{Compléter un tableau de variations}{type=dragfill}
\answer{}{Conclure}{type=dragfill}
#endif

#if #TARGET(efonction)
\title{2.3 Étude de fonction}
\statement{
<div class="encadre">
<div id="haut"><div class="wimscenter">
<img src="\imagedir/panorama1.png" alt="Saut de ouf !" /></div>
</div>
<p class="problematique"> \pro1</p>
<div class="wimscenter"><a class="bouton" \special{help problematique, Problématique}</a></div>
<div class="enonce">\enonce </div>
<br/>
Les ressources suivantes sont mises à disposition.
 <br />
<div class="wimscenter"><a class="bouton" \special{help videotableur, Vidéo Open Office}</a>
<a class="bouton" \special{help videogeogebra, Vidéo GéoGébra}</a>
</div>
 <br /><br/>
<div class="question">
<div class="wimscenter">
\geo
</div>
<br />
Déterminer les variations de la fonction f.
<ul><li>La fonction f est \embed{reply1,10} sur l'intervalle [ \embed{reply2,4} ; \embed{reply3,4}].</li>
<li>La fonction f est \embed{reply4,10} sur l'intervalle [ \embed{reply5,4} ; \embed{reply6,4} ].</li>
</ul>
Construire le tableau de variations.
<table class="tabvariation">
<tr>
<td> \(x)</td><td>\embed{reply7,4}</td>
<td></td>
<td>\embed{reply8,4}</td><td></td>
<td>\embed{reply9,4}</td>
</tr>
<tr>
<td >\(f(x))</td><td> \embed{reply10,4} </td>
<td> \embed{reply11} </td>
<td>\embed{reply12,4}</td><td> \embed{reply13} </td>
<td> \embed{reply14,4} </td>
</tr>
</table>
Déterminer la hauteur du saut : \embed{reply15,4} m.
<br />
La valeur trouvée est-elle précise ?  \embed{reply16,1} \embed{reply16,2}
</div>
</div>}
\answer{}{croissante}{type=atext}
\answer{}{0}{type=numeric}
\answer{}{28,32,30}{type=range}
\answer{}{décroissante}{type=atext}
\answer{}{28,32,30}{type=range}
\answer{}{70}{type=numeric}

\answer{}{0}{type=numeric}
\answer{}{28,32,30}{type=range}
\answer{}{70}{type=numeric}

\answer{}{5.9}{type=numeric}
\answer{}{&#8599;;&#8600;}{type=clickfill}
\answer{}{14,14.6,14.3}{type=range}
\answer{}{&#8600;}{type=clickfill}
\answer{}{-2.5}{type=numeric}

\answer{}{14,14.6,14.3}{type=range}
\answer{Précision}{2;Oui,Non}{type=radio}{option=shuffle split nonstop noanalyzeprint}
#endif

#if #TARGET(ederive)
\title{2.4 Étude à l'aide de la fonction dérivée}
\text{code1=[[x,reply1,,reply2,,reply3;f'(x),,reply4,,reply5,,reply6], text=[Signe de,before,2] wimscenter reply=[[1,2;1,4;1,6;2,3;2,4;2,5],[2]]]}
\text{code=wims(declosing \code1)}
\text{Z=slib(function/tabsignes \code )}
\statement{
<div class="encadre">
<div id="haut"><div class="wimscenter">
<img src="\imagedir/panorama1.png" alt="Saut de ouf !" /></div>
</div>
<p class="problematique"> \pro1</p>
<div class="wimscenter"><a class="bouton" \special{help problematique, Problématique}</a></div>
<div class="enonce">\enonce </div>
<br/>
Les ressources suivantes sont mises à disposition.
 <br />
<div class="wimscenter"><a class="bouton" \special{help videotableur, Vidéo Open Office}</a>
<a class="bouton" \special{help videogeogebra, Vidéo GéoGébra}</a>
</div>
 <br /><br/>
<div class="question">
<div class="wimscenter">
\geo
</div>
<br />
Pour étudier la fonction \(f), on va étudier une autre fonction appelée <b>fonction dérivée \(f') </b> définie par :
<br />
<div class="wimscenter">\(f'(x)) = – 0,02x+ 0,58 sur l'intervalle [ 0 ; 70 ]</div>
<br />
Tracer la fonction \(f') en rentrant la fonction dans la barre de saisie de la figure ci-dessus.
<br /><br />
Résoudre l'équation \(f'(x)) =0.
<div class="wimscenter">x= \embed{reply1,4}</div>
<br />
Compléter le tableau de signes de la fonction \(f').
\special{codeinput \Z, 1,div
reply2,4,
reply3,4,
reply4,4,
reply5,4,
reply6,4,
reply7,4,
}
Compléter le tableau de signes de la fonction \(f') et de variation de la fonction \(f).
<br />
<table class="tabvariation"  style="width:800px">
<tr>
<td> \(x)</td>
<td>\embed{reply8,4}</td>
<td></td>
<td>\embed{reply9,4}</td>
<td></td>
<td>\embed{reply10,4}</td>
</tr>
<tr>
<td>\( \text{signe de }\: f'(x)\)</td>
<td></td>
<td> \embed{reply11,\size} </td>
<td>\embed{reply12,4}</td>
<td> \embed{reply13,\size} </td>
<td></td>
</tr>
<tr>
<td>\( \text{Variation de}\: f(x)\)</td>
<td>\embed{reply14,4}</td>
<td> \embed{reply15,\size} </td>
<td>\embed{reply16,4}</td>
<td> \embed{reply17,\size} </td>
<td>\embed{reply18,4}</td>
</tr>
</table>
<br />
Déterminer la corrélation entre \(f') et \(f) :
<br />
Lorsque la fonction \(f') est \embed{reply19,10}, alors la fonction \(f) est  \embed{reply20,10} sur l'intervalle [  \embed{reply21,4} ; \embed{reply22,4} ]
<br />
Lorsque la fonction \(f') est \embed{reply23,10}, alors la fonction \(f) est \embed{reply24,10} sur l'intervalle [  \embed{reply25,4} ; \embed{reply26,4} ]
<br /><br />
Conclusion :
<table class="wimscenter wimsborder" style="width:1000px">
<tr>
<td style="text-align: center;">1<sup>er</sup> étape</td>
<td style="text-align: center;">2<sup>e</sup> étape</td>
<td style="text-align: center;">3<sup>e</sup> étape</td>
<td style="text-align: center;">4<sup>e</sup> étape</td>
<td style="text-align: center;">5<sup>e</sup> étape</td>
</tr>
<tr>
<td style="text-align: center;">\embed{reply27,\size}</td>
<td style="text-align: center;">\embed{reply28,\size}</td>
<td style="text-align: center;">\embed{reply29,\size}</td>
<td style="text-align: center;">\embed{reply30,\size}</td>
<td style="text-align: center;">\embed{reply31,\size}</td>
</tr>
</table>
</div>
</div>}
\answer{}{29}{type=numeric}

\answer{}{0}{type=numeric}
\answer{}{29}{type=numeric}
\answer{}{70}{type=numeric}
\answer{}{+}{type=raw}{option=nospace}
\answer{}{0}{type=numeric}
\answer{}{-}{type=raw}{option=nospace}

\answer{}{0}{type=numeric}
\answer{}{29}{type=numeric}
\answer{}{70}{type=numeric}
\answer{}{+}{type=clickfill}
\answer{}{0}{type=numeric}
\answer{}{-}{type=clickfill}

\answer{}{5.9}{type=numeric}
\answer{}{&#8599;;&#8600;}{type=clickfill}
\answer{}{14.31}{type=numeric}
\answer{}{&#8600;}{type=clickfill}
\answer{}{-2.5}{type=numeric}

\answer{}{positive}{type=atext}
\answer{}{croissante}{type=atext}
\answer{}{0}{type=numeric}
\answer{}{29}{type=numeric}

\answer{}{négative}{type=atext}
\answer{}{décroissante}{type=atext}
\answer{}{29}{type=numeric}
\answer{}{70}{type=numeric}

\answer{}{Résoudre l'équation \(f\prime(x)=0)}{type=clickfill}
\answer{}{Déterminer le signe de \(f\prime(x)) sur les différents intervalles}{type=clickfill}
\answer{}{Compléter le tableau de signe}{type=clickfill}
\answer{}{Compléter le tableau de variations}{type=clickfill}
\answer{}{Conclure}{type=clickfill}
#endif

\help{
\if{ \help_subject issametext problematique}{
<div style="border: 2px solid #393b40;margin:10px;padding:30px;-moz-border-radius-topleft: 0;-moz-border-radius-bottomright: 0;-moz-border-radius-topright: 40px;-moz-border-radius-bottomleft: 40px;text-align: justify;line-height: 2em;background-color: #e6ebff;text-indent: 0px;">
<div class= wimscenter><h2>Problématique</h2>
<video preload="auto" width="600" height="320" poster="\imagedir/iremlp.gif" controls="controls" style="width: 50 %;padding:  15px; margin: 0px; border: 5px solid black; border-radius: 15px; box-shadow: 10px 10px 5px gray; box-sizing: border-box;">
<source src="https://tube-sciences-technologies.apps.education.fr/download/videos/d7add2d8-4d42-4fc3-ae26-4a744e8417ed-224.mp4" type="video/mp4">
Your browser does not support HTML5 video.
</video>
<br />
</div>
</div>}
\if{ \help_subject issametext videotableur}{
<div style="border: 2px solid #393b40;margin:10px;padding:30px;-moz-border-radius-topleft: 0;-moz-border-radius-bottomright: 0;-moz-border-radius-topright: 40px;-moz-border-radius-bottomleft: 40px;text-align: justify;line-height: 2em;background-color: #e6ebff;text-indent: 0px;">
<div class= wimscenter><h2>Réaliser un tableau de valeurs</h2>
<video preload="auto" width="600" height="320" poster="\imagedir/iremlp.gif" controls="controls" style="width: 50 %;padding:  15px; margin: 0px; border: 5px solid black; border-radius: 15px; box-shadow: 10px 10px 5px gray; box-sizing: border-box;">
<source src="https://tube-sciences-technologies.apps.education.fr/download/videos/3174c974-9750-4d31-83e9-92c3f43ad9f5-768.ogv" type="video/mp4">
Your browser does not support HTML5 video.
</video>
<br /><h2>Construire la courbe représentative d'une fonction</h2>
<video preload="auto" width="600" height="320" poster="\imagedir/iremlp.gif" controls="controls" style="width: 50 %;padding:  15px; margin: 0px; border: 5px solid black; border-radius: 15px; box-shadow: 10px 10px 5px gray; box-sizing: border-box;">
<source src="https://tube-sciences-technologies.apps.education.fr/download/videos/10a4b6ad-ef82-41b0-b203-0dfe59aeba99-768.mp4" type="video/mp4">
Your browser does not support HTML5 video.
</video>
<br />
</div>
</div>}
\if{ \help_subject issametext videogeogebra}{
<div style="border: 2px solid #393b40;margin:10px;padding:30px;-moz-border-radius-topleft: 0;-moz-border-radius-bottomright: 0;-moz-border-radius-topright: 40px;-moz-border-radius-bottomleft: 40px;text-align: justify;line-height: 2em;background-color: #e6ebff;text-indent: 0px;">
<div class=wimscenter><h2>Géogébra</h2></div>
Le fichier est à télécharger pour réaliser le travail :
<a href="\imagedir/robbie_maddison_eleve.ggb">Geogebra</a> <br/>
<br />
<br />
<div class= wimscenter><h2>Construire la courbe représentative d'une fonction</h2>
<video preload="auto" width="600" height="320" poster="\imagedir/irempl.gif" controls="controls" style="width: 50 %;padding:  15px; margin: 0px; border: 5px solid black; border-radius: 15px; box-shadow: 10px 10px 5px gray; box-sizing: border-box;">
<source src="https://tube-sciences-technologies.apps.education.fr/download/videos/efa6db26-5958-42c8-b0fa-3a2499751ad0-360.mp4 type="video/mp4">
Your browser does not support HTML5 video.
</video>
<br /><h2>Réglage de la fenêtre</h2>
<source src="" type="video/mp4">
<video preload="auto" width="600" height="320" poster="\imagedir/iremlp.gif" controls="controls" style="width: 50 %;padding:  15px; margin: 0px; border: 5px solid black; border-radius: 15px; box-shadow: 10px 10px 5px gray; box-sizing: border-box;">
<source src="https://tube-sciences-technologies.apps.education.fr/download/videos/2cda0876-78b5-4445-91bb-e2e969893b50-360.ogv">
Your browser does not support HTML5 video.
</video>
<br /><h2>Réaliser un tableau de valeurs</h2>
<video preload="auto" width="600" height="320" poster="\imagedir/iremlp.gif" controls="controls" style="width: 50 %;padding:  15px; margin: 0px; border: 5px solid black; border-radius: 15px; box-shadow: 10px 10px 5px gray; box-sizing: border-box;">
<source src="https://tube-sciences-technologies.apps.education.fr/download/videos/de335f01-6d6d-428f-ad98-283c59c3fff6-720.ogv" type="video/mp4">
Your browser does not support HTML5 video.
</video>
</div>
</div>}
}
