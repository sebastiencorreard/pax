\text{Data=wims(record 0 of table)}
\text{data=\Data}
\text{empty=}
\if{\confparm4 notsametext \empty and \selective notsametext no}{
  \text{data=row(\confparm4,\data)}
}
\text{totname=column(3,\data)}
\text{totsymbole=column(2,\data)}

\integer{datacnt=min(\confparm3,rows(\data))}
