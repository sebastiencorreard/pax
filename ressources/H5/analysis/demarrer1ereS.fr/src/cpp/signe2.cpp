target=signe2
##### : par lecture graphique
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{1000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{xsize=random(8,10,12)}
\integer{ysize=random(8,10,12)}
\integer{casf=random(1..6)}
\integer{sign=random(-1,1)}
\real{k=random(1..0.5*\ysize)}

\integer{signa=random(-1,1)}
\integer{a=(\casf!=4)?\signa*random(2..\xsize-3):random(-6..-3)}
\integer{b=(\casf!=4)?random(0,1)*(-\signa)*random(2..\xsize-1):random(-1..2)}
\integer{c=(\casf==4)?random(4..6)}
\integer{p=(\casf>4)?random(-0.5*\ysize..0.5*\ysize)}
/** definition des fonctions ; tirage aléatoire (casf) **/
\function{f=(\casf==1)?(\sign/\k)*(x-\a)}
\function{f=(\casf==2)?(\sign/\k)*(x-\a)*(x-\b)}
\function{f=(\casf==3)?(\sign/\k)*((x-\a)^2+random(1..4))}
\function{f=(\casf==4)?(\sign/\k^3)*(x-\a)*(x-\b)*(x-\c)}
\function{f=(\casf==5)?\sign*(\k/(x-\a)+\p)}
\function{f=(\casf==6)?\sign*(\k/((x-\a)^2+0.5)+\p)}

/** nombre et valeurs de racines **/
/** sol=\xsize+1 signifie aucune racine dans l'ensemble D **/
/** casf= 4 : au moins deux racines distinctes a et c **/

\text{sol=none}
\text{sol=(\casf==1)?\a }
\text{sol=(\casf==2 and \a==\b)?\a}
\text{sol=(\casf==2 and \a<\b)?\a,\b}
\text{sol=(\casf==2 and \b<\a)?\b,\a}
\text{sol=(\casf==4 and \a==\b)? \a,\c}
\text{sol=(\casf==4 and \a!=\b and \c!=\b)? \a,\b,\c}
\text{sol=(\casf==4 and \a!=\b and \c==\b)? \a,\b}
\rational{rac5=(\casf==5 and \p!=0)? simplify(\a-(\k/\p))}
\text{sol=(\casf==5 and \p!=0 and \rac5 <= \xsize and \rac5 >= -\xsize)? \rac5}
\rational{rad=\p!=0?simplify((-\k/\p)-0.5)}
\text{sol=(\casf==6 and \p!=0 and \rad>=0 )? simplify(\a-sqrt(\rad)),simplify(\a+sqrt(\rad)) }

\text{n=(none isitemof \sol)?0:items(\sol)}


/** preparation du graphique **/
/** correction casf==5 ; fxmil et fxmil2 en a+/-0.1 au lieu de a+/-0.5**/

\real{fxmin = min(max(evaluate(\f,x=-\xsize),-20),20)}
\real{fxmax = max(min(evaluate(\f,x=\xsize), 20),-20)}
\real{fxmil = (\n>1 and \casf!=6) ?max(min(evaluate(\f,x=0.5*(\sol[1]+\sol[2])),20),-20)}
\real{fxmil = (\casf==6) ?max(min(evaluate(\f,x=\a),20),-20)}
\real{fxmil = (\casf==5) ?max(min(evaluate(\f,x=\a-0.5),20),-20)}

\real{fxmil2 =(\n==3)?max(min(evaluate(\f,x=0.5*(\sol[2]+\sol[3])),20),-20)}
\real{fxmil2 = (\casf==5) ?max(min(evaluate(\f,x=\a+0.5),20),-20)}


\text{ll=((\n==1 and \casf!=5) or (\n==0 and \casf!=6))?0,\fxmin,\fxmax}

/** casf = 6 tenir compte de la valeur au milieu des racines **/

\text{ll=(\n==2 or \casf==6)?\fxmil,\fxmin,\fxmax}

\text{ll=(\n==3 or \casf==5)?\fxmil,\fxmil2,\fxmin,\fxmax}

text{ll=pari(L=List([\ll]) ; listsort(L); Vec(L))}
\text{ll=wims(sort numeric items \ll)}

\integer{yfloor=\ll[1]}
\integer{yceiling=\ll[-1]+1}

\integer{ymin=(\yfloor>0)?-1:\yfloor-1}
\integer{ymax=(\yceiling<0)?1:\yceiling+1}

\text{ticks=text black,-1, -20,small,-20
text black,-1,-15,small,-15
text black,-1,-10,small,-10
text black,-1,-5,small,-5
text black,-1,5,small,5
text black,-1,10,small,10
text black,-1,15,small,15
text black,-1,20,small,20
text black,-10,-0.2,small,-10
text black,-5,-0.2,small,-5
text black,5,-0.2,small,5
text black,10,-0.2,small,10
linewidth 3
point -10,0,black
point -5,0,black
point 5,0,black
point 10,0,black
point 0,-20,black
point 0,-15,black
point 0,-10,black
point 0,-5,black
point 0,5,black
point 0,10,black
point 0,15,black
point 0,20,black
}

/** Etape 2 : racines ordonnées par construction **/
/** calculer les val. arrondies au dixième pour casf 5 et 6 **/

\real{x1=(\n!=0 and \casf<5)?\sol[1]}
\real{x1=(\n!=0 and \casf>4)?pari(0.1*floor(10*\sol[1]))}
\real{x2=(\n>1 and \casf<5)?\sol[2]}
\text{ll=pari(L=List([\sol]); listsort(L) ;Vec(L))}
\real{x2=(\n>1 and \casf>4)?pari(0.1*floor(10*\ll[2]))}
\real{x3=(\n==3)?\c}

/** reponses ; repi indique les numéros des bons choix **/

\text{choix2=+,-}
\text{choix3=(\n!=0 or \casf==5 )?+,-}
\text{choix4=(\n>1 or \casf==5 )?+,-}
\text{choix5=(\n>2)?+,-}

/** casf = 5 (n = 1) ; tenir compte des valeurs de part et d'autre de la valeur interdite a **/

\text{rep2 = (\fxmin>0)?1:2}
\text{rep3 = ((\n==1 or (\casf==5 and \n==0)) and \fxmax>0)?1}
\text{rep3 = ((\n==1 or (\casf==5 and \n==0)) and \fxmax<0)?2}
/** \text{rep3 = (\casf==5 and \n==1 and \x1<\a and \fxmil>0)?1}**/
/** \text{rep3 = (\casf==5 and \n==1 and \x1<\a and \fxmil<0)?2}**/
/** \text{rep3 = (\casf==5 and \n==1 and \x1>\a and \fxmil2>0)?1}**/
/** \text{rep3 = (\casf==5 and \n==1 and \x1>\a and \fxmil2<0)?2}**/
\text{rep3 = (\casf==5 and \n==1 and \sign*\p>0)?2}
\text{rep3 = (\casf==5 and \n==1 and \sign*\p<0)?1}
\text{rep3 = (\n>1 and \fxmil>0)?1}
\text{rep3 = (\n>1 and \fxmil<0)?2}
\text{rep4 = (\casf==5 and \n==1 and \fxmax>0)?1}
\text{rep4 = (\casf==5 and \n==1 and \fxmax<0)?2}
\text{rep4 = (\n==2 and \fxmax>0)?1}
\text{rep4 = (\n==2 and \fxmax<0)?2}
\text{rep4 = (\n==3 and \fxmil2>0)?1}
\text{rep4 = (\n==3 and \fxmil2<0)?2}
\text{rep5 = (\n==3 and \fxmax>0)?1}
\text{rep5 = (\n==3 and \fxmax<0)?2}

/** Nombre variable de champs réponses **/

\text{listreply = \casf==5?reply2,reply3:reply2}
\text{listreply = (\casf==5 and \n==1) ?\listreply,reply4}
\text{listreply = (\casf!=5 and \n!=0)?\listreply,reply3}
\text{listreply = (\n>1 )?\listreply,reply4}
\text{listreply = (\n>2 )?\listreply,reply5}

\steps{reply1
\listreply }

\statement{
<div class="monenonce">
La représentation graphique d'une fonction \(f),définie sur
\(\mathcal{D}\) = \if{\casf!=5}{[-\xsize, \xsize]}{&#91;-\xsize,\a&#91; \cup &#93; \a,\xsize &#93;},
est donnée dans le repère (O ; I, J) ci-contre. On admet que la fonction \(f) ne change pas de sens de variation
en dehors du graphique.
</div>
<div class="wims_instruction">
Répondre aux questions suivantes par lecture graphique.
</div>
<div class="wims_columns">
<div class="medium_size img_col">
<!-- début de la colonne gauche : liste des questions -->
<ol>
\if{\step==1}{
<li>
<label for="reply1">
Combien l'équation \(f(x) = 0) a-t-elle de solutions dans \(\mathcal{D}\) ?</label>
\embed{reply1, 5}</li>}
\if{\step==2 and \casf!=5 and \n==0}{
<li>
L'équation \(f(x) = 0) n'a aucune solution dans \(\mathcal{D}\).
</li>
<li>\name_question \(f\):
<table border="1" >
<tr>
<td width="5%" > \(x)</td><td align="left" width="40%" >-\xsize</td><td align="right" width="40%" >\xsize</td>
</tr><tr>
<td width="5%" >\(f(x))</td><td colspan=2 align="center"> \embed{reply2}</td>
</tr>
</table>
</li>
}
\if{\step==2 and \casf==5 and \n==0 }{<li>
L'équation \(f(x) = 0) n'admet aucune solution dans \(\mathcal{D}\).
<br>La fonction \(f) n'est pas définie en \a.
</li>
<li>\name_question \(f\):
<table border="1" >
<tr>
<td width="5%" > \(x)</td><td width="40%" align="left">-\xsize</td><td align="center">\a</td><td width="40%" align="right">\xsize</td>
</tr>
<tr>
<td width="5%" > \(f(x))</td><td width="40%" align="center"> \embed{reply2}</td><td align="center">||</td><td width="40%" align="center"> \embed{reply3}</td>
</tr>
</table></li>
}
\if{\step==2 and \casf!=5 and \n==1 }{<li>
L'équation \(f(x) = 0\) a une unique solution \(x_1\) dans \(\mathcal{D}\).
<br>La valeur arrondie au dixième de \(x_1\) est \x1.
</li>
<li>\name_question \(f\):</li>
<table border=1 border="solid">
<tr>
<td width="5%" > \(x)</td><td width="40%" align="left">-\xsize</td><td align="center">\x1</td><td width="40%" align="right">\xsize</td>
</tr><tr>
<td width="5%" > \(f(x))</td><td width="40%" align="center"> \embed{reply2}</td><td align="center">0</td><td width="40%" align="center"> \embed{reply3}</td>
</tr>
</table>
</li>
}
\if{\step==2 and \casf==5 and \n==1 and \x1 < \a }{<li>
L'équation \(f(x) = 0) a une unique solution \(x_1\) dans \(\mathcal{D}\).
La fonction \(f) n'est pas définie en \a.
<br>La valeur arrondie au dizième de \(x_1\) est : \x1.
</li>
<li>\name_question \(f\):
<table border="1">
<tr>
<td width="5%"> \(x)</td><td width="25%" align="left">-\xsize</td>
<td width="5%" align="center"> \x1</td><td width="25%" > &nbsp;</td><td align="center" width="5%"> \a</td><td width="25%" align="right">\xsize</td>
</tr>
<tr>
<td width="5%" >\(f(x))</td><td width="25%" align="center"> \embed{reply2}</td><td width="5%" align="center">0</td><td width="25%" align="center"> \embed{reply3}</td><td align="center" width="5%">||</td>
<td width="25%" align="center"> \embed{reply4}</td>
</tr>
</table>
</li>
}
\if{\step==2 and \casf==5 and \n==1 and \a < \x1 }{<li>
L'équation \(f(x) = 0\) a une unique solution \(x_1\) dans \(\mathcal{D}\).
La fonction \(f\) n'est pas définie en \a.
<br>La valeur arrondie au dizième de \(x_1\) est : \x1.
</li>
<li>\name_question \(f\):
<table border="1">
<tr>
<td width="5%"> \(x)</td><td width="20%" align="left">-\xsize</td>
<td align="center" width="5%"> \a</td><td width="20%" > &nbsp;</td><td align="center" width="5%">\x1</td><td width="20%" align="right">\xsize</td>
</tr>
<tr>
<td width="5%">\(f(x))</td><td width="20%" align="center"> \embed{reply2}</td><td align="center" width="5%">||</td><td width="20%" align="center"> \embed{reply3}</td><td align="center" width="5%">0</td>
<td width="20%" align="center"> \embed{reply4}</td>
</tr>
</table>
</li>
}
\if{\step==2 and \n==2}{
<li>
L'équation \(f(x) = 0) a deux solutions \(x_1\) et \(x_2\) dans \(\mathcal{D}\).
<br>Les valeurs arrondies de \(x_1\) et \(x_2\) sont respectivement : \x1 et \x2.
</li>
<li>\name_question \(f\):
<table border="1" >
<tr>
<td width="5%"> \(x)</td><td width="25%" align="left">-\xsize</td>
<td align="center" width="5%"> \x1</td><td width="25%" > &nbsp;</td>
<td align="center" width="5%"> \x2</td><td width="25%" align="right">\xsize</td>
</tr>
<tr>
<td width="5%">\(f(x))</td><td width="25%" align="center"> \embed{reply2}</td>
<td align="center" width="5%">0</td><td width="25%" align="center"> \embed{reply3}</td><td align="center" width="5%"> 0</td>
<td width="25%" align="center"> \embed{reply4}</td>
</tr>
</table></li>
}
\if{\step==2 and \n==3}{<li>
L'équation \(f(x) = 0) a trois solutions \(x_1\), \(x_2\) et \(x_3\) dans \(\mathcal{D}\).
<br>Les valeurs arrondies au dixième de \(x_1\), \(x_2\) et \(x_3\) sont respectivement : \x1, \x2 et \x3.
</li>
<li>\name_question \(f\):
<table border="1">
<tr><td> \(x)</td>
<td align="left" width="20%" >-\xsize</td>
<td align ="center">\x1</td>
<td width="20%" > &nbsp;</td>
<td align="center">\x2</td>
<td width="20%" > &nbsp;</td>
<td align="center">\x3</td>
<td width="20%" align="right"> \xsize</td></tr>
<tr>
<td >\(f(x)\)</td>
<td width="20%" align="left"> \embed{reply2}</td>
<td align="center"> 0</td>
<td width="20%" align="center"> \embed{reply3}</td>
<td align="center">0</td>
<td width="20%" align="center"> \embed{reply4}</td>
<td align="center">0</td>
<td width="20%" align="center"> \embed{reply5}</td>
</tr>
</table></li>
}
</ol>
<!-- fin de la colonne gauche : les questions -->
</div>
<!-- colonne droite : le graphique -->
<div class="medium_size text_col">
<div class="wimscenter">
\draw{350,350}{
xrange -\xsize,\xsize
yrange \ymin,\ymax
parallel -\xsize,\ymin,-\xsize,\ymax,1,0, 2*\xsize+1, grey
parallel -\xsize,\ymin,\xsize,\ymin,0,1, (-\ymin)+\ymax+1, grey
hline 0,0,black
vline 0,0,black
arrow 0,0,1,0,8, black
arrow 0,0,0,1,8, black
text black,-0.5,-0.2,small,O
text black,1,-0.3,small,I
text black,-0.5,1,small,J
\ticks
linewidth 1.5
plot blue, \f
}
</div>
</div>
</div>
}

\hint{Le nombre \(f(x)) est strictement positif (resp. strictement négatif) pour tout réel
\(x) de l'intervalle \(I) si et seulement, sur cet intervalle,
la courbe représentative de \(f) est située au-dessus (resp. en-dessous)
de l'axe des abscisses.
<br>
\(f(x)) est nul si et seulement si \(x) est l'abscisse
d'un point d'intersection de la courbe représentative de \(f\) avec l'axe des abscisses.}

\answer{Nombre de zéro(s)}{\n}{type=numeric}
\answer{}{\rep2 ; \choix2}{type=menu}
\answer{}{\rep3 ; \choix3}{type=menu}
\answer{}{\rep4 ; \choix4}{type=menu}
\answer{}{\rep5 ; \choix5}{type=menu}
