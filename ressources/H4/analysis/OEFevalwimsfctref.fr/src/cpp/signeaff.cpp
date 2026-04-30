target=signeaff1 signeaff2 signeaff3 signeaff4 signeaff5

#if defined TARGET_signeaff1
# define NUM 1
#endif
#if defined TARGET_signeaff2
# define NUM 2
#endif
#if defined TARGET_signeaff3
# define NUM 3
#endif
#if defined TARGET_signeaff4
# define NUM 4
#endif
#if defined TARGET_signeaff5
# define NUM 5
#endif
#include "lang_titles.inc"
author{Régine, Mangeard}
\email{regine@mangeard.fr}
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
\integer{a=randint(1..9)*randint(1,-1)}
\integer{b=randint(1..9)*randint(1,-1)}
\rational{x0=-\b / \a}
\text{exp=\(texmath(\a*x+\b))}
\text{posi=<span class="big">+</span>}
\text{nega=<span class="big">-</span>}
\text{sg=\a>0?\nega:\posi}
\text{sd=\a<0?\nega:\posi}

\text{clicList=\posi,\nega}
%%%% taille des signes ##
\text{size=30x30x1}

#if defined TARGET_signeaff1
\statement{
  Compléter&nbsp;:<div>
  <label for="reply1">L'expression \exp s'annule et change de signe en \(x=)
  </label>\embed{reply1,3}.</div>
  Puis remplir le tableau des signes suivant&nbsp;:
<table class="tab_var">
  <tr><th>\(x)</th>
  <td style="width:20%">\(-\infty)</td>
  <td style="width:20%">\embed{reply2,3}</td>
  <td style="width:30%">&nbsp;</td>
  <td style="width:20%">\(+\infty)</td>
</tr><tr>
<th>\exp</th>
<td style="width:30%">\embed{reply3,\size}</td>
<td style="width:20%">0</td>
<td style="width:30%">\embed{reply4,\size}</td>
<td style="width:20%">&nbsp;</td>
</tr>
</table>
}
\answer{valeur de x}{\x0}{type=numeric}
\answer{ligne des x}{\x0}{type=numeric}
\answer{signe à gauche}{\sg;\clicList}{type=clickfill}
\answer{signe à droite}{\sd;\clicList}{type=clickfill}
#endif
#if (defined TARGET_signeaff2  || defined TARGET_signeaff3 )
#if defined TARGET_signeaff2
\integer{x1=\x0+randint(1..9)}
\text{symb=\a>0?>:<}
\text{cond2=\(f(\x1) \symb 0)}
#endif
#if defined TARGET_signeaff3
\text{monotone=\a>0?croissante:décroissante}
\text{cond2=\(f) est \monotone}
#endif

\statement{
  On considère une fonction affine \(f) telle que
<ol><li>\(f(\x0)=0)</li>
<li>\cond2 </li>
</ol>
  Remplir le tableau des signes suivant&nbsp;:
<table class="tab_var"><tr>
<th>\(x)</th>
<td style="width:20%">\(-\infty)</td>
<td style="width:30%">&nbsp;</td>
<td style="width:20%">\embed{reply1,3}</td>
<td style="width:30%">&nbsp;</td>
<td style="width:20%">\(+\infty)</td>
</tr><tr>
<th>\(f(x)\)</th>
<td style="width:20%">&nbsp;</td>
<td style="width:30%">\embed{reply2,\size}</td>
<td style="width:20%">0</td>
<td style="width:30%">\embed{reply3,\size}</td>
<td style="width:20%">&nbsp;</td>
</tr>
</table>
}
\answer{ligne des x}{\x0}{type=numeric}
\answer{signe à gauche}{\sg;\clicList}{type=clickfill}
\answer{signe à droite}{\sd;\clicList}{type=clickfill}
#endif

#if (defined TARGET_signeaff4  || defined TARGET_signeaff5 )
\integer{a2=randint(1..9)*randint(1,-1)}
\integer{b2=randint(1..9)*randint(1,-1)}
\rational{x1=-\b2 / \a2}
\rational{x1=\x0=\x1?\x1+1}
\text{sgf=\a>0?\nega:\posi}
\text{sdf=\a<0?\nega:\posi}
\text{sgg=\a2>0?\nega:\posi}
\text{sdg=\a2<0?\nega:\posi}
\text{zero=<span class="big">0</span>}
\text{interdit=<span class="big">&#124;&#124;</span>}
\text{clicList=\clicList,\zero,\interdit}
\rational{val1=\x0<\x1?\x0:\x1}
\rational{val2=\x0<\x1?\x1:\x0}

\integer{aa=\a*\a2}
\text{s1=\aa>0?\posi:\nega}
\text{s2=\aa<0?\posi:\nega}

#if defined TARGET_signeaff4
\text{quest=du produit \(f \times g)}
\text{lignef=\(f(x) \times g(x))}
\text{v1=\zero}
\text{v2=\zero}
#endif
#if defined TARGET_signeaff5
\text{quest=du quotient \(\frac{f}{g})}
\text{lignef=\(\frac{f(x)}{g(x)})}
\text{v1=\x0<\x1?\zero:\interdit}
\text{v2=\x0<\x1?\interdit:\zero}
#endif
\statement{
  On considère deux fonctions affines \(f) et \(g)
  dont les tableaux des signes sont donnés ci-dessous&nbsp;:
<table class="tab_var"><tr>
<th>\(x)</th>
<td style="width:20%">\(-\infty)</td>
<td style="width:30%">&nbsp;</td>
<td style="width:20%">\x0</td>
<td style="width:30%">&nbsp;</td>
<td style="width:20%">\(+\infty)</td>
</tr><tr>
<th>\(f(x)\)</th>
<td style="width:20%">&nbsp;</td>
<td style="width:30%">\sgf</td>
<td style="width:20%">0</td>
<td style="width:30%">\sdf</td>
<td style="width:20%">&nbsp;</td>
</tr>
</table>
<br class="spacer">
<table class="tab_var">
<tr>
<th>\(x)</th>
<td style="width:20%">\(-\infty)</td>
<td style="width:30%">&nbsp;</td>
<td style="width:20%">\x1</td>
<td style="width:30%">&nbsp;</td>
<td style="width:20%">\(+\infty)</td>
</tr><tr>
<th>\(g(x)\)</th>
<td style="width:20%">&nbsp;</td>
<td style="width:30%">\sgg</td>
<td style="width:20%">0</td>
<td style="width:30%">\sdg</td>
<td style="width:20%">&nbsp;</td>
</tr>
</table>
  Remplir le tableau des signes \quest.
<table class="tab_var">
<tr>
<th>\(x)</th>
<td style="width:10%">\(-\infty)</td>
<td style="width:20%">&nbsp;</td>
<td style="width:10%">\embed{reply1,3}</td>
<td style="width:20%">&nbsp;</td>
<td style="width:10%">\embed{reply2,3}</td>
<td style="width:20%">&nbsp;</td>
<td style="width:10%">\(+\infty)</td>
</tr><tr>
<th>\lignef</th>
<td style="width:10%">&nbsp;</td>
<td style="width:20%">\embed{reply3,\size}</td>
<td style="width:10%">\embed{reply4,\size}</td>
<td style="width:20%">\embed{reply5,\size}</td>
<td style="width:10%">\embed{reply6,\size}</td>
<td style="width:20%">\embed{reply7,\size}</td>
<td style="width:10%">&nbsp;</td>
</tr>
</table>
}
\answer{}{\val1}{type=numeric}
\answer{}{\val2}{type=numeric}
\answer{signe à gauche}{\s1;\clicList}{type=clickfill}
\answer{valeur gauche}{\v1;\clicList}{type=clickfill}
\answer{signe au milieu}{\s2;\clicList}{type=clickfill}
\answer{valeur droite}{\v2;\clicList}{type=clickfill}
\answer{signe à droite}{\s1;\clicList}{type=clickfill}
#endif
