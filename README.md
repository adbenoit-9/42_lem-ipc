# LEM-IPC (@42Paris)
*A simple IPC game*

## Usage
```
$ git clone https://github.com/adbenoit-9/42_lem-ipc.git
$ cd 42_lem-ipc
$ make
$ ./lemipc [options]
```

## Description

**IPC (inter-process communication)**: Enable communication between separate processes using shared memory and message queues.

### Game rules

The idea is to have players (gathered in teams) battle on a 2D board. For a team to be victorious, they will have to be the last team on the board.
When a player dies, they disappear from the board.
For a player to be killed, they must be touched by at least 2 players from the same team, that is, one adjacent tile to the tile the target stands on (diagonal works). Of course, the killing team will have to be different from the target’s. When a player understands they’re surrounded by at least 2 players from another and same team, he must leave the board and end their execution.
One board tile will only take one player at a time.

### Options

Running the program with no options will start the game if it is not and will show the map.

<p style="margin-top: 1em;">
    <strong>--help</strong><br>
    Print help info and exit.<br><br>
    <strong>--team</strong> <ins>id</ins><br>
    Create a player from the team [id] (must be a number between 1 and 9).<br><br>
</p>


