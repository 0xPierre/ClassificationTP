# PaintAI 🖌️

[//]: # (To view this page with graphic comfort please follow this link:)
[//]: # (https://github.com/0xPierre/ClassificationTP)

<p align="center">
  <a href="https://gitlab.com/m9712/mygarden/-/blob/master/LICENSE">
    <img src="https://img.shields.io/badge/license-GPLv3-blue.svg?style=flat-square" alt="MyGarden is released under the GPLv3 license." />
  </a>
  <a href="https://liberapay.com/MyGarden/">
    <img src="https://img.shields.io/liberapay/gives/MyGarden.svg?logo=liberapay&style=flat-square" alt="liberapay MyGarden" />
  </a>

</p>


**A simple app to learn numbers**

![](./docs/img.png)

Paint AI is built with kind of Technologies😃:  
[![C](https://img.shields.io/badge/C-3178c6?style=for-the-badge&logo=c&labelColor=gray)](https://www.typescriptlang.org/)
[![Linux](https://img.shields.io/badge/Linux-DD0031?style=for-the-badge&logo=linux&labelColor=gray)](https://kernel.org)

## Enhancement 🚄

- Add GUI interface
- Add sigmoid activation function
- Add entropy feature
- Add multi threading tree creation
- Convolution matrix
- Real time number recognized
- Save learnings in a file
- Add bagging (Intances and Features)
- Dataset editing (colors filters, copy...)
- Search for the best hyperparameters.

**More details below 👇️**

##### Add GUI interface
In order to have a better user experience we designed a beautiful paint area to
unleash your potential.

We made the choice to use SDL, the most popular cross-platform GUI utility in c.
SDL is an easy library to use (almost 😁) to create complex interface in seconds.
We also use SDL to manage sound in the app sound

##### Add sigmoid activation function
The sigmoid activation function is used to have better results while evaluating trees.
With this method all the tree is cross which avoid to miss the best solution.

In details a score is calculated for each node and duplicated with his parents.
When all leafs are reach, the leaf with the highest score is returned.

##### Add entropy feature
Another methode to compute impurity with log math function.

##### Add multi threading tree creation
Creating trees are very slow... to save times multi threading is the best option.
So by default when a random forest is created all the available CPU core are used to perform the action in a minimum of time.
OpenMP is used here for this task.

##### Convolution matrix
In image processing, a convolution matrix (or kernel) is a small matrix used for blurring,
sharpening, edge detection, and other operations on an image.
It involves sliding the matrix over the image and performing a mathematical (median operation for our project) operation at each step.

##### Real time number recognized
When you draw on the GUI app the number is recognized automatically in real time.

##### Add sound when writing
Add sound just for fun 🤣

##### Save learnings in a file
Creating trees can take a while even with multithreading. That why we added the possibility to save trains tree
in a file. And when you need the trained tree, you have just to load it again !!
Magic no ?

##### Add bagging (Intances and Features)
The idea behind this idea is to have efficient tree able to quickly sort instances.
For this we need trees with uniq split characteristics and bagging allow to do that.
Instead, to take all the instances and all the features we take randomly few of them to have bigger diversity and get better results.

##### Dataset editing (colors filters, copy...)
Improve dataset quality by removing parasite pixels and more...

##### Search for the best hyperparameters.
Have a good function is good but have good functions and coefficient parameters is better 😆.
That why we created several functions to find the best coefficient for our functions.
We used an AWS server with 24 CPU core to do this.

## How to contribute 🚀

Thank you for your contribution to the open source world !😍

- Contact us by email
- Open a MR

## Support 🛟

If you need assistance or want to ask a question about the app, you are welcome to ask for support in our
Forums.
If you have found a bug, feel free to open a new Issue on Gitlab.

## Licence 📜

The app core is under GPLv3 but be careful Images and sounds data are limited are restricted to
copyright.
