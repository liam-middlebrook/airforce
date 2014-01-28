Air Force (https://github.com/Sheph/airforce)
=========================

1. About
-------------------

The goal of this project is to create high quality
open-source arcade game that can run on most desktop and
mobile platforms such as Linux, Windows, Android, iOS, etc.

The main reason why I started this projects is because I
wanted to have a mobile game that keeps the gameplay
unique all the time and frequently provides some new
game elements. Modern mobile games such as Angry Birds
are nice, but they get boring quickly, think about it,
all you have to do is to shoot pigs with birds and
yout have 300+ levels of the same stuff. Yes, they
do give you some new bird type from time to time and
the locations are changing, but the gameplay is always
the same, you just shoot pigs with birds.
Now take a look at
Contra Hard Corps - http://www.youtube.com/watch?v=91vYIxt6oDo
Though this is only level 1 you can see that
there's always something new happening, now you're
fighting that fire breathing thing, the next moment building
goes off and you clime it and then some huge monster comes out
and attacks you, etc. One major problem with Contra Hard
Corps however is that it's really hard to play. What I want
to do is to combine the principles of Angry Birds and
Contra Hard Corps - make a game that's both easy and fun
to play and that always brings something new into
gameplay, i.e. keeps the player involved.

2. Status
-------------------

This is still very early prototype, it's a work in progress
and it's pretty far from being done.

3. Building and running
-------------------

Currently it builds and runs only on linux.

In order to simplify building (for myself :)) I keep
third-party dependencies in binary form inside ./lib dir.
If you're on Ubuntu 12.04 32-bit then you won't have
any problems building/running, otherwise you'll probably
have to rebuild these third-party libs yourself...

To build:

cd ./airforce
./cmake_i386_release.sh
cd ../airforce-i386-release
make

To run:

cd ./out/bin
./airforce

Use left and right arrow keys to steer and navigate the world.

4. Contacts
-------------------

I'm Stanislav Vorobiov, contact me at sheffmail@mail.ru if you
want to contribute or you have suggestions/ideas. Thanks.
