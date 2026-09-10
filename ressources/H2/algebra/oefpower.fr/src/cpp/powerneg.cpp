target=powerneg
#include "lang_titles.inc"
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{10000}

\text{aa=randint(2,4,5,7,11,13,17,23)}
\text{cc= randint(3,2,5,7,\aa, 11, 13,19,29)}
\integer{a = \aa*random(1,-1)}
\text{cho=random(1,2)}
\integer{c=\cc*random(1,-1)}
\integer{b= item(\cho,\a,\c)}

\integer{n=random(2..11)*random(1,-1)}
\integer{m=random(2..11)*random(1,-1)}
\integer{p=random(2..11)*random(1,-1)}

\text{at=\a>0 ? \a:(\a)}
\text{bt=\b>0 ? \b:(\b)}
\text{ct=\c>0 ? \c:(\c)}
\text{ar=abs(\a)=abs(\c) ? (-1) : \at}
\real{ar=abs(\a)}
\text{cr= abs(\a)=abs(\c) ? \cc :\ct}
\real{cr=abs(\c)}
\integer{sol1=\cho=1 ? \n+(\m): \n}
\integer{sol2=\cho=2 ? \p+(\m): \p}
\integer{sol1= abs(\a)=abs(\c) ?\n+(\m)+(\p)}
\integer{signe=sign((\a)^(\n)*(\b)^(\m)*(\c)^(\p))}
integer{sol1= abs(\a)=abs(\c) and \signe=1? 0}
integer{sol1= abs(\a)=abs(\c) and \signe=-1? 1}
\text{shu=shuffle(1,2,3)}
\text{liste=\at^\n,\bt^\m,\ct^\p}
\text{atn=item(item(1,\shu),\liste)}
\text{btm=item(item(2,\shu),\liste)}
\text{ctp=item(item(3,\shu),\liste)}
\text{choix=\name_choix}
\text{pos=\signe=1 ? item(1,\choix): item(2,\choix)}
\text{as= item(item(1,\shu),\a,\b,\c)}
\text{bs= item(item(2,\shu),\a,\b,\c)}
\text{cs= item(item(3,\shu),\a,\b,\c)}
\text{listeexp=\as <0 ? item(item(1,\shu),\n,\m,\p):}
\text{listeexp= \bs <0 ? \listeexp,item(item(2,\shu),\n,\m,\p)}
\text{listeexp= \cs <0 ? \listeexp,item(item(3,\shu),\n,\m,\p)}
\text{listeneg=\as <0 ? item(item(1,\shu),\a,\b,\c):}
\text{listeneg= \bs <0 ? \listeneg,item(item(2,\shu),\a,\b,\c)}
\text{listeneg= \cs <0 ? \listeneg,item(item(3,\shu),\a,\b,\c)}

\text{listeneg=wims(listuniq \listeneg)}
\text{listeexp=wims(nonempty items \listeexp)}
\text{n0=wims(itemcnt \listeexp)}
\text{n1=wims(itemcnt \listeneg)}
\text{STEPS=\ar = \cr ? choice1
reply1:
choice1
reply1, reply2
}
\steps{\STEPS}

\statement{
\if{\step <=1}{ \name_statement[1;1] \(\atn) \times \( \btm) \times \(\ctp) \name_statement[1;2]
  \embed{choice 1}.}
\if{\step=2}{\name_statement[2;]:
<div class="wimscenter">
\if{\signe=1 and \ar !=\cr }{
  \(\atn) \times \( \btm) \times \(\ctp) = \ar<sup><sup>\embed{reply 1,3}</sup></sup>
 \cr<sup><sup>\embed{reply 2,3}</sup></sup>}
 \if{\signe=1 and \ar=\cr }{
  \(\atn) \times \( \btm)\(\times )\(\ctp) =
 \ar<sup><sup>\embed{reply 1,3}</sup></sup>
 }
 \if{\signe=-1 and \ar<>\cr}{
  \(\atn)\(\times)\( \btm) \times \(\ctp) = -\ar<sup><sup>\embed{reply 1,3}</sup></sup>
 \cr<sup><sup>\embed{reply 2,3}</sup></sup></div>}
 \if{\signe=-1 and \ar=\cr}{\(\atn)\(\times)\( \btm) \times \(\ctp) = -\ar<sup><sup>\
 \embed{reply 1,3}</sup></sup>}
</div>}
}
\choice{}{\pos}{\choix}
\answer{}{\sol1}{type=numeric}
\answer{}{\sol2}{type=numeric}

\feedback{\choice1 notsametext \pos and (\a<0 or \c<0)}{
  \name_feed[1;1] \if{\n0=1}{\name_feed[1;2]}{\name_feed[1;3]} \listeexp
  \if{\n1=1}{\name_feed[2;1] }{\name_feed[3;1] } \listeneg 
      \if{\n0=1}{\name_feed[2;2]}{\name_feed[3;2]} ?
\if{\n0=1}{\name_feed[4;1]}{\name_feed[4;2]} \name_feed[4;3]
}
\feedback{\choice1 notsametext \pos and \a>0 and \c>0}{\name_feed[5;]}
