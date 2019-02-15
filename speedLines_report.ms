.TL
Speed-line Generation Tool for Compositors
.AU
Kristiyan Aladjov
.AB
In this paper I present a semi-automatic method for drawing stylized motion blur in the form of speed-lines within a pre-rendered 3D animation sequence utilizing the information found in secondary images known as AOVs (Arbitrary Output Variables) that most modern offline rendering software is capable of outputting. I proceed to examine and evaluate several possible implementations using The Foundry NUKE Developer Kit, ImageMagick's C++ image processing library (Magick++) and a more manual method using NUKE's pre-existing built-in tools. An overview of the origin, purpose and variation of speed-lines in the variety of fields is also included. A comparison is made between the more common approach of producing these visual elements before the rendering process within a 3D environment and my attempt to draw the element post rendering.
In short the method tracks a certain part of an animated 3D model using the data in the UV pass and then determines the attributes of the speed-lines such as thickness and direction using the data stored in the velocity pass.
.AE
.NH
Introduction
.PP
It can be seen that in recent years the world of Computer Animation is gradually trying to diversify its visual style, moving
away from what is now considered the conventional CG look. A common method is to try to adapt the aesthetic of other visual
of one such element - ''Speed lines''. “Speed lines” is an art technique that is used to convey rapid motion using streaks.
media such as traditional animation, graphic novels etc. This visual imitation occasionally introduce elements that a regular computer animation toolset
has a difficult time replicating. That is why I decided to take on the task of developing a tool that can automate or at least aid in the creation.


.NH 2
Origin of the speed-line
.PP
A range of different  an artistic interpretation of motion blur artefacts present in photographed images.   There is no exact record of when speed-lines were used for the first time but it was most likely in the sphere of advertisement in the early 20\*{th\*} century.
A more popular use of the speed-line is found in comic books where artist would use the technique to depict rapid movements performed by a character. Instructional imagery
on certain products also makes use of speed-lines on their packaging or user manuals. Moving away from static imagery we find speed-lines as well as other stylized blurring
effects being used in motion graphics and traditional animation. Their use in the two media is vastly different. Motion graphics would often put emphasis on these 2D effects and use
them less as a secondary visual element that only enhances the feeling of movement. In some cases the speed-line would be treated as an entity completely separate from any other
moving part of the image. Animation takes the opposite approach and tries to move attention away from the speed-lines using them primarily when producing
.I "smear frames" .
Smearing employs a variety of blurring techniques such as stroboscopic effect and temporal flares but speed-lines still remain an essential component.
-- PUT IMAGE OF SMEAR FRAME HERE --
.NH 2
Different uses

.NH
Context
.PP
Related work

.NH
Hypothesis
.NH 2 
Visual Style
.PP
As seen above speed-lines can have different visual qualities depending on their purpose.--DISCUSS THE PURPOSE-- The visual style that I aim to achieve was
a flat 2D element meaning that it was not affected by lighting, that was widest at its source and gradually narrows down to a single
point at its end. It could be looked at as a middle ground between the thicker, more eye-catching speed-lines seen in motion graphics and
the subtle, sudden style that appears in traditional animation.

-
Unlike similar attempts to implement speed-lines into 3D animation, I chose to approach this as a tool to be used after the 3D rendering
process is complete. At this point in a conventional animation pipeline the user would have access to a variety of utility passes that
contain data which could drive different attributes of the speed-lines. The two utility passes that are necessary for this method to work
are a UV pass which contains data about the UV texture coordinates on a model and a velocity pass that stores the per-pixel rate of translation in
the XYZ axes of the animated 3D model.
- Put image of RGBA, UV, Velocity pass -
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
.TC
