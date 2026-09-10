target=sommation2
#include "lang_titles.inc"
#include "author.inc"
\description{Simplifier une expression comportant deux sommes ayant le même nombre de termes}
\integer{h=randint(0..3)*random(-1,1)}
\integer{l=randint(0..3)*random(-1,1)}
\integer{l=\l=\h? \l+randint(1..3)}
\integer{S=randint(5..6)}
\integer{N=\h+\S-1}
\integer{M=\l+\S-1}

\integer{a=randint(2..3)}
\integer{b=randint(2..4)*random(1,-1)}
\text{n=randitem(n,i,j,t,r)}
\text{an=randitem(\b*\a^\n,\a*\n+(\b),\b*\n^(\a-1),(\b*\n)^\a)}
\text{an=simplify(\an)}
\text{antex=texmath(\an)}
\text{bn=randitem(\b*\a^\n,\a*\n+(\b),\b*\n^(\a-1),(\b*\n)^\a)}
\text{bn=simplify(\bn)}
\text{bntex=texmath(\bn)}
\real{A=0}
\for{k=\h to \N}{\real{A=\A+evalue(\an,\n=\k)}}
\real{B=0}
\for{k=\l to \M}{\real{B=\B+evalue(\bn,\n=\k)}}
\real{C=\A+\B}
\text{an1=simplify(evalue(\an,\n=\n+\h-1))}
\text{bn1=simplify(evalue(\bn,\n=\n+\l-1))}
\text{cn=simplify(\an1+\bn1)}
\text{an1tex=texmath(\an1)}
\text{bn1tex=texmath(\bn1)}
\text{cntex=texmath(\cn)}
\integer{terme=0}
\integer{variable=0}
\statement{<div>On note \(S\) l'expression suivante</div>
<div class="wimscenter">
\(\displaystyle{S = \sum_{\n = \h }^{\N } \antex }\) +
\(\displaystyle{\sum_{\n=\l }^{\M } \bntex}\)
</div>
<div class="wims_question">
  Écrire \(S\) sous la forme d'une somme unique :
  <div class="wimscenter">
  <label for="reply1">\(\displaystyle{\large{S=\sum_{\n=1}^\S }}\)</label> \embed{reply 1,10}
  </div>
</div>
}

\answer{}{\rep}{type=formal}
\real{u=0}
\text{rep1=wims(rawmath \rep)}
\for{k=1 to \S}{\real{u=\u+evalue(\rep1,\n=\k)}}

\condition{Somme exacte}{\u=\C}
\text{ style1 = border:1px solid #ffcc66;
  margin:0 5%;
  color:black;
  padding:0.5%;
  margin:0 5%;
}

\if{\n isvariableof \rep1}{\integer{variable=1}}{\integer{variable=0}}
\integer{terme=simplify(\an+(\bn)-(\reply1))}
\feedback{\variable=0}{<div style="\style1">Attention au nom de l'indice de sommation.</div> }
\feedback{\terme=0 and \u!=\C}{<div style="\style1">
  Pour pouvoir regrouper les termes généraux de deux sommes,
  il faut que les indices des deux sommes varient dans le même ensemble d'entiers.
  </div>}
\solution{
\if{\terme=0 or \variable=0}{Une réponse est :
<div class="wimscenter">\(\displaystyle{ S = \sum_{\n=1 }^{\S }(\cntex)}\) .</div>}
{Une façon de mener la transformation est de faire un changement de variable sur chaque somme pour se ramener à des sommes dont l'indice varie de 1 à \S :
<div class="wimscenter">\(\displaystyle{S = \sum_{\n=1}^{\S} (\an1tex)} \) + \(\displaystyle{\sum_{\n=1}^{\S} (\bn1tex) }\).</div>
On peut maintenant regrouper les deux sommes en une seule :
<div class="wimscenter">\(\displaystyle{S = \sum_{\n=1}^{\S} (\cntex)}\) .</div>}
}
\hint{Voici deux exemples montrant comment écrire des expressions dans les champs de réponse :
<ul><li> \(\a\n\) s'écrit <span class="tt">\a*\n</span></li><li> \(\n^2\)
  s'écrit <span class="tt">\n^2</span></li></ul> }
