# Development Journal
## Week One
#### Experimenting with Box2D

First, I worked on compiling the actual Box2D source code which caused me a lot of head aches to begin with. My first issue was trying to use Xcode which I am not at all familiar with. this caused many difficulties when I was trying to follow tutorials which included `premake`, `cmake`, and other modules I was unfamiliar with. However, after following some YouTube tutorials and reading the issue reports in Github I was able to compile and run the example code. The included TestBed which I was able to run was extremely cool, even though it had some bugs. It was a good showcase of all the things that Box2D has to offer and many things from the physics engine are things I will need to utilize including: collisions, gravity, and friction. Looking forward I am definitely excited about my project because of the power of Box2D and I think that it will be very helpful for creating my project.

#### Experimenting with OpenFrameworks

After compiling and running the actual Box2D source code, I worked on the OF snake assignment and got my first exposure to OpenFrameworks. After doing a little bit of searching of how to link together OpenFrameworks and Box2D I came across a OpenFrameworks Box2D wrapper. Initially, I cloned the master branch but it did not work. However, after I realized that I changed to the stable build branch and cloned it into the addons section of OpenFrameworks. Using the OpenFrameworks project generator I created a project using the ofBox2D add on. Then, I copied the example code from the ofBox2D repo and was able to get an OpenFrameworks application to open with Box2D incorporated.

#### Take-Aways

Looking forward, I need to become more familiar with the way that the Box2D wrapper works and figure out the best way to integrate Box2D with a GUI. I also need to narrow down which parts of the Box2D library I actually need to use since there is so much that it can do and it would be very easy to get overwhelmed.

## Week Two
#### Road-Blocks

This week I realized that the OpenFrameworksBox2D wrapper does not have all of the functionality that I need. It only has distance joints while I need to have revolute joints and motors in order for my walkers to move in a controlled manner. For this reason, I have decided to not use the wrapper and directly use the Box2D library and draw the world using OFXGui.

Additionally, I noticed that Box2D uses traditional xy-coordinates while OFXGui draws screen coordinates (from the top left corner and positive is downwards). I need to figure out how to transform to fit and draw on to the screen.
#### Progress

So far, I have been working on the layout of my class structure. I have build a PhysicsWorld class and a Walker class, with a Simulation class for the future. Currently, I can generate a world in Box2D when I create a world object as well as 3 circles that will be the nodes for my walker. 

I have bound the nodes and joints together with one revolute joint in the rear and one distance joint in the front of the walker. Also, I have drawn the static nodes and joints in OFDraw.

#### To Do
- [x] Create Box2D world in world object
- [x] Create nodes for walker
- [x] Draw nodes and joints in OFDraw
- [x] Bind nodes with revolute joints
- [ ] Transform Box2D coordinates to screen coordinates
- [ ] Draw everything to visually debug
- [ ] Get basic walking completed 
- [ ] Work on Simulation class for genetic algorithm
