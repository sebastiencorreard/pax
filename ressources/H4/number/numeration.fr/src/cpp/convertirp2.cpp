target=convertirp2

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}


\text{size=20x25x}
\integer{basep=row(1,\confparm4)}
\text{S=row(3,\confparm4)}
\text{S=item(1 to \basep,\S)}

\text{p=shuffle(2,3,4,5)}
\text{nombre=}
\text{srep=}
\text{lsize=}
\for{r=1 to \confparm3}{
 \integer{N=randint(0..\basep-1)}
 \text{N=\N=0?}
 \for{s=1 to \p[\r]-1}{
  \integer{n=randint(0..\basep-1)}
  \text{t=\s=1?\n*\basep:\n*\basep^\s}
  \text{N=\n!=0?\N+\t}
 }
 \integer{n=randint(1..\basep-1)}
 \text{N=\N+\n*\basep^\p[\r]}
 \integer{t=\N}
 \text{a=texmath(\N)}
 \text{n=slib(basep \t,\S)}
 \text{nombre=wims(append item \a to \nombre)}
 \text{rep=slib(char2item \n)}
 \integer{tmp=items(\rep)}
 \text{lsize=wims(append item \size\tmp to \lsize)} 
 \text{srep=wims(append line \rep to \srep)}
}

\text{ltrep=item(1 to \confparm3,r1,r2,r3,r4,r5)}
\steps{\ltrep}




#include "lang.inc"

\statement{
\txtstatement1<p>
\if{\confparm3=1}{
 \txtstatement2 
}{
 \txtstatement3
}
</p>
<table class="wimscenter wimsborder">
 <tr><th>\txtbaseten</th><th>\txtbase \basep</th></tr>
 \for{k=1 to \confparm3}{<tr><td>\(\nombre[\k]) </td><td> \embed{r\k,\lsize[\k]}</td></tr>}
</table>
}

\answer{\nombre 1 }{\srep[1;];\S}{type=clickfill}
\answer{\nombre 2 }{\srep[2;];\S}{type=clickfill}
\answer{\nombre 3 }{\srep[3;];\S}{type=clickfill}
\answer{\nombre 4 }{\srep[4;];\S}{type=clickfill}
\answer{\nombre 5 }{\srep[5;];\S}{type=clickfill}
