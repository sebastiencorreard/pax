\text{data=wims(record 0 of table.\lang)}
\text{data=\data=? wims(record 0 of table)}
\integer{end=rows(\data)}
\integer{confparm1=\confparm1 notitemof 1,2,3,4?0}
\integer{confparm2=\confparm2 notitemof 1,2,3,4?0}
\text{empty=}
\integer{confparm3=\confparm3 issametext \empty or \confparm3<7 or
  \confparm3>\end?54}
\text{list=wims(values x for x=1 to \end)}
\text{confparm4=wims(listintersect \confparm4 and \list)}

\integer{given=\confparm1>0?\confparm1:randint(1..4)}
\integer{cp=\confparm2=\confparm1?0:\confparm2}
\text{remain=wims(listcomplement \given in 1,2,3,4)}
\text{remain=\candouble issametext yes and \given != 1?\given,\remain}
\integer{ask=\cp>0 and \cp isitemof \remain?\cp:randitem(\remain)}

