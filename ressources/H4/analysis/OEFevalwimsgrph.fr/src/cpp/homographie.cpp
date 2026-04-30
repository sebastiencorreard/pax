target=homographie1 homographie2 homographie3 homographie4 homographie5
#include "lang_titles.inc"
#include "author.inc"
\precision{100}
#include "vartab.inc"
\integer{b=randint(-10..10)}
\integer{c=randint(1..10)*randint(1,-1)}
\integer{a=randint(1..10)*randint(1,-1)}
\text{f=\a/(x-\b)+\c}
\text{tf=texmath(maxima(\f))}
\rational{xs=\b}
\rational{ys=\c}
\text{variations=\(\searrow),\(\nearrow)}
\text{c_f=\a>0?1,1:2,2}
\text{v=\variations[\c_f]}
\integer{orient=\a>0?1:2}
\text{axe=x=\b}
#if defined TARGET_homographie1
\statement{On considère l'hyperbole d'équation  \(y = f(x)) avec \(f(x) = \tf).
  Quelle est son sens de variation?
<div class="wimscenter">\embed{reply1}</div>
}

\answer{orientation }{\orient;Deux fois décroissante, Deux fois croissante}{type=radio}
#endif
#if defined TARGET_homographie2
\statement{On considère l'hyperbole d'équation \(y = f(x)) avec \(f(x) = \tf).
<ol>
<li><label for="reply1">Pour quelle valeur la fonction \(f) n'est-elle pas définie&nbsp;?</label>
<div class="wimscenter">\embed{reply1,4}</div></li>
<li><label for="reply2">Quelle valeur n'est jamais atteinte par la fonction \(f)?</label>
<div class="wimscenter">\embed{reply2,4}</div></li>
</ol>
}

\answer{valeur non définie }{\xs}{type=numeric}
\answer{valeur non atteinte }{\ys}{type=numeric}
#endif
#if defined TARGET_homographie3
\statement{On considère l'hyperbole d'équation \(y = \tf).
  Quelles sont les coordonnées de son centre de symetrie \(C) ?
<div class="wimscenter"><label for="reply1">\(C)</label>(\embed{reply1,4}, \embed{reply2,4})</div>
}

\answer{Abscisse du centre }{\xs}{type=numeric}
\answer{Ordonnée du centre }{\ys}{type=numeric}
#endif
#if (defined TARGET_homographie5  || defined TARGET_homographie4 )
\integer{b=randint(1..10)*randint(1,-1)}
\integer{c=randint(1..10)*randint(1,-1)}
\integer{a=randint(1..10)*randint(1,-1)}
\integer{c=\b=\c?2*\c}
\text{f=\a/(x-\b)+\c}
\text{tf=texmath(maxima(\f))}
\rational{xs=\b}
\rational{ys=\c}
\text{variations=\(\searrow),\(\nearrow)}
\text{v=\variations[\c_f]}
\integer{orient=\a>0?1:2}
\text{axe=x=\b}
\text{variations=\(\searrow),\(\nearrow)}
\text{pos=\a<0?bottom,top:top,bottom}
\text{c_f=\a>0?1,1:2,2}
\text{monotone=\variations[\c_f]}
\text{yinf=\a>0?\(-\infty),\(+\infty):\(+\infty),\(-\infty)}

#if defined TARGET_homographie4
\integer{off=randint(1..5)}
\rational{xu=\xs-\off}
\rational{xv=\xs+\off}
\rational{yu=evaluate(\f,x=\xu)}
\rational{yv=evaluate(\f,x=\xv)}
\integer{yk1=\a>0?randint(\yv+1..\yv+10):randint(\yu+1..\yu+10)}
\integer{yk2=\a>0?randint(\yu-10..\yu-1):randint(\yv-10..\yv-1)}
\integer{yk3=\a>0?randint(\yu+0.5..\yv-0.5):randint(\yv+0.5..\yu-0.5)}
\integer{yk3= \a<\off ? \ys : \yk3}
\text{questions = \yk1 , \yk2, \yk3}
\text{reponses = 2,2,1}
\text{i =  shuffle(3)}
\text{lstrep=aucune solution, une solution unique, deux solutions distinctes}
\statement{
<ol>
<li>
  Compléter, par les valeurs exactes, le tableau des variations sur [\xu;\xv] de
  la fonction \(f) définie  par \(f(x) = \tf).
<table class="tab_var">
<tr>
  <th style="width:15%"> \(x)</th>
  <td style="width:15%;text-align:left"> \xu</td>
  <td style="width:8%"></td>
  <td style="width:8%"></td>
  <td style="width:2%">\embed{reply1,1}</td>
  <td style="width:8%"></td>
  <td style="width:8%;"></td>
  <td style="width:15%;text-align:right">\xv</td>
</tr><tr>
  <th style="width:15%">\(var f)</th>
  <td style="width:15%;text-align:left" valign="\pos[1]">\embed{reply2,5}</td>
  <td style="width:8%"> \monotone[1] </td>
  <td style="width:8%" valign="\pos[2]"> \yinf[1] </td>
  <td style="width:1%;color:red">||</td>
  <td style="width:15%" valign="\pos[1]"> \yinf[2] </td>
  <td style="width:8%"> \monotone[2]</td>
  <td style="width:15%;text-align:right" valign="\pos[2]">  \embed{reply3,5} </td>
  </tr>
</table>
</li>
<li> Par lecture du tableau, donner le nombre de solutions sur [\xu;\xv] des équations suivantes:
 <ol>
<li>\(f(x) = \questions[\i[1]]):\embed{reply4} </li>
<li>\(f(x) = \questions[\i[2]]):\embed{reply5} </li>
<li>\(f(x) = \questions[\i[3]]):\embed{reply6} </li>
</ol>
</li>
</ol>

}

\answer{abscisse du sommet }{\xs}{type=numexp}
\answer{ordonnée gauche}{\yu}{type=numexp}
\answer{ordonnée droite}{\yv}{type=numexp}
\answer{\(f(x) = \questions[\i[1]])}{\reponses[\i[1]];\lstrep}{type=radio}
\answer{\(f(x) = \questions[\i[2]])}{\reponses[\i[2]];\lstrep}{type=radio}
\answer{\(f(x) = \questions[\i[3]])}{\reponses[\i[3]];\lstrep}{type=radio}

#endif
#if defined TARGET_homographie5
\text{f1=texmath(maxima(\a/(x-\b)+\c))}
\text{f2=texmath(maxima(\a/(x+\b)+\c))}
\text{f3=texmath(maxima(\a/(x-\b)-\c))}
\text{f4=texmath(maxima(\a/(x-\c)+\b))}
\text{lstrep=\(\f1),\(\f2),\(\f3),\(\f4)}
\statement{
  Le tableau des variations d'une fonction homographique \(f) est:
<table class="tab_var">
<tr>
  <th style="width:15%">\(x)</th>
      <td style="width:15%;text-align:left"> \(-\infty)</td>
      <td style="width:8%"></td>
      <td style="width:8%"></td>
      <td style="width:1%">\xs</td>
      <td style="width:8%"></td>
      <td style="width:8%"></td>
      <td style="width:15%;text-align:right">\(+\infty)</td>
</tr><tr>
  <th style="width:15%" valign="middle">\(var f)</th>
     <td style="width:15%;text-align:left" valign="\pos[1]"> \ys </td>
     <td style="width:8%"> \monotone[1] </td>
     <td style="width:8%" valign="\pos[2]"> \yinf[1] </td>
  <td style="width:1%;color:red">||</td>
     <td style="width:15%" valign="\pos[1]"> \yinf[2] </td>
     <td style="width:8%"> \monotone[2]</td>
     <td style="width:15%;text-align:right" valign="\pos[2]">\ys  </td>
      </tr>
</table>
  Retrouver parmi les expressions suivantes, une expression possible pour \(f(x)):
<ul>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
</ul>
}
\answer{expression possible}{1;\lstrep}{type=radio}{option=shuffle}
#endif
#endif
