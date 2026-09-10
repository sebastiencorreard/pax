target=opercplx0 opercplx1 opercplx2 opercplx3 opercplx4
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
#define TITRE Opérations et complexes
\computeanswer{no}

\integer{x1=randint(-5..5)}
\integer{y1=\x1=0?randint(1..5)*randint(1,-1):randint(-5..5)}
\integer{x2=randint(-5..5)}
\integer{y2=\x2=0?randint(1..5)*randint(1,-1):randint(-5..5)}
\complex{z1=\x1+(\y1)*i}
\complex{z2=\x2+(\y2)*i}

#if defined TARGET_opercplx0
#define NUM 0
#endif
#if defined TARGET_opercplx1
#define NUM 1
#endif
#if defined TARGET_opercplx2
#define NUM 2
#endif
#if defined TARGET_opercplx3
#define NUM 3
#endif
#if defined TARGET_opercplx4
#define NUM 4
#endif
\title{TITRE NUM}
#if defined TARGET_opercplx0
\complex{z=(\x1+(\y1)*i)+(\x2+(\y2)*i)}
\text{quest=u+v}
\text{quest=wims(replace internal u by z_1 in \quest)}
\text{quest=wims(replace internal v by z_2 in \quest)}

\statement{<p>Soient les nombres complexes \(z_1=\z1) et \(z_2=\z2).</p>
   Calculer \(\quest):
<div class="wimscenter">
<label for="reply1">\(\quest)=</label>\embed{reply1}</div>
}
\answer{\(\quest)}{\z}{type=complex}
#endif

#if defined TARGET_opercplx1
\integer{a=randint(1..5)*randint(1,-1)}
\integer{b=randint(1..5)*randint(1,-1)}
\complex{z=\a*(\x1+(\y1)*i)+\b*(\x2+(\y2)*i)}

\text{quest=texmath(\a*u+\b*v)}
\text{quest=wims(replace internal u by z_1 in \quest)}
\text{quest=wims(replace internal v by z_2 in \quest)}

\statement{<p>Soient les nombres complexes \(z_1=\z1) et \(z_2=\z2).</p>
   Calculer \(\quest):
<div class="wimscenter">
<label for="reply1">\(\quest)=</label>\embed{reply1}</div>
}
\answer{\(\quest)}{\z}{type=complex}
#endif

#if defined TARGET_opercplx2
\complex{z=(\x1+(\y1)*i)*(\x2+(\y2)*i)}
\complex{zc=(\x1+(\y1)*i)^2}

\statement{<p>Soient les nombres complexes \(z_1=\z1) et \(z_2=\z2).</p>
   Calculer:
<ol>
<li><label for="reply1">\(z_1 \times z_2)=</label>\embed{reply1}</li>
<li><label for="reply2">\(z_1^2)=</label>\embed{reply2}</li>
</ol>
}
\answer{\(z_1 \times z_2)}{\z}{type=complex}
\answer{\(z_1^2)}{\zc}{type=complex}
#endif

#if defined TARGET_opercplx3
\complex{z=(\x1+\y1*i)/(\x2+\y2*i)}
\complex{zi=1/(\x1+\y1*i)}

\statement{<p>Soient les nombres complexes \(z_1=\z1) et \(z_2=\z2).</p>
   Calculer sous forme algébrique:
<ol>
<li><label for="reply1">\(\frac{1}{z_1})=</label>\embed{reply1}</li>
<li><label for="reply2">\(\frac{z_1}{z_2})</label>=\embed{reply2}</li>
</ol>
}
\answer{\(\frac{1}{z_1})}{\zi}{type=complex}
\answer{\(\frac{z_1}{z_2})}{\z}{type=complex}
#endif
#if defined TARGET_opercplx4
\integer{r1=randint(1..9)}
\integer{r2=randint(1..9)}
\integer{n1=randint(1..5)*randint(1,-1)}
\integer{n2=randint(1..5)*randint(1,-1)}
\integer{d1=randint(2..5)}
\integer{d2=randint(2..5)}
\integer{d2=\d1}
\rational{a1=simplify(\n1/\d1)}
\rational{a1=\a1>1?simplify(\a1-2)}
\rational{a1=\a1<=-1?simplify(\a1+2)}

\rational{a2=simplify(\n2/\d2)}
\rational{a2=\a2>1?simplify(\a2-2)}
\rational{a2=\a2<=-1?simplify(\a2+2)}

\rational{a1p=abs(\a1)}
\rational{a2p=abs(\a2)}

\text{a1c=\a1>0?\imath texmath(\a1) \pi:-\imath texmath(\a1p) \pi}
\text{a2c=\a2>0?\imath texmath(\a2) \pi:-\imath texmath(\a2p) \pi}

\text{z1=\r1=1?e^{\displaystyle\a1c}:\r1 e^{\displaystyle\a1c}}
\text{z2=\r2=1?e^{\displaystyle\a2c}:\r2 e^{\displaystyle\a2c}}

\integer{mzp=\r1*\r2}
\rational{azp=simplify(\a1+(\a2))}
\integer{mzc=\r1^2}
\rational{azc=simplify(2*\a1)}
\rational{mzi=1/\r1}
\rational{azi=simplify(-(\a1))}
\rational{mzf=\r1/\r2}
\rational{azf=simplify(\a1-(\a2))}

\rational{azp=\azp>1?simplify(\azp-2)}
\rational{azp=\azp<=-1?simplify(\azp+2)}
\rational{azc=\azc>1?simplify(\azc-2)}
\rational{azc=\azc<=-1?simplify(\azc+2)}
\rational{azi=\azi>1?simplify(\azi-2)}
\rational{azi=\azi<=-1?simplify(\azi+2)}
\rational{azf=\azf>1?simplify(\azf-2)}
\rational{azf=\azf<=-1?simplify(\azf+2)}

\statement{
<p>Soient les nombres complexes \(z_1=\z1) et \(z_2=\z2).</p>
  Calculer sous forme exponentielle:
<ol>
<li><label for="reply1">\(z_1 \times z_2)=</label>\embed{reply1} e <sup>\(\imath)
  \embed{reply2,4}\(\pi)</sup></li>
<li><label for="reply3">\(z_1^2)=</label>\embed{reply3} e <sup>\(\imath) \embed{reply4,4}\(\pi)</sup></li>
<li><label for="reply5">\(\frac{1}{z_1})=</label>\embed{reply5} e <sup>\(\imath) \embed{reply6,4}\(\pi)</sup></li>
<li><label for="reply7">\(\frac{z_1}{z_2})=</label>\embed{reply7} e <sup>\(\imath) \embed{reply8,4}\(\pi)</sup></li>
</ol>
<div class="wims_instruction">
L'argument doit être dans l'intervalle
\(\rbrack -\pi,\pi\rbrack\)
</div>
}
\answer{module \(z_1 \times z_2)}{\mzp}{type=numeric}
\answer{argument \(z_1 \times z_2)}{\azp}{type=numexp}
\answer{module \(z_1^2)}{\mzc}{type=numeric}
\answer{argument \(z_1^2)}{\azc}{type=numexp}
\answer{module \(\frac{1}{z_1})}{\mzi}{type=numexp}
\answer{argument \(\frac{1}{z_1})}{\azi}{type=numexp}
\answer{module \(\frac{z_1}{z_2})}{\mzf}{type=numexp}
\answer{argument \(\frac{z_1}{z_2})}{\azf}{type=numexp}
#endif
