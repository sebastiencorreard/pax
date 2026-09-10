\text{Pdata=wims(record 0 of position)}
\text{pdata=\Pdata}
\text{empty=}
\if{\confparm4 notsametext \empty and \selective notsametext no}{
  \text{pdata=row(\confparm4,\pdata)}
}
\text{totname=column(3,\pdata)}
\text{totsymbole=column(2,\pdata)}

\integer{pdatacnt=min(\confparm3,rows(\pdata))}
