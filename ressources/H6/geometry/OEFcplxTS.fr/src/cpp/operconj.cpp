target=operconj1 operconj2 operconj3 operconj4
\author{Régine, Mangeard}
\email{regine@mangeard.fr}

\computeanswer{yes}
#define TITRE Opérations et conjugués
#if defined TARGET_operconj1
# define NUM 1
#endif
#if defined TARGET_operconj2
# define NUM 2
#endif
#if defined TARGET_operconj3
# define NUM 3
#endif
#if defined TARGET_operconj4
# define NUM 4
#endif
\title{TITRE NUM}
\integer{x1=randint(-5..5)}
\integer{y1=\x1=0?randint(1..5)*randint(1,-1):randint(-5..5)}
\integer{x2=randint(-5..5)}
\integer{y2=\x2=0?randint(1..5)*randint(1,-1):randint(-5..5)}
\complex{z1=\x1+\y1*i}
\complex{z2=\x2+\y2*i}

#if defined TARGET_operconj1
\integer{a=randint(1..5)*randint(1,-1)}
\integer{b=randint(1..5)*randint(1,-1)}
\integer{i=randint(1..4)}
\if{\i=1}{
  \complex{z=\a*(\x1-\y1*i)+\b*(\x2+\y2*i)}
  \text{tz1=\overline{z_1}}
  \text{tz2=z_2}
  \text{quest=texmath(\a*u+\b*v)}
  \text{quest=wims(replace internal v by \tz2 in \quest)}
  \text{quest=wims(replace internal u by \tz1 in \quest)}
}
\if{\i=2}{
  \complex{z=\a*(\x1+\y1*i)+\b*(\x2-\y2*i)}
  \text{tz2=\overline{z_2}}
  \text{tz1=z_1}
  \text{quest=texmath(\a*u+\b*v)}
  \text{quest=wims(replace internal u by \tz1 in \quest)}
  \text{quest=wims(replace internal v by \tz2 in \quest)}
}
\if{\i=3}{
  \complex{z=\a*(\x1-\y1*i)+\b*(\x2-\y2*i)}
  \text{tz1=z_1}
  \text{tz2=z_2}
  \text{quest=texmath(\a*u+\b*v)}
  \text{quest=wims(replace internal u by \tz1 in \quest)}
  \text{quest=wims(replace internal v by \tz2 in \quest)}
  \text{quest=\overline{(\quest)}}
}
\if{\i=4}{
  \complex{z=\a*(\x1-\y1*i)+\b*(\x2+\y2*i)}
  \text{tz2=\overline{z_2}}
  \text{tz1=z_1}
  \text{quest=texmath(\a*u+\b*v)}
  \text{quest=wims(replace internal v by \tz2 in \quest)}
  \text{quest=wims(replace internal u by \tz1 in \quest)}
  \text{quest=\overline{\quest}}
}


\statement{<p>Soient les nombres complexes \(z_1=\z1) et \(z_2=\z2).</p>
Calculer \(\quest):
<div class="wimscenter"><label for="reply1">\(\quest)=</label>\embed{reply1}</div>
}
\answer{\(\quest)}{\z}{type=complex}
#endif
#if defined TARGET_operconj2
\integer{i=randint(1..4)}
\if{\i=1}{
  \complex{z=(\x1-\y1*i)*(\x2+\y2*i)}
  \text{tz1=\overline{z_1}}
  \text{tz2=z_2}
  \text{quest=texmath((u)*(v))}
  \text{quest=wims(replace internal v by \tz2 in \quest)}
  \text{quest=wims(replace internal u by \tz1 in \quest)}
}
\if{\i=2}{
  \complex{z=(\x1+\y1*i)*(\x2-\y2*i)}
  \text{tz2=\overline{z_2}}
  \text{tz1=z_1}
  \text{quest=texmath((u)*(v))}
  \text{quest=wims(replace internal u by \tz1 in \quest)}
  \text{quest=wims(replace internal v by \tz2 in \quest)}
}
\if{\i=3}{
  \complex{z=(\x1-\y1*i)*(\x2-\y2*i)}
  \text{tz1=z_1}
  \text{tz2=z_2}
  \text{quest=texmath((u)*(v))}
  \text{quest=wims(replace internal u by \tz1 in \quest)}
  \text{quest=wims(replace internal v by \tz2 in \quest)}
  \text{quest=\overline{(\quest)}}
}
\if{\i=4}{
  \complex{z=(\x1-\y1*i)*(\x2+\y2*i)}
  \text{tz2=\overline{z_2}}
  \text{tz1=z_1}
  \text{quest=texmath((u)*(v))}
  \text{quest=wims(replace internal v by \tz2 in \quest)}
  \text{quest=wims(replace internal u by \tz1 in \quest)}
  \text{quest=\overline{(\quest)}}
}

\if{\i<3}{
  \complex{zc=(\x1-\y1*i)^2}
  \text{quest2=(\overline{z_1})^2}
}{
  \complex{zc=conj((\x1-\y1*i)^2)}
  \text{quest2=(\overline{\overline{z_1})^2}}
}

\statement{<p>Soient les nombres complexes \(z_1=\z1) et \(z_2=\z2).</p>
Calculer:
<ol>
<li><label for="reply1">\(\quest)=</label>\embed{reply1}</li>
<li><label for="reply2">\(\quest2)=</label>\embed{reply2}</li>
</ol>
}
\answer{\(\quest)}{\z}{type=complex}
\answer{\(\quest2)}{\zc}{type=complex}
#endif
#if defined TARGET_operconj3
\integer{i=randint(1..4)}
\if{\i=1}{
  \complex{z=(\x1-\y1*i)/(\x2+\y2*i)}
  \text{tz1=\overline{z_1}}
  \text{tz2=z_2}
  \text{quest=texmath((u)/(vv))}
  \text{quest=wims(replace internal vv by \tz2 in \quest)}
  \text{quest=wims(replace internal u by \tz1 in \quest)}
}
\if{\i=2}{
  \complex{z=(\x1+\y1*i)/(\x2-\y2*i)}
  \text{tz2=\overline{z_2}}
  \text{tz1=z_1}
  \text{quest=texmath((u)/(vv))}
  \text{quest=wims(replace internal u by \tz1 in \quest)}
  \text{quest=wims(replace internal vv by \tz2 in \quest)}
}
\if{\i=3}{
  \complex{z=(\x1-\y1*i)/(\x2-\y2*i)}
  \text{tz1=z_1}
  \text{tz2=z_2}
  \text{quest=texmath((u)/(vv))}
  \text{quest=wims(replace internal u by \tz1 in \quest)}
  \text{quest=wims(replace internal vv by \tz2 in \quest)}
  \text{quest=\overline{(\quest)}}
}
\if{\i=4}{
  \complex{z=(\x1-\y1*i)/(\x2+\y2*i)}
  \text{tz2=\overline{z_2}}
  \text{tz1=z_1}
  \text{quest=texmath((u)/(vv))}
  \text{quest=wims(replace internal vv by \tz2 in \quest)}
  \text{quest=wims(replace internal u by \tz1 in \quest)}
  \text{quest=\overline{(\quest)}}
}
\if{\i<3}{
  \complex{zi=1/(\x1-\y1*i)}
  \text{quest2=\frac{1}{\overline{z_1}}}
}{
  \complex{zi=1/(\x1+\y1*i)}
  \text{quest2=\overline{(\frac{1}{\overline{z_1}})}}
}

\statement{<p>
Soient les nombres complexes \(z_1=\z1) et \(z_2=\z2).</p>
Calculer sous forme algébrique:
<ol>
<li><label for="reply1">\(\quest2)=</label>\embed{reply1}</li>
<li><label for="reply2">\(\quest)=</label>\embed{reply2}</li>
</ol>
}
\answer{\(\quest2)}{\zi}{type=complex}
\answer{\(\quest)}{\z}{type=complex}
#endif

#if defined TARGET_operconj4
\integer{r1=randint(1..9)}
\integer{r2=randint(1..9)}
\integer{n1=randint(1,2,3,5)*randint(1,-1)}
\integer{n2=randint(1,2,3,5)*randint(1,-1)}
\integer{d1=randint(2..5)}
\integer{d2=\d1}
\rational{a1=\n1=\d1?simplify((\n1+1)/\d1):simplify(\n1/\d1)}
\rational{a1=\a1>1?simplify(\a1-2)}
\rational{a1=\a1<=-1?simplify(\a1+2)}

\rational{a2=simplify(\n2/\d2)}
\rational{a2=\a2>1?simplify(\a2-2)}
\rational{a2=\a2<=-1?simplify(\a2+2)}

\rational{a1p=abs(\a1)}
\rational{a2p=abs(\a2)}

\text{ta1=\a1>0?-\imath texmath(\a1p) \pi:\imath texmath(\a1p) \pi}
\text{ta2=\a2>0?\imath texmath(\a2) \pi:-\imath texmath(\a2p) \pi}

\text{z1=\r1=1?e^{\displaystyle\ta1}:\r1 e^{\displaystyle\ta1}}
\text{z2=\r2=1?e^{\displaystyle\ta2}:\r2 e^{\displaystyle\ta2}}
\text{z1=\a1=0?\r1}
\text{z2=\a2=0?\r2}


\integer{mzp=\r1*\r2}
\rational{azp=simplify(\a1+\a2)}
\integer{mzc=\r1^2}
\rational{azc=simplify(2*\a1)}
\rational{mzi=1/\r1}
\rational{azi=simplify(-\a1)}
\rational{mzf=\r1/\r2}
\rational{azf=simplify(\a1-\a2)}

\rational{azp=\azp>1?simplify(\azp-2)}
\rational{azp=\azp<=-1?simplify(\azp+2)}
\rational{azc=\azc>1?simplify(\azc-2)}
\rational{azc=\azc<=-1?simplify(\azc+2)}
\rational{azi=\azi>1?simplify(\azi-2)}
\rational{azi=\azi<=-1?simplify(\azi+2)}
\rational{azf=\azf>1?simplify(\azf-2)}
\rational{azf=\azf>1?simplify(\azf-2)}
\rational{azf=\azf<=-1?simplify(\azf+2)}
\rational{azf=\azf<=-1?simplify(\azf+2)}

\statement{<p>
Soient les nombres complexes \(z_1=\z1) et \(z_2=\z2).</p>
Calculer sous forme exponenentielle:
<ol>
<li><label for="reply1">\(\overline{z_1} \times z_2)=</label>\embed{reply1} e <sup>\(\imath) \embed{reply2,4}\(\pi)</sup></li>
<li><label for="reply3">\(\overline{z_1}^2)=</label>\embed{reply3} e <sup>\(\imath) \embed{reply4,4}\(\pi)</sup></li>
<li><label for="reply5">\(\frac{1}{\overline{z_1}})=</label>\embed{reply5} e <sup>\(\imath) \embed{reply6,4}\(\pi)</sup></li>
<li><label for="reply7">\(\frac{\overline{z_1}}{z_2})=</label>\embed{reply7} e <sup>\(\imath) \embed{reply8,4}\(\pi)</sup></li>
</ol>
}
\answer{module \(\overline{z_1} \times z_2)}{\mzp}{type=numeric}
\answer{argument \(\overline{z_1} \times z_2)}{\azp}{type=numexp}
\answer{module \(\overline{z_1}^2)}{\mzc}{type=numeric}
\answer{argument \(\overline{z_1}^2)}{\azc}{type=numexp}
\answer{module \(\frac{1}{\overline{z_1}})}{\mzi}{type=numexp}
\answer{argument \(\frac{1}{\overline{z_1}})}{\azi}{type=numexp}
\answer{module \(\frac{\overline{z_1}}{z_2})}{\mzf}{type=numexp}
\answer{argument \(\frac{\overline{z_1}}{z_2})}{\azf}{type=numexp}
#endif
