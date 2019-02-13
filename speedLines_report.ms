.TL
Speedlines Generation Tool for Compositors
.AU
Kristiyan Aladjov
.AB
This is where the abstract goes.
.AE

.NH
Introduction
.PP
It can be seen that in recent years the world of Computer Animation is gradually trying to diversify its visual style, moving
away from what is now considered the conventional CG look. A common method is to try to adapt the aesthetic of other visual
media such as traditional animation, graphic novels etc. This visual imitation occasionally introduce elements that a regular CG toolset
has a difficult time replicating. That is why I decided to take on the task of developing an efficient tool that can automate the creation
of one such element - “Speed lines”. “Speed lines” is an art technique that is used to convey rapid motion using streaks.

.NH 1
Origin of the speed-line
.NH 2
Different uses

.NH
Context
.PP
Related work

.NH
Hypothesis
.PP
-VISUAL STYLE-
As seen above speed-lines can have different visual qualities depending on their purpose. The visual style that I aim to achieve was
a flat 2D element meaning that it was not affected by lighting, that was widest at its source and gradually narrows down to a single
point at its end. It could be looked at as a middle ground between the thicker, more eye-catching speed-lines seen in motion graphics and
the subtle, sudden style that appears in traditional animation.

-
Unlike similar attempts to implement speed-lines into 3D animation, I chose to approach this as a tool to be used after the 3D rendering
process is complete. At this point in a conventional animation pipeline the user would have access to a variety of utility passes that
contain data which could drive different attributes of the speed-lines. The two utility passes that are necessary for this method to work
are a UV pass which contains data about the UV texture coordinates on a model and a velocity pass that stores the per-pixel rate of translation in
the XYZ axes of the animated 3D model.

-
This 2D method of drawing speed-lines has three main steps - choosing a moving point on the animated model (initialization); recording its position on every 
frame that it is visible on (tracking) and using the tracked points to draw a 2D polygon that represents the final speed-line (drawing).
Initializing a speed-line requires us to set up a starting point on a moving part of the image. That is done by giving the point a random XY coordinate
until it lands on a pixel that has RGB values other than zero on both the UV pass and the velocity pass. The UV pass determines  whether
the starting point sits on the object and the velocity pass determines whether that part of the object is moving. Thus we avoid having starting points
that sit outside the model or sit on a non-moving part of the 3D object. For this part the UV pass could be replaced by simply having an alpha channel included
in the velocity pass  but that would needlessly increase the amount of inputs that the user needs to provide since the UV data is still needed for the following step. 
Tracking is where it becomes apparent why the UV pass is required. During initialization every starting point samples the UV colour. The program then proceeds
to scan through subsequent frames in the animation, looking for a pixel with the exact same colour value. The UV pass is useful for this situation since
the color values always remain the same throughout every frame and are attached to the same piece of geometry thus making it the perfect tracking marker for a CG character.
The tracking process ends up outputting an array of points, each having sampled the velocity data at its position on the corresponding frame.
Finally in order to draw the speed-lines -CONTINUE-

.NH 1
Why compositing?
.NH 2
Pre-existing tools
.NH 3
User control
.NH 4
Scattering and tracking 
.PP


.NH
Process
.NH 1
Using the NUKE Developer Kit
.PP
My initial approach was to use the NUKE Development Kit(NDK) so that the tool could be loaded and used within the The Foundry
Nuke compositing package.
.NH 2
Using ImageMagick++
.NH 3
Using NUKE's pre-existing tools
.NH
Analysis
.PP
Critical evaluation of the process and the hypo

.NH
Conclusion
.PP
Final words and future work.

.NH
References
