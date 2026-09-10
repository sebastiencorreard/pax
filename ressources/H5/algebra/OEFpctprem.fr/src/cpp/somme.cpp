target=somme1 somme2 somme3 somme4 somme5

\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{100}
#define TITLE Somme de proportions
#if defined TARGET_somme1
\title{TITLE 1}
\text{lstrep=C'est possible,C'est impossible}
\integer{a=randint(2..6)}
\integer{b=\a+randint(1..3)}
\integer{c=randint(2..6)}
\integer{d=\c+randint(1..3)}
\integer{rep=randint(1,2)}
\if{\rep=1}{
  \integer{d=\b}
  \integer{c=\b-\a}
}{
 \integer{rep=\a/ \b + \c / \d=1?1}
}
\text{tsol=\rep=1?C'est possible puisque la somme des proportions vaut 1: C'est impossible puisque la somme des proportions ne vaut pas 1}
\rational{x1=simplify(\a / \b)}
\text{x1=\(\x1)}
\rational{x2=simplify(\c / \d)}
\text{x2=\(\x2)}

\statement{
<p>
  Lise affirme que dans sa classe, la part des filles est de \x1 et celle des garçons et de \x2.
 <br>Qu'en pensez-vous&nbsp;?
</p>
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{\rep;\lstrep}{type=radio}
\solution{\tsol.}
#endif

#if defined TARGET_somme2
\title{TITLE 2}
\text{lstrep=C'est possible,C'est impossible}
\text{data=15,3,5,randint(1..5),
12,3,2,randint(1..5),
21,3,7,randint(1..5)}
\text{cedata=randomrow(\data)}
\integer{den=\cedata[1]}
\rational{x1=simplify(\cedata[2] / \den)}
\rational{x2=simplify(\cedata[3] / \den)}
\rational{x3=simplify(\cedata[4] / \den)}
\rational{x4=simplify(1-\x1-\x2-\x3)}
\text{xl=shuffle(\x1,\x2,\x3,\x4)}
\rational{to=\xl[1]}
\rational{pv=\xl[2]}
\rational{pr=\xl[3]}
\rational{co=\xl[4]}
\rational{rouge=\to+\pr}
\rational{vert=\co+\pv}
\text{tsol=
<p>Puisque les proportions portent sur le même ensemble de référence, on peut les ajouter.</p>
<ul class="wims_nopuce">
<li>Part de légumes rouges&nbsp;: \(\to+\pr=\rouge\).</li>
<li>Part de légumes verts&nbsp;: \(\co+\pv=\vert\).</li>
</ul>
}
\statement{
<p>
  Dans une recette de cuisine dans laquelle il faut mélanger des tomates,
  des poivrons et des courgettes, il est indiqué les proportions suivantes&nbsp;:
</p>
<div class="table-scroll">
<table class="wimscenter wimsborder">
<caption>Tableau des proportions</caption>
<tr><th>Légumes</th><th>Proportions</th></tr>
<tr><th>Tomates</th><td>\(\to\)</td></tr>
<tr><th>Poivrons verts</th><td>\(\pv\)</td></tr>
<tr><th>Poivrons rouges</th><td>\(\pr\)</td></tr>
<tr><th>Courgettes</th><td>\(\co\)</td></tr>
</table>
</div>
  <ul><li>
  <label for="reply1">
  Quelle est la part des légumes rouges (tomates et poivrons rouges)&nbsp;?
  </label>\embed{reply1}.
  </li><li>
  <label for="reply2">
  Quelle est la part des légumes verts (courgettes et poivrons verts)&nbsp;?
  </label> \embed{reply2}.
  </li></ul>
}
\answer{}{\rouge}{type=numexp}{option=noreduction}
\answer{}{\vert}{type=numexp}{option=noreduction}

\solution{\tsol}
#endif

#if defined TARGET_somme3
\title{TITLE 3}
\text{lstnom=Marc,Lucie,Fred,Aurélie,Mathieu}
\integer{k=randint(1,2)}
\integer{p1=randint(30..48)}
\integer{p2=\k=2?100-\p1:\p1}
\integer{p=\k=2?50:\p1}
\text{aussi=\k=1?aussi}
\text{nom=randitem(\lstnom)}
\text{lstrep=\nom a raison,\nom a tort}
\text{tsol=Soit respectivement \(N_1\) et \(N_2\) le nombre d'élèves dans la première et la deuxième classe de BTS.
  <ul><li>
  Le nombre de filles en BTS est&nbsp;: <span class="nowrap">\(N_1 \times \frac{\p1}{100} + N_2 \times \frac{\p2}{100}\).</span>
  </li><li>
  La proportion de filles en BTS est donc&nbsp;:
  \(\frac{N_1 \times \frac{\p1}{100} + N_2 \times \frac{\p2}{100}}{N_1+N_2}\)
 }
\text{tsol=\k=1?\tsol c'est à dire \(\frac{(N_1+N_2) \times \frac{\p1}{100}}{N_1+N_2}\) 
soit encore <span class="nowrap">\(\frac{\p1}{100}\).</span></li></ul><p>
  Cette proportion ne dépend pas du nombre d'élèves de chaque classe et \nom a raison.:\tsol</li></ul><p>
  Cette proportion dépend du nombre d'élèves dans chaque classe et \nom a tort.}
\text{tsol=\tsol</p>}
\statement{
<p>
  Dans le lycée de \nom, il y a 2 classes de BTS.<br>
  Dans la première, il y a \p1 % de filles et dans la deuxième il y a \aussi \p2 % de filles.
</p><p>
\nom affirme qu'on peut en déduire qu'il y a \p % de filles en BTS.
</p><p>
  Qu'en pensez-vous&nbsp;?
</p>
<div class="wimscenter"> \embed{reply1}</div>
}
\answer{}{\k;\lstrep}{type=radio}
\solution{\tsol}
#endif

#if defined TARGET_somme4 || defined TARGET_somme5

# if defined TARGET_somme4
\title{TITLE 4}
\integer{p1=randint(2..5)}
\integer{p2=randint(1..9-\p1)*10}
\integer{p1=10*\p1}
\integer{sol1=(\p1+\p2)/2}
\integer{sol2=\p1+\p2}
\integer{sol3=\p1*\p2/100}
\text{lstrep=shuffle(\sol1 %,\sol2 %, \sol3 %),on ne peut pas savoir}
\integer{ind1=position(\sol1 %,\lstrep)}
\integer{rep=\p1=\p2?\ind1:4}
\text{tsol=Soit respectivement \(N_1\) et \(N_2\) le nombre de filles et de garçons dans le groupe.<br>
  Le nombre de sportifs est \(N_1 \times \frac{\p1}{100} + N_2 \times \frac{\p2}{100}).<br>
  La proportion de sportifs est donc&nbsp;: <span class="nowrap">\(\frac{N_1 \times \frac{\p1}{100} + N_2 \times \frac{\p2}{100}}{N_1+N_2}\)</span>}
\text{tsol=\p1=\p2?\tsol c'est à dire \(\frac{(N_1+N_2) \times \frac{\p1}{100}}{N_1+N_2}\) 
soit encore <span class="nowrap">\(\frac{\p1}{100}\).</span><br> Cette proportion ne dépend ni du nombre de filles ni du nombre de garçons dans le groupe. :\tsol<br> Cette proportion dépend du nombre de filles et du nombre de garçons dans le groupe, on ne peut donc pas savoir&nbsp;!}
\text{tcomp=Le pourcentage d'élèves de ce groupe pratiquant un sport est&nbsp;:}
#endif
# if defined TARGET_somme5
\title{TITLE 5}
\integer{p1=randint(2..5)}
\integer{p2=randint(1..9-\p1)*10}
\integer{p1=10*\p1}
\integer{nb=10*randitem(4,5,8,10,16,20,25)}
\integer{n1=min(randint(3..5)*10,\nb-10)}
\integer{n2=\nb-\n1}
\real{part=(\p1*\n1+\p2*\n2)/100}
\real{sol=(\p1*\n1+\p2*\n2)/\nb}
\text{tsol=Le nombre de sportifs est <span class="nowrap">\(\n1 \times \frac{\p1}{100} + \n2 \times \frac{\p2}{100}=\part\).</span><br>
  La proportion de sportifs est donc&nbsp;: \(\frac{\part}{\n1+\n2}=\frac{\part}{\nb}\) soit <span class="nowrap">\(\sol\) %.</span>}
\text{tcomp=Sachant qu'il y a \n1 filles et \n2 garçons,
  quelle est la proportion, en pourcentage, d'élèves de ce groupe pratiquant un sport&nbsp;?}
# endif
\statement{
<p>
  Dans un groupe d'élèves, \p1&nbsp;% des filles et \p2&nbsp;% des garçons font du sport.
</p>
# if defined TARGET_somme4
<p>\tcomp</p>
<div class="wimscenter"> \embed{reply1} </div>
# else
<p><label for="reply1">\tcomp</label></p>
<div class="wimscenter nowrap"> \embed{reply1} %</div>
# endif
}
# if defined TARGET_somme4
\answer{}{\rep;\lstrep}{type=radio}
# else
\answer{}{\sol}{type=numexp}{option=noreduction}
# endif
\solution{\tsol}
#endif
