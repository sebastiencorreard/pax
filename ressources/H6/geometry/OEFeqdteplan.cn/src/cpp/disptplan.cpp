target=distptplan1 distptplan2 distplan3

#if #TARGET(distptplan1)
\title{点到平面的距离 1}
#endif
#if #TARGET(distptplan2)
\title{点到平面的距离 2}
#endif
#if #TARGET(distplan3)
\title{平行平面间的距离}
#endif
\author{R間ine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{1000}

\matrix{V=slib(matrix/invertible 3,3)}
\matrix{u=\V[1;]}
\matrix{v=\V[2;]}
\matrix{w=\V[3;]}

\integer{ux=\V[1;1]}
\integer{uy=\V[1;2]}
\integer{uz=\V[1;3]}
\integer{vx=\V[2;1]}
\integer{vy=\V[2;2]}
\integer{vz=\V[2;3]}
\integer{wx=\V[3;1]}
\integer{wy=\V[3;2]}
\integer{wz=\V[3;3]}
\integer{xa=randint(-9..9)}
\integer{ya=randint(-9..9)}
\integer{za=randint(-9..9)}

///// equation param閠rique de P(A,u,v)
\text{eqx=simplify(\xa+\ux*t+\vx*s)}
\text{eqy=simplify(\ya+\uy*t+\vy*s)}
\text{eqz=simplify(\za+\uz*t+\vz*s)}

///// equation du plan (A,u,v)
\integer{nx=\uy*(\vz)-(\uz)*(\vy)}
\integer{ny=(\uz)*(\vx)-(\ux)*(\vz)}
\integer{nz=(\ux)*(\vy)-(\uy)*(\vx)}
\integer{d1=(\xa)*(\nx)+(\ya)*(\ny)+(\za)*(\nz)}
\text{eqpl1=texmath(simplify(\nx*x+\ny*y+\nz*z-\d1)=0)}

\integer{d2=\d1+randint(5..20)*randint(1,-1)}
\text{eqpl2=texmath(simplify(\nx*x+\ny*y+\nz*z-\d2)=0)}


\text{txtsol=}
\text{eqxx=texmath(\eqx)}
\text{eqyy=texmath(\eqy)}
\text{eqzz=texmath(\eqz)}

///// coordonn閑s du point B
\integer{xb=randint(-9..9)}
\integer{yb=randint(-9..9)}
\integer{zb=randint(-9..9)}
#if #TARGET(distplan3)
\if{\nx=0}
   {
   \if{\ny=0}
     {
     \integer{xb=0}
     \integer{yb=0}
     \rational{zb=\d2 / (\nz)}
     }
     {
     \integer{xb=0}
     \integer{zb=0}
     \rational{yb=\d2 / (\ny)}
     }
   }
   {
    \integer{yb=0}
    \integer{zb=0}
    \rational{xb=\d2 / (\nx)}
   }
#endif

///// distance de P au plan
\real{dist=pari(abs(\nx*(\xb) + (\ny)*(\yb) + (\nz)*(\zb) -(\d1)) /sqrt((\nx)^2+(\ny)^2+(\nz)^2))}

#if #TARGET(distptplan1)
\statement{<p>
考虑由变量 \(t) 和 \(s) 的参数方程组定义的平面 \((P)):

<center>
x=\(\eqxx\)<br>
y=\(\eqyy\)<br>
z=\(\eqzz\)<br>
</center>
计算点 \(B(\xb,\yb,\zb)) 到平面 \((P)) 的距离
<br>
<center>距离=\embed{reply1,7}</center>

}
\answer{距离}{\dist}{type=numeric}
\hint{首先应该建立 \((P)) 的一般方程}
#endif
#if #TARGET(distptplan2)
\statement{<p>
考虑由以下一般方程定义的平面 \((P)):
<center>
\( \eqpl1).
</center>
<p>
计算点 \(B(\xb,\yb,\zb)) 到平面 \((P)) 的距离
</p>
<center>距离=\embed{reply1,7}</center>

}
\answer{距离}{\dist}{type=numeric}
#endif
#if #TARGET(distplan3)
\statement{<p>
考虑由以下一般方程定义的平面 \((P)):</p>
<center>
\( \eqpl1).
</center>
以及由以下一般方程定义的平行平面 \((Q)):
<center>
\( \eqpl2).
</center>
计算平面 \((P)) 到平面 \((Q)) 的距离
<br>
<center>距离=\embed{reply1,7}</center>

}
\answer{距离}{\dist}{type=numeric}
\hint{设有 \((P)) 的点 \(A). \(A) 到 \((Q)) 的距离与 \(A) 的选取无关.}

#endif
