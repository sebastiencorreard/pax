target=methodologie2
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{a = (-1)^random(0,1)*random(1..10)}
\integer{b = (-1)^random(0,1)*random(2..10)}
\integer{c = (-1)^random(0,1)*random(1..3)}
\integer{d = (-1)^random(0,1)*random(2..8)}
\text{signd=\d>0?pos:neg}

\rational{racu=-(\b)/(\a)}

/** Faire en sorte que les racines soient distinctes **/
\integer{d=(-(\d)/(\c)=\racu)?-\d}
\rational{racv=-(\d)/(\c)}

\function{u=\a*x + \b}
\function{u2=(\u)^2}

\function{v=\c*x + \d}
\function{v2=(\v)^2}

\integer{e=random(2..6)}
\integer{f=\e^2}
\integer{k=random(1,-1)}
\text{signk=\k==1?pos:neg}
\function{s=\k==1?\v2+\f:-\v2-\f}

\function{t=\v2-\f}
\integer{g=\d-\e}
\integer{h=\d+\e}
\function{p=\g==0?\c*x:\c*x + \g}
\rational{racp=-(\g)/(\c)}
\function{q=\g==0?\c*x:\c*x + \h}
\rational{racq=-(\h)/(\c)}
\function{fact=(\p)*(\q)}

/** Présenter le tableau correct dans environ 1 cas sur 3**/

\integer{err=random(1,1,0)}

/** Six cas de produits ou quotients **/

\integer{cas=random(1..6)}

\text{listFc=\d(\t),(\u)\v2,(\u)(\s),(\u)/(\s),(\d)/(\t),(\u)/(\v2)}
\function{Fc=item(\cas,\listFc)}
\text{Fc=texmath(\Fc)}

/** facteurs corrects **/

\if{\err==0}{
\text{listU=\p,\u,\u,\u,\p,\u}
\text{listV=\q,\v2,\s,\s,\q,\v2}
\text{listW=\d,0,0,0,\d,0}

\text{lesracU=\racp,\racu,\racu,\racu,\racp,\racu}
\text{lesracV=\racq,\racv,inf,inf,\racq,\racv}

/** les coefficients directeurs du premier facteur U **/
\text{lesdirU=\c,\a,\a,\a,\c,\a}
\text{lesdirV=\c,pos,\signk,\signk,\c,pos}
\text{lesdirW=\signd,0,0,0,\signd,0}
}

/** facteurs incorrects **/
\if{\err==1}{
\text{listU=\d,\u,\u,\u,\d,\u}
\text{listV=\v2,\v,\k*\v2,\k*\v2,\v2,\v}
\text{listW=-\f,0,\k*\f,\k*\f,-\f,0}

\text{lesracU=inf,\racu,\racu,\racu,inf,\racu}
\text{lesracV=\racv,\racv,\racv,\racv,\racv,\racv}
\text{lesdirU=\signd,\a,\a,\a,\signd,\a }
\text{lesdirV=pos,\c,\signk,\signk,pos,\c}
\text{lesdirW=neg,0,\signk,\signk,neg,0}
}

/** les bons/mauvais facteurs du tableau proposé **/

\function{U=item(\cas,\listU)}
\function{V=item(\cas,\listV)}
\function{W=item(\cas,\listW)}
\rational{racU=item(\cas,\lesracU)}
\rational{racV=item(\cas,\lesracV)}
\text{dirU=item(\cas,\lesdirU)}
\text{dirV=item(\cas,\lesdirV)}
\text{dirW=item(\cas,\lesdirW)}

/** ordonner les racines ; par défaut il y en a deux **/
/** sinon, voir la déf. de x1 selon cas **/

\text{vi=(\err==1 and \cas>3)?\racV}
\text{vi=(\err==0 and \cas==5)?\racU,\racV}
\text{vi=(\err==0 and \cas==6)?\racV}

\integer{rgerac=\racU<\racV?1:2}
\rational{x1=\rgerac==1?\racU:\racV}
\rational{x2=\rgerac==1?\racV:\racU}
\rational{x1=(\err==1 and \cas isin 1,5)?\racV}
\rational{x1=(\err==0 and \cas isin 3,4)?\racU}

/** choix pour les barres et signes **/
\text{signs=+,-}
\text{bars=0,||,|}

/** règles des signes pour les facteurs U et V**/
/** pour les facteurs de signe constant sX=soppX=dirX (pos ou neg)**/

!!!!bug corrigé le 01/10/08 = \integer{sU=\dirU==\a and \dirU>0?1:2}
\integer{sU=\dirU>0?1:2}
\integer{sU=(pos isin \dirU)?1}
\integer{sU=(neg isin \dirU)?2}
!!!!\integer{sopU=\dirU==\a and \dirU>0?2:1}
\integer{sopU=\dirU>0?2:1}
\integer{sopU=(pos isin \dirU)?1}
\integer{sopU=(neg isin \dirU)?2}

!!!!!cond. inutile corrigée le 01/10/08 = \integer{sV=(\dirV==\c and \dirV>0)?1:2}
\integer{sV=(\dirV>0)?1:2}
\integer{sV=(pos isin \dirV) ?1}
\integer{sV=(neg isin \dirV) ?2}
\integer{sopV=(\dirV>0)?2:1}
\integer{sopV=(pos isin \dirV)?1}
\integer{sopV=(neg isin \dirV)?2}

\integer{sW=(pos isin \dirW)?1}
\integer{sW=(neg isin \dirW)?2}

/** calculs sur les signes et zéros **/

\text{bad3=\sopU}
\text{bad4=\x1==\racU?1:3}
\text{bad5=\x1==\racU?\sU:\sopU}
\text{bad6=\x2==\racU?1:3}
\text{bad7=\sU}

\text{bad8=\sopV}
\text{bad9=\x1==\racV?1:3}
\text{bad10=\x1==\racV?\sV:\sopV}
\text{bad11=\x2==\racV?1:3}
\text{bad12=\sV}

/** special coef constant (W)**/

\text{bad2=\sW}

/** cas 1 à 3 : produit ; cas 4 à 6 : quotient **/

\text{bad13=\bad3*\bad8==2?2:1}
\text{bad14=(\cas>3 and \x1 isin \vi)?2:1}
\text{bad15=\bad5*\bad10==2?2:1}
\text{bad16=(\cas>3 and \x2 isin \vi)?2:1}
\text{bad17=\bad7*\bad12==2?2:1}

/** inverser les signes si un coeff négatif dans le tableau**/
\if{\bad2==2}{
\text{bad13=\bad13==2?1:2}
\text{bad15=\bad15==2?1:2}
\text{bad17=\bad17==2?1:2}
}

/** tableau erroné avec deux racines (tous cas sauf 1 et 5) **/
/** tableau correct avec deux racines (tous cas sauf 3 et 4) **/

\if{(\err==1 and \cas notin 1,5) or (\err==0 and \cas notin 3,4)}
{
\text{table=
<table class="wimsborder" style="width:80%">
<tr>
<td style="width:15%;text-align:center">\(x\)</td>
<td style="width:25%;text-align:left">\(-\infty\)</td>
<td style="width:5%;text-align:center">\x1</td>
<td style="width:25%;text-align:right"></td>
<td style="width:5%;text-align:center">\x2</td>
<td style="width:25%;text-align:right">\(+\infty\)</td>
</tr><tr>
<td style="width:15%;text-align:center">\(\U\)</td>
<td style="width:25%;text-align:center">item(\bad3,\signs)</td>
<td style="width:5%;text-align:center">item(\bad4,\bars)</td>
<td style="width:25%;text-align:center">item(\bad5,\signs) </td>
<td style="width:5%;text-align:center">item(\bad6,\bars)</td>
<td style="width:25%;text-align:center">item(\bad7,\signs)</td>
</tr><tr>
<td style="width:15%;text-align:center">\(\V\)</td>
<td style="width:25%;text-align:center">item(\bad8,\signs)</td>
<td style="width:5%;text-align:center">item(\bad9,\bars)</td>
<td style="width:25%;text-align:center">item(\bad10,\signs) </td>
<td style="width:5%;text-align:center">item(\bad11,\bars)</td>
<td style="width:25%;text-align:center">item(\bad12,\signs)</td>
</tr>
}
/** s'il y a un facteur constant **/
\if{\dirW!=0}{
  \text{table=\table
<tr><td style="text-align:center">\(\W\)</td>
<td style="width:25%;text-align:center">item(\bad2,\signs)</td>
<td style="width:5%;text-align:center">item(3,\bars)</td>
<td style="width:25%;text-align:center">item(\bad2,\signs) </td>
<td style="width:5%;text-align:center">item(3,\bars)</td>
<td style="width:25%;text-align:center">item(\bad2,\signs)</td>
</tr>}
}
\text{table=\table
<tr>
<td style="width:15%;text-align:center">\(f(x)\)</td>
<td style="width:25%;text-align:center">item(\bad13,\signs)</td>
<td style="width:5%;text-align:center">item(\bad14,\bars)</td>
<td style="width:25%;text-align:center">item(\bad15,\signs)</td>
<td style="width:5%;text-align:center">item(\bad16,\bars)</td>
<td style="width:25%;text-align:center">item(\bad17,\signs)</td>
</tr></table>}
}

/** tableau erroné avec une seule racine (cas 1 ou 5) **/
/** tableau correct avec une seule racine (cas 3 ou 4) **/

\if{(\err==1 and \cas isin 1,5) or (\err==0 and \cas isin 3,4)}{
\text{table=
<table border=1 border="solid" width="80%">
<tr>
<td style="width:15%;text-align:center">\(x\)</td>
<td style="width:25%;text-align:left">\(-\infty\)</td>
<td style="width:5%;text-align:center">\x1</td>
<td style="width:25%;text-align:right">\(+\infty\)</td>
</tr>
<tr>
<td style="width:15%;text-align:center">\(\U\)</td>
<td style="width:25%;text-align:center">item(\bad3,\signs)</td>
<td style="width:5%;text-align:center">item(\bad4,\bars)</td>
<td style="width:25%;text-align:center">item(\bad7,\signs)</td>
</tr>
<tr>
<td style="width:15%;text-align:center">\(\V\)</td>
<td style="width:25%;text-align:center">item(\bad8,\signs)</td>
<td style="width:5%;text-align:center">item(\bad9,\bars)</td>
<td style="width:25%;text-align:center">item(\bad12,\signs)</td>
</tr>
}
/** s'il y a un facteur constant **/
\if{\dirW!=0}{
  \text{table=\table
<tr><td align="center">\(\W\)</td>
<td style="width:25%;text-align:center">item(\bad2,\signs)</td>
<td style="width:5%;text-align:center">item(3,\bars)</td>
<td style="width:25%;text-align:center">item(\bad2,\signs)</td>
</tr>}
}
\text{table=\table
<tr>
<td style="width:15%;text-align:center">\(f(x)\)</td>
<td style="width:25%;text-align:center">item(\bad13,\signs)</td>
<td style="width:5%;text-align:center">item(\bad14,\bars)</td>
<td style="width:25%;text-align:center">item(\bad17,\signs)</td>
</tr></table>}
}
\text{choix=\name_choix}
\text{choix=(\err==1 and \cas notin 2,6) or (\err==0 and \cas isin 1,5)?\choix,
  \(\W\) \name_choixp}

\text{goodrep=\err==0?1}
\text{goodrep=(\err==1 and \cas isin 1,5)?2,5,7}
\text{goodrep=(\err==1 and \cas isin 2,6)?3}
\text{goodrep=(\err==1 and \cas isin 3,4)?4,5,7}
\integer{nbchoix = items(\choix)}
\statement{
<div class="wims_question">
 \name_enonce : <div class="center">\({}f(x) = \Fc\)</div>
<div class="wimscenter">
 \table
</div>
\name_question[1]? \name_question[2], \name_question[3]
</div>
<ul>
\for{i=1 to \nbchoix}{<li class="wims_nopuce">\embed{reply1,\i}</li>}
</ul>
}

\answer{}{\goodrep;\choix}{type=checkbox}{option=shuffle}

!!! bug corrige le 01/11/08 :

\feedback{(\cas==2 or \cas==4) and \reply1 notsametext \goodrep}
\feedback{(\cas==3 or \cas==4) and \reply1 notsametext \goodrep}
{<div class="macorrection envert"><strong>\name_remember</strong> :
\name_feed1[1], \name_feed1[2] \(\s\)
  \name_feed1[3]
\if{\k==1}{\name_posneg[1]}{\name_posneg[2]}, \name_forall \(x).</div>}

\feedback{(\cas==1 or \cas==5) and \reply1 notsametext \goodrep }{
<div class="macorrection envert"><strong>\name_remember</strong> :
\name_feed1[1], \name_feed1[4] \(\t\)
\name_feed1[5] \(a^2 - b^2= (a-b)(a+b)\).</div>}
