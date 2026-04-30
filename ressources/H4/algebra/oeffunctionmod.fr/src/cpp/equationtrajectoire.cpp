target=tableaudevaleurs representationgraphique variationfonction conclusion
\language{fr}
\range{-5..5}
\author{Laurent,Gallien;Julien,Lyotard;Moïse,Muller;Jean-Luc,Pernette;Irem de Dijon}
\email{Julien.Lyotard@ac-dijon.fr}
représentationgraphique variations tableaudevariations conclusion
\computeanswer{no}
\format{html}
\precision{100000}

\text{pro=QUELLE EST LA HAUTEUR DU SAUT DE ROBBIE MADDISON ?}

\text{enonce=La trajectoire du saut réalisé par Robbie Maddison est une courbe parabolique
 dont la fonction est définie par :
<br />
<div class="wimscenter">\(f(x)) = – 0,008x<sup>2</sup>+ 0,76x + 6 sur l'intervalle [ 0;100 ]</div>}


#if #TARGET(tableaudevaleurs)
\title{1.1 Tableau de valeurs}
\statement{
<div class="encadre">
<div id="haut"><div class="wimscenter">
<img src="\imagedir/robbie-maddison.png" alt="Saut du canal de Corinthe" /></div>
</div>
<p class="problematique"> \pro</p>
<div class="wimscenter"><a class="bouton" \special{help sautrobbie, Saut de Robbie Maddison}</a></div>
<div class="enonce">\enonce </div>
Après avoir regardé les vidéos, répondre aux différentes questions.
<br /><br/>
<div class="wimscenter"><a class="bouton" \special{help videotableur, Vidéo Open Office}</a>
<a class="bouton" \special{help videogeogebra, Vidéo GéoGébra}</a>
</div>
<br />
<div class="question">
Compléter le tableau de valeurs à l'aide d'un tableur <b>et</b> du logiciel libre GeoGebra.
<div id="tab">
<table class="tab" border="2">
<tr>
<th>\(x\)</th>
\for{uu=1 to 11}{<td>\embed{reply\uu,4}</td>}
</tr>
<tr>
<th>\(f(x)\) </th>
\for{uu=12 to 22}{<td>\embed{reply\uu,4}</td>}
</tr>
</table>
</div>
</div>
</div>}
\answer{}{0}{type=numeric}
\answer{}{10}{type=numeric}
\answer{}{20}{type=numeric}
\answer{}{30}{type=numeric}
\answer{}{40}{type=numeric}
\answer{}{50}{type=numeric}
\answer{}{60}{type=numeric}
\answer{}{70}{type=numeric}
\answer{}{80}{type=numeric}
\answer{}{90}{type=numeric}
\answer{}{100}{type=numeric}

\answer{}{6}{type=numeric}
\answer{}{12.8}{type=numeric}
\answer{}{18}{type=numeric}
\answer{}{21.6}{type=numeric}
\answer{}{23.6}{type=numeric}
\answer{}{24}{type=numeric}
\answer{}{22.8}{type=numeric}
\answer{}{20}{type=numeric}
\answer{}{15.6}{type=numeric}
\answer{}{9.6}{type=numeric}
\answer{}{2}{type=numeric}
#endif

#if #TARGET(representationgraphique)
\title{1.2 Représentation Graphique}

\matrix{nstep= reply1}
\nextstep{\nstep}
\integer{rep=(\confparm1=)?314:\confparm1}

\statement{
<div class="encadre">
<div id="haut"><div class="wimscenter">
<img src="\imagedir/robbie-maddison.png" alt="Saut du canal de Corinthe" /></div>
</div>
<p class="problematique"> \pro</p>
<div class="wimscenter"><a class="bouton" \special{help sautrobbie, Saut de Robbie Maddison}</a></div>
<div class="enonce">\enonce </div>
Après avoir regardé les vidéos, répondre aux différentes questions.
<br /><br/>
<div class="wimscenter"><a class="bouton" \special{help videotableur, Vidéo Open Office}</a>
<a class="bouton" \special{help videogeogebra, Vidéo GéoGébra}</a>
</div>
<br />
<div class="question">
Réaliser la représentation graphique de cette fonction à l'aide d'un tableur
 <b>et</b> du logiciel libre GeoGebra.
 <br />
\if{\step=1}{<div class="wimscenter">
\embed{reply1,20
type="password"}</div>}{}
<br /> <img src="\imagedir/Appel.jpg" alt="Appel" /><span class="bold" style="text-decoration: underline">Appel 1 :</span>
Présenter vos graphiques à l'enseignant pour qu'il valide cette étape.
</div>
</div>}
\answer{Validation enseignant}{\rep}{type=numeric}{option=noanalyzeprint nonstop}
\text{nstep=(\step=2)?}
#endif

#if #TARGET(variationfonction)
\title{1.3 Variations et tableau de variations de la fonction}
\statement
{
<div class="encadre">
<div id="haut"><div class="wimscenter">
<img src="\imagedir/robbie-maddison.png" alt="Saut du canal de Corinthe" /></div>
</div>
<p class="problematique"> \pro</p>
<div class="wimscenter"><a class="bouton" \special{help sautrobbie, Saut de Robbie Maddison}</a></div>
<div class="enonce">\enonce </div>
Après avoir regardé les vidéos, répondre aux différentes questions.
<br /><br/>
<div class="wimscenter"><a class="bouton" \special{help videotableur, Vidéo Open Office}</a>
<a class="bouton" \special{help videogeogebra, Vidéo GéoGébra}</a>
</div>
<br />
<div class="question">
Déterminer les variations de la fonction f.
<ul><li>La fonction f est \embed{reply1,10} sur l'intervalle [ \embed{reply2,4} ; \embed{reply3,4}].</li>
<li>La fonction f est \embed{reply4,10} sur l'intervalle [ \embed{reply5,4} ; \embed{reply6,4} ].</li>
</ul>
Compléter le tableau de variations.
<table class="tabvariation">
<tr>
<td> \(x)</td><td>\embed{reply7,4}</td>
<td></td>
<td>\embed{reply8,4}</td><td></td>
<td>\embed{reply9,4}</td>
</tr>
<tr>
<td>\(f(x))</td><td> \embed{reply10,4} </td>
<td> \embed{reply11,78x18} </td>
<td>\embed{reply12,4}</td><td> \embed{reply13,78x18} </td>
<td> \embed{reply14,4}</td>
</tr>
</table>
</div>}
\answer{}{croissante}{type=atext}
\answer{}{0}{type=numeric}
\answer{}{45,50,47.5}{type=range}
\answer{}{décroissante}{type=atext}
\answer{}{45,50,47.5}{type=range}
\answer{}{100}{type=numeric}

\answer{}{0}{type=numeric}
\answer{}{45,50,47.5}{type=range}
\answer{}{100}{type=numeric}

\answer{}{6}{type=numeric}
\answer{}{&#8599;;&#8600;}{type=clickfill}
\answer{}{24,24.43,24.428}{type=range}
\answer{}{&#8600;}{type=clickfill}
\answer{}{2}{type=numeric}
#endif

#if #TARGET(conclusion)
\title{1.4 Conclusion}
\statement{
<div class="encadre">
<div id="haut"><div class="wimscenter">
<img src="\imagedir/robbie-maddison.png" alt="Saut du canal de Corinthe" /></div>
</div>
<p class="problematique"> \pro</p>
<div class="wimscenter"><a class="bouton" \special{help sautrobbie, Saut de Robbie Maddison}</a></div>
<div class="enonce">\enonce </div>
Après avoir regardé les vidéos, répondre aux différentes questions.
<br /><br/>
<div class="wimscenter"><a class="bouton" \special{help videotableur, Vidéo Open Office}</a>
<a class="bouton" \special{help videogeogebra, Vidéo GéoGébra}</a>
</div>
<br />
<div class="question">
Conclusion :
<ul><li>Quelle est la hauteur du saut de Robbie par rapport au sol ?
<br />
<div class="wimscenter">\embed{reply1,4}</div>
</li>
<li>Le canal de Corinthe a une profondeur de 52 m. Quelle est la hauteur du saut par rapport à l'eau ?
<br />
<div class="wimscenter">\embed{reply2,4}</div>
</li>
</ul>
</div>
</div>}
\answer{}{24,24.43,24.428}{type=range}
\answer{}{76,76.43,76.428}{type=range}
#endif

\help{
\if{ \help_subject issametext sautrobbie}{
<div style="border: 2px solid #393b40;margin:10px;padding:30px;-moz-border-radius-topleft: 0;-moz-border-radius-bottomright: 0;-moz-border-radius-topright: 40px;-moz-border-radius-bottomleft: 40px;text-align: justify;line-height: 2em;background-color: #e6ebff;text-indent: 0px;">
<div class= wimscenter><h2>Saut de Robbie par les médias</h2>
<video preload="auto" width="600" height="320" poster="\imagedir/iremlp.gif" controls="controls" style="width: 50 %;padding:  15px; margin: 0px; border: 5px solid black; border-radius: 15px; box-shadow: 10px 10px 5px gray; box-sizing: border-box;">
<source src="https://tube-sciences-technologies.apps.education.fr/download/videos/8433d3d3-91f1-4b7e-a07c-98c673ddd6cd-720.mp4" type="video/mp4">
Your browser does not support HTML5 video.
</video>
<br /><h2>Saut de Robbie fimé par un amateur</h2>
<video preload="auto" width="600" height="320" poster="\imagedir/iremlp.gif" controls="controls" style="width: 50 %;padding:  15px; margin: 0px; border: 5px solid black; border-radius: 15px; box-shadow: 10px 10px 5px gray; box-sizing: border-box;">
<source src="https://tube-sciences-technologies.apps.education.fr/download/videos/498a81c2-7e86-4876-848c-162bac4c088c-360.mp4" type="video/mp4">
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
