target=successeur1 successeur2 predecesseur1 predecesseur2

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}

\text{size=20x25x}

\integer{basep=row(1,\confparm4)}
\text{S=row(3,\confparm4)}
\text{S=item(1 to \basep,\S)}

#if defined TARGET_predecesseur1
 \integer{sg=-1}
 \integer{spe=1}
#endif

#if defined TARGET_predecesseur2
 \integer{sg=-1}
 \integer{spe=0}
#endif

#if defined TARGET_successeur1
 \integer{sg=1}
 \integer{spe=1}
#endif

#if defined TARGET_successeur2
 \integer{sg=1}
 \integer{spe=0}
#endif

#include "lang.inc"

\text{type=item(\sg+2,\txttype)}
\text{types=item(\sg+2,\txttypes)}
\text{Type=item(\sg+2,\txtttype)}
\text{p=shuffle(2,3,4,5)}
\text{nombre=}
\text{srep=}
\text{lsize=}
\for{r=1 to \confparm3}{
 \integer{n=randint(1..\basep-1)}
 \integer{N=\spe=1?\basep^\p[\r]*\n:randint(\basep^\p[\r]..\basep^(\p[\r]+1))}
 \integer{N2=\N-1}
 \text{n=slib(basep \N,\S)}
 \text{rep=slib(basep \N2,\S)}
 \if{\sg<0}{
  \text{rep=slib(char2item \rep)}
  \text{n=\(\overline{\n}^{\basep})}
  \integer{tmp=items(\rep)}
  \integer{tmp=\tmp+randint(0..4)}
  \text{rep=slib(addzero \rep;\tmp)}
  \text{srep=wims(append line \rep to \srep)}
  \text{nombre=wims(append item \n to \nombre)}
 }{
  \text{n=slib(char2item \n)}
  \text{rep=\(\overline{\rep}^{\basep})}
  \integer{tmp=items(\n)}
  \integer{tmp=\tmp+randint(0..4)}
  \text{n=slib(addzero \n;\tmp)}
  \text{srep=wims(append line \n to \srep)}
  \text{nombre=wims(append item \rep to \nombre)}
 }
 \text{lsize=wims(append item \size\tmp to \lsize)}
}

\text{ltrep=item(1 to \confparm3,r1,r2,r3,r4,r5)}
\steps{\ltrep}

\statement{
\txtstatement1
<p>
\if{\confparm3=1}{
 \txtst2a \type \txtst2b
}{
 \txtst3a \types \txtst3b
}
</p>
<table class="wimscenter wimsborder">
 <tr><th>\txtnum</th><th>\Type</th></tr>
 \for{k=1 to \confparm3}{<tr><td>\nombre[\k] </td><td> \embed{r\k,\lsize[\k]}</td></tr>}
</table>
}

\answer{\nombre 1 }{\srep[1;];\S}{type=clickfill}
\answer{\nombre 2 }{\srep[2;];\S}{type=clickfill}
\answer{\nombre 3 }{\srep[3;];\S}{type=clickfill}
\answer{\nombre 4 }{\srep[4;];\S}{type=clickfill}
\answer{\nombre 5}{\srep[5;];\S}{type=clickfill}
