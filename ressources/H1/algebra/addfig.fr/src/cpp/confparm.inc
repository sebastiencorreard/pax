
\integer{confparm1=\confparm1 issametext ?1}
\integer{confparm2=\confparm2 issametext ?0}
\text{vars=shuffle(a,b,c,d,r,s,t,x,y,z)}
\text{rt=sqrt(random(2,3,5))}
\text{list=wims(record \confparm1 of src/data)}
\text{nature=\list[1;]}
\text{parms=\list[2;]}
\text{smin=\list[3;1]}
\text{smax=\list[3;2]}
\integer{smean=(\smin+\smax)/2}
\text{obj=\parms[1]}
\text{sizex=\parms[2]}
\text{sizey=\parms[3]}
\text{sizex=\sizex =? 60}
\text{sizey=\sizey=? 35}
\text{size=\sizex \sizey}
\text{list=wims(rows2lines row(4..-1,\list))}
\integer{n=items(\list)}
\if{\n<=3}{
 \text{a=\list[1]}
 \text{b=\list[2]}
 \text{c=\list[3]}
 \text{randtype=computed}
 \if{\c<0}{
  \text{sh1=wims(values \c*x,-(\c)*x for x=\a to \b)}
 }{
  \text{sh1=wims(values \c*x for x=\a to \b)}
 }
 \text{list=\sh1}
}{
 \text{randtype=listed}
}
\text{list=wims(mathsubst f=\vars[1] in \list)}
\text{list=wims(mathsubst g=\vars[2] in \list)}
\text{list=wims(mathsubst rt=\rt in \list)}
\text{sh=item(1..\tot,shuffle(\list))}

