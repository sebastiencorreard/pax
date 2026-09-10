\text{dessin1=
arrow 0,0,3,0,10,black
arrow 0,0,0,3, 10,black
arrow 0,0,-1.6,-1.6, 10,black
text blue, -1.8,-1.8, medium, x
text blue,0.5,2.9, medium, z
text blue,2.8, 0.5,medium, y
}
\if{\H=2}{
  \text{dessin= xrange -3,3
yrange -3,3
\dessin1
linewidth 2
segment 0,0,2.2,2.2,green
segment 0,0, 2.2,-0.5,green
dsegment 2.2,-0.5,2.2,2.2,black
dsegment 0,2.5,2.2,2.2,black
trange 5*pi/4,2*pi-pi/16
plot , cos(t),sin(t)
arrow cos(-pi/16-0.2),sin(-pi/16-0.2),cos(-pi/16),sin(-pi/16),10, red
trange pi/4, pi/2
plot , cos(t),sin(t)
arc 0, 0, 2, 2, 45, 90, red
arc 0, 0, 2, 2, 225,348.75, red
text black, 1.1, 0.8, large, r
arrow cos(pi/4+0.2),sin(pi/4+0.2),cos(pi/4),sin(pi/4),10, red
copy 1.3*cos(3*pi/8),1.3*sin(3*pi/8),-1,-1,-1,-1,mathfonts/109/\mphi
copy 1.3*cos(3*pi/2+0.2),1.3*sin(3*pi/2+0.2),-1,-1,-1,-1,mathfonts/109/\mtheta
  }
}
{\text{dessin= xrange -3,3
yrange -3,3
\dessin1
linewidth 2
segment 0,0,2.2,2.2,green
segment 0,0, 2.2,-0.8,green
dsegment 2.2,-0.8,2.2,2.2,black
dsegment 0,2.8,2.2,2.2,black
arrow cos(-pi/16-0.4),sin(-pi/16-0.4),cos(-pi/16-0.2),sin(-pi/16-0.2),10, red
text black, 1.3, -0.6, medium, r
text black, -0.2, 1.5, medium, z
arc 0, 0, 2, 2, 225,335, red
copy 1.3*cos(3*pi/2+0.2),1.3*sin(3*pi/2+0.2),-1,-1,-1,-1,mathfonts/109/theta.gif
}
}
