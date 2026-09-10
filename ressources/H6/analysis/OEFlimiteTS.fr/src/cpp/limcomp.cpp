target=limcomp1 limcomp2 limcomp3 limcomp4
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
#if defined TARGET_limcomp1
#define NUM 1
#endif
#if defined TARGET_limcomp2
#define NUM 2
#endif
#if defined TARGET_limcomp3
#define NUM 3
#endif
#if defined TARGET_limcomp4
#define NUM 4
#endif
#include "lang_titles.inc"
\text{infd=\(+\infty\)}
\text{infg=\(-\infty\)}
\text{zero=\(0\)}
\text{sans=sans limite}
\text{size=80x30x1}
\text{listinf=\infd, \infg}
\text{lstlim=a une limite finie nulle, a une limite finie non nulle, a une limite infinie, n'a pas de limite}
\text{size=50x20x1}

#if defined TARGET_limcomp2
\text{alist=wims(makelist x,-x for x=1 to 10)}
\text{alist=shuffle(\alist)}
\integer{a=\alist[1]}
\integer{b=\alist[2]}
\integer{c=\alist[3]}
 \integer{e=randint(1..10)*randint(1,-1)}
 \integer{d=randint(1..10)*randint(1,-1)}
 \integer{h=\d+randint(1..10)*randint(1,-1)}
 \integer{h=\h=0?2*\d}

\integer{cas=randint(1..9)}

///integer{cas=9}

\if{\cas=1}{
 \text{numf=maxima(expand((x-\a)*(x-\a+\b)))}
 \text{f=(\numf)/(x-\a)}
 \text{ft=texmath((\numf)/(x-\a))}
 \text{numg=maxima(expand((x-\b)*(x-\b+\c)))}
 \text{g=(\numg)/(x-\b)}
 \text{gt=texmath((\numg)/(x-\b))}
 \integer{nat=1}
 \integer{replim=\c}
 \text{mstep=r1
r2}
 }
\if{\cas=2}{
 \text{numf=maxima(expand((x-\a)*(x-\a+\b)))}
 \text{f=(\numf)/(x-\a)}
 \text{ft=texmath((\numf)/(x-\a))}
 \text{g=\e/(x-\b)^2}
 \text{gt=texmath(\e/(x-\b)^2)}
 \integer{nat=2}
 \text{repinf=\e>0?\infd:\infg}
 \text{mstep=r1
r3}
 }
\if{\cas=9}{
 \text{numf=maxima(expand((x-\a)*(x-\a+\b)))}
 \text{f=(\numf)/(x-\a)}
 \text{ft=texmath((\numf)/(x-\a))}
 \text{g=\e/(x-\b)^2}
 \text{gt=texmath(\e/(x-\b))}
 \integer{nat=3}
 \text{mstep=r1}
 }

\if{\cas=3}{
 \text{g=(\c*x+\d)/(x+\h)}
 \text{gt=texmath((\c*x+\d)/(x+\h))}
 \text{f=\e/(x-\a)^2}
 \text{ft=texmath(\e/(x-\a)^2)}
 \integer{nat=1}
 \integer{replim=\c}
 \text{mstep=r1
r2}
 }

\if{\cas=4}{
 \text{g=(\c*x^2+\d)/(x+\h)}
 \text{gt=texmath((\c*x^2+\d)/(x+\h))}
 \text{f=\e/(x-\a)^2}
 \text{ft=texmath(\e/(x-\a)^2)}
 \integer{nat=2}
 \text{repinf=\e*\c>0?\infd:\infg}
 \text{mstep=r1
r3}
 }

\if{\cas=5}{
 \text{a=randitem(+\infty,-\infty)}
 \text{f=(\b*\e*x+\d)/(\e*x+\h)}
 \text{ft=texmath((maxima(\b*\e*x+\d))/(\e*x+\h))}
 \text{numg=maxima(expand((x-\b)*(x-\b+\c)))}
 \text{g=(\numg)/(x-\b)}
 \text{gt=texmath((\numg)/(x-\b))}
 \integer{nat=1}
 \integer{replim=\c}
 \text{mstep=r1
r2}
 }

\if{\cas=6}{
 \text{a=randitem(+\infty,-\infty)}
 \text{f=(\b*\e*x+\d)/(\e*x+\h)}
 \text{ft=texmath((maxima(\b*\e*x+\d))/(\e*x+\h))}
 \text{g=(x-\c)/(x-\b)^2}
 \text{gt=texmath((x- \c)/(x-\b)^2)}
 \integer{nat=2}
 \text{repinf=\b-\c>0?\infd:\infg}
 \text{mstep=r1
r3}
 }

\if{\cas=7}{
 \text{a=randitem(+\infty,-\infty)}
 \text{f=(\b*\e*x^2+\d)/(\e*x+\h)}
 \text{ft=texmath((maxima(\b*\e*x^2+\d))/(\e*x+\h))}
 \text{g=(\e*\c*x^2+\b)/(\e*x^2+\d)}
 \text{gt=texmath((maxima(\c*\e*x^2+\b))/(\e*x^2+\d))}
 \integer{nat=1}
 \integer{replim=\c}
 \text{mstep=r1
r2}
 }

\if{\cas=8}
 {
 \text{a=randitem(+\infty,-\infty)}
 \text{f=(\b*\e*x^2+\d)/(\e*x+\h)}
 \text{ft=texmath((maxima(\b*\e*x^2+\d))/(\e*x+\h))}
 \text{g=(\e*\c*x^2+\b)/(\e*x^2+\d)}
 \text{gt=texmath((maxima(\c*\e*x^2+\b))/(\e*x+\d))}
 \integer{nat=2}
 \if{\a=+\infty}{
    \text{repinf=\b*\c>0?\infd:\infg}
   }{
    \text{repinf=\b*\c<0?\infd:\infg}
   }
 \text{mstep=r1
r3}
 }

\steps{\mstep}
\statement{
  On considère les fonctions \(f) et \(g) définies par
<div class="wimscenter">\(f(x) = \ft) et \(g(x) = \gt\).</div>
  <p>Déterminer \(\displaystyle\lim_{x \rightarrow \a} g \circ f(x)).</p>
\if{\step=1}{
  Cette limite
<ul class="wims_nopuce">
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}
</li></ul>
}
\if{\step=2 and \nat=1}{
  <label for="reply2">Cette limite est finie, que vaut-elle ?</label> \embed{reply2,7}
}
\if{\step=2 and \nat=2}{
  Cette limite est infinie, que vaut-elle ? \embed{reply3,\size}
 }
}
\answer{nature de la limite}{\nat;est finie, est infinie, n'existe pas}{type=radio}
\answer{limite finie}{\replim}{type=numeric}
\answer{limite infinie}{\repinf;\listinf}{type=clickfill}

#endif
#if defined TARGET_limcomp1
\text{alist=wims(makelist x,-x for x=1 to 10)}
\text{alist=shuffle(\alist)}
\integer{a=\alist[1]}
\integer{b=\alist[2]}
\integer{c=\alist[3]}
\integer{d=\alist[4]}

\integer{cas=randint(1,4)}
///
integer{cas=1}

\text{lstpos=bottom,top,bottom,top}
\text{lstarrow=\(\nearrow\),\(\searrow\)}
 \integer{nata=randint(1,2)}
///
 integer{nata=1}
 \integer{indf=randint(1,2)}
 \integer{natb=randint(1,2)}
///
 integer{natb=2}
 \text{ta=\a}
 \text{txa=\a}
 \text{tb=\b}
 \text{txb=\b}

\if{\nata=1}{
  \integer{a=\cas=1?1000:-1000}
  \text{ta=\cas=1?\infd:\infg}
  \text{txa=\cas=1?+\infty:-\infty}
  }
\if{\cas=1}{
 \if{\natb=1}{
  \integer{b=\indf=1?1000:-1000}
  \integer{b=\a=1000?-1000}
  \text{tb=\b=1000?\infd:\infg}
  \integer{indf=\a=1000?2}
 }
 \text{tabf=<table class="wimscenter wimsnoborder" style="border: solid black 1px;">
<tr style="border: solid black 1px;">
  <th style="width:15%;border-right: solid black 1px;">\(x)</th>
  <td style="width:15%;text-align:left">\(-\infty)</td>
  <td style="width:8%;"></td>
  <td style="width:15%;text-align:right">\ta</td>
</tr><tr style="border: solid black 1px;">
  <th style="border-right: solid black 1px;width:15%" valign="middle" rowspan="3" >var \(f)</th>
  <td style="width:15%;text-align:left" rowspan="3" valign="\lstpos[\indf]">\listinf[3-\indf]</td>
  <td style="width:8%;" rowspan="3">\lstarrow[\indf]</td>
  <td style="width:15%;text-align:right" rowspan="3" valign="\lstpos[3-\indf]">\tb</td>
</tr>
</table>
}
 }
 {
/// cas=2
 \if{\natb=1}
 {
  \integer{b=\indf=1?1000:-1000}
  \integer{b=\a=-1000?1000}
  \text{tb=\b=1000?\infd:\infg}
  \integer{indf=\b=-1000?1:2}
 }
 \text{tabf=<table class="wimscenter wimsnoborder" style="border: solid black 1px;">
 <tr style="border: solid black 1px;">
  <th style="width:15%;">\(x)</th>
  <td style="width:15%;text-align:left">\ta</td>
  <td style="width:8%;"></td>
  <td style="width:15%;text-align:right">\(+\infty)</td>
 </tr><tr style="border: solid black 1px;">
  <th style="border-right: solid black 1px;width:15%" valign="middle" rowspan="3" >var \(f)</th>
  <td style="width:15%;text-align:left" rowspan="3" valign="\lstpos[\indf]">\tb</td>
  <td style="width:8%;" rowspan="3">\lstarrow[\indf]</td>
  <td style="width:15%;text-align:right" rowspan="3" valign="\lstpos[3-\indf]">
  \listinf[\indf]</td>
</tr>
</table>}
 }

  \text{xsl=\a,\b,\d}
  \text{xl=wims(sort numeric list \xsl)}
  \integer{ia=position(\a,\xl)}
  \integer{ib=position(\b,\xl)}
  \integer{id=position(\d,\xl)}
  \text{xl=wims(replace item -1000 by \infg in \xl)}
  \text{xl=wims(replace item 1000 by \infd in \xl)}
  \integer{ig=randint(1,-1)}
  \text{valg=}
  \integer{v=\c-randint(3..5)*\ig}
  \text{valg=wims(append item \v to \valg)}
  \integer{v=\c+randint(5..10)*\ig}
  \text{valg=wims(append item \v to \valg)}
  \text{valg=wims(append item \c to \valg)}
  \integer{v=\c+randint(5..10)*\ig}
  \text{valg=wims(append item \v to \valg)}
  \integer{v=\c-randint(3..5)*\ig}
  \text{valg=wims(append item \v to \valg)}
  \text{gl=item(4-\ib..6-\ib,\valg)}
  \integer{ig=\gl[1]<\gl[2]?1:2}
  \integer{nat=\ib=2?1:randint(1,2)}
  \if{\nat=1}{
    \integer{replim=\c}
    \text{mstep=r1
r2}
  }{
    \text{tc=\ig=1?\infg:\infd}
    \text{gl=wims(replace item \c by \tc in \gl)}
    \text{repinf=\tc}
    \text{mstep=r1
r3}
  }
 \text{tabg=<table class="wimscenter wimsnoborder" style="border: solid black 1px;">
 <tr style="border: solid black 1px;">
  <th style="border-right: solid black 1px;;width:15%;">\(x)</th>
  <td style="width:15%;text-align:left">\xl[1]</td>
  <td style="width:8%;"></td>
  <td style="width:15%;">\xl[2]</td>
  <td style="width:8%;"></td>
  <td style="width:15%;text-align:right">\xl[3]</td>
</tr><tr style="border: solid black 1px;">
  <th style="border-right: solid black 1px;width:15%" valign="middle" rowspan="3">var \(g)</th>
  <td style="width:15%;text-align:left" rowspan="3" valign="\lstpos[\ig]">\gl[1]</td>
  <td style="width:8%;" rowspan="3">\lstarrow[\ig]</td>
  <td style="width:15%;" rowspan="3" valign="\lstpos[3-\ig]">\gl[2]</td>
  <td style="width:8%;" rowspan="3">\lstarrow[3-\ig] </td>
  <td style="width:15%;" rowspan="3" valign="\lstpos[\ig]">\gl[3]</td>
 </tr>
</table>
}

\steps{\mstep}
\statement{
  On considère les fonctions \(f) et \(g) dont on connaît les tableaux de variations:
<div class="wimscenter">\tabf et \tabg</div>
<p>
  Déterminer \(\displaystyle\lim_{x \rightarrow \txa} g \circ f(x)).
</p>
\if{\step=1}{
Cette limite
<ul class="wims_nopuce">
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
</ul>
}
\if{\step=2 and \nat=1}{
  <label for="reply2">Cette limite est finie, que vaut-elle ?</label> \embed{reply2,7}.
}
\if{\step=2 and \nat=2}{
  Cette limite est infinie, que vaut-elle ? \embed{reply3,\size}
 }
}
\answer{nature de la limite}{\nat;est finie, est infinie, n'existe pas}{type=radio}
\answer{limite finie}{\replim}{type=numeric}
\answer{limite infinie}{\repinf;\listinf}{type=clickfill}

#endif

#if (defined TARGET_limcomp3 || defined TARGET_limcomp4 )
# if defined TARGET_limcomp3
\integer{choix=1}
# else
\integer{choix=2}
# endif
#include "varcomp3data.inc"
\statement{<p>
\intro</p>
\if{\choix=1}
 {\tableau}
 {\draw{300,300}{\dessin}}
<p>Construire le tableau des variations de la fonction \(u= f^2) puis
  celui de la fonction \(v= \frac{1}{f}).
</p>
<div class="wims_instruction">On précisera bien les limites aux bornes
  du domaine de définition, et on placera les espaces nécessaires au bon alignement.
</div>
<ol>
<li>Tableau des variations de \(u):
  <table class="wimscenter wimsborder">
   <tr><th>\(x)</th><td>\embed{reply1,\size}</td></tr>
   <tr><th>\(var u)</th><td>\embed{reply2,\size}</td></tr>
   </table>
</li><li>Tableau des variations de \(v):
  <table class="wimscenter wimsborder">
    <tr><th>\(x)</th><td>\embed{reply3,\size}</td></tr>
    <tr><th>\(var v)</th><td>\embed{reply4,\size}</td></tr>
</table>
</li>
</ol>
}
\answer{}{\grepux;\clicList}{type=clickfill}
\answer{}{\grepuy;\clicList}{type=clickfill}
\answer{}{\grepvx;\clicList}{type=clickfill}
\answer{}{\grepvy;\clicList}{type=clickfill}
#endif
