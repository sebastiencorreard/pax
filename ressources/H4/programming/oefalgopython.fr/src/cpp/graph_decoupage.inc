\text{B1=slib(geo2D/jsxgraph jsxbox1,600 x 200,JXG.Options.point.fixed = false;
JXG.Options.point.showInfobox=true;
JXG.Options.point.highlight=false;
JXG.Options.point.name = "";
JXG.Options.point.face = "[]";
JXG.Options.point.size = 5;
JXG.Options.point.withLabel=true;
const board = JXG.JSXGraph.initBoard('jsxbox1', {axis:false, boundingbox: [-10,2,10,-2],
shownavigation:false,showCopyright : false,
showZoom : true,keepaspectratio : false,
  zoom: {factorX: 1.25,factorY: 1.25,wheel: true,needShift: false,eps: 0.001},
  pan: {needShift: false,enabled: true,needTwoFingers: true,pinchHorizontal: true, pinchVertical: true,pinchSensitivity: 7}});
const xxaxis = board.create('axis', [[0, 0], [1,0]]);
var p1=board.create('point',[-8,0],{name:'a', fixed: true, strokeColor:'black',label: {Color:'blue',offset:[-15,10]}});
var p2=board.create('point',[8,0],{name:'b', fixed: true, strokeColor:'black',label: {Color:'blue'}});

board.create('line',[p1,p2],{straightFirst:false, straightLast:false});
var nn = board.create('slider',[[-8,1.5],[-4,1.5],[1,1,10]],{name:'nombre de sous-intervalles',snapWidth:1});

var dynamicObjects = [];
var glider_xi = null;
var lastN = -1;

function clearDynamic() {
  if (glider_xi !== null) {
    board.removeObject(glider_xi);
    glider_xi = null;
  }
  for (var i = 0; i < dynamicObjects.length; i++) {
    board.removeObject(dynamicObjects[i]);
  }
  dynamicObjects = [];
}

function rebuild() {
  var n = Math.round(nn.Value());
  if (n === lastN) return;
  lastN = n;
  var a = p1.X();
  var b = p2.X();
  var h = (b - a) / n;
  board.suspendUpdate();
  clearDynamic();
  var subdivPoints = [];
  for (var i = 0; i <= n; i++) {
      var xi = a + h * i;
      var pt = board.create('point', [xi, 0], {name: 'x_{' + i + '}', strokeColor: 'green', fillColor: 'green', face: '+', size: 11, fixed: true,showInfobox: false, label: { offset: [0, -18], fontSize: 10 }});
      dynamicObjects.push(pt);
      subdivPoints.push(pt);
      if (i < n) {var txt = board.create('text', [xi + h / 2, 0.5, 'h'], {anchorX: 'middle', fontSize: 12, fixed: true});
        dynamicObjects.push(txt);
      }
  }
var topSeg = board.create('segment', [[a, 0.25], [b, 0.25]], { strokeColor: 'green', strokeWidth: 2, fixed: true});
dynamicObjects.push(topSeg);
glider_xi = board.create('glider', [a, 0, xxaxis], { name: 'x_i',
  showInfobox: false,
  fillColor: 'white', strokeColor: 'red',
  face: 'o', size: 12,
  attractors: subdivPoints,
  attractorDistance: h / 2,
  snatchDistance: h / 2,
  label: { color: 'red', offset: [0, 25], fontSize: 12 }
});
var label_xi = board.create('text', [0, -1, function() {
      var k = Math.round((glider_xi.X() - p1.X()) / h);
      if (k === 0) return 'x_i = a';
      if (k === 1) return 'x_i = a+h';
      return 'x_i = a+' + k + 'h';
    }], { anchorX: 'middle', fontSize: 14, color: 'red', fixed: true });
dynamicObjects.push(label_xi);
board.unsuspendUpdate();
}

rebuild();
nn.on('drag', function() {rebuild();});
)}
