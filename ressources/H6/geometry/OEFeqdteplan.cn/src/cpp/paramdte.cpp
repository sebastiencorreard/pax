target=paramdte1 paramdte2

#if #TARGET(paramdte1)
\title{直线的参数方程 1}
#endif
#if #TARGET(paramdte2)
\title{直线的参数方程 2}
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

## equation param閠rique de D(A,u)
\text{eqx=\xa+\ux*t}
\text{eqy=\ya+\uy*t}
\text{eqz=\za+\uz*t}
\text{eqxx=simplify(\eqx)}
\text{eqyy=simplify(\eqy)}
\text{eqzz=simplify(\eqz)}

## equation du plan (A,u,v)
\integer{nx=\uy*\vz-\uz*\vy}
\integer{ny=\uz*\vx-\ux*\vz}
\integer{nz=\ux*\vy-\uy*\vx}
\integer{d1=\xa*\nx+\ya*\ny+\za*\nz}
\text{eqpl1=texmath(simplify(\nx*x+\ny*y+\nz*z-\d1)=0)}

## equation du plan (A,u,w)
\integer{mx=\uy*\wz-\uz*\wy}
\integer{my=\uz*\wx-\ux*\wz}
\integer{mz=\ux*\wy-\uy*\wx}
\integer{d2=\xa*\mx+\ya*\my+\za*\mz}
\text{eqpl2=texmath(simplify(\mx*x+\my*y+\mz*z-\d2)=0)}
\text{txtsol=}

#if #TARGET(paramdte1)
\statement{<p>
请给出以 \(t) 为变量的直线 \((D)) 的参数方程组,
直线 \((D)) 通过点 \(A(\xa,\ya,\za)) 而且方向向量是
\(\vec{u}\left(\begin{array}{c}\u[1]\\ \u[2]\\ \u[3]\end{array}\right)).
<center>
\(x) 的方程, 以 \(t) 为变量:x=\embed{reply1}<br>
\(y) 的方程, 以 \(t) 为变量:y=\embed{reply2}<br>
\(z) 的方程, 以 \(t) 为变量:z=\embed{reply3}<br>
</center>
}
#endif
#if #TARGET(paramdte2)
\statement{<p>
请给出以 \(t) 为变量的直线 \((D)) 的参数方程组,
直线 \((D)) 由以下方程组定义:
<center>
\( \begin{array}{c}\eqpl1 \\ \eqpl2 \end{array}).
</center>
<center>
<table><tr><td>\(x) 的方程, 以 \(t) 为变量:</td><td>x=\embed{reply1}</td></tr>
<tr><td>\(y) 的方程, 以 \(t) 为变量:</td><td>y=\embed{reply2}</td></tr>
<tr><td>\(z) 的方程, 以 \(t) 为变量:</td><td>z=\embed{reply3}</td></tr>
</table></center>
}
#endif


\answer{x 的方程}{\eqx2}{weight=0}
\answer{y 的方程}{\eqy2}{weight=0}
\answer{z 的方程}{\eqz2}{weight=0}
\real{vxa=evaluate(\reply1,t,t=0)}
\real{vya=evaluate(\reply2,t,t=0)}
\real{vza=evaluate(\reply3,t,t=0)}
\real{vxb=evaluate(\reply1,t,t=1)}
\real{vyb=evaluate(\reply2,t,t=1)}
\real{vzb=evaluate(\reply3,t,t=1)}
\real{colin1=(\vxb-\vxa)*\uy - (\vyb - \vya)*\ux}
\real{colin2=(\vyb-\vya)*\uz - (\vzb - \vza)*\uy}
\real{colin3=(\vzb-\vza)*\ux - (\vxb - \vxa)*\uz}
\real{colinb1=(\vxb-\xa)*\uy - (\vyb - \ya)*\ux}
\real{colinb2=(\vyb-\ya)*\uz - (\vzb - \za)*\uy}
\real{colinb3=(\vzb-\za)*\ux - (\vxb - \xa)*\uz}
\integer{condannexe=\vxa=\xa and \vya=\ya and \vza=\za?1:0}
\integer{macond1=\colin1=0 and \colin2=0 and \colin3=0?1:0}
\integer{macond2=\colinb1=0 and \colinb2=0 and \colinb3=0?1:0}
\integer{macondition=\macond1=1 and \macond2=1?1:0}
\text{col=\macondition=1?绿色:红色}
\text{txtsol=\macondition=1?是对的</font>:不对</font><br>
这里是一个可能的解:<center> \(x=\eqxx) <br> \(y=\eqyy) <br> \(z=\eqzz) </center>}
\text{txtsol=\condannexe=0 and \macondition=1? \txtsol 尽管这不是我所期待的, 实际上有许多可能的解,<br>
例如 <br>
<center> \(x=\eqxx) <br> \(y=\eqyy) <br> \(z=\eqzz) </center>}
#if #TARGET(paramdte1)
\text{txtsol=\macond1=0? \txtsol, 向量 u 不是由这些方程所定义的直线的方向向量}
\text{txtsol=\macond2=0? \txtsol, 点 A 不属于由这些方程所定义的直线}
#endif
\condition{\macondition=1}{weight=100000}{option=hide}
\feedback{1=1}{<font color=\col>你的解\txtsol}
