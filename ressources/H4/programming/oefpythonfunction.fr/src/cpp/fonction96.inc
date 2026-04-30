\title{FCT 16}

\text{par=()}
\text{par1=wims(char 1 of \par)}
\text{par2=wims(char 2 of \par)}
\text{crochet=[]}
\text{cri=wims(char 1 of \crochet)}
\text{cre=wims(char 2 of \crochet)}

\text{fct_alg=??}
\integer{b=randomitem(-1,1)*randint(1..5)}
\integer{aq=randint(1..2)}
\text{ppmm=(\aq==1)?+:-}
\integer{xi=randint(-3..-1)}
\integer{xm=\xi+randint(4..6)}
\integer{xsol1=\xi+randint(1..2)}
\integer{xsol2=\xm-1}
\text{fct_pari=\ppmm(t-(\xsol1))*(t-(\xsol2))+\b}
\text{fct_pari=maxima(simplify(\fct_pari))}
\text{fct_ecr=wims(replace t by x in \fct_pari)}
\text{fct_ecr=maxima(simplify(\fct_ecr))}

\integer{nez=randint(1..4)}
\text{inn=&lt;,>,&lt;=,>=}
\text{inn=\inn[\nez]}
\text{eta=reply1,reply2,reply3}
\if{((\aq==1 and (\nez==4 or \nez==2)) or (\aq==2 and (\nez==3 or \nez==1)))}{
\text{etape=\eta,reply4,reply5}
\text{pn=\xi}
\text{pnn=\xsol1}
}{
\text{etape=\eta}
\text{pn=\xsol1}
\text{pnn=\xsol2}
}
\text{ca=((\aq==1 and \nez==1) or (\aq==2 and \nez==2))?\left \cre: \left \cri}
\text{caa=((\aq==1 and \nez==4) or (\aq==2 and \nez==3))? \left \cre \cup \right \cri}
\text{caa=((\aq==1 and \nez==2) or (\aq==2 and \nez==1))? \left \cri \cup \right \cre}
\text{caa=((\aq==2 and \nez==2) or (\aq==1 and \nez==1))? \left \cri}
\text{caa=((\aq==2 and \nez=4) or (\aq==1 and \nez==3))?\left \cre}

\matrix{STEP=\etape}
\steps{\STEP}


\real{pas=randomitem(0.01,0.02,0.05)}
\text{xi_alg=??}
\text{xm_alg=??}
\text{pas_alg=??}
\text{instruction_code=instruction=[x**2,&lt;k,>k,&lt;=k,>=k]}

\integer{rb=randint(1..2)}
\text{colorr=(\rb==1)?red:blue}
\text{colorb=(\rb==1)?blue:red}
\text{colorin=(\rb==1)?>=:<}

\text{ineq=(\nez==1)?-(yl[nn])>-(\b)}
\text{ineq=(\nez==2)?yl[nn]>\b}
\text{ineq=(\nez==3)?-(yl[nn])>= -(\b)}
|| abs(yl[nn]-(\b))<10^-(9)
\text{ineq=(\nez==4)?yl[nn]>=\b}
|| abs(yl[nn]-(\b))<10^-(9)



\text{parialgo=if(\ineq,colorl=concat(colorl,[\colorr]);,colorl=concat(colorl,[\colorb]););}
\text{paricolor=\colorl[\kj]}

\text{initpythn=n=0}
\text{initpythcol=color_list=[]}
\text{scriptpyth=if y_list[n] ?? :
      color_list.append('\colorr')
  else:
      color_list.append('\colorb')
  n=n+1}
\text{scriptpythh=print(color_list[\:10])}

\text{javalc=color_liste=Sk.ffi.remapToJs(Sk.globals["color_list"]);}
