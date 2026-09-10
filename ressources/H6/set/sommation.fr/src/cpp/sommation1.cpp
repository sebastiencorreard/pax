target=sommation
#include "lang_titles.inc"
#include "author.inc"
\description{Une suite de nombre est proposée. Il s'agit d'écrire la somme ou le produit de ces nombres à l'aide des opérateurs somme ou produit.}
\observation{L'énoncé propose soit un produit, soit une somme à compléter. Le terme général est de la forme b*a^n, a*n+b, b*n^(a-1) ou (b*n)^a}
\integer{N=randint(6..9)}
\integer{a=randint(2..3)}
\integer{b=randint(1..4)*random(1,-1)}
\text{n=randitem(n,i,j,t,r)}
\integer{h=randint(-1..2)}
\integer{N1=\N+\h-1}
\integer{choix=random(1,2)}
\text{ast=item(\choix,+,*)}
\text{som=item(\choix,\sum,\prod)}
\text{lasomme=item(\choix,la somme, le produit)}
\text{delasomme=item(\choix,de la somme, du produit)}
\text{unesomme=item(\choix,d'une somme, d'un produit)}
\text{analsomme=item(\choix,La somme est correcte, Le produit est correct)}
\if{\choix=1}{
  \text{an=randitem(\b*\a^\n,\a*\n+(\b), \b*\n^(\a-1),(\b*\n)^\a)}
}{
  \integer{bs = abs(\b)}
  \text{an=randitem(\b*\a^\n,\a*\n+\bs,-\a*\n-\bs,\b*\n^(\a-1),(\b*\n)^\a)}
}

text{an = \confparm1 = 1 ? randitem(\b*\a^\n,\a*\n+(\b))}
\text{an1=simplify(\an)}
\text{an1=simplify(evalue(\an,\n=(\n-\h+1)))}
\text{texan1=texmath(\an1)}
\for{k=1 to \N}{
  \real{u=evalue(\an,\n=\k)}
  \if{\k=1}{
    \text{S=\u}
    \integer{somme=\u}
  }{
    \text{S=\S,  \u}
    \integer{somme=\somme\ast \u}
  }
}

\text{ style4 = background-color: #FFEECD;
  margin : 5% 5%;
  text-align : center ;
  color : black;
  padding :1%;
}
\text{ style1 = border-left:2px solid red;
  margin : 0 2%;
  color : black;
  padding : 1%;}

\text{name_indice=Plus grande valeur pour l'indice}
\text{name_terme=Terme général}
\statement{Voici un ensemble d'entiers :
<p style="\style4">\leftbrace1 \S \rightbrace1</p>
<div class="wims_question">
On peut écrire \lasomme de ses éléments sous la forme \unesomme
ayant le même nombre de termes,
en trouver l'expression :
<div class="wimscenter">
\special{mathmlinput [\large{\displaystyle{\som _{\n = \h}^{reply1}reply2}}],2
reply1
reply2,7}
</div>
</div>
}
\answer{\name_indice}{\N1}{type=formal}
\answer{\name_terme}{\rep2}{type=formal}

\integer{somme1=\ast issametext + ? 0:1}
\for{k=\h to \reply1}{
  \integer{u=evalue(\rep2,\n=\k)}
  \integer{somme1=\somme1 \ast \u}
}

\condition{\analsomme }{\somme1=\somme}

\feedback{\somme1<>\somme}{Une réponse est
<div class="wimscenter">
\if{\ast issametext +}{\(\displaystyle{\sum_{\n=\h}^{\N1}}\)}
{\(\displaystyle{\prod_{\n=\h}^{\N1}}\)}\(\texan1\).</div>
}


\feedback{\N1 <> \reply1}{<div style="\style1"> Le nombre de termes
n'est pas bon car la règle du jeu est qu'il y en ait \(\N\). </div>}
\text{test = pari(print(\an1 - (\reply2) == 0))}
\feedback{\test = 1 and \N1 <> \reply1 }{<div style="\style1">Cependant, l'expression du terme général
\delasomme est correcte. Faites attention au nombre de termes la prochaine fois.</div> }
\text{var = \n isvariableof \reply2 ? 1: 0}
\feedback{\var=0}{<div style="\style1">Attention au nom de l'indice de sommation.</div> }
