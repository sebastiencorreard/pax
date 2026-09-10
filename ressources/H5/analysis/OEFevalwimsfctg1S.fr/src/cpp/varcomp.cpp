target=varcomp1 varcomp2 varcomp3 varcomp4 varcomp5
#include "author.inc"
\precision{1000}
#include "vartab.inc"
#include "lang_titles.inc"
#if defined TARGET_varcomp1
\integer{a=randint(1..10)*randint(1,-1)}
\integer{k=randint(1,-1)}
\integer{m=randint(1..10)*\k}
\integer{s=-randint(1..10)*\k}
\integer{k=randint(1,-1)}
\integer{p=randint(1..10)*\k}
\integer{r=-randint(1..10)*\k}
\text{f=\m*u+\p}
\text{g=\s*u+\r}
\integer{a1=\a+1}
\integer{a2=2*\a}
\integer{k=randint(1,2)}
\text{variations = \(\nearrow),\(\searrow)}
\text{c_u=\k=1?2,1:1,2}
\text{c_mu=\k=1?1,2:2,1}
\text{v=\m>0?\variations[\c_u]:\variations[\c_mu]}
\text{v2=\s>0?\variations[\c_u]:\variations[\c_mu]}
\text{monotone=\variations[\c_u]}
\integer{x0=\k=1?\a:\a1}
\integer{ux0=\k=1?0:\a2}
\integer{yf=\m*\ux0+\p}
\integer{yg=\s*\ux0+\r}

\text{tableau=<table class="tab_var">
  <tr>
  <th>\(x)</th>
  <td style="text-align:left">-\(\infty)</td>
  <td>\x0</td>
  <td style="text-align:right">+\(\infty)</td>
  </tr><tr>
  <th>\(var u)</th>
  <td>\monotone[1] </td>
  <td>\ux0 </td>
  <td>\monotone[2] </td>
</tr>
</table>
}
\statement{
Voici le tableau des variations d'une fonction \(u) définie sur \(\ \RR).
\tableau
Construire le tableau des variations de la fonction \(f = \f) puis celui de la fonction \(g = \g).
<ol>
<li>Tableau des variations de \(f):
<table class="tab_var">
<tr>
<th>\(x)</th>
<td style="text-align:left">-\(\infty)</td>
<td>\embed{reply1,5} </td>
<td style="text-align:right">+\(\infty)</td>
</tr><tr>
<th>\(var f)</th>
<td>\embed{reply2,100x30} </td>
<td>\embed{reply4,5} </td>
<td>\embed{reply3} </td>
</tr>
</table>
</li>
<li>Tableau des variations de \(g):
<table class="tab_var">
<tr>
<th>\(x)</th>
<td style="text-align:left">-\(\infty)</td>
<td>\embed{reply5,5} </td>
<td style="text-align:right">+\(\infty)</td>
</tr><tr>
<th>\(var g)</th>
<td>\embed{reply6} </td>
<td>\embed{reply8,5} </td>
<td>\embed{reply7}</td>
</tr>
</table>
</li>
</ol>
}
\answer{abscisse du sommet de f }{\x0}
\answer{monotonie 1 pour f}{\v[1] }{type=clickfill}{option = shuffle}
\answer{monotonie 2 pour f}{\v[2] }{type=clickfill}{option = shuffle}
\answer{ordonnée du sommet de f}{\yf}
\answer{abscisse du sommet de g }{\x0}
\answer{monotonie 1 pour g }{\v2[1] }{type=clickfill}{option = shuffle}
\answer{monotonie 2 pour g}{\v2[2] }{type=clickfill}{option = shuffle}
\answer{ordonnée du sommet de g}{\yg}
#endif
#if defined TARGET_varcomp2
\integer{a=randint(2..10)*randint(1,-1)}
\integer{b=randint(1..10)*randint(1,-1)}
\text{f=texmath(\a*x+\b)}
\text{g=texmath(maxima(-\a+1)*x)}
\text{u=texmath(x^2)}
\text{v=texmath(1/x)}
\rational{r=simplify(-\b / \a)}
\integer{k=randint(1,2)}
\text{intvu=\k=1?&#93;\(0;+\infty)&#91;:&#93;\(-\infty;0)&#91;}
\integer{rep1=1}
\integer{rep2=\a>0?2:1}
\integer{rep3=\a>0?1:2}
\integer{rep4=\a>0?1:2}
\integer{rep5=\a>0?2:1}
\integer{rep6=\k=1?2:1}

\statement{
On considère les fonctions:
<ul class="inline"><li>\(f: x \mapsto \f)</li><li>
\(g: x \mapsto \g)
</li><li>\(u: x \mapsto \u)
</li><li>\(v: x \mapsto \v)
</li></ul>
Les propositions suivantes sont-elles vraies ou fausses?
<ol>
<li>\(f \circ g) est strictement décroissante sur \(\,\RR): \embed{reply1}
</li>
<li>\(g \circ v) est strictement décroissante sur &#93;\(0;+\infty)&#91;: \embed{reply2}
</li>
<li>\(g \circ u) est strictement croissante sur &#93;\(-\infty;0)&#91;: \embed{reply3}
</li>
<li>\(v \circ f) est strictement décroissante sur &#93;\(\r;+\infty)&#91;: \embed{reply4}
</li>
<li>\(u \circ f) est strictement décroissante sur &#93;\(\r;+\infty)&#91;: \embed{reply5}
</li>
<li>\(v \circ u) est strictement croissante sur \intvu: \embed{reply6}
</li>
</ol>
}
\answer{}{\rep1;Vrai,Faux}{type=radio}
\answer{}{\rep2;Vrai,Faux}{type=radio}
\answer{}{\rep3;Vrai,Faux}{type=radio}
\answer{}{\rep4;Vrai,Faux}{type=radio}
\answer{}{\rep5;Vrai,Faux}{type=radio}
\answer{}{\rep6;Vrai,Faux}{type=radio}
#endif
#if defined TARGET_varcomp3
#include "varcomp3data.inc"
\statement{<div class="float_right">
\if{\choix=1}{\tableau}{\draw{300,300}{\dessin}}
</div>
\intro
<p>Construire le tableau des variations de la fonction \(u= f^2) puis celui de
la fonction \(v= \frac{1}{f}).</p>
<div class="wims_instruction">
On ne précisera pas les limites de part et d'autre d'une discontinuité, \consigne.</div>
<ol>
<li>Tableau des variations de \(u):
 <table class="tab_var">
    <tr><th>\(x) </th><td>\embed{reply1,\size}</td></tr>
    <tr><th>\(var u) </th><td>\embed{reply2,\size}</td></tr>
 </table>
</li>
<li>Tableau des variations de \(v):
<table class="tab_var">
    <tr><th>\(x) </th><td>\embed{reply3,\size}</td></tr>
    <tr><th>\(var v) </th><td>\embed{reply4,\size}</td></tr>
</table>
</li>
</ol>
}
\answer{}{\grepux;\clicList}{type=clickfill}
\answer{}{\grepuy;\clicList}{type=clickfill}
\answer{}{\grepvx;\clicList}{type=clickfill}
\answer{}{\grepvy;\clicList}{type=clickfill}
#endif

#if (defined TARGET_varcomp4 || defined TARGET_varcomp5 )
\integer{a1=random(1..3)*random(1,-1)}
\integer{a2=random(1..3)*random(1,-1)}
\integer{c1=randint(1..10)*random(1,-1)}
\integer{c2=randint(1..10)*random(1,-1)}
\integer{c3=randint(1..10)*random(1,-1)}
# if defined TARGET_varcomp4
\integer{m=randint(1..10)}
# else
\integer{m=-randint(1..10)}
#endif
\integer{p=randint(1..10)*random(1,-1)}

\text{flist=\c1*(x+\c3)^2+\c2,
\c1*x^2+\c3,
\c1*(\a2*x+\a1)^2}

\integer{\cas=random(1..3)}
\function{f=item(\cas,\flist)}

\function{g=\m*x+\p}
\function{recg=(x-\p)/(\m)}
\text{dispg=texmath(\g)}


\rational{x0=\cas==1?-(\c3) }
\rational{x0=\cas==2?0 }
\rational{x0=\cas==3?-(\a1/\a2) }

\rational{x1=evaluate(\recg,x=\x0)}
\rational{fx0=evaluate(\f,x=\x0)}
\rational{gofx0=evaluate(\g,x=evaluate(\f,x=\x0))}
\rational{fogx1=evaluate(\f,x=evaluate(\g,x=\x1))}

\integer{a=\x0-randint(1..10)}
\integer{c=\x0+randint(1..10)}
\rational{ya=evaluate(\f,x=\a)}
\rational{yc=evaluate(\f,x=\c)}
\rational{gofa=evaluate(\g,x=\ya)}
\rational{gofc=evaluate(\g,x=\yc)}

\integer{k=randint(1,2)}
\if{\m>0}
 {
\rational{xmin=\k=1?simplify((\a-\p)/(\m)):simplify((\x0-\p)/(\m))}
\rational{xmax=\k=1?simplify((\x0-\p)/(\m)):simplify((\c-\p)/(\m))}
\rational{ymin=\k=1?\ya:\fx0}
\rational{ymax=\k=1?\fx0:\yc}
\rational{gx1=\k=1?\a:\x0}
\rational{gx2=\k=1?\x0:\c}
\rational{gxmin=\gx1<\gx2?\gx1:\gx2}
\rational{gxmax=\gx1<\gx2?\gx2:\gx1}
 }
 {
\rational{xmax=\k=1?simplify((\a-\p)/(\m)):simplify((\x0-\p)/(\m))}
\rational{xmin=\k=1?simplify((\x0-\p)/(\m)):simplify((\c-\p)/(\m))}
\rational{ymax=\k=1?\ya:\fx0}
\rational{ymin=\k=1?\fx0:\yc}
\rational{gx2=\k=1?\a:\x0}
\rational{gx1=\k=1?\x0:\c}
\rational{gxmin=\gx1<\gx2?\gx1:\gx2}
\rational{gxmax=\gx1<\gx2?\gx2:\gx1}
 }

\text{choix1=croissante,décroissante}
\text{variations = \(\nearrow),\(\searrow)}
\text{c_comp=\c1*\m>0?2,1:1,2}
\text{v=\variations[\c_comp]}
\text{v2=\variations[\c_comp]}
\text{c_f=\c1>0?2,1:1,2}
\text{monotone=\variations[\c_f]}
\text{c_g=\m>0?1:2}
\integer{cc1=-1*\c1}
 \text{pos=\c1>0?top,bottom,top:bottom,top,bottom}
\integer{rep7=\c_comp[\k]}


\statement{
Soit \(g) la fonction affine définie par \(g(x)=\dispg)
 et \(f) une fonction définie sur [\a;\c] dont le tableau des variations
 est donné ci-dessous
<table class="tab_var">
<tr>
  <th>\(x)</th>
      <td style="text-align:left">\a</td>
      <td></td>
      <td>\x0</td>
      <td></td>
      <td style="text-align:right">\c</td>
</tr>
<tr>
  <th>\(var f)</th>
     <td style="text-align:left" valign="\pos[1]">\ya </td>
     <td>\monotone[1] </td>
     <td valign="\pos[2]">\fx0 </td>
     <td>\monotone[2]</td>
     <td style="text-align:right" valign="\pos[3]">\yc </td>
      </tr>
</table>

<ol>
<li>
Compléter le tableau des variations de la fonction \(g\circ f) sur [\a;\c]:
<table class="tab_var">
<tr>
<th>\(x)</th>
<td style="text-align:left">\(\a)</td>
<td>\embed{reply1,5} </td>
<td style="text-align:right">\(\c)</td>
</tr><tr>
<th>\(var g\circ f)</th>
<td>\embed{reply2,5}\embed{reply3} </td>
<td>\embed{reply4,5} </td>
<td>\embed{reply5}\embed{reply6,5} </td>
</tr>
</table>
</li>
<li>
Compléter la phrase: Pour tout \(x \in ) [\xmin;\xmax], \(g(x) \in )
[\embed{reply10,3};\embed{reply11,3}]<br>
En déduire les variations de la fonction \(f\circ g) sur [\xmin;\xmax]:<br>
\(f \circ g) est \embed{reply7} de \embed{reply8,5} à \embed{reply9,5}
</li>
</ol>
}

\answer{abscisse du sommet pour gof }{\x0}
\answer{borne gauche pour gof }{\gofa}
\answer{monotonie 1 }{\v[1] }{type=clickfill}{option = shuffle}
\answer{ordonnée du sommet}{\gofx0}
\answer{monotonie 2}{\v[2] }{type=clickfill}{option = shuffle}
\answer{borne droite pour gof }{\gofc}
\answer{sens de variation de fog }{\rep7;\choix1}{type=menu}
\answer{borne gauche pour fog }{\ymin}
\answer{borne droite pour fog }{\ymax}
\answer{borne inf de g(x)}{\gxmin}{type=numeric}
\answer{borne sup de g(x)}{\gxmax}{type=numeric}

#endif
