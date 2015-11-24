# gridstack
GridStack is a simple utility to help to prototype GridMove's layouts with a simple DSL.

## Overview of GridMove ##

[GridMove](http://jgpaiva.donationcoders.com/gridmove.html) is a program that
aims at making windows management easier. It helps you with this task by
defining a visual grid on your desktop, to which you can easily snap windows.
This program comes bundled with some predefined grid templates, that can be
easily swaped, but also has ways of creating custom grids or sharing grids made
by others.

GridMove makes moving windows, resizing windows, displaying them on cascade or
on mosaic, making them on top or anything you can think of as easy as drag and
drop.

This tool was made taking in mind those who own big screens and keep organizing
their windows. This program is specially useful for anyone that keeps more than
1 window on the screen at one time, because it helps the user to maximize the
usable space of the monitor, by resizing the windows in a much easier way than
moving and resizing them one by one.

Thanks to its simple interaction methods, GridMove becomes intuitive and fast,
helping you to improve your workflow.

### Features ###

  * 3 different interaction methods to suit everyone's likes
  * Several pre-made grid templates that can be easily swaped
  * Ability to set windows on top and maximize them vertically or horizontally
  * Full keyboard support, which can organize windows with one hotkey press
  * Multi Monitor Support
  * Customizable hotkeys
  * Customizable interface
  * Possibility to create dynamic custom grids
  * Complete help file

### Downloads ###
One can download it from it’s [homepage](http://jgpaiva.donationcoders.com/gridmove.html).

## How to use GridStack ##

First, you should write a special text file, describing window layout.
Usually I save it with an extension **stack**. Suppose, that it has name **my.stack**.
To get a corresponding grid call _gridstack_ in such manner:
`GridStack my.stack my.grid`

### How to define desired layout ###
I’ll show it by example.

![Sample layout](http://xitsa.github.io/gridstack/window_en.png)

Look at the picture. On left top corner is a desired layout.

Defining layout is iterative process of dissecting windows on vertical or horizontal parts.

Lets start with empty window. Thats easy, monitor one has one window, that fills all.
```
Monitor 1
    Window
```
Now split Window on two horizontal parts A and B. Let width of A be 3 times
width of B (and the same height).  So let substitute window by a HStack
construction:
```
Monitor 1
    HStack
        (
            Window 3 #Part A
            Window 1 #Part B
        )
```
Now split Part A on two vertical parts C and D. And let height of C be 2 times
of D (and the same width).
```
Monitor 1
    HStack
        (
            VStack 3 #Part A
                (
                    Window 2 #Part C
                    Window 1 #Part D
                )
            Window 1 #Part B
        )
```
Part C doesn't need any divisions, so let proceed with a part D, that needed to
be split on three horizontal parts.  Lets make them the same. Please note, that
if relative size is equal one, it can be omitted.
```
Monitor 1
    HStack
        (
            VStack 3 #Part A
                (
                    Window 2 #Part C
                    HStack 1 #Part D
                        (
                            Window #Part E
                            Window #Part F
                            Window #Part G
                        )
                )
            Window 1 #Part B
        )
```
We are almost done, and have only part B needed to be split on three vertical
parts H, I and J.
```
Monitor 1
    HStack
        (
            VStack 3 #Part A
                (
                    Window 2 #Part C
                    HStack 1 #Part D
                        (
                            Window #Part E
                            Window #Part F
                            Window #Part G
                        )
                )
            VStack 1 #Part B
                (
                    Window #Part H
                    Window #Part I
                    Window #Part J
                )
        )
```
### What if I want exact size? ###
If, for example you want parts E, F and G to have height 200 pixels use absolute
notation: **`<number>!`** (with an exclamation mark).

Between number and '!' must not be any spaces!
```
Monitor 1
    HStack
        (
            VStack 3 #Part A
                (
                    Window 2 #Part C
                    HStack 200! #Part D has 200 pixels height
                        (
                            Window #Part E
                            Window #Part F
                            Window #Part G
                        )
                )
            VStack 1 #Part B
                (
                    Window #Part H
                    Window #Part I
                    Window #Part J
                )
        )
```
