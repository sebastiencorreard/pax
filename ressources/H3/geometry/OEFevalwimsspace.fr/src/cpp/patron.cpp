target=patron1 patron3 patron4 patron5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{donnees=}
#if defined TARGET_patron1
\text{ch=randrow(1,2,2
1,1,2
1,1,1)}
 \text{ch=shuffle(\ch)}
 \integer{m=item(\ch[1],11,8)}
 \text{files=item(\ch[1],src/patroncube.don,src/fpatroncube.don)}
 \text{donnees=wims(append line \ch[1],randint(1..\m),\files to \donnees)}
 \integer{m=item(\ch[2],9,5)}
 \text{files=item(\ch[2],src/patronpave.don,src/fpatronpave.don)}
 \text{donnees=wims(append line \ch[2],randint(1..\m),\files to \donnees)}
 \text{files=item(\ch[3],src/pcarre.don,src/fpcarre.don)}
 \text{donnees=wims(append line \ch[3],randint(1..9),\files to \donnees)}
#endif
#if defined TARGET_patron3
  \integer{ch=randint(1..2)}
 \if{\ch=1}{
  \text{donnees=1,randint(1..11),src/patroncube.don
2,randint(1..8),src/fpatroncube.don}
 }{
  \text{m=shuffle(1,2,3,4,5,6,7,8,9,10,11)}
  \text{donnees=1,\m[1],src/patroncube.don
1,\m[2],src/patroncube.don}
 }
 \text{donnees=\donnees
2,randint(1..9),src/patronpave.don
2,randint(1..5),src/fpatronpave.don
2,randint(1..2),src/ptriangle.don
2,randint(1..2),src/fptriangle.don}
#endif
#if defined TARGET_patron4
  \integer{ch=randint(1..2)}
 \text{chp=randrow(9,src/pcarre.don,src/fpcarre.don
2,src/ptriangle.don,src/fptriangle.don)}
 \if{\ch=1}{
  \text{donnees=1,randint(1..\chp[1]),\chp[2]
2,randint(1..\chp[1]),\chp[3]}
 }{
  \text{m=wims(values v for v=1 to \chp[1])}
  \text{m=shuffle(\m)}
  \text{donnees=1,\m[1],\chp[2]
1,\m[2],\chp[2]}
 }
 \text{donnees=\donnees
2,randint(1..9),src/patronpave.don
2,randint(1..5),src/fpatronpave.don
2,randint(1..11),src/patroncube.don
2,randint(1..8),src/fpatroncube.don}
#endif
#if defined TARGET_patron5
  \integer{ch=randint(1..2)}
 \if{\ch=1}{
  \text{donnees=1,randint(1..9),src/patronpave.don
2,randint(1..5),src/fpatronpave.don}
 }{
  \text{m=shuffle(1,2,3,4,5,6,7,8,9)}
  \text{donnees=1,\m[1],src/patronpave.don
1,\m[2],src/patronpave.don}
 }
 \text{m=shuffle(1,2,3,4,5,6,7,8)}
 \text{donnees=\donnees
2,\m[1],src/fpatroncube.don
2,\m[2],src/fpatroncube.don
2,randint(1..2),src/ptriangle.don
2,randint(1..2),src/fptriangle.don}
#endif
\text{enonce=\name_enonce}
\text{ltimage=}
\text{good=}
\integer{nbl=rows(\donnees)}
\for{k=1 to \nbl}{
 \text{don=row(\k,\donnees)}
 \text{dessin=wims(record \don[2] of \don[3])}
 \text{image=draw(200,200
\dessin)}
 \text{image=<img src='\image' alt=''>}
 \text{ltimage=wims(append item \image to \ltimage)}
 \text{good=\don[1]=1?wims(append item \k to \good)}
}

\statement{
\enonce?
 <ul class="inline">
 \for{j=1 to \nbl}{
  <li>\embed{r1,\j}</li>
 }
 </ul>
}

\answer{}{\good;\ltimage}{type=checkbox}{options=shuffle split}
