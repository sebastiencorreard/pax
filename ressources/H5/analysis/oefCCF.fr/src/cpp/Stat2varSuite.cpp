target=demarche TIC prime2020 nature montant2001 montant2020 conc

\language{fr}
nuagemodele protocole equation choixderive outil
modele analyse protocole equation protocole equation substitution choixmodele
\range{-5..5}
\author{Julien,LYOTARD}
\email{julien.lyotard@ac-dijon.fr}

\computeanswer{no}
\format{html}
\precision{100000}

\text{pro=COMMENT ESTIMER LA PRIME D'ASSURANCE DE LA VOITURE EN 2020 ?}

\text{enonce=En consultant sur internet les bases de données de l'Institut national de la statistique
 et des études économiques (INSEE), on trouve l'évolution des primes d'assurances voitures. Le tableau
 donné en ressource présente le prix annuel de l'assurance voiture avec un prix de base de
 500 € en 2000. Elle ne tient pas compte des bonus malus que peuvent obtenir les conducteurs
 durant cette période.}

\text{suite=wims(record 0 of help/suite.txt)}

#if #TARGET(demarche)
\title{2.1 (C2) Série stat à 2 var - suites}
\statement{
<div class="encadre">
<div id="boiteg">
<img src="\imagedir/assurance.png" alt="Assurance voiture" />
</div>
<p class="problematique"> \pro</p>
<div class="enonce">\enonce </div>
<br />
Après avoir regardé les ressources dans les liens suivants, répondre aux différentes questions.
<div></div>
<div class="wimscenter"><a class="bouton" href="\imagedir/Tableau2.ods">Ressource 1</a>
\special{help suite, Ressource 2}
</div>
<br />
<div class="question">
Présenter une méthode rapide et détaillée  pour répondre à la problématique de départ.<br />
<div style="padding-left:30px;font-style:italic;font-size:10px;"><img src="\imagedir/attention.png" alt="Attention" />
 La précision et la rigueur de la démarche tiendront pour une partie importante de la notation.</div>
<div class="wimscenter">\embed{reply1,6x50}</div>
<br />
<div style="padding-left:70%;"><img src="\imagedir/Appel.jpg" alt="Appel" /><span class="bold" style="text-decoration: underline">Appel 1 :</span>
 Présenter la démarche choisie à l'examinateur.</div>
</div>
</div>}
\answer{}{\kgkgg}{type=symtext}{option= nopunct nocs nomath noparentheses noquote}
\condition{Pour estimer la prime d'assurance\(,) on réalise un <u>nuage de points</u> puis la <u>droite de tendance</u>. On détermine l'<u>équation</u> de cette droite.
 Une simple substitution de x par sa valeur en 2020 permet de déterminer le montant prévisionnel de la prime.}
{nuage de points isin \kgkgg and (courbe de tendance isin \kgkgg or droite de tendance isin \kgkgg) and équation isin \kgkgg}
\help{\if{\help_subject issametext suite}{\suite}}
#endif

#if #TARGET(TIC)
\title{2.2 (C1 et C2) Série stat à 2 var - Suites}
\statement{
<div class="encadre">
<div id="boiteg">
<img src="\imagedir/assurance.png" alt="Assurance voiture" />
</div>
<p class="problematique"> \pro</p>
<div class="enonce">\enonce </div>
<br />
Après avoir regardé les ressources dans les liens suivants, répondre aux différentes questions.
<br /><br/>
<div class="wimscenter"><a class="bouton" href="\imagedir/Tableau2.ods">Ressource 1</a>
\special{help suite, Ressource 2}
</div>
<br />
<div class="question">
Appliquer la méthode validée par le professeur.
<div style="padding-left:30px;font-style:italic;font-size:10px;"><img src="\imagedir/attention.png" alt="Attention" />
 L’autonomie de traitement de cette partie tiendra une partie importante de la notation.</div>
L'équation est de la forme : \(y=) \embed{reply1,30}
<div style="padding-left:70%"><img src="\imagedir/Appel.jpg" alt="Appel" /><span class="bold" style="text-decoration: underline">Appel 2 :</span>
 Présenter le travail réalisé. 
</div>
<div></div>
Durant les 2 appels réalisés par le candidat, l'examinateur peut être amené à proposer les protocoles de
 secours. Dans le cas où le candidat accepte, cette aide apportée engendrera une pénalité sur la notation.
 <table><tr><td><a class="bouton" href="\imagedir/Protocole1.odt">Protocole de secours n°1</a><br /></td></tr>
<tr><td><br /><a class="bouton" href="\imagedir/Protocole2.odt">Protocole de secours n°2</a><br /></td></tr>
</table>
<br />
</div>
<div style="padding-left:70%;"><img src="\imagedir/attention.png" alt="Attention" />
<b>Le fichier réalisé est à transmettre impérativement à cette étape.</b></div>
</div>
\reply1}

\answer{}{1.68x+506.21,1.68x-2853.05}{type=algexp}
\help{\if{ \help_subject issametext suite}{\suite}}
#endif

#if #TARGET(prime2020)
\title{2.3 (C3) Série stat à 2 var - suites}
\statement{
<div class="encadre">
<div id="boiteg">
<img src="\imagedir/assurance.png" alt="Assurance voiture" />
</div>
<p class="problematique"> \pro</p>
<div class="enonce">\enonce </div>
<br />
Après avoir regardé les ressources dans les liens suivants, répondre aux différentes questions.
<div></div>
<div class="wimscenter"><a class="bouton" href="\imagedir/Tableau2.ods">Ressource 1</a>
\special{help suite, Ressource 2}
</div>
<br />
<div class="enonce">Le graphique obtenu aux questions précédentes est donné ci-dessous :
<br />
<div class="wimscenter">
<img src="\imagedir/corgraph.jpg" alt="Spéculation immobilière" />
</div>
</div>
<br />
<div class="question">
Si l'évolution perdure, déterminer la prime d'assurance en 2020.
<div class="wimscenter">\embed{reply1,10} &euro;</div>
</div>
</div>}
\answer{Prime en 2020 :}{539.81}{type=numeric}
\help{\if{ \help_subject issametext suite}{\suite}}
#endif

#if #TARGET(nature)
\title{2.4 (C1) Série stat à 2 var - suites}
\statement{
<div class="encadre">
<div id="boiteg">
<img src="\imagedir/assurance.png" alt="Assurance voiture" />
</div>
<p class="problematique"> \pro</p>
<div class="enonce">\enonce </div>
<br />
Après avoir regardé les ressources dans les liens suivants, répondre aux différentes questions.
<div></div>
<div class="wimscenter"><a class="bouton" href="\imagedir/Tableau2.ods">Ressource 1</a>
\special{help suite, Ressource 2}
</div>
<br />
<div class="enonce">
On prend en compte l’évolution des risques liés au conducteur.
<ul><li>Si le conducteur a un accident dans l'année, il prend un malus
 qui correspond à une augmentation de 25 % de l'assurance.</li>
 <li>Dans le cas où le propriétaire du véhicule n'a pas d'accident dans
 l'année, le conducteur prend un bonus qui correspond à une diminution de 5 %. de l'assurance.</li></ul>
<br />
<table class="wimscenter wimsborder">
<tr><th>Première modélisation</th><th>Deuxième modélisation</th></tr>
<tr>
<td><b> Le conducteur a un accident par an.</b>
<br />
Coût de l'assurance en 2000 : <b> 500 &euro;</b>
<br />
Chaque année la prime augmente de <b>25 %</b>.
</td>
<td>
<b> Le conducteur n'a aucun accident par an.</b>
<br />
Coût de l'assurance en 2000 : <b> 500 &euro;</b>
<br />
Chaque année la prime augmente de <b>5 %</b>.
</td>
</tr>
</table>
<br />
</div>
<br />
<div class="question">
Nommer la nature de la suite pour chaque modélisation :
<ul><li>Le premier modèle engendre une suite : \embed{reply1,20} </li>
<li>Le deuxième modèle engendre une suite : \embed{reply2,20} </li></ul>
</div>
<div style="padding-left:70%;"><img src="\imagedir/attention.png" alt="Attention" />
<b>À la fin de cette étape, un fichier peut être éventuellement transmis à l'enseignant.</b></div>
</div>}
\answer{Nature de la suite du premier modèle :}{géométrique}{type=atext}
\answer{Nature de la suite du deuxième modèle :}{géométrique}{type=atext}
\help{\if{ \help_subject issametext suite}{\suite}}
#endif

#if #TARGET(montant2001)
\title{2.5 (C1) Série stat à 2 var - suites}
\statement{
<div class="encadre">
<div id="boiteg">
<img src="\imagedir/assurance.png" alt="Assurance voiture" />
</div>
<p class="problematique"> \pro</p>
<div class="enonce">\enonce </div>
<br />
Après avoir regardé les ressources dans les liens suivants, répondre aux différentes questions.
<div></div>
<div class="wimscenter"><a class="bouton" href="\imagedir/Tableau2.ods">Ressource 1</a>
\special{help suite, Ressource 2}
</div>
<br />
<div class="enonce">
On prend en compte l’évolution des risques liés au conducteur.
<ul><li>Si le conducteur a un accident dans l'année, il prend un malus
 qui correspond à une augmentation de 25 % de l'assurance.</li>
 <li>Dans le cas où le propriétaire du véhicule n'a pas d'accident dans
 l'année, le conducteur prend un bonus qui correspond à une diminution de 5 %. de l'assurance.</li></ul>
<br />
<table class="wimscenter wimsborder">
<tr><th>Première modélisation</th><th>Deuxième modélisation</th></tr>
<tr>
<td><b> Le conducteur a un accident par an.</b>
<br />
Coût de l'assurance en 2000 : <b> 500 &euro;</b>
<br />
Chaque année la prime augmente de <b>25 %</b>.
</td>
<td>
<b> Le conducteur n'a aucun accident par an.</b>
<br />
Coût de l'assurance en 2000 : <b> 500 &euro;</b>
<br />
Chaque année la prime augmente de <b>5 %</b>.
</td>
</tr>
</table>
<br />
</div>
<br />
<div class="question">
Déterminer le montant de la prime pour les deux modèles en 2001 :
<ul><li>Tarif de l'assurance avec le premier modèle : \embed{reply1,10} &euro;</li>
<li>Tarif de l'assurance avec le deuxième modèle : \embed{reply2,10} &euro;</li></ul>
</div>
<div style="padding-left:70%;"><img src="\imagedir/attention.png" alt="Attention" />
<b>À la fin de cette étape, un fichier peut être éventuellement transmis à l'enseignant.</b></div>
</div>}
\answer{Montant du premier modèle :}{625}{type=numeric}
\answer{Montant du deuxième modèle :}{475}{type=numeric}
\help{\if{ \help_subject issametext suite}{\suite}}
#endif

#if #TARGET(conc)
\title{2.6 (C2 ou TIC) Série stat à 2 var - suites}
\statement{
<div class="encadre">
<div id="boiteg">
<img src="\imagedir/assurance.png" alt="Assurance voiture" />
</div>
<p class="problematique"> \pro</p>
<div class="enonce">\enonce </div>
<br />
Après avoir regardé les ressources dans les liens suivants, répondre aux différentes questions.
<br /><br/>
<div class="wimscenter"><a class="bouton" href="\imagedir/Tableau2.ods">Ressource 1</a>
\special{help suite, Ressource 2}
</div>
<br />
<div class="enonce">
On prend en compte l’évolution des risques liés au conducteur.
<ul><li>Si le conducteur a un accident dans l'année, il prend un malus
 qui correspond à une augmentation de 25 % de l'assurance.</li>
 <li>Dans le cas où le propriétaire du véhicule n'a pas d'accident dans
 l'année, le conducteur prend un bonus qui correspond à une diminution de 5 %. de l'assurance.</li></ul>
<br />
<table class="wimscenter wimsborder">
<tr><th>Première modélisation</th><th>Deuxième modélisation</th></tr>
<tr>
<td><b> Le conducteur a un accident par an.</b>
<br />
Coût de l'assurance en 2000 : <b> 500 &euro;</b>
<br />
Chaque année la prime augmente de <b>25 %</b>.
</td>
<td>
<b> Le conducteur n'a aucun accident par an.</b>
<br />
Coût de l'assurance en 2000 : <b> 500 &euro;</b>
<br />
Chaque année la prime augmente de <b>5 %</b>.
</td>
</tr>
</table>
<br />
</div>
<br />
<div class="question">
Calculer le prix de l'assurance en 2020 :
<ul><li>L'automobilisme a un accident par an : \embed{reply1,10} &euro;</li>
<li>Le conducteur n'a pas d'accident : \embed{reply2,10} &euro;</li></ul>
</div>
<div style="padding-left:70%;"><img src="\imagedir/attention.png" alt="Attention" />
<b>À la fin de cette étape, un fichier peut être éventuellement transmis à l'enseignant.</b></div>
</div>}
\answer{Montant du premier modèle :}{43368.09}{type=numeric}
\answer{Montant du deuxième modèle :}{179.24}{type=numeric}
\help{\if{ \help_subject issametext suite}{\suite}}
#endif

#if #TARGET(montant2020)
\title{2.7 (C4) Série stat à 2 var - suites}
\statement{
<div class="encadre">
<div id="boiteg">
<img src="\imagedir/assurance.png" alt="Assurance voiture" />
</div>
<p class="problematique"> \pro</p>
<div class="enonce">\enonce </div>
<br />
Après avoir regardé les ressources dans les liens suivants, répondre aux différentes questions.
<div></div>
<div class="wimscenter"><a class="bouton" href="\imagedir/Tableau2.ods">Ressource 1</a>
\special{help suite, Ressource 2}
</div>
<br />
<div class="enonce">
On prend en compte l’évolution des risques liés au conducteur.
<ul><li>Si le conducteur a un accident dans l'année, il prend un malus
 qui correspond à une augmentation de 25 % de l'assurance.</li>
 <li>Dans le cas où le propriétaire du véhicule n'a pas d'accident dans
 l'année, le conducteur prend un bonus qui correspond à une diminution de 5 %. de l'assurance.</li></ul>
<br />
<table class="wimscenter wimsborder">
<tr><th>Première modélisation</th><th>Deuxième modélisation</th></tr>
<tr>
<td><b> Le conducteur a un accident par an.</b>
<br />
Coût de l'assurance en 2000 : <b> 500 &euro;</b>
<br />
Chaque année la prime augmente de <b>25 %</b>.
</td>
<td>
<b> Le conducteur n'a aucun accident par an.</b>
<br />
Coût de l'assurance en 2000 : <b> 500 &euro;</b>
<br />
Chaque année la prime augmente de <b>5 %</b>.
</td>
</tr>
</table>
<br />
</div>
<br />
<div class="question">
<b>Conclusion sur l'ensemble du sujet :</b>
<br />
Indiquer le facteur qui influe le plus sur le prix de l'assurance :
<ul>
\for{h = 1 to 3}{<li>\embed{reply1,\h}</li>}
</ul>
</div>
<div style="padding-left:70%;"><img src="\imagedir/attention.png" alt="Attention" />
<b>À la fin de cette étape, un fichier peut être éventuellement transmis à l'enseignant.</b></div>
</div>}
\answer{Facteur qui influence le plus le prix :}{1;Avoir un accident par an,Avoir aucun accident,Évolution des primes d'assurance selon l'inflation}{type=radio}{option=shuffle split}
\help{\if{ \help_subject issametext suite}{\suite}}
#endif
