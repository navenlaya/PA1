Cpt_S 223
PA1: Linux Commands Matching Game

Commands and Description
Advantage: A linked list makes it easy to add and remove commands without shifting everything around. This is useful in the program because new commands can be added or removed without worrying about size limits.

Disadvantage: It takes more memory since each command also stores a pointer to the next one. Searching for a command is also slower because you have to go through the list one by one.

User Profiles
Advantage: An array makes it quick to find a player's profile since you can access it directly by index. This helps when loading a saved game.

Disadvantage: The size is fixed, so if there are more than 100 players, no new profiles can be added unless the array is resized, which would take extra work.
