# CChat
By Winston Venderbush, Max Bertfield, and Jack Schluger

<hr>

### What is CChat?
CChat is a comprehensive chatroom program written in C. Users can host a server with the inclued server files and set up chatrooms that can be joined by clients on local or networked connections. Users can then seamlessly interact with other users in the chatroom, making use of our custom <b>CChat Markup Language</b> to spice-up their messages!

<hr>

### How to use it?
<b>Note</b>: <i>CChat has no dependencies! It is written entirely in native C, which makes it easy to use and quick to set up!</i>

1. Simply compile the program by typing a quick command: `$ make`
2. Once the files are compiled, start a server using `$ ./server`
3. Open a client by typing: `$ ./client`
4. Once the server is running, a client can connect to it after choosing a username by typing in that server's local or network IP address (if port forwarding is enabled)
5. To ensure you have a complete installation of CChat, your download should include:
`server.c`
`server.h`
`client.c`
`client.h`
`markup.c`
`markup.h`
`networking.c`
`networking.h`
`makefile`

<hr>

### CChat Markup Language (CML)

CChat comes with its own custom markup language for adding flare to your messages! You can use the markup language in any message or even when creating your username!

####Emojis
CML has a collection of emojis that you can access in chatrooms by tags that begin and end with `~~`. The tags are as follows:

* `~~smile~~` -- Inserts the `ʘ‿ʘ` emoji
* `~~shrug~~` -- Inserts the `¯\_(ツ)_/¯` emoji
* `~~scared~~` -- Inserts the `⊙﹏⊙` emoji
* `~~disapprove~~` -- Inserts the `ಠ_ಠ` emoji
* `~~cute~~` -- Inserts the `(｡◕‿◕｡)` emoji
* `~~excited~~` -- Inserts the `ヽ(*▽*)/` emoji
* `~~devious~~` -- Inserts the `ಠ‿ಠ` emoji
* `~~tableflip~~` -- Inserts the `(╯°□°）╯︵ ┻━┻` emoji
* `~~cat~~` -- Inserts the `^ᵒᴥᵒ^` emoji
* `~~fight~~` -- Inserts the `ლ(｀ー´ლ)` emoji
* `~~bear~~` -- Inserts the `ʕ•ᴥ•ʔ` emoji
* `~~blob~~` -- Inserts the `༼ つ ◕_◕ ༽つ` emoji
* `~~cry~~` -- Inserts the `ಥ_ಥ` emoji
* `~~love~~` -- Inserts the `(づ￣ ³￣)づ` emoji
* `~~confused~~` -- Inserts the `(⊙_☉)` emoji
* `~~fightme~~` -- Inserts the `(ง •̀_•́)ง` emoji
* `~~hiding~~` -- Inserts the `|_・)` emoji
* `~~sleep~~` -- Inserts the `(ᴗ˳ᴗ)` emoji

####Colors
With CML, you can also change the color of text in the chatroom by using tags that begin and end with `::`. The tags are as follows:

* `::red::` -- Sets the following text to red
* `::black::` -- Sets the following text to black
* `::white::` -- Sets the following text to white
* `::green::` -- Sets the following text to green
* `::yellow::` -- Sets the following text to yellow
* `::blue::` -- Sets the following text to blue
* `::magenta::` -- Sets the following text to magenta
* `::cyan::` -- Sets the following text to cyan
* `::basic::` -- Sets the following text back to the default terminal color scheme

<hr>

###Known Bugs
1. When multiple clients connect and one disconnects, certain clients might not receive messages until a new client connects. To resolve this bug, create another client and connect to the server, then quit it, and messages should flow normally
2. Sometimes the server has a messy exit if a user closes clients rapidly, resulting in error 17 - fifo already exists. If this happens, you can easily reset the server interface by following these steps.
  1. Stop the server. Press `CTRL + C` repeatedly until the server stops.
  2. Enter `$ ls -a` into your terminal to see all files in the directory.
  3. Remove all files of this format: .# where # is any number (for example: `$ rm .0`)
  4. Restart the server using `$ ./server`
  5. Your server should restart cleanly. If it does not, give the socket time to naturally close and try again.
3. Exting clients with anything other than CTRL-C will crash the server
4. Exiting the server with anything other than CTRL-C will crash all the client
5. If a client is typing and a message is sent, that client displays a white bar before the message.
<hr>

We hope you enjoy using CChat!






