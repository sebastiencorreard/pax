\integer{xmin=-5}
\integer{xmax=5}
\integer{ymin=-5}
\integer{ymax=5}
\integer{xsc=\xmax-\xmin+1}
\integer{ysc=\ymax-\ymin+1}
\text{repere=xrange \xmin,\xmax
yrange \ymin,\ymax
linewidth 2
  parallel \xmin,\ymin,\xmin,\ymax,1,0,\xsc,grey
  parallel \xmin,\ymin,\xmax,\ymin,0,1,\ysc,grey
vline 0,0,black
hline 0,0,black
segment -0.2,1,0.2,1,black
segment 1,-0.2,1,0.2,black
text black,0.7,-0.1,medium,I
text black,-0.4,1,medium,J
text black,-0.3,-0.1,medium,O

segment -0.2,1,0.2,1,black
segment -0.2,3,0.2,3,black
text black,-0.4,3,medium,3
text black,-1,-3,medium,-3
segment -0.2,-3,0.2,-3,black
segment 3,-0.2,3,0.2,black
text black,2.7,-0.2,medium,3
text black,-3.5,-0.2,medium,-3
segment -3,-0.2,-3,0.2,black}
