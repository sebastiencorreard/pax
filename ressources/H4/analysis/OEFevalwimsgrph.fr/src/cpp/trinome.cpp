target=trinome1 trinome2 trinome3 trinome4 trinome5
#include "lang_titles.inc"
#include "author.inc"
\precision{100}

#include "vartab.inc"
\integer{b=randint(-10..10)}
\integer{c=randint(-10..10)}
\integer{a=randint(1..10)*randint(1,-1)}
\text{f=\a*(x-\b)^2+\c}
\text{tf=texmath(maxima(\f))}
\rational{xs=\b}
\rational{ys=\c}
\text{variations=\(\searrow),\(\nearrow)}
\text{c_f=\a>0?1,2:2,1}
\text{v=\variations[\c_f]}
\integer{orient=\a>0?1:2}
\text{axe=x=\b}
#if defined TARGET_trinome1
\statement{On considère la parabole d'équation \(y = \tf).
  Quelle est son orientation?
<div class="wimscenter">\embed{reply1}</div>
}

\answer{orientation }{\orient;Vers le haut, Vers le bas}{type=radio}
#endif
#if defined TARGET_trinome2
\statement{On considère la parabole d'équation \(y = \tf).
  <label for="reply1">Quelle est l'équation de son axe de symétrie?</label>
<div class="wimscenter">\embed{reply1,20}</div>
}

\answer{équation de l'axe }{\axe}{type=monequation}
#endif
#if defined TARGET_trinome3
\statement{On considère la parabole d'équation \(y = \tf).
  Quelles sont les coordonnées de son sommet \(S\) ?
<div class="wimscenter"><label for="reply1">\(S)</label>(\embed{reply1,4}, \embed{reply2,4})</div>
}

\answer{abscisse du sommet }{\xs}{type=numeric}
\answer{ordonnée du sommet }{\ys}{type=numeric}
#endif

#if defined TARGET_trinome4
\integer{off=randint(1..5)}
\rational{xu=\xs-\off}
\rational{xv=\xs+\off}
\rational{yu=evaluate(\f,x=\xu)}
\rational{yv=evaluate(\f,x=\xv)}
\integer{yk=\a>0?randint(\ys+0.5..\yu-0.5):randint(\yu+0.5..\ys-0.5)}
\integer{rep5=(\a>0 and \ys<0) or (\a<0 and \ys>0)?3:1}
\integer{rep5=\ys=0?2}
\text{lstrep=Aucune solution, une solution unique, deux solutions distinctes}
\statement{
<ol>
<li>
  Compléter, par les valeurs exactes, le tableau des variations de
  la fonction \(f) définie sur [\xu;\xv] par \(f(x) = \tf).
<table class="tab_var">
<tr>
<th style="width:10%"> \(x)</th>
<td style="width:40%;text-align:left" colspan="2">\(\xu)</td>
<td style="width:10%"> \embed{reply1,5} </td>
<td style="width:40%;text-align:right" colspan="2">\(\xv)</td>
</tr><tr>
<th style="width:10%">\(var  f)</th>
<td style="width:10%;text-align:left"> \embed{reply2,5}</td>
<td style="width:30%">\v[1] </td>
<td style="width:10%"> \embed{reply3,5} </td>
<td style="width:30%"> \v[2]</td>
<td style="width:10%;text-align:right">\embed{reply4,5} </td>
</tr>
</table>
</li>
<li> Par lecture du tableau, donner le nombre de solutions sur [\xu;\xv] des équations suivantes:
 <ol>
<li>\(f(x) = 0): \embed{reply5} </li>
<li>\(f(x) = \ys): \embed{reply6} </li>
<li>\(f(x) = \yk): \embed{reply7} </li>
</ol>
</li>
</ol>
}

\answer{abscisse du sommet }{\xs}{type=numexp}
\answer{ordonnée gauche}{\yu}{type=numexp}
\answer{ordonnée du sommet}{\ys}{type=numexp}
\answer{ordonnée droite}{\yv}{type=numexp}
\answer{f(x) = 0}{\rep5;\lstrep}{type=radio}
\answer{f(x) = \ys}{2;\lstrep}{type=radio}
\answer{f(x) = \yk}{3;\lstrep}{type=radio}

#endif
#if defined TARGET_trinome5
\integer{b=randint(1..10)*randint(1,-1)}
\integer{c=randint(1..10)*randint(1,-1)}
\integer{a=randint(1..10)*randint(1,-1)}
\integer{c=\b=\c?2*\c}
\text{f=\a*(x-\b)^2+\c}
\text{tf=texmath(maxima(\f))}
\rational{xs=\b}
\rational{ys=\c}
\text{variations=\(\searrow),\(\nearrow)}
\text{c_f=\a>0?1,2:2,1}
\text{v=\variations[\c_f]}
\integer{orient=\a>0?1:2}
\text{axe=x=\b}
\text{variations=\(\searrow),\(\nearrow)}
\text{pos=\a>0?top,bottom,top:bottom,top,bottom}
\text{c_f=\a>0?1,2:2,1}
\text{monotone=\variations[\c_f]}

\text{f1=texmath(maxima(\a*(x-\b)^2+\c))}
\text{f2=texmath(maxima(\a*(x+\b)^2+\c))}
\text{f3=texmath(maxima(\a*(x-\b)^2-\c))}
\text{f4=texmath(maxima(\a*(x-\c)^2+\b))}
\text{lstrep=\(\f1),\(\f2),\(\f3),\(\f4)}
\statement{
  Le tableau des variations d'une fonction trinôme du second degré \(f) est

<table class="tab_var">
<tr>
  <th style="width:15%"> \(x)</th>
      <td style="width:15%;text-align:left"> \(-\infty)</td>
      <td style="width:8%"></td>
      <td style="width:15%"> \xs</td>
      <td style="width:8%"></td>
      <td style="width:15%;text-align:right">\(+\infty)</td>
</tr><tr>
  <th style="width:15%" valign="middle">\(var f)</th>
     <td style="width:15%;text-align:left" valign="\pos[1]">  </td>
     <td style="width:8%"> \monotone[1] </td>
     <td style="width:15%" valign="\pos[2]"> \ys </td>
     <td style="width:8%"> \monotone[2]</td>
     <td style="width:15%;text-align:right" valign="\pos[3]">  </td>
    </tr>
</table>

  Retrouver parmi les expressions suivantes, une expression possible pour \(f(x)).
<ul><li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
</ul>
}
\answer{expression possible}{1;\lstrep}{type=radio}{option=shuffle}
#endif
