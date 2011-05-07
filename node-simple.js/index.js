//Constructor for the NodeSimple class.
NodeSimpleJS = function() {
  this.m_counter = 0;
}

//Use the prototype mechanism to create
//a method on the class.  Normal JS crap, you know.
NodeSimpleJS.prototype.add = function(a, b) {
  return a + b;
}

//Expose the constructor function by
//attaching it to the exports var.
exports.NodeSimpleJS = NodeSimpleJS;


