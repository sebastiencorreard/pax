target=comparerB1 comparerB2 comparerB3 comparerB4 comparerB5
#define TITRE Comparer deux fractions
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
\conputeanswer{yes}

\text{v=shuffle(2,3,4,5,6,7,8,9)}
#if defined TARGET_comparerB1 
 \title{TITRE 1}
 \text{fr1=\v[1]/\v[2]}
 \text{fr2=\v[3]/\v[2]}
#endif

#if defined TARGET_comparerB2 
 \title{TITRE 2}
 \text{fr1=\v[1]/\v[2]}
 \text{fr2=\v[1]/\v[3]}
#endif

#if defined TARGET_comparerB3 
 \title{TITRE 3}
 \text{fr1=-\v[1]/\v[2]}
 \text{fr2=-\v[3]/\v[2]}
#endif

#if defined TARGET_comparerB4 
 \title{TITRE 4}
 \integer{m1=min(\v[1],\v[2])}
 \integer{M1=max(\v[1],\v[2])}
 \integer{m2=min(\v[3],\v[4])}
 \integer{M2=max(\v[3],\v[4])}
 \text{fr1=\m1/\M1}
 \text{fr2=\M2/\m2}
#endif

#if defined TARGET_comparerB5 
 \title{TITRE 5}
 \integer{a=\v[1]+1}
 \integer{b=\v[2]+1}
 \text{fr1=\v[1]/\a}
 \text{fr2=\v[2]/\b}
#endif

\text{list=\fr1<\fr2?\fr1,\fr2:\fr2,\fr1}
\text{list=\(texmath(\list[1])),\(texmath(\list[2]))}
\integer{ch=randint(1..2)}
\text{type=item(\ch,la plus grande,la plus petite)}
\text{rep=\ch=1?\list[2]:\list[1]}

\statement{
Quelle est \type des deux fractions ?}

\choice{}{\rep}{\list}
