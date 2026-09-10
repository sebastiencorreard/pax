target=tabvar1 tabvar2 tabvar3 tabvar4 tabvar5
#include "author.inc"
\precision{1000}
#include "vartab.inc"
#include "lang_titles.inc"
#if defined TARGET_tabvar5
\text{lstrep=toujours positif, toujours négatif, d'abord positif puis négatif, d'abord négatif puis positif}
\integer{x2=randint(5..20)}
\integer{x1=randint(1..\x2-2)}
\integer{choix=randint(1,2)}
\integer{nbsol=1}
\if{\choix=2}{
 \integer{y1=randint(-10..-1)}
 \integer{y0=\y1-randint(5..15)}
 \integer{y2=\y1-randint(2..10)}
 \integer{y3=randint(6..15)}
  \text{reps=2,2,4}
  \text{pos=bottom,top,bottom,top}
  \text{monotone = \(\nearrow),\(\searrow),\(\nearrow)}
 }{
 \integer{y2=randint(-10..-1)}
 \integer{y0=randint(5..15)}
 \integer{y1=\y2-randint(2..10)}
 \integer{y3=randint(-15..-6)}
  \text{reps=3,2,2}
  \text{monotone = \(\searrow),\(\nearrow),\(\searrow)}
  \text{pos=top,bottom,top,bottom}
 }
\statement{
  On considère une fonction \(g), dont on connaît le tableau des variations:
<table class="tab_var"><tr>
  <th>\(x)</th>
  <td style="text-align:left"> \(-\infty)</td>
  <td></td>
  <td>\x1</td>
  <td></td>
  <td>\x2</td>
  <td></td>
  <td style="text-align:right">\(\infty)</td>
</tr><tr>
  <th valign="middle">\(var g)</th>
  <td style="text-align:left" valign="\pos[1]"> \y0 </td>
  <td> \monotone[1] </td>
  <td valign="\pos[2]"> \y1 </td>
  <td> \monotone[2]</td>
  <td valign="\pos[3]"> \y2 </td>
  <td> \monotone[3] </td>
  <td style="text-align:right" valign="\pos[4]"> \y3 </td>
  </tr>
</table>
\tableau
<ol>
<li><label for="reply1">Quel est le nombre de solutions de l'équation \(g(x)=0)?
</label>\embed{reply1,3}</li>
<li>Quel est le signe de \(g(x))?
<ul>
<li>sur &#93;\(-\infty);\x1&#93;? \embed{reply2}</li>
<li>sur &#91;\x1;\x2&#93;? \embed{reply3}</li>
<li>sur &#91;\x1;\(+\infty)&#91;? \embed{reply4}</li>
</ul></li></ol>
}
\answer{nombre de solutions}{\nbsol}{type=numeric}
\answer{&#93;\(-\infty);\x1&#93;}{\reps[1];\lstrep}{type=radio}
\answer{&#91;\x1;\x2&#93;}{\reps[2];\lstrep}{type=radio}
\answer{&#91;\x1;\(+\infty)&#91;}{\reps[3];\lstrep}{type=radio}
#else
\integer{x0=-5-randint(0..9)}
\integer{x1=randint(-4..-1)}
\integer{x2=randint(1..4)}
\integer{x3=5+randint(0..9)}
\integer{choix=randint(1,2)}
integer{choix=2}
\integer{choix2=randint(1,2)}
integer{choix2=2}
\text{symb1=>,<}
\text{symb2=<,>}
\text{signef=négative, négative, positive}
\if{\choix=2}{
  \real{q1=randint(\x2*10+1..\x3*10-3)/10}
  \real{q=randint(\x2*10+1..\x3*10-3)/10}
  \real{q=\q2=\q1?\q+0.1}
  \real{q2=\q1<\q?\q:\q1}
  \real{q1=\q1>\q?\q}
  \real{q3=randint(\x0*10+1..\x1*10-3)/10}
  \integer{q4=\x0}
  \integer{y2=randint(1..9)}
  \integer{y0=\y2+randint(1..9)}
  \integer{y1=randint(-9..-1)}
  \integer{y1=\y1=\x1?\y1-1}
  \integer{y3=0}
  \integer{s=\y2}
  \integer{t=\y1}
  \integer{t2=\t-1}
  \integer{u=\y0}
  \integer{xmin=\x1}
  \integer{xmax=\x0}
  \integer{xn1=\x2}
  \integer{xn2=\x3}
  \text{reps=3,2,1,1,3}
  \text{monotone = \(\searrow),\(\nearrow),\(\searrow)}
  \text{pos=top,bottom,top,bottom}
  \text{extrema=majorant,minorant}
  \text{variations = décroissante,décroissante}
 }{
  \real{q1=randint(\x0*10+1..\x1*10-3)/10}
  \real{q=randint(\x0*10+1..\x1*10-3)/10}
  \real{q=\q2=\q1?\q+0.1}
  \real{q2=\q1<\q?\q:\q1}
  \real{q1=\q1>\q?\q}
  \real{q3=randint(\x2*10+1..\x3*10-3)/10}
  \integer{q4=\x3}
  \integer{y1=randint(1..9)}
  \integer{y3=\y1+randint(1..9)}
  \integer{y2=randint(-9..-1)}
  \integer{y0=0}
  \integer{s=\y1}
  \integer{t=\y2}
  \integer{t2=\t-1}
  \integer{u=\y3}
  \integer{xmin=\x2}
  \integer{xmax=\x3}
  \integer{xn1=\x1}
  \integer{xn2=\x2}
  \text{reps=3,1,2,2,3}
  \text{pos=bottom,top,bottom,top}
  \text{monotone = \(\nearrow),\(\searrow),\(\nearrow)}
  \text{extrema=minorant,majorant}
  \text{variations = croissante,décroissante}

 }
# if defined TARGET_tabvar1
\text{lstrep=Vrai, Faux, On ne peut pas savoir}
\text{prop=\(f(0)=0),\(f(\q1) \symb1[\choix2] f(\q2)),\(f(\q3) \symb2[\choix2] f(\q4)),\(f(\q2) \symb2[\choix2] f(\q4)),\(f(\q2) \symb1[\choix2] f(\q3))}
\if{\choix=1}{
  \text{reps=\choix2=1?3,2,1,1,3:3,1,2,2,3}
 }{
  \text{reps=\choix2=1?3,1,1,1,3:3,2,2,2,3}
 }
\text{consigne= ou si on ne peut pas savoir}
# else
\text{lstrep=Vrai, Faux}
\text{consigne=}
# endif
# if defined TARGET_tabvar2
\text{prop=\(f) s'annule une seule fois, l'équation \(f(x)=\s) a deux solutions distinctes, 0 a trois antécédents par \(f), 0 a trois images par \(f), la courbe de \(f) coupe trois fois la droite d'équation \(y=\t)}
  \text{reps=2,1,1,2,2}
# endif
# if defined TARGET_tabvar3
\if{\choix=1}{
\text{prop=\u est un majorant de \(f) sur &#91; \q1 &#59; \q3 &#93; , \t2 est un minorant de \(f) sur &#91; \x0 &#59; \x1 &#93;, Pour tout \(x \in ) &#91; \x0 &#59; \x3 &#93; &#44; \(0 \le f(x) \le \u), Ce tableau de variations ne permet pas d'encadrer \(f(x)) sur &#91; 0 &#59; \q3 &#93;, l'image de l'intervalle &#91; \x0 &#59; \x2 &#93; est &#91; \t &#59; \s &#93;}
}{
\text{prop=\u est un majorant de \(f) sur &#91; \q3 &#59; \q1 &#93; , \t2 est un minorant de \(f) sur &#91; \x2 &#59; \x3 &#93;, Pour tout \(x \in ) &#91; \x0 &#59; \x3 &#93; &#44; \(0 \le f(x) \le \u), Ce tableau de variations ne permet pas d'encadrer \(f(x)) sur &#91; \q3 &#59; 0 &#93;, l'image de l'intervalle &#91; \x0 &#59; \x2 &#93; est &#91; \t &#59; \u &#93;}
}
  \text{reps=1,1,2,2,1}
# endif
# if defined TARGET_tabvar4
\if{\choix2=1}{
\text{prop=\(f) est strictement \variations[1] sur &#91; \x0 &#59; \x1 &#93; , \(f) est négative sur &#91; \xn1 &#59; \xn2 &#93;, \(f) est strictement \variations[2] sur &#91; \xn1 &#59; \xn2 &#93; , Le maximum de \(f) sur &#91; \x0 &#59; \x3 &#93; est \xmax atteint en \u, Le minimum de \(f) sur &#91; \x0 &#59; \x3 &#93; est \t atteint en \xmin}
  \text{reps=1,2,1,2,1}
 }{
\text{prop=\(f) est strictement \variations[1] sur &#91; \x0 &#59; \x1 &#93; , \(f) est négative sur &#91; \xn1 &#59; \xn2 &#93;, \(f) est strictement \variations[2] sur &#91; \xn1 &#59; \xn2 &#93; , Le maximum de \(f) sur &#91; \x0 &#59; \x3 &#93; est \u atteint en \xmax, Le minimum de \(f) sur &#91; \x0 &#59; \x3 &#93; est \xmin atteint en \t}
  \text{reps=1,2,1,1,2}
}
# endif

\statement{
 On considère une fonction \(f) définie sur &#91; \x0; \x3 &#93;, dont on connaît le tableau des variations:
<table class="tab_var">
  <tr>
    <th> \(x)</th>
    <td style="text-align:left"> \x0</td>
    <td></td>
    <td>\x1</td>
    <td></td>
    <td>\x2</td>
    <td></td>
    <td style="text-align:right">\x3</td>
  </tr><tr>
    <th valign="middle">\(var f)</th>
    <td style="text-align:left" valign="\pos[1]"> \y0 </td>
    <td> \monotone[1] </td>
    <td valign="\pos[2]"> \y1 </td>
    <td> \monotone[2]  </td>
    <td valign="\pos[3]"> \y2 </td>
    <td> \monotone[3] </td>
    <td style="text-align:right" valign="\pos[4]"> \y3 </td>
    </tr>
</table>
\tableau
  Pour chaque affirmation, dire si elle est vraie ou fausse \consigne:
<ol>
<li> \prop[1]: \embed{reply1}</li>
<li> \prop[2]: \embed{reply2}</li>
<li> \prop[3]: \embed{reply3}</li>
<li> \prop[4]: \embed{reply4}</li>
<li> \prop[5]: \embed{reply5}</li>
</ol>
}
\answer{\prop[1]}{\reps[1];\lstrep}{type=radio}
\answer{\prop[2]}{\reps[2];\lstrep}{type=radio}
\answer{\prop[3]}{\reps[3];\lstrep}{type=radio}
\answer{\prop[4]}{\reps[4];\lstrep}{type=radio}
\answer{\prop[5]}{\reps[5];\lstrep}{type=radio}
#endif
