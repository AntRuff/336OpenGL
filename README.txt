Anthony Ruffalo aruffalo
Brady Soloman bsoloman

Basis of the code comes from Victor Gordon and found at this link https://www.youtube.com/watch?v=45MIykWJ-C4, however all specific work for the assignment
was adapted and created by us. 
Partial version for turn in.

Runs in Visual Studio 2022 IDE, but we can show it working later if that is needed.

Builds a cube with 6 different textures and current moves the cube. x, y, and z move the cube in the negative x, y, and z direction respectively.
Holding shift with any of those keys moves the cube in the positive direction accordingly.

The l, m, and n keys rotate the cube around the x, y, and z axis respetively. Holding shift with any of these keys rotates the cube in the opposite direction.

The r, g, and b keys change the color channels of the light, reducing them to a minimum of 0. Holding shift with any of these keys instead increases the color channel to a max of 1.

The u key moves the light up in space, or down if shift is held. The v key moves the light to the left, or to the right if the shift key is held.

The cube contains 4 sides rendered with a texture containing an image and a GL_LINEAR_MIPMAP_LINEAR filter, and 2 sides rendered with a texture that changes color based on the level.
The last 2 sides are rendered with a different filter, 1 being GL_LINEAR_MIPMAP_LINEAR, and the other is GL_NEAREST_MIPMAP_NEAREST.