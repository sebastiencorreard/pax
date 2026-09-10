target=calctersuite5AS calctersuite5SS calctersuite6AS calctersuite6SS
#include "author.inc"
#if defined TARGET_calctersuite5AS || defined TARGET_calctersuite5SS
# define NUM 5
#endif
#if defined TARGET_calctersuite6AS || defined TARGET_calctersuite6SS
# define NUM 6
#endif
#include "lang_titles.inc"
#if defined TARGET_calctersuite5SS || defined TARGET_calctersuite5AS
# if defined TARGET_calctersuite5AS
\precision{1000}
# endif
# if defined TARGET_calctersuite5SS
\precision{100}
# endif
\integer{a=randint(4..8)}
\real{r=1+\a/100}
\integer{u1=randint(1..5)}
\integer{ns=random(10..15)}
\real{u2=\u1*\r}
\real{u3=\u2*\r}
\real{uder=\u1*\r^(\ns-1)}
\real{distance_totale= \u1 *(1-\r^\ns)/(1-\r)}
#endif
#if defined TARGET_calctersuite6AS
\precision{1000}
\integer{r=random(100,200,300,400,500)}
\real{mr=1+\r/10000}
\integer{u1=randint(1..5)}
\integer{ns=random(10..15)}
\real{u2=\u1+\r/1000}
\real{u3=\u2+\r/1000}
\real{uder=\u1+\r*(\ns-1)/1000}
\real{distance_totale= \ns *(\u1+\uder)/2}
#endif
#if defined TARGET_calctersuite6SS
\integer{r=random(100,200,300,400,500)}
\integer{u1=randint(1..5)}
\integer{ns=random(10..15)}
\real{u2=\u1+\r/1000}
\real{u3=\u2+\r/1000}
\real{uder=\u1+\r*(\ns-1)/1000}
\real{mr=1+\r/10000}
#endif
#include "lang_calcter.inc"

:%%%%%%%%%%%%%% Rien à modifier avant l'énoncé %%%%%%%%%%%%%%%%

\text{data=wims(singlespace \data)}
\text{data=wims(embraced randitem \data)}
\text{data=slib(text/cutchoice2 \data)}
#if defined TARGET_calctersuite6AS || defined TARGET_calctersuite5AS
\integer{qs=6}
#endif
#if defined TARGET_calctersuite5SS || defined TARGET_calctersuite6SS
\integer{qs=5}
#endif
\text{good=}
\text{field=}
\for{i=1 to \qs}{
 \text{f=\data[2*\i;]}
 \text{g=\f[1]}
 \text{f=wims(sort items \f)}
 \text{g=positionof(\g,\f)}
 \text{good=\good\g,}
 \text{field=\field\f;}
}

\text{pre=wims(embraced randitem \pre)}
\text{post=wims(embraced randitem \post)}
\text{qlist=wims(makelist reply x for x=1 to \qs)}
\steps{\qlist}
#if defined TARGET_calctersuite5SS || defined TARGET_calctersuite5AS
\text{vrep=\a %}
#endif
#if defined TARGET_calctersuite6AS || defined TARGET_calctersuite6SS
\text{vrep=\r m}
#endif
\text{bg1=boy,girl}
\text{bg=randitem(1,2)}
\text{bg1=\bg1[\bg]}
\text{prenom=slib(lang/fname ,\bg1)}
#include "lang.inc"
:%%%%%%%%%%%%% Maintenant l'énoncé en code html. %%%%%%%%%%%%%%%%%%%%

::Vous n'avez pas besoin de modifier ceci en général.
\statement {<p>\name_statement \( u_1 ) = \u1.</p>
\data[1;]
\for{k=1 to 2}{
\embed{r \k,\len} \data[2*\k+1;]}
<p>
\name_statement1
</p>
<div class="wims_instruction">\name_instruction</div>
<ul><li>
 <label for="reply3"> \(u_2\) =</label> \embed{reply 3,3} km
</li><li>
  <label for="reply4">\(u_3\) =</label> \embed{reply 4,3} km
</li><li>
  <label for="reply5">\(u_\ns\)</label> = \embed{reply 5,3} km
</li></ul>
#if defined TARGET_calctersuite5AS || defined TARGET_calctersuite6AS
\name_statement2
<label for="reply6">\name_distancetotale =</label> \embed{reply 6,3} km.
#endif
}

:%%%%%%%%%%%%% Rien à modifier ci-après. %%%%%%%%%%%%%%%%%

\answer{Champ 1}{\good[1];\field[1;]}{type=menu}
\answer{Champ 2}{\good[2];\field[2;]}{type=menu}

\answer{3}{\u2}{numeric}
\answer{4}{\u3}{numeric}
\answer{5}{\uder}{numeric}
#if defined TARGET_calctersuite5AS || defined TARGET_calctersuite6AS
\answer{6}{\distance_totale}{numeric}
#endif
