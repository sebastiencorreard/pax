\integer{facedeb=randint(1..6)}
\integer{facefin=randint(1..6)}
\text{lstpt=}
\for{ ii = \n1 to \n2}{
  \if {\facedeb isitemof \faces[\ii;]}{
    \text{lstpt= wims(append item \listpoint[\ii] to \lstpt)}
  }
}
\text{lstpt = shuffle (\lstpt)}
\text{pt1 = \lstpt[1]}
\text{pt2 = \lstpt[2]}
\text{lstpt=}
\for{ ii = \n1 to \n2}{
  \if {\facefin isitemof \faces[\ii;]}{
    \text{lstpt= wims(append item \listpoint[\ii] to \lstpt)}
  }
}
\text{lstpt = shuffle(\lstpt)}
\text{pt3 = \lstpt[1]}
\text{pt4 = \lstpt[2]}
\integer{indpt1=position(\pt1,\listpoint)}
\integer{indpt2=position(\pt2,\listpoint)}
\integer{indpt3=position(\pt3,\listpoint)}
\integer{indpt4=position(\pt4,\listpoint)}
\text{dessin=
 segment \pt[\indpt1;],\pt[\indpt2;],red
 segment \pt[\indpt3;],\pt[\indpt4;],blue
}
