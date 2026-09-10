target=paramplan1 paramplan2 paramplan3

#if #TARGET(paramplan1)
\title{平面的参数方程 1}
#endif
#if #TARGET(paramplan2)
\title{平面的参数方程 2}
#endif
#if #TARGET(paramplan3)
\title{平面的参数方程 3}
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

## equation param閠rique de P(A,u,v)
\text{eqx=simplify(\xa+\ux*t+\vx*s)}
\text{eqy=simplify(\ya+\uy*t+\vy*s)}
\text{eqz=simplify(\za+\uz*t+\vz*s)}

## equation du plan (A,u,v)
\integer{nx=\uy*\vz-\uz*\vy}
\integer{ny=\uz*\vx-\ux*\vz}
\integer{nz=\ux*\vy-\uy*\vx}
\integer{d1=\xa*\nx+\ya*\ny+\za*\nz}
\text{eqpl1=texmath(\nx*x+\ny*y+\nz*z-\d1=0)}

\text{txtsol=}
\text{eqxx=texmath(\eqx)}
\text{eqyy=texmath(\eqy)}
\text{eqzz=texmath(\eqz)}

#if #TARGET(paramplan1)

\integer{k=random(1,1,2)}
\integer{it=random(0,1,2,3,1/2,3/2)*randint(1,-1)}
\integer{is=random(0,1,2,3,1/2,3/2)*randint(1,-1)}
\real{xb=evaluate(\eqx,t=\it,s=\is)}
\real{yb=evaluate(\eqy,t=\it,s=\is)}
\real{zb=evaluate(\eqz,t=\it,s=\is)}
\if{\k=2}
  {
## on casse le point
\integer{k2=randint(1..3)}
 \if{\k2=1}
  {
  \integer{it2=\it+random(1,-1,2,-2)}
  \real{xb=evaluate(\eqx,t=\it2,s=\is)}
  \integer{k=\ux=0?1:2}
  }
 \if{\k2=2}
  {
  \integer{it2=\it+random(1,-1,2,-2)}
  \real{yb=evaluate(\eqy,t=\it2,s=\is)}
  \integer{k=\uy=0?1:2}
  }
 \if{\k2=3}
  {
  \integer{is2=\is+random(1,-1,2,-2)}
  \real{zb=evaluate(\eqz,t=\it,s=\is2)}
  \integer{k=\vz=0?1:2}
  }
 }
\integer{rep=\k}

\statement{<p>
考虑由变量 \(t) 和 \(s) 的参数方程组定义的平面 \((P)):

<center>
<center>
x=\(\eqxx)<br>
y=\(\eqyy)<br>
z=\(\eqzz)<br>
</center>
</center>
点 \(B(\xb,\yb,\zb)) 是否属于平面 \((P))?
<br>
\embed{reply1}

}
\answer{}{\rep;是,否}{type=radio}
\feedback{\rep=1}{只要取 \(t=\it) 与 \(s=\is)}
#endif
#if #TARGET(paramplan2)
\statement{<p>
考虑由变量 \(t) 和 \(s) 的参数方程组定义的平面 \((P)):
<center>
x=\(\eqxx)<br>
y=\(\eqyy)<br>
z=\(\eqzz)<br>
</center>
给出平面 \((P)) 的一般方程.
<p>
\embed{reply1}
}
\answer{一般方程}{\eqpl1}{type=equation}
#endif
#if #TARGET(paramplan3)
\statement{<p>
写出平面 \((P)) 关于变量 \(t) 与 \(s) 的参数方程组,
平面 \((P)) 由以下一般方程定义:
<center>
\( \eqpl1).
<p>
<table><tr><td>\(x) 的方程, 以 \(t) 与 \(s) 为变量:</td><td>x=\embed{reply1}</td></tr>
<tr><td>\(y) 的方程, 以 \(t) 与 \(s) 为变量:</td><td>y=\embed{reply2}</td></tr>
<tr><td>\(z) 的方程, 以 \(t) 与 \(s) 为变量:</td><td>z=\embed{reply3}</td></tr>
</table>
</center>
}


\answer{x 的方程}{\repx}{weight=0}
\answer{y 的方程}{\repy}{weight=0}
\answer{z 的方程}{\repz}{weight=0}
\real{hx=evaluate(\reply1,t,s,t=0,s=0)}
\real{hy=evaluate(\reply2,t,s,t=0,s=0)}
\real{hz=evaluate(\reply3,t,s,t=0,s=0)}
\real{vxa=evaluate(\reply1,t,s,t=1,s=0)-\hx}
\real{vya=evaluate(\reply2,t,s,t=1,s=0)-\hy}
\real{vza=evaluate(\reply3,t,s,t=1,s=0)-\hz}
\real{vxb=evaluate(\reply1,t,s,t=0,s=1)-\hx}
\real{vyb=evaluate(\reply2,t,s,t=0,s=1)-\hy}
\real{vzb=evaluate(\reply3,t,s,t=0,s=1)-\hz}
## il faut va et n orthogonaux
\integer{cond1=\vxa*\nx+\vya*\ny+\vza*\nz}
## il faut vb et n orthogonaux
\integer{cond2=\vxb*\nx+\vyb*\ny+\vzb*\nz}
## il faut va et vb ind閜endants
\real{colin1=\vxb*\vya - \vyb*\vxa}
\real{colin2=\vyb*\vza - \vzb*\vya}
\real{colin3=\vzb*\vxa - \vxb*\vza}
\integer{cond3=\colin1=0 and \colin2=0 and \colin3=0?1:0}
## il faut que le point h v閞ifie l'閝uation du plan 
\integer{cond4=\hx*\nx+\hy*\ny+\hz*\nz-\d1}
\integer{macondition=\cond1=0 and \cond2=0 and \cond3=0 and \cond4=0?1:0}
\text{col=\macondition=1?绿色:红色}
\text{txtsol=\macondition=1?是对的</font>:不对</font><br>}
\text{txtsol=\cond1=0?\txtsol: \txtsol,  \(t) 前面的系数不定义此平面的一个向量,<br>}
\text{txtsol=\cond2=0?\txtsol: \txtsol, \(s) 前面的系数不定义此平面的一个向量,<br>}
\text{txtsol=\cond3=0?\txtsol: \txtsol, \(t) 与 \(s) 前面的系数不定义此平面的两个线性无关向量,<br>}
\text{txtsol=\cond4=0?\txtsol: \txtsol, \(t=0) 与 \(s=0) 得到的点不属于 \((P)):\cond4=\hx*\nx+\hy*\ny+\hz*\nz-\d1}

\condition{你的解}{\macondition=1}{weight=100000}{option=hide}
\feedback{1=1}{ <font color=\col>你的解\txtsol}
#endif
