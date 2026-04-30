target=enchaintvar1 enchaintvar2 enchaintvar3 enchaintvar4 enchaintvar5
#if defined TARGET_enchaintvar1
# define NUM 1
#endif
#if defined TARGET_enchaintvar2
# define NUM 2
#endif
#if defined TARGET_enchaintvar3
# define NUM 3
#endif
#if defined TARGET_enchaintvar4
# define NUM 4
#endif
#if defined TARGET_enchaintvar5
# define NUM 5
#endif
#include "lang_titles.inc"
\language{fr}
\range{-5..5}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}
\css{<style>
table.tab_var {margin-left:auto;margin-right:auto;
   border:solid 1px black;}
table.tab_var tr, table.tab_var td, table.tab_var th {
   padding:7pt;margin-top:10px; margin-bottom:10px;
   text-align:center; border-collapse:collapse; min-width:10pt;
   }
table.tab_var th { border:solid 1px black}
table.tab_var tr { border:solid 1px black}
.big{color:red;font-size:120%;font-weight:bold}
</style>
}
 \integer{numa=randint(1..5)*random(1,-1)}
 \integer{dena=randint(1..5)}
 \rational{a=simplify(\numa / \dena)}
 \integer{numb=randint(1..5)*random(1,-1)}
 \integer{denb=randint(1..5)}
 \rational{b=simplify(\numb / \denb)}
 \integer{numc=randint(1..5)*random(1,-1)}
 \integer{denc=randint(1..5)}
 \rational{c=simplify(\numc / \denc)}
 \integer{numd=randint(1..5)*random(1,-1)}
 \integer{dend=randint(1..5)}
 \rational{d=simplify(\numd / \dend)}
 \integer{ia=random(1,-1)}
 \integer{ib=random(1,-1)}
 \integer{ic=random(1,-1)}
 \text{sa=\ia=1?:-}
 \text{sb=\ib=1?+:-}
 \text{sc=\ic=1?:-}
 \text{ta=\a=1?:texmath(\a)}
 \text{tb=\b=1?:texmath(\b)}
 \text{tc=\c=1?:texmath(\c)}
 \function{aff1=texmath(maxima(\a*x+\b))}
 \function{aff2=texmath(maxima(\c*x+\d))}
 \text{crocg=&#91;}
 \text{crocd=&#93;}
 \text{crochg=\crocg}
 \text{crochd=\crocd}
 \text{ptvirg=&#59;}
 \text{infg=\(-\infty)}
 \text{infd=\(+\infty)}
 \text{lstvar=croissante,décroissante}
\text{variations = \(\nearrow),\(\searrow)}
 \rational{ac=\a*\c}
 \rational{b1=simplify(-(\b) / (\a))}

#if defined TARGET_enchaintvar1
 \function{fref=texmath(x^2)}
 \function{f=texmath(\c*(\a*x+\b)^2+\d)}
 \integer{ind1=\ac>0?2:1}
 \integer{ind2=\ac>0?1:2}
 \integer{indb1=\ac>0?1:2}
 \integer{indb2=\ac>0?2:1}
#endif
#if defined TARGET_enchaintvar2
 \function{fref=texmath(1/x)}
 \function{f=texmath(\c/(\a*x+\b)+\d)}
 \text{crochg=\crocd}
 \text{crochd=\crocg}
 \integer{ind1=\ac>0?2:1}
 \integer{ind2=\ac>0?2:1}
 \integer{indb1=\ac>0?1:2}
 \integer{indb2=\ac>0?1:2}
#endif
#if defined TARGET_enchaintvar3
 \function{fref=texmath(x^2)}
 \function{f=texmath(\c*(\a*x+\b)^2+\d)}
\text{c_comp=\ac>0?2,1:1,2}
\text{v2=\variations[\c_comp]}
#endif
#if defined TARGET_enchaintvar4
 \function{fref=texmath(1/x)}
 \function{f=texmath(\c/(\a*x+\b)+\d)}
\text{c_comp=\ac>0?2,2:1,1}
\text{v2=\variations[\c_comp]}
#endif

 \text{e1=\(\begin{array}{ccccccc}& \aff1&&\fref&&\aff2&\\ x & \longmapsto &\cdots &\longmapsto & \cdots & \longmapsto & \cdots\end{array})}
\text{var1=\(f) est \lstvar[\ind2] sur \crochg \b1 \ptvirg \infd \crocg}
\text{var2=\(f) est \lstvar[\ind1] sur \crocd \infg \ptvirg \b1 \crochd}
\text{var3=\(f) est \lstvar[\indb2] sur \crochg \b1 \ptvirg \infd \crocg}
\text{var4=\(f) est \lstvar[\indb1] sur \crocd \infg \ptvirg \b1 \crochd}

#if defined TARGET_enchaintvar5
 \integer{k=random(1,2)}
 \if{\k=1}{
    \function{fref=texmath(x^2)}
    \function{f1=\(texmath(maxima(\c*(\a*x+\b)^2+\d)))}
    \function{f2=\(texmath(maxima(\c/(\a*x+\b)+\d)))}
    \function{f3=\(texmath(maxima(\c*(\a*x-\b)^2+\d)))}
    \function{f4=\(texmath(maxima(-\c*(\a*x+\b)^2+\d)))}

    \text{c_comp=\ac>0?2,1:1,2}
    \text{v2=\variations[\c_comp]}
    \text{listf=\f1,\f2,\f3,\f4}
  }
  {
    \function{fref=texmath(1/x)}
    \function{f1=\(texmath(maxima(\c/(\a*x+\b)+\d)))}
    \function{f2=\(texmath(maxima(\c*(\a*x+\b)^2+\d)))}
    \function{f3=\(texmath(maxima(\c/(\a*x-\b)+\d)))}
    \function{f4=\(texmath(maxima(-\c/(\a*x+\b)+\d)))}
    \text{c_comp=\ac>0?2,2:1,1}
    \text{v2=\variations[\c_comp]}
    \text{listf=\f1,\f2,\f3,\f4}
  }

#endif

\text{liste=\var1,\var2,\var3,\var4}
\statement{
#if defined TARGET_enchaintvar5
  On considère une fonction \(f) donnée par son tableau des variations:
<table class="tab_var">
<tr>
 <th style="width:10%"> \(x)</th>
 <td style="width:30%;text-align:left">-\(\infty)</td>
 <td style="width:5%">\b1</td>
 <td style="width:30%;text-align:right">+\(\infty)</td>
</tr><tr>
<th style="width:10%">\(f)</th><td style="width:30%"> \v2[1] </td><td style="width:5%">
\if{\k=1}
{\d}
{ &#124;&#124;}
</td><td style="width:30%"> \v2[2] </td>
</tr>
</table>
  Cocher l'expression algébrique pouvant lui correspondre.
<ul>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
</ul>}

\answer{Enchainement ?}{1;\listf}{type=radio}{option=shuffle}
#else
  On considère une fonction \(f) définie par l'enchainement de fonctions de référence:
<div class="wimscenter"> \e1.</div>
#if (defined TARGET_enchaintvar1 || defined TARGET_enchaintvar2 )
  Cocher les bonnes réponses.
<ol>
<li> \embed{reply1,1}</li>
<li> \embed{reply1,2}</li>
<li> \embed{reply1,3}</li>
<li> \embed{reply1,4}</li>
</ol>
}
\answer{Enchainement ?}{1,2;\liste}{type=checkbox}{option=shuffle}
#endif
#if (defined TARGET_enchaintvar3 || defined TARGET_enchaintvar4 )
  Remplir le tableau de variations&nbsp;:
<table class="tab_var">
<tr>
 <th style="width:10%"> \(x)</th>
 <td style="width:30%;text-align:left">-\(\infty)</td>
 <td style="width:5%">\embed{reply1,5}</td>
 <td style="width:30%;text-align:right">+\(\infty)</td>
</tr><tr>
 <th style="width:10%">\(f)</th>
 <td style="width:30%">\embed{reply2}</td>
 <td style="width:5%">
#if defined TARGET_enchaintvar3
\embed{reply4,5}
#else
&#124;&#124;
#endif
</td><td style="width:30%"> \embed{reply3} </td>
</tr>
</table>

}
\answer{abscisse du sommet pour f }{\b1}
\answer{monotonie 1 }{\v2[1];\variations }{type=clickfill}{option = shuffle}
\answer{monotonie 1}{\v2[2];\variations }{type=clickfill}{option = shuffle}
#if defined TARGET_enchaintvar3
\answer{ordonnée du sommet}{\d}
#endif

#endif

#endif
