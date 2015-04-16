You need to make a quick change in the project settings for this one (everyone else probably already figured out a solution to this. Patch it in if you know how to fix it).

Go into project properties -- build -- arm compiler -- include options. Under preinclude paths, type in stdbool.h and stdint.h

That should take care of things.