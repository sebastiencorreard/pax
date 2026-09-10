\integer{mucnt=items(\mulist)}
\text{data=1/2,3/2,5/2,1/3,2/3,4/3,5/3,
1/4,3/4,5/4,1/5,2/5,3/5,4/5,6/5,1/6,5/6}
\text{all=}
\for{f in \data}{
 \text{ff=wims(translate / to , in \f)}
 \text{nums=wims(values \ff[1]*x for x in \mulist)}
 \text{dens=wims(values \ff[2]*x for x in \mulist)}
 \text{this=}
 \for{F=1 to \mucnt}{
  \text{this=wims(append item \nums[\F]/\dens[\F] to \this)}
 }
 \matrix{all=\all
shuffle(\this)}
}
