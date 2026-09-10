target=vartrinome1 vartrinome2 vartrinome3 vartrinome4 vartrinome5
\keywords{function_variation,trinomial}
\author{Régine, Mangeard;Maguy, Bruno}
\email{regine@mangeard.fr}
\format{html}
\precision{100}
#if defined TARGET_vartrinome1
# define NUM 1
#endif
#if defined TARGET_vartrinome2
# define NUM 2
#endif
#if defined TARGET_vartrinome3
# define NUM 3
#endif
#if defined TARGET_vartrinome4
# define NUM 4
#endif
#if defined TARGET_vartrinome5
# define NUM 5
#endif
#include "lang_titles.inc"
\integer{b=randint(-10..10)}
\integer{c=randint(-10..10)}
#if (defined TARGET_vartrinome1 || defined TARGET_vartrinome2)
# if defined TARGET_vartrinome1
\rational{a=random(0.5,1,2,3,4,5,6,7,8,9,10)}
# else
\rational{a=-random(0.5,1,2,3,4,5,6,7,8,9,10)}
# endif
\text{f=\a*x^2+\b*x+\c}
\text{tf=texmath(maxima(\f))}
\rational{xs=-\b/(2*\a)}
\rational{ys=evaluate(\f,x=\xs)}
\text{variations=\(\searrow),\(\nearrow)}
\text{c_f=\a>0?1,2:2,1}
\text{v=\variations[\c_f]}
\text{name_question=Compléter le tableau des variations de la fonction \(f\) telle que}
\text{name_instruction=Donner les valeurs exactes des coordonnées du sommet
  de la parabole.}
\statement{
  \name_question \(f(x)=\tf\).

<div class="wims_instruction">\name_instruction</div>

<table class="wimsborder wimscenter">
<tr>
<th style="width:10%">\(x\)</th>
<td style="width:40%;text-align:left">\(-\infty\)</td>
<td style="width:10%"> \embed{reply1,5} </td>
<td style="width:40%;text-align:right">\(+\infty\)</td>
</tr><tr>
<th style="width:10%">\(var f\)</th>
<td style="width:40%"> \embed{reply2} </td>
<td style="width:10%"> \embed{reply3,5} </td>
<td style="width:40%"> \embed{reply4} </td>
</tr>
</table>
}

\answer{abscisse du sommet }{\xs}{type=numexp}
\answer{monotonie 1 }{\v[1] }{type=clickfill}{option = shuffle}
\answer{ordonnée du sommet}{\ys}{type=numexp}
\answer{monotonie 2}{\v[2] }{type=clickfill}{option = shuffle}
#endif
#if defined TARGET_vartrinome3
\rational{a=random(0.5,1,2,3,4,5,6,7,8,9,10)}
*randint(1,-1)
\text{f=\a*x^2+\b*x+\c}
\text{tf=texmath(maxima(\f))}
\rational{xs=-\b/(2*\a)}
\rational{ys=evaluate(\f,x=\xs)}
\text{variations=\(\searrow),\(\nearrow)}
\text{c_f=\a>0?1,2:2,1}
\text{v=\variations[\c_f]}
\integer{off=randint(1..5)}
\rational{xu=\xs-\off}
\rational{xv=\xs+\off}
\rational{yu=evaluate(\f,x=\xu)}
\rational{yv=evaluate(\f,x=\xv)}
\integer{yk=\a>0?randint(\ys+0.5..\yu-0.5):randint(\yu+0.5..\ys-0.5)}
\integer{rep5=(\a>0 and \ys<0 and \yu>0 ) or (\a<0 and \ys>0 and \yu<0)?3:1}
\integer{rep5=\ys=0?2}
\text{lstrep=Aucune solution, une solution unique, deux solutions distinctes}
\statement{
<ol>
<li>
  Compléter, par les valeurs exactes, le tableau des variations de
  la fonction \(f\) définie sur [\xu;\xv] par \(f(x)=\tf\).
<table class="wimsnoborder wimscenter" style="border:solid 1px black">
<tr style="border:solid 1px black">
<th style="width:10%;border:solid 1px black"> \(x\)</th>
<td style="width:40%;text-align:left" colspan="2">\(\xu\)</td>
<td style="width:10%"> \embed{reply1,5} </td>
<td style="width:40%;text-align:right" colspan="2">\(\xv\)</td>
</tr><tr style="border:solid 1px black">
<th style="width:10%;border:solid 1px black">var  \(f\)</th>
<td style="width:10%;text-align:left">\embed{reply2,5}</td>
<td style="width:30%">\v[1] </td>
<td style="width:10%">\embed{reply3,5} </td>
<td style="width:30%">\v[2]</td><td style="width:10%;text-align:right">\embed{reply4,5}</td>
</tr>
</table>
</li>
<li>Par lecture du tableau, donner le nombre de solutions sur [\xu;\xv] des équations suivantes:
 <ol>
<li>\(f(x)=0\):\embed{reply5} </li>
<li>\(f(x)=\ys\):\embed{reply6} </li>
<li>\(f(x)=\yk\):\embed{reply7} </li>
</ol>
</li>
</ol>
}

\answer{abscisse du sommet}{\xs}{type=numexp}
\answer{ordonnée gauche}{\yu}{type=numexp}
\answer{ordonnée du sommet}{\ys}{type=numexp}
\answer{ordonnée droite}{\yv}{type=numexp}
\answer{f(x)=0}{\rep5;\lstrep}{type=radio}
\answer{f(x)=\ys}{2;\lstrep}{type=radio}
\answer{f(x)=\yk}{3;\lstrep}{type=radio}
#endif
#if (defined TARGET_vartrinome4 || defined TARGET_vartrinome5)
#if defined TARGET_vartrinome4
\integer{a=randint(1..10)}
#else
\integer{a=-randint(1..10)}
#endif
\text{variations=\(\searrow),\(\nearrow)}
\text{pos=\a>0?top,bottom,top:bottom,top,bottom}
\text{c_f=\a>0?1,2:2,1}
\text{monotone=\variations[\c_f]}

\integer{s=randint(1..10)*randint(1,-1)}
\integer{b=randint(1..10)*randint(1,-1)}
\integer{b=\b=\s?2*\b}
\integer{fs=randint(-10..10)}
\integer{p=randint(-10..10)}
\integer{p=\p=\fs?\p+randint(1.5)}
\text{f1=texmath(maxima(x^2-\s*x+\p))}
\text{f2=texmath(maxima(\a*x^2-2*\a*\s*x+\a*(\s)^2+\fs))}
\text{f3=texmath(maxima(\a*x^2-\a*(\s+\b)*x+\a*\s*\b+\fs))}
\text{f4=texmath(maxima(-\a*x^2+2*\a*\s*x-\a*(\s)^2+\fs))}
\text{lstrep=\(\f1),\(\f2),\(\f3),\(\f4)}
\statement{
  Le tableau des variations d'une fonction trinôme du second degré \(f\) est:

<table class="wimsnoborder wimscenter">
<tr style="border:solid 1px black">
  <th style="width:15%;border:solid 1px black"> \(x\)</th>
  <td style="width:15%;text-align:left"> \(-\infty\)</td>
  <td style="width:8%"></td>
  <td style="width:15%">\s</td>
  <td style="width:8%"></td>
  <td style="width:15%;text-align:right">\(+\infty\)</td>
</tr><tr style="border:solid 1px black">
  <th style="width:15%:border:solid 1px black;vertical-align: middle;">\(var f\)</th>
  <td style="width:15%;text-align:left; vertical-align:\pos[1]"></td>
  <td style="width:8%">\monotone[1] </td>
  <td style="width:15%;vertical-align:\pos[2]">\fs</td>
  <td style="width:8%">\monotone[2]</td>
  <td style="width:15%;text-align:right;vertical-align:\pos[3]"></td>
 </tr>
</table>

  Retrouver parmi les expressions suivantes, une expression possible pour \(f(x)\):
<ul>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
</ul>
}
\answer{expression possible}{2;\lstrep}{type=radio}{option=shuffle}
#endif
