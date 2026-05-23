#define TOT (ROWS*COLS)

\integer{rows=ROWS}
\integer{cols=COLS}
\integer{tot=TOT}

\integer{confparm1=\confparm1=?1}
\integer{confparm2=\confparm2=?1}
\text{o1=item(\confparm2,1,1,2,2)}
\text{o2=item(\confparm2,1,2,1,2)}
\text{op1=item(\o1,+,*)}
\text{op2=item(\o2,+,*)}
\text{Name1=item(\o1,\operlist)}
\text{Name2=item(\o2,\operlist)}
\text{names=item(\confparm2,\optionlist)}
\text{vars=shuffle(a,b,c,d,r,s,t,x,y,z)}
\text{rt=sqrt(random(2,3,5))}
\text{list=wims(record \confparm1 of src/data_\datalang)}
\text{nature=row(1,\list)}
\text{parms=row(2,\list)}
\text{obj=\parms[1]}
\text{sizex=\parms[2]}
\text{sizey=\parms[3]}
\text{sizex=\sizex =? 60}
\text{sizey=\sizey=? 35}
\text{size=\sizex \sizey}
\text{list=wims(rows2lines row(3..-1,\list))}
\text{modbase=\parms[4..-1]}
\if{\modbase notsametext}{
  \text{modbase=randitem(\modbase)}
  \text{list=wims(values x%\modbase for x=0 to max(\modbase-1,TOT + 10))}
}
\integer{n=items(\list)}
\if{\n<=3 and \modbase issametext}{
  \text{a=\list[1]}
  \text{b=\list[2]}
  \text{c=\list[3]}
  \text{randtype=computed}
  \if{\c<0}{
     \text{sh1=wims(values \c*x,-(\c)*x for x=\a to \b)}
  }{
   \text{sh1=wims(values \c*x for x=\a to \b)}
  }
  \text{sh=item(1..\tot,shuffle(\sh1))}
}{
 \text{randtype=listed}
 \text{sh=item(1..\tot,shuffle(\list))}
}
\text{sh=wims(mathsubst f=\vars[1] in \sh)}
\text{sh=wims(mathsubst g=\vars[2] in \sh)}
\text{sh=wims(mathsubst rt=\rt in \sh)}
\text{empty=}

\text{goodlist=(\sh[1]),(\sh[2]),(\sh[3]),(\sh[4]),
(\sh[5]),(\sh[6]),(\sh[7]),(\sh[8]),
(\sh[9]),(\sh[10]),(\sh[11]),(\sh[12]),
(\sh[13]),(\sh[14]),(\sh[15]),(\sh[16])}

\text{rowvals=}
\for{x=1 to \rows}{
 \text{r=wims(replace , by \op1 in \goodlist[(\x-1)*\cols+1..\x*\cols])}
 \text{r=maxima(expand(\r))}
 \if{\modbase notsametext}{\integer{r=\r%\modbase}}
 \text{rowvals=wims(append item \r to \rowvals)}
}

\text{colvals=}
\for{y=1 to \cols}{
 \text{c=wims(replace , by \op2 in \goodlist[wims(values \cols*(x-1)+\y for x=1 to \rows)])}
 \text{c=maxima(expand(\c))}
 \if{\modbase notsametext}{\integer{c=\c%\modbase}}
 \text{colvals=wims(append item \c to \colvals)}
}

#ifndef PARTIAL
 \text{replies=item(1..\tot,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16)}
 \steps{\replies}
#endif

#ifdef TYPED
 \integer{size=\sizex/10-2}
#endif

\statement{<em>\nature</em>.
#ifdef TYPED
<p>\tstatement0 \obj,
#else
<p>\tstatement1 \obj \tstatement2,
#endif
\tstatement3
\if{\modbase issametext}{
 \names \tstatement31:
}{
 \names \tstatement31 \tstatement4 \modbase:
}
</p>
<table class="wimsborder wimscenter">
<tr><th></th>
\for{cc=1 to COLS}{<th class="small">\tcolumn \cc</th>}
<th>\Name1</th></tr>
\for{rr=1 to ROWS}{
<tr><th class="small">\trow \rr</th>
 \for{cc=1 to COLS}{
#ifdef PARTIAL
 <td>
 \if{\mlist[(\rr-1)*\cols+\cc]=1}
 {\(\sh[(\rr-1)*\cols+\cc])}{\embed{\replies[(\rr-1)*\cols+\cc],\size}}
 </td>
#else
  <td>\embed{\replies[(\rr-1)*\cols+\cc],\size}</td>
#endif
}
<td>\(\rowvals[\rr])</td></tr>
}
<tr><th>\Name2</th>
\for{cc=1 to COLS}{<td>\(\colvals[\cc])</td>}
</tr></table>
}
