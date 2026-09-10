
\text{confparm1=\confparm1 issametext ? \confparm4}

\text{methods=}
\for{m in \confparm1}{
 \if{(a2 notin \m or \f_a2 notsametext a1) and
     (v2 notin \m or \f_v2 notsametext v1)}{
   \text{methods=wims(append item \m to \methods)}
 }
}

\text{method=wims(translate internal / to , in randitem(\methods))}
\text{method=\method issametext ? v1+r,a1}
\text{given=wims(translate a+b to a b in \method[1])}
\text{ask=\method[2]}
\int{tolerance=\confparm2>0 and \confparm2<=7?\confparm2:3}
\text{tolerance=item(\tolerance,10,5,2,1,0.5,0.2,0.1)}
