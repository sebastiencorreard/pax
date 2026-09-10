target=oefegalfract1 oefegalfract2 oefegalfract3 oefegalfract4  oefegalfract5
#define TITRE Egalités de fractions
\langage{fr}
\author{Jean-Luc,Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}

#if defined TARGET_oefegalfract1
\title{TITRE 1}

\text{l=shuffle(9)}
\text{n=}
\text{d=}
\for{i=1 to 4}{
   \text{a=\l[\i]}
   \integer{b=10}
   \text{n=wims(append item \a to \n)}
   \text{d=wims(append item \b to \d)}
}
\text{nr=}
\text{dr=}
\for{i=1 to 4}{
   \integer{a=\n[\i]*10}
   \integer{b=\d[\i]*10}
   \text{nr=wims(append item \a to \nr)}
   \text{dr=wims(append item \b to \dr)}
}
\text{rep1=\(\frac{\n[1]}{\d[1]}),\(\frac{\n[2]}{\d[2]}),\(\frac{\n[3]}{\d[3]}),\(\frac{\n[4]}{\d[4]})}
\text{rep2=\(\frac{\nr[1]}{\dr[1]}),\(\frac{\nr[2]}{\dr[2]}),
\(\frac{\nr[3]}{\dr[3]}),\(\frac{\nr[4]}{\dr[4]})}
#endif

#if defined TARGET_oefegalfract2
\title{TITRE 2}
\text{l=shuffle(2,3,4,5,6,7,8,9,10,11,12)}
\matrix{ln=wims(record 1 of src/fractions)}
\text{n=}
\text{d=}
\for{i=1 to 4}{
   \text{a=row(\l[\i]-1,\ln)}
   \integer{b=randomitem(\a)}
   \text{n=wims(append item \b to \n)}
   \text{d=wims(append item \l[\i] to \d)}
}
\text{nr=}
\text{dr=}
\for{i=1 to 4}{
   \integer{a=\n[\i]*2}
   \integer{b=\d[\i]*2}
   \text{nr=wims(append item \a to \nr)}
   \text{dr=wims(append item \b to \dr)}
}
\text{rep1=\(\frac{\n[1]}{\d[1]}),\(\frac{\n[2]}{\d[2]}),\(\frac{\n[3]}{\d[3]}),\(\frac{\n[4]}{\d[4]})}
\text{rep2=\(\frac{\nr[1]}{\dr[1]}),\(\frac{\nr[2]}{\dr[2]}),
\(\frac{\nr[3]}{\dr[3]}),\(\frac{\nr[4]}{\dr[4]})}
#endif

#if defined TARGET_oefegalfract3
\title{TITRE 3}
\text{l=shuffle(2,3,4,5,6,7,8,9,10,11,12)}
\matrix{ln=wims(record 1 of src/fractions)}
\text{n=}
\text{d=}
\for{i=1 to 4}{
   \text{a=row(\l[\i]-1,\ln)}
   \integer{b=randomitem(\a)}
   \text{n=wims(append item \b to \n)}
   \text{d=wims(append item \l[\i] to \d)}
}
\text{nr=}
\text{dr=}
\for{i=1 to 4}{
   \integer{a=\n[\i]*3}
   \integer{b=\d[\i]*3}
   \text{nr=wims(append item \a to \nr)}
   \text{dr=wims(append item \b to \dr)}
}
\text{rep1=\(\frac{\n[1]}{\d[1]}),\(\frac{\n[2]}{\d[2]}),\(\frac{\n[3]}{\d[3]}),\(\frac{\n[4]}{\d[4]})}
\text{rep2=\(\frac{\nr[1]}{\dr[1]}),\(\frac{\nr[2]}{\dr[2]}),
\(\frac{\nr[3]}{\dr[3]}),\(\frac{\nr[4]}{\dr[4]})}
#endif

#if defined TARGET_oefegalfract4
\title{TITRE 4}
\text{l=shuffle(2,3,4,5,6,7,8,9,10,11,12)}
\matrix{ln=wims(record 1 of src/fractions)}
\integer{m=randint(4..9)}
\text{n=}
\text{d=}
\for{i=1 to 4}{
   \text{a=row(\l[\i]-1,\ln)}
   \integer{b=randomitem(\a)}
   \text{n=wims(append item \b to \n)}
   \text{d=wims(append item \l[\i] to \d)}
}
\text{nr=}
\text{dr=}
\for{i=1 to 4}{
   \integer{a=\n[\i]*\m}
   \integer{b=\d[\i]*\m}
   \text{nr=wims(append item \a to \nr)}
   \text{dr=wims(append item \b to \dr)}
}
\text{rep1=\(\frac{\n[1]}{\d[1]}),\(\frac{\n[2]}{\d[2]}),\(\frac{\n[3]}{\d[3]}),\(\frac{\n[4]}{\d[4]})}
\text{rep2=\(\frac{\nr[1]}{\dr[1]}),\(\frac{\nr[2]}{\dr[2]}),
\(\frac{\nr[3]}{\dr[3]}),\(\frac{\nr[4]}{\dr[4]})}
#endif

#if defined TARGET_oefegalfract5
\title{TITRE 5}
\text{l=shuffle(2,3,4,5,6,7,8,9,10,11,12)}
\matrix{ln=wims(record 1 of src/fractions)}
\text{n=}
\text{d=}
\for{i=1 to 4}{
   \text{a=row(\l[\i]-1,\ln)}
   \integer{b=randomitem(\a)}
   \text{n=wims(append item \b to \n)}
   \text{d=wims(append item \l[\i] to \d)}
}
\text{nr=}
\text{dr=}
\for{i=1 to 4}{
   \integer{m=randint(2..9)}
   \integer{a=\n[\i]*\m}
   \integer{b=\d[\i]*\m}
   \text{nr=wims(append item \a to \nr)}
   \text{dr=wims(append item \b to \dr)}
}
\text{rep1=\(\frac{\n[1]}{\d[1]}),\(\frac{\n[2]}{\d[2]}),\(\frac{\n[3]}{\d[3]}),\(\frac{\n[4]}{\d[4]})}
\text{rep2=\(\frac{\nr[1]}{\dr[1]}),\(\frac{\nr[2]}{\dr[2]}),
\(\frac{\nr[3]}{\dr[3]}),\(\frac{\nr[4]}{\dr[4]})}
#endif

\statement
{
Mettre en relation les fractions représentant le même nombre :
<div class="wimscenter">
\embed{r1,60x50}
</div>
}

\answer{}{\rep1;\rep2}{type=correspond}
