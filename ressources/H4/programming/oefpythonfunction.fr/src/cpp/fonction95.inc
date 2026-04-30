\title{FCT 15}

\text{par=()}
\text{par1=wims(char 1 of \par)}
\text{par2=wims(char 2 of \par)}
\text{crochet=[]}
\text{cri=wims(char 1 of \crochet)}
\text{cre=wims(char 2 of \crochet)}

\text{fct_alg=??}
\integer{b=randomitem(-1,1)*randint(1..5)}
\text{bb=\b}
\integer{aq=randint(1..2)}
\text{ppmm=(\aq==1)?+:-}
\integer{xi=randint(-3..-1)}
integer{xi=-3}
\integer{xm=\xi+randint(4..6)}
integer{xm=2}
\integer{xsol1=\xi+randint(1..2)}
\integer{xsol2=\xm-1}
\text{fct_pari=\ppmm(t-\xsol1)*(t-\xsol2)+\b}
\text{fct_pari=maxima(simplify(\fct_pari))}

\text{fct_ecr=wims(replace t by x in \fct_pari)}
\text{fct_ecr=maxima(simplify(\fct_ecr))}

\text{pn=\xsol1}
\text{pnn=\xsol1}

\real{pas=randomitem(0.01,0.02,0.05)}
\text{xi_alg=??}
\text{xm_alg=??}
\text{pas_alg=??}
\text{instruction_code=instruction=[x**2,y_list[n]==k,abs(y_list[n]-(k))&lt;10**(-9)]}

\integer{rb=randint(1..2)}
\text{colorr=(\rb==1)?red:blue}
\text{colorb=(\rb==1)?blue:red}

\text{parialgo=if(abs(yl[nn]-(\b))<10^-(9),nzero=nn;);
if(abs(yl[nn]-(\b))<10^-(9),colorl=concat(colorl,[\colorr]);,colorl=concat(colorl,[\colorb]););}
\text{paricolor=\colorl[\kj]}

\text{initpythn=n=0}
\text{initpythcol=color_list=[]}
\text{scriptpyth=if  ?? :
      color_list.append('\colorr')
  else:
      color_list.append('\colorb')
  n=n+1}
\text{scriptpythh=print(color_list[\:10])}

\text{javalc=color_liste=Sk.ffi.remapToJs(Sk.globals["color_list"]);}
