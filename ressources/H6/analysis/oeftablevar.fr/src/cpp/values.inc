\text{infval=100000000}
\text{values=
1,2,3,4,5,6,7,8,9,10,
11,12,13,14,15,16,17,18,19,20,21,23,24,25,27,30,
random(4,5,6,7,8)0,random(3,4,5,6,7)5,random(3,4,5,6,7)2,
random(3,4,5,6,7)8,random(1,2,3)00,random(4,5,10)00
}
\text{values=frac isitemof \confparm1?\values,
 1/2,3/2,5/2,7/2,9/2,11/2,13/2,
 1/3,2/3,4/3,5/3,7/3,8/3,10/3
}
\text{values=root isitemof \confparm1?\values,
sqrt(3),sqrt(5),sqrt(6),sqrt(7),sqrt(8),sqrt(11),sqrt(12),
sqrt(18),sqrt(20),sqrt(30),sqrt(40),sqrt(60)
}
\text{values=pie isitemof \confparm1?\values,
pi,e,sqrt(2),pi+1,pi-1,e+1,e-1,
pi^2,e^2,pi^3,e^3,1/pi,1/e,2*pi,2*e,4*pi,4*e
}
\text{values=log isitemof \confparm1?\values,
ln(2),ln(3),ln(4),ln(5),ln(8),ln(10),ln(15),ln(20),ln(30),ln(50)
}
\text{values=exp isitemof \confparm1?\values,
2^e,3^e,2^pi,3^pi,pi^e,e^pi,pi^pi,e^e,
4^e,5^e,2^-e,2^-pi,pi^-e,e^-pi
}

\text{values=wims(makelist -x for x in \values),0,\values}

\text{values=wims(sort numeric items \values)}
\integer{vcnt=items(\values)}
