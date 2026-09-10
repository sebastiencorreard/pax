target=nuagemodele protocole equation choixderive outil
\language{fr}
modele analyse protocole equation protocole equation substitution choixmodele
\range{-5..5}
\author{Moise,MULLER;Julien,LYOTARD}
\email{,Julien.Lyotard@ac-dijon.fr}

\computeanswer{no}
\format{html}
\precision{100000}

\text{pro=Quel prix de vente moyen au m<sup>2</sup> peut-on prévoir en 2020 ?}

\text{enonce=Une agence immobilière francilienne a récupéré un fichier contenant l'évolution des biens vendus
 sur la période 1991 - 2012. Les prix moyens de ventes sont calculés sur l'ensemble des 20
 arrondissements de Paris. Le gérant compte analyser les données pour prévoir l'évolution des prix
 à long terme et anticiper les fluctuations dues aux spéculateurs immobiliers.
Il assurera ainsi un service de qualité à ses clients en optimisant leurs profits.}

\text{option=showToolBar=true
language=fr
customToolBar="0|40"
width=900
height=650
file=prixloyer.ggb
number=1
showAlgebraInput=false
enableRightClick=false
showToolBarHelp=false
}

\text{A=<iframe scrolling="no" title="Évolution des prix des loyers" src="https://www.geogebra.org/material/iframe/id/ez592Mhv/width/900/height/650/border/888888/sfsb/true/smb/false/stb/false/stbh/false/ai/false/asb/false/sri/false/rc/false/ld/false/sdz/false/ctl/false" width="900px" height="650px" style="border:0px;"> </iframe></div>}
le OEF  
text{B=slib(geo2D/ggb2jsxgraph prixloyer.ggb,800x650,1)}

\text{derive=wims(record 0 of help/derive.txt)} 
\text{tableau=wims(record 0 of help/tableau.txt)}

#if #TARGET(nuagemodele)
\title{1.1 (C1) Série stat à 2 var - fonction et dérivation}
\statement{
<div class="encadre">
<div id="boited">
<img src="\imagedir/speculation3.jpg" alt="Spéculation immobilière" />
</div>
<p class="problematique"> \pro</p>
<div class="enonce">\enonce </div>
<br />
Après avoir regardé les ressources dans les liens suivants, répondre aux différentes questions.
<div></div>
<div class="wimscenter">\special{help derive, Ressource 1}
\special{help tableau, Ressource 2}
\special{help geogebra, Ressource 3}
</div>
<br />
<div class="question">
Comment appelle-t-on ces groupements de points ?<br />
<div class="wimscenter">\embed{reply1}</div>
Faire correspondre à chaque modèle le type de fonction utilisée et l'analyse adéquat.
<table class="wimscenter wimsborder" style="width:1000px">
<tr>
<th></th>
<th>Fonction associée</th>
<th>Analyse du modèle</th>
</tr>
<tr>
<th>Modèle 1</th>
<td>\embed{reply2,400x100x1}</td>
<td>\embed{reply3,400x100x1}</td>
</tr>
<tr>
<th>Modèle 2</th>
<td>\embed{reply4,400x100x1}</td>
<td>\embed{reply5,400x100x1}</td>
</tr>
<tr>
<th>Modèle 3</th>
<td>\embed{reply6,400x100x1}</td>
<td>\embed{reply7,400x100x1}</td>
</tr>
</table>
</div>
<div style="padding-left:70%;"><img src="\imagedir/attention.png" alt="Attention" />
<b>Penser à transmettre le(s) fichier(s) réalisés à l'enseignant.</b></div>
</div>}

\answer{Groupements points}{2;une ligne de points,un nuage de points,un groupement de points,un alignement de points}{type=checkbox}{option=shuffle eqweight split}
\answer{Fonction Modèle 1}{Fonction affine;Fonction inverse,Fonction carrée,Fonction cube,Fonction linéaire}{type=clickfill}{option=split shuffle}
\answer{Analyse Modèle 1}{Malgré quelques variations\(,) le prix au m<sup>2</sup> des appartements franciliens augmente régulièrement depuis 20 ans.; Après une baisse qui a duré presque 5 ans\(,) l'envolée des prix que l'on subit depuis 1996 semble ne pas vouloir s'arrêter., Les prix vont continuer à croître\(,) mais de moins en moins rapidement pour finir par stagner aux alentours de 2020.}{type=clickfill}{option=split shuffle} 
\answer{Fonction Modèle 2}{Fonction carrée}{type=clickfill}{option=split shuffle}
\answer{Analyse Modèle 2}{Après une baisse qui a duré presque 5 ans\(,) l'envolée des prix que l'on subit depuis 1996 semble ne pas vouloir s'arrêter.}{type=clickfill}{option=split shuffle} 
\answer{Fonction Modèle 3}{Fonction cube}{type=clickfill}{option=split shuffle}
\answer{Analyse Modèle 3}{Les prix vont continuer à croître\(,) mais de moins en moins rapidement pour finir par stagner aux alentours de 2020.}{type=clickfill}{option=split shuffle} 

\help{
\if{ \help_subject issametext derive}{\derive}
\if{ \help_subject issametext tableau}{
<div style="border: 2px solid var(--wims_bgcolor);margin:10px;padding:30px;border-radius 0px 0px 40px 40px;text-align: justify;line-height: 2em;background-color: var(--wims_ref_bgcolor);text-indent: 0px;">
<h2 class="wimscenter">Prix au m<sup>2</h2>
Après une petite recherche sur internet, on trouve le tableau suivant :
<a href="\imagedir/Tableau.ods">Évolution des prix au m<sup>2</sup></a> <br />
Prix au m<sup>2</sup> des appartements anciens par arrondissement<br />
Appartements anciens vendus libre de gré à gré en pleine propriété <br />
Indices Notaires INSEE à base trimestrielle.
<br />&nbsp;&nbsp;<span style="font-weight:bold; text-decoration:underline">Source :</span> 
<a href=" http://www.base-bien.com" target="wims_external">Base-bien.com</a>
</div>
}
\if{ \help_subject issametext geogebra}{
<div style="border: 2px solid var(--wims_bgcolor);margin:10px;padding:30px;border-radius 0px 0px 40px 40px;text-align: justify;line-height: 2em;background-color: var(--wims_ref_bgcolor);text-indent: 0px;">
<h2 class="wimscenter">Modélisation des données</h2>
\A
</div>}}
#endif

#if #TARGET(protocole)
\title{1.2 (C2 et C4) Série stat à 2 var - fonction et dérivation}
\statement{
<div class="encadre">
<div id="boited">
<img src="\imagedir/speculation3.jpg" alt="Spéculation immobilière" />
</div>
<p class="problematique"> \pro</p>
<div class="enonce">\enonce </div>
<br />
Après avoir regardé les ressources dans les liens suivants, répondre aux différentes questions.
<div></div>
<div class="wimscenter">\special{help derive, Ressource 1}
\special{help tableau, Ressource 2}
\special{help geogebra, Ressource 3}
</div>
<br />
<div class="question">
Proposer un protocole qui permet de vérifier les données du modèle 1. <br/>
<div class="wimscenter">\embed{reply1}</div>
<br/>
<div style="padding-left:70%;"><img src="\imagedir/Appel.jpg" alt="Appel" /><span style="font-weight:bold; text-decoration:underline">Appel 1 :</span>
 Présenter votre réponse à l'enseignant.</div>
</div>
<div style="padding-left:70%;"><img src="\imagedir/attention.png" alt="Attention" />
<b>Penser à transmettre le(s) fichier(s) réalisés à l'enseignant.</b></div>
</div>}

\answer{}{\kgkgg}{type=symtext}{option= nopunct nocs nomath noparentheses noquote}
\condition{Pour vérifier la cohérence de l'équation du modèle 1\(,) on réalise un nuage de points puis la droite de tendance. On détermine ainsi l'équation de la droite}
{nuage de points isin \kgkgg and (courbe de tendance isin \kgkgg or droite de tendance isin \kgkgg) and équation isin \kgkgg}

\help{ 
\if{ \help_subject issametext derive}{\derive}
\if{ \help_subject issametext tableau}{
<div style="border: 2px solid var(--wims_bgcolor);margin:10px;padding:30px;border-radius 0px 0px 40px 40px;text-align: justify;line-height: 2em;background-color: var(--wims_ref_bgcolor);text-indent: 0px;">
<h2 class="wimscenter">Prix au m<sup>2</h2>
Après une petite recherche sur internet, on trouve le tableau suivant :
<a href="\imagedir/Tableau.ods">Évolution des prix au m<sup>2</sup></a> <br />
Prix au m<sup>2</sup> des appartements anciens par arrondissement<br />
Appartements anciens vendus libre de gré à gré en pleine propriété <br />
Indices Notaires - INSEE à base trimestrielle.
<br />&nbsp;&nbsp;<span style="font-weight:bold; text-decoration:underline">Source :</span> <a href=" http://www.base-bien.com" target="wims_external">Base-bien.com</a>
</div>}
\if{ \help_subject issametext geogebra}{
<div style="border: 2px solid var(--wims_bgcolor);margin:10px;padding:30px;border-radius 0px 0px 40px 40px;text-align: justify;line-height: 2em;background-color: var(--wims_ref_bgcolor);text-indent: 0px;">
<h2 class="wimscenter">Modélisation des données</h2>
\A
</div>}}
#endif
#if #TARGET(equation)
\title{1.3 (C4 et C3) Série stat à 2 var - fonction et dérivation}
\statement{
<div class="encadre">
<div id="boited">
<img src="\imagedir/speculation3.jpg" alt="Spéculation immobilière" />
</div>
<p class="problematique"> \pro</p>
<div class="enonce">\enonce </div>
<div class="enonce">Le protocole défini à la question précédente est le suivant : 
<ul><li>Réaliser le nuage de points</li>
<li>Déterminer la droite de tendance</li>
<li>Afficher l'équation de la droite</li></ul>
</div>
<br />
Après avoir regardé les ressources dans les liens suivants, répondre aux différentes questions.
<div></div>
<div class="wimscenter">\special{help derive, Ressource 1}
\special{help tableau, Ressource 2}
\special{help geogebra, Ressource 3}
</div>
<br />
<div class="question">
Donner le résultat obtenu à l'aide du protocole avec les coefficients arrondis au centième : <br />
<div class="wimscenter">\embed{reply1,30}</div>
<br />
Si la tendance perdure, déterminer le prix au m<sup>2</sup> prévu au trimestre 2 de l'année 2020.
 Arrondir la valeur au centième. 
<div class="wimscenter">\embed{reply2,30}</div>
</div>
<div style="padding-left:70%;"><img src="\imagedir/attention.png" alt="Attention" />
<b>Penser à transmettre le(s) fichier(s) réalisés à l'enseignant.</b></div>
</div>}

\answer{}{y=73.30x+1424.45}{type=equation}{option= nopunct nocs nomath noparentheses noquote}
\answer{}{10073.85}{type=numeric}{option= nopunct nocs nomath noparentheses noquote}
\help{ 
\if{ \help_subject issametext derive}{\derive}
\if{ \help_subject issametext tableau}{
<div style="border: 2px solid var(--wims_bgcolor);margin:10px;padding:30px;border-radius 0px 0px 40px 40px;text-align: justify;line-height: 2em;background-color: var(--wims_ref_bgcolor);text-indent: 0px;">
<h2 class="wimscenter">Prix au m<sup>2</h2>
Après une petite recherche sur internet, on trouve le tableau suivant :
<a href="\imagedir/Tableau.ods">Évolution des prix au m<sup>2</sup></a> <br />
Prix au m<sup>2</sup> des appartements anciens par arrondissement<br />
Appartements anciens vendus libre de gré à gré en pleine propriété <br />
Indices Notaires - INSEE à base trimestrielle.
<br />&nbsp;&nbsp;<span style="font-weight:bold; text-decoration:underline">Source :</span> <a href=" http://www.base-bien.com" target="wims_external">Base-bien.com</a>
</div>}
\if{ \help_subject issametext geogebra}{
<div style="border: 2px solid var(--wims_bgcolor);margin:10px;padding:30px;border-radius 0px 0px 40px 40px;text-align: justify;line-height: 2em;background-color: var(--wims_ref_bgcolor);text-indent: 0px;">
<h2 class="wimscenter">Modélisation des données</h2>
\A
</div>}}
#endif

#if #TARGET(choixderive)
\title{1.4 (C2) Série stat à 2 var - fonction et dérivation}
\function{f=-0.017x³+3.91x²-152.58x+4205.82}
\function{fp = diff(\f,x)}
\statement{
<div class="encadre">
<div id="boited">
<img src="\imagedir/speculation3.jpg" alt="Spéculation immobilière" />
</div>
<p class="problematique"> \pro</p>
<div class="enonce">\enonce </div>
<br />
Après avoir regardé les ressources dans les liens suivants, répondre aux différentes questions.
<br /><br />
<div class="wimscenter">\special{help derive, Ressource 1}
\special{help tableau, Ressource 2}
\special{help geogebra, Ressource 3}
</div>
<br />
<div class="question">
Quel est le modèle le plus simple à utiliser ?
<ul>
\for{h = 1 to 3}{<li>\embed{reply1,\h}</li>}
</ul>
Quel est le modèle qui semble être le plus proche des variations de prix ?
<ul>
\for{h = 1 to 3}{<li>\embed{reply2,\h}</li>}
</ul>
</div>
<div class="enonce">
L'agence immobilière utilise le modèle 3 pour établir ses prévisions. Afin de cibler les
spéculateurs immobiliers, elle cherche à connaître la période pendant laquelle les prix ont le
plus augmenté.
</div>
<div class="question">
<p>Le modèle mathématique utilisé est la fonction \(f(x)=\f).</p>
Déterminer la fonction dérivée de \(f(x)) :
<div class="wimscenter">\(f'(x)=)\embed{reply3,30}</div>
</div>
<div style="padding-left:70%;"><img src="\imagedir/attention.png" alt="Attention" />
<b>Penser à transmettre le(s) fichier(s) réalisés à l'enseignant.</b></div>
</div>}

\answer{Modèle le plus simple :}{\tata;Modèle 1, Modèle 2,Modèle 3}{type=radio}{option=shuffle split}
\answer{Modèle proche réalité :}{\toto;Modèle 1, Modèle 2,Modèle 3}{type=radio}{option=shuffle split}
\answer{Fonction dérivée}{\fp}{type = formal}
\help{ 
\if{ \help_subject issametext derive}{\derive}
\if{ \help_subject issametext tableau}{
<div style="border: 2px solid var(--wims_bgcolor);margin:10px;padding:30px;border-radius 0px 0px 40px 40px;text-align: justify;line-height: 2em;background-color: var(--wims_ref_bgcolor);text-indent: 0px;">
<h2 class="wimscenter">Prix au m<sup>2</h2>
Après une petite recherche sur internet, on trouve le tableau suivant :
<a href="\imagedir/Tableau.ods">Évolution des prix au m<sup>2</sup></a> <br />
Prix au m<sup>2</sup> des appartements anciens par arrondissement<br />
Appartements anciens vendus libre de gré à gré en pleine propriété <br />
Indices Notaires - INSEE à base trimestrielle.
<br />&nbsp;&nbsp;<span style="font-weight:bold; text-decoration:underline">Source :</span> <a href=" http://www.base-bien.com" target="wims_external">Base-bien.com</a>
</div>}
\if{ \help_subject issametext geogebra}{
<div style="border: 2px solid var(--wims_bgcolor);margin:10px;padding:30px;border-radius 0px 0px 40px 40px;text-align: justify;line-height: 2em;background-color: var(--wims_ref_bgcolor);text-indent: 0px;">
<h2 class="wimscenter">Modélisation des données</h2>
\A
</div>}}
#endif
#if #TARGET(outil)
\title{1.5 (C2 C3 et C4) Série stat à 2 var - fonction et dérivation}
\function{f=-0.017x³+3.91x²-152.58x+4205.82}
\function{fp = diff(\f,x)}
\statement{
<div class="encadre">
<div id="boited">
<img src="\imagedir/speculation3.jpg" alt="Spéculation immobilière" />
</div>
<p class="problematique"> \pro</p>
<div class="enonce">\enonce </div>
<div class="enonce">
Afin de cibler les 
spéculateurs immobiliers, il cherche à connaître la période pendant laquelle les prix ont le
plus augmenter.
<p>Le modèle mathématique utilisé est la fonction \(f(x)=\f).
<br />
La dérivée de la fonction f est donnée par : \(f'(x)=\fp)
</p>
</div>
<br />
Après avoir regardé les ressources dans les liens suivants, répondre aux différentes questions.
<br /><br />
<div class="wimscenter">\special{help derive, Ressource 1}
\special{help tableau, Ressource 2}
\special{help geogebra, Ressource 3}
</div>
<br />
<div class="question">
Déterminer la valeur de x pour laquelle la dérivée est maximale.    x= \embed{reply1,10}
<br />
<br />
En déduire l'année où les spéculateurs étaient le plus nombreux :   \embed{reply2,10}
<br />
<br />
Calculer le prix prévu par l'agence immobilière au 2<sup>e</sup> trimestre de l'annnée 2020. Arrondir à l'unité.
<div class="wimscenter">\embed{reply3,10}</div>
</div>
<div style="padding-left:70%;"><img src="\imagedir/attention.png" alt="Attention" />
<b>Penser à transmettre le(s) fichier(s) réalisés à l'enseignant.</b></div>
</div>}

\answer{Valeur de x pour f'max :}{74.7,78.6,76.67}{type=range}
\answer{Année spéculation importante :}{2009|2010}{type=nocase}
\answer{Prix au 2<sup>e>/sup>trimestre 2020 :}{9189}{type=numeric}
\help{ 
\if{ \help_subject issametext derive}{\derive}
\if{ \help_subject issametext tableau}{
<div style="border: 2px solid var(--wims_bgcolor);margin:10px;padding:30px;border-radius 0px 0px 40px 40px;text-align: justify;line-height: 2em;background-color: var(--wims_ref_bgcolor);text-indent: 0px;">
<h2 class="wimscenter">Prix au m<sup>2</h2>
Après une petite recherche sur internet, on trouve le tableau suivant :
<a href="\imagedir/Tableau.ods">Évolution des prix au m<sup>2</sup></a> <br />
Prix au m<sup>2</sup> des appartements anciens par arrondissement<br />
Appartements anciens vendus libre de gré à gré en pleine propriété <br />
Indices Notaires - INSEE à base trimestrielle.
<br />&nbsp;&nbsp;<span style="font-weight:bold; text-decoration:underline">Source :</span> <a href=" http://www.base-bien.com" target="wims_external">Base-bien.com</a>
</div>}
\if{ \help_subject issametext geogebra}{
<div style="border: 2px solid var(--wims_bgcolor);margin:10px;padding:30px;border-radius 0px 0px 40px 40px;text-align: justify;line-height: 2em;background-color: var(--wims_ref_bgcolor);text-indent: 0px;">
<h2 class="wimscenter">Modélisation des données</h2>
\A
</div>}}
#endif
