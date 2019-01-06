Droplet
=======

**WARNING:** This is a in-progress repository and pretty much everything is subject to change at any time! So its advisable to consider this reference rather than a usable plugin at this stage.

Droplet is a mixture of some pretty old code - spruced and tidied - along with some newer nodes. The idea is to provide a utility plugin for maya which exposes some useful nodes to help minimise graph complexity and simplify the implmeentation of some common rigging paradigms.

As the repository matures and becomes stable I'll update this page to reflect which parts are reliable and not subject to change.

Nodes
=====

Stacks
------

The idea behind stacks are to be able to perform basic arithmetic on multiple values simultaneously. These types of operations - such as calculating the sum of more than two values - typically require you to create multiple built-in nodes and chain the results together. Stacks mitigate this by allowing you to input as many values as required.

Droplet has took the approach of not utilising an operator attribute to define the behaviour of the node. Instead droplet opts for implementing the different operations as completely different nodes for the following reasons:

* At-a-glance understanding of what a node is doing
* Less code required to generate behaviours (no need to set operator attributes)
* Easier to read code - no 'node.operation.set(2)' - where the value is meaningless without ingrained knowledge
* Less complexity within the compute function of any individual node

Stacks come in two different flavours - floats or angles. Using angle stacks are useful when wanting to operate on rotations but want to avoid increased graph complexity of unit conversion nodes.

Stack Node List:

    FloatStackSum : Adds all the inputs together
    FloatStackMinus : Negates each number from the last negation
    FloatStackMul : Multiplies each input value together
    FloatStackDivide : Divides each value in sequence from one-another
    FloatStackRange : Returns the range between the maximum and minimum value
    FloatStackMin : Returns the smallest value of all the inputs
    FloatStackMax : Returns the largest value of all the inputs
    FloatStackSum : Adds all the inputs together
    AngleStackMinus : Negates each number from the last negation
    AngleStackMul : Multiplies each input value together
    AngleStackDivide : Divides each value in sequence from one-another
    AngleStackRange : Returns the range between the maximum and minimum value
    AngleStackMin : Returns the smallest value of all the inputs
    AngleStackMax : Returns the largest value of all the inputs

Rigging
-------

This holds a series of nodes which implement common rigging paradigms. The goal here is to minimise node complexity and repetition.

Rigging Node List:

    Soft2BoneIk : This takes in two world transforms and calculates the bone lengths for a 2 bone (3 joint) chain. Soft Ik prevents the ik snap which can occur during hyper extension

Compiled Plug-ins
=================

All the source is available if you want to compile it. However, until the repository stabilises there will only be Maya 2018 (x64-windows) plugins available.

Contributions
=============
Given that this is a relatively new module it is always appreciated if you can communicate any bugs, issues, ideas or recommendations to mike@twisted.space