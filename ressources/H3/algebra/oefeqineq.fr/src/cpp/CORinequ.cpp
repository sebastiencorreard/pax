target= CORinequ3 CORinequ4 CORinequ5
#include "author.inc"
#if defined TARGET_CORinequ3
# define NUM 4
#endif
#if defined TARGET_CORinequ4
# define NUM 5
#endif
#if defined TARGET_CORinequ5
# define NUM 6
#endif

#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}
\text{size=45x150x100}

\integer{confparm1=\confparm1=?1}
\integer{confparm2=\confparm2=?1}
\integer{nombre=NUM}


#include "valeurs.inc"

\integer{confparm1=\confparm1 /2=0?\confparm1-1}
\text{champ=wims(record \confparm1 of src/generateur)}
\text{A=row(2,\champ)}
\text{B=row(3,\champ)}
\text{c=item(3,\A)}
\if{\B=}{
  \text{aa=item(1,\A)}
  \text{bb=item(2,\A)}
  \text{valeurs=wims(values v for v=\aa to \bb)}
}{
  \text{valeurs=\B}
}
\text{valeurs=wims(listuniq \valeurs)}
\text{valeurs=shuffle(\valeurs)}
\text{a=item(1,\valeurs)}
\text{b=item(2,\valeurs)}
\if{\c<0}{
 \text{b=randitem(-,)\b}
}

\text{x=randitem(x,y,a,b)}
\text{symb=<,>}
\text{inf=item(1,\symb)}
\text{sup=item(2,\symb)}


\if{\confparm1>4}{
 \integer{ai=100*\a}
 \integer{bi=100*\b}
 \text{dd=simplify((\bi)/(\ai))}
 \integer{dd2=\bi-\ai}
 \text{dd2=slib(decimal \dd2,2)}
 \text{dd3=\dd2>0?-\dd2:wims(char 2 to -1 of \dd2)}
}{
 \text{dd=simplify((\b)/(\a))}
 \text{dd2=simplify(\b-\a)}
 \text{dd3=simplify(-\dd2)}
}
\text{donnees=(\x \inf \dd,-\a*\x \sup -\b,\a*\x-\b \inf 0,\a*\x \inf \b),(\x \inf -\dd,-\a*\x \sup \b,\a*\x+\b \inf 0,\a*\x \inf -\b),(\x \sup \dd,-\a*\x \inf -\b,\a*\x-\b \sup 0,\a*\x \sup \b),(\x \sup -\dd,-\a*\x \inf \b,\a*\x+\b \sup 0,\a*\x \sup -\b),(\x \sup \dd2,\x+\a \sup \b),
(\x \sup \dd3,\x-\a \sup -\b)}

\text{donnees=shuffle(\donnees)}
\text{donnees=wims(item 1 to \nombre of \donnees)}

\text{ra=}
\text{nb=}
\for{i=1 to \nombre}{
  \text{TMP=item(\i,\donnees)}
  \text{TMP=wims(declosing \TMP)}
  \text{tmp=item(1,\TMP)}
  \text{tmp=texmath(\tmp)}
  \text{ra=wims(append item \(\tmp) to \ra)}
  \text{tmp=wims(item 2 to -1 of \TMP)}
  \text{tmp=randitem(\tmp)}
  \text{tmp=texmath(\tmp)}
  \text{nb=wims(append item \(\tmp) to \nb)}
}

\integer{ch=random(1..2)}
\if{\ch=2}{
  \text{nb=wims(replace internal < by \leq in \nb)}
  \text{ra=wims(replace internal < by \leq in \ra)}
  \text{nb=wims(replace internal > by \geq in \nb)}
  \text{ra=wims(replace internal > by \geq in \ra)}
}

\statement{\name_question
  <div class="wimscenter">
  \embed{reply 1,\size}
  </div>
}

\reply{\name_answer}{\nb;\ra}{type=correspond}
