target=tauxalcoolemie
\language{fr}
\author{Laurent,Gallien;Julien,Lyotard;Moïse,Muller;Jean-Luc,Pernette;Irem de Dijon}
\email{Julien.Lyotard@ac-dijon.fr}

#if #TARGET(tauxalcoolemie)
\title{Soirée trop arrosée}
\computeanswer{no}
\range{-5..5}

\format{html}
\precision{100000}

\matrix{nstep= reply1,reply2,reply3}
\nextstep{\nstep}

\real{tam=}
\real{aa=}
\function{ff=}
\text{flate=}
\function{ffp=}
\text{mm=}
\integer{yym=}
\text{AA=}
\real{gg=}
\text{lnv= wims(makelist x for x = 1 to 20)}
\text{ltv= wims(values x,x+0.5 for x = 0 to 7)}
\text{lltv=}
\text{llltv=}
\real{r=}
\real{rr=}
\real{r1=}
\real{r2=}
\real{r3=}
\real{rre=}
\integer{rrm=}


Bout de code sympa
\text{S=wims(values \ff for t=0 to 7)}

\text{pro=UNE SOIRÉE TROP ARROSÉE ?}
\text{enonce=À l'issue d'une soirée, un élève qui a bu doit raccompagner ses copains avec sa voiture.
<br />
Avant de démarrer, un ami lui dit :
<br />
- Tu as trop bu !
<br />
- Pourtant je n'ai pas beaucoup bu ! Hic ! Hic !
<br />
- Attends j'ai une application sur mon smartphone qui me donne la courbe du taux d'alcoolémie
 en fonction du temps !
<br />
<b>Pour conduire sans être en infraction, l'alcoolémie en France doit être inférieure à 0,5 g/L.
(Alcoolémie = Masse d'alcool contenue dans un litre de sang)</b>
}
\matrix{rrep=}

\statement{
<div class="encadre">
<div id="haut"><div class="wimscenter">
<img src="\imagedir/William_Hogarth-A_Midnight_Modern_Conversation.jpg" alt="William Hogarth-A Midnight Modern Conversation" /></div>
</div>
<div id="boiteg">
<img src="\imagedir/Georg_Emanuel_Opitz_Der_Saufer_1804.jpg" alt="Georg Emanuel-Opitz Der Säufer 1804" />
</div>
<div id="boited">
<img src="\imagedir/Postcard-A_Happy_New_Year_1912.jpg" alt="Postcard-A Happy New Year 1912.jpg" />
</div>
<p class="problematique"> \pro</p>
<div class="enonce">\enonce </div>
\if{\step=1}{
<div class="question">
<div class="etape">Etape : \step sur 4</div>
Pour obtenir la courbe, l'application demande un certain nombre de renseignements.
<br />Combien de verres avez-vous bu au bar ? \embed{reply1}
<br />Quelle est votre masse corporelle ? \embed{reply2,4} en kg
<br />Êtes-vous de sexe masculin ou féminin ? \embed{reply3}
<br /></div>}
\if{\step=2}{
<div class="question">
Pour obtenir la courbe, l'application demande un certain nombre de renseignements.
<br />Combien de verres avez-vous bu au bar ? <select>
<option value="test" selected="selected">\reply1</option>
</select>
<br />Quelle est ta masse corporelle ? <input size="4" name="toto" value="\reply2" readonly /> en kg
<br />Êtes-vous de sexe masculin ou féminin ? <input type="radio" value="Homme" \if{\reply3 isin Homme}{checked="checked"} readonly />
<label>Homme</label>
<input type="radio" value="Femme" \if{\reply3 isin Femme}{checked="checked"} readonly /><label>Femme</label>
<br /></div>
La variation du taux d'alcoolémie en g/L est fonction du temps en heures. La courbe représentative
de la fonction f est donnée par le graphique ci-dessous :
<div class="wimscenter">\(f(t))=\flate sur l'intervalle [ 0 ; 7 ]</div>
\AA
<div class="question">
<div class="etape">Etape : \step sur 4</div>
Compléter le tableau suivant :
<br />
<div id="tab">
<table class="tab" border="2">
<tr>
<th style="text-align:center;">\(x\)</th>
\for{uu=1 to 15}{<td>\ltv[\uu]</td>}
</tr>
<tr>
<th style="text-align:center;">\(f(x)) </th>
<td style="text-align:center;">0</td>
<td>\llltv[2]</td>
\for{p=4 to 16}{<td>\embed{reply\p,3}</td>}
</tr>
</table>
</div>
Ce tableau s'appelle un \embed{reply17,200x20x1}.
</div>}
\if{\step=3}{
<div class="question">
Pour obtenir la courbe, l'application demande un certain nombre de renseignements.
<br />Combien de verres avez-vous bu au bar ? <select>
<option value="test" selected="selected">\reply1</option>
</select>
<br />Quelle est ta masse corporelle ? <input size="4" name="toto" value="\reply2"  readonly/> en kg
<br />Êtes-vous de sexe masculin ou féminin ? <input type="radio" value="Homme" \if{\reply3 isin Homme}{checked="checked"} readonly/>
<label>Homme</label>
<input type="radio" value="Femme" \if{\reply3 isin Femme}{checked="checked"} readonly/><label>Femme</label>
<br /></div>
La variation du taux d'alcoolémie en g/L est fonction du temps en heures. La courbe représentative
de la fonction f est donnée par le graphique ci-dessous :
<div class="wimscenter">\(f(t))=\flate sur l'intervalle [ 0 ; 7 ]</div>
\AA
Le tableau de valeurs corrigé est donné par :
<div style="overflow-x: auto;">
<table class="wimsborder wimscenter">
<tr>
<th style="text-align:center;">\(x\)</th>
\for{uu=1 to 15}{<td>\ltv[\uu]</td>}
</tr>
<tr>
<th style="text-align:center;">\(f(x)\)</th>
<td style="text-align:center;">0</td>
<td style="text-align:center;">\lltv[2]</td>
\for{p=4 to 16}{<td style="text-align:center;">
\if{abs(\rrep[\p-3]-\lltv[\p-1])<=0.02}{<span style="color:#0dff00;font-weight:bold">\llltv[\p-1]</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\rrep[\p-3]</span>&nbsp;<span style="color:#0dff00;font-weight:bold">\llltv[\p-1]</span>}
</td>
}
</tr>
</table>
</div>
<div class="question">
<div class="etape">Etape : \step sur 4</div>
Déterminer les variations de la fonction f.
<ul><li>La fonction f est \embed{reply18,200x20x1} sur l'intervalle [ \embed{reply19,4} ; \embed{reply20,4}].</li>
<li>La fonction f est \embed{reply21,200x20x1} sur l'intervalle [ \embed{reply22,4} ; \embed{reply23,4} ].</li>
</ul>
Compléter le tableau ci-dessous :
<table class="tabvariation" style="width:1000px">
<tr>
<td> \(x\)</td><td>\embed{reply24,4}</td>
<td></td>
<td>\embed{reply25,4}</td><td></td>
<td>\embed{reply26,4}</td>
</tr>
<tr>
<td>\(f(x))</td>
<td> \embed{reply27,4} </td>
<td> \embed{reply28,200x20x1} </td>
<td>\embed{reply29,4}</td>
<td> \embed{reply30,200x20x1} </td>
<td> \embed{reply31,4} </td>
</tr>
</table>
Ce tableau s'appelle un \embed{reply32,200x20x1}.
</div>}
\if{\step=4}{
<div class="question">
Pour obtenir la courbe, l'application demande un certain nombre de renseignements.
<br />Combien de verres avez-vous bu au bar ? <select>
<option value="test" selected="selected">\reply1</option>
</select>
<br />Quelle est ta masse corporelle ? <input size="4" name="toto" value="\reply2"  readonly/> en kg
<br />Êtes-vous de sexe masculin ou féminin ? <input type="radio" value="Homme" \if{\reply3 isin Homme}{checked="checked"} readonly/>
<label>Homme</label>
<input type="radio" value="Femme" \if{\reply3 isin Femme}{checked="checked"} readonly/><label>Femme</label>
<br /></div>
La variation du taux d'alcoolémie en g/L est fonction du temps en heures. La courbe représentative
de la fonction f est donnée par le graphique ci-dessous :
<div class="wimscenter">\(f(t))=\flate sur l'intervalle [ 0 ; 7 ]</div>
\AA
<br />
Le tableau de valeurs corrigé est donné par :
<div style="overflow-x: auto;">
<table class="wimsborder wimscenter">
<tr>
<th style="text-align:center;">\(x\)</th>
\for{uu=1 to 15}{<td>\ltv[\uu]</td>}
</tr>
<tr>
<th style="text-align:center;">\(f(x)\)</th>
<td style="text-align:center;">0</td>
<td style="text-align:center;">\lltv[2]</td>
\for{p=4 to 16}{<td style="text-align:center;">
\if{abs(\rrep[\p-3]-\lltv[\p-1])<=0.02}{<span style="color:#0dff00;font-weight:bold">\llltv[\p-1]</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\rrep[\p-3]</span>&nbsp;<span style="color:#0dff00;font-weight:bold">\llltv[\p-1]</span>}
</td>
}
</tr>
</table>
</div>
Le tableau de variations corrigé est donné :
<div style="overflow-x: auto;">
<table class="tabvariation">
<tr>
<td>\(x\)</td><td style="width:20%;">\if{\reply24=0}{<span style="color:#0dff00;font-weight:bold">0</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\reply24</span>&nbsp;<span style="color:#0dff00;font-weight:bold">0</span>}
</td>
<td style="width:20%;"></td>
<td style="width:20%;">
\if{\reply25=1}{<span style="color:#0dff00;font-weight:bold">1</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\reply25</span>&nbsp;<span style="color:#0dff00;font-weight:bold">1</span>}
</td><td style="width:20%;"></td>
<td style="width:20%;">
\if{\reply26=7}{<span style="color:#0dff00;font-weight:bold">7</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\reply26</span>&nbsp;<span style="color:#0dff00;font-weight:bold">7</span>}
</td>
</tr>
<tr>
<td>\(f(x)\)</td>
<td style="width:20%;">
\if{\reply27=0}{<span style="color:#0dff00;font-weight:bold">0</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\reply27</span>&nbsp;<span style="color:#0dff00;font-weight:bold">0</span>}
</td>
<td style="width:20%;">
\if{\reply28 isin &#8599;}{<span style="color:#0dff00;font-weight:bold">&#8599;</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\reply28</span>&nbsp;<span style="color:#0dff00;font-weight:bold">&#8599;</span>}
</td>
<td style="width:20%;">
\if{abs(\rep29-\lltv[3])<=0.02}{<span style="color:#0dff00;font-weight:bold">\llltv[3]</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\reply29</span>&nbsp;<span style="color:#0dff00;font-weight:bold">\llltv[3]</span>}
</td>
<td style="width:20%;">
\if{\reply30 isin &#8600;}{<span style="color:#0dff00;font-weight:bold">&#8600;</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\reply30</span>&nbsp;<span style="color:#0dff00;font-weight:bold">&#8600;</span>}
</td>
<td style="width:20%;">
\if{abs(\reply31-\lltv[15])<=0.02}{<span style="color:#0dff00;font-weight:bold">\llltv[15]</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\reply31</span>&nbsp;<span style="color:#0dff00;font-weight:bold">\llltv[15]</span>}
</td>
</tr>
</table>
</div>

<div class="question">
<div class="etape">Etape : \step sur 4</div>
Déterminer le temps où l'alcoolémie est maximal : \embed{reply33,4} heure.
<br />
Déterminer le moment où l'élève pourra prendre le volant : \embed{reply34,4} heures.
<br />
Convertir ce temps en heures et minutes : \embed{reply35,4} heures et \embed{reply36,4} minutes.
\if{\llltv[3]>2}{
<br /> Les riques de coma éthilique sont avérés lorsque le taux d'alcolémie dépasse 2g/L.
<br />Donner un intervalle en heure ou l'élève peut tomber dans le coma éthilique : [\embed{reply37,4};\embed{reply38,4}]
<br /> La durée du risque de coma éthilique est donc de : \embed{reply39,4} heures.}
</div>}
\if{\step=5}{
<div class="question">
Pour obtenir la courbe, l'application demande un certain nombre de renseignements.
<br />Combien de verres avez-vous bu au bar ? <select>
<option value="test" selected="selected">\reply1</option>
</select>
<br />Quelle est ta masse corporelle ? <input size="4" name="toto" value="\reply2"  readonly/> en kg
<br />Êtes-vous de sexe masculin ou féminin ? <input type="radio" value="Homme" \if{\reply3 isin Homme}{checked="checked"} readonly/>
<label>Homme</label>
<input type="radio" value="Femme" \if{\reply3 isin Femme}{checked="checked"} readonly/><label>Femme</label>
<br /></div>
La variation du taux d'alcoolémie en g/L est fonction du temps en heures. La courbe représentative
de la fonction f est donnée par le graphique ci-dessous :
<div class="wimscenter">\(f(t))=\flate sur l'intervalle [ 0 ; 7 ]</div>
\AA
Le tableau de valeurs corrigé est donné par :
<div style="overflow-x: auto;">
<table class="wimsborder wimscenter">
<tr>
<th style="text-align:center;">\(x\)</th>
\for{uu=1 to 15}{<td>\ltv[\uu]</td>}
</tr>
<tr>
<th style="text-align:center;">\(f(x)\)</th>
<td style="text-align:center;">0</td>
<td style="text-align:center;">\lltv[2]</td>
\for{p=4 to 16}{<td style="text-align:center;">
\if{abs(\rrep[\p-3]-\lltv[\p-1])<=0.02}{<span style="color:#0dff00;font-weight:bold">\llltv[\p-1]</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\rrep[\p-3]</span>&nbsp;<span style="color:#0dff00;font-weight:bold">\llltv[\p-1]</span>}
</td>
}
</tr>
</table>
</div>

Le tableau de variations corrigé est le suivant :
<div style="overflow-x: auto;">
<table class="tabvariation">
<tr>
<td>\(x\)</td><td style="width:20%;">\if{\reply24=0}{<span style="color:#0dff00;font-weight:bold">0</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\reply24</span>&nbsp;<span style="color:#0dff00;font-weight:bold">0</span>}
</td>
<td style="width:20%;"></td>
<td style="width:20%;">
\if{\reply25=1}{<span style="color:#0dff00;font-weight:bold">1</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\reply25</span>&nbsp;<span style="color:#0dff00;font-weight:bold">1</span>}
</td><td style="width:20%;"></td>
<td style="width:20%;">
\if{\reply26=7}{<span style="color:#0dff00;font-weight:bold">7</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\reply26</span>&nbsp;<span style="color:#0dff00;font-weight:bold">7</span>}
</td>
</tr>
<tr>
<td>\(f(x)\)</td>
<td style="width:20%;">
\if{\reply27=0}{<span style="color:#0dff00;font-weight:bold">0</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\reply27</span>&nbsp;<span style="color:#0dff00;font-weight:bold">0</span>}
</td>
<td style="width:20%;">
\if{\reply28 isin &#8599;}{<span style="color:#0dff00;font-weight:bold">&#8599;</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\reply28</span>&nbsp;<span style="color:#0dff00;font-weight:bold">&#8599;</span>}
</td>
<td style="width:20%;">
\if{abs(\rep29-\lltv[3])<=0.02}{<span style="color:#0dff00;font-weight:bold">\llltv[3]</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\reply29</span>&nbsp;<span style="color:#0dff00;font-weight:bold">\llltv[3]</span>}
</td>
<td style="width:20%;">
\if{\reply30 isin &#8600;}{<span style="color:#0dff00;font-weight:bold">&#8600;</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\reply30</span>&nbsp;<span style="color:#0dff00;font-weight:bold">&#8600;</span>}
</td>
<td style="width:20%;">
\if{abs(\reply31-\lltv[15])<=0.02}{<span style="color:#0dff00;font-weight:bold">\llltv[15]</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\reply31</span>&nbsp;<span style="color:#0dff00;font-weight:bold">\llltv[15]</span>}
</td>
</tr>
</table>
</div>
Le temps où l'alcoolémie est maximal est de
\if{\reply33=1}{<span style="color:#0dff00;font-weight:bold">1 H.</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\reply33</span>&nbsp;<span style="color:#0dff00;font-weight:bold">1 H.</span>}
<br />
L'élève pourra prendre le volant au bout de
\if{abs(\rep34-\rr)<=0.02}{<span style="color:#0dff00;font-weight:bold">\rr H</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\rep34</span>&nbsp;<span style="color:#0dff00;font-weight:bold">\rr H</span>}
soit \if{\rep35=\rre}{<span style="color:#0dff00;font-weight:bold">\rre H</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\rep35</span>&nbsp;<span style="color:#0dff00;font-weight:bold">\rre H</span>}
et \if{abs(\rep36-\rrm)<=2}{<span style="color:#0dff00;font-weight:bold">\rrm minutes.</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\rep36</span>&nbsp;<span style="color:#0dff00;font-weight:bold">\rrm minutes.</span>}
\if{\llltv[3]>2}{
<br /> Les riques de coma éthilique sont avérés lorsque le taux d'alcolémie dépasse 2g/L.
<br />L'intervalle en heure ou l'élève peut tomber dans le coma éthilique est de : &#91;
\if{abs(\rep37-\r1)<=0.02}{<span style="color:#0dff00;font-weight:bold"> \r1 ;</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through"> \rep37</span>&nbsp;<span style="color:#0dff00;font-weight:bold">\r1 ;</span>}
\if{abs(\rep38-\r2)<=0.02}{<span style="color:#0dff00;font-weight:bold">\r2 &#93;</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\rep38</span>&nbsp;<span style="color:#0dff00;font-weight:bold">\r2 &#93;</span>}
<br /> La durée du risque de coma éthilique est donc de :
\if{abs(\rep39-\r3)<=0.02}{<span style="color:#0dff00;font-weight:bold">\r3 H.</span>}
{<span style="color:red;font-weight:bold;text-decoration:line-through">\rep39</span>&nbsp;<span style="color:#0dff00;font-weight:bold">\r3 H.</span>}
}
</div>}
</div>}

\answer{}{\nv;\lnv}{type=menu}{option=noanalyzeprint}
\answer{}{\mc}{type=numeric}{option=noanalyzeprint}
\answer{}{\mf;Homme,Femme}{type=radio}{option=noanalyzeprint}

\if{\step>=2}{
\real{tam=(\mf isin Homme)?10*\nv/\mc/0.7:10*\nv/\mc/0.6}
\integer{aa=\tam/exp(-1)*100}
\real{aaa=\aa/100}
\function{ff=\aaa*t*exp(-t)}
\text{flate=\aaa t e<sup>-t</sup>}
\function{ffp=diff(\ff,t)}
\text{mm=slib(function/bounds \ff,t,0,7)}
\integer{yym=\mm[2]+1}
\real{gg=evalue(\ff,t=6)}
\text{AA=slib(geo2D/jsxgraph jsxbox,800 x 400,var brd = JXG.JSXGraph.initBoard('jsxbox',
 {axis:true, boundingbox: [-0.5,\yym,7,-0.5]});
 li=brd.create('functiongraph', [function(t){return \aaa*t*Math.exp(-t);},0,7]);
 brd.create('glider',[6,\gg,li],{name:'Bouge moi', strokeColor:'black'});
 )}
 \for{oo=0 to 7}{\real{tv=evalue(\ff,t=\oo)}
\integer{tttv=\tv*100}
\real{ttv=\tttv/100}
\real{tvv=evalue(\ff,t=\oo+0.5)}
\integer{tttvv=\tvv*100}
\real{ttvv=\tttvv/100}
\text{lltv=wims(append item \tv,\tvv to \lltv)}
\text{llltv=wims(append item \ttv,\ttvv to \llltv)}
}
\real{r1=solve(\aaa*x*exp(-x)-2,x=0..1)}
\real{r2=solve(\aaa*x*exp(-x)-2,x=1..7)}
\real{r3=\r2-\r1}
\real{rr=solve(\aaa*x*exp(-x)-0.5,x=1..7)}
\real{rre=floor(\rr)}
\integer{rrm=(\rr-\rre)*60}
}

\answer{}{\rep4}{type=numeric}{option=noanalyzeprint}
\condition{Le taux d'alcoolémie est de \llltv[3]. Votre réponse 4 est de \rep4.}{abs(\rep4-\lltv[3])<=0.02}{option=hide}
\answer{}{\rep5}{type=numeric}{option=noanalyzeprint}
\condition{Le taux d'alcoolémie est de \llltv[4]. Votre réponse 5 est de \rep5.}{abs(\rep5-\lltv[4])<=0.02}{option=hide}
\answer{}{\rep6}{type=numeric}{option=noanalyzeprint}
\condition{Le taux d'alcoolémie est de \llltv[5]. Votre réponse 6 est de \rep6.}{abs(\rep6-\lltv[5])<=0.02}{option=hide}
\answer{}{\rep7}{type=numeric}{option=noanalyzeprint}
\condition{Le taux d'alcoolémie est de \llltv[6]. Votre réponse 7 est de \rep7.}{abs(\rep7-\lltv[6])<=0.02}{option=hide}
\answer{}{\rep8}{type=numeric}{option=noanalyzeprint}
\condition{Le taux d'alcoolémie est de \llltv[7]. Votre réponse 8 est de \rep8.}{abs(\rep8-\lltv[7])<=0.02}{option=hide}
\answer{}{\rep9}{type=numeric}{option=noanalyzeprint}
\condition{Le taux d'alcoolémie est de \llltv[8]. Votre réponse 9 est de \rep9.}{abs(\rep9-\lltv[8])<=0.02}{option=hide}
\answer{}{\rep10}{type=numeric}{option=noanalyzeprint}
\condition{Le taux d'alcoolémie est de \llltv[9]. Votre réponse 10 est de \rep10.}{abs(\rep10-\lltv[9])<=0.02}{option=hide}
\answer{}{\rep11}{type=numeric}{option=noanalyzeprint}
\condition{Le taux d'alcoolémie est de \llltv[10]. Votre réponse 11 est de \rep11.}{abs(\rep11-\lltv[10])<=0.02}{option=hide}
\answer{}{\rep12}{type=numeric}{option=noanalyzeprint}
\condition{Le taux d'alcoolémie est de \llltv[11]. Votre réponse 12 est de \rep12.}{abs(\rep12-\lltv[11])<=0.02}{option=hide}
\answer{}{\rep13}{type=numeric}{option=noanalyzeprint}
\condition{Le taux d'alcoolémie est de \llltv[12]. Votre réponse 13 est de \rep13.}{abs(\rep13-\lltv[12])<=0.02}{option=hide}
\answer{}{\rep14}{type=numeric}{option=noanalyzeprint}
\condition{Le taux d'alcoolémie est de \llltv[13]. Votre réponse 14 est de \rep14.}{abs(\rep14-\lltv[13])<=0.02}{option=hide}
\answer{}{\rep15}{type=numeric}{option=noanalyzeprint}
\condition{Le taux d'alcoolémie est de \llltv[14]. Votre réponse 15 est de \rep15.}{abs(\rep15-\lltv[14])<=0.02}{option=hide}
\answer{}{\rep16}{type=numeric}{option=noanalyzeprint}
\condition{Le taux d'alcoolémie est de \llltv[15]. Votre réponse 16 est de \rep16.}{abs(\rep16-\lltv[15])<=0.02}{option=hide}
\answer{Tableau de valeurs}{tableau de valeurs;tableau de variations,tableau de comparaisons,tableau de signes}{type=clickfill}{option=noanalyzeprint nonstop}

\answer{}{croissante;}{type=clickfill}{option=noanalyzeprint nonstop}
\answer{}{0}{type=numeric}{option=noanalyzeprint nonstop}
\answer{}{1}{type=numeric}{option=noanalyzeprint nonstop}
\answer{}{décroissante;}{type=clickfill}{option=noanalyzeprint nonstop}
\answer{}{1}{type=numeric}{option=noanalyzeprint nonstop}
\answer{}{7}{type=numeric}{option=noanalyzeprint nonstop}

\answer{}{0}{type=numeric}{option=noanalyzeprint nonstop}
\answer{}{1}{type=numeric}{option=noanalyzeprint nonstop}
\answer{}{7}{type=numeric}{option=noanalyzeprint nonstop}
\answer{}{0}{type=numeric}{option=noanalyzeprint nonstop}
\answer{}{&#8599;}{type=clickfill}{option=noanalyzeprint nonstop}
\answer{}{\rep29}{type=numeric}{option=noanalyzeprint nonstop}
\condition{Le taux d'alcoolémie est de \llltv[3]. Votre réponse 29 est de \rep29.}{abs(\rep29-\lltv[3])<=0.02}{option=hide}
\answer{}{&#8600;}{type=clickfill}{option=noanalyzeprint nonstop}
\answer{}{\rep31}{type=numeric}{option=noanalyzeprint nonstop}
\condition{Le taux d'alcoolémie est de \llltv[15]. Votre réponse 31 est de \rep31.}{abs(\rep31-\lltv[15])<=0.02}{option=hide}
\answer{Tableau de variations}{tableau de variations;tableau de valeurs,tableau de comparaisons,tableau de signes}{type=clickfill}{option=noanalyzeprint nonstop}


\answer{}{1}{type=numeric}{option=nonstop}
\answer{}{\rep34}{type=numeric}
\condition{Vous pouvez prendre la voiture au bout de \rr. Votre réponse 34 est de \rep34.}{abs(\rep34-\rr)<=0.02}
\answer{}{\rep35}{type=numeric}
\condition{Vous pouvez prendre la voiture au bout de \rre. Votre réponse 35 est de \rep35.}{abs(\rep35-\rre)<=0.02}
\answer{}{\rep36}{type=numeric}
\condition{Vous pouvez prendre la voiture au bout de \rrm. Votre réponse 36 est de \rep36.}{abs(\rep36-\rrm)<=2}
\answer{}{\rep37}{type=numeric}
\condition{Le risque de coma éthilique commence au bout de \r1. Votre réponse 37 est de \rep37.}{abs(\rep37-\r1)<=0.02}
\answer{}{\rep38}{type=numeric}
\condition{Le risque de coma éthilique se termine au bout \r2. Votre réponse 38 est de \rep38.}{abs(\rep38-\r2)<=0.02}
\answer{}{\rep39}{type=numeric}
\condition{La durée de coma éthilique est de \r3. Votre réponse 39 est de \rep39.}{abs(\rep39-\r3)<=0.02}

\matrix{rrep=\rep4,\rep5,\rep6,\rep7,\rep8,\rep9,\rep10,\rep11,\rep12,\rep13,\rep14,\rep15,\rep16}

\text{etape2= wims(makelist r x for x = 4 to 17)}
\text{etape3= wims(makelist r x for x = 18 to 32)}
\text{etape4= wims(makelist r x for x = 33 to 39)}
\text{etape44= wims(makelist r x for x = 33 to 36)}
\text{nstep=(\step=2)? \etape2}
\text{nstep=(\step=3)? \etape3}
\text{nstep=(\step=4 and \llltv[3]>2)? \etape4}
\text{nstep=(\step=4 and \llltv[3]<2)? \etape44}
#endif
